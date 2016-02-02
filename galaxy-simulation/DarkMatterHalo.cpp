#include "DarkMatterHalo.h"
#include <cmath>
#include <iostream>

using namespace std;

DarkMatterHalo::DarkMatterHalo()
{
	cout << "Default DarkMatterHalo constructor called. An error has occured" << endl;
};

DarkMatterHalo::~DarkMatterHalo()
{
	cout << "DarkMatterHalo destructor called" << endl;
};

DarkMatterHalo::DarkMatterHalo(const int& numberOfBodies,
				   			   const double& mass, 
							   const double& xScaleHeight, 
							   const double& yScaleHeight, 
							   const double& zScaleHeight)
{
	std::default_random_engine generator;

  	std::uniform_real_distribution<double> distributionR(0., 1.);
  	std::uniform_real_distribution<double> distributionTheta(0., 2*M_PI);
  	std::uniform_real_distribution<double> distributionPhi(0., M_PI);
  	//get uniform unit sphere, then multiply each direction by the scale height



	for (int i = 0; i < numberOfBodies; i++)
	{
		double Radius = distributionR(generator);
		double Theta = distributionTheta(generator);
		double Phi = distributionPhi(generator);

		//Uniform ellipsoid. currently static
		double xPos = xScaleHeight*Radius*sin(Phi)*cos(Theta);
		double yPos = yScaleHeight*Radius*sin(Phi)*sin(Theta);
		double zPos = zScaleHeight*Radius*cos(Phi);

		string name = "DarkMatter";

		addBody(new Body(name, mass/numberOfBodies, xPos, yPos, zPos, 0, 0, 0, 0, false));
	}
};