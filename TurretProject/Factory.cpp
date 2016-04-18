#include "stdafx.h"
#include "Factory.h"
#include "ParticleSystem.h"
#include "Score.h"

Factory::Factory()
{
}

void Factory::Initialise()
{
	if (!m_texture.loadFromFile("factory.png")) //**************
	{
		//error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(55, 55);
	m_rotation = 0;
	m_sprite.setRotation(m_rotation);
	m_alive = true;
	m_health = 3;
	m_radius = 50;
	smokeOn = false;
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

bool Factory::Colliding(bool playerKilledMe, sf::Vector2f playerPos)
{
	if (m_alive == true)
	{
		if (m_health > 0 && playerKilledMe == true)		//if the player hits the factory and the factory has health then damage the factory
		{
			m_health -= 1;
			damageSound.play();
			return true;		//return true
		}
		else
		{
		//float distance = sqrt((targetPosition.x - m_position.x)*(targetPosition.x - m_position.x) + (targetPosition.y - m_position.y)*(targetPosition.y - m_position.y));
			for (int i = 0; i < 30; i++)
			{
				ParticleSystem::GetInstance()->addParticle(m_position, 0);
				ParticleSystem::GetInstance()->addParticle(m_position, 1);
			}
			DistantSound(playerPos);		//decreases the volume of sound effects the further away the explosion occurs from the player
			
			int score = Score::GetInstance()->getScore();
			if (playerKilledMe == true)
			{
				Score::GetInstance()->setScore(score + 50);
			}
			m_alive = false;
			return true;		//return true
		}
	}
	else
		return false;
}

void Factory::DistantSound(sf::Vector2f playerPos)
{
	if (DistanceFrom(playerPos) > 600)
	{
		explosionSound.setVolume(10);
	}
	else if (DistanceFrom(playerPos) > 500)
	{
		explosionSound.setVolume(20);
	}
	else if (DistanceFrom(playerPos) > 400)
	{
		explosionSound.setVolume(40);
	}
	else if (DistanceFrom(playerPos) > 300)
	{
		explosionSound.setVolume(50);
	}
	if (DistanceFrom(playerPos) < 300)
	{
		explosionSound.setVolume(60);
	}
	explosionSound.play();
}

bool Factory::IsColliding(sf::Vector2f targetPosition, int targetRadius)
{
	if (m_alive == true)
	{
		if (DistanceFrom(targetPosition) < m_radius + targetRadius)		//collision occurs
		{
			return true;		//return true
		}
		else
		{
			return false;	//return false
		}
	}
	return false;
}

float Factory::DistanceFrom(sf::Vector2f player)
{
	float len = sqrt((player.x - m_position.x)*(player.x - m_position.x) + (player.y - m_position.y)*(player.y - m_position.y));
	return len;
}

void Factory::Smoke(float time)
{
	if (m_health >= 1 && m_health <= 2)
	{
		ParticleSystem::GetInstance()->addParticle(m_position, 1);
		smokeOn = true;
	}
	else if (m_health == 0)
	{
		ParticleSystem::GetInstance()->addParticle(m_position, 0);
		ParticleSystem::GetInstance()->addParticle(m_position, 1);
		
		smokeOn = true;
	}

}