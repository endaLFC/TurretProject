#pragma once
#include "SFML\Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{

	public:
		Menu(float width, float height);
		~Menu();

		void Draw(sf::RenderWindow &window);
		void MoveUp();
		void MoveDown();
		void Update(float time);
		int GetPressedItem() {return selectedItemIndex;}

	private:
		int selectedItemIndex;
		sf::Font font;
		sf::Text text[MAX_NUMBER_OF_ITEMS];
		sf::Texture texture;
		sf::Sprite background;
		sf::IntRect animationRect;
		float frameTimer;
		float initialFrameTimer;
		int random;
};

