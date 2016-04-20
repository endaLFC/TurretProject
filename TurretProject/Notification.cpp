#include "stdafx.h"
#include "Notification.h"


Notification::Notification()
{
}


Notification::~Notification()
{
}

void Notification::Initialise()
{
	if (!font.loadFromFile("TELE2.TTF"))
	{
		//handle error
	}
	if (!m_texture.loadFromFile("block2.png"))
	{
		//error
	}
	m_position = sf::Vector2f(130,-50);
	m_textPosition = sf::Vector2f(m_position.x + 17, m_position.y + 15);
	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_alive = true;
	inPosition = false;
	waitTime = 0;
	text.setFont(font);
	text.setString("DESTROY ALL ENEMIES");
	text.setColor(sf::Color::Black);
	text.setScale(0.38, 0.9);
	text.setPosition(m_textPosition);

}

void Notification::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(text);
}

void Notification::Update(float time)
{
	if (m_alive == true)
	{
		if (m_position.y <= 10.0)
		{
			m_position.y += time * 10;
			m_textPosition.y += time * 10;
		}
		else
		{
			inPosition = true;
		}

		if (inPosition == true)
		{
			waitTime += time;
		}
		if (waitTime > 5)
		{
			m_position.y -= time * 5;
			m_textPosition.y -= time * 5;
		}
		if (m_position.y <= -100)
		{
			m_alive = false;
		}
	}
}