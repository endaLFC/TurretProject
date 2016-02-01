#include "stdafx.h"
#include "Factory.h"
#include "ParticleSystem.h"

Factory::Factory()
{
}

void Factory::Initialise()
{
	if (!m_texture.loadFromFile("TIE_Fighter.png")) //**************
	{
		//error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(40, 35);
	m_rotation = 0;
	m_sprite.setRotation(m_rotation);
	m_alive = true;
	m_health = 3;
	m_radius = 50;
	smokeOn = false;
	/*int r, g, b;
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;*/
	m_sprite.setColor(sf::Color(255, 255, 255));

	buffer.loadFromFile("Explosion.wav");
	explosionSound.setBuffer(buffer);
	damageBuffer.loadFromFile("damage.wav");
	damageSound.setBuffer(damageBuffer);
}

bool Factory::Update(float time)
{
	if (m_alive)
	{
		m_sprite.setPosition(m_position);
		m_sprite.setRotation(m_rotation);
		WrapAroundScreen();
		Smoke(time);
		SpawnPredator(time);
		return true;
	}
	else 
	{
		return false;
	}
}

bool Factory::SpawnPredator(float time)
{
	float spawnTimer = 0;
	spawnTimer += time;

	if (spawnTimer > 0.1)
	{
		cout << "YOLO "<< endl;
		spawnTimer = 0;
		return true;
	}
	else
		return false;
}

void Factory::Draw(sf::RenderWindow& window)
{
	if (m_alive == true)
	{
		window.draw(m_sprite);
	}
}

void Factory::WrapAroundScreen()
{
	if (m_position.x > 2400)
		m_position.x = 0;
	else if (m_position.x < 0)
		m_position.x = 2400;

	if (m_position.y > 1800)
		m_position.y = 0;
	else if (m_position.y < 0)
		m_position.y = 1800;
}

bool Factory::IsColliding()
{
	if (m_alive == true)
	{
		if (m_health > 0)
		{
			m_health -= 1;
			damageSound.play();
		}
		else
		{
		//float distance = sqrt((targetPosition.x - m_position.x)*(targetPosition.x - m_position.x) + (targetPosition.y - m_position.y)*(targetPosition.y - m_position.y));
		//std::cout << "COLLISION in factory" << std::endl;
			explosionSound.play();
			m_alive = false;
			return true;		//return true
		}
	}
	else
		return false;
}

float Factory::DistanceFrom(sf::Vector2f player)
{
	float len = sqrt((player.x - m_position.x)*(player.x - m_position.x) + (player.y - m_position.y)*(player.y - m_position.y));
	return len;
}

void Factory::Smoke(float time)
{
	/*if (smokeOn == true)
	{
 		smokeOnTime += time;
		if (smokeOnTime >= 0.01)
		{
			smokeOnTime = 0;
			smokeOn = false;
		}
	}*/

	if (m_health >= 1 && m_health <= 2)// && smokeOn == false)
	{
		ParticleSystem::GetInstance()->addParticle(m_position, 1);
		smokeOn = true;
	}
	else if (m_health == 0)// && smokeOn == false)
	{
		ParticleSystem::GetInstance()->addParticle(m_position, 0);
		ParticleSystem::GetInstance()->addParticle(m_position, 1);
		smokeOn = true;
	}

}