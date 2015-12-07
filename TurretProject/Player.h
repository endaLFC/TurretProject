#pragma once
#include "SFML\Graphics.hpp"
#include "Bullet.h"
#include "BulletManager.h"

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
		void Initialise();
		sf::Vector2f GetPos() { return m_pos; }
		int GetRadius() { return m_radius; }
		//Bullet b1;

	protected:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Vector2f m_pos;
		sf::Vector2f m_direction;
		sf::FloatRect m_bounds;

		int m_radius;
		float m_speed;
		float m_rotation;

		bool fired;
		float firedTime;
		float firedTimeControl;
		
		float toRadians(float degrees);
		void Rotation(int dir, float t);
		void Move(float time);
};

