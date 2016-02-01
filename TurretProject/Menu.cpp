#include "stdafx.h"
#include "Menu.h"


Menu::Menu(float width, float height)
{
	//if (!font.loadFromFile("C:\\Windows\\Fonts\\Arkhip_font.ttf"))
	if (!font.loadFromFile("digital-7.regular.ttf"))
	{
		//handle error
	}
	frameTimer = 0;
	texture.loadFromFile("Asteroids4.jpg");
	background.setTexture(texture);
	animationRect = { 0, 0, 1100, 800 };

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		text[i].setCharacterSize(50);
	}

	text[0].setFont(font);
	text[0].setColor(sf::Color::Red);
	text[0].setString("Play");
	text[0].setPosition(sf::Vector2f(width/15 * 2, height/(MAX_NUMBER_OF_ITEMS + 1 ) * 3));

	text[1].setFont(font);
	text[1].setColor(sf::Color::White);
	text[1].setString("Options");
	text[1].setPosition(sf::Vector2f(width /15 * 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	text[2].setFont(font);
	text[2].setColor(sf::Color::White);
	text[2].setString("Exit");
	text[2].setPosition(sf::Vector2f(width /15 * 11.3, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::Draw(sf::RenderWindow &window)
{
	window.draw(background);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(text[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		Sleep(150);
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		text[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		Sleep(150);
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		text[selectedItemIndex].setColor(sf::Color::Red);
	}
}


void Menu::Update(float time)
{
	frameTimer += time;

	if (frameTimer >= 0.15)
	{
		if (animationRect.left < 5500)
			animationRect.left += 1100;
		else
			animationRect.left = 0;
		frameTimer = 0;
	}
	background.setTextureRect(animationRect);
}