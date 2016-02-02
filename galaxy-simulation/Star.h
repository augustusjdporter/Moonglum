#ifndef STAR_H
#define STAR_H

#include "../body.h"

class Star : public Body
{
public:
	Star(double tempMass,
		 double tempxPosition, 
		 double tempyPosition, 
		 double tempzPosition, 
		 double tempxVelocity, 
		 double tempyVelocity, 
		 double tempzVelocity,
		 double tempRadius,
		 bool	tempLogTrajectory)
		  : Body("Star", 
				tempMass, 
				tempxPosition, 
				tempyPosition, 
				tempzPosition, 
				tempxVelocity, 
				tempyVelocity, 
				tempzVelocity, 
				tempRadius, 
				tempLogTrajectory)
	{
		
		
	};

	~Star()
	{
		std::cout << "Star destructor called" << endl;
	};

private:
	Star()
	{
		std::cout << "Error: Star default constructor called" << std::endl;
	};
};

#endif