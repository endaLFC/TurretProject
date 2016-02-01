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
		void Draw(sf::RenderWindow &window);
		void DrawScore(sf::RenderWindow &window);
		void DrawLock(sf::RenderWindow &window);
		void MoveLeft();
		void MoveRight();
		void Initialise();
		void SetSpriteScale(float s) { m_sprite.setScale(s,s); };
		sf::Vector2f GetPos() { return m_pos; }
		int GetRadius() { return m_radius; }
		int GetRot() { return m_rotation; }
		void SetSpeed(float tS, float mS) { m_speed = tS; maxSpeed = mS; speedBoost = true; }
		void SetShrink(bool x) { shrink = x; }
		bool GetShrink() { return shrink; }
		bool GetLocked() { return locked; }


	protected:
		bool isInLockZone();
		void lockStuff();
		void unlockStuff();
		void slowLock(float t);

		const int TURRET = 0, SPACESHIP = 1, LOCKING = 2;

		sf::Texture m_texture;
		sf::Sprite m_sprite;

		sf::Texture m_landingzoneTexture;
		sf::Sprite m_landingzoneSprite;

		sf::Texture m_lockedTexture; 
		sf::Texture m_unlockedTexture;
		sf::Texture m_lockingTexture;
		sf::Sprite m_lockSprite;

		sf::Vector2f m_pos;
		const sf::Vector2f startPos = sf::Vector2f(1350, 1800);
		sf::Vector2f m_direction;
		sf::FloatRect m_bounds;
		sf::SoundBuffer buffer;
		sf::Sound sound;


		float lockSpeed;
		int m_radius;
		float m_speed;
		float maxSpeed;
		float forward_speed;
		float m_rotation;

		bool locked;
		int turretMode;

		bool shrink = false;
		bool speedBoost = false;

		bool fired;
		bool fireSide;
		float firedTime;
		float firedTimeControl;
		
		float toRadians(float degrees);
		void Rotation(int dir, float t);
		void Move(float time);
		void WrapAroundScreen();

		sf::Font font;
		sf::Text text[MAX_NUMBER_OF_ITEMS];
};

