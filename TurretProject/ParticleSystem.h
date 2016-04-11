#pragma once
#include "vector"
#include "list"
#include "Particle.h"


using namespace std;

class ParticleSystem
{
public:
	static ParticleSystem* GetInstance();
	~ParticleSystem();
	void Init();
	void addParticle(sf::Vector2f newPos, int type);
	void Update(float time);
	void Draw(sf::RenderWindow &window);
	
private:
	ParticleSystem()
	{
		
	}
	list<Particle*> particles;
	

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Texture m_SmokeTexture;
	sf::Sprite m_SmokeSprite;

	static bool instanceFlag;
	static ParticleSystem* instance;

	sf::Vector2f Normalise(sf::Vector2f vec);
};

