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
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(40, 35);//40,40
	m_radius = 30;
	m_speed = 100;
	maxSpeed = 500;
	forward_speed = 0;
	m_rotation = -90;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	m_pos = sf::Vector2f(1350, 1800);
	m_sprite.setPosition(m_pos);
	fired = false;
	firedTime = 0;
	firedTimeControl = 0.2;
	fireSide = false;
	
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Rotation(1, time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
	{
		Rotation(-1, time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (forward_speed <= maxSpeed)
			forward_speed += 10;
		for (int i = 0; i < 5;i++)
			ParticleSystem::GetInstance()->addParticle(m_pos,1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (forward_speed >= 10)
			forward_speed -= 10;
	}
	else if (forward_speed >= 3)
		forward_speed -= 3;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fired == false && Energy::GetInstance()->GetEnergy() >= 0.25)
	{
		sound.play();
		Energy::GetInstance()->Shot1();

		if (fireSide == false)
			BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x - 17 + (m_direction.x * 35), m_pos.y + (m_direction.y * 35)));	//(m_pos.x - 17 + (m_direction.x * 120), m_pos.y + (m_direction.y * 120))	// cos(toRadians(m_rotation)
		else 
			BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x + 10 + (m_direction.x * 35), m_pos.y + (m_direction.y * 35)));	//(m_pos.x + 10 + (m_direction.x * 120), m_pos.y + (m_direction.y * 120))	// sin(toRadians(m_rotation)

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

}

void Player::Draw(sf::RenderWindow& window)
{
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

float Player::toRadians(float degrees)
{
	return (degrees * 3.14) / 180;
}

void Player::Rotation(int dir, float t)
{
	m_rotation += 1.5 * m_speed * t * dir;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
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