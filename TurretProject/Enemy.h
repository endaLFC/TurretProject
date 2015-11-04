#pragma once
class Enemy
{
public:
	//Functions
	Enemy();
	Enemy(sf::Vector2f pos, float speed);

	void Update(float time, sf::Vector2f playerPos);
	void Load();
	bool IsColliding(sf::Vector2f targetPosition, int targetRadius);
	void Draw(sf::RenderWindow& window);

protected:
	//Functions
	void Move(float time, sf::Vector2f playerPos);
	void Rotation(int dir);
	void WrapAroundScreen();
	sf::Vector2f SlowTurn(sf::Vector2f m_direction, sf::Vector2f dir);
	void GetDirection(sf::Vector2f playerPos);


	sf::Vector2f Normalise(sf::Vector2f vec);
	float DistanceFrom(sf::Vector2f enemy, sf::Vector2f player);
	//Variables
	int m_radius = 50;
	int m_width;
	int m_height;
	float m_speed;
	float m_rotation;
	float toRadians(float degrees);
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::FloatRect m_bounds;
	
};

