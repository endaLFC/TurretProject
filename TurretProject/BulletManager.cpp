#include "stdafx.h"
#include "BulletManager.h"
#include "ParticleSystem.h"
#include "Score.h"

bool BulletManager::instanceFlag = false;
BulletManager* BulletManager::instance = NULL;

BulletManager* BulletManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new BulletManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
void BulletManager::Init()
{
	if (!m_texture.loadFromFile("laser.png"))
	{
		//error
	}
}

BulletManager::~BulletManager()
{

}


void BulletManager::PlayerFire(float rotation, sf::Vector2f position)
{
	Bullet b(rotation, position);
	b.Initialise(&m_texture);
	//b.Initialise(NULL);
	bullets.push_back(b);
}

void BulletManager::Update(float time)
{
	list<Bullet>::iterator it = bullets.begin();
	for (it = bullets.begin(); it != bullets.end();)
	{
		if (!it->Update(time))
		{	
			it = bullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void BulletManager::Draw(sf::RenderWindow &window)
{
	list<Bullet>::iterator it = bullets.begin();
	for (it = bullets.begin(); it != bullets.end(); ++it)
	{
		it->Draw(window);
	}
}

bool BulletManager::IsColliding(sf::Vector2f targetPosition, int targetRadius, bool targetAlive)
{
	bool collision = false;
	list<Bullet>::iterator it = bullets.begin();
	for (it = bullets.begin(); it != bullets.end();)
	{
		if (it->IsColliding(targetPosition, targetRadius, targetAlive))
		{
			it = bullets.erase(it);
			collision = true;
			break;
		}
		if (!collision)
		{
			++it;
		}
	}
	return collision;
}

