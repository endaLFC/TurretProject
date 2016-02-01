#include "stdafx.h"
#include "Powerup.h"


Powerup::Powerup()
{
	m_position = sf::Vector2f(0, 0);
}

void Powerup::Initialise(sf::Vector2f pos, int type)
{
	m_type = type;
	if (m_type == 0)
	{
		if (!m_texture.loadFromFile("powerup.png"))
		{
			//error
		}
	}
	else if (m_type == 1)
	{
		if (!m_texture.loadFromFile("powerup2.png"))
		{
			//error
		}
	}
	
	
	m_position = pos;
	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(30, 30);
	m_rotation = 0;
	m_sprite.setRotation(m_rotation);
	rotateSpeed = rand() % (40 - 20) + 20;
	m_rotation = -90;
	m_radius = 20;
	m_sprite.setColor(sf::Color(255, 255, 255));
	m_alive = true;
}

void Powerup::Draw(sf::RenderWindow& window)
{
	if (m_alive == true)
		window.draw(m_sprite);
}

bool Powerup::IsColliding(sf::Vector2f targetPosition, int targetRadius)
{
	if (m_alive == true)
	{
		float distance = sqrt((targetPosition.x - m_position.x)*(targetPosition.x - m_position.x) + (targetPosition.y - m_position.y)*(targetPosition.y - m_position.y));
		if (distance < m_radius + targetRadius)		//collision occurs
		{
			m_alive = false;
			return true;	//return true
		}
		else
		{
			return false;	//return false
		}
	}
}

void Powerup::Rotate(float time)
{
	if (m_alive == true)
	{
		m_rotation += time * rotateSpeed;
		m_sprite.setRotation(m_rotation);
	}
}