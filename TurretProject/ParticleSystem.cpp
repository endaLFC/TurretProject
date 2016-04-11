#include "stdafx.h"
#include "ParticleSystem.h"


bool ParticleSystem::instanceFlag = false;
ParticleSystem* ParticleSystem::instance = NULL;

ParticleSystem* ParticleSystem::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new ParticleSystem;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Init()
{
	if (!m_texture.loadFromFile("explosion.png"))
	{
		//error
	}
	m_sprite.setTexture(m_texture);

	if (!m_SmokeTexture.loadFromFile("Smoke.png"))
	{
		//error
	}
	m_SmokeSprite.setTexture(m_SmokeTexture);
}

void ParticleSystem::addParticle(sf::Vector2f position, int type)
{
	

	sf::Vector2f direction = sf::Vector2f((rand() % 100) - 50, (rand() % 100) - 50);
	Particle* p = new Particle(position, Normalise(direction) ,rand() % 250, type);

	particles.push_back(p);

}

void ParticleSystem::Update(float time)
{

	list<Particle*>::iterator it = particles.begin();
	for (it = particles.begin(); it != particles.end();)
	{
		(*it)->Update(time);
		if ((*it)->GetAlive())
		{
			++it;
		}
		else
		{
       
			delete (*it);
			it = particles.erase(it);
			//remove from list 
		}
	}

	

}

void ParticleSystem::Draw(sf::RenderWindow &window)
{
	for each (Particle* p in particles)
	{
		
		/*int r, g, b;
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;*/

		m_sprite.setColor(sf::Color(255, 255, 255, p->getOpacity()));
		m_SmokeSprite.setColor(sf::Color(255, 255, 255, p->getOpacity()));
		if (p->GetType() == 0)
		{
			m_sprite.setPosition(p->GetPosition());
			window.draw(m_sprite);
		}
		else if (p->GetType() == 1)
		{
			m_SmokeSprite.setPosition(p->GetPosition());
			window.draw(m_SmokeSprite);
		}
		
	}

}

sf::Vector2f ParticleSystem::Normalise(sf::Vector2f vec)
{
	float len = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	return vec / len;
}
