
#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <cmath>
#endif

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
#include <thread>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef __linux__ 
#include <unistd.h>
#endif
#include <time.h>

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

#ifdef _WIN32
#include <Windows.h>

void mkdir(const char* directory, const int code)
{
	CreateDirectory(directory, NULL);
};
#endif

using namespace std;

int main(int argc, char* argv[])
{

	cout << " __  __                    ____ _                 " << endl;
	cout << "|  \\/  | ___   ___  _ __  / ___| |_   _ _ __ ___  " << endl;
	cout << "| |\\/| |/ _ \\ / _ \\| '_ \\| |  _| | | | | '_ ` _ \\ " << endl;
	cout << "| |  | | (_) | (_) | | | | |_| | | |_| | | | | | |" << endl;
	cout << "|_|  |_|\\___/ \\___/|_| |_|\\____|_|\\__,_|_| |_| |_|" << endl;
	cout << endl;
	cout << "Moonglum by Augustus Porter." << endl;
	cout << "A project to create N-Body simulations on a home PC." << endl;
	cout << "Contact: augustusjdporter@gmail.com" << endl;
	cout << endl;
	cout << "Github: https://github.com/augustusjdporter/Moonglum" << endl;
	cout << endl;
	
	const time_t ctt = time(0);
	cout << asctime(localtime(&ctt)) << endl;//output time 

	
	time_t beginninguni, enduni;

	//Start by checking there are enough command line arguments
	if(argc < 2)
	{
		cout << "Too few command line arguments. Command line should read:" << endl;
		cout << "\t./Moonglum [simulation name] [path to config file]" << endl;
		cout << "when starting a new simulation; or:" << endl;
		cout << "\t./Moonglum [simulation name]" << endl;
		cout << "when resuming a simulation from the last save state." << endl;
		cout << endl;
		return 0;
	}
	else if(argc > 3)
	{
		cout << "Too many command line arguments. Command line should read:" << endl;
		cout << "\t./Moonglum [simulation name] [path to config file]" << endl;
		cout << "when starting a new simulation; or:" << endl;
		cout << "\t./Moonglum [simulation name]" << endl;
		cout << "when resuming a simulation from the last save state." << endl;
		cout << endl;
		return 0;
	};

	string simulationName(argv[1]);

	//Define parameters to be filled by the config reader	
	int timestep(0);
	int numberOfSteps(0);
	int samplingRate(0);
	double normalisation(0);
	
	Universe simulation_universe(simulationName);
	
	string path;
	int stepCount(1);
	int plotNumber(0);
	string simulationType;
	if (argc == 3) //starting new simulation
	{
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

		simulationType = configReader.simulationType();
		path = configReader.simulationType() + "-simulation/Coords/" + simulationName + "/";

		//make the files - one with IDs of bodies which are tracking trajectories, one with the trajectory coordinates
	}
	else if (argc == 2) //loading simulation from save state
	{
		path = path = "planetary-simulation/Coords/" + simulationName + "/";
		if (!simulation_universe.loadFromSaveFile("planetary-simulation/Coords/" + simulationName + "/saveFile.txt", plotNumber, stepCount, timestep, samplingRate, normalisation))
		{
			cout << "No saveFile in simulation " << simulationName << " exists! Cannot resume simulation." << endl;
			return 0;
		}
		simulationType = "planetary";

		cout << "How many more timesteps? ";
		cin >> numberOfSteps;
		numberOfSteps = stepCount + numberOfSteps; //Need to take account of the steps which have already happened, then add our new steps on top.
	};

	//Make directory structure
	{
		string galaxy_directory = "galaxy-simulation";
		mkdir(galaxy_directory.c_str(), 0700);
		mkdir((galaxy_directory + "/Coords").c_str(), 0700);

		string planetary_directory = "planetary-simulation";
		mkdir(planetary_directory.c_str(), 0700);
		mkdir((planetary_directory + "/Coords").c_str(), 0700);
	}

	mkdir((path).c_str(), 0700);

	mkdir((path + "Snapshots/").c_str(), 0700);

	mkdir((path + "Plots/").c_str(), 0700);

	mkdir((path + "trajectories/").c_str(), 0700);

	if (argc == 3)
	{
		simulation_universe.makeTrajectoryFiles(path + "trajectories/", simulationName + "_isTrackingTrajectories.txt", simulationName + "_trajectories.txt");
	}
	
	int j(0), k(0), count(0);

	//gravitationally bind the systems in the universe
	simulation_universe.bindSystems();
	
	int refresh = samplingRate; //when refresh = samplingRate, we take a snapshot

  	while (stepCount <= numberOfSteps)
  	{
  		beginninguni = time(0);
		int start_s = clock();
		simulation_universe.updateUniverse(timestep);

		stringstream combiner;
		combiner << "Snapshots/It_" << stepCount << ".txt";

		string file_name;
		combiner >> file_name;


		//simulation_universe.printCoordinatesToFile(path, file_name, normalisation);

		if(refresh == samplingRate)
		{
			
			
			std::string command = "ipython " + simulationType + "-simulation/plot-" + simulationType + "-simulation.py ";
    		command += simulationName;
    		command += " ";

    		ostringstream convertIntToString;
    		convertIntToString << stepCount;
	
    		command = command + convertIntToString.str() + " ";

			convertIntToString.str(std::string());

			convertIntToString << plotNumber;

			command = command + convertIntToString.str();
    		
    		cout << endl;

			//Call python plotting on command line. result is currently unused
			auto run_python_command = [&]()
			{
				cout << command << endl;
				int result = system(command.c_str());
			};

			simulation_universe.saveState(path, plotNumber, stepCount, timestep, samplingRate, normalisation);
			simulation_universe.printCoordinatesToFile(path, file_name, normalisation);
			std::thread(run_python_command).detach();
    		
    		cout << endl;

			refresh = 0;
			plotNumber++;

		}

		enduni = time(0);
		int stop_s = clock();
		cout << "Time taken for step " << stepCount << " (seconds): " << enduni - beginninguni << endl;
		cout << "ms: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;

		refresh++;
		stepCount++;
	}

	cout << "Simulation is finished! Thank you for using Moonglum!" << endl;
	return 0;
};
