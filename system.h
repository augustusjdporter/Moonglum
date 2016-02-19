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
class System;

typedef std::map<string, System*> SystemMap;
typedef std::map<int, Body*> BodyMap; //Convert the vector of bodies to map of bodies, with ID as the key.

using namespace std;

class System
{
public:

	//Constructors/destructors
	System();

	System(const string& name);

	~System();

	//Add a body to the system (either object or pointer to object (can whittle down to one function))
	void addBody(const Body newBody);

	void addBody(Body* newBody);

	//Add another astrophysical system from which to feel gravitational influence.
	void addBoundSystem(System* newSystem);

	//Calculate gravitational acceleration of the bodies in the system.
	void update(const double& timestep);

	//Print the coordinates of the bodies in the system to file.
	void printCoordinates(ofstream* coordinate_file, ofstream* trajectory_file, const double& normalisation);

	//Access functions
	vector<Body*>* Bodies();

	const string& name() const;

private:

	vector<Body*> m_Bodies;
	SystemMap m_BoundSystems;	//map of other systems, used to enable gravitational interactions between two systems
	string m_name;
};

#endif