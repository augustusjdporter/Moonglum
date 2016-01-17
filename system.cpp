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
	Body newBodyToAdd = new Body(newBody);
	m_Bodies.push_back(&newBody);
}

void System::update()
{
	return;
}

void System::printCoordinates()
{
	return;
}