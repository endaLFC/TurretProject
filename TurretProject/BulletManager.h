#pragma once
#include "vector"
#include "list"
#include "Bullet.h"
#include "EnemyManager.h"
#include "Player.h"
using namespace std;

class BulletManager
{
public:
	static BulletManager* GetInstance();
	~BulletManager();
	void Init();
	void PlayerFire(float rotation, sf::Vector2f position);
	void Update(float time);
	void Draw(sf::RenderWindow &window);
	bool IsColliding(sf::Vector2f targetPosition, int targetRadius, bool targetAlive);
private:
	BulletManager()
	{
		bullets = list<Bullet>();
	}
	list<Bullet> bullets;
	sf::Texture m_texture;
	static bool instanceFlag;
	static BulletManager* instance;
};

