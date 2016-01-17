#ifndef SYSTEM_H // Will only be true the once!
#define SYSTEM_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#include "body.h"

using namespace std;

class System
{
public:
	System();

	~System(){};

	void addBody(const Body newBody);

	void addBody(Body* newBody);

	void update(const double& timestep);

	void printCoordinates(const string& fileName);

private:

	vector<Body*> m_Bodies;
	string m_name;
};

#endif