#pragma once
#include "SFML\Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4

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
	void GameWon(bool won);
	void SetScore(int score);

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text text[MAX_NUMBER_OF_ITEMS + 1];
	sf::Texture borderTexture;
	sf::Sprite borderSprite;

	sf::Texture borderTexture2;
	sf::Sprite borderSprite2;

	sf::Texture tableTexture;
	sf::Sprite tableSprite;

	sf::Texture texture;
	sf::Texture texture2;
	sf::Sprite background;
	sf::IntRect animationRect;
	float frameTimer;
	int random;
};

