#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#include "system.h"

using namespace std;

System::System()
{
	m_name = "Ghost";
}

void System::addBody(const Body newBody)
{
	Body* newBodyToAdd = new Body(newBody);
	m_Bodies.push_back(newBodyToAdd);
}

void System::update(const double& timestep)
{
	vector <Body*>::iterator it;
	for (it = m_Bodies.begin(); it != m_Bodies.end(); ++it)
  	{
  		//cout << "making acc calc" << endl;
		vector<double> acceleration = (*it)->accelerationCalc(&m_Bodies);
		//cout << "completed acc calc" << endl;

		(*it)->set_xPosition((*it)->xPosition() + (*it)->xVelocity()*timestep);
		(*it)->set_yPosition((*it)->yPosition() + (*it)->yVelocity()*timestep);
		(*it)->set_zPosition((*it)->zPosition() + (*it)->zVelocity()*timestep);
	
		(*it)->set_xVelocity((*it)->xVelocity() + acceleration.at(0)*timestep);
		(*it)->set_yVelocity((*it)->yVelocity() + acceleration.at(1)*timestep);
		(*it)->set_zVelocity((*it)->zVelocity() + acceleration.at(2)*timestep);
		//cout << acceleration.at(0)*timestep << endl;
		//cout << acceleration.at(1)*timestep << endl;
		//cout << acceleration.at(2)*timestep << endl;
	}	
	return;
}

void System::printCoordinates(const string& filename)
{
	return;
}