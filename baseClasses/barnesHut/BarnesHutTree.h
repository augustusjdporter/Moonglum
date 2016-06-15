#pragma once
#include <vector>

#include "../body.h"
#include "Quadrant.h"

using namespace std;

class BarnesHutTree
{
public:
	BarnesHutTree();

	BarnesHutTree(const Quadrant quadrant);

	~BarnesHutTree();

	void insertBody(const Body& body);

	const bool isExternal();

	void updateForceOnBody(const shared_ptr<Body>& body);

private:
	Body				m_bodyInTree; //Body in the tree. either single body or aggregate
	Quadrant					m_Quadrant; //Square region of the tree
	BarnesHutTree*	m_NW;
	BarnesHutTree*	m_NE;
	BarnesHutTree*	m_SW;
	BarnesHutTree*	m_SE;

};