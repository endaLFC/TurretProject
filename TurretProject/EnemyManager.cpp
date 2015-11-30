#include "stdafx.h"
#include "EnemyManager.h"

bool EnemyManager::instanceFlag = false;
EnemyManager* EnemyManager::instance = NULL;

EnemyManager* EnemyManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new EnemyManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
void EnemyManager::Init()
{
	if (!m_texture.loadFromFile("BulletSprite.png")) //**************
	{
		//error
	}
}

EnemyManager::~EnemyManager()
{

}


void EnemyManager::CreateEnemy(sf::Vector2f position)
{
	Enemy e(position, 50);
	e.Initialise(&m_texture);
	enemies.push_back(e);
}

void EnemyManager::Update(float time)
{
	list<Enemy>::iterator it = enemies.begin();
	for (it = enemies.begin(); it != enemies.end();)
	{
		if (!it->Update(time))
		{
			it = enemies.erase(it);
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

bool BulletManager::IsColliding(Enemy *enemy)
{
	if (enemy->GetAlive() == true)
	{
		list<Bullet>::iterator it = bullets.begin();
		for (it = bullets.begin(); it != bullets.end();)
		{
			if (it->IsColliding(enemy->GetPosition(), enemy->GetRadius()))
			{
				it = bullets.erase(it);
				return true;
			}
			else
			{
				++it;

			}
		}
		return false;
	}
}