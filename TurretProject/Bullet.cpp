#include "stdafx.h"
#include "Bullet.h"
#include "Energy.h"

Bullet::Bullet(float rotation, sf::Vector2f position)
{
	
	m_pos = position;
	m_rotation = rotation;
	alive = true;
	m_speed = 1000;
}

void Bullet::Initialise(sf::Texture * text)
{
	m_texture = text;
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(15, 10);
	int r, g, b;
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
	if (Energy::GetInstance()->GetEnergy() < 0.15)
		m_sprite.setColor(sf::Color(255 * Energy::GetInstance()->GetEnergy() ,255,255));
	else
		m_sprite.setColor(sf::Color(255, 255, 255));
}



Bullet::~Bullet()
{
}

bool Bullet::Update(float time)
{
	Move(time);

	if (m_pos.x > 2400 || m_pos.x < 0 || m_pos.y < 0 || m_pos.y > 1800)
		alive = false;

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

bool Bullet::IsColliding(sf::Vector2f targetPosition, int targetRadius, bool targetAlive)
{
	float distance = sqrt((targetPosition.x - m_pos.x)*(targetPosition.x - m_pos.x) + (targetPosition.y - m_pos.y)*(targetPosition.y - m_pos.y));
	if (distance < m_radius + targetRadius && alive == true && targetAlive == true)		//collision occurs
	{
		std::cout << "COLLISION" << std::endl;
		return true;	//return true
	}
	else
	{
		return false;	//return false
	}
}
