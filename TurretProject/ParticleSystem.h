#pragma once
#include "vector"
#include "list"
#include "Bullet.h"
using namespace std;

class ParticleSystem
{
public:
	static ParticleSystem* GetInstance();
	~ParticleSystem();
	void Init();
	void addParticle(sf::Vector2f newPos);
	void Update(float time);
	void Draw(sf::RenderWindow &window);

private:
	list<sf::Vector2f> m_pos;
	list<sf::Vector2f> m_dir;

	list<float> m_angle;
	list<float> m_force;

	list<int> timeToLive;
	list<int> timeAlive;
	
	sf::Texture m_texture;

	static bool instanceFlag;
	static ParticleSystem* instance;
};

