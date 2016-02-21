//Main entry point for a simulation of a planetary system.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "baseClasses/body.h"
#include "baseClasses/system.h"
#include "baseClasses/Universe.h"
#include "baseClasses/Constants.h"

#include "Utilities/XmlReader.h"
#include "Utilities/Utilities.h"
#include "Utilities/rapidxml-1.13/rapidxml.hpp" //defines xml config reader
#include "planetary-simulation/ProtoplanetaryCloud.h"
#include "galaxy-simulation/Galaxy.h"
#include "galaxy-simulation/Gas.h"
#include "galaxy-simulation/BlackHole.h"
#include "galaxy-simulation/DarkMatterHalo.h"
#include "galaxy-simulation/Star.h"

using namespace std;

int parsePlanetaryConfig(char* configFile, int* timestep, int* numberOfSteps, int* samplingRate, Universe* simulation_universe);

int parseGalaxyConfig(char* configFile, int* timestep, int* numberOfSteps, int* samplingRate, Universe* simulation_universe);

int main(int argc, char* argv[])
{
	cout << endl;
	cout << "Moonglum by Augustus Porter." << endl;
	cout << "A project to create N-Body simulations on a home PC." << endl;
	cout << "Contact: augustusjdporter@gmail.com" << endl;
	cout << endl;

	const time_t ctt = time(0);
	cout << asctime(localtime(&ctt)) << endl;//output time 
	time_t beginninguni, enduni;

	//Start by checking there are enough command line arguments
	if(argc < 3)
	{
		cout << "Not enough command line arguments. Command line should read:" << endl;
		cout << "./Moonglum [simulation name] [path to config file]" << endl;
		cout << endl;
		return 0;
	}
	else if(argc > 3)
	{
		cout << "Too many command line arguments. Command line should read:" << endl;
		cout << "./Moonglum [simulation name] [path to config file]" << endl;
		cout << endl;
		return 0;
	}

	string simulationName(argv[1]);

	//Define parameters to be filled by the config reader	
	int timestep;
	int numberOfSteps;
	int samplingRate;
	double normalisation;
	
	Universe simulation_universe(simulationName);

	XmlReader configReader;
	int errorHandle = configReader.parseConfig(argv[2], &timestep, &numberOfSteps, &samplingRate, &normalisation, &simulation_universe);
	if (errorHandle == -1)
	{
		cout << "Unable to open config file \"" << string(argv[2]) << "\". Check the path is correct." << endl;
		cout << endl;
		return 0;
	}
	else if (errorHandle == -2)
	{
		cout << "Simulation config is not defined as \"galaxy\" or \"planetary\"." << endl;
		cout << endl;
		return 0;
	}
	else
	{
		cout << "Config parsed successfully!" << endl;
	}

	//Make directory structure
	{
		string galaxy_directory = "galaxy-simulation";
		mkdir(galaxy_directory.c_str(), 0700);
		mkdir((galaxy_directory + "/Coords").c_str(), 0700);

		string planetary_directory = "planetary-simulation";
		mkdir(planetary_directory.c_str(), 0700);
		mkdir((planetary_directory + "/Coords").c_str(), 0700);
	}

	string path = configReader.simulationType() + "-simulation/Coords/" + simulationName + "/";

	mkdir((path).c_str(), 0700);

	mkdir((path + "Snapshots/").c_str(), 0700);

	mkdir((path + "Plots/").c_str(), 0700);

	mkdir((path + "trajectories/").c_str(), 0700);
	
	int j(0), k(0), count(0);

	//gravitationally bind the systems in the universe
	simulation_universe.bindSystems();
	//make the files - one with IDs of bodies which are tracking trajectories, one with the trajectory coordinates
	simulation_universe.makeTrajectoryFiles(path + "trajectories/", simulationName + "_isTrackingTrajectories.txt", simulationName + "_trajectories.txt");
	int thisthing = 1;
	int refresh = samplingRate;
	int printCount = 1;

  	while (thisthing <= numberOfSteps)
  	{
  		beginninguni = time(0);

		simulation_universe.updateUniverse(timestep);

		if(refresh == samplingRate)
		{
			stringstream combiner;
			combiner << "Snapshots/It_" << printCount << ".txt";

			string file_name;
			combiner >> file_name;


			simulation_universe.printCoordinatesToFile(path, file_name, normalisation);
			
			std::string command = "ipython " + configReader.simulationType() + "-simulation/plot-" + configReader.simulationType() + "-simulation.py ";
    		command += simulationName;
    		command += " ";

    		ostringstream convertIntToString;
    		convertIntToString << printCount;

    		
    		command = command + convertIntToString.str();
    		cout << command << endl;
    		cout << endl;
    		system(command.c_str());
    		cout << endl;

			refresh = 0;
			printCount++;

		}

		enduni = time(0);
		cout << "Time taken for step " << thisthing << " (seconds): " << enduni - beginninguni << endl;

		refresh++;
		thisthing++;
	}

	cout << "Simulation is finished! Thank you for using Moonglum!" << endl;
	return 0;
};