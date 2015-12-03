//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 

#include "Menu.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"


////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	int counter = 0;
	Menu menu(window.getSize().x, window.getSize().y);

	int gameMode = 0;
	CONST int MENU = 0, PLAY = 1, OPTIONS = 2, EXIT = 3, GAMEOVER = 4;

	sf::Texture playTexture;
	sf::Texture gameOverTexture;
	sf::Texture optionsTexture;
	sf::Sprite background;

	sf::Time time;
	sf::Clock clock;

	Player p1;
	p1.Initialise();

	/*Enemy enemies[3];

	enemies[1] = Enemy(sf::Vector2f(700, 0), 75);
	enemies[2] = Enemy(sf::Vector2f(400, 0), 50);

	for (int i = 0; i < 3; i++)
	{
		enemies[i].Load();
	}*/

	playTexture.loadFromFile("Earth.jpg");
	gameOverTexture.loadFromFile("GameOver.jpg");
	optionsTexture.loadFromFile("OptionsBackground.jpg");

	BulletManager::GetInstance()->Init();
	EnemyManager::GetInstance()->Init();

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
				{
					gameMode = EXIT;
				}
			}

			//DRAW CODE HERE
			window.clear();
			menu.Draw(window);
			window.display();
				
			break;

		case PLAY:
			p1.Update(t);
			/*for (int i = 0; i < 3; i++)
			{
				enemies[i].Update(t, p1.GetPos());
			}*/
			BulletManager::GetInstance()->Update(t);
			EnemyManager::GetInstance()->Update(t, p1.GetPos());

			//DRAW CODE HERE
			window.clear();
			background.setTexture(playTexture);
			window.draw(background);

			p1.Draw(window);
			//for (int i = 0; i < 3; i++)
			//{
			//	if (BulletManager::GetInstance()->IsColliding(&enemies[i]))
			//	{
			//		//do something
			//		enemies[i].SetAlive(false);
			//	}

			//	if (enemies[i].IsColliding(p1.GetPos(), p1.GetRadius()))
			//	{
			//		gameMode = GAMEOVER;
			//	}

			//	enemies[i].Draw(window);	

			//}
			if (BulletManager::GetInstance()->IsColliding())
			{
				//do something
				//enemies[i].SetAlive(false);
			}

			if (EnemyManager::GetInstance()->IsColliding(p1.GetPos(), p1.GetRadius()))
			{
				gameMode = GAMEOVER;
			}

			EnemyManager::GetInstance()->Draw(window);


			
			counter++;

			if (counter > 1000)
			{
				counter = 0;
			}



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && counter == 1)
			{
				EnemyManager::GetInstance()->CreateEnemy(sf::Vector2f(0,0));
			}






			BulletManager::GetInstance()->Draw(window);
			
			window.display();
			break;

		case OPTIONS:
				
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				gameMode = MENU;
			}

			//DRAW CODE HERE
			window.clear();
			background.setTexture(optionsTexture);
			window.draw(background);
			window.display();
			break;

		case EXIT:

			window.close();

			break;

		case GAMEOVER:

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			//DRAW CODE HERE
			window.clear();

			background.setTexture(gameOverTexture);
			window.draw(background);
			window.display();
			break;
		}

	} //loop back for next frame

	return EXIT_SUCCESS;
}