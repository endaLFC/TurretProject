#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	if (!m_texture.loadFromFile(" "))
	{
		// error...
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(1, 1);
	m_pos = sf::Vector2f(0, 0);

	m_speed = 100;
	m_rotation = 0;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	m_pos = sf::Vector2f(5, 5);
}


Bullet::~Bullet()
{
}

void Bullet::Update(float time)
{
	Move(time);
}

void Bullet::Move(float time)
{
	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(m_rotation);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
	{
		
	}

}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

float Bullet::toRadians(float degrees)
{
	return (degrees * 3.14) / 180;
}

void Bullet::Rotation(int dir, float t)
{
	m_rotation += m_speed * t * dir;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
}
