#ifndef SYSTEM_H // Will only be true the once!
#define SYSTEM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <random>

#include "body.h"
class System;

typedef std::map<string, System*> SystemMap;

using namespace std;

class System
{
public:
	System();

	System(const string& name);

	~System();

	void addBody(const Body newBody);

	void addBody(Body* newBody);

	void addBoundSystem(System* newSystem);

	void update(const double& timestep);

	void printCoordinates(const string& path, const string& fileName);

	vector<Body*>* Bodies();

	const string& name() const;

private:

	vector<Body*> m_Bodies;
	SystemMap m_BoundSystems;	//map of other systems, used to enable gravitational interactions between two systems
	string m_name;
};

#endif