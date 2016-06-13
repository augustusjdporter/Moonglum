#include "BarnesHutTree.h"

BarnesHutTree::BarnesHutTree() : m_Quadrant(0.0, 0.0, 0.0)
{
}

BarnesHutTree::BarnesHutTree(const Quadrant quadrant) : m_Quadrant(quadrant)
{

}

BarnesHutTree::~BarnesHutTree()
{
}

void BarnesHutTree::insertBody(const shared_ptr<Body> body)
{
	//If there's not a body there already, put the body there.
	if (m_bodiesInTree.size() == 0)
	{
		m_bodiesInTree.push_back(body);
	}
	//If there's already a body there, but it's not an external node
	//combine the two bodies and figure out which quadrant of the 
	//tree it should be located in. Then recursively update the nodes below it.
	else if (hasChildren() == false)
	{
		m_bodiesInTree.push_back(body);

		if (body->isInQuadrant(m_Quadrant.NWQuad()))
		{
			if (m_NW.get() == NULL)
			{
				m_NW.reset(new BarnesHutTree(m_Quadrant.NWQuad()));
			}
			m_NW->insertBody(body);
		}
		else if (body->isInQuadrant(m_Quadrant.NEQuad()))
		{
			if (m_NE.get() == NULL)
			{
				m_NE.reset(new BarnesHutTree(m_Quadrant.NEQuad()));
			}
			m_NE->insertBody(body);
		}
		else if (body->isInQuadrant(m_Quadrant.SWQuad()))
		{
			if (m_SW.get() == NULL)
			{
				m_SW.reset(new BarnesHutTree(m_Quadrant.SWQuad()));	
			}
			m_SW->insertBody(body);
		}
		else if (body->isInQuadrant(m_Quadrant.SEQuad()))
		{
			if (m_SE.get() == NULL)
			{
				m_SE.reset(new BarnesHutTree(m_Quadrant.SEQuad()));
			};
			m_SE->insertBody(body);
		};
	}
	//If the node is external and contains another body, create BHTrees
	//where the bodies should go, update the node, and end 
	//(do not do anything recursively)
	else if (hasChildren() == true)
	{

	}
};

const bool BarnesHutTree::hasChildren()
{
	if (m_NW.get() == NULL && m_NE.get() == NULL && m_SW.get() == NULL && m_SE.get() == NULL)
	{
		return false;
	}
	else
	{
		return true;
	};
}
;
