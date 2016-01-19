//cc SolarSystem.cpp -o SolarSystem -L/usr/lib/ -lcpgplot -lpgplot -lm
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "../body.h"
#include "../system.h"

using namespace std;

int main()
{
	const double AU(1.4960*pow(10, 11));
	const double timestep(24*3600/4);//day/16 in seconds
	int j(0), k(0), count(0);
	System solarSystem;

	solarSystem.addBody(new Body("Sun", 1.9891*pow(10, 30), 0, 0, 0, 0, 0, 0));
	//solarSystem.addBody(new Body("Sun", 1.9891*pow(10, 30), -0.1, 0, 0, 0, -3.3*pow(10,2), 0));
	solarSystem.addBody(new Body("Earth", 5.972*pow(10, 24), 1*AU, 0, 0, 0, 3.3*pow(10,4) , 0));
//	solarSystem.addBody(new Body("Jupiter", 1.898*pow(10, 24), 5.2*AU, 0, 0, 0, 47.051*pow(10,6)/3600 , 0));

int thisthing = 1;
int refresh = 1;
int printCount = 1;
  	while (thisthing <= 365*4)
  	{
		solarSystem.update(timestep);

		if(refresh == 4)
		{
			stringstream combiner;
			combiner << "Coords/It_" << printCount << ".txt";
			string file_name;
			combiner >> file_name;
			solarSystem.printCoordinates(file_name);
			refresh = 0;
			printCount++;
		}
		refresh++;
		thisthing++;
	}

	return 0;
}