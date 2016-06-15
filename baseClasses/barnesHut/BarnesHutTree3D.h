#pragma once
#include <vector>

#include "../body.h"
#include "Quadrant3D.h"

using namespace std;

class BarnesHutTree3D
{
public:
	BarnesHutTree3D();

	BarnesHutTree3D(const Quadrant3D quadrant);

	~BarnesHutTree3D();

	void insertBody(const Body& body);

	const bool isExternal() const;

	void updateForceOnBody(const shared_ptr<Body>& body) const;

private:
	Body				m_bodyInTree; //Body in the tree. either single body or aggregate
	Quadrant3D					m_Quadrant; //Square region of the tree

	//bottom not labeled
	BarnesHutTree3D*	m_NW;
	BarnesHutTree3D*	m_NE;
	BarnesHutTree3D*	m_SW;
	BarnesHutTree3D*	m_SE;

	BarnesHutTree3D*	m_topNW;
	BarnesHutTree3D*	m_topNE;
	BarnesHutTree3D*	m_topSW;
	BarnesHutTree3D*	m_topSE;

};