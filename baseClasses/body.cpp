#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <cmath>
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#include <sys/types.h>
#include <sys/stat.h>
#ifdef __linux__ 
#include <unistd.h>
#endif

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

	m_xAcceleration = 0;
	m_yAcceleration = 0;
	m_zAcceleration = 0;
	
	m_radius = 0;
	m_relaxation = 0;
	
	m_trajectory = NULL;
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
	
	m_relaxation = bodyToCopy.relaxation();

	m_logTrajectory = bodyToCopy.isTrackingTrajectory();

	m_xAcceleration = 0;
	m_yAcceleration = 0;
	m_zAcceleration = 0;
	
	m_trajectory = NULL;
};

Body::~Body()
{
	/*if (m_name != "Planetesimal")*/
	cout << "Destroying " << m_name << " " << m_ID << endl;
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

	m_xAcceleration = 0;
	m_yAcceleration = 0;
	m_zAcceleration = 0;
	
	m_trajectory = NULL;

	//m_relaxation = 0.05*3.0857*pow(10, 12);
	m_relaxation = m_radius;
	if (m_name != "Planetesimal")
	cout << m_name << " created " << m_ID << endl;
}
Body::Body(int tempID, string tempName, double tempMass, double tempRadius, double tempRelaxation, double tempxPosition, double tempyPosition, double tempzPosition, double tempxVelocity, double tempyVelocity, double tempzVelocity, bool tempLogTrajectory)
{
	m_ID = tempID;
	m_trajectory = NULL;

	m_name = tempName;
	m_mass = tempMass;

	m_xPosition = tempxPosition;
	m_yPosition = tempyPosition;
	m_zPosition = tempzPosition;

	m_xVelocity = tempxVelocity;
	m_yVelocity = tempyVelocity;
	m_zVelocity = tempzVelocity;

	m_isValid = tempLogTrajectory;

	m_radius = tempRadius;

	m_logTrajectory = tempLogTrajectory;

	m_xAcceleration = 0;
	m_yAcceleration = 0;
	m_zAcceleration = 0;
	
	m_isValid = true;
	
	m_trajectory = NULL;

	//m_relaxation = 0.05*3.0857*pow(10, 12);
	m_relaxation = tempRelaxation;
	if (m_name != "Planetesimal")
		cout << m_name << " created " << m_ID << endl;
};

const int& Body::ID() const
{
	return m_ID;
}

const double Body::twoDimensionalDistanceToOtherBody(const Body& otherBody)
{
	double rx = m_xPosition - otherBody.xPosition();
	double ry = m_yPosition - otherBody.yPosition();

	return pow(pow(rx, 2) + pow(ry, 2), 0.5);
}

const double Body::threeDimensionalDistanceToOtherBody(const Body& otherBody)
{
	double rx = m_xPosition - otherBody.xPosition();
	double ry = m_yPosition - otherBody.yPosition();
	double rz = m_zPosition - otherBody.zPosition();

	return pow(pow(rx, 2) + pow(ry, 2) + pow(rz, 2), 0.5);
}

void Body::addToAccelerationDueToOneBody(const Body& otherBody)
{
	double rx = m_xPosition - otherBody.xPosition();
	double ry = m_yPosition - otherBody.yPosition();
	double rz = m_zPosition - otherBody.zPosition();
	double rCubed = pow(rx*rx + ry*ry + rz*rz + relaxation(), 1.5);

	double magAcc = -G*otherBody.mass() / rCubed;

	m_xAcceleration += magAcc*rx;
	m_yAcceleration += magAcc*ry;
	m_zAcceleration += magAcc*rz;

	return;
};

void Body::accelerationCalc(vector<shared_ptr<Body>>* Body_Vector)
{
	m_xAcceleration = 0;
	m_yAcceleration = 0;
	m_zAcceleration = 0;

	for (auto it = Body_Vector->begin(); it != Body_Vector->end(); ++it)
	{
		//if (ID() == (*it)->ID() || (*it)->isValid() == false) continue; //check it is same body, and that other body is valid. Don't need this if relaxation is non-zero, as the nominator for acceleration calc will be zero at last step
		//F = G*M*m*r_vector/r^3
		//a = G*M*r_vector/r^3
		double rx = m_xPosition - (*it)->xPosition();
		double ry = m_yPosition - (*it)->yPosition();
		double rz = m_zPosition - (*it)->zPosition();
		double rCubed = pow(rx*rx + ry*ry + rz*rz + relaxation(), 1.5);
		if (rCubed == 0)
			continue;
		//when bodies touch, they stick. Conserve linear momentum
		/*if(rCubed <= pow(radius() + (*it)->radius(), 3))
		{
			if((*it)->name() == "Sun" || (*it)->name() == "Star" || (*it)->name() == "Jupiter" || (*it)->name() == "Earth") continue;
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
			cout << (*it)->name() << " deleted an entry" << endl;
			--it;
			
			Body_Vector->erase(it);
		}
		else	//if bodies aren't touching, calculate acceleration
		{*/
			double magAcc = -G*(*it)->mass()/rCubed; 

			m_xAcceleration += magAcc*rx;
			m_yAcceleration += magAcc*ry;
			m_zAcceleration += magAcc*rz;
		//}	
	}

	return;
};

const double& Body::xPosition() const
{
	return m_xPosition;
};

const double& Body::yPosition() const
{
	return m_yPosition;
};

const double& Body::zPosition() const
{
	return m_zPosition;
};

const double& Body::xVelocity() const
{
	return m_xVelocity;
};

const double& Body::yVelocity() const
{
	return m_yVelocity;
};

const double& Body::zVelocity() const
{
	return m_zVelocity;
};

const string& Body::name() const
{
	return m_name;
};

const double& Body::mass() const
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

const double& Body::radius() const
{
	return m_radius;
};

const bool& Body::isValid() const
{
	return m_isValid;
};

void Body::set_isValid(const bool& new_isValid)
{
	m_isValid = new_isValid;
	return;
}
void Body::set_acceleration(const double & x, const double & y, const double & z)
{
	m_xAcceleration = x;
	m_yAcceleration = y;
	m_zAcceleration = z;
}
;

const double Body::density() const
{
	return m_mass / ((4/3)*M_PI*pow(m_radius, 3));
};

const bool& Body::isTrackingTrajectory() const
{
	return m_logTrajectory;
};

void Body::addToTrajectory(ofstream* trajectory_file)
{
	if(isTrackingTrajectory() == true && trajectory_file != NULL)
	{
		*trajectory_file << m_ID << "\t" << m_xPosition/AU << "\t" << m_yPosition/AU << "\t" << m_zPosition/AU << endl;
	}
};

const double& Body::relaxation() const
{
	return m_relaxation;
};

void Body::update_position_and_velocity(const double& timestep)
{
	m_xPosition += m_xVelocity*timestep + 0.5*m_xAcceleration*timestep*timestep;//s = vt + 1/2at^2
	m_yPosition += m_yVelocity*timestep + 0.5*m_xAcceleration*timestep*timestep;
	m_zPosition += m_zVelocity*timestep + 0.5*m_xAcceleration*timestep*timestep;

	//cout << "vel1: " << m_xVelocity << " " << m_yVelocity << " " << m_zVelocity << endl;
	m_xVelocity += m_xAcceleration*timestep;
	m_yVelocity += m_yAcceleration*timestep;
	m_zVelocity += m_zAcceleration*timestep;
	//cout << "vel2: " << m_xVelocity << " " << m_yVelocity << " " << m_zVelocity << endl;
	return;
};

const bool Body::isInQuadrant(const Quadrant& quad) const
{
	return quad.isPointInQuadrant(m_xPosition, m_yPosition);
}

const bool Body::isInQuadrant(const Quadrant3D& quad) const
{
	return quad.isPointInQuadrant(m_xPosition, m_yPosition, m_zPosition);
}

const double& Body::xAcceleration() const
{
	return m_xAcceleration;
};

const double& Body::yAcceleration() const
{
	return m_yAcceleration;
};

const double& Body::zAcceleration() const
{
	return m_zAcceleration;
};
