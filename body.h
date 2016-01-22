#ifndef Body_H // Will only be true the once!
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
		 bool	tempLogTrajectory);

	Body(const Body& bodyToCopy); //copy constructor

	const double xPosition() const;

	const double yPosition() const;

	const double zPosition() const;

	const double xVelocity() const;

	const double yVelocity() const;

	const double zVelocity() const;

	void set_xPosition(const double& new_xPosition);

	void set_yPosition(const double& new_yPosition);

	void set_zPosition(const double& new_zPosition);

	void set_xVelocity(const double& new_xVelocity);

	void set_yVelocity(const double& new_yVelocity);

	void set_zVelocity(const double& new_zVelocity);

	const string name() const;

	const double mass() const;

	void set_mass(const double& new_mass);

	void set_Radius(const double& new_Radius);

	const double radius() const;

	virtual vector<double> accelerationCalc(vector<Body>* Body_Vector);

	virtual vector<double> accelerationCalc(vector<Body*>* Body_Vector);

	const bool isValid() const;

	void set_isValid(const bool& new_isValid);

	const double density() const;

	const bool isTrackingTrajectory() const;

	void addToTrajectory(const string& path);



private:

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