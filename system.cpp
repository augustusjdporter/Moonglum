#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>

#include "system.h"

using namespace std;

System::System()
{
	m_name = "Ghost";
}

void System::addBody(Body* newBody)
{
	m_Bodies.push_back(newBody);
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
		vector<double> acceleration = (*it)->accelerationCalc(&m_Bodies);

		(*it)->set_xPosition((*it)->xPosition() + (*it)->xVelocity()*timestep);
		(*it)->set_yPosition((*it)->yPosition() + (*it)->yVelocity()*timestep);
		(*it)->set_zPosition((*it)->zPosition() + (*it)->zVelocity()*timestep);
	
		(*it)->set_xVelocity((*it)->xVelocity() + acceleration.at(0)*timestep);
		(*it)->set_yVelocity((*it)->yVelocity() + acceleration.at(1)*timestep);
		(*it)->set_zVelocity((*it)->zVelocity() + acceleration.at(2)*timestep);
	}
	return;
}

void System::printCoordinates(const string& filename)
{
	ofstream file;
	file.open (filename);
	for (int i=0; i<m_Bodies.size(); i++)
	{
		file << m_Bodies.at(i)->name() << "\t" << m_Bodies.at(i)->xPosition() << "\t" << m_Bodies.at(i)->yPosition() << "\t" << m_Bodies.at(i)->zPosition() << endl;//prints shape data with overloaded <<
	}	
	file.close();
	return;
}