#include "stdafx.h"
#include "Enemy.h"
#include "ParticleSystem.h"

//PUBLIC
Enemy::Enemy()
{
	//m_sprite.setOrigin(40, 35);

	/*m_speed = 100;
	m_rotation = 0;
	m_sprite.setrotation(m_rotation);
	m_direction = sf::vector2f(cos(toradians(m_rotation)), sin(toradians(m_rotation)));
	m_position = sf::vector2f(0, 0);
	m_alive = true;*/
}

Enemy::Enemy(sf::Vector2f pos, float speed)
{
	/*m_sprite.setOrigin(40, 35);
	m_speed = speed;
	m_rotation = 0;
	m_sprite.setRotation(m_rotation);
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	m_alive = true;*/
	m_position = sf::Vector2f(pos.x, pos.y);
}

void Enemy::Initialise(sf::Texture * text)
{
	m_texture = text;
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(40, 35);
	m_speed = 50;
	m_rotation = 0;
	m_sprite.setRotation(m_rotation);
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	m_alive = true;
	int x = rand() % 800;
	int y = rand() % 10;
	m_health = 2;

	smokeOn = 0;

	m_position = sf::Vector2f(x, y);
	int r, g, b;
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
	m_sprite.setColor(sf::Color(r, g, b));
}

bool Enemy::Update(float time, sf::Vector2f playerPos)
{
	if (m_alive)
	{
		GetDirection(playerPos);
		Move(time, playerPos);
		WrapAroundScreen();
		Smoke(time);
		return true;
	}
	else {
		return false;
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	if (m_alive == true)
	{
		m_sprite.setRotation(m_rotation);
		window.draw(m_sprite);
	}
	
}


//PRIVATE

void Enemy::Move(float time, sf::Vector2f playerPos)
{
	if (m_alive == true)
	{
			m_position += m_direction * time * m_speed;
			m_sprite.setPosition(m_position);
	}
}

void Enemy::WrapAroundScreen()
{
	if (m_position.x > 800)
		m_position.x = 0;
	else if (m_position.x < 0)
		m_position.x = 800;

	if (m_position.y > 600)
		m_position.y = 0;
	else if (m_position.y < 0)
		m_position.y = 600;

}

void Enemy::Rotation(int dir)
{
	m_rotation += 0.1 * dir;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
}

float Enemy::toRadians(float degrees)
{
	return (degrees * 3.14) / 180;
}

void Enemy::GetDirection(sf::Vector2f playerPos)
{
	sf::Vector2f dir = playerPos - m_position;
	dir = Normalise(dir);
	//m_direction = dir;

	m_direction = SlowTurn(m_direction, dir);

	m_rotation = atan2f(m_direction.y, m_direction.x) * 180 / 3.14;
	//m_rotation = atan2f(dir.y, dir.x) * 180 / 3.14;
	m_sprite.setRotation(m_rotation);
}

sf::Vector2f Enemy::Normalise(sf::Vector2f vec)
{
	float len = sqrt(vec.x * vec.x + vec.y * vec.y);
	return sf::Vector2f(vec.x / len, vec.y / len);
}

float Enemy::DistanceFrom(sf::Vector2f enemy, sf::Vector2f player)
{
	float len = sqrt((player.x - enemy.x)*(player.x - enemy.x) + (player.y - enemy.y)*(player.y - enemy.y));
	return len;
}

sf::Vector2f Enemy::SlowTurn(sf::Vector2f m_direction, sf::Vector2f dir)
{
	if (m_direction.x < dir.x)
		m_direction.x += 0.0001;
	else if (m_direction.x > dir.x)
		m_direction.x -= 0.0001;

	if (m_direction.y < dir.y)
		m_direction.y += 0.0001;
	else if (m_direction.y > dir.y)
		m_direction.y -= 0.0001;

	return m_direction;
}

bool Enemy::IsColliding(sf::Vector2f targetPosition, int targetRadius)
{
	if (m_alive == true)
	{
		//float distance = sqrt((targetPosition.x - m_position.x)*(targetPosition.x - m_position.x) + (targetPosition.y - m_position.y)*(targetPosition.y - m_position.y));
		if (DistanceFrom(targetPosition, m_position) < m_radius + targetRadius)		//collision occurs
		{
			std::cout << "COLLISION" << std::endl;
			m_alive = false;
			return true;		//return true
		}
		else
		{
			return false;	//return false
		}
	}
	return false;
}

void Enemy::Smoke(float time)
{
	if (smokeOn == true)
	{
		smokeOnTime += time;
		if (smokeOnTime >= 0.01)
		{
			smokeOnTime = 0;
			smokeOn = false;
		}
	}
	
	if (m_health == 1 && smokeOn == false)
	{
		ParticleSystem::GetInstance()->addParticle(m_position, 1);
		smokeOn = true;
	}
	else if (m_health == 0 && smokeOn == false)
	{
		ParticleSystem::GetInstance()->addParticle(m_position, 0);
		for (int i = 0; i < 10; i++)
		{
			ParticleSystem::GetInstance()->addParticle(m_position,1);
		}
		smokeOn = true;
	}
	
}