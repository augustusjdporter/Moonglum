#ifndef Universe_h
#define Universe_h

#include <fstream>
#include "body.h"
#include "system.h"
#include "Constants.h"
#include "../baseClasses/barnesHut/Quadrant.h"

typedef std::map<string, System*> SystemMap;

class Universe
{
public:
	//Constructors/Destructors
	Universe(string simName);

	~Universe();

	void addSystem(System* systemToAdd);

	void bindSystems();

	void updateUniverse(double timestep, SimSolver simSolver);

	void printCoordinatesToFile(const string& path, const string& filename, const double& normalisation);

	void makeTrajectoryFiles(const string& path, const string& isTrackingFilename, const string& trajectoriesFilename);

	void saveState(const string & path, const int & plotNumber, const int & coordNumber, const double& timestep, const int& samplingRate, const double& normalisation);

	bool loadFromSaveFile(const string& filePath, int& plotNumber, int& coordNumber, int& timestep, int& samplingRate, double& normalisation);

private:
	SystemMap m_astrophysicalSystems; //The astrophysical systems which constitute this Universe (simulation)
	ofstream  m_trajectoriesFile;
	
	System	m_allSystems;
	string m_name;

	bool run_on_gpu;
};



#endif