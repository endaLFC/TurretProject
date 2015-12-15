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
	m_pos = { 300, 600 };
	//m_sprite.setPosition(m_pos);
	if (!m_texture.loadFromFile("laser.png"))
	{
		//error
	}
	m_sprite.setTexture(m_texture);
}

Energy::~Energy()
{
}

void Energy::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
