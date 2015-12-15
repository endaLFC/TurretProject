#include "stdafx.h"
#include "Particle.h"


Particle::Particle(sf::Vector2f position, sf::Vector2f direction, float speed, int t)
{
	m_pos = position;
	m_direction = direction;
	m_alive = true;
	m_speed = speed;
	timeAlive = 0;
	timeToLive = ((rand() % 200) / 100) + 0.2;
	opacity = 255;
	type = t;
}

Particle::~Particle()
{
}

void Particle::Update(float time)
{
	m_pos += m_direction * time * m_speed;

	timeAlive += time;

	if (timeAlive > timeToLive)
	{
		m_alive = false;
	}
	opacity -= time * 200;
		

}
