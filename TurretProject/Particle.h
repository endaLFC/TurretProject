#pragma once
#include "SFML\Graphics.hpp"

class Particle
{
public:
	Particle(sf::Vector2f position, sf::Vector2f direction, float speed, int type);
	~Particle();

	void Update(float time);
	sf::Vector2f GetPosition(){ return m_pos; }
	bool GetAlive() { return m_alive; }
	float GetTimePercentageLeft() { return (timeToLive - timeAlive / timeToLive )* 100;  }
	float getOpacity(){ return opacity; }
	int GetType() { return type; }

protected:
	sf::Vector2f m_pos;
	sf::Vector2f m_direction;
	float timeAlive;
	float timeToLive;
	float m_speed;
	float opacity;
	bool m_alive;
	int type;
};

