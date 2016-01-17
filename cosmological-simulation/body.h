#ifndef Body_H // Will only be true the once!
#define Body_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

class Body
{
 public:
	string name;
	double mass;
	double xPosition, yPosition, zPosition;
	double xVelocity, yVelocity, zVelocity;
	//double xTrack[100000], yTrack[100000];



	Body();

	~Body();

	Body(string tempName, 
		 double tempMass,
		 double tempxPosition, 
		 double tempyPosition, 
		 double tempzPosition, 
		 double tempxVelocity, 
		 double tempyVelocity, 
		 double tempzVelocity);

	vector<double> accelerationCalc(vector <Body> Body_Vector);
};

#endif