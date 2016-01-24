//cc SolarSystem.cpp -o SolarSystem -L/usr/lib/ -lcpgplot -lpgplot -lm
//g++ -std=c++0x -O3 -o SolarSystem.out -I. SolarSystem.cpp ../body.cpp ../system.cpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../body.h"
#include "../system.h"
#include "ProtoplanetaryCloud.h"

using namespace std;

int enterInteger();

double enterDouble();

int main()
{
	const double Solar_Mass(1.989*pow(10, 30));
	const double AU(1.4960*pow(10, 11));
	const double timestep(24*3600/5);//day/5 in seconds

	const double solar_radius(6.96*pow(10, 8));
	const double earth_radius(6.37*pow(10, 6));//needs to be updated when have internet
	const double jupiter_radius(6.99*pow(10, 7));

	const time_t ctt = time(0);
	cout << asctime(localtime(&ctt)) << endl;//output time 
	time_t beginninguni, enduni;

	string simulationName;
	cout << "Name the simulation: ";
	cin >> simulationName;
	cout << endl;
	string path = "Coords/" + simulationName + "/";
	const char* directory = (path).c_str();
	mkdir(directory, 0700);

	const char* snapshots_directory = (path + "Snapshots/").c_str();
	mkdir(snapshots_directory, 0700);

	const char* plots_directory = (path + "Plots/").c_str();
	mkdir(plots_directory, 0700);
	
	int j(0), k(0), count(0);



	System solarSystem;

	solarSystem.addBody(new Body("Sun", 1.9891*pow(10, 30), 0, 0, 0, 0, 0, 0, solar_radius, true));
	solarSystem.addBody(new Body("Earth", 5.972*pow(10, 24), 1*AU, 0, 0, 0, 3.3*pow(10,4) , 0, earth_radius, true));
	solarSystem.addBody(new Body("Jupiter", 1.898*pow(10, 27), 5.2*AU, 0, 0, 0, 47.051*pow(10,6)/3600 , 0, jupiter_radius, true));

	ProtoplanetaryCloud cloud(800, 0.01*Solar_Mass, 4*AU, 4*AU, 0.2*AU, 0.0, 0.0);

	cloud.addBoundSystem(&solarSystem);
	solarSystem.addBoundSystem(&cloud);

	int thisthing = 1;
	int refresh = 1;
	int printCount = 1;
	cout << "How many iterations (each iteration is 1/5 day)? ";
	int iterationNumber = enterInteger();
  	while (thisthing <= iterationNumber)
  	{
  		

		solarSystem.update(timestep);
		cloud.update(timestep);

		if(refresh == 90)
		{
			beginninguni = time(0);

			stringstream combiner;
			combiner << "Snapshots/It_" << printCount << ".txt";

			string file_name;
			combiner >> file_name;

			solarSystem.printCoordinates(path, file_name);
			
			std::string command = "ipython plot-planetary-simulation.py ";
    		command += simulationName;
    		command += " ";

    		ostringstream convertIntToString;
    		convertIntToString << printCount;

    		
    		command = command + convertIntToString.str();
    		cout << command << endl;
    		system(command.c_str());

			enduni = time(0);
			cout << "Time taken for step " << thisthing << " (seconds): " << enduni - beginninguni << endl;

			refresh = 0;
			printCount++;

		}
		refresh++;
		thisthing++;

		
	}

	return 0;
}

int enterInteger()//used for every user input number to make sure there is good input. Made a function for convenience.
{
	double number;
	int badCharCount(0);
	bool goodInput(false);
	string temp;
	cin.clear();
	cin.ignore(10000, '\n');
	getline(cin, temp);

	while(goodInput == false)//if success == 1, a good number has been read and will be returned
	{
		if(temp[0] != '0' &&  temp[0] != '1' &&  temp[0] != '2' &&  temp[0] != '3' &&  temp[0] != '4' &&  
		   temp[0] != '5' &&  temp[0] != '6' &&  temp[0] != '7' &&  temp[0] != '8' &&  temp[0] != '9') 
		{
		   	badCharCount++;//first char may be - to denote negative
		}

		for(std::string::size_type i = 1; i < temp.size(); ++i)//loop through all char and make sure they are digits or .
		{
			if(temp[i] != '0' &&  temp[i] != '1' &&  temp[i] != '2' &&  temp[i] != '3' &&  temp[i] != '4' &&  
			   temp[i] != '5' &&  temp[i] != '6' &&  temp[i] != '7' &&  temp[i] != '8' &&  temp[i] != '9') 
			{
				badCharCount++;//this parameter is greater than zero if any bad characters have been input
			}
		}

		if(badCharCount > 0)//if bad input
		{
			cout << temp << " is not an integer; please enter an integer: ";
			getline(cin, temp);
			badCharCount = 0;
		}
		else//if good input
		{
			stringstream string2num;//convert the string to a double
			string2num << temp;
			string2num >> number;
			goodInput = true;
		}
	}
		
	return number;
}

double enterDouble()//used for every user input number to make sure there is good input. Made a function for convenience.
{
	double number;
	int badCharCount(0), pointCount(0);
	bool success(false);
	string temp;
	cin.clear();
	cin.ignore(10000, '\n');
	getline(cin, temp);

	while(success == false)//if success == 1, a good number has been read and will be returned
	{
		if(temp[0] != '-' && temp[0] != '0' &&  temp[0] != '1' &&  temp[0] != '2' &&  temp[0] != '3' &&  temp[0] != '4' &&  
		   temp[0] != '5' &&  temp[0] != '6' &&  temp[0] != '7' &&  temp[0] != '8' &&  temp[0] != '9' &&  temp[0] != '.') badCharCount++;//first char may be - to denote negative
		if(temp[0] == '.')  pointCount++;//used to make sure no more than one . input

		for(std::string::size_type i = 1; i < temp.size(); ++i)//loop through all char and make sure they are digits or .
		{
			if(temp[i] != '0' &&  temp[i] != '1' &&  temp[i] != '2' &&  temp[i] != '3' &&  temp[i] != '4' &&  
			   temp[i] != '5' &&  temp[i] != '6' &&  temp[i] != '7' &&  temp[i] != '8' &&  temp[i] != '9' &&  
			   temp[i] != '.') 
			{
				badCharCount++;//this parameter is greater than zero if any bad characters have been input
			}

			if(temp[i] == '.') pointCount++;//used to make sure no more than one . input

		}
		if(badCharCount > 0 || pointCount > 1)//if bad input
		{
			cout << "Please enter a number: ";
			getline(cin, temp);
			badCharCount = 0;
			pointCount = 0;
		}
		else//if good input
		{
			stringstream string2num;//convert the string to a double
			string2num << temp;
			string2num >> number;
			success = true;
		}
	}
		
	return number;
}