#pragma once
#include "SFML\Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class GameOverMenu
{

public:
	GameOverMenu(float width, float height);
	~GameOverMenu();

	void Draw(sf::RenderWindow &window);
	void MoveLeft();
	void MoveRight();
	void Update(float time);
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text text[MAX_NUMBER_OF_ITEMS];
	sf::Texture borderTexture;
	sf::Sprite borderSprite;

	sf::Texture texture;
	sf::Sprite background;
	sf::IntRect animationRect;
	float frameTimer;
	int random;
};

