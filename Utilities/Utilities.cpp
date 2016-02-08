#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "Utilities.h"

using namespace std;

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
};