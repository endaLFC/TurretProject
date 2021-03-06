#pragma once
#include "SFML\Graphics.hpp"

class Bullet
{
	public:
		Bullet(float rotation, sf::Vector2f position);
		~Bullet();

		bool Update(float time);
		sf::Vector2f GetPosition();
		bool GetAlive() { return alive; }
		void Draw(sf::RenderWindow &window);
		void Shoot();
		void Initialise(sf::Texture * text);
		int GetRadius() { return m_radius; }
		bool IsColliding(sf::Vector2f targetPosition, int targetRadius, bool targetAlive);

	protected:
		sf::Texture* m_texture;
		sf::Sprite m_sprite;
		sf::Vector2f m_pos;
		sf::Vector2f m_direction;

		sf::Vector2f widthHeight = sf::Vector2f(10,15);

		int m_radius = 10;

		float m_speed;
		float m_rotation;
		bool alive;

		float toRadians(float degrees);
		void Rotation(int dir);
		void Move(float time);
		void WithinBounds();
};