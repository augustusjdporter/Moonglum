#include "Universe.h"

using namespace std;

Universe::Universe(string simName)
{
	cout << "Creating universe" << endl;
	m_name = simName;
};

void Universe::addSystem(System* systemToAdd)
{
	m_astrophysicalSystems.insert(make_pair(systemToAdd->name(), systemToAdd));
	return;
};

Universe::~Universe()
{
	cout << "Destroying universe" << endl;

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
	for (SystemMap::iterator iterator1 = m_astrophysicalSystems.begin(); iterator1 != m_astrophysicalSystems.end(); iterator1++)
	{
		for (SystemMap::iterator iterator2 = m_astrophysicalSystems.begin(); iterator2 != m_astrophysicalSystems.end(); iterator2++)
		{
			if(iterator2->first != iterator1->first)
			{
				iterator1->second->addBoundSystem(iterator2->second);
			}
		}
	}
	return;
};

void Universe::updateUniverse(double timestep)
{
	for (SystemMap::iterator iterator = m_astrophysicalSystems.begin(); iterator != m_astrophysicalSystems.end(); iterator++)
	{
		iterator->second->update(timestep);
	}
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