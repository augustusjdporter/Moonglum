#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <thread>

#include "system.h"

using namespace std;

unsigned concurentThreadsSupported = std::thread::hardware_concurrency();

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
	SystemMap::iterator it;
	for (it = m_BoundSystems.begin(); it != m_BoundSystems.end(); ++it)
	{
		it->second = NULL;
	}

	while (!m_Bodies.empty())
	{
		if (delete m_Bodies.back() != NULL)
		{
			delete m_Bodies.back();
			m_Bodies.pop_back();
		};
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
	vector<thread> threads;
	auto acceleration_func = [&](int start, int total)
    {
        for (int i = start; i < start + total; ++i)
        {
			m_Bodies.at(i)->accelerationCalc(&m_Bodies);
        };
    };
	
	for (int i = 0; i < concurentThreadsSupported; ++i)
	{
		if (i != concurentThreadsSupported-1)
        	threads.push_back(thread(acceleration_func, i * m_Bodies.size()/concurentThreadsSupported, m_Bodies.size()/concurentThreadsSupported));
		else	//Chuck any of the remainder into the last thread (wont make a difference in performance, will usually be a max of 3 bodies)
			threads.push_back(thread(acceleration_func, i * m_Bodies.size()/concurentThreadsSupported, m_Bodies.size()/concurentThreadsSupported + m_Bodies.size()%concurentThreadsSupported));
	}
	
	for (auto& th : threads) 
        th.join();
	
	threads.clear();
	
	auto update_pos_func = [&](int start, int total)
    {
		for (int i = start; i < start + total; ++i)
        {		
			m_Bodies.at(i)->update_position_and_velocity(timestep);
        };
	};
	
	for (int i = 0; i < concurentThreadsSupported; ++i)
	{
		if (i != concurentThreadsSupported-1)
        	threads.push_back(thread(update_pos_func, i * m_Bodies.size()/concurentThreadsSupported, m_Bodies.size()/concurentThreadsSupported));
		else	//Chuck any of the remainder into the last thread (wont make a difference in performance, will usually be a max of 3 bodies)
			threads.push_back(thread(update_pos_func, i * m_Bodies.size()/concurentThreadsSupported, m_Bodies.size()/concurentThreadsSupported + m_Bodies.size()%concurentThreadsSupported));
	};
	
	for (auto& th : threads) 
        th.join();
	return;
};

void System::printCoordinates(ofstream* coordinate_file, ofstream* trajectory_file, const double& normalisation)
{
	for (int i=0; i < m_Bodies.size(); i++)
	{
		*coordinate_file << m_Bodies.at(i)->name() << "\t" << m_Bodies.at(i)->xPosition()/normalisation << "\t" << m_Bodies.at(i)->yPosition()/normalisation << "\t" << m_Bodies.at(i)->zPosition()/normalisation << endl;//prints shape data with overloaded <<
		if(m_Bodies.at(i)->isTrackingTrajectory() == true)
		{
			m_Bodies.at(i)->addToTrajectory(trajectory_file);
		}
	}

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
