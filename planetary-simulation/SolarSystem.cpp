//cc SolarSystem.cpp -o SolarSystem -L/usr/lib/ -lcpgplot -lpgplot -lm
//g++ -std=c++0x -O3 -o SolarSystem.out -I. SolarSystem.cpp ../body.cpp ../system.cpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../body.h"
#include "../system.h"

using namespace std;

int main()
{
	string simulationName;
	cout << "Name the simulation: ";
	cin >> simulationName;
	cout << endl;
	string path = "Coords/" + simulationName + "/";
	const char* directory = (path).c_str();
	mkdir(directory, 0700);

	const char* snapshots_directory = (path + "Snapshots/").c_str();
	mkdir(snapshots_directory, 0700);

	const double AU(1.4960*pow(10, 11));
	const double timestep(24*3600/20);//day/16 in seconds
	int j(0), k(0), count(0);
	System solarSystem;

	solarSystem.addBody(new Body("Sun", 1.9891*pow(10, 30), 0, 0, 0, 0, 0, 0, true));
	///solarSystem.addBody(new Body("Sun", 1.9891*pow(10, 30), -0.1, 0, 0, 0, -3.3*pow(10,2), 0));
	solarSystem.addBody(new Body("Earth", 5.972*pow(10, 24), 1*AU, 0, 0, 0, 3.3*pow(10,4) , 0, true));
	solarSystem.addBody(new Body("Jupiter", 1.898*pow(10, 24), 5.2*AU, 0, 0, 0, 47.051*pow(10,6)/3600 , 0, true));

int thisthing = 1;
int refresh = 1;
int printCount = 1;
  	while (thisthing <= 365*120)
  	{
		solarSystem.update(timestep);

		if(refresh == 80)
		{
			stringstream combiner;
			combiner << "Snapshots/It_" << printCount << ".txt";
			string file_name;
			combiner >> file_name;
			solarSystem.printCoordinates(path, file_name);
			refresh = 0;
			printCount++;
		}
		refresh++;
		thisthing++;
	}

	return 0;
}