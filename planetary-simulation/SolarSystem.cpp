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

	const double AU(1.4960*pow(10, 11));
	const double timestep(24*3600/100);//day/16 in seconds
	int j(0), k(0), count(0);



	System solarSystem;

	solarSystem.addBody(new Body("Sun", 1.9891*pow(10, 30), 0, 0, 0, 0, 0, 0, true));
	solarSystem.addBody(new Body("Earth", 5.972*pow(10, 24), 1*AU, 0, 0, 0, 3.3*pow(10,4) , 0, true));
	solarSystem.addBody(new Body("Jupiter", 1.898*pow(10, 24), 5.2*AU, 0, 0, 0, 47.051*pow(10,6)/3600 , 0, true));

	int thisthing = 1;
	int refresh = 1;
	int printCount = 1;
	cout << "How many iterations? ";
	int iterationNumber = enterInteger();
  	while (thisthing <= iterationNumber)
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

double enterNumber()//used for every user input number to make sure there is good input. Made a function for convenience.
{
	double number;
	int badCharCount(0), success(0), pointCount(0);
	string temp;
	cin.clear();
	cin.ignore(10000, '\n');
	getline(cin, temp);

	while(success == 0)//if success == 1, a good number has been read and will be returned
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
		if(badCharCount>0 || pointCount>1)//if bad input
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
			success++;
		}
	}
		
	return number;
}