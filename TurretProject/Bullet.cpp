#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(float rotation, sf::Vector2f position)
{
	
	m_pos = position;
	m_rotation = rotation;
	alive = true;
	m_speed = 300;
}

void Bullet::Initialise(sf::Texture * text)
{
	m_texture = text;
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(5, 7.5);
}



Bullet::~Bullet()
{
}

bool Bullet::Update(float time)
{

	Move(time);
	return alive;
}

void Bullet::Move(float time)
{
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	m_pos += m_direction * time * m_speed;
	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(m_rotation);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

float Bullet::toRadians(float degrees)
{
	return (degrees * 3.14) / 180;
}

void Bullet::Rotation(int dir)
{
	m_rotation += m_speed * dir;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
}
