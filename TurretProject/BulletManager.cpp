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
	buffer.loadFromFile("Explosion.wav");
	sound.setBuffer(buffer);
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

bool BulletManager::IsColliding()
{
   	bool collision = false;
	list<Bullet>::iterator it = bullets.begin();
	for (it = bullets.begin(); it != bullets.end();)
	{
		bool hit = false;
		list<Enemy>* enemies = EnemyManager::GetInstance()->GetEnemies();
		for (list<Enemy>::iterator Enemyit = enemies->begin(); Enemyit != enemies->end();)
		{
			if (it->IsColliding(Enemyit->GetPosition(), Enemyit->GetRadius()))
			{
				sound.play();
				int playerScore = Score::GetInstance()->getScore();
				Score::GetInstance()->setScore(playerScore + 10);
				for (int i = 0; i < 100; i++)
				{
					ParticleSystem::GetInstance()->addParticle(Enemyit->GetPosition());
				}

				it = bullets.erase(it);
				Enemyit = enemies->erase(Enemyit);
				hit = true;
				collision = true;				
				break;
			}
			else
			{
				++Enemyit;
			}
		}
		if (!hit)
		{
			++it;
		}
		
	}
	return collision;
}

