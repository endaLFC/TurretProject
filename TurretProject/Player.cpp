#include "stdafx.h"
#include "Player.h"
#include "Score.h"


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
	text[0].setPosition(sf::Vector2f(185, 17));

	text[1].setFont(font);
	text[1].setColor(sf::Color::White);
	text[1].setString("X");
	text[1].setPosition(sf::Vector2f(385, 17));

	text[2].setFont(font);
	text[2].setColor(sf::Color::White);
	text[2].setString("ap: ");
	text[2].setPosition(sf::Vector2f(460, 17));

	text[3].setFont(font);
	text[3].setColor(sf::Color::White);
	text[3].setPosition(sf::Vector2f(275, 17));


	if (!m_texture.loadFromFile("flakcannonx.png"))
	{
		// error...
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(40, 40);
	m_radius = 40;
	m_speed = 100;
	m_rotation = -90;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	m_pos = sf::Vector2f(400, 600);
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
	Move(time);
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
	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(m_rotation);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_rotation < -45)
	{
		Rotation(1, time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_rotation > -135)
	{
		Rotation(-1, time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fired == false)
	{
		sound.play();

		if (fireSide == false)
			BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x - 17 + (m_direction.x * 120), m_pos.y + (m_direction.y * 120)));
		else 
			BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x + 10 + (m_direction.x * 120), m_pos.y + (m_direction.y * 120)));

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
	m_rotation += m_speed * t * dir;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
}
