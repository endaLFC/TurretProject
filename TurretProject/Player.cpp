#include "stdafx.h"
#include "Player.h"
#include "Score.h"
#include "Energy.h"
#include "ParticleSystem.h"

Player::Player()
{
	
}

void Player::Initialise()
{
	if (!font.loadFromFile("TELE2.TTF")) //  digital-7.regular
	{
		//handle error
	}


	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		text[i].setCharacterSize(15);
	}

	text[0].setFont(font);
	text[0].setColor(sf::Color::White);
	text[0].setString("Score: ");
	text[0].setPosition(sf::Vector2f(25, 17));

	text[1].setFont(font);
	text[1].setColor(sf::Color::White);
	text[1].setString("X");
	text[1].setPosition(sf::Vector2f(225, 17));

	text[2].setFont(font);
	text[2].setColor(sf::Color::White);
	text[2].setString("ap: ");
	text[2].setPosition(sf::Vector2f(290, 17));

	text[3].setFont(font);
	text[3].setColor(sf::Color::White);
	text[3].setPosition(sf::Vector2f(115, 17));


	//if (!m_texture.loadFromFile("flakcannonx.png"))
	if (!m_texture.loadFromFile("Spaceship.png"))
	{
		// error...
	}
	if (!m_lockedTexture.loadFromFile("lock.png"))
	{
		// error...
	}
	if (!m_unlockedTexture.loadFromFile("unlock.png"))
	{
		// error...
	}
	if (!m_lockingTexture.loadFromFile("locking.png"))
	{
		// error...
	}
	if (!m_landingzoneTexture.loadFromFile("landingzone.png"))
	{
		// error...
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(40, 35);//40,40

	m_lockSprite.setTexture(m_lockedTexture);
	m_landingzoneSprite.setTexture(m_landingzoneTexture);

	lockSpeed = 50;

	m_radius = 30;
	m_speed = 100;
	maxSpeed = 500;
	forward_speed = 0;
	m_rotation = 270;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	m_pos = startPos;
	m_sprite.setPosition(m_pos);
	m_lockSprite.setPosition(227, 628);
	m_landingzoneSprite.setPosition(1130,1500);
	fired = false;
	firedTime = 0;
	firedTimeControl = 0.2;
	fireSide = false;
	locked = true;
	turretMode = TURRET;

	buffer.loadFromFile("blaster-firing.wav");
	sound.setBuffer(buffer);
}


Player::~Player()
{

}

void Player::Update(float time)
{
	if (shrink == true && speedBoost == true)
	{
		m_sprite.setScale(0.75, 0.75);
		m_radius = 20;
		m_sprite.setColor(sf::Color::Yellow);
	}
	else if (shrink == true && speedBoost == false)
	{
		m_sprite.setScale(0.75, 0.75);
		m_radius = 20;
		m_sprite.setColor(sf::Color::Cyan);				//sf::Color(50, 190, 150));
	}
	else if (speedBoost == true && shrink == false)
	{
		m_sprite.setColor(sf::Color::Magenta);				//sf::Color(50, 190, 150));
	}

	if (locked == true && turretMode == LOCKING)
		slowLock(time);


	Move(time);
	WrapAroundScreen();
	text[3].setString(to_string(Score::GetInstance()->getScore()));
	if (Score::GetInstance()->getScore() >= 500)
		text[3].setColor(sf::Color::Red);
	else if (Score::GetInstance()->getScore() == 420)
		text[3].setColor(sf::Color::Green);
	else if (Score::GetInstance()->getScore() >= 400)
		text[3].setColor(sf::Color::Cyan);
	else if (Score::GetInstance()->getScore() >= 300)
		text[3].setColor(sf::Color::Yellow);
	else if (Score::GetInstance()->getScore() >= 200)
		text[3].setColor(sf::Color::Magenta);
	else if (Score::GetInstance()->getScore() >= 100)
		text[3].setColor(sf::Color::Blue);
}

void Player::Move(float time)
{
	m_pos += m_direction * time * forward_speed;
	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(m_rotation);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && turretMode != LOCKING)
	{
		Rotation(1, time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && turretMode != LOCKING)
	{
		Rotation(-1, time);
	}
	if (locked == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (forward_speed <= maxSpeed)
				forward_speed += 10;
			for (int i = 0; i < 5; i++)
				ParticleSystem::GetInstance()->addParticle(m_pos, 1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (forward_speed >= 10)
				forward_speed -= 10;
		}
		else if (forward_speed >= 3)
			forward_speed -= 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fired == false && Energy::GetInstance()->GetEnergy() >= 0.25 && turretMode != LOCKING)
	{
		sound.play();
		Energy::GetInstance()->Shot1();

		if (fireSide == false)
		{
			float xBefore = 10;
			float yBefore = -25;
			float xAfter = xBefore * cos(toRadians(m_rotation)) - yBefore * sin(toRadians(m_rotation));
			float yAfter = xBefore * sin(toRadians(m_rotation)) + yBefore * cos(toRadians(m_rotation));

		
			BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x + xAfter, m_pos.y + (yAfter)));	//(m_pos.x - 17 + (m_direction.x * 120), m_pos.y + (m_direction.y * 120))	// cos(toRadians(m_rotation)
		}
		else
		{
			float xBefore = 10;
			float yBefore = 25;
			float xAfter = xBefore * cos(toRadians(m_rotation)) - yBefore * sin(toRadians(m_rotation));
			float yAfter = xBefore * sin(toRadians(m_rotation)) + yBefore * cos(toRadians(m_rotation)) ;
		
			BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x + xAfter, m_pos.y + (yAfter)));	//(m_pos.x + 10 + (m_direction.x * 120), m_pos.y + (m_direction.y * 120))	// sin(toRadians(m_rotation)
		}

		fired = true;
	}


	if (fired == true)
	{
		firedTime+=time;
		if (firedTime >= firedTimeControl)
		{
			firedTime = 0;
			fired = false;

			if (fireSide == false)
				fireSide = true;
			else
				fireSide = false;
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && locked == true && turretMode == TURRET)
	{
		unlockStuff();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && locked == false && isInLockZone() == true)
	{
		lockStuff();
	}

}

void Player::Draw(sf::RenderWindow& window)
{
	if (locked == false)
	{
		window.draw(m_landingzoneSprite);
	}

	window.draw(m_sprite);
	/*for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(text[i]);
	}*/
}

void Player::DrawScore(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(text[i]);
	}
}

void Player::DrawLock(sf::RenderWindow& window)
{
	window.draw(m_lockSprite);
}

float Player::toRadians(float degrees)
{
	return (degrees * 3.14) / 180;
}

void Player::Rotation(int dir, float t)
{
	m_rotation += 1.5 * m_speed * t * dir;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));


	if (m_rotation >= 360)
	{
		m_rotation = m_rotation - 360;
	}
	else if (m_rotation < 0)
	{
		m_rotation = 360 - m_rotation;
	}

}

void Player::WrapAroundScreen()
{
	if (m_pos.x > 2400)
		m_pos.x = 0;
	else if (m_pos.x < 0)
		m_pos.x = 2400;

	if (m_pos.y > 1800)
		m_pos.y = 0;
	else if (m_pos.y < 0)
		m_pos.y = 1800;
}

bool Player::isInLockZone()	//checking if the player is in the landing zone and can lock into turret
{//1130,1500
	if (m_pos.x > 1130 && m_pos.x < 1550 && m_pos.y > 1500 && m_pos.y < 1800)
		return true;
	else
		return false;
}

void Player::lockStuff()		//things to do when locked
{
	m_lockSprite.setTexture(m_lockingTexture);
	forward_speed = 0;
	turretMode = LOCKING;
	locked = true;
}

void Player::unlockStuff()		//things to do when unlocked
{
	m_lockSprite.setTexture(m_unlockedTexture);
	forward_speed = 250;
	turretMode = SPACESHIP;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	locked = false;
}

void Player::slowLock(float t)
{
	if (m_pos.x < startPos.x + 3 && m_pos.x > startPos.x - 3)
		m_pos.x = startPos.x;
	else if (m_pos.x < startPos.x)
		m_pos.x += lockSpeed * t;
	else if (m_pos.x > startPos.x)
		m_pos.x -= lockSpeed * t;

	if (m_pos.y < startPos.y + 3 && m_pos.y > startPos.y - 3)
		m_pos.y = startPos.y;
	else if (m_pos.y < startPos.y)
		m_pos.y += lockSpeed * t;
	else if (m_pos.y > startPos.y)
		m_pos.y -= lockSpeed * t;

	if (m_rotation < 272 && m_rotation > 268)
		m_rotation = 270;
	else if (m_rotation > 270)
		m_rotation -= lockSpeed * t;
	else if (m_rotation < 270)
		m_rotation += lockSpeed * t;
	
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));


	if (m_pos == startPos && m_rotation == 270)
	{
		turretMode = TURRET;
		m_lockSprite.setTexture(m_lockedTexture);
	}
}