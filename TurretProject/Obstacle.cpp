#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle()
{
	m_position = sf::Vector2f(0, 0);
}

void Obstacle::Initialise(sf::Vector2f pos,int x,int y,int z,int radius)
{
	if (!m_texture.loadFromFile("asteroid.png"))
	{
		//error
	}
	m_position = pos;
	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(100, 100);
	m_sprite.setRotation(m_rotation);
	rotateSpeed = rand() % (40 - 20) + 20;
	m_rotation = 0;
	m_radius = radius;
	m_sprite.setColor(sf::Color(x, y, z));

	if (m_radius == 40)
		m_sprite.setScale(0.7,0.7);
	else if (m_radius == 80)
		m_sprite.setScale(1, 1);
	else if (m_radius == 110)
		m_sprite.setScale(1.3, 1.3);
}

void Obstacle::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

bool Obstacle::IsColliding(sf::Vector2f targetPosition, int targetRadius)
{
	float distance = sqrt((targetPosition.x - m_position.x)*(targetPosition.x - m_position.x) + (targetPosition.y - m_position.y)*(targetPosition.y - m_position.y));
	if (distance < m_radius + targetRadius)		//collision occurs
	{
		//std::cout << "COLLISION" << std::endl;
		return true;	//return true
	}
	else
	{
		return false;	//return false
	}
}

void Obstacle::Rotate(float time)
{
	m_rotation += time * rotateSpeed;
	m_sprite.setRotation(m_rotation);
}