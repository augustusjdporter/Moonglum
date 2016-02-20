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

#include "body.h"
#include "system.h"
#include "Universe.h"
#include "Constants.h"

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
	cout << "NBody simulations by Augustus Porter." << endl;
	cout << endl;
	if(argc < 3)
	{
		cout << "Not enough command line arguments. Command line should read:" << endl;
		cout << "./SolarSystem [simulation name] [path to config file]" << endl;
		cout << endl;
		return 0;
	}
	else if(argc > 3)
	{
		cout << "Too many command line arguments. Command line should read:" << endl;
		cout << "./SolarSystem [simulation name] [path to config file]" << endl;
		cout << endl;
		return 0;
	}

	const time_t ctt = time(0);
	cout << asctime(localtime(&ctt)) << endl;//output time 
	time_t beginninguni, enduni;

	int timestep;
	int numberOfSteps;
	int samplingRate;
	double normalisation;
	
	string simulationName(argv[1]);

	Universe simulation_universe(simulationName); //pass in simulation name
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

	string path = configReader.simulationType() + "-simulation/Coords/" + simulationName + "/";

	const char* directory = (path).c_str();
	mkdir(directory, 0700);

	const char* snapshots_directory = (path + "Snapshots/").c_str();
	mkdir(snapshots_directory, 0700);

	const char* plots_directory = (path + "Plots/").c_str();
	mkdir(plots_directory, 0700);

	const char* traj_directory = (path + "trajectories/").c_str();
	mkdir(traj_directory, 0700);
	
	int j(0), k(0), count(0);

	simulation_universe.bindSystems();
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
    		system(command.c_str());

			refresh = 0;
			printCount++;

		}

		enduni = time(0);
		cout << "Time taken for step " << thisthing << " (seconds): " << enduni - beginninguni << endl;

		refresh++;
		thisthing++;
	}

	return 0;
};