#ifndef GAS_H
#define GAS_H

#include "../body.h"

class Gas : public Body
{
public:
	Gas(double tempMass,
		 double tempxPosition, 
		 double tempyPosition, 
		 double tempzPosition, 
		 double tempxVelocity, 
		 double tempyVelocity, 
		 double tempzVelocity,
		 double tempRadius,
		 bool	tempLogTrajectory)
		  : Body("Gas", 
				tempMass, 
				tempxPosition, 
				tempyPosition, 
				tempzPosition, 
				tempxVelocity, 
				tempyVelocity, 
				tempzVelocity, 
				tempRadius, 
				tempLogTrajectory)
	{};

	~Gas()
	{
		std::cout << "Gas destructor called" << endl;
	};

private:
	Gas()
	{
		std::cout << "Error: Gas default constructor called" << std::endl;
	};
};

#endif