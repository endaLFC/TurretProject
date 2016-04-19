#include "stdafx.h" 
#include <iostream>
#include "Pvector.h"
#include "Boid.h"

using namespace std;

#ifndef FLOCK_H_
#define FLOCK_H_

/*
Brief description of Flock Class:
// This file contains the class needed to create flock of boids. It utilizes
// the boids class and initializes boid flocks with parameters that can be
// specified. This class will be utilized in main.
*/

class Flock
{
private:

public:
	//Public Variables
	vector<Boid> flock;

	//Constructors
	Flock() {}

	//Accessor functions
	int getSize();
	Boid getBoid(int i);
	//Mutator Functions
	void addBoid(Boid b);
	void flocking(sf::Vector2f playerPos, sf::Vector2f asteroidPos);
	void swarming(sf::Vector2f playerPos);
	void ClearAll();

};

#endif