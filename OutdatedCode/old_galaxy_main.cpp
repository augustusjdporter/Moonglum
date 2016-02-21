//main entry point for a galaxy simulation


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <utility>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../body.h"
#include "../system.h"

#include "../Utilities/Utilities.h"
#include "../Utilities/rapidxml-1.13/rapidxml.hpp" //defines xml config reader

#include "DarkMatterHalo.h"
#include "Gas.h"
#include "BlackHole.h"
#include "Star.h"
#include "Galaxy.h"

//typedef

using namespace std;

int parseConfig(char* configFile, int* timestep, int* numberOfSteps, int* samplingRate, System* loneBodies, vector<System>* systems);

int main(int argc, char* argv[])
{

	cout << endl;
	cout << "NBody simulations by Augustus Porter." << endl;
	cout << endl;
	if(argc < 3)
	{
		cout << "Not enough command line arguments. Command line should read:" << endl;
		cout << "./GalaxySim [simulation name] [path to config file]" << endl;
		cout << endl;
		return 0;
	}
	else if(argc > 3)
	{
		cout << "Too many command line arguments. Command line should read:" << endl;
		cout << "./GalaxySim [simulation name] [path to config file]" << endl;
		cout << endl;
		return 0;
	}

	vector<System> systems;
	System loneBodies;
	int timestep;
	int numberOfSteps;
	int samplingRate;
	int errorHandle = parseConfig(argv[2], &timestep, &numberOfSteps, &samplingRate, &loneBodies, &systems);
	if (errorHandle == -1)
	{
		cout << "Unable to open config file \"" << string(argv[2]) << "\". Check the path is correct." << endl;
		cout << endl;
		return 0;
	}
	else
	{
		cout << "Config parsed successfully!" << endl;
	}
	cout << "timetep: " << timestep << endl;
	cout << "number: " << numberOfSteps << endl;
	cout << "samplingRate: " << samplingRate << endl;
	string simulationName(argv[1]);

	string path = "Coords/" + simulationName + "/";
	const char* directory = (path).c_str();
	mkdir(directory, 0700);

	const char* snapshots_directory = (path + "Snapshots/").c_str();
	mkdir(snapshots_directory, 0700);

	const char* plots_directory = (path + "Plots/").c_str();
	mkdir(plots_directory, 0700);

	const time_t ctt = time(0);
	cout << asctime(localtime(&ctt)) << endl;//output time 
	time_t beginninguni, enduni;

	const double kPc(3.0857*pow(10, 15));
	const double Solar_Mass(1.989*pow(10, 30));
	const double year(3600*365.25);
	//const double timestep(years_number*year);//year in seconds

	

	


	for (int i = 0; i < systems.size(); i++)
	{
		for (int j = 0; j < systems.size(); j++)
		{
			if (i == j) continue;
			systems.at(i).addBoundSystem(&systems.at(j));
		}
	}

	int thisthing = 1;
	int refresh = samplingRate;
	int printCount = 1;

  	while (thisthing <= numberOfSteps)
  	{
  		beginninguni = time(0);

		for (int i = 0; i < systems.size(); i++)
		{
			systems.at(i).update(timestep);
		}

		if(refresh == samplingRate)
		{
			if (systems.size() > 0)
			{
				stringstream combiner;
				combiner << "Snapshots/It_" << printCount << ".txt";

				string file_name;
				combiner >> file_name;

			
				systems.at(0).printCoordinates(path, file_name, kPc);
			
				std::string command = "ipython plot-galaxy-simulation.py ";
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

		}

		enduni = time(0);
		cout << "Time taken for step " << thisthing << " (seconds): " << enduni - beginninguni << endl;

		refresh++;
		thisthing++;
	}

	return 0;
}

using namespace rapidxml;
int parseConfig(char* configFile, int* timestep, int* numberOfSteps, int* samplingRate, System* loneBodies, vector<System>* systems)
{
	//Checking file exists
	FILE *file = fopen(configFile, "r");
	if (file == NULL) 
	{
        return -1;
    }
    fclose(file);

	const double AU(1.4960*pow(10, 11));
	const double G(6.67*pow(10, -11));
	const double solar_radius(6.96*pow(10, 8));
	const double earth_radius(6.37*pow(10, 6));//needs to be updated when have internet
	const double jupiter_radius(6.99*pow(10, 7));
	const double solar_mass(1.9891*pow(10, 30));
	const double earth_mass(5.972*pow(10, 24));
	const double secondsInYear(3600*24*365.25);

	const double kPc(3.0857*pow(10, 15));
	const double Solar_Mass(1.989*pow(10, 30));
	
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile (configFile);

	cout << "Parsing " << string(configFile) << "..." << endl;
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("SimulationProfile");

	*timestep = atoi(root_node->first_node("timestep")->value())*secondsInYear;
	*numberOfSteps = atoi(root_node->first_node("numberOfSteps")->value());
	*samplingRate = atoi(root_node->first_node("samplingRate")->value());

	for (xml_node<> * galaxy_node = root_node->first_node("Galaxy"); galaxy_node; galaxy_node = galaxy_node->next_sibling("Star"))
	{
		int numberOfStars = atoi(galaxy_node->first_attribute("numberOfStars")->value());
		double massOfStars = atof(galaxy_node->first_attribute("massOfStars")->value())*solar_mass;
		int numberOfGas = atoi(galaxy_node->first_attribute("numberOfGas")->value());
		double massOfGas = atof(galaxy_node->first_attribute("massOfGas")->value())*solar_mass;
		double massOfBH = atof(galaxy_node->first_attribute("massBlackHole")->value())*solar_mass;
		double xScale = atof(galaxy_node->first_attribute("xScale")->value())*kPc;
		double yScale = atof(galaxy_node->first_attribute("yScale")->value())*kPc;
		double zScale = atof(galaxy_node->first_attribute("zScale")->value())*kPc;
		double velocity = atof(galaxy_node->first_attribute("velocity")->value());
		double dispersion = atof(galaxy_node->first_attribute("dispersion")->value());

		systems->push_back(Galaxy(numberOfStars,
								  massOfStars, //stars
					 			  numberOfGas, 
					 			  numberOfGas, //gas
					 			  massOfBH, //mass of BH
					 			  xScale, 
					 			  yScale, 
					 			  zScale, //x,y,z
					 			  velocity, 
					 			  dispersion));// velocity and dispersion
	}

	for (xml_node<> * darkMatter_node = root_node->first_node("DarkMatterHalo"); darkMatter_node; darkMatter_node = darkMatter_node->next_sibling("Star"))
	{
		int numberOfDM = atoi(darkMatter_node->first_attribute("numberOfDM")->value());
		double massOfDM = atof(darkMatter_node->first_attribute("massOfDM")->value())*solar_mass;
		double xScale = atof(darkMatter_node->first_attribute("xScale")->value())*kPc;
		double yScale = atof(darkMatter_node->first_attribute("yScale")->value())*kPc;
		double zScale = atof(darkMatter_node->first_attribute("zScale")->value())*kPc;
		systems->push_back(DarkMatterHalo(numberOfDM, massOfDM, xScale, yScale, zScale));
	}
	return 0;
}
