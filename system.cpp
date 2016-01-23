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
};

System::System(const string& name)
{
	m_name = name;
};

System::~System()
{
	cout << "System destructor" << endl;
	SystemMap::iterator it;
	for (it = m_BoundSystems.begin(); it != m_BoundSystems.end(); ++it)
	{
		it->second = NULL;
	}

	cout << m_name << " destructor called." << endl;
	while (!m_Bodies.empty())
	{
		delete m_Bodies.back();
		m_Bodies.pop_back();
	}



	m_BoundSystems.clear();
	m_name = "";
};

void System::addBody(Body* newBody)
{
	m_Bodies.push_back(newBody);
};

void System::addBody(const Body newBody)
{
	Body* newBodyToAdd = new Body(newBody);
	m_Bodies.push_back(newBodyToAdd);
};

void System::update(const double& timestep)
{
	
	
	vector <Body*>::iterator it;
	for (it = m_Bodies.begin(); it != m_Bodies.end(); ++it)
  	{
		vector<double> acceleration = (*it)->accelerationCalc(&m_Bodies);//calculate acceleration from own system

		SystemMap::iterator system_it;
		for(system_it = m_BoundSystems.begin(); system_it != m_BoundSystems.end(); system_it++) 
		{
    		vector<double> temp_acceleration = (*it)->accelerationCalc(system_it->second->Bodies());//calculate acceleration from any additional systems

    		acceleration.at(0) = acceleration.at(0) + temp_acceleration.at(0);
    		acceleration.at(1) = acceleration.at(1) + temp_acceleration.at(1);
    		acceleration.at(2) = acceleration.at(2) + temp_acceleration.at(2);
		}

		(*it)->set_xPosition((*it)->xPosition() + (*it)->xVelocity()*timestep);
		(*it)->set_yPosition((*it)->yPosition() + (*it)->yVelocity()*timestep);
		(*it)->set_zPosition((*it)->zPosition() + (*it)->zVelocity()*timestep);
	
		(*it)->set_xVelocity((*it)->xVelocity() + acceleration.at(0)*timestep);
		(*it)->set_yVelocity((*it)->yVelocity() + acceleration.at(1)*timestep);
		(*it)->set_zVelocity((*it)->zVelocity() + acceleration.at(2)*timestep);
	}
	return;
};

void System::printCoordinates(const string& path, const string& filename)
{
	const double AU(1.4960*pow(10, 11));
	ofstream file;
	file.open (path + filename);
	for (int i=0; i < m_Bodies.size(); i++)
	{
		file << m_Bodies.at(i)->name() << "\t" << m_Bodies.at(i)->xPosition()/AU << "\t" << m_Bodies.at(i)->yPosition()/AU << "\t" << m_Bodies.at(i)->zPosition()/AU << endl;//prints shape data with overloaded <<
		if(m_Bodies.at(i)->isTrackingTrajectory() == true)
		{
			m_Bodies.at(i)->addToTrajectory(path);
		}
	}

	//we want to write bound systems coordinates to the same file.
	if (m_BoundSystems.size() > 0)
	{
		SystemMap::iterator it;
		for (it = m_BoundSystems.begin(); it != m_BoundSystems.end(); ++it)
		{
			vector<Body*>* tempBodies = it->second->Bodies();
			if (tempBodies != NULL)
			{
				for (int i=0; i < tempBodies->size(); i++)
				{
					file << tempBodies->at(i)->name() << "\t" << tempBodies->at(i)->xPosition()/AU << "\t" << tempBodies->at(i)->yPosition()/AU << "\t" << tempBodies->at(i)->zPosition()/AU << endl;//prints shape data with overloaded <<
					if(tempBodies->at(i)->isTrackingTrajectory() == true)
					{
						tempBodies->at(i)->addToTrajectory(path);
					}
				}
			}
		}
	}
	file.close();
	return;
};

void System::addBoundSystem(System* newSystem)
{
	m_BoundSystems.insert(make_pair(newSystem->name(), newSystem));
	return;
};

const string& System::name() const 
{
	return m_name;
};

vector<Body*>* System::Bodies()
{
	return &m_Bodies;
};