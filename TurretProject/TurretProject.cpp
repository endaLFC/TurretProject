//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 

#include "Menu.h"
#include "OptionsMenu.h"
#include "GameOverMenu.h"
#include "SoundOptions.h"
#include "PlayerOptions.h"
#include "Player.h"
#include "BulletManager.h"
//#include "EnemyManager.h"
#include "ParticleSystem.h"
#include "Energy.h"
#include "Boid.h"
#include "Pvector.h"
#include "Flock.h"
#include "Factory.h"
#include "Obstacle.h"
#include "Powerup.h"
#include "FlockEnemy.h"
#include "SwarmEnemy.h"
////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int gameMode = 0;
CONST int MENU = 0, PLAY = 1, OPTIONS = 2, EXIT = 3, GAMEOVER = 4, AUDIO = 5, PLAYER = 6;
sf::RenderWindow window(sf::VideoMode(1100, 800, 32), "SFML First Program");
float t;
float gameOverCount = 0;
Player p1;
Powerup mushroomSmall;
Powerup mushroomColour;

bool enemiesDestroyed = true;
bool gameReset = false;

Obstacle obstacle;
Obstacle obstacle2;
Obstacle obstacle3;

float boidsSize = 10;
Flock flock;
Flock swarm;
Flock factory;

vector<FlockEnemy*> flockEnemies;
vector<SwarmEnemy*> swarmEnemies;
vector<Factory*> factories;

void GameOverTimer()
{
	gameOverCount += t;
	if (gameOverCount > 2)
	{
		gameMode = GAMEOVER;
		gameOverCount = 0;
	}
}

void ManageFlockEnemies()
{
	for (int i = 0; i < flockEnemies.size(); i++)
	{
		flockEnemies[i]->Draw(window);
		flockEnemies[i]->Update(t);
		//Matches up the location of the shape to the boid
		flockEnemies[i]->SetPosition(sf::Vector2f(flock.getBoid(i).location.x, flock.getBoid(i).location.y));
		// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
		float theta;
		theta = flock.getBoid(i).angle(flock.getBoid(i).velocity);
		flockEnemies[i]->SetRotation(theta);

		if (BulletManager::GetInstance()->IsColliding(flockEnemies[i]->GetPosition(), flockEnemies[i]->GetRadius(), flockEnemies[i]->GetAlive()) && flockEnemies[i]->GetAlive() == true)
		{
			flockEnemies[i]->Colliding(true, p1.GetPos());

		}
		if (flockEnemies[i]->IsColliding(p1.GetPos(), p1.GetRadius()) && p1.GetHealth() > 0)
		{
			flockEnemies[i]->Colliding(true, p1.GetPos());
			p1.AlterHealth(-7);
		}
		else if (flockEnemies[i]->IsColliding(obstacle.GetPosition(), obstacle.GetRadius()))
		{
			flockEnemies[i]->Colliding(false, p1.GetPos());
		}
		else if (flockEnemies[i]->IsColliding(obstacle2.GetPosition(), obstacle2.GetRadius()))
		{
			flockEnemies[i]->Colliding(false, p1.GetPos());
		}
		else if (flockEnemies[i]->IsColliding(obstacle3.GetPosition(), obstacle3.GetRadius()))
		{
			flockEnemies[i]->Colliding(false, p1.GetPos());
		}
	}
}
void ManageSwarmEnemies()
{
	for (int i = 0; i < swarmEnemies.size(); i++)
	{
		swarmEnemies[i]->Draw(window);
		swarmEnemies[i]->Update(t);
		//Matches up the location of the shape to the boid
		swarmEnemies[i]->SetPosition(sf::Vector2f(swarm.getBoid(i).location.x, swarm.getBoid(i).location.y));
		// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
		float theta;
		theta = swarm.getBoid(i).angle(swarm.getBoid(i).velocity);
		swarmEnemies[i]->SetRotation(theta);

		if (BulletManager::GetInstance()->IsColliding(swarmEnemies[i]->GetPosition(), swarmEnemies[i]->GetRadius(), swarmEnemies[i]->GetAlive()) && swarmEnemies[i]->GetAlive() == true)
		{
			swarmEnemies[i]->Colliding(true, p1.GetPos());
		}
		if (swarmEnemies[i]->IsColliding(p1.GetPos(), p1.GetRadius()) && p1.GetHealth() > 0)
		{
			swarmEnemies[i]->Colliding(true, p1.GetPos());
			p1.AlterHealth(-3);
		}
		else if (swarmEnemies[i]->IsColliding(obstacle.GetPosition(), obstacle.GetRadius()))
		{
			swarmEnemies[i]->Colliding(false, p1.GetPos());
		}
		else if (swarmEnemies[i]->IsColliding(obstacle2.GetPosition(), obstacle2.GetRadius()))
		{
			swarmEnemies[i]->Colliding(false, p1.GetPos());
		}
		else if (swarmEnemies[i]->IsColliding(obstacle3.GetPosition(), obstacle3.GetRadius()))
		{
			swarmEnemies[i]->Colliding(false, p1.GetPos());
		}
	}
}
void ManageFactoryEnemies()
{
	//drawing factory boids
	for (int i = 0; i < factories.size(); i++)
	{
		factories[i]->Draw(window);
		factories[i]->Update(t);
		//Matches up the location of the shape to the boid
		factories[i]->SetPosition(sf::Vector2f(factory.getBoid(i).location.x, factory.getBoid(i).location.y));
		// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
		float theta;
		theta = factory.getBoid(i).angle(factory.getBoid(i).velocity);
		factories[i]->SetRotation(theta);

		if (BulletManager::GetInstance()->IsColliding(factories[i]->GetPosition(), factories[i]->GetRadius(), factories[i]->GetAlive()) && factories[i]->GetAlive() == true)
		{
			factories[i]->Colliding(true, p1.GetPos());
		}
		if (factories[i]->IsColliding(p1.GetPos(), p1.GetRadius()) && p1.GetHealth() > 0)
		{
			factories[i]->Colliding(true, p1.GetPos());
			if (factories[i]->GetAlive() == false)
			{
				p1.AlterHealth(-25);
			}
		}
		else if (factories[i]->IsColliding(obstacle.GetPosition(), obstacle.GetRadius()))
		{
			factories[i]->Colliding(false, p1.GetPos());
		}
		else if (factories[i]->IsColliding(obstacle2.GetPosition(), obstacle2.GetRadius()))
		{
			factories[i]->Colliding(false, p1.GetPos());
		}
		else if (factories[i]->IsColliding(obstacle3.GetPosition(), obstacle3.GetRadius()))
		{
			factories[i]->Colliding(false, p1.GetPos());
		}
	}
}
void ManageEnemies()
{
	ManageFlockEnemies();
	ManageSwarmEnemies();
	ManageFactoryEnemies();
}

void CreateEnemies()
{
	for (int i = 0; i < 20; i++) //Creating flock enemies
	{
		float x, y;
		x = rand() % 2200;
		y = rand() % 200 + 400;
		Boid b(x, y, 0); //Starts the boid with a random position in the window.
		FlockEnemy *fE = new FlockEnemy;
		fE->Initialise();
		fE->SetPosition(sf::Vector2f(x, y));
		flock.addBoid(b);
		flockEnemies.push_back(fE);
	}

	for (int i = 0; i < 50; i++) //Creating swarm enemies
	{
		float x, y;
		x = rand() % 2200;
		y = rand() % 200 + 700;
		Boid b(x, y, 1); //Starts the boid with a random position in the window.
		SwarmEnemy *sE = new SwarmEnemy;
		sE->Initialise();
		sE->SetPosition(sf::Vector2f(x, y));
		swarm.addBoid(b);
		swarmEnemies.push_back(sE);
	}

	for (int i = 0; i < 5; i++) //Number of boids is hardcoded for testing pusposes.
	{
		//Boid b(rand() % window_width, rand() % window_height); //Starts the boid with a random position in the window.
		Boid b(800, 1000, 2);
		Factory *f = new Factory;
		f->Initialise();
		f->SetPosition(sf::Vector2f(800, 600));
		factory.addBoid(b);
		factories.push_back(f);
	}
}

void ResetGame()
{
	if (gameReset == false)
	{
		p1.Restart();
		mushroomSmall.setAlive(true);
		mushroomColour.setAlive(true);
		gameReset = true;
		//CreateEnemies();
	}
}



int main()
{
	sf::Listener::setGlobalVolume(50);
	srand(time(NULL));
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 1100, 800));

	sf::Music backgroundMusic;
	sf::Sound menuBeep;
	sf::SoundBuffer menuBeepBuffer;
	sf::Sound menuBeep2;
	sf::SoundBuffer menuBeep2Buffer;

	backgroundMusic.openFromFile("music2.ogg");
	backgroundMusic.setVolume(50);
	backgroundMusic.play();

	menuBeepBuffer.loadFromFile("menubeep.wav");
	menuBeep.setBuffer(menuBeepBuffer);
	menuBeep.setVolume(30);

	menuBeep2Buffer.loadFromFile("menubeep2.wav");
	menuBeep2.setBuffer(menuBeep2Buffer);
	menuBeep2.setVolume(30);

	// Create the main window 

	window.setFramerateLimit(60);
	int gameOverCounter = 0;
	Menu menu(window.getSize().x, window.getSize().y);
	GameOverMenu gameOverMenu(window.getSize().x, window.getSize().y);
	OptionsMenu optionsMenu(window.getSize().x, window.getSize().y);
	SoundOptions soundOptions(window.getSize().x, window.getSize().y, backgroundMusic);
	PlayerOptions playerOptions(window.getSize().x, window.getSize().y, backgroundMusic);


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

	
	p1.Initialise();


	playTexture.loadFromFile("space3.jpg");
	radarTexture.loadFromFile("space2.jpg");
	radarBorderTexture.loadFromFile("radarBorder3.png");
	scoreHUDTexture.loadFromFile("hud2.png");
	//gameOverTexture.loadFromFile("GameOver.jpg");
	//optionsTexture.loadFromFile("OptionsBkg.jpg");

	BulletManager::GetInstance()->Init();
	//EnemyManager::GetInstance()->Init();
	ParticleSystem::GetInstance()->Init();
	Energy::GetInstance()->Initialise();

	sf::View main(sf::FloatRect(0, 0, 1100, 800));
	sf::View miniMap(sf::FloatRect(0, 0, 3300, 2400));
	sf::View scoreHUD(sf::FloatRect(0, 0, 500, 80));

	miniMap.setViewport(sf::FloatRect(0.03f, 0.72f, 0.25f, 0.25f));
	scoreHUD.setViewport(sf::FloatRect(0.2f, 0.02f, 0.6f, 0.1f));

	background.setTexture(playTexture);
	radarBackground.setTexture(radarTexture);
	scoreHUDSprite.setTexture(scoreHUDTexture);
	radarBorderSpr.setTexture(radarBorderTexture);

	//scoreHUDSprite.setPosition(160,0);
	radarBorderSpr.setPosition(10, 550);

	obstacle.Initialise(sf::Vector2f(600, 1600), 100, 100, 255, 40);
	obstacle2.Initialise(sf::Vector2f(1700, 800), 100, 255, 100, 80);
	obstacle3.Initialise(sf::Vector2f(1300, 100), 255, 100, 100, 110);

	mushroomSmall.Initialise(obstacle.GetPosition(), obstacle2.GetPosition(), obstacle3.GetPosition(), 0);
	mushroomColour.Initialise(obstacle.GetPosition(), obstacle2.GetPosition(), obstacle3.GetPosition(), 1);

	CreateEnemies();

	//Start game loop 
	while (window.isOpen())
	{
		time = clock.getElapsedTime();
		t = time.asSeconds();
		clock.restart();
		// Process events 
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
				
			switch (gameMode)
			{
			case MENU:
				if (event.type == event.KeyPressed)
				{

					if (event.key.code == sf::Keyboard::Up)
					{
						if (menu.GetPressedItem() > 0)
						{
							menuBeep.play();
						}
						menu.MoveUp();
					}
					else if (event.key.code == sf::Keyboard::Down)
					{
						if (menu.GetPressedItem() < 2)
						{
							menuBeep.play();
						}
						menu.MoveDown();
					}
					else if (event.key.code == sf::Keyboard::Return)
					{
						menuBeep2.play();
						if (menu.GetPressedItem() == 0)
						{
							gameMode = PLAY;
						}
						if (menu.GetPressedItem() == 1)
						{
							gameMode = OPTIONS;
						}
						if (menu.GetPressedItem() == 2)
						{
							gameMode = EXIT;
						}
					}
				}
				break;
			case OPTIONS:
				if (event.type == event.KeyPressed)
				{

					if (event.key.code == sf::Keyboard::Left)
					{
						if (optionsMenu.GetPressedItem() > 0)
						{
							menuBeep.play();
						}
						optionsMenu.MoveLeft();
					}
					else if (event.key.code == sf::Keyboard::Right)
					{
						if (optionsMenu.GetPressedItem() < 2)
						{
							menuBeep.play();
						}
						optionsMenu.MoveRight();
					}
					else if (event.key.code == sf::Keyboard::Return)
					{
						menuBeep2.play();
						if (optionsMenu.GetPressedItem() == 0)
						{
							gameMode = PLAYER;
							//Video button pressed
						}
						if (optionsMenu.GetPressedItem() == 1)
						{
							//audio button pressed
							gameMode = AUDIO;
						}
						if (optionsMenu.GetPressedItem() == 2)
						{

							gameMode = MENU;
						}
					}
				}
				break;

			case AUDIO:
				if (event.type == event.KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Up)
					{
						if (soundOptions.GetPressedItem() > 0)
						{
							menuBeep.play();
						}
						if (soundOptions.GetPressedItem() == 1)
						{
							soundOptions.setVolArrows(true);
							soundOptions.setSongArrows(false);
						}
						else if (soundOptions.GetPressedItem() == 2)
						{
							soundOptions.setSongArrows(true);
						}
						soundOptions.MoveUp();
					}
					else if (event.key.code == sf::Keyboard::Down)
					{
						if (soundOptions.GetPressedItem() < 2)
						{
							menuBeep.play();
						}
						if (soundOptions.GetPressedItem() == 0)
						{
							soundOptions.setVolArrows(false);
							soundOptions.setSongArrows(true);
						}
						else if (soundOptions.GetPressedItem() == 1)
						{
							soundOptions.setSongArrows(false);
						}
						soundOptions.MoveDown();
					}
					else if (event.key.code == sf::Keyboard::Right)
					{
						menuBeep.play();
						if (soundOptions.GetPressedItem() == 0)
						{
							//volume increased
							soundOptions.AlterVolume(1, backgroundMusic);
						}
						else if (soundOptions.GetPressedItem() == 1)
						{
							//song change
							soundOptions.ChangeSong(1, backgroundMusic);
						}
					}
					else if (event.key.code == sf::Keyboard::Left)
					{
						menuBeep.play();
						if (soundOptions.GetPressedItem() == 0)
						{
							//volume increased
							soundOptions.AlterVolume(-1, backgroundMusic);
						}
						else if (soundOptions.GetPressedItem() == 1)
						{
							//song change
							soundOptions.ChangeSong(-1, backgroundMusic);
						}
					}
					else if (event.key.code == sf::Keyboard::Return)
					{
						menuBeep2.play();
						if (soundOptions.GetPressedItem() == 0)
						{
							//volume button pressed
						}
						else if (soundOptions.GetPressedItem() == 1)
						{
							//music button pressed
						}
						else if (soundOptions.GetPressedItem() == 2)
						{
							gameMode = OPTIONS;
						}
					}
				}
				break;

			case PLAYER:
				if (event.type == event.KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Up)
					{
						if (playerOptions.GetPressedItem() > 0)
						{
							menuBeep.play();
						}
						if (playerOptions.GetPressedItem() == 1)
						{
							playerOptions.setSkinArrows(true);
							playerOptions.setHealthArrows(false);
						}
						else if (playerOptions.GetPressedItem() == 2)
						{
							playerOptions.setHealthArrows(true);
						}
						playerOptions.MoveUp();
					}
					else if (event.key.code == sf::Keyboard::Down)
					{
						if (playerOptions.GetPressedItem() < 2)
						{
							menuBeep.play();
						}
						if (playerOptions.GetPressedItem() == 0)
						{
							playerOptions.setSkinArrows(false);
							playerOptions.setHealthArrows(true);
						}
						else if (playerOptions.GetPressedItem() == 1)
						{
							playerOptions.setHealthArrows(false);
						}
						playerOptions.MoveDown();
					}
					else if (event.key.code == sf::Keyboard::Right)
					{
						menuBeep.play();
						if (playerOptions.GetPressedItem() == 0)
						{
							//skin change
							playerOptions.ChangeSkin(1, p1);
						}
						else if (playerOptions.GetPressedItem() == 1)
						{
							//health change
							playerOptions.AlterHealth(1, p1);
						}
					}
					else if (event.key.code == sf::Keyboard::Left)
					{
						menuBeep.play();
						if (playerOptions.GetPressedItem() == 0)
						{
							//skin change
							playerOptions.ChangeSkin(-1, p1);
						}
						else if (playerOptions.GetPressedItem() == 1)
						{
							//health change
							playerOptions.AlterHealth(-1, p1);
						}
					}
					else if (event.key.code == sf::Keyboard::Return)
					{
						menuBeep2.play();
						if (playerOptions.GetPressedItem() == 0)
						{
							//skin button pressed
						}
						else if (playerOptions.GetPressedItem() == 1)
						{
							//health button pressed
						}
						else if (playerOptions.GetPressedItem() == 2)
						{
							gameMode = OPTIONS;
						}
					}
				}
				break;
			case GAMEOVER:
				ResetGame();
				if (event.type == event.KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Left)
					{
						
						if (gameOverMenu.GetPressedItem() > 0)
						{
							menuBeep.play();
						}
						gameOverMenu.MoveLeft();
					}
					else if (event.key.code == sf::Keyboard::Right)
					{
						if (gameOverMenu.GetPressedItem() < 2)
						{
							menuBeep.play();
						}
						
						gameOverMenu.MoveRight();
					}
					else if (event.key.code == sf::Keyboard::Return)
					{
						menuBeep2.play();
						if (gameOverMenu.GetPressedItem() == 0)
						{
							//skin button pressed
							gameMode = PLAY;
						}
						else if (gameOverMenu.GetPressedItem() == 1)
						{
							gameMode = MENU;
						}
						else if (gameOverMenu.GetPressedItem() == 2)
						{
							gameMode = EXIT;
						}
					}
				}
				break;
			}
		}			//end game loop

		switch (gameMode)
		{
		case MENU:
			window.setKeyRepeatEnabled(false);

			background.setTexture(playTexture);

			menu.Update(t);

			//DRAW CODE HERE
			window.clear();
			menu.Draw(window);

			window.display();

			break;

		case PLAY:
			gameReset = false;
			p1.Update(t);
			BulletManager::GetInstance()->Update(t);
			//EnemyManager::GetInstance()->Update(t, p1.GetPos());
			ParticleSystem::GetInstance()->Update(t);
			Energy::GetInstance()->Update(t);
			if (mushroomColour.getAlive() == false)
			{
				mushroomColour.Update(t);
			}
			if (mushroomSmall.getAlive() == false)
			{
				mushroomSmall.Update(t);
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			window.clear();

			if (p1.GetPos().x >= 550 && p1.GetPos().x <= 1850)
			{
				view.setCenter(p1.GetPos().x, view.getCenter().y);
			}
			else if (p1.GetPos().x < 550)
			{
				view.setCenter(550, view.getCenter().y);
			}
			else if (p1.GetPos().x > 1850)
			{
				view.setCenter(1850, view.getCenter().y);
			}
			if (p1.GetPos().y >= 400 && p1.GetPos().y <= 1400)
			{
				view.setCenter(view.getCenter().x, p1.GetPos().y);
			}
			else if (p1.GetPos().y < 400)
			{
				view.setCenter(view.getCenter().x, 400);
			}
			else if (p1.GetPos().y > 1400)
			{
				view.setCenter(view.getCenter().x, 1400);
			}
			window.setView(view);
			window.draw(background);

			//creating all enemies
			ManageEnemies();

			if (obstacle.IsColliding(p1.GetPos(), p1.GetRadius()))
			{
				p1.AlterHealth(-100);
				p1.SetAlive(false);
			}
			else if (obstacle2.IsColliding(p1.GetPos(), p1.GetRadius()))
			{
				p1.AlterHealth(-100);
				p1.SetAlive(false);

			}
			else if (obstacle3.IsColliding(p1.GetPos(), p1.GetRadius()))
			{
				p1.AlterHealth(-100);
				p1.SetAlive(false);
			}

			if (p1.GetHealth() <= 0)
			{
				p1.SetAlive(false);
				GameOverTimer();
			}

			if (mushroomSmall.IsColliding(p1.GetPos(), p1.GetRadius()) && mushroomSmall.GetType() == 0)// && mushroomSmall.getAlive() == true)
			{
				p1.SetShrink(true);
			}

			if (mushroomColour.IsColliding(p1.GetPos(), p1.GetRadius()) && mushroomColour.GetType() == 1)// && mushroomColour.getAlive() == true)
			{
				p1.SetSpeed(150, 600);		//upgrading turn speed and max speed
			}

			obstacle.Rotate(t);
			obstacle.Draw(window);
			obstacle2.Rotate(t);
			obstacle2.Draw(window);
			obstacle3.Rotate(t*0.3);
			obstacle3.Draw(window);

			mushroomSmall.Draw(window);
			mushroomColour.Draw(window);

			//Applies the three rules to each boid in the flock and changes them accordingly.
			flock.flocking(p1.GetPos(), obstacle.GetPosition());
			flock.flocking(p1.GetPos(), obstacle2.GetPosition());
			flock.flocking(p1.GetPos(), obstacle3.GetPosition());

			swarm.swarming(p1.GetPos());

			factory.flocking(p1.GetPos(), obstacle.GetPosition());
			factory.flocking(p1.GetPos(), obstacle2.GetPosition());
			factory.flocking(p1.GetPos(), obstacle3.GetPosition());

			BulletManager::GetInstance()->Draw(window);
			ParticleSystem::GetInstance()->Draw(window);
			p1.Draw(window);

			window.setView(miniMap);
			window.draw(radarBackground);
			obstacle.Draw(window);
			obstacle2.Draw(window);
			obstacle3.Draw(window);
			mushroomSmall.SetSpriteScale(2);
			mushroomSmall.Draw(window);
			mushroomSmall.SetSpriteScale(1);
			mushroomColour.SetSpriteScale(2);
			mushroomColour.Draw(window);
			mushroomColour.SetSpriteScale(1);
			p1.Draw(window);

			for (int i = 0; i < flockEnemies.size(); i++)
			{
				flockEnemies[i]->SetScale(2);
				flockEnemies[i]->Draw(window);
				flockEnemies[i]->SetScale(1);
			}
			for (int i = 0; i < swarmEnemies.size(); i++)
			{
				swarmEnemies[i]->SetScale(2);
				swarmEnemies[i]->Draw(window);
				swarmEnemies[i]->SetScale(1);
			}
			for (int i = 0; i < factories.size(); i++)
			{
				//factories[i]->SetScale(3);
				factories[i]->Draw(window);
				//factories[i]->SetScale(1);
			}
			BulletManager::GetInstance()->Draw(window);
			ParticleSystem::GetInstance()->Draw(window);

			window.setView(scoreHUD);
			p1.DrawScore(window);
			window.draw(scoreHUDSprite);

			Energy::GetInstance()->Draw(window);

			window.setView(main); //setting view back to main
			window.draw(radarBorderSpr);
			p1.DrawLock(window);

			window.display();
			break;

		case OPTIONS:
			optionsMenu.Update(t);
			//DRAW CODE HERE
			window.clear();
			optionsMenu.Draw(window);
			window.display();
			break;

		case AUDIO:
			soundOptions.Update(t, window);
			//DRAW CODE HERE
			window.clear();
			soundOptions.Draw(window);
			window.display();
			break;

		case PLAYER:
			playerOptions.Update(t, window);
			//DRAW CODE HERE
			window.clear();
			playerOptions.Draw(window);
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

			gameOverMenu.Update(t);
			//DRAW CODE HERE
			window.clear();
			gameOverMenu.Draw(window);
			window.display();
			break;
		}

	} //loop back for next frame
	return EXIT_SUCCESS;
}
