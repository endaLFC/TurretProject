#include "stdafx.h"
#include "BulletManager.h"

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
	if (!m_texture.loadFromFile("BulletSprite.png"))
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
	bullets.push_back(b);
}

void BulletManager::Update(float time)
{
	list<Bullet>::iterator it = bullets.begin();
	for (it = bullets.begin(); it != bullets.end(); ++it)
	{
		if (!it->Update(time))
		{
			//remove from vector 
			//reset iterator 
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