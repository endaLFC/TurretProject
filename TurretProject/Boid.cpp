// This file defines the boid class. This includes the attributes found in
// boids -- speed, location on the board, acceleration, etc.
#include "stdafx.h" 
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "SFML/Graphics.hpp"
#include "Boid.h"

// Global Variables for borders()
// desktopTemp gets screen resolution of PC running the program
sf::VideoMode desktopTemp = sf::VideoMode::getDesktopMode(); 
const int window_height = 1800;
const int window_width = 2400;

#define w_height window_height
#define w_width window_width
#define PI 3.141592635

using namespace std;

// =============================================== //
// ======== Boid Functions from Boid.h =========== //
// =============================================== //

// Adds force Pvector to current force Pvector
void Boid::applyForce(Pvector force)
{
	acceleration.addVector(force);
}



// Function that checks and modifies the distance
// of a boid if it breaks the law of separation.
Pvector Boid::Separation(vector<Boid> boids, sf::Vector2f playerPos)
{
	// If the boid we're looking at is a predator, do not run the separation
	// algorithm
	
	// Distance of field of vision for separation between boids
	float desiredseparation = 60;
	float desiredseparation2 = 100;
	float desiredseparation3 = 300;
	float desiredseparation4 = 70;
	float desiredseparation5 = 150;

	Pvector steer(0, 0);
	int count = 0;
	// For every boid in the system, check if it's too close
	for (int i = 0; i < boids.size(); i++)
	{
		// Calculate distance from current boid to boid we're looking at
		float d = location.distance(boids[i].location);
		Pvector p(playerPos.x, playerPos.y);
		float d2 = location.distance(p); //distance from player

		//If the boids are too close to the player retreat
		if ((d2 > 0) && (d2 < desiredseparation2) && boidType == FLOCK)
		{
			Pvector boid2Player(0, 0);
			boid2Player = boid2Player.subTwoVector(location, p);
			boid2Player.normalize();
			boid2Player.mulScalar(d2);
			steer.addVector(boid2Player);
			count++;
		}

		//If the boids are too close to the player retreat
		if ((d2 > 0) && (d2 < desiredseparation3) && boidType == FACTORY)
		{
			Pvector boid2Player(0, 0);
			boid2Player = boid2Player.subTwoVector(location, p);
			boid2Player.normalize();
			boid2Player.mulScalar(d2);
			steer.addVector(boid2Player);
			count++;
		}

		// If this is a fellow boid and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation4) && boidType == FACTORY)
		{
			Pvector diff(0, 0);
			diff = diff.subTwoVector(location, boids[i].location);
			diff.normalize();
			diff.divScalar(d);      // Weight by distance
			steer.addVector(diff);
			count++;
		}

		// If this is a fellow boid and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation) && boidType == FLOCK)
		{
			Pvector diff(0,0);
			diff = diff.subTwoVector(location, boids[i].location); 
			diff.normalize();
			diff.divScalar(d);      // Weight by distance
			steer.addVector(diff);
			count++;
		}
		// If current boid is a predator and the boid we're looking at is also
		// a predator, then separate only slightly 
		if ((d > 0) && (d < desiredseparation) && predator == true && boids[i].predator == true)
		{
			Pvector pred2pred(0, 0);
			pred2pred = pred2pred.subTwoVector(location, boids[i].location);
			pred2pred.normalize();
			pred2pred.divScalar(d);
			steer.addVector(pred2pred);
			count++;
		} 

		// If current boid is not a predator, but the boid we're looking at is
		// a predator, then create a large separation Pvector
		else if ((d > 0) && (d < desiredseparation+70) && boids[i].predator == true)
		{
			Pvector pred(0, 0);
			pred = pred.subTwoVector(location, boids[i].location);
			pred.mulScalar(900);
			steer.addVector(pred);
			count++;
		}
	}
	/*
	Pvector p(playerPos.x, playerPos.y);
	float d2 = location.distance(p);
	if ((d2 > 0) && (d2 < desiredseparation))
	{
		Pvector boid2Player(0, 0);
		boid2Player = boid2Player.subTwoVector(location, p);
		boid2Player.normalize();
		boid2Player.divScalar(d2);
		steer.addVector(boid2Player);
		count++;
	}
	*/

	// Adds average difference of location to acceleration
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude() > 0) 
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}


Pvector Boid::AsteroidSeparation(vector<Boid> boids, sf::Vector2f asteroidPos)
{
	// If the boid we're looking at is a predator, do not run the separation
	// algorithm

	// Distance of field of vision for separation between boids
	float desiredseparation = 250;

	Pvector steer(0, 0);
	int count = 0;
	// For every boid in the system, check if it's too close
	for (int i = 0; i < boids.size(); i++)
	{
		//calc distance from asteroid to boid
		Pvector asteroid(asteroidPos.x, asteroidPos.y);
		float d = location.distance(asteroid); //distance from asteroid

		//If the boids are too close to the asteroid avoid it
		if ((d > 0) && (d < desiredseparation))
		{
			Pvector boid2Asteroid(0, 0);
			boid2Asteroid = boid2Asteroid.subTwoVector(location, asteroid);
			boid2Asteroid.normalize();
			boid2Asteroid.mulScalar(d);
			steer.addVector(boid2Asteroid);
			count++;
		}
	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude() > 0)
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}

// Alignment calculates the average velocity in the field of view and 
// manipulates the velocity of the Boid passed as parameter to adjust to that
// of nearby boids.
Pvector Boid::Alignment(vector<Boid> Boids)
{
	// If the boid we're looking at is a predator, do not run the alignment
	// algorithm
	//if (predator == true)
	//	return Pvector(0,0);
	float neighbordist = 140;
	float neighbordist2 = 140;

	Pvector sum(0, 0);	
	int count = 0;
	for (int i = 0; i < Boids.size(); i++)
	{
		float d = location.distance(Boids[i].location);
		if ((d > 0) && (d < neighbordist2) && boidType == FACTORY) // 0 < d < 50
		{
			sum.addVector(Boids[i].velocity);
			count++;
		}
		if ((d > 0) && (d < neighbordist) && boidType == FLOCK) // 0 < d < 50
		{
			sum.addVector(Boids[i].velocity);
			count++;
		}
	}
	// If there are boids close enough for alignment...
	if (count > 0)
	{
		sum.divScalar((float)count);// Divide sum by the number of close boids (average of velocity)
		sum.normalize();	   		// Turn sum into a unit vector, and
		sum.mulScalar(maxSpeed);    // Multiply by maxSpeed
		// Steer = Desired - Velocity
		Pvector steer; 
		steer = steer.subTwoVector(sum, velocity); //sum = desired(average)  
		steer.limit(maxForce);
		return steer;
	} else {
		Pvector temp(0, 0);
		return temp;
	}
}

// Cohesion finds the average location of nearby boids and manipulates the 
// steering force to move in that direction.
Pvector Boid::Cohesion(vector<Boid> Boids)
{
	// If the boid we're looking at is a predator, do not run the cohesion
	// algorithm
	//if (predator == true)
	//	return Pvector(0,0);

	float neighbordist = 50;

	float neighbordist2 = 140;

	Pvector sum(0, 0);	
	int count = 0;
	for (int i = 0; i < Boids.size(); i++)
	{
		float d = location.distance(Boids[i].location);
		if ((d > 0) && (d < neighbordist2) && boidType == FACTORY)
		{
			sum.addVector(Boids[i].location);
			count++;
		}

		if ((d > 0) && (d < neighbordist) && boidType == FLOCK)
		{
			sum.addVector(Boids[i].location);
			count++;
		}
	}
	if (count > 0)
	{
		sum.divScalar(count);
		return seek(sum);
	} else {
		Pvector temp(0,0);
		return temp;
	}
}

// Seek function limits the maxSpeed, finds necessary steering force and
// normalizes the vectors.
Pvector Boid::seek(Pvector v)
{
	Pvector desired;
	desired.subVector(v);  // A vector pointing from the location to the target
	// Normalize desired and scale to maximum speed
	desired.normalize();
	desired.mulScalar(maxSpeed);
	// Steering = Desired minus Velocity
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(maxForce);  // Limit to maximum steering force
	return acceleration;
}

//Update modifies velocity, location, and resets acceleration with values that
//are given by the three laws.
void Boid::update()
{
	//To make the slow down not as abrupt
	acceleration.mulScalar(.4);
	// Update velocity
	velocity.addVector(acceleration);
	// Limit speed
	velocity.limit(maxSpeed);
	location.addVector(velocity);
	// Reset accelertion to 0 each cycle
	acceleration.mulScalar(0);
}

//Run runs flock on the flock of boids for each boid.
//Which applies the three rules, modifies accordingly, updates data, checks is data is
//out of range, fixes that for SFML, and renders it on the window.
void Boid::run(vector <Boid> v, sf::Vector2f playerPos, sf::Vector2f asteroidPos)
{
	flock(v, playerPos);
	AvoidAsteroids(v, asteroidPos);
	update();
	borders();
}

//Applies all three laws for the flock of boids and modifies to keep them from
//breaking the laws.
void Boid::flock(vector<Boid> v, sf::Vector2f playerPos)
{
	Pvector sep = Separation(v, playerPos);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep.mulScalar(1.5);
	ali.mulScalar(1.0); // Might need to alter weights for different characteristics
	coh.mulScalar(1.0);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

void Boid::AvoidAsteroids(vector<Boid> v, sf::Vector2f asteroidPos)
{
	Pvector sep = AsteroidSeparation(v, asteroidPos);
	// Arbitrarily weight these forces
	sep.mulScalar(1.5);
	// Add the force vectors to acceleration
	applyForce(sep);
}

// Checks if boids go out of the window and if so, wraps them around to the other side.
void Boid::borders()
{
	if (location.x < 0) location.x += w_width; 
	if (location.y < 0) location.y += w_height;
	if (location.x > w_width) location.x -= w_width;
	if (location.y > w_height) location.y -= w_height;
}

// Calculates the angle for the velocity of a boid which allows the visual 
// image to rotate in the direction that it is going in.
float Boid::angle(Pvector v)
{
	// From the definition of the dot product
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}

void Boid::swarm(vector <Boid> v, sf::Vector2f playerPos)
{
	Pvector	R;
	Pvector sum(0, 0);

	int count = 0;

	for (int i = 0; i < v.size(); i ++)		//cycling through every boid 
	{
		tuple<bool, Pvector> LJValue = CalcLJ(v[i], playerPos);
		if (std::get<0>(LJValue))
		{
			sum.addVector(std::get<1>(LJValue));
			count++;
		}
	}

	if (count > 0)
	sum.divScalar(count);

	applyForce(sum);
	update();
	borders();
}

tuple<bool, Pvector> Boid::CalcLJ(Boid b, sf::Vector2f playerPos)
{
	Pvector	R;
	Pvector p(playerPos.x, playerPos.y);


	float neighbordist = 500;
	float neighbordist2 = 200;
	float A = 100;
	float B = 5000;
	float N = 1;
	float M = 2;

	float d = location.distance(b.location);
	float d2 = location.distance(p);

	if ((d2 > 0) && (d2 < neighbordist2))
	{
		R = location;
		R.subVector(p);

		float D = R.magnitude();
		float U = -A / pow(D, N) + B / pow(D, M);
		R.normalize();

		R.mulScalar(U);
		return tuple<bool, Pvector>(true, R);
	}
	else if ((d > 0) && (d < neighbordist)) // 0 < d < 500
	{
		R = location;
		R.subVector(b.location);

		float D = R.magnitude();
		float U = -A / pow(D, N) + B / pow(D, M);
		R.normalize();

		R.mulScalar(U);
		return tuple<bool, Pvector>(true, R);
	}
	else
		return tuple<bool, Pvector>(false, R);
}