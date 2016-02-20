#ifndef PROTOPLANETARYCLOUD_H
#define PROTOPLANETARYCLOUD_H

#include "../system.h"
#include "../Constants.h"

class ProtoplanetaryCloud : public System
{
public:
	

	~ProtoplanetaryCloud(); //Destructor

	ProtoplanetaryCloud(const int& numberOfBodies,
						const double& mass,
						const double& xCenter, 
						const double& yCenter, 
						const double& zCenter,
						const double& xScaleHeight, 
						const double& yScaleHeight, 
						const double& zScaleHeight,
						const double& veocity,
						const double& velocityDispersion);

private:
	ProtoplanetaryCloud(); //Default constructor - should be unused (set as private())
};

#endif