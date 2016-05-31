#include "Universe.h"

using namespace std;

Universe::Universe(string simName)
{
	m_name = simName;
};

void Universe::addSystem(System* systemToAdd)
{
	m_astrophysicalSystems.insert(make_pair(systemToAdd->name(), systemToAdd));
	return;
};

Universe::~Universe()
{
	m_trajectoriesFile.close();

	for (SystemMap::iterator iterator = m_astrophysicalSystems.begin(); iterator != m_astrophysicalSystems.end(); iterator++)
	{
		delete iterator->second;
		iterator->second = NULL;
	}
	
	m_astrophysicalSystems.clear();
};

void Universe::bindSystems()
{
	//possibly put handles to all the bodies into one big "System", and do all calculations from this.
	//Printing could stay the same as long as the pointers are to the right bodies.
	/*for (SystemMap::iterator iterator1 = m_astrophysicalSystems.begin(); iterator1 != m_astrophysicalSystems.end(); iterator1++)
	{
		for (SystemMap::iterator iterator2 = m_astrophysicalSystems.begin(); iterator2 != m_astrophysicalSystems.end(); iterator2++)
		{
			if(iterator2->first != iterator1->first)
			{
				iterator1->second->addBoundSystem(iterator2->second);
			}
		}
	}*/
	
	for (SystemMap::iterator iterator1 = m_astrophysicalSystems.begin(); iterator1 != m_astrophysicalSystems.end(); iterator1++)
	{
		for (auto iterator2 = iterator1->second->Bodies()->begin(); iterator2 != iterator1->second->Bodies()->end(); iterator2++)
		{
			m_allSystems.addBody(*iterator2);
		};
	};
	
	return;
};

void Universe::updateUniverse(double timestep)
{
	//Make this only update the one big system
	/*for (SystemMap::iterator iterator = m_astrophysicalSystems.begin(); iterator != m_astrophysicalSystems.end(); iterator++)
	{
		iterator->second->update(timestep);
	}*/
	m_allSystems.update(timestep);
	return;
};

void Universe::printCoordinatesToFile(const string& path, const string& filename, const double& normalisation)
{
	ofstream coordinate_file;
	coordinate_file.open(path + filename);

	for (SystemMap::iterator iterator = m_astrophysicalSystems.begin(); iterator != m_astrophysicalSystems.end(); iterator++)
	{
		iterator->second->printCoordinates(&coordinate_file, &m_trajectoriesFile, normalisation);
	}
	coordinate_file.close();

	return;
};

void Universe::makeTrajectoryFiles(const string& path, const string& isTrackingFilename, const string& trajectoriesFilename)
{
	ofstream isTrackingTrajectoryFile;
	isTrackingTrajectoryFile.open(path + isTrackingFilename);
	for (SystemMap::iterator iterator = m_astrophysicalSystems.begin(); iterator != m_astrophysicalSystems.end(); iterator++)
	{
		for (int i = 0; i < iterator->second->Bodies()->size(); i++)
		{
			if(iterator->second->Bodies()->at(i)->isTrackingTrajectory() == true)
			{
				isTrackingTrajectoryFile << iterator->second->Bodies()->at(i)->ID() << endl;
			}
		}
	}
	isTrackingTrajectoryFile.close();

	m_trajectoriesFile.open(path + trajectoriesFilename);
};
