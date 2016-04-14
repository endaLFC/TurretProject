#include "stdafx.h"
#include "SoundOptions.h"


SoundOptions::SoundOptions(float width, float height, sf::Music &backgroundMusic)
{
	volMax = false;
	volMin = false;
	songMax = false;
	songMin = true;
	displayVolArrows = true;
	displaySongArrows = false;
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

	if (!leftArrowTex.loadFromFile("arrowLeft.png"))
	{
	}
	if (!rightArrowTex.loadFromFile("arrowRight.png"))
	{
	}
	
	//leftArrowSpr.setPosition(sf::Vector2f(width / 15 * 6.25, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.05));
	leftArrowSpr.setTexture(leftArrowTex);

	//rightArrowSpr.setPosition(sf::Vector2f(width / 15 * 11.1, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.05));
	rightArrowSpr.setTexture(rightArrowTex);

	m_volSprite.setOrigin(0, 0);
	m_volSprite.setPosition(width / 15 * 6.7, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.02);
	m_volSprite.setTexture(m_volTexture);

	volWidth = 50;
	m_vol2Sprite.setOrigin(0, 0);
	m_vol2Sprite.setPosition(width / 15 * 6.75, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.03);
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
	text[0].setPosition(sf::Vector2f(width / 15 * 3.6, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	text[1].setFont(font);
	text[1].setColor(sf::Color::Color(0, 20, 60));	//navy
	text[1].setString("Music");
	text[1].setScale(0.55, 0.55);
	text[1].setPosition(sf::Vector2f(width / 15 * 3.6, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.5));

	text[2].setFont(font);
	text[2].setColor(sf::Color::Color(0, 20, 60));
	text[2].setString("Back");
	text[2].setScale(0.6, 0.6);
	text[2].setPosition(sf::Vector2f(width / 15 * 3.6, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	songName = "Yeezy";

	text[3].setFont(font);
	text[3].setColor(sf::Color::Color(180, 35, 35));	//red
	
	text[3].setScale(0.6, 0.6);
	text[3].setPosition(sf::Vector2f(width / 15 * 7, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.5));

	selectedItemIndex = 0;
	songCount = 0;
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
	if (displayVolArrows == true)
	{
		leftArrowSpr.setPosition(sf::Vector2f(1100 / 15 * 6.26, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 2.05));
		rightArrowSpr.setPosition(sf::Vector2f(1100 / 15 * 11.2, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 2.05));
		if (volMin == false)
		{
			window.draw(leftArrowSpr);
		}
		if (volMax == false)
		{
			window.draw(rightArrowSpr);
		}
	}
	else if (displaySongArrows == true)
	{
		leftArrowSpr.setPosition(sf::Vector2f(1100 / 15 * 6.26, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 2.55));
		rightArrowSpr.setPosition(sf::Vector2f(1100 / 15 * 11.1, 800 / (MAX_NUMBER_OF_ITEMS + 1) * 2.55));
		if (songMin == false)
		{
			window.draw(leftArrowSpr);
		}
		if (songMax == false)
		{
			window.draw(rightArrowSpr);
		}
	}

	


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
	if (change == 1 && volWidth <= 80)
	{
		volWidth += 10;
		volMin = false;
	}
	else if (change == 1 && volWidth == 90)
	{
		volWidth += 10;
		volMax = true;
	}
	if (change == -1 && volWidth >= 20)
	{
		volWidth -= 10;
		volMax = false;
	}
	else if (change == -1 && volWidth == 10)
	{
		volWidth -= 10;
		volMin = true;
	}
	//backgroundMusic.setVolume(volWidth);
	sf::Listener::setGlobalVolume(volWidth);
}

void SoundOptions::ChangeSong(int change,sf::Music &backgroundMusic)
{
	if (change == 1 && songCount < 6)
	{
		songCount++;
		//songMax = true;
	}
	else if (change == -1 && songCount > 0)
	{
		songCount--;
	}

	//changing song
	if (songCount == 0)
	{
		backgroundMusic.openFromFile("music2.ogg");
		backgroundMusic.play();
		songName = "Yeezy";
		songMin = true;
	}
	else if (songCount == 1)
	{
		backgroundMusic.openFromFile("music.ogg");
		backgroundMusic.play();
		songName = "Space";
		songMin = false;
	}
	else if (songCount == 2)
	{
		backgroundMusic.openFromFile("Drake.ogg");
		backgroundMusic.play();
		songName = "Bling";
	}
	else if (songCount == 3)
	{
		backgroundMusic.openFromFile("Schoolboy.ogg");
		backgroundMusic.play();
		songName = "Schoolboy";
	}
	else if (songCount == 4)
	{
		backgroundMusic.openFromFile("Sexy.ogg");
		backgroundMusic.play();
		songName = "Sexy";
	}
	else if (songCount == 5)
	{
		backgroundMusic.openFromFile("StarWars.ogg ");
		backgroundMusic.play();
		songName = "Phantom";
		songMax = false;
	}
	else if (songCount == 6)
	{
		backgroundMusic.openFromFile("Journey.ogg ");
		backgroundMusic.play();
		songName = "Journey";
		songMax = true;
	}
	
}