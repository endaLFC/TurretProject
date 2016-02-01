//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 

#include "Menu.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "ParticleSystem.h"
#include "Energy.h"
#include "Boid.h"
#include "Pvector.h"
#include "Flock.h"
#include "Factory.h"
#include "Obstacle.h"
#include "Powerup.h"
////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	sf::View view;
	view.reset(sf::FloatRect(0,0, 1100,800));

	float boidsSize = 10;
	//string action = "flock";
	Flock flock;
	Flock swarm;
	Flock factory;
	Flock preds;

	vector<sf::CircleShape> shapes;
	vector<sf::CircleShape> shapes2;
	vector<Factory*> factories;

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(1100, 800, 32), "SFML First Program");
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
	

	playTexture.loadFromFile("space3.jpg");
	radarTexture.loadFromFile("space2.jpg");
	radarBorderTexture.loadFromFile("radarBorder2.png");
	scoreHUDTexture.loadFromFile("hud2.png");
	gameOverTexture.loadFromFile("GameOver.jpg");
	optionsTexture.loadFromFile("OptionsBackground.jpg");

	BulletManager::GetInstance()->Init();
	EnemyManager::GetInstance()->Init();
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
	radarBorderSpr.setPosition(10,550);

	Obstacle obstacle;
	Obstacle obstacle2;

	Powerup mushroomSmall;
	Powerup mushroomColour;

	obstacle.Initialise(sf::Vector2f(600, 1600));
	obstacle2.Initialise(sf::Vector2f(1700, 800));

	mushroomSmall.Initialise(sf::Vector2f(200, 200), 0);
	mushroomColour.Initialise(sf::Vector2f(2000, 1500), 1);

	//creating flock boids
	for (int i = 0; i < 50; i++) //Number of boids is hardcoded for testing pusposes.
	{
		//Boid b(rand() % window_width, rand() % window_height); //Starts the boid with a random position in the window.
		Boid b(800 / 3, 600 / 3, 0); //Starts all boids in the center of the screen
		sf::CircleShape shape(10, 3); //Shape with a radius of 10 and 3 points (Making it a triangle)

		//Changing the Visual Properties of the shape
		//shape.setPosition(b.location.x, b.location.y); //Sets position of shape to random location that boid was set to.
		shape.setPosition(800, 600); //Testing purposes, starts all shapes in the center of screen.
		shape.setOutlineColor(sf::Color(0, 255, 0));
		shape.setFillColor(sf::Color::Black);
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(1);
		shape.setRadius(boidsSize);

		//Adding the boid to the flock and adding the shapes to the vector<sf::CircleShape>
		flock.addBoid(b);
		shapes.push_back(shape);
	}

	//creating swarm boids
	for (int i = 0; i < 50; i++) //Number of boids is hardcoded for testing pusposes.
	{
		//Boid b(rand() % window_width, rand() % window_height); //Starts the boid with a random position in the window.
		Boid b(800 * 2, 600, 1); //Starts all boids in the center of the screen
		sf::CircleShape shape(10, 3); //Shape with a radius of 10 and 3 points (Making it a triangle)

		//Changing the Visual Properties of the shape
		//shape.setPosition(b.location.x, b.location.y); //Sets position of shape to random location that boid was set to.
		shape.setPosition(800, 600); //Testing purposes, starts all shapes in the center of screen.
		shape.setOutlineColor(sf::Color(255, 0, 0));
		shape.setFillColor(sf::Color::Black);
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(1);
		shape.setRadius(boidsSize);

		//Adding the boid to the flock and adding the shapes to the vector<sf::CircleShape>
		swarm.addBoid(b);
		shapes2.push_back(shape);
	}


	for (int i = 0; i < 5; i++) //Number of boids is hardcoded for testing pusposes.
	{
		//Boid b(rand() % window_width, rand() % window_height); //Starts the boid with a random position in the window.
		Boid b(800, 1000, 2); //Starts all boids in the center of the screen
		Factory *f = new Factory;
		f->Initialise();
		f->SetPosition(sf::Vector2f(800,600));
		factory.addBoid(b);
		factories.push_back(f);
	}


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

			menu.Update(t);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				menu.MoveUp();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
			/*
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				action = "swarm";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				action = "flock";
			}
			*/

			//check for mouse click, draws and adds boid to flock if so.
			//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			//{
			//	//Gets mouse coordinates, sets that as the location of the boid and the shape
			//	sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
			//	Boid b(mouseCoords.x, mouseCoords.y, true);
			//	sf::CircleShape shape(10, 3);

			//	//Changing visual properties of newly created boid
			//	shape.setPosition(mouseCoords.x, mouseCoords.y);
			//	shape.setOutlineColor(sf::Color(255, 0, 0));
			//	shape.setFillColor(sf::Color(255, 0, 0));
			//	shape.setOutlineColor(sf::Color::White);
			//	shape.setOutlineThickness(1);
			//	shape.setRadius(boidsSize);

			//	//Adds newly created boid and shape to their respective data structure
			//	flock.addBoid(b);
			//	shapes.push_back(shape);

			//	//New Shape is drawn
			//	window.draw(shapes[shapes.size() - 1]);
			//}

			p1.Update(t);
			BulletManager::GetInstance()->Update(t);
			EnemyManager::GetInstance()->Update(t, p1.GetPos());
			ParticleSystem::GetInstance()->Update(t);
			Energy::GetInstance()->Update(t);

			if (BulletManager::GetInstance()->IsColliding())
			{
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && counter == 1) //&& counter == 1
			{
				EnemyManager::GetInstance()->CreateEnemy(sf::Vector2f(0,0));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			window.clear();
			//window.setView(main);

			//view.setCenter(p1.GetPos());
			//view.setCenter(p1.GetPos());

			if (p1.GetPos().x >= 550 && p1.GetPos().x <= 1850)
				view.setCenter(p1.GetPos().x, view.getCenter().y);
			else if (p1.GetPos().x < 550)
				view.setCenter(550, view.getCenter().y);
			else if (p1.GetPos().x > 1850)
				view.setCenter(1850, view.getCenter().y);

			if (p1.GetPos().y >= 400 && p1.GetPos().y <= 1400)
				view.setCenter(view.getCenter().x, p1.GetPos().y);
			else if (p1.GetPos().y < 400)
				view.setCenter(view.getCenter().x, 400);
			else if (p1.GetPos().y > 1400)
				view.setCenter(view.getCenter().x, 1400);

			window.setView(view);			
			window.draw(background);

			for (int i = 0; i < shapes.size(); i++)
			{
				window.draw(shapes[i]);
				//Matches up the location of the shape to the boid
				shapes[i].setPosition(flock.getBoid(i).location.x, flock.getBoid(i).location.y);

				// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
				float theta;
				theta = flock.getBoid(i).angle(flock.getBoid(i).velocity);
				shapes[i].setRotation(theta);

				if (BulletManager::GetInstance()->IsColliding2(shapes[i].getPosition(), shapes[i].getRadius(), true))
				{
					shapes[i].setFillColor(sf::Color::Red);
				}
			}

			//drawing swarm boids
			for (int i = 0; i < shapes2.size(); i++)
			{
				window.draw(shapes2[i]);
				//Matches up the location of the shape to the boid
				shapes2[i].setPosition(swarm.getBoid(i).location.x, swarm.getBoid(i).location.y);
				// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
				float theta;
				theta = swarm.getBoid(i).angle(swarm.getBoid(i).velocity);
				shapes2[i].setRotation(theta);

				if (BulletManager::GetInstance()->IsColliding2(shapes2[i].getPosition(), shapes2[i].getRadius(), true))
				{
					shapes2[i].setFillColor(sf::Color::Red);
				}
			}

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

				if (BulletManager::GetInstance()->IsColliding2(factories[i]->GetPosition(), factories[i]->GetRadius(), factories[i]->GetAlive()) && factories[i]->GetAlive() == true)
				{
					factories[i]->IsColliding();
				}
			}


			if (obstacle.IsColliding(p1.GetPos(), p1.GetRadius()))
			{
				gameMode = GAMEOVER;
			}
			else if (obstacle2.IsColliding(p1.GetPos(), p1.GetRadius()))
			{
				gameMode = GAMEOVER;
			}

			if (mushroomSmall.IsColliding(p1.GetPos(), p1.GetRadius()) && mushroomSmall.GetType() == 0)
			{
				p1.SetShrink(true);
			}

			if (mushroomColour.IsColliding(p1.GetPos(), p1.GetRadius()) && mushroomColour.GetType() == 1)
			{
				p1.SetSpeed(150, 600);		//upgrading turn speed and max speed
			}

			obstacle.Rotate(t);
			obstacle.Draw(window);
			obstacle2.Rotate(t);
			obstacle2.Draw(window);

			mushroomSmall.Draw(window);
			mushroomColour.Draw(window);

			//Applies the three rules to each boid in the flock and changes them accordingly.
			//if (action == "flock")
			flock.flocking(p1.GetPos(), obstacle.GetPosition());
			flock.flocking(p1.GetPos(), obstacle2.GetPosition());
			//else
			swarm.swarming(p1.GetPos());
			

			factory.flocking(p1.GetPos(), obstacle.GetPosition());
			factory.flocking(p1.GetPos(), obstacle2.GetPosition());



			
			EnemyManager::GetInstance()->Draw(window);
			BulletManager::GetInstance()->Draw(window);
			ParticleSystem::GetInstance()->Draw(window);
			//window.draw(scoreHUDSprite);
			p1.Draw(window);
			//Energy::GetInstance()->Draw(window);


			window.setView(miniMap);
			window.draw(radarBackground);
			p1.SetSpriteScale(3);
			obstacle.SetSpriteScale(2);
			obstacle.Draw(window);
			obstacle.SetSpriteScale(1);
			obstacle2.SetSpriteScale(2);
			obstacle2.Draw(window);
			obstacle2.SetSpriteScale(1);
			mushroomSmall.SetSpriteScale(3);
			mushroomSmall.Draw(window);
			mushroomSmall.SetSpriteScale(1);
			mushroomColour.SetSpriteScale(3);
			mushroomColour.Draw(window);
			mushroomColour.SetSpriteScale(1);
			p1.Draw(window);
			p1.SetSpriteScale(1);
			for (int i = 0; i < shapes.size(); i++)
			{
				shapes[i].setScale(5,5); 
				window.draw(shapes[i]);
				shapes[i].setScale(1, 1);
			}
			for (int i = 0; i < shapes2.size(); i++)
			{
				shapes2[i].setScale(5, 5);
				window.draw(shapes2[i]);
				shapes2[i].setScale(1, 1);
			}
			for (int i = 0; i < factories.size(); i++)
			{
				factories[i]->SetScale(3);
				factories[i]->Draw(window);
				factories[i]->SetScale(1);
			}
			EnemyManager::GetInstance()->Draw(window);
			BulletManager::GetInstance()->Draw(window);
			ParticleSystem::GetInstance()->Draw(window);

			window.setView(scoreHUD);
			window.draw(scoreHUDSprite);
			p1.DrawScore(window);
			Energy::GetInstance()->Draw(window);

			window.setView(main); //setting view back to main
			window.draw(radarBorderSpr);
			p1.DrawLock(window);

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