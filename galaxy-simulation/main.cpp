//g++ -std=c++11 -O3 -o NBody.out -I. NBody.cpp body.cpp


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

#include "DarkMatterHalo.h"
#include "Gas.h"
#include "BlackHole.h"
#include "Star.h"
#include "Galaxy.h"

//typedef

using namespace std;

int enterInteger();

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

	const char* plots_directory = (path + "Plots/").c_str();
	mkdir(plots_directory, 0700);


	cout << "Enter number of star bodies: ";
	int star_number = enterInteger();

	cout << "Enter number of gas bodies: ";
	int gas_number = enterInteger();

	cout << "Enter number of dark matter bodies: ";
	int darkMatter_number = enterInteger();

	cout << "Enter number of iterations to take: ";
	int iteration_number = enterInteger();


	cout << "Enter timestep (years): ";
	int years_number = enterInteger();


	const time_t ctt = time(0);
	cout << asctime(localtime(&ctt)) << endl;//output time 
	time_t beginninguni, enduni;

	const double kPc(3.0857*pow(10, 15));
	const double Solar_Mass(1.989*pow(10, 30));
	const double year(3600*365.25);
	const double timestep(years_number*year);//year in seconds

	Galaxy simGalaxy(star_number, 100*pow(10,9)*Solar_Mass, //stars
					 gas_number, 3*pow(10, 9)*Solar_Mass, //gas
					 4.6*pow(10, 6)*Solar_Mass, //mass of BH
					 8*kPc, 8*kPc, 1*kPc, //x,y,z
					 180000, 1*pow(10,5));// velocity and dispersion

	DarkMatterHalo simHalo(darkMatter_number, 1*pow(10, 12)*Solar_Mass, 50*kPc, 50*kPc, 50*kPc);

	simGalaxy.addBoundSystem(&simHalo);

	for (int j = 0; j < iteration_number; j++)
	{
		beginninguni = time(0);

		simGalaxy.update(timestep);

		stringstream combiner;
		combiner << "Snapshots/It_" << j << ".txt";

		string file_name;
		combiner >> file_name;

		simGalaxy.printCoordinates(path, file_name, kPc);
			
		std::string command = "ipython plot-galaxy-simulation.py ";
    	command += simulationName;
    	command += " ";

    	ostringstream convertIntToString;
    	convertIntToString << j;

    		
    	command = command + convertIntToString.str();
    	cout << command << endl;
    	system(command.c_str());

    	enduni = time(0);
		cout << "Time taken for this universe (seconds): " << enduni - beginninguni << endl;
	}

	return 0;
}

int enterInteger()//used for every user input number to make sure there is good input. Made a function for convenience.
{
	double number;
	int badCharCount(0);
	bool goodInput(false);
	string temp;
	//cin.clear();
	//cin.ignore(10000, '\n');
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