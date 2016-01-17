//cc SolarSystem.cpp -o SolarSystem -L/usr/lib/ -lcpgplot -lpgplot -lm
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "../body.h"
#include "../system.h"

using namespace std;

int main()
{
	const double AU(1.4960*pow(10, 11));
	const double timestep(5400);//day/16 in seconds
	int j(0), k(0), count(0);
	System solarSystem;

	vector <Body> Planets;
	solarSystem.addBody(new Body("Sun", 1.9891*pow(10, 30), 0.1, 0, 0, 0, 3.3*pow(10,2), 0));
	solarSystem.addBody(new Body("Sun", 1.9891*pow(10, 30), -0.1, 0, 0, 0, -3.3*pow(10,2), 0));
	solarSystem.addBody(new Body("Earth", 5.972*pow(10, 24), 1*AU, 0, 0, 0, 3.3*pow(10,4) , 0));
	solarSystem.addBody(new Body("Jupiter", 1.898*pow(10, 24), 5.2*AU, 0, 0, 0, 47.051*pow(10,6)/3600 , 0));


//cpgenv(Planets.at(0).xPosition/AU-10., Planets.at(0).xPosition/AU+10.0, Planets.at(0).yPosition/AU-10., Planets.at(0).yPosition/AU+10.0, 0, 1);
    	//cpglab("(x)", "(y)", " ");

	//const int thisthing(1);
int thisthing = 1;
  	while (thisthing == 1)
  	{
  		cout << "1";
		solarSystem.update(timestep);



  	/*for (int i = 0; i< Planets.size(); i++)
  	{

  	float xs[] = {Planets.at(i).xPosition/AU};//pgpt needs to be array
  	float ys[] = {Planets.at(i).yPosition/AU};

		Planets.at(i).xTrack[j] = Planets.at(i).xPosition/AU;
		Planets.at(i).yTrack[j] = Planets.at(i).yPosition/AU;
  }*/
	}


  	// Free memory
	//delete[] xPositions;
	//delete[] yPositions;
	return 0;
}