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
	void Update(float time);
	void Draw(sf::RenderWindow &window);
	bool IsColliding(Enemy *enemy);
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

