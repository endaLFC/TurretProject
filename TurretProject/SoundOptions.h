#pragma once
#include "SFML\Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4

class SoundOptions
{

public:
	SoundOptions(float width, float height, sf::Music &backgroundMusic);
	~SoundOptions();

	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void Update(float time, sf::RenderWindow &window);
	int GetPressedItem() { return selectedItemIndex; }
	void AlterVolume(int change, sf::Music &backgroundMusic);
	void ChangeSong(int change, sf::Music &backgroundMusic);
	void setVolArrows(bool x) { displayVolArrows = x; }
	void setSongArrows(bool x) { displaySongArrows = x; }


private:
	int selectedItemIndex;

	sf::Texture m_volTexture;
	sf::Sprite m_volSprite;
	sf::Texture m_vol2Texture;
	sf::Sprite m_vol2Sprite;
	float volWidth;

	sf::Font font;
	sf::Text text[MAX_NUMBER_OF_ITEMS];
	sf::Texture texture;
	sf::Sprite background;
	sf::IntRect animationRect;
	float frameTimer;
	float initialFrameTimer;
	int random;

	sf::String songName;

	sf::Texture leftArrowTex;
	sf::Sprite leftArrowSpr;
	sf::Texture rightArrowTex;
	sf::Sprite rightArrowSpr;

	bool volMax, volMin, songMax, songMin;
	bool displayVolArrows, displaySongArrows;
	int songCount;
};

