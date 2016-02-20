#ifndef XMLREADER_H
#define XMLREADER_H

#include <iostream>
#include <vector>
#include <fstream>

#include "../body.h"
#include "../system.h"
#include "../Universe.h"
#include "../Constants.h"
#include "Utilities.h"
#include "../planetary-simulation/ProtoplanetaryCloud.h"
#include "../galaxy-simulation/Galaxy.h"
#include "../galaxy-simulation/Gas.h"
#include "../galaxy-simulation/BlackHole.h"
#include "../galaxy-simulation/DarkMatterHalo.h"
#include "../galaxy-simulation/Star.h"

#include "rapidxml-1.13/rapidxml.hpp" //defines xml config reader

using namespace std;
using namespace rapidxml;

class XmlReader
{
public:
	XmlReader();

	~XmlReader();

	int parseConfig(char* configFile, int* timestep, int* numberOfSteps, int* samplingRate, double* normalisation, Universe* simulation_universe);

	const string simulationType() const;

private:
	int parseGalaxyConfig();

	int parsePlanetaryConfig();

	int* m_timestep;
	int* m_numberOfSteps;
	int* m_samplingRate;
	Universe* m_simulation_universe;

	xml_document<> m_doc;
	xml_node<> * m_root_node;

	string m_simulation_type;
};
#endif