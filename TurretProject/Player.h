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
		void SetAlive(bool x);
		bool GetShrink() { return shrink; }
		bool GetLocked() { return locked; }
		int GetHealth() { return health; }
		void SetHealth(int newHealth) {health = newHealth; }

	protected:
		bool m_alive;
		bool isInLockZone();
		void lockStuff();
		void unlockStuff();
		void slowLock(float t);

		const int TURRET = 0, SPACESHIP = 1, LOCKING = 2, NONE = 3, PURPLE = 4, RED = 5;

		sf::Texture m_texture;
		sf::Texture m_poweruptexture;
		sf::Texture m_powerup2texture;
		sf::Texture m_powerup3texture;
		sf::Sprite m_sprite;
		sf::Texture m_dockTexture;
		sf::Sprite m_dockSprite;

		sf::Texture m_healthTexture;
		sf::Sprite m_healthSprite;
		sf::Texture m_health2Texture;
		sf::Sprite m_health2Sprite;

		int powerUp;

		sf::Texture m_landingzoneTexture;
		sf::Sprite m_landingzoneSprite;

		sf::Texture m_lockedTexture; 
		sf::Texture m_unlockedTexture;
		sf::Texture m_lockingTexture;
		sf::Sprite m_lockSprite;

		sf::Vector2f m_pos;
		sf::Vector2f startPos;
		sf::Vector2f m_direction;
		sf::FloatRect m_bounds;

		sf::SoundBuffer buffer;
		sf::Sound sound;

		sf::SoundBuffer buffer2;
		sf::Sound sound2;

		sf::SoundBuffer fireBuffer;
		sf::Sound fireSound;

		sf::SoundBuffer lockBuffer;
		sf::Sound lockSound;

		sf::SoundBuffer lockinBuffer;
		sf::Sound lockinSound;

		sf::SoundBuffer deadBuffer;
		sf::Sound deadSound;

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
		bool fired2;
		bool fireSide;
		float firedTime;
		float firedTimeControl;
		
		float toRadians(float degrees);
		void Rotation(int dir, float t);
		void Move(float time);
		void WrapAroundScreen();

		sf::Font font;
		sf::Text text[MAX_NUMBER_OF_ITEMS];

		float turretRot;

		float vol;

		float health = 100;

};

