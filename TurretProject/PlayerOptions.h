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
	void ChangeSkin(int change, Player &player);
	void setHealthArrows(bool x) { displayHealthArrows = x; }
	void setSkinArrows(bool x) { displaySkinArrows = x; }

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

	sf::String skinName;

	sf::Texture leftArrowTex;
	sf::Sprite leftArrowSpr;
	sf::Texture rightArrowTex;
	sf::Sprite rightArrowSpr;

	bool healthMax, healthMin, skinMax, skinMin; // songMax, songMin;
	bool displayHealthArrows, displaySkinArrows; // displaySongArrows;
	int skinCount;
};

