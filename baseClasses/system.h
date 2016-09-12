//system.h: Defines the Systems class, which defines a gravitationally bound system of Bodies.
#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <random>

#include "Constants.h"
#include "body.h"
#include "barnesHut/BarnesHutTree.h"
#include "barnesHut/BarnesHutTree3D.h"

class System;

typedef std::map<string, System*> SystemMap;
typedef std::map<int, Body*> BodyMap; //Convert the vector of bodies to map of bodies, with ID as the key.

using namespace std;

enum SimSolver
{
	bruteForceCPU,
	bruteForceGPU,
	barnesHutCPU
};

class System
{
public:

	//Constructors/destructors
	System();

	System(const string& name);

	~System();

	//Add a body to the system
	void addBody(shared_ptr<Body> newBody);

	//Add another astrophysical system from which to feel gravitational influence.
	void addBoundSystem(System* newSystem);

	//Calculate gravitational acceleration of the bodies in the system.

#ifdef GPU_COMPUTE
	void update_on_gpu(const double& timestep);
#endif

	void update_on_cpu(const double& timestep);

	void update_barnes_hut(const double& timestep);

	void update_barnes_hut3D(const double& timestep);

	//Print the coordinates of the bodies in the system to file.
	void printCoordinates(ofstream* coordinate_file, ofstream* trajectory_file, const double& normalisation);

	//Access functions
	vector<shared_ptr<Body>>* Bodies();

	const string& name() const;

private:

	vector<shared_ptr<Body>> m_Bodies;
	SystemMap m_BoundSystems;	//map of other systems, used to enable gravitational interactions between two systems
	string m_name;
};

#endif