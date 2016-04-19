#include "stdafx.h"
#include "Powerup.h"


Powerup::Powerup()
{
	m_position = sf::Vector2f(0, 0);
}

void Powerup::Initialise(sf::Vector2f asteroidPos, sf::Vector2f asteroidPos2, sf::Vector2f asteroidPos3, int type)
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
	
	o = 255;
	
	x = rand() % 2100 + 50;
	y = rand() % 700 + 50;
	sf::Vector2f tempPos(x, y);

	while (OverlappingAsteroid(asteroidPos, asteroidPos2, asteroidPos3, tempPos) == true)
	{
		x = rand() % 2100 + 50;
		y = rand() % 700 + 50;
		sf::Vector2f tempPos(x, y);
	}

	if (OverlappingAsteroid(asteroidPos, asteroidPos2, asteroidPos3, tempPos) == false)
	{
		m_position = tempPos;
	}
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

	buffer.loadFromFile("pickup.wav");
	sound.setBuffer(buffer);
}

void Powerup::Draw(sf::RenderWindow& window)
{
	if (o > 0)
		window.draw(m_sprite);
}

bool Powerup::IsColliding(sf::Vector2f targetPosition, int targetRadius)
{
	if (m_alive == true)
	{
		float distance = sqrt((targetPosition.x - m_position.x)*(targetPosition.x - m_position.x) + (targetPosition.y - m_position.y)*(targetPosition.y - m_position.y));
		if (distance < m_radius + targetRadius)		//collision occurs
		{
			sound.play();
			m_alive = false;
			return true;	//return true
		}
	}
	return false;	//return false
}

void Powerup::Rotate(float time)
{
	if (m_alive == true)
	{
		m_rotation += time * rotateSpeed;
		m_sprite.setRotation(m_rotation);
	}
}

void Powerup::Fade(float time)
{
	if (o >= 0)
	{
		o -= time * 800;
		m_sprite.setColor(sf::Color::Color(255,255,255, o));
	}
}

void Powerup::Update(float time)
{
	Fade(time);
}

bool Powerup::OverlappingAsteroid(sf::Vector2f asteroidPos, sf::Vector2f asteroidPos2, sf::Vector2f asteroidPos3, sf::Vector2f powerUpPos)
{
	if (powerUpPos.x < asteroidPos.x + 70 && powerUpPos.x > asteroidPos.x - 70 && powerUpPos.y < asteroidPos.y + 70 && powerUpPos.y > asteroidPos.y - 70)	//if within bounds of asteroid 1
	{
		return true;
	}
	else if (powerUpPos.x < asteroidPos2.x + 100 && powerUpPos.x > asteroidPos2.x - 100 && powerUpPos.y < asteroidPos2.y + 100 && powerUpPos.y > asteroidPos2.y - 100)	//if within bounds of asteroid 2
	{
		return true;
	}
	else if (powerUpPos.x < asteroidPos3.x + 150 && powerUpPos.x > asteroidPos3.x - 150 && powerUpPos.y < asteroidPos3.y + 150 && powerUpPos.y > asteroidPos3.y - 150)	//if within bounds of asteroid 3
	{
		return true;
	}
	else
	{
		return false;
	}
}
