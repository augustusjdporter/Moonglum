#pragma once
#include <iostream>
#include <memory>

using namespace std;
//Class that defines a quadrant on a Barnes-Hut tree
class Quadrant
{
public:
	Quadrant(const double& xMin, const double& yMin, const double& sideLength);

	~Quadrant();

	const double& xMin() const;

	const double& yMin() const;

	const double& sideLength() const;

	//returns true if the given point is in the quadrant.
	const bool isPointInQuadrant(const double& x, const double& y) const;

	const Quadrant NWQuad();

	const Quadrant NEQuad();

	const Quadrant SWQuad();

	const Quadrant SEQuad();

private:
	Quadrant();

	double m_xMin;
	double m_yMin;
	double m_sideLength;
};