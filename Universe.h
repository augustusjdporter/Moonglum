#ifndef Universe_h
#define Universe_h

#include "body.h"
#include "system.h"

typedef std::map<string, System*> SystemMap;

class Universe
{
public:
	//Constructors/Destructors
	Universe();

	~Universe();

	void addSystem(System* systemToAdd);

	void bindSystems();

	void updateUniverse(double timestep);

	void printCoordinatesToFile(const string& path, const string& filename, const double& normalisation);

private:
	SystemMap m_astrophysicalSystems; //The astrophysical systems which constitute this Universe (simulation)
};



#endif