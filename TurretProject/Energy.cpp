#include "stdafx.h"
#include "Energy.h"

bool Energy::instanceFlag = false;
Energy* Energy::instance = NULL;

Energy* Energy::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new Energy;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void Energy::Initialise()
{
	if (!m_texture.loadFromFile("laser2.png"))
	{
		//error
	}
	energyWidth = 1;
	m_pos = { 495, 15 };
	m_sprite.setOrigin(0, 0);
	m_sprite.setPosition(m_pos);
	m_sprite.setTexture(m_texture);
}

Energy::~Energy()
{
}

void Energy::Update(float time)
{
	if (energyWidth <= 1)
		energyWidth += time * 0.5;

	m_sprite.setScale(energyWidth, 1);
	m_sprite.setColor(sf::Color(255* energyWidth, 255, 255));
}

void Energy::Shot1()
{
	energyWidth -= 0.2;
}

void Energy::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
