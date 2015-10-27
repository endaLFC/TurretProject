#include "stdafx.h"
#include "Menu.h"


Menu::Menu(float width, float height)
{
	//if (!font.loadFromFile("C:\\Windows\\Fonts\\Arkhip_font.ttf"))
	if (!font.loadFromFile("Capture_it.ttf"))
	{
		//handle error
	}
	
	texture.loadFromFile("Skull.jpg");
	background.setTexture(texture);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		text[i].setCharacterSize(50);
	}

	text[0].setFont(font);
	text[0].setColor(sf::Color::Red);
	text[0].setString("Play");
	text[0].setPosition(sf::Vector2f(width/1.5, height/(MAX_NUMBER_OF_ITEMS + 1 ) * 0.75));

	text[1].setFont(font);
	text[1].setColor(sf::Color::White);
	text[1].setString("Options");
	text[1].setPosition(sf::Vector2f(width /1.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.5));

	text[2].setFont(font);
	text[2].setColor(sf::Color::White);
	text[2].setString("Exit");
	text[2].setPosition(sf::Vector2f(width /1.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.25));

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
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		text[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		text[selectedItemIndex].setColor(sf::Color::Red);
	}
}