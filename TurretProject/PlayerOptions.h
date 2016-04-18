#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"

#define MAX_NUMBER_OF_ITEMS 4

class PlayerOptions
{

public:
	PlayerOptions(float width, float height, sf::Music &backgroundMusic);
	~PlayerOptions();

	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void Update(float time, sf::RenderWindow &window);
	int GetPressedItem() { return selectedItemIndex; }
	void AlterHealth(int change, Player &player);
	//void ChangeSong(int change, sf::Music &backgroundMusic);
	//void setVolArrows(bool x) { displayVolArrows = x; }
	//void setSongArrows(bool x) { displaySongArrows = x; }

private:
	int selectedItemIndex;

	sf::Texture m_healthTexture;
	sf::Sprite m_healthSprite;
	sf::Texture m_health2Texture;
	sf::Sprite m_health2Sprite;
	float healthWidth;

	sf::Font font;
	sf::Text text[MAX_NUMBER_OF_ITEMS];
	sf::Texture texture;
	sf::Sprite background;
	int random;

	sf::String songName;

	sf::Texture leftArrowTex;
	sf::Sprite leftArrowSpr;
	sf::Texture rightArrowTex;
	sf::Sprite rightArrowSpr;

	bool healthMax, healthMin; // songMax, songMin;
	bool displayHealthArrows; // displaySongArrows;
};

