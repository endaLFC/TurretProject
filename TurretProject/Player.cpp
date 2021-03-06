#include "stdafx.h"
#include "Player.h"
#include "Score.h"
#include "Energy.h"
#include "ParticleSystem.h"

Player::Player()
{
	
}

void Player::Initialise()
{
	m_alive = true;

	if (!font.loadFromFile("TELE2.TTF")) //  digital-7.regular
	{
		//handle error
	}

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		text[i].setCharacterSize(15);
	}

	text[0].setFont(font);
	text[0].setColor(sf::Color::White);
	text[0].setString("Score: ");
	text[0].setPosition(sf::Vector2f(25, 17));

	text[1].setFont(font);
	text[1].setColor(sf::Color::White);
	text[1].setString("X");
	text[1].setPosition(sf::Vector2f(225, 17));

	text[2].setFont(font);
	text[2].setColor(sf::Color::White);
	text[2].setString("ap: ");
	text[2].setPosition(sf::Vector2f(290, 17));

	text[3].setFont(font);
	text[3].setColor(sf::Color::White);
	text[3].setPosition(sf::Vector2f(115, 17));


	//if (!m_texture.loadFromFile("flakcannonx.png"))
	if (!m_texture.loadFromFile("spacecraft3.png"))
	{
		// error...
	}
	if (!m_superTexture.loadFromFile("superCraft.png"))
	{
		// error...
	}
	if (!m_superTexturePU1.loadFromFile("superCraftPowerUp1.png"))
	{
		// error...
	}
	if (!m_superTexturePU2.loadFromFile("superCraftPowerUp2.png"))
	{
		// error...
	}
	if (!m_superTexturePU3.loadFromFile("superCraftPowerUp3.png"))
	{
		// error...
	}
	if (!m_superDockTexture.loadFromFile("superCraft2.png"))
	{
		// error...
	}
	if (!m_poweruptexture.loadFromFile("spacecraftpowerup1.png"))
	{
		// error...
	}
	if (!m_powerup2texture.loadFromFile("spacecraftpowerup2.png"))
	{
		// error...
	}
	if (!m_powerup3texture.loadFromFile("spacecraftpowerup3.png"))
	{
		// error...
	}
	if (!m_dockTexture.loadFromFile("spacecraft4.png"))
	{
		// error...
	}
	if (!m_lockedTexture.loadFromFile("lock.png"))
	{
		// error...
	}
	if (!m_unlockedTexture.loadFromFile("unlock.png"))
	{
		// error...
	}
	if (!m_lockingTexture.loadFromFile("locking.png"))
	{
		// error...
	}
	if (!m_landingzoneTexture.loadFromFile("landingzone.png"))
	{
		// error...
	}
	if (!m_healthTexture.loadFromFile("Healthbar.png"))
	{
		// error...
	}
	if (!m_health2Texture.loadFromFile("Healthbar2.png"))
	{
		// error...
	}

	m_healthSprite.setTexture(m_healthTexture);
	m_health2Sprite.setTexture(m_health2Texture);

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(110, 85);

	m_dockSprite.setTexture(m_dockTexture);
	m_dockSprite.setOrigin(110, 85);

	m_lockSprite.setTexture(m_lockedTexture);
	m_landingzoneSprite.setTexture(m_landingzoneTexture);

	lockSpeed = 50;

	m_radius = 70;
	m_speed = 100;
	maxSpeed = 500;
	forward_speed = 0;
	m_rotation = 270;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	startPos = sf::Vector2f(1350, 1700);
	m_pos = startPos;
	m_sprite.setPosition(m_pos);
	m_dockSprite.setPosition(startPos);
	m_dockSprite.setRotation(m_rotation);
	m_lockSprite.setPosition(239, 647);
	m_healthSprite.setPosition(187, 47);
	m_health2Sprite.setPosition(189, 49);
	m_landingzoneSprite.setPosition(1130,1500);
	fired = false;
	fired2 = false;
	firedTime = 0;
	firedTimeControl = 0.2;
	fireSide = false;
	locked = true;
	turretMode = TURRET;

	buffer.loadFromFile("blaster-firing.wav");
	sound.setBuffer(buffer);

	buffer2.loadFromFile("takeoff.wav");
	sound2.setBuffer(buffer2);

	fireBuffer.loadFromFile("thrusters.wav");
	fireSound.setBuffer(fireBuffer);

	lockBuffer.loadFromFile("lockingin.wav");
	lockSound.setBuffer(lockBuffer);

	lockinBuffer.loadFromFile("lockin.wav");
	lockinSound.setBuffer(lockinBuffer);

	deadBuffer.loadFromFile("playerdead.wav");
	deadSound.setBuffer(deadBuffer);

	turretRot = 0;

	vol = 50;

	deadSound.setVolume(100);
	sound.setVolume(40);
	fireSound.setVolume(vol);
	m_health = 100;
	m_turretHealth = 100;
	shrink = false;
	speedBoost = false;
}

Player::~Player()
{
	
}

void Player::Update(float time)
{
	if (turretMode == SPACESHIP)
	{
		m_health2Sprite.setScale(m_health / 100, 1);
		m_health2Sprite.setColor(sf::Color::Color(255, m_health * 2.5, m_health * 2.5));
	}
	else if ((turretMode == TURRET))
	{
		m_health2Sprite.setScale(m_turretHealth / 100, 1);
		m_health2Sprite.setColor(sf::Color::Color(255,0,255));
		//m_health2Sprite.setColor(sf::Color::Color(255, m_turretHealth * 2.5, 255));
	}
	if (m_alive == true)
	{
		if (turretMode == TURRET)
		{
			turretRot = m_rotation;
		}
		else if (turretMode == LOCKING)		//if the ship is locking into the dock, make the dock do the appropriate rotation
		{
			if (turretRot < 272 && turretRot > 268)
			{
				turretRot = 270;
			}
			else if (turretRot > 270)
			{
				turretRot -= lockSpeed * time;
			}
			else if (turretRot < 270)
			{
				turretRot += lockSpeed * time;
			}
		}
		SkinSelector(skinType);

		if (locked == true && turretMode == LOCKING)
		{
			slowLock(time);
		}
		Move(time);
		WrapAroundScreen();
	}

	//changing the colour of the score text depending on the score
	text[3].setString(to_string(Score::GetInstance()->getScore()));
	if (Score::GetInstance()->getScore() >= 500)
	{
		text[3].setColor(sf::Color::Red);
	}
	else if (Score::GetInstance()->getScore() >= 400)
	{
		text[3].setColor(sf::Color::Green);
	}
	else if (Score::GetInstance()->getScore() >= 300)
	{
		text[3].setColor(sf::Color::Yellow);
	}
	else if (Score::GetInstance()->getScore() >= 200)
	{
		text[3].setColor(sf::Color::Magenta);
	}
	else if (Score::GetInstance()->getScore() >= 100)
	{
		text[3].setColor(sf::Color::Cyan);
	}
}

void Player::Move(float time)
{
	m_pos += m_direction * time * forward_speed;
	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(m_rotation);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && turretMode != LOCKING)
	{
		Rotation(1, time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && turretMode != LOCKING)
	{
		Rotation(-1, time);
	}
	if (locked == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			vol = 80;

			if (fireSound.getStatus() != fireSound.Playing)		//making sure the moving sound doesn't loop over itself
			{
				fireSound.play();
			}
			if (forward_speed <= maxSpeed)
			{
				forward_speed += 10;
			}
				
			ParticleSystem::GetInstance()->addParticle(m_pos, 1);

			m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (forward_speed >= 50)		//slow down the ship when down is pressed
			{
				forward_speed -= 10;
			}
		}
		if (forward_speed >= 103)			//dampening on the ships movement
		{
			forward_speed -= 3;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			//making the movement sound fade out nicely when up is not being pressed
			vol -= time * 50;
			if (vol <= 1)
			{
				vol = 0;
				fireSound.stop();
			}
		}
		fireSound.setVolume(vol);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && Energy::GetInstance()->GetEnergy() >= 0.25 && turretMode != LOCKING)
	{
		if (turretMode == TURRET && fired == false)
		{
			sound.play();
			Energy::GetInstance()->Shot1();		//taking energy from the energy bar

			if (fireSide == false)				//used to flick between shooting from the left and right turret cannon
			{
				float xBefore = 80;
				float yBefore = -45;
				float xAfter = xBefore * cos(toRadians(m_rotation)) - yBefore * sin(toRadians(m_rotation));
				float yAfter = xBefore * sin(toRadians(m_rotation)) + yBefore * cos(toRadians(m_rotation));
				BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x + xAfter, m_pos.y + (yAfter)));	//(m_pos.x - 17 + (m_direction.x * 120), m_pos.y + (m_direction.y * 120))	// cos(toRadians(m_rotation)
			}
			else
			{
				float xBefore = 80;
				float yBefore = 45;
				float xAfter = xBefore * cos(toRadians(m_rotation)) - yBefore * sin(toRadians(m_rotation));
				float yAfter = xBefore * sin(toRadians(m_rotation)) + yBefore * cos(toRadians(m_rotation));
				BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x + xAfter, m_pos.y + (yAfter)));	//(m_pos.x + 10 + (m_direction.x * 120), m_pos.y + (m_direction.y * 120))	// sin(toRadians(m_rotation)
			}
			fired = true;
		}
		else if (turretMode == SPACESHIP && fired2 == false)		//shooting while in spaceship mode
		{
			sound.play();
			Energy::GetInstance()->Shot1();

			float xBefore = 80;
			float yBefore = 0;
			float xAfter = xBefore * cos(toRadians(m_rotation)) - yBefore * sin(toRadians(m_rotation));
			float yAfter = xBefore * sin(toRadians(m_rotation)) + yBefore * cos(toRadians(m_rotation));

			BulletManager::GetInstance()->PlayerFire(m_rotation, sf::Vector2f(m_pos.x + xAfter, m_pos.y + (yAfter)));

			fired2 = true;
		}
	}

	if (fired == true)		//switching between different sides to fire on while in turret mode and causing a delay between shots
	{
		firedTime+=time;
		if (firedTime >= firedTimeControl)
		{
			firedTime = 0;
			fired = false;

			if (fireSide == false)
				fireSide = true;
			else
				fireSide = false;
		}
	}
	if (fired2 == true)		//causes a delay between shots while in spaceship mode
	{
		firedTime += time;
		if (firedTime >= firedTimeControl*2)
		{
			firedTime = 0;
			fired2 = false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && locked == true && turretMode == TURRET)
	{
		sound2.play();
		unlockStuff();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && locked == false && isInLockZone() == true)
	{
		lockSound.play();
		lockStuff();
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	if (locked == false)
	{
		window.draw(m_landingzoneSprite);
	}
	m_dockSprite.setRotation(turretRot);

	if (m_alive == true)
	{
		SkinSelector(skinType);
		window.draw(m_sprite);
	}
	window.draw(m_dockSprite);
}

void Player::DrawScore(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(text[i]);
	}
	//drawing the heakthbar and the frame nehind th healthbar
	window.draw(m_healthSprite);
	window.draw(m_health2Sprite);
}

void Player::DrawLock(sf::RenderWindow& window)
{
	window.draw(m_lockSprite);
}

float Player::toRadians(float degrees)
{
	return (degrees * 3.14) / 180;
}

void Player::Rotation(int dir, float t)
{
	if (m_rotation >= 360)
	{
		m_rotation = m_rotation - 360;
	}
	else if (m_rotation < 0)
	{
		m_rotation = 360 - m_rotation;
	}
	m_rotation += 1.5 * m_speed * t * dir;
}

void Player::WrapAroundScreen()
{
	if (m_pos.x > 2400)
		m_pos.x = 0;
	else if (m_pos.x < 0)
		m_pos.x = 2400;

	if (m_pos.y > 1800)
		m_pos.y = 0;
	else if (m_pos.y < 0)
		m_pos.y = 1800;
}

bool Player::isInLockZone()		//checking if the player is in the landing zone and can lock into turret
{
	if (m_pos.x > 1130 && m_pos.x < 1550 && m_pos.y > 1500 && m_pos.y < 1800)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::lockStuff()		//things to do when locked
{
	if (fireSound.Playing)
	{
		fireSound.stop();
	}
	m_lockSprite.setTexture(m_lockingTexture);
	forward_speed = 0;
	turretMode = LOCKING;
	locked = true;
}

void Player::unlockStuff()		//things to do when unlocked
{
	m_lockSprite.setTexture(m_unlockedTexture);
	forward_speed = 250;
	turretMode = SPACESHIP;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	locked = false;
}

void Player::slowLock(float t)
{
	//making the player rotate and move position slowly over time to fit nicely into the turret dock
	if (m_rotation >= 360)
	{
		m_rotation = m_rotation - 360;
	}
	else if (m_rotation < 0)
	{
		m_rotation = 360 - m_rotation;
	}

	if (m_pos.x < startPos.x + 3 && m_pos.x > startPos.x - 3)
	{
		m_pos.x = startPos.x;
	}
	else if (m_pos.x < startPos.x)
	{
		m_pos.x += lockSpeed * t;
	}
	else if (m_pos.x > startPos.x)
	{
		m_pos.x -= lockSpeed * t;
	}

	if (m_pos.y < startPos.y + 3 && m_pos.y > startPos.y - 3)
	{
		m_pos.y = startPos.y;
	}
	else if (m_pos.y < startPos.y)
	{
		m_pos.y += lockSpeed * t;
	}
	else if (m_pos.y > startPos.y)
	{
		m_pos.y -= lockSpeed * t;
	}

	if (m_rotation < 272 && m_rotation > 268)
	{
		m_rotation = 270;
	}
	else if (m_rotation > 270 || m_rotation <= 90)
	{
		m_rotation -= lockSpeed * t;
	}
	else if (m_rotation < 270)
	{
		m_rotation += lockSpeed * t;
	}
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));


	if (m_pos == startPos && m_rotation == 270)
	{
		lockinSound.play();
		lockSound.stop();
		turretMode = TURRET;
		m_lockSprite.setTexture(m_lockedTexture);
	}
}

void Player::SetAlive(bool x)
{ 
	if (m_alive == true && x == false)
	{
		if (fireSound.Playing)
		{
			fireSound.stop();
		}
		deadSound.play();
		for (int i = 0; i < 200; i++)
		{
			ParticleSystem::GetInstance()->addParticle(m_pos, 1);
			ParticleSystem::GetInstance()->addParticle(m_pos, 0);
		}
		m_alive = x;
	}
}

void Player::AlterHealth(int change)
{
	if (turretMode == SPACESHIP)
	{
		m_health += change;
		if (m_health >= 100)
		{
			m_health = 100;
		}
		else if (m_health <= 0)
		{
			m_health = 0;
			SetAlive(false);
		}
	}
	else if (turretMode == TURRET)
	{
		m_turretHealth += change/2;
		if (m_turretHealth >= 100)
		{
			m_turretHealth = 100;
		}
		else if (m_turretHealth <= 0)
		{
			m_turretHealth = 0;
			SetAlive(false);
		}
	}
	
}

void Player::SkinSelector(int skinType)
{
	if (skinType == 3)		//if super skin
	{
		m_sprite.setColor(sf::Color::Color(255, 255, 255));
		m_dockSprite.setColor(sf::Color::Color(255, 255, 255));
		//checking for powerups
		if (shrink == true && speedBoost == true)
		{
			m_sprite.setScale(0.75, 0.75);
			m_radius = 20;
			m_sprite.setTexture(m_superTexturePU3);
		}
		else if (shrink == true && speedBoost == false)
		{
			m_sprite.setScale(0.75, 0.75);
			m_radius = 20;
			m_sprite.setTexture(m_superTexturePU2);
		}
		else if (shrink == false && speedBoost == true)
		{
			m_sprite.setTexture(m_superTexturePU1);
		}
		else
		{
			m_sprite.setScale(1, 1);
			m_sprite.setTexture(m_superTexture);
		}

		m_dockSprite.setTexture(m_superDockTexture);
	}
	else		//if not super skin
	{
		//check powerups
		if (shrink == true && speedBoost == true)
		{
			m_sprite.setScale(0.75, 0.75);
			m_radius = 20;
			m_sprite.setTexture(m_powerup3texture);
		}
		else if (shrink == true && speedBoost == false)
		{
			m_sprite.setScale(0.75, 0.75);
			m_radius = 20;
			m_sprite.setTexture(m_powerup2texture);
		}
		else if (speedBoost == true && shrink == false)
		{
			m_sprite.setTexture(m_poweruptexture);
		}
		else
		{
			m_sprite.setScale(1, 1);
			m_sprite.setTexture(m_texture);
		}
		m_dockSprite.setTexture(m_dockTexture);

		if (skinType == 0)
		{
			m_sprite.setColor(sf::Color::Color(255, 255, 255));
			m_dockSprite.setColor(sf::Color::Color(255, 255, 255));
		}
		else if (skinType == 1)
		{
			m_sprite.setColor(sf::Color::Color(255, 100, 100));
			m_dockSprite.setColor(sf::Color::Color(255, 100, 100));
		}
		else if (skinType == 2)
		{
			m_sprite.setColor(sf::Color::Color(100, 100, 255));
			m_dockSprite.setColor(sf::Color::Color(100, 100, 255));
		}
	}
}

void Player::Restart()
{
	m_alive = true;
	m_radius = 70;
	m_speed = 100;
	maxSpeed = 500;
	forward_speed = 0;
	m_rotation = 270;
	m_direction = sf::Vector2f(cos(toRadians(m_rotation)), sin(toRadians(m_rotation)));
	m_pos = startPos;
	shrink = false;
	speedBoost = false;
	fired = false;
	fired2 = false;
	firedTime = 0;
	firedTimeControl = 0.2;
	fireSide = false;
	locked = true;
	turretMode = TURRET;
	turretRot = 0;
	m_health = 100;
	m_turretHealth = 100;
	SkinSelector(skinType);
	Score::GetInstance()->setScore(0);
	text[3].setColor(sf::Color::White);
}