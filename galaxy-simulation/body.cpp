#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#include "body.h"

using namespace std;

Body::Body()
{
	name = "Ghost";
	mass = 0;
	xPosition = yPosition = xVelocity = yVelocity = 0;
}

Body::~Body(){}

Body::Body(string tempName, 
	 double tempMass,
	 double tempxPosition, 
	 double tempyPosition, 
	 double tempzPosition, 
	 double tempxVelocity, 
	 double tempyVelocity, 
	 double tempzVelocity)
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

vector<double> Body::accelerationCalc(vector <Body> Body_Vector)
{
	const double G(6.67384*pow(10,-11));
	const double Solar_Radius(6.955*pow(10,8));

	double accX(0), accY(0), accZ(0);

	vector <double> acceleration;
	vector <Body>::iterator it;
	for (it = Body_Vector.begin(); it != Body_Vector.end(); ++it)
	{
		if (name == it->name) continue;
		//F = G*M*m*r_vector/r^3
		//a = G*M*r_vector/r^3
		double rx = xPosition - it->xPosition;
		double ry = yPosition - it->yPosition;
		double rz = zPosition - it->zPosition;
		double rCubed = pow(rx*rx + ry*ry + rz*rz + 3*pow(10,8)*pow(10,7), 1.5);

		double magAcc = -G*it->mass/rCubed;

		accX = accX + magAcc*rx;
		accY = accY + magAcc*ry;
		accZ = accZ + magAcc*rz;
	}

	acceleration.push_back(accX);
	acceleration.push_back(accY);
	acceleration.push_back(accZ);

	return acceleration;
}