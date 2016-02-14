//body.h: Defines the Body class, an abstract body which exerts and feels gravitational force.

#ifndef Body_H
#define Body_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>


using namespace std;

class Body
{
 public:

 	//Constructors/destructors
	Body();

	~Body();

	Body(string tempName, 
		 double tempMass,
		 double tempxPosition, 
		 double tempyPosition, 
		 double tempzPosition, 
		 double tempxVelocity, 
		 double tempyVelocity, 
		 double tempzVelocity,
		 double tempRadius,
		 bool	tempLogTrajectory);

	Body(const Body& bodyToCopy); //copy constructor

//Functions to calculate the gravitational acceleration due to other bodies.
	virtual vector<double> accelerationCalc(vector<Body>* Body_Vector);

	virtual vector<double> accelerationCalc(vector<Body*>* Body_Vector);

	//Access functions
	const double xPosition() const;

	const double yPosition() const;

	const double zPosition() const;

	const double xVelocity() const;

	const double yVelocity() const;

	const double zVelocity() const;

	const string name() const;

	const double mass() const;

	virtual const double radius() const;

	const bool isValid() const;

	const double density() const;

	const bool isTrackingTrajectory() const;

	const double relaxation() const;

	const int ID() const;

	//Setting functions
	void set_xPosition(const double& new_xPosition);

	void set_yPosition(const double& new_yPosition);

	void set_zPosition(const double& new_zPosition);

	void set_xVelocity(const double& new_xVelocity);

	void set_yVelocity(const double& new_yVelocity);

	void set_zVelocity(const double& new_zVelocity);

	void set_mass(const double& new_mass);

	void set_Radius(const double& new_Radius);

	void set_isValid(const bool& new_isValid);
	
	//Function to add coordinates to the body's trajectory file
	void addToTrajectory(const string& path);

	



private:

	int 		m_ID;
	string 		m_name;
	double 		m_mass;
	double 		m_xPosition, m_yPosition, m_zPosition;
	double 		m_xVelocity, m_yVelocity, m_zVelocity;
	double 		m_radius;
	double		m_relaxation;
	bool   		m_isValid;	//false if we do not want to use body in acceleration calcs
	bool		m_logTrajectory;
	std::ofstream* 	m_trajectory; //pointer as i was getting weird ass compiler issues if it wasn't...
	
	
};

#endif