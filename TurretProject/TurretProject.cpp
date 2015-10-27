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

	/*
	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arkhip_font.ttf");

	//create a formatted text string
	sf::Text text;
	text.setFont(font);
	text.setString("Hello World");
	text.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	text.setPosition(20, 40);
	text.setCharacterSize(50);

	//create a circle
	sf::CircleShape circle(50);
	circle.setPosition(300, 200);

	*/

	int gameMode = 0;
	CONST int MENU = 0, PLAY = 1, OPTIONS = 2, EXIT = 3;


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
					if(menu.GetPressedItem() == 0)
						std::cout << "Play Button has been pressed" << std::endl;
					if (menu.GetPressedItem() == 1)
						std::cout << "Options Button has been pressed" << std::endl;
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

		//prepare frame
		window.clear();

		menu.Draw(window);

		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}