//cc SolarSystem.cpp -o SolarSystem -L/usr/lib/ -lcpgplot -lpgplot -lm
//g++ -std=c++0x -O3 -o SolarSystem.out -I. SolarSystem.cpp ../body.cpp ../system.cpp

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

#include "../body.h"
#include "../system.h"


#include "../Utilities/Utilities.h"
#include "../Utilities/rapidxml-1.13/rapidxml.hpp" //defines xml config reader
#include "ProtoplanetaryCloud.h"

using namespace std;

int parseConfig(char* configFile, int* timestep, int* numberOfSteps, int* samplingRate, vector<System>* systems);

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

	int timestep;
	int numberOfSteps;
	int samplingRate;
	
	
	vector<System> systems;
	//systems.push_back(*solarSystemTemp);
	int errorHandle = parseConfig(argv[2], &timestep, &numberOfSteps, &samplingRate, &systems);
	//solarSystemTemp = NULL;
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

	cout << "systems size " << systems.size() << endl;
	const double Solar_Mass(1.989*pow(10, 30));
	const double AU(1.4960*pow(10, 11));
	const double G(6.67*pow(10, -11));

	const double solar_radius(6.96*pow(10, 8));
	const double earth_radius(6.37*pow(10, 6));//needs to be updated when have internet
	const double jupiter_radius(6.99*pow(10, 7));
	const double solar_mass(1.9891*pow(10, 30));

	const time_t ctt = time(0);
	cout << asctime(localtime(&ctt)) << endl;//output time 
	time_t beginninguni, enduni;

	string simulationName(argv[1]);
	string path = "Coords/" + simulationName + "/";
	const char* directory = (path).c_str();
	mkdir(directory, 0700);

	const char* snapshots_directory = (path + "Snapshots/").c_str();
	mkdir(snapshots_directory, 0700);

	const char* plots_directory = (path + "Plots/").c_str();
	mkdir(plots_directory, 0700);
	
	int j(0), k(0), count(0);

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

		//solarSystem.update(timestep);

		if(refresh == samplingRate)
		{
			if (systems.size() > 0)
			{
				stringstream combiner;
				combiner << "Snapshots/It_" << printCount << ".txt";

				string file_name;
				combiner >> file_name;

			
				systems.at(0).printCoordinates(path, file_name, AU);
				//solarSystem.printCoordinates(path, file_name, AU);
			
				std::string command = "ipython plot-planetary-simulation.py ";
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
int parseConfig(char* configFile, int* timestep, int* numberOfSteps, int* samplingRate, vector<System>* systems)
{
	//Checking file exists
	FILE *file = fopen(configFile, "r");
	if (file == NULL) 
	{
        return -1;
    }
    fclose(file);

    const double Solar_Mass(1.989*pow(10, 30));
	const double AU(1.4960*pow(10, 11));
	const double G(6.67*pow(10, -11));
	const double solar_radius(6.96*pow(10, 8));
	const double earth_radius(6.37*pow(10, 6));//needs to be updated when have internet
	const double jupiter_radius(6.99*pow(10, 7));
	const double solar_mass(1.9891*pow(10, 30));
	const double earth_mass(5.972*pow(10, 24));
	const double secondsInYear(3600*24*365.25);
	
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

	*timestep = atoi(root_node->first_node("timestep")->value());
	*numberOfSteps = atoi(root_node->first_node("numberOfSteps")->value());
	*samplingRate = atoi(root_node->first_node("samplingRate")->value());

	// Iterate over the stars
	for (xml_node<> * star_node = root_node->first_node("Star"); star_node; star_node = star_node->next_sibling("Star"))
	{
		System* solarSystem = new System("tempSystem");

		string starName = star_node->first_attribute("name")->value();
		double starMass = atof(star_node->first_attribute("mass")->value())*solar_mass;
		double starXPos = atof(star_node->first_attribute("x")->value());
		double starYPos = atof(star_node->first_attribute("y")->value());
		double starZPos = atof(star_node->first_attribute("z")->value());
		double starXVel = atof(star_node->first_attribute("xVel")->value());
		double starYVel = atof(star_node->first_attribute("yVel")->value());
		double starZVel = atof(star_node->first_attribute("zVel")->value());
		double starRadius = atof(star_node->first_attribute("radius")->value())*solar_radius;
		bool logStarTrajectory = bool(atof(star_node->first_attribute("logTrajectory")->value()));
		solarSystem->addBody(new Body(starName, 
									  starMass, 
									  starXPos, 
									  starYPos, 
									  starZPos, 
									  starXVel, 
									  starYVel, 
									  starZVel, 
									  starRadius, 
									  logStarTrajectory));

	    for(xml_node<> * planet_node = star_node->first_node("Planet"); planet_node; planet_node = planet_node->next_sibling("Planet"))
	    {
	    	string planetName = planet_node->first_attribute("name")->value();
	    	double orbitalPeriod = atof(planet_node->first_attribute("orbitalPeriod")->value())*secondsInYear;
	    	double orbitalRadius = atof(planet_node->first_attribute("orbitalRadius")->value())*AU;
	    	double inclination = atof(planet_node->first_attribute("inclination")->value());
	    	double planetMass = atof(planet_node->first_attribute("mass")->value())*earth_mass;
			double planetXPos = atof(planet_node->first_attribute("orbitalRadius")->value()) + starXPos;
			double planetYPos = atof(star_node->first_attribute("y")->value());
			double planetZPos = atof(star_node->first_attribute("z")->value());
			double planetXVel = 0;
			double planetYVel = 1/(orbitalPeriod)*(2*M_PI)*orbitalRadius*cos(M_PI*inclination/180);
			double planetZVel = 1/(orbitalPeriod)*(2*M_PI)*orbitalRadius*sin(M_PI*inclination/180);
			double planetRadius = atof(planet_node->first_attribute("radius")->value())*earth_radius;
			bool logPlanetTrajectory = bool(atof(planet_node->first_attribute("logTrajectory")->value()));
	    	//v=wr
	    	//requires further development if the star is moving
	    	solarSystem->addBody(new Body(planetName, 
									 	  planetMass, 
									 	  atof(planet_node->first_attribute("orbitalRadius")->value())*AU, 
									 	  atof(star_node->first_attribute("y")->value()), //place it at same x and y as star. This can be looked into
									 	  atof(star_node->first_attribute("z")->value()), 
									 	  0, 
									 	  planetYVel, 
									 	  planetZVel, 
									 	  planetRadius, 
									 	  logPlanetTrajectory));
	    }

	    systems->push_back(*solarSystem);
	    solarSystem = NULL;
	    for(xml_node<> * cloud_node = star_node->first_node("ProtoplanetaryCloud"); cloud_node; cloud_node = cloud_node->next_sibling("ProtoplanetaryCloud"))
	    {
	    	int numberOfPlanetesimals = atoi(cloud_node->first_attribute("numberOfPlanetesimals")->value());
	    	double cloudMass = atof(cloud_node->first_attribute("mass")->value())*Solar_Mass;
	    	double cloudXCenter = starXPos;
	    	double cloudYCenter = starYPos;
	    	double cloudZCenter = starZPos;
	    	double cloudXScale = atof(cloud_node->first_attribute("xScale")->value())*AU;
	    	double cloudYScale = atof(cloud_node->first_attribute("yScale")->value())*AU;
	    	double cloudZScale = atof(cloud_node->first_attribute("zScale")->value())*AU;
	    	double cloudVelocity = 0;
	    	double cloudDispersion = 0;
	    	systems->push_back(ProtoplanetaryCloud(numberOfPlanetesimals, 
										    	   cloudMass, 
										    	   cloudXCenter, //place it at same x and y as star. This can be looked into
										    	   cloudYCenter, //place it at same x and y as star. This can be looked into
									 	 		   cloudZCenter,  
										    	   cloudXScale, 
										    	   cloudYScale, 
										    	   cloudZScale, 
										    	   cloudVelocity, 
										    	   cloudDispersion));
	    }    
	}
	return 0;
}