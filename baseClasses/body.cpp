#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "body.h"

using namespace std;

static int bodyCount(0);

Body::Body()
{
	m_ID = bodyCount;
	bodyCount++;
	m_name = "Ghost";
	m_mass = 0;
	m_xPosition = m_yPosition = m_xVelocity = m_yVelocity = 0;
};

Body::Body(const Body& bodyToCopy)
{
	m_ID = bodyToCopy.ID();

	m_name = bodyToCopy.name();
	m_mass = bodyToCopy.mass();

	m_xPosition = bodyToCopy.xPosition();
	m_yPosition = bodyToCopy.yPosition();
	m_zPosition = bodyToCopy.zPosition();

	m_xVelocity = bodyToCopy.xVelocity();
	m_yVelocity = bodyToCopy.yVelocity();
	m_zVelocity = bodyToCopy.zVelocity();

	m_isValid = bodyToCopy.isValid();

	m_radius = bodyToCopy.radius();
};

Body::~Body()
{
	if (m_trajectory != NULL)
	{
		if(m_trajectory->is_open() == true)
		{
			m_trajectory->close();
			delete m_trajectory;
			m_trajectory = NULL;
		}
	}
};

Body::Body(string tempName, 
	 double tempMass,
	 double tempxPosition, 
	 double tempyPosition, 
	 double tempzPosition, 
	 double tempxVelocity, 
	 double tempyVelocity, 
	 double tempzVelocity,
	 double tempRadius,
	 bool	tempLogTrajectory)
{
	m_ID = bodyCount;
	bodyCount++;
	m_trajectory = NULL;

	m_name = tempName;
	m_mass = tempMass;

	m_xPosition = tempxPosition;
	m_yPosition = tempyPosition;
	m_zPosition = tempzPosition;

	m_xVelocity = tempxVelocity;
	m_yVelocity = tempyVelocity;
	m_zVelocity = tempzVelocity;

	m_isValid = true;

	m_radius = tempRadius;

	m_logTrajectory = tempLogTrajectory;

	//m_relaxation = 0.05*3.0857*pow(10, 12);
	m_relaxation = 0.0;
};

const int Body::ID() const
{
	return m_ID;
}

vector<double> Body::accelerationCalc(vector<Body*>* Body_Vector)
{
	double accX(0), accY(0), accZ(0);

	vector <double> acceleration;
	vector <Body*>::iterator it;
	for (it = Body_Vector->begin(); it != Body_Vector->end(); ++it)
	{
		if (ID() == (*it)->ID() || (*it)->isValid() == false) continue; //check it is same body, and that other body is valid
		//F = G*M*m*r_vector/r^3
		//a = G*M*r_vector/r^3
		double rx = xPosition() - (*it)->xPosition();
		double ry = yPosition() - (*it)->yPosition();
		double rz = zPosition() - (*it)->zPosition();
		double rCubed = pow(rx*rx + ry*ry + rz*rz + relaxation(), 1.5);

		//when bodies touch, they stick. Conserve linear momentum
		if(rCubed <= pow(radius() + (*it)->radius(), 3))
		{
			
			//combine them
			(*it)->set_isValid(false);
			double new_mass = mass() + (*it)->mass();

			//place "this" body in the center of mass (COM = (m1x1 +m2x2)/(m1+m2))
			double xCOM = (mass()*xPosition() + (*it)->mass()*(*it)->xPosition()) / new_mass;
			double yCOM = (mass()*yPosition() + (*it)->mass()*(*it)->yPosition()) / new_mass;
			double zCOM = (mass()*zPosition() + (*it)->mass()*(*it)->zPosition()) / new_mass;

			//conserve momentum. NewVel = Mom/new mass
			double new_xVelocity = (mass()*xVelocity() + (*it)->mass()*(*it)->xVelocity()) / new_mass;
			double new_yVelocity = (mass()*yVelocity() + (*it)->mass()*(*it)->yVelocity()) / new_mass;
			double new_zVelocity = (mass()*zVelocity() + (*it)->mass()*(*it)->zVelocity()) / new_mass;

			//Set new velocity, position, and mass to "this" body
			set_xVelocity(new_xVelocity);
			set_yVelocity(new_yVelocity);
			set_zVelocity(new_zVelocity);

			set_xPosition(xCOM);
			set_yPosition(yCOM);
			set_zPosition(zCOM);

			set_mass(new_mass);

			//What to do about the radius? Keep average density? New density = p1m1 + p2m2/m1+m2
			double new_density = (density()*mass() + (*it)->density()*(*it)->mass()) / new_mass;

			//r = (3/4 m/(p pi))^1/3
			set_Radius(pow(3/4 * new_mass/(M_PI * new_density), 1/3));

			//remove the body from the vector
			Body_Vector->erase(it);
			--it;
			cout << "deleted an entry" << endl;
		}
		else	//if bodies aren't touching, calculate acceleration
		{
			double magAcc = -G*(*it)->mass()/rCubed; 

			accX = accX + magAcc*rx;
			accY = accY + magAcc*ry;
			accZ = accZ + magAcc*rz;
		}	
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

const double Body::density() const
{
	return m_mass / ((4/3)*M_PI*pow(m_radius, 3));
};

const bool Body::isTrackingTrajectory() const
{
	return m_logTrajectory;
};

void Body::addToTrajectory(ofstream* trajectory_file)
{
	if(isTrackingTrajectory() == true && trajectory_file != NULL)
	{
		*trajectory_file << m_ID << "\t" << m_xPosition/AU << "\t" << m_zPosition/AU << "\t" << m_zPosition/AU << endl;
	}
};

const double Body::relaxation() const
{
	return m_relaxation;
}