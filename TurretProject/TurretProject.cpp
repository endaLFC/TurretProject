//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 

#include "Menu.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "ParticleSystem.h"


////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	//window.setFramerateLimit(60);
	int counter = 0;
	Menu menu(window.getSize().x, window.getSize().y);

	int gameMode = 0;
	CONST int MENU = 0, PLAY = 1, OPTIONS = 2, EXIT = 3, GAMEOVER = 4;

	sf::Texture playTexture;
	sf::Texture gameOverTexture;
	sf::Texture optionsTexture;
	sf::Texture radarTexture;
	sf::Texture radarBorderTexture;
	sf::Texture scoreHUDTexture;
	sf::Sprite background;
	sf::Sprite radarBackground;
	sf::Sprite radarBorderSpr;
	sf::Sprite scoreHUDSprite;

	sf::Time time;
	sf::Clock clock;
	

	Player p1;
	p1.Initialise();

	playTexture.loadFromFile("space.jpg");
	radarTexture.loadFromFile("radar.png");
	radarBorderTexture.loadFromFile("radarBorder.png");
	scoreHUDTexture.loadFromFile("hud.png");
	gameOverTexture.loadFromFile("GameOver.jpg");
	optionsTexture.loadFromFile("OptionsBackground.jpg");

	BulletManager::GetInstance()->Init();
	EnemyManager::GetInstance()->Init();
	ParticleSystem::GetInstance()->Init();

	sf::View main(sf::FloatRect(0, 0, 800, 600));
	sf::View miniMap;

	miniMap.setViewport(sf::FloatRect(0.03f, 0.8f, 0.25f, 0.25f));

	background.setTexture(playTexture);
	radarBackground.setTexture(radarTexture);
	scoreHUDSprite.setTexture(scoreHUDTexture);
	radarBorderSpr.setTexture(radarBorderTexture);

	scoreHUDSprite.setPosition(160,0);
	radarBorderSpr.setPosition(0,468);

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
			background.setTexture(playTexture);

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
			BulletManager::GetInstance()->Update(t);
			EnemyManager::GetInstance()->Update(t, p1.GetPos());
			ParticleSystem::GetInstance()->Update(t);

			//DRAW CODE HERE
			

			if (BulletManager::GetInstance()->IsColliding())
			{
				//do something
				//enemies[i].SetAlive(false);
			}

			if (EnemyManager::GetInstance()->IsColliding(p1.GetPos(), p1.GetRadius()))
			{
				gameMode = GAMEOVER;
			}

			counter++;

			if (counter > 500)
			{
				counter = 0;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && counter == 1)
			{
				EnemyManager::GetInstance()->CreateEnemy(sf::Vector2f(0,0));
			}

			window.clear();
			window.setView(main);
			window.draw(background);
			EnemyManager::GetInstance()->Draw(window);
			BulletManager::GetInstance()->Draw(window);
			ParticleSystem::GetInstance()->Draw(window);
			window.draw(scoreHUDSprite);
			p1.Draw(window);

			window.setView(miniMap);
			window.draw(radarBackground);
			p1.Draw(window);
			EnemyManager::GetInstance()->Draw(window);
			BulletManager::GetInstance()->Draw(window);
			ParticleSystem::GetInstance()->Draw(window);

			window.setView(main); //setting view back to main
			window.draw(radarBorderSpr);

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