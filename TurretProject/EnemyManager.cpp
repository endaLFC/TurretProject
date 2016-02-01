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
	if (!m_texture.loadFromFile("TIE_Fighter.png")) //**************
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

void EnemyManager::Update(float time, sf::Vector2f playerPos)
{
	list<Enemy>::iterator it = enemies.begin();
	for (it = enemies.begin(); it != enemies.end();)
	{
		if (!it->Update(time, playerPos))
		{
			it = enemies.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void EnemyManager::Draw(sf::RenderWindow &window)
{
	list<Enemy>::iterator it = enemies.begin();
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		it->Draw(window);
	}
}

bool EnemyManager::IsColliding(sf::Vector2f targetPosition, int targetRadius)
{
		list<Enemy>::iterator it = enemies.begin();
		for (it = enemies.begin(); it != enemies.end();)
		{
			if (it->IsColliding(targetPosition, targetRadius))
			{
				it = enemies.erase(it);
				return true;
			}
			else
			{
				++it;
			}
		}
		return false;
}


list<Enemy>* EnemyManager::GetEnemies()
{
	return &enemies;
}