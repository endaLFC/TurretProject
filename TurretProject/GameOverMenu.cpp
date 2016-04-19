#include "stdafx.h"
#include "GameOverMenu.h"


GameOverMenu::GameOverMenu(float width, float height)
{
	//if (!font.loadFromFile("C:\\Windows\\Fonts\\Arkhip_font.ttf"))
	if (!font.loadFromFile("TELE2.TTF"))
	{
		//handle error
	}
	frameTimer = 0;
	texture.loadFromFile("EndGame.jpg");
	borderTexture.loadFromFile("box.png");
	borderSprite.setTexture(borderTexture);
	background.setTexture(texture);
	animationRect = { 0, 0, 1100, 800 };

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		text[i].setCharacterSize(50);
	}

	text[0].setFont(font);
	text[0].setColor(sf::Color::Color(80, 160, 180)); //dark red
	text[0].setString("Retry");
	text[0].setScale(0.6, 0.6);
	text[0].setPosition(sf::Vector2f(width / 15 * 2.9, height / (MAX_NUMBER_OF_ITEMS + 1) * 3.65));

	text[1].setFont(font);
	text[1].setColor(sf::Color::Color(120, 120, 120));	//grey
	text[1].setString("Main Menu");
	text[1].setScale(0.5, 0.5);
	text[1].setPosition(sf::Vector2f(width / 15 * 6.15, height / (MAX_NUMBER_OF_ITEMS + 1) * 3.67));

	text[2].setFont(font);
	text[2].setColor(sf::Color::Color(120, 120, 120));
	text[2].setString("Exit");
	text[2].setScale(0.6, 0.6);
	text[2].setPosition(sf::Vector2f(width / 15 * 10.2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3.65));

	selectedItemIndex = 0;
}


GameOverMenu::~GameOverMenu()
{
}

void GameOverMenu::Draw(sf::RenderWindow &window)
{
	window.draw(background);
	//border1
	borderSprite.setPosition(1100 / 15 * 2.6, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 3.61);
	borderSprite.setScale(1, 1);
	window.draw(borderSprite);
	//border2
	borderSprite.setPosition(1100 / 15 * 5.9, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 3.61);
	borderSprite.setScale(1.2, 1);
	window.draw(borderSprite);
	//border3
	borderSprite.setPosition(1100 / 15 * 9.7, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 3.61);
	borderSprite.setScale(0.9, 1);
	window.draw(borderSprite);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(text[i]);
	}
}

void GameOverMenu::MoveLeft()
{
	if (selectedItemIndex - 1 >= 0)
	{
		text[selectedItemIndex].setColor(sf::Color::Color(120, 120, 120));
		selectedItemIndex--;
		text[selectedItemIndex].setColor(sf::Color::Color(80, 160, 180));
	}
}

void GameOverMenu::MoveRight()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		text[selectedItemIndex].setColor(sf::Color::Color(120, 120, 120));
		selectedItemIndex++;
		text[selectedItemIndex].setColor(sf::Color::Color(80, 160, 180));
	}
}


void GameOverMenu::Update(float time)
{
	/* initialize random seed: */
	random = rand() % 10 + 1;
	frameTimer += time;

	if (frameTimer >= 0.3)		//this timer flicks through the animation
	{
		if (animationRect.left < 5500)
		{
			animationRect.left += 1100;
		}
		else
		{
			animationRect.left = 0;
		}

		frameTimer = 0;
	}

	background.setTextureRect(animationRect);
}