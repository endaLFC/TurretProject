#pragma once
class Obstacle
{
public:
	Obstacle();

	bool IsColliding(sf::Vector2f targetPosition, int targetRadius);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return m_position; }
	int GetRadius() { return m_radius; }
	void Initialise(sf::Vector2f pos);
	void SetSpriteScale(float s) { m_sprite.setScale(s, s); };
	void Rotate(float time);

protected:
	//Functions
	void WrapAroundScreen();
	void GetDirection(sf::Vector2f playerPos, float time);
	//Variables
	int m_radius = 80;
	float m_rotation;
	int rotateSpeed;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};

