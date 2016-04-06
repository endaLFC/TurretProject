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
	m_alive = true;

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
	if (!m_texture.loadFromFile("spacecraft3.png"))
	{
		// error...
	}
	if (!m_poweruptexture.loadFromFile("spacecraftpowerup1.png"))
	{
		// error...
	}
	if (!m_powerup2texture.loadFromFile("spacecraftpowerup2.png"))
	{
		// error...
	}
	if (!m_powerup3texture.loadFromFile("spacecraftpowerup3.png"))
	{
		// error...
	}
	if (!m_dockTexture.loadFromFile("spacecraft4.png"))
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
	m_sprite.setOrigin(110, 85);//40,40

	m_dockSprite.setTexture(m_dockTexture);
	m_dockSprite.setOrigin(110, 85);//40,40

	m_lockSprite.setTexture(m_lockedTexture);
	m_landingzoneSprite.setTexture(m_landingzoneTexture);

	lockSpeed = 50;

	m_radius = 70;
	m_speed = 100;
	maxSpeed = 500;
	forward_speed = 0;
	m_rotation = 270;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	startPos = sf::Vector2f(1350, 1700);
	m_pos = startPos;
	m_sprite.setPosition(m_pos);
	m_dockSprite.setPosition(startPos);
	m_dockSprite.setRotation(m_rotation);
	m_lockSprite.setPosition(239, 647);
	m_landingzoneSprite.setPosition(1130,1500);
	fired = false;
	fired2 = false;
	firedTime = 0;
	firedTimeControl = 0.2;
	fireSide = false;
	locked = true;
	turretMode = TURRET;

	buffer.loadFromFile("blaster-firing.wav");
	sound.setBuffer(buffer);

	buffer2.loadFromFile("takeoff.wav");
	sound2.setBuffer(buffer2);

	fireBuffer.loadFromFile("thrusters.wav");
	fireSound.setBuffer(fireBuffer);

	lockBuffer.loadFromFile("lockingin.wav");
	lockSound.setBuffer(lockBuffer);

	lockinBuffer.loadFromFile("lockin.wav");
	lockinSound.setBuffer(lockinBuffer);

	deadBuffer.loadFromFile("playerdead.wav");
	deadSound.setBuffer(lockinBuffer);

	turretRot = 0;

	vol = 50;

	sound.setVolume(40);
	fireSound.setVolume(vol);
}


Player::~Player()
{

}

void Player::Update(float time)
{
	if (m_alive == true)
	{

		if (turretMode == TURRET)
		{
			turretRot = m_rotation;
		}
		else if (turretMode == LOCKING)
		{
			if (turretRot < 272 && turretRot > 268)
				turretRot = 270;
			else if (turretRot > 270)
				turretRot -= lockSpeed * time;
			else if (turretRot < 270)
				turretRot += lockSpeed * time;
		}

		if (shrink == true && speedBoost == true)
		{
			m_sprite.setScale(0.75, 0.75);
			m_radius = 20;
			m_sprite.setTexture(m_powerup3texture);
		}
		else if (shrink == true && speedBoost == false)
		{
			m_sprite.setScale(0.75, 0.75);
			m_radius = 20;
			m_sprite.setTexture(m_powerup2texture);
		}
		else if (speedBoost == true && shrink == false)
		{
			m_sprite.setTexture(m_poweruptexture);
		}

		if (locked == true && turretMode == LOCKING)
			slowLock(time);


		Move(time);
		WrapAroundScreen();

	}

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
			vol = 50;

			if (fireSound.getStatus() != fireSound.Playing)
				fireSound.play();
			if (forward_speed <= maxSpeed)
				forward_speed += 10;
			for (int i = 0; i < 5; i++)
				ParticleSystem::GetInstance()->addParticle(m_pos, 1);

			m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (forward_speed >= 30)
				forward_speed -= 10;
		}
		if (forward_speed >= 23)
			forward_speed -= 3;

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			vol -= time * 50;
			if (vol <= 1)
			{
				vol = 0;
				fireSound.stop();
			}
				
		}

		fireSound.setVolume(vol);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && Energy::GetInstance()->GetEnergy() >= 0.25 && turretMode != LOCKING)
	{
		if (turretMode == TURRET && fired == false)
		{
			sound.play();
			Energy::GetInstance()->Shot1();

			if (fireSide == false)
			{
				float xBefore = 80;
				float yBefore = -45;
				float xAfter = xBefore * cos(toRadians(m_rotation)) - yBefore * sin(toRadians(m_rotation));
				float yAfter = xBefore * sin(toRadians(m_rotation)) + yBefore * cos(toRadians(m_rotation));


				BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x + xAfter, m_pos.y + (yAfter)));	//(m_pos.x - 17 + (m_direction.x * 120), m_pos.y + (m_direction.y * 120))	// cos(toRadians(m_rotation)
			}
			else
			{
				float xBefore = 80;
				float yBefore = 45;
				float xAfter = xBefore * cos(toRadians(m_rotation)) - yBefore * sin(toRadians(m_rotation));
				float yAfter = xBefore * sin(toRadians(m_rotation)) + yBefore * cos(toRadians(m_rotation));

				BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x + xAfter, m_pos.y + (yAfter)));	//(m_pos.x + 10 + (m_direction.x * 120), m_pos.y + (m_direction.y * 120))	// sin(toRadians(m_rotation)
			}
			fired = true;
		}
		else if (turretMode == SPACESHIP && fired2 == false)
		{
			sound.play();
			Energy::GetInstance()->Shot1();

			float xBefore = 80;
			float yBefore = 0;
			float xAfter = xBefore * cos(toRadians(m_rotation)) - yBefore * sin(toRadians(m_rotation));
			float yAfter = xBefore * sin(toRadians(m_rotation)) + yBefore * cos(toRadians(m_rotation));

			BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x + xAfter, m_pos.y + (yAfter)));

			fired2 = true;
		}

		
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

	if (fired2 == true)
	{
		firedTime += time;
		if (firedTime >= firedTimeControl*2)
		{
			firedTime = 0;
			fired2 = false;
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && locked == true && turretMode == TURRET)
	{
		sound2.play();
		unlockStuff();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && locked == false && isInLockZone() == true)
	{
		lockSound.play();
		lockStuff();
	}

}

void Player::Draw(sf::RenderWindow& window)
{
	if (locked == false)
	{
		window.draw(m_landingzoneSprite);
	}
	m_dockSprite.setRotation(turretRot);

	if (m_alive == true)
		window.draw(m_sprite);

	window.draw(m_dockSprite);
	

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
	if (m_rotation >= 360)
	{
		m_rotation = m_rotation - 360;
	}
	else if (m_rotation < 0)
	{
		m_rotation = 360 - m_rotation;
	}

	m_rotation += 1.5 * m_speed * t * dir;
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
	if (fireSound.Playing)
		fireSound.stop();


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
	if (m_rotation >= 360)
	{
		m_rotation = m_rotation - 360;
	}
	else if (m_rotation < 0)
	{
		m_rotation = 360 - m_rotation;
	}


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
	else if (m_rotation > 270 || m_rotation <= 90)
		m_rotation -= lockSpeed * t;
	else if (m_rotation < 270)
		m_rotation += lockSpeed * t;
	
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));


	if (m_pos == startPos && m_rotation == 270)
	{
		lockinSound.play();
		lockSound.stop();
		turretMode = TURRET;
		m_lockSprite.setTexture(m_lockedTexture);
	}
}

void Player::SetAlive(bool x)
{ 
	if (m_alive == true && x == false)
	{
		if (fireSound.Playing)
		{
			fireSound.stop();
		}

		deadSound.play();
		
		for (int i = 0; i < 500; i++)
		{
			ParticleSystem::GetInstance()->addParticle(m_pos, 1);
			ParticleSystem::GetInstance()->addParticle(m_pos, 0);
		}
		m_alive = x;
	}
}