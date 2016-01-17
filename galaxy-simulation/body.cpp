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
	m_name = "Ghost";
	m_mass = 0;
	m_xPosition = m_yPosition = m_xVelocity = m_yVelocity = 0;
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
	m_name = tempName;
	m_mass = tempMass;

	m_xPosition = tempxPosition;
	m_yPosition = tempyPosition;
	m_zPosition = tempzPosition;

	m_xVelocity = tempxVelocity;
	m_yVelocity = tempyVelocity;
	m_zVelocity = tempzVelocity;

	m_isValid = true;

	cout << m_name << " created." << endl;
}

vector<double> Body::accelerationCalc(vector<Body>& Body_Vector)
{
	const double G(6.67384*pow(10,-11));
	const double Solar_Radius(6.955*pow(10,8));

	double accX(0), accY(0), accZ(0);

	vector <double> acceleration;
	vector <Body>::iterator it;
	for (it = Body_Vector.begin(); it != Body_Vector.end(); ++it)
	{
		if (this->name() == it->name() || it->isValid() == false) continue;
		//F = G*M*m*r_vector/r^3
		//a = G*M*r_vector/r^3
		double rx = xPosition() - it->xPosition();
		double ry = yPosition() - it->yPosition();
		double rz = zPosition() - it->zPosition();
		double rCubed = pow(rx*rx + ry*ry + rz*rz + 3*pow(10,8)*pow(10,7), 1.5);

		if(rCubed < pow(this->radius() + it->radius(), 3))
		{
			//combine them
			it->set_isValid(false);
		}

		double magAcc = -G*it->mass()/rCubed;

		accX = accX + magAcc*rx;
		accY = accY + magAcc*ry;
		accZ = accZ + magAcc*rz;
	}

	acceleration.push_back(accX);
	acceleration.push_back(accY);
	acceleration.push_back(accZ);

	return acceleration;
};

const double Body::xPosition() const
{
	return m_xPosition;
};

const double Body::yPosition() const
{
	return m_yPosition;
};

const double Body::zPosition() const
{
	return m_zPosition;
};

const double Body::xVelocity() const
{
	return m_xVelocity;
};

const double Body::yVelocity() const
{
	return m_yVelocity;
};

const double Body::zVelocity() const
{
	return m_zVelocity;
};

const string Body::name() const
{
	return m_name;
};

const double Body::mass() const
{
	return m_mass;
};

void Body::set_xPosition(const double& new_xPosition)
{
	m_xPosition = new_xPosition;
	return;
};

void Body::set_yPosition(const double& new_yPosition)
{
	m_yPosition = new_yPosition;
	return;
};

void Body::set_zPosition(const double& new_zPosition)
{
	m_zPosition = new_zPosition;
	return;
};

void Body::set_xVelocity(const double& new_xVelocity)
{
	m_xVelocity = new_xVelocity;
	return;
};

void Body::set_yVelocity(const double& new_yVelocity)
{
	m_yVelocity = new_yVelocity;
	return;
};

void Body::set_zVelocity(const double& new_zVelocity)
{
	m_zVelocity = new_zVelocity;
	return;
};

void Body::set_mass(const double& new_mass)
{
	m_mass = new_mass;
	return;
};

void Body::set_Radius(const double& new_Radius)
{
	m_radius = new_Radius;
	return;
};

const double Body::radius() const
{
	return m_radius;
};

const bool Body::isValid() const
{
	return m_isValid;
};

void Body::set_isValid(const bool& new_isValid)
{
	m_isValid = new_isValid;
	return;
};