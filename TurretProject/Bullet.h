#pragma once
#include "SFML\Graphics.hpp"

class Bullet
{
	public:
		Bullet();
		~Bullet();

		void Update(float time);
		sf::Vector2f GetPosition();
		bool GetAlive() { return alive; }
		void Draw(sf::RenderWindow &window);
		void Shoot();


	protected:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Vector2f m_pos;
		sf::Vector2f m_direction;

		sf::FloatRect m_bounds;

		int m_width;
		int m_height;
		float m_speed;
		float m_rotation;
		bool alive;

		float toRadians(float degrees);
		void Rotation(int dir, float t);
		void Move(float time);
};