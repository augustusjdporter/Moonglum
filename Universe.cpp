#include "Universe.h"

using namespace std;

void Universe::addSystem(System* systemToAdd)
{
	m_astrophysicalSystems.insert(make_pair(systemToAdd->name(), systemToAdd));
	return;
};

Universe::~Universe()
{
	cout << "Destroying universe" << endl;
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
	for (SystemMap::iterator iterator = m_astrophysicalSystems.begin(); iterator != m_astrophysicalSystems.end(); iterator++)
	{
		iterator->second->printCoordinates(path, filename, normalisation); //Only print coordinates of one system - this takes care of printing all the bound systems of this particular system
		return;
	}
};