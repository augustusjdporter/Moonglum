//cc SolarSystem.cpp -o SolarSystem -L/usr/lib/ -lcpgplot -lpgplot -lm
#include "cpgplot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Planet
{
 public:
	string name;
	double mass;
	double xPosition, yPosition, zPosition;
	double xVelocity, yVelocity, zVelocity;
	float xTrack[100000], yTrack[100000];

	int pgplotIcon, pgplotColour;

	Planet()
	{
		name = "Ghost";
		mass = 0;
		xPosition = yPosition = xVelocity = yVelocity = 0;
	}

	Planet(string tempName, double tempMass, double tempxPosition, double tempyPosition, double tempzPosition, double tempxVelocity, double tempyVelocity, double tempzVelocity)
	{
		name = tempName;
		mass = tempMass;

		xPosition = tempxPosition;
		yPosition = tempyPosition;
		zPosition = tempzPosition;

		xVelocity = tempxVelocity;
		yVelocity = tempyVelocity;
		zVelocity = tempzVelocity;

		cout << name << " created." << endl;
	}

	vector<double> accelerationCalc(vector <Planet> Planets)
		{
			const double G(6.67384*pow(10,-11));
			double accX(0), accY(0), accZ(0);
			vector <double> acceleration;
			for (int i = 0; i< Planets.size(); i++)
			{

				if (name == Planets.at(i).name) continue;

				//F = G*M*m*r_vector/r^3
				//a = G*M*r_vector/r^3

				double rx = xPosition - Planets.at(i).xPosition;
				double ry = yPosition - Planets.at(i).yPosition;
				double rz = zPosition - Planets.at(i).zPosition;
				double rCubed = pow(rx*rx + ry*ry + rz*rz, 1.5);

				double magAcc = -G*Planets.at(i).mass/rCubed;
				accX = accX + magAcc*rx;
				accY = accY + magAcc*ry;
				accZ = accZ + magAcc*rz;

			}

			acceleration.push_back(accX);
			acceleration.push_back(accY);
			acceleration.push_back(accZ);
			return acceleration;
		}
};

int main()
{
	const double AU(1.4960*pow(10, 11));
	const double timestep(5400);//day/16 in seconds
	int j(0), k(0), count(0);

	if(cpgbeg(0, " ", 1, 1) != 1)
    return EXIT_FAILURE;

	vector <Planet> Planets;
	Planets.push_back(Planet("Sun", 1.9891*pow(10, 30), 0.1, 0, 0, 0, 3.3*pow(10,2), 0));
	Planets.push_back(Planet("Sun", 1.9891*pow(10, 30), -0.1, 0, 0, 0, -3.3*pow(10,2), 0));
	//Planets.push_back(Planet("Sun", 1.9891*pow(10, 30), 0, 0, 0, 0, 0, 0));
	//Planets.push_back(Planet("Sun", 1.9891*pow(10, 30), 0, 0, 0, 0, 0, 0));
	Planets.push_back(Planet("Earth", 5.972*pow(10, 24), 1*AU, 0, 0, 0, 3.3*pow(10,4) , 0));
	Planets.push_back(Planet("Jupiter", 1.898*pow(10, 24), 5.2*AU, 0, 0, 0, 47.051*pow(10,6)/3600 , 0));


cpgenv(Planets.at(0).xPosition/AU-10., Planets.at(0).xPosition/AU+10.0, Planets.at(0).yPosition/AU-10., Planets.at(0).yPosition/AU+10.0, 0, 1);
    	cpglab("(x)", "(y)", " ");

	const int thisthing(1);

  while (thisthing == 1)
  {

	for (int i = 0; i< Planets.size(); i++)
  	{
	vector<double> acceleration = Planets.at(i).accelerationCalc(Planets);

	Planets.at(i).xPosition = Planets.at(i).xPosition + Planets.at(i).xVelocity*timestep;
	Planets.at(i).yPosition = Planets.at(i).yPosition + Planets.at(i).yVelocity*timestep;
	Planets.at(i).zPosition = Planets.at(i).zPosition + Planets.at(i).zVelocity*timestep;
	//cout << Planets.at(i).name << " position: " << Planets.at(i).xPosition/AU << " " << Planets.at(i).yPosition/AU << " " << Planets.at(i).zPosition/AU << endl;

	Planets.at(i).xVelocity = Planets.at(i).xVelocity + acceleration.at(0)*timestep;
	Planets.at(i).yVelocity = Planets.at(i).yVelocity + acceleration.at(1)*timestep;
	Planets.at(i).zVelocity = Planets.at(i).zVelocity + acceleration.at(2)*timestep;
	}



  	for (int i = 0; i< Planets.size(); i++)
  	{

  	float xs[] = {Planets.at(i).xPosition/AU};//pgpt needs to be array
  	float ys[] = {Planets.at(i).yPosition/AU};

		Planets.at(i).xTrack[j] = Planets.at(i).xPosition/AU;
		Planets.at(i).yTrack[j] = Planets.at(i).yPosition/AU;

	if (k == j){
		if (count == 0)
		{
		
    	count = count + 1;
		}
    cpgpt(1, xs, ys, 8);
    cpgline(j+1, Planets.at(i).xTrack, Planets.at(i).yTrack);
    if (i == Planets.size()-1){k=k+128;}
	}

  }
  count = 0;
  j=j+1;
  if (j==99999){j=0; k = 0;}
}
  cpgend();
  return EXIT_SUCCESS;

  	// Free memory
	//delete[] xPositions;
	//delete[] yPositions;
	return 0;
}