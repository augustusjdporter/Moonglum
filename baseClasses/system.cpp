#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <thread>

#include "system.h"

#ifdef GPU_COMPUTE
#include "..\Utilities\OpenCLFunctions.h"

vex::Context ctx(
	vex::Filter::Type(CL_DEVICE_TYPE_GPU) &&
	vex::Filter::DoublePrecision &&
	vex::Filter::Count(1)
);
#endif

unsigned concurentThreadsSupported = std::thread::hardware_concurrency();

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
	SystemMap::iterator it;
	for (it = m_BoundSystems.begin(); it != m_BoundSystems.end(); ++it)
	{
		it->second = NULL;
	}

	while (!m_Bodies.empty())
	{
		if (m_Bodies.back() != NULL)
		{
			delete m_Bodies.back();
			m_Bodies.back() = NULL;
			m_Bodies.pop_back();
		}
		else
		{
			m_Bodies.pop_back();
		};
	};

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


void System::update_on_cpu(const double& timestep)
{	
	cout << "calculating acc on cpu" << endl;
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
			threads.push_back(thread(acceleration_func, i * m_Bodies.size()/concurentThreadsSupported, m_Bodies.size()/concurentThreadsSupported + m_Bodies.size()%concurentThreadsSupported-1));
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
		if (i != concurentThreadsSupported - 1)
			threads.push_back(thread(update_pos_func, i * m_Bodies.size() / concurentThreadsSupported, m_Bodies.size() / concurentThreadsSupported));
		else	//Chuck any of the remainder into the last thread (wont make a difference in performance, will usually be a max of 3 bodies)
			threads.push_back(thread(update_pos_func, i * m_Bodies.size() / concurentThreadsSupported, m_Bodies.size() / concurentThreadsSupported + m_Bodies.size() % concurentThreadsSupported-1));
	};

	for (auto& th : threads)
		th.join();
	return;
};

#ifdef GPU_COMPUTE
void System::update_on_gpu(const double& timestep)
{	
	cout << "calculating acc on gpu" << endl;
	size_t n = m_Bodies.size();
	vex::vector<double> m(ctx, n);
	vex::vector<cl_double3> q(ctx, n), acc(ctx, n);

	for (int i = 0; i < n; i++)
	{
		cl_double3 j;
		j.x = m_Bodies.at(i)->xPosition();
		j.y = m_Bodies.at(i)->yPosition();
		j.z = m_Bodies.at(i)->zPosition();
		q[i] = j;

		m[i] = m_Bodies.at(i)->mass();
	}

	acc = calculate_acceleration(n, vex::element_index(), vex::raw_pointer(m), vex::raw_pointer(q));

	for (int i = 0; i < n; i++)
	{
		cl_double3 temp_acceleration = acc[i];
		m_Bodies.at(i)->set_acceleration(temp_acceleration.x, temp_acceleration.y, temp_acceleration.z);
	}

	vector<thread> threads;
	auto update_pos_func = [&](int start, int total)
	{
		for (int i = start; i < start + total; ++i)
		{
			m_Bodies.at(i)->update_position_and_velocity(timestep);
		};
	};

	for (int i = 0; i < concurentThreadsSupported; ++i)
	{
		if (i != concurentThreadsSupported - 1)
			threads.push_back(thread(update_pos_func, i * m_Bodies.size() / concurentThreadsSupported, m_Bodies.size() / concurentThreadsSupported));
		else	//Chuck any of the remainder into the last thread (wont make a difference in performance, will usually be a max of 3 bodies)
			threads.push_back(thread(update_pos_func, i * m_Bodies.size() / concurentThreadsSupported, m_Bodies.size() / concurentThreadsSupported + m_Bodies.size() % concurentThreadsSupported));
	};

	for (auto& th : threads)
		th.join();
	return;
};
#endif

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
