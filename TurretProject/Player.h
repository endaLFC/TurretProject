#pragma once
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Bullet.h"
#include "BulletManager.h"

#define MAX_NUMBER_OF_ITEMS 4

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

	protected:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Vector2f m_pos;
		sf::Vector2f m_direction;
		sf::FloatRect m_bounds;
		sf::SoundBuffer buffer;
		sf::Sound sound;

		int m_radius;
		float m_speed;
		float m_rotation;

		bool fired;
		bool fireSide;
		float firedTime;
		float firedTimeControl;
		
		float toRadians(float degrees);
		void Rotation(int dir, float t);
		void Move(float time);

		sf::Font font;
		sf::Text text[MAX_NUMBER_OF_ITEMS];
};

