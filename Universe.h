#ifndef Universe_h
#define Universe_h

#include <fstream>
#include "body.h"
#include "system.h"
#include "Constants.h"

typedef std::map<string, System*> SystemMap;

class Universe
{
public:
	//Constructors/Destructors
	Universe(string simName);

	~Universe();

	void addSystem(System* systemToAdd);

	void bindSystems();

	void updateUniverse(double timestep);

	void printCoordinatesToFile(const string& path, const string& filename, const double& normalisation);

	void makeIsTrackingTrajectoryFile(const string& path, const string& filename);

private:
	SystemMap m_astrophysicalSystems; //The astrophysical systems which constitute this Universe (simulation)
	ofstream  m_trajectoriesFile;
};



#endif