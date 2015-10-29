#pragma once
#include "SFML\Graphics.hpp"

class Player
{
	public:
		Player();
		~Player();

		void Update(float time);
		sf::Vector2f GetPosition();
		void Draw(sf::RenderWindow &window);
		void MoveLeft();
		void MoveRight();

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
		
		float toRadians(float degrees);
		void Rotation(int dir);
		void Move(float time);
};

