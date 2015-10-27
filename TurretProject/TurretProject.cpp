//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>
#include "Menu.h"



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

	texture.loadFromFile("Earth.jpg");
	background.setTexture(texture);

	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
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
				
				break;

			case PLAY:
				

				break;

			case OPTIONS:
				

				break;

			case EXIT:

				window.close();

				break;
			}
		}



		switch (gameMode)
		{
		case MENU:
			window.clear();

			menu.Draw(window);

			window.display();
			break;

		case PLAY:
			window.clear();

			window.draw(background);

			window.display();
			break;

		case OPTIONS:
			window.clear();


			window.display();

			break;
		}


	} //loop back for next frame

	return EXIT_SUCCESS;
}