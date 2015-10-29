#include "stdafx.h"
#include "Player.h"



Player::Player()
{
	if (!m_texture.loadFromFile("cannon.png"))
	{
		// error...
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(25, 120);
	m_pos = sf::Vector2f(0, 0);

	m_speed = 500;
	m_rotation = 0;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	m_pos = sf::Vector2f(400, 570);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Rotation(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Rotation(-1);
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

float Player::toRadians(float degrees)
{
	return (degrees * 3.14) / 180;
}

void Player::Rotation(int dir)
{
	m_rotation += 0.05 * dir;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
}
