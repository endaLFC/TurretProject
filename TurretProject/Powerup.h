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
	void Initialise(sf::Vector2f asteroidPos, sf::Vector2f asteroidPos2, sf::Vector2f asteroidPos3, int type);
	void SetSpriteScale(float s) { m_sprite.setScale(s, s); }
	void Rotate(float time);
	void Update(float time);
	bool getAlive() { return m_alive; }
	void setAlive(bool x) { m_alive = x, o = 255; }
	void Restart(sf::Vector2f asteroidPos, sf::Vector2f asteroidPos2, sf::Vector2f asteroidPos3);

protected:
	//Functions
	float x, y;
	void Fade(float time);
	bool OverlappingAsteroid(sf::Vector2f asteroidPos, sf::Vector2f asteroidPos2, sf::Vector2f asteroidPos3, sf::Vector2f powerUpPos);
	//Variables
	bool m_alive;
	int m_radius;
	float m_rotation;
	int rotateSpeed;
	int m_type;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::SoundBuffer buffer;
	sf::Sound sound;
	int o;
};

