#include "ProtoplanetaryCloud.h"
#include <random>

ProtoplanetaryCloud::ProtoplanetaryCloud() //Default constructor - should be unused (set as private())
{
	//
};

ProtoplanetaryCloud::~ProtoplanetaryCloud() //Destructor
{
	std::cout << "Protoplanetary cloud destructor" << std::endl;
};

ProtoplanetaryCloud::ProtoplanetaryCloud(const int& numberOfBodies,
										 const double& mass, 
										 const double& xScaleHeight, 
										 const double& yScaleHeight, 
										 const double& zScaleHeight,
										 const double& velocity,
										 const double& velocityDispersion)
{

	//F = m1v^2/R = Gm1m2/r^2
	//v^2 = Gm2/R
	//v = pow(G*m_sun/R, 0.5)

	const double Solar_Mass(1.989*pow(10, 30));
	const double G(6.67384*pow(10,-11));
	
	const double jupiter_radius(6.96*pow(10, 8)/10);

	std::default_random_engine generator;

  	std::normal_distribution<double> distributionx(0., xScaleHeight);
  	std::normal_distribution<double> distributiony(0., yScaleHeight);
  	std::normal_distribution<double> distributionz(0., zScaleHeight);
  	std::normal_distribution<double> distribution_velocity(velocity, velocityDispersion);

	for (int i = 0; i < numberOfBodies; i++)
	{
		double xPos = distributionx(generator);
		double yPos = distributiony(generator);
		double zPos = distributionz(generator);

		//Direction of velocity (perpindicular to the displacement) assume no z Velocity
		double velocity_Direction_x = pow(pow(xPos,2) + pow(yPos,2),-0.5)*(-yPos);
		double velocity_Direction_y = pow(pow(xPos,2) + pow(yPos,2),-0.5)*(xPos);

		//Magnitude of velocity (constant) ms^-1
		double velocity_magnitude = distribution_velocity(generator);
		double newVel = pow(G*Solar_Mass/pow(pow(xPos, 2) + pow(yPos, 2), 0.5), 0.5);
		double xVel = velocity_Direction_x * newVel;
		double yVel = velocity_Direction_y * newVel;
		double zVel = 0;

		stringstream combiner;
		combiner << "Planetesimal" << i;
		string name;
		combiner >> name;

		addBody(new Body(name, mass/numberOfBodies, xPos, yPos, zPos, xVel, yVel, zVel, 0.05*jupiter_radius, false));
	}
};