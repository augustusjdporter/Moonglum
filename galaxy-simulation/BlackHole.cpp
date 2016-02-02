#include "BlackHole.h"
#include <iostream>

using namespace std;

BlackHole::BlackHole()
{
	cout << "Error: BlackHole default constructor called" << endl;
};

BlackHole::BlackHole(double tempMass,
		 			 double tempxPosition, 
					 double tempyPosition, 
					 double tempzPosition, 
					 double tempxVelocity, 
					 double tempyVelocity, 
					 double tempzVelocity,
					 bool	tempLogTrajectory) 

						: Body("BlackHole", 
							tempMass, 
							tempxPosition, 
							tempyPosition, 
							tempzPosition, 
							tempxVelocity, 
							tempyVelocity, 
							tempzVelocity, 
							0, 
							tempLogTrajectory)
{

};

BlackHole::~BlackHole()
{
	cout << name() << " destructor called." << endl;
};

const double BlackHole::radius() const
{
	const double G(6.67384*pow(10,-11));
	const double c(3*pow(10, 8));

	return 2*G*mass()/pow(c, 2);
}