#pragma once
#include "vector"
#include "list"
#include "Bullet.h"
#include "Enemy.h"
using namespace std;

class EnemyManager
{
public:
	static EnemyManager* GetInstance();
	~EnemyManager();
	void Init();
	void CreateEnemy(sf::Vector2f position);
	void Update(float time, sf::Vector2f playerPos);
	void Draw(sf::RenderWindow &window);
	bool IsColliding(sf::Vector2f targetPosition, int targetRadius);

	list<Enemy>* GetEnemies();
private:
	EnemyManager()
	{
		enemies = list<Enemy>();
	}
	list<Enemy> enemies;
	sf::Texture m_texture;
	static bool instanceFlag;
	static EnemyManager* instance;
};

