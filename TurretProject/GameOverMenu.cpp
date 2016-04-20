#include "stdafx.h"
#include "GameOverMenu.h"
#include "Score.h"

GameOverMenu::GameOverMenu(float width, float height)
{
	//if (!font.loadFromFile("C:\\Windows\\Fonts\\Arkhip_font.ttf"))
	if (!font.loadFromFile("TELE2.TTF"))
	{
		//handle error
	}
	frameTimer = 0;
	texture.loadFromFile("EndGame.jpg");
	texture2.loadFromFile("EndGame2.jpg");
	borderTexture.loadFromFile("box.png");
	borderSprite.setTexture(borderTexture);

	borderTexture2.loadFromFile("box2.png");
	borderSprite2.setTexture(borderTexture2);

	tableTexture.loadFromFile("block.png");
	tableSprite.setTexture(tableTexture);

	//background.setTexture(texture);
	animationRect = { 0, 0, 1100, 800 };

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		text[i].setCharacterSize(50);
	}

	text[0].setFont(font);
	text[0].setColor(sf::Color::Color(80, 160, 180)); //dark red
	text[0].setString("Retry");
	text[0].setScale(0.6, 0.6);
	text[0].setPosition(sf::Vector2f(width / 15 * 2.9, height / (MAX_NUMBER_OF_ITEMS) * 3.65));

	text[1].setFont(font);
	text[1].setColor(sf::Color::Color(120, 120, 120));	//grey
	text[1].setString("Main Menu");
	text[1].setScale(0.5, 0.5);
	text[1].setPosition(sf::Vector2f(width / 15 * 6.15, height / (MAX_NUMBER_OF_ITEMS) * 3.67));

	text[2].setFont(font);
	text[2].setColor(sf::Color::Color(120, 120, 120));
	text[2].setString("Exit");
	text[2].setScale(0.6, 0.6);
	text[2].setPosition(sf::Vector2f(width / 15 * 10.2, height / (MAX_NUMBER_OF_ITEMS) * 3.65));

	text[3].setFont(font);
	text[3].setColor(sf::Color::Color(250, 150, 30));
	text[3].setString("");
	text[3].setPosition(sf::Vector2f(width / 15 * 3.87, height / (MAX_NUMBER_OF_ITEMS) * 3));

	text[4].setFont(font);
	text[4].setString("");
	text[4].setScale(1, 1);

	borderSprite2.setPosition(1100 / 15 * 3.48, 800 / (MAX_NUMBER_OF_ITEMS)* 2.95);
	borderSprite2.setScale(3, 1);

	tableSprite.setPosition(sf::Vector2f(width / 15 * 5.2, height / (MAX_NUMBER_OF_ITEMS)));

	selectedItemIndex = 0;
}


GameOverMenu::~GameOverMenu()
{
}

void GameOverMenu::Draw(sf::RenderWindow &window)
{
	window.draw(background);
	//border1
	borderSprite.setPosition(1100 / 15 * 2.6, 800 / (MAX_NUMBER_OF_ITEMS) * 3.61);
	borderSprite.setScale(1, 1);
	window.draw(borderSprite);
	//border2
	borderSprite.setPosition(1100 / 15 * 5.9, 800 / (MAX_NUMBER_OF_ITEMS) * 3.61);
	borderSprite.setScale(1.2, 1);
	window.draw(borderSprite);
	//border3
	borderSprite.setPosition(1100 / 15 * 9.7, 800 / (MAX_NUMBER_OF_ITEMS) * 3.61);
	borderSprite.setScale(0.9, 1);
	window.draw(borderSprite);
	//score border
	window.draw(borderSprite2);
	window.draw(tableSprite);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS + 1; i++)
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
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS - 1)
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

	if (frameTimer >= 0.15)		//this timer flicks through the animation
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

void GameOverMenu::GameWon(bool won)
{
	if (won == true)
	{
		text[4].setPosition(sf::Vector2f(1100 / 15 * 5.65, 800 / (MAX_NUMBER_OF_ITEMS)*1.18));
		background.setTexture(texture);
		text[4].setColor(sf::Color::Color(50, 250, 50));
		text[4].setString("You Won!");
	}
	else
	{
		text[4].setPosition(sf::Vector2f(1100 / 15 * 5.5, 800 / (MAX_NUMBER_OF_ITEMS)*1.18));
		background.setTexture(texture2);
		text[4].setColor(sf::Color::Color(250, 50, 50));
		text[4].setString("You Lost!");
	}
}

void GameOverMenu::SetScore(int score)
{
	if (score == 1)
	{
		tableSprite.setColor(sf::Color::Color(255, 50, 50));
		text[3].setString("You don't deserve a score");
		text[3].setScale(0.43,0.6);
	}
	else
	{
		tableSprite.setColor(sf::Color::Color(50, 255, 50));
		text[3].setString("Your score was: " + std::to_string(score));
		text[3].setScale(0.6, 0.6);
	}
}