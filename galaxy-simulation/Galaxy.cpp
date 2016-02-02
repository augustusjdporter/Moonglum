#include "Galaxy.h"
#include "Gas.h"
#include "Star.h"
#include "BlackHole.h"
#include <random>

Galaxy::Galaxy() //Default constructor - should be unused (set as private())
{
	//
};

Galaxy::~Galaxy()
{
	std::cout << "Galaxy destructor" << std::endl;
};

Galaxy::Galaxy(const int& numberOfStars,
			   const double& massStars,
			   const int& numberOfGas,
			   const double& massGas,
			   const double& massBlackHole,
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
	const double solar_radius(6.96*pow(10, 8));
	const double G(6.67384*pow(10,-11));
	
	const double jupiter_radius(6.99*pow(10, 7));

	std::default_random_engine generator;

  	std::uniform_real_distribution<double> distributionR(0., 1.);
  	std::uniform_real_distribution<double> distributionTheta(0., 2*M_PI);
  	std::normal_distribution<double> distributionz(0., zScaleHeight);
  	std::normal_distribution<double> distribution_velocity(velocity, velocityDispersion);

	for (int i = 0; i < numberOfStars; i++)
	{
		double R = distributionR(generator);
		double Theta = distributionTheta(generator);
		double zPos = distributionz(generator);

		double xPos = xScaleHeight*R*cos(Theta);
		double yPos = yScaleHeight*R*sin(Theta);

		//Direction of velocity (perpindicular to the displacement) assume no z Velocity
		double velocity_Direction_x = pow(pow(xPos,2) + pow(yPos,2),-0.5)*(-yPos);
		double velocity_Direction_y = pow(pow(xPos,2) + pow(yPos,2),-0.5)*(xPos);

		//Magnitude of velocity (constant) ms^-1
		double velocity_magnitude = distribution_velocity(generator);
		double xVel = velocity_Direction_x * velocity_magnitude;
		double yVel = velocity_Direction_y * velocity_magnitude;
		double zVel = 0;

		addBody(new Star(massStars/numberOfStars, xPos, yPos, zPos, xVel, yVel, zVel, solar_radius, false));
	}

	for (int i = 0; i < numberOfGas; i++)
	{
		double R = distributionR(generator);
		double Theta = distributionTheta(generator);
		double zPos = distributionz(generator);

		double xPos = xScaleHeight*R*cos(Theta);
		double yPos = yScaleHeight*R*sin(Theta);

		//Direction of velocity (perpindicular to the displacement) assume no z Velocity
		double velocity_Direction_x = pow(pow(xPos,2) + pow(yPos,2),-0.5)*(-yPos);
		double velocity_Direction_y = pow(pow(xPos,2) + pow(yPos,2),-0.5)*(xPos);

		//Magnitude of velocity (constant) ms^-1
		double velocity_magnitude = distribution_velocity(generator);
		double xVel = velocity_Direction_x * velocity_magnitude;
		double yVel = velocity_Direction_y * velocity_magnitude;
		double zVel = 0;

		addBody(new Gas(massGas/numberOfGas, xPos, yPos, zPos, xVel, yVel, zVel, 10*solar_radius, false));
	}

	addBody(new BlackHole(massBlackHole, 0, 0, 0, 0, 0, 0, true));
};