#pragma once
class Powerup
{
public:
	Powerup();

	bool IsColliding(sf::Vector2f targetPosition, int targetRadius);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return m_position; }
	int GetRadius() { return m_radius; }
	int GetType() { return m_type; }
	void Initialise(sf::Vector2f pos, int type);
	void SetSpriteScale(float s) { m_sprite.setScale(s, s); };
	void Rotate(float time);

protected:
	//Functions
	void WrapAroundScreen();
	//Variables
	bool m_alive;
	int m_radius;
	float m_rotation;
	int rotateSpeed;
	int m_type;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};

