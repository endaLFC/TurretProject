#include "stdafx.h"
#include "OptionsMenu.h"


OptionsMenu::OptionsMenu(float width, float height)
{
	//if (!font.loadFromFile("C:\\Windows\\Fonts\\Arkhip_font.ttf"))
	if (!font.loadFromFile("TELE2.TTF"))
	{
		//handle error
	}
	frameTimer = 0;
	initialFrameTimer = 0;
	//texture.loadFromFile("Asteroids4.jpg");
	texture.loadFromFile("OptionsBkg.jpg");
	background.setTexture(texture);
	animationRect = { 0, 0, 1100, 800 };

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		text[i].setCharacterSize(50);
	}

	text[0].setFont(font);
	text[0].setColor(sf::Color::Color(180, 35, 35)); //dark red
	text[0].setString("Video");
	text[0].setScale(0.6, 0.6);
	//text[0].setPosition(sf::Vector2f(width/15 * 2, height/(MAX_NUMBER_OF_ITEMS + 1 ) * 3));
	text[0].setPosition(sf::Vector2f(width / 15 * 11.2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.6));

	text[1].setFont(font);
	text[1].setColor(sf::Color::Color(120, 120, 120));	//grey
	text[1].setString("Volume");
	text[1].setScale(0.5, 0.5);
	//text[1].setPosition(sf::Vector2f(width /15 * 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	text[1].setPosition(sf::Vector2f(width / 15 * 11, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	text[2].setFont(font);
	text[2].setColor(sf::Color::Color(120, 120, 120));
	text[2].setString("Back");
	text[2].setScale(0.6, 0.6);
	text[2].setPosition(sf::Vector2f(width / 15 * 11.4, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.35));

	selectedItemIndex = 0;


}


OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::Draw(sf::RenderWindow &window)
{
	window.draw(background);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(text[i]);
	}
}

void OptionsMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		//beepSound.play();
		Sleep(150);
		text[selectedItemIndex].setColor(sf::Color::Color(120, 120, 120));
		selectedItemIndex--;
		text[selectedItemIndex].setColor(sf::Color::Color(180, 35, 35));
	}
}

void OptionsMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		//beepSound.play();
		Sleep(150);
		text[selectedItemIndex].setColor(sf::Color::Color(120, 120, 120));
		selectedItemIndex++;
		text[selectedItemIndex].setColor(sf::Color::Color(180, 35, 35));
	}
}


void OptionsMenu::Update(float time)
{
	/* initialize random seed: */

	random = rand() % 10 + 1;
	frameTimer += time;
	initialFrameTimer += time;



		if (frameTimer >= 0.3)
		{
			if (animationRect.left < 3300)
			{
				animationRect.left += 1100;
			}
			else
			{
				animationRect.left = 0;
				initialFrameTimer = 0;
			}

			frameTimer = 0;
		}
	background.setTextureRect(animationRect);
}