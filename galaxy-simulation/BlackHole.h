#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "../body.h"

class BlackHole : public Body
{
public:
	BlackHole(double tempMass,
		 	  double tempxPosition, 
		 	  double tempyPosition, 
		 	  double tempzPosition, 
		 	  double tempxVelocity, 
		 	  double tempyVelocity, 
		 	  double tempzVelocity,
		 	  bool	tempLogTrajectory);

	~BlackHole();

	const double radius() const;

private:
	BlackHole();
};

#endif