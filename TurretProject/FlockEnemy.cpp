#include "stdafx.h"
#include "FlockEnemy.h"
#include "ParticleSystem.h"
#include "Score.h"

FlockEnemy::FlockEnemy()
{
}

void FlockEnemy::Initialise()
{
	if (!m_texture.loadFromFile("flockship.png")) //**************
	{
		//error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(32, 32);
	m_rotation = 0;
	m_sprite.setRotation(m_rotation);
	m_alive = true;
	m_radius = 50;
	int r, g, b;
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
	m_sprite.setColor(sf::Color(r, g, b));

	buffer.loadFromFile("Explosion.wav");
	explosionSound.setBuffer(buffer);
	explosionSound.setVolume(50);
}

bool FlockEnemy::Update(float time)
{
	if (m_alive)
	{
		m_sprite.setPosition(m_position);
		m_sprite.setRotation(m_rotation);
		WrapAroundScreen();
		return true;
	}
	else
	{
		return false;
	}
}

void FlockEnemy::Draw(sf::RenderWindow& window)
{
	if (m_alive == true)
	{
		window.draw(m_sprite);
	}
}

void FlockEnemy::WrapAroundScreen()
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

bool FlockEnemy::Colliding(bool playerKilledMe, sf::Vector2f playerPos)
{
	if (m_alive == true)
	{
		for (int i = 0; i < 25; i++)
		{
			ParticleSystem::GetInstance()->addParticle(m_position, 0);
			ParticleSystem::GetInstance()->addParticle(m_position, 1);
		}
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
			explosionSound.setVolume(30);
		}
		else if (DistanceFrom(playerPos) > 300)
		{
			explosionSound.setVolume(40);
		}
		explosionSound.play();

		if (DistanceFrom(playerPos) < 300)
		{
			explosionSound.setVolume(50);
		}

		int score = Score::GetInstance()->getScore();
		if (playerKilledMe == true)
		{
			Score::GetInstance()->setScore(score + 10);
		}
		m_alive = false;
		return true;		//return true
	}
	else
		return false;
}

bool FlockEnemy::IsColliding(sf::Vector2f targetPosition, int targetRadius)
{
	if (m_alive == true)
	{
		//float distance = sqrt((targetPosition.x - m_position.x)*(targetPosition.x - m_position.x) + (targetPosition.y - m_position.y)*(targetPosition.y - m_position.y));
		if (DistanceFrom(targetPosition) < m_radius + targetRadius)		//collision occurs
		{
			//m_alive = false;
			return true;		//return true
		}
		else
		{
			return false;	//return false
		}
	}
	return false;
}

float FlockEnemy::DistanceFrom(sf::Vector2f player)
{
	float len = sqrt((player.x - m_position.x)*(player.x - m_position.x) + (player.y - m_position.y)*(player.y - m_position.y));
	return len;
}