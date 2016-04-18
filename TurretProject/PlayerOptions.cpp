#include "stdafx.h"
#include "PlayerOptions.h"


PlayerOptions::PlayerOptions(float width, float height, sf::Music &backgroundMusic)
{
	healthMax = true;
	healthMin = false;
	skinMin = true;
	skinMax = false;
	displaySkinArrows = true;
	displayHealthArrows = false;
	skinCount = 0;

	if (!font.loadFromFile("TELE2.TTF"))
	{
		//handle error
	}
	texture.loadFromFile("SoundOptionsBkg.jpg");

	if (!m_healthTexture.loadFromFile("volumebar.png"))
	{
		//error
	}
	if (!m_health2Texture.loadFromFile("volumebar2.png"))
	{
		//error
	}

	if (!leftArrowTex.loadFromFile("arrowLeft.png"))
	{
	}
	if (!rightArrowTex.loadFromFile("arrowRight.png"))
	{
	}

	leftArrowSpr.setTexture(leftArrowTex);

	rightArrowSpr.setTexture(rightArrowTex);

	m_healthSprite.setOrigin(0, 0);
	m_healthSprite.setPosition(width / 15 * 6.7, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.52);
	m_healthSprite.setTexture(m_healthTexture);

	healthWidth = 100;
	m_health2Sprite.setOrigin(0, 0);
	m_health2Sprite.setColor(sf::Color::Color(100,255,100));
	m_health2Sprite.setPosition(width / 15 * 6.75, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.53);
	m_health2Sprite.setTexture(m_health2Texture);

	background.setTexture(texture);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		text[i].setCharacterSize(50);
	}
	text[0].setFont(font);
	text[0].setColor(sf::Color::Color(140, 140, 40)); //yellow
	text[0].setString("Skin");
	text[0].setScale(0.6, 0.6);
	text[0].setPosition(sf::Vector2f(width / 15 * 3.6, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	text[1].setFont(font);
	text[1].setColor(sf::Color::Color(0, 20, 60));	//navy
	text[1].setString("Health");
	text[1].setScale(0.55, 0.55);
	text[1].setPosition(sf::Vector2f(width / 15 * 3.6, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.5));

	text[2].setFont(font);
	text[2].setColor(sf::Color::Color(0, 20, 60));
	text[2].setString("Back");
	text[2].setScale(0.6, 0.6);
	text[2].setPosition(sf::Vector2f(width / 15 * 3.6, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	skinName = "Classic";

	text[3].setFont(font);
	text[3].setColor(sf::Color::Color(180, 35, 35));	//red

	text[3].setScale(0.6, 0.6);
	text[3].setPosition(sf::Vector2f(width / 15 * 7, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	selectedItemIndex = 0;
}


PlayerOptions::~PlayerOptions()
{
}

void PlayerOptions::Draw(sf::RenderWindow &window)
{
	window.draw(background);
	window.draw(m_healthSprite);
	m_health2Sprite.setScale(healthWidth / 100, 1);
	window.draw(m_health2Sprite);
	if (displaySkinArrows == true)
	{
		leftArrowSpr.setPosition(sf::Vector2f(1100 / 15 * 6.26, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 2.05));
		rightArrowSpr.setPosition(sf::Vector2f(1100 / 15 * 11.2, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 2.05));
		if (skinMin == false)
		{
			window.draw(leftArrowSpr);
		}
		if (skinMax == false)
		{
			window.draw(rightArrowSpr);
		}
	}
	else if (displayHealthArrows == true)
	{
		leftArrowSpr.setPosition(sf::Vector2f(1100 / 15 * 6.26, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 2.55));
		rightArrowSpr.setPosition(sf::Vector2f(1100 / 15 * 11.2, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 2.55));
		if (healthMin == false)
		{
			window.draw(leftArrowSpr);
		}
		if (healthMax == false)
		{
			window.draw(rightArrowSpr);
		}
	}
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(text[i]);
	}
	text[3].setString(skinName);
}

void PlayerOptions::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		text[selectedItemIndex].setColor(sf::Color::Color(0, 20, 60));
		selectedItemIndex--;
		text[selectedItemIndex].setColor(sf::Color::Color(140, 140, 40));
	}
}

void PlayerOptions::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS - 1)
	{
		text[selectedItemIndex].setColor(sf::Color::Color(0, 20, 60));
		selectedItemIndex++;
		text[selectedItemIndex].setColor(sf::Color::Color(140, 140, 40));
	}
}


void PlayerOptions::Update(float time, sf::RenderWindow &window)
{
	/* initialize random seed: */
}

void PlayerOptions::AlterHealth(int change, Player &player)
{
	//changing the healthbar
	if (change == 1 && healthWidth == 1)
	{
		healthWidth += 9;
		healthMin = false;
	}
	else if (change == 1 && healthWidth <= 80)
	{
		healthWidth += 10;
	}
	else if (change == 1 && healthWidth == 90)
	{
		healthWidth += 10;
		healthMax = true;
	}
	if (change == -1 && healthWidth >= 20)
	{
		healthWidth -= 10;
		healthMax = false;
	}
	else if (change == -1 && healthWidth == 10)
	{
		healthWidth -= 9;
		healthMin = true;
	}

	player.SetHealth(healthWidth);
}

void PlayerOptions::ChangeSkin(int change, Player &player)
{
	//changing the player's skin
	if (change == 1 && skinCount < 3)
	{
		skinCount++;
	}
	else if (change == -1 && skinCount > 0)
	{
		skinCount--;
	}

	//changing song
	if (skinCount == 0)
	{
		skinName = "Classic";
		skinMin = true;
		player.SetSkinType(0);
	}
	else if (skinCount == 1)
	{
		skinName = "Red";
		skinMin = false;
		player.SetSkinType(1);
	}
	else if (skinCount == 2)
	{
		skinName = "Blue";
		skinMax = false;
		player.SetSkinType(2);
	}
	else if (skinCount == 3)
	{
		skinName = "Super";
		skinMax = true;
		player.SetSkinType(3);
	}
}
