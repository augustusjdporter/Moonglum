#pragma once
#include <iostream>
#include <memory>

using namespace std;
//Class that defines a quadrant on a Barnes-Hut tree
class Quadrant3D
{
public:
	Quadrant3D(const double& xMin, const double& yMin, const double& zMin, const double& sideLength);

	~Quadrant3D();

	const double& xMin() const;

	const double& yMin() const;

	const double& zMin() const;

	const double& sideLength() const;

	//returns true if the given point is in the quadrant.
	const bool isPointInQuadrant(const double& x, const double& y, const double& z) const;

	//Regular ones are bottom
	const Quadrant3D NWQuad();

	const Quadrant3D NEQuad();

	const Quadrant3D SWQuad();

	const Quadrant3D SEQuad();


	const Quadrant3D topNWQuad();

	const Quadrant3D topNEQuad();

	const Quadrant3D topSWQuad();

	const Quadrant3D topSEQuad();

private:
	Quadrant3D();

	double m_xMin;
	double m_yMin;
	double m_zMin;
	double m_sideLength;
};