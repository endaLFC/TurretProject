#include "stdafx.h"
#include "Player.h"




Player::Player()
{
	
}

void Player::Initialise()
{
	if (!m_texture.loadFromFile("newcannon.png"))
	{
		// error...
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(40, 40);
	m_pos = sf::Vector2f(0, 0);

	m_speed = 100;
	m_rotation = -90;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	m_pos = sf::Vector2f(400, 570);
	//b1.Initialise(m_rotation,m_pos);
}


Player::~Player()
{

}

void Player::Update(float time)
{
	Move(time);
}

void Player::Move(float time)
{
	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(m_rotation);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_rotation < 0)
	{
		Rotation(1, time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_rotation > -180)
	{
		Rotation(-1, time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		BulletManager::GetInstance()->PlayerFire(m_rotation,m_pos);
	}

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	//if (b1.GetAlive() == true)
	//	b1.Draw(window);
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
