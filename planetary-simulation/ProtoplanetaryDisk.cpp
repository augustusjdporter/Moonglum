//cc SolarSystem.cpp -o SolarSystem -L/usr/lib/ -lcpgplot -lpgplot -lm
#include "cpgplot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
using namespace std;

class Planet
{
 public:
	string name;
	float mass;
	float xPosition, yPosition, zPosition;
	float xVelocity, yVelocity, zVelocity;
	float xTrack[100000], yTrack[100000];

	int pgplotIcon, pgplotColour;

	Planet()
	{
		name = "Ghost";
		mass = 0;
		xPosition = yPosition = xVelocity = yVelocity = 0;
	}

	Planet(string tempName, float tempMass, float tempxPosition, float tempyPosition, float tempzPosition, float tempxVelocity, float tempyVelocity, float tempzVelocity)
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

	vector<float> accelerationCalc(vector <Planet> Planets)
		{
			const float G(6.67384*pow(10,-11));
			float accX(0), accY(0), accZ(0);
			vector <float> acceleration;
			for (int i = 0; i< Planets.size(); i++)
			{

				if (name == Planets.at(i).name) continue;

				//F = G*M*m*r_vector/r^3
				//a = G*M*r_vector/r^3

				float rx = xPosition - Planets.at(i).xPosition;
				float ry = yPosition - Planets.at(i).yPosition;
				float rz = zPosition - Planets.at(i).zPosition;
				float rCubed = pow(rx*rx + ry*ry + rz*rz, 1.5);

				float magAcc = -G*Planets.at(i).mass/rCubed;
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
	const float kPc(1.4960*pow(10, 11));
	const float timestep(86400);//year in seconds
	int j(0), k(0), count(0);
	std::default_random_engine generator;
  	std::normal_distribution<float> distribution(0.,3.0*kPc);
  	std::normal_distribution<float> distributionz(0.,1.0*kPc);
  	std::normal_distribution<float> distributionxvel(3.3*pow(10,3),1*pow(10,4));
  	std::normal_distribution<float> distributionyvel(3.3*pow(10,3),1*pow(10,4));


	if(cpgbeg(0, " ", 1, 1) != 1)
    return EXIT_FAILURE;

	vector <Planet> Planets;
	//Planets.push_back(Planet("Sun", 1.9891*pow(10, 32), 0, 0, 0, 0, 0, 0));
	for (int i =0; i<100; i++){
		float numberx = distribution(generator);
		float numbery = distribution(generator);
		float numberz = distributionz(generator);
		float numberxvel = distributionxvel(generator);
		float numberyvel = distributionyvel(generator);
		stringstream combiner;
		combiner << "Star" << i;
		string name;
		combiner >> name;
	Planets.push_back(Planet(name, 1.898*pow(10, 24), numberx, numbery, numberz, numberxvel, numberyvel, 0));
	}
	//Planets.push_back(Planet("Sun", 1.9891*pow(10, 30), 0, 0, 0, 0, 0, 0));




	const int thisthing(1);

  while (thisthing == 1)
  {

	for (int i = 0; i< Planets.size(); i++)
  	{
	vector<float> acceleration = Planets.at(i).accelerationCalc(Planets);

	Planets.at(i).xPosition = Planets.at(i).xPosition + Planets.at(i).xVelocity*timestep;
	Planets.at(i).yPosition = Planets.at(i).yPosition + Planets.at(i).yVelocity*timestep;
	Planets.at(i).zPosition = Planets.at(i).zPosition + Planets.at(i).zVelocity*timestep;
	if (i ==1){
	//cout << Planets.at(i).name << " position: " << Planets.at(i).xPosition/kPc << " " << Planets.at(i).yPosition/kPc << " " << Planets.at(i).zPosition/kPc << endl;
	}
	Planets.at(i).xVelocity = Planets.at(i).xVelocity + acceleration.at(0)*timestep;
	Planets.at(i).yVelocity = Planets.at(i).yVelocity + acceleration.at(1)*timestep;
	Planets.at(i).zVelocity = Planets.at(i).zVelocity + acceleration.at(2)*timestep;
	}



  	for (int i = 0; i< Planets.size(); i++)
  	{

  	float xs[] = {Planets.at(i).xPosition/kPc};//pgpt needs to be array
  	float ys[] = {Planets.at(i).yPosition/kPc};

		Planets.at(i).xTrack[j] = Planets.at(i).xPosition/kPc;
		Planets.at(i).yTrack[j] = Planets.at(i).yPosition/kPc;

	if (k == j){
		if (count == 0)
		{
		cpgenv(Planets.at(0).xPosition/kPc-10., Planets.at(0).xPosition/kPc+10.0, Planets.at(0).yPosition/kPc-10., Planets.at(0).yPosition/kPc+10.0, 0, 1);
    	cpglab("(x)", "(y)", " ");
    	count = count + 1;
		}
    cpgpt(1, xs, ys, 27);
    cpgline(j+1, Planets.at(i).xTrack, Planets.at(i).yTrack);
    if (i == Planets.size()-1){k=k+3;}
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