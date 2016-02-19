#include "ProtoplanetaryCloud.h"
#include <random>

ProtoplanetaryCloud::ProtoplanetaryCloud() : System("ProtoplanetaryCloud")//Default constructor - should be unused (set as private())
{
	//
};

ProtoplanetaryCloud::~ProtoplanetaryCloud() //Destructor
{
	std::cout << "Protoplanetary cloud destructor" << std::endl;
};

ProtoplanetaryCloud::ProtoplanetaryCloud(const int& numberOfBodies,
										 const double& mass,
										 const double& xCenter, 
										 const double& yCenter, 
										 const double& zCenter,
										 const double& xScaleHeight, 
										 const double& yScaleHeight, 
										 const double& zScaleHeight,
										 const double& velocity,
										 const double& velocityDispersion) : System("ProtoplanetaryCloud")
{

	//F = m1v^2/R = Gm1m2/r^2
	//v^2 = Gm2/R
	//v = pow(G*m_sun/R, 0.5)

	std::default_random_engine generator;

  	std::normal_distribution<double> distributionx(xCenter, xScaleHeight);
  	std::normal_distribution<double> distributiony(yCenter, yScaleHeight);
  	std::normal_distribution<double> distributionz(zCenter, zScaleHeight);
  	std::normal_distribution<double> distribution_velocity(velocity, velocityDispersion);

	for (int i = 0; i < numberOfBodies; i++)
	{
		double xPos = distributionx(generator);
		double yPos = distributiony(generator);
		double zPos = distributionz(generator);

		//Direction of velocity (perpindicular to the displacement) assume no z Velocity
		double velocity_Direction_x = pow(pow(xPos-xCenter,2) + pow(yPos-yCenter,2),-0.5)*(-(yPos-yCenter));
		double velocity_Direction_y = pow(pow(xPos-xCenter,2) + pow(yPos-yCenter,2),-0.5)*(xPos-xCenter);

		//Magnitude of velocity (constant) ms^-1
		double velocity_magnitude = distribution_velocity(generator);
		double newVel = pow(G*solar_Mass/pow(pow(xPos-xCenter, 2) + pow(yPos-yCenter, 2), 0.5), 0.5);
		double xVel = velocity_Direction_x * newVel;
		double yVel = velocity_Direction_y * newVel;
		double zVel = 0;

		string name = "Planetesimal";

		addBody(new Body(name, mass/numberOfBodies, xPos, yPos, zPos, xVel, yVel, zVel, 0.2*jupiter_radius, false));
	}
};
