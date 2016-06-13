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

	void insertBody(const shared_ptr<Body> body);

	const bool hasChildren();

private:
	vector<shared_ptr<Body>>				m_bodiesInTree; //Bodies in the tree
	Quadrant					m_Quadrant; //Square region of the tree
	unique_ptr<BarnesHutTree>	m_NW;
	unique_ptr<BarnesHutTree>	m_NE;
	unique_ptr<BarnesHutTree>	m_SW;
	unique_ptr<BarnesHutTree>	m_SE;

};