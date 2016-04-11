#include "stdafx.h"
#include "SoundOptions.h"


SoundOptions::SoundOptions(float width, float height, sf::Music &backgroundMusic)
{
	//if (!font.loadFromFile("C:\\Windows\\Fonts\\Arkhip_font.ttf"))
	if (!font.loadFromFile("TELE2.TTF"))
	{
		//handle error
	}
	frameTimer = 0;
	//texture.loadFromFile("Asteroids4.jpg");
	texture.loadFromFile("SoundOptionsBkg.jpg");

	
	if (!m_volTexture.loadFromFile("volumebar.png"))
	{
		//error
	}
	if (!m_vol2Texture.loadFromFile("volumebar2.png"))
	{
		//error
	}
	
	m_volSprite.setOrigin(0, 0);
	m_volSprite.setPosition(width / 15 * 6.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.52);
	m_volSprite.setTexture(m_volTexture);

	volWidth = 50;
	m_vol2Sprite.setOrigin(0, 0);
	m_vol2Sprite.setPosition(width / 15 * 6.56, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.53);
	m_vol2Sprite.setTexture(m_vol2Texture);

	background.setTexture(texture);
	animationRect = { 0, 0, 1100, 800 };

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		text[i].setCharacterSize(50);
	}
	text[0].setFont(font);
	text[0].setColor(sf::Color::Color(140, 140, 40)); //yellow
	text[0].setString("Volume");
	text[0].setScale(0.6, 0.6);
	text[0].setPosition(sf::Vector2f(width / 15 * 3.6, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.5));

	text[1].setFont(font);
	text[1].setColor(sf::Color::Color(0, 20, 60));	//navy
	text[1].setString("Music");
	text[1].setScale(0.55, 0.55);
	text[1].setPosition(sf::Vector2f(width / 15 * 3.6, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	text[2].setFont(font);
	text[2].setColor(sf::Color::Color(0, 20, 60));
	text[2].setString("Back");
	text[2].setScale(0.6, 0.6);
	text[2].setPosition(sf::Vector2f(width / 15 * 3.6, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.5));

	songName = "Yeezy";

	text[3].setFont(font);
	text[3].setColor(sf::Color::Color(180, 35, 35));	//red
	
	text[3].setScale(0.6, 0.6);
	text[3].setPosition(sf::Vector2f(width / 15 * 7, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	selectedItemIndex = 0;
}


SoundOptions::~SoundOptions()
{
}

void SoundOptions::Draw(sf::RenderWindow &window)
{
	window.draw(background);
	window.draw(m_volSprite);
	m_vol2Sprite.setScale(volWidth / 100, 1);
	window.draw(m_vol2Sprite);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(text[i]);
	}
	text[3].setString(songName);
}

void SoundOptions::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		//beepSound.play();
		text[selectedItemIndex].setColor(sf::Color::Color(0, 20, 60));
		selectedItemIndex--;
		text[selectedItemIndex].setColor(sf::Color::Color(140, 140, 40));
	}
}

void SoundOptions::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS - 1)
	{
		//beepSound.play();
		text[selectedItemIndex].setColor(sf::Color::Color(0, 20, 60));
		selectedItemIndex++;
		text[selectedItemIndex].setColor(sf::Color::Color(140, 140, 40));
	}
}


void SoundOptions::Update(float time, sf::RenderWindow &window)
{
	/* initialize random seed: */
	
}

void SoundOptions::AlterVolume(int change, sf::Music &backgroundMusic)
{
	if (change == 1 && volWidth <= 90)
	{
		volWidth += 10;
	}
	if (change == -1 && volWidth >= 10)
	{
		volWidth -= 10;
	}
	backgroundMusic.setVolume(volWidth);
}

void SoundOptions::ChangeSong(int change,sf::Music &backgroundMusic)
{
	if (change == 1)
	{
		backgroundMusic.openFromFile("music.ogg");
		backgroundMusic.play();
		songName = "Space";
	}
	else if (change == -1)
	{
		backgroundMusic.openFromFile("music2.ogg");
		backgroundMusic.play();
		songName = "Yeezy";
	}
	
}