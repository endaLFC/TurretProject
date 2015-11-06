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

}

void ParticleSystem::addParticle(sf::Vector2f position)
{
	
}

void ParticleSystem::Update(float time)
{

}

void ParticleSystem::Draw(sf::RenderWindow &window)
{
	
}
