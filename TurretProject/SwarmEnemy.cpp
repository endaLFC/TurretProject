#include "stdafx.h"
#include "SwarmEnemy.h"
#include "ParticleSystem.h"
#include "Score.h"

SwarmEnemy::SwarmEnemy()
{
}

void SwarmEnemy::Initialise()
{
	if (!m_texture.loadFromFile("swarmenemy.png")) //**************
	{
		//error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(15, 11);
	m_rotation = 0;
	m_sprite.setRotation(m_rotation);
	m_alive = true;
	m_radius = 15;
	int r, g, b;
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
	m_sprite.setColor(sf::Color(255, 255, 255));

	buffer.loadFromFile("Explosion.wav");
	explosionSound.setBuffer(buffer);
	explosionSound.setVolume(25);
}

bool SwarmEnemy::Update(float time)
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

void SwarmEnemy::Draw(sf::RenderWindow& window)
{
	if (m_alive == true)
	{
		window.draw(m_sprite);
	}
}

void SwarmEnemy::WrapAroundScreen()
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

bool SwarmEnemy::IsColliding()
{
	if (m_alive == true)
	{
		for (int i = 0; i < 50; i++)
		{
			ParticleSystem::GetInstance()->addParticle(m_position, 0);
			ParticleSystem::GetInstance()->addParticle(m_position, 1);
		}
		explosionSound.play();

		int score = Score::GetInstance()->getScore();
		Score::GetInstance()->setScore(score + 5);
		m_alive = false;
		return true;		//return true
	}
	else
		return false;
}

float SwarmEnemy::DistanceFrom(sf::Vector2f player)
{
	float len = sqrt((player.x - m_position.x)*(player.x - m_position.x) + (player.y - m_position.y)*(player.y - m_position.y));
	return len;
}