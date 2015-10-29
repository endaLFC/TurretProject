//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 

#include "Menu.h"
#include "Player.h"


////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");

	Menu menu(window.getSize().x, window.getSize().y);

	int gameMode = 0;
	CONST int MENU = 0, PLAY = 1, OPTIONS = 2, EXIT = 3;

	sf::Texture texture;
	sf::Sprite background;

	sf::Time time;
	sf::Clock clock;

	Player p1;

	texture.loadFromFile("Earth.jpg");
	background.setTexture(texture);

	// Start game loop 
	while (window.isOpen())
	{
		time = clock.getElapsedTime();
		float t = time.asSeconds();
		clock.restart();

		// Process events 
		sf::Event Event;
		switch (gameMode)
		{
		case MENU:
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				menu.MoveUp();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				menu.MoveDown();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if (menu.GetPressedItem() == 0)
				{
					gameMode = PLAY;
					std::cout << "Play Button has been pressed" << std::endl;
				}
				if (menu.GetPressedItem() == 1)
				{
					gameMode = OPTIONS;
					std::cout << "Options Button has been pressed" << std::endl;
				}
				if (menu.GetPressedItem() == 2)
					gameMode = EXIT;
			}

			//DRAW CODE HERE
			window.clear();
			menu.Draw(window);
			window.display();
				
			break;

		case PLAY:
			p1.Update(t);

			
			//DRAW CODE HERE
			window.clear();
			window.draw(background);
			p1.Draw(window);
			window.display();
			break;

		case OPTIONS:
				
			//DRAW CODE HERE
			window.clear();

			window.display();
			break;

		case EXIT:

			window.close();

			break;
		}

	} //loop back for next frame

	return EXIT_SUCCESS;
}