#pragma once
class FlockEnemy
{
public:
	//Functions
	FlockEnemy();

	bool Update(float time);
	bool Colliding();
	bool IsColliding(sf::Vector2f targetPosition, int targetRadius);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return m_position; }
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	void SetRadius(float radius) { m_radius = radius; }
	float GetRadius() { return m_radius; }
	void SetRotation(float rot) { m_rotation = rot - 90; }
	void SetScale(float scale) { m_sprite.setScale(sf::Vector2f(scale, scale)); }
	bool GetAlive() { return m_alive; }
	void SetAlive(bool alive) { m_alive = alive; }
	void Initialise();

protected:
	//Functions
	void Move(float time, sf::Vector2f playerPos);
	void WrapAroundScreen();
	float DistanceFrom(sf::Vector2f player);
	//Variables
	int m_radius = 40;
	bool m_alive;
	float m_speed;
	float m_rotation;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::FloatRect m_bounds;

	sf::SoundBuffer buffer;
	sf::Sound explosionSound;

};

