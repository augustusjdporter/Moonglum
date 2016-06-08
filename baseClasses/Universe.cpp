#include "Universe.h"

using namespace std;

Universe::Universe(string simName)
{
	m_name = simName;
	run_on_gpu = true;
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

#ifdef GPU_COMPUTE
	m_allSystems.update_on_gpu(timestep);
#else
	m_allSystems.update_on_cpu(timestep);
#endif

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
}
void Universe::saveState(const string & path, const int & plotNumber, const int & coordNumber, const double& timestep, const int& samplingRate, const double& normalisation)
{
	ofstream saveFile;
	saveFile.open(path + "/saveFile.txt");

	saveFile << "CoordinateSnapshotNumber:\t" << coordNumber << endl;
	saveFile << "PlotNumber:\t" << plotNumber << endl;
	saveFile << "Timestep:\t" << timestep << endl;
	saveFile << "samplingRate:\t" << samplingRate << endl;
	saveFile << "normalisation\t" << normalisation << endl;
	for (auto bodyIter : *m_allSystems.Bodies())
	{
		//if (bodyIter->isValid())
		saveFile << bodyIter->ID() << "\t" << bodyIter->name() << "\t" << bodyIter->mass() << "\t" << bodyIter->radius() << "\t" << bodyIter->relaxation() << "\t" << bodyIter->xPosition() << "\t" << bodyIter->yPosition() << "\t" << bodyIter->zPosition() << "\t" << bodyIter->xVelocity() << "\t" << bodyIter->yVelocity() << "\t" << bodyIter->zVelocity() << "\t" << bodyIter->isTrackingTrajectory() << endl;
	};

	saveFile.close();
	return;

}
bool Universe::loadFromSaveFile(const string & filePath, int& plotNumber, int& coordNumber, int& timestep, int& samplingRate, double& normalisation)
{
	bool result;
	ifstream saveFile;
	saveFile.open(filePath);

	if (saveFile.is_open())
	{
		string dummy;
		saveFile >> dummy >> coordNumber;
		saveFile >> dummy >> plotNumber;
		saveFile >> dummy >> timestep;
		saveFile >> dummy >> samplingRate;
		saveFile >> dummy >> normalisation;

		int ID;
		string name;
		double mass;
		double radius;
		double relaxation;
		double xPosition;
		double yPosition;
		double zPosition;
		double xVelocity;
		double yVelocity;
		double zVelocity;
		bool istracking;

		m_astrophysicalSystems.insert(make_pair("defaultSystem", new System()));

		while (saveFile >> ID >> name >> mass >> radius >> relaxation >> xPosition >> yPosition >> zPosition >> xVelocity >> yVelocity >> zVelocity >> istracking)
		{
			shared_ptr<Body> bodyPtr(new Body(ID, name, mass, radius, relaxation, xPosition, yPosition, zPosition, xVelocity, yVelocity, zVelocity, istracking));
			m_astrophysicalSystems.begin()->second->addBody(bodyPtr);
		};

		result = true;
	}
	else
	{
		result = false;
	};

	return result;
};
