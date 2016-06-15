#include "BarnesHutTree.h"

BarnesHutTree::BarnesHutTree() : m_Quadrant(0.0, 0.0, 0.0)
{
	m_NW = NULL;
	m_SW = NULL;
	m_NE = NULL;
	m_SE = NULL;
}

BarnesHutTree::BarnesHutTree(const Quadrant quadrant) : m_Quadrant(quadrant)
{

}

BarnesHutTree::~BarnesHutTree()
{
	if (m_NW != NULL)
	{
		delete m_NW;
		m_NW = NULL;
	};
	if(m_SW != NULL)
	{
		delete m_SW;
		m_SW = NULL;
	};
	if(m_NE != NULL)
	{
		delete m_NE;
		m_NE = NULL;
	};
	if(m_SE != NULL)
	{
		delete m_SE;
		m_SE = NULL;
	};
}

void BarnesHutTree::insertBody(const Body& body)
{
	//If there's not a body there already, put the body there.
	if (m_bodyInTree.mass() == 0)
	{
		m_bodyInTree.set_mass(body.mass());
		m_bodyInTree.set_xPosition(body.xPosition());
		m_bodyInTree.set_yPosition(body.yPosition());
		m_bodyInTree.set_zPosition(body.zPosition());
	}
	//If there's already a body there, but it's not an external node
	//combine the two bodies and figure out which quadrant of the 
	//tree it should be located in. Then recursively update the nodes below it.
	else if (isExternal() == false)
	{
		double newMass = m_bodyInTree.mass() + body.mass();
		m_bodyInTree.set_xPosition((m_bodyInTree.xPosition()*m_bodyInTree.mass() + body.xPosition()*body.mass()) / newMass);
		m_bodyInTree.set_yPosition((m_bodyInTree.yPosition()*m_bodyInTree.mass() + body.yPosition()*body.mass()) / newMass);
		m_bodyInTree.set_zPosition((m_bodyInTree.zPosition()*m_bodyInTree.mass() + body.zPosition()*body.mass()) / newMass);
		m_bodyInTree.set_mass(m_bodyInTree.mass() + body.mass());
		if (body.isInQuadrant(m_Quadrant.NWQuad()))
		{
			if (!m_NW)
			{
				m_NW = new BarnesHutTree(m_Quadrant.NWQuad());
			}
			m_NW->insertBody(body);
		}
		else if (body.isInQuadrant(m_Quadrant.NEQuad()))
		{
			if (!m_NE)
			{
				m_NE = new BarnesHutTree(m_Quadrant.NEQuad());
			}
			m_NE->insertBody(body);
		}
		else if (body.isInQuadrant(m_Quadrant.SWQuad()))
		{
			if (!m_SW)
			{
				m_SW = new BarnesHutTree(m_Quadrant.SWQuad());	
			}
			m_SW->insertBody(body);
		}
		else if (body.isInQuadrant(m_Quadrant.SEQuad()))
		{
			if (!m_SE)
			{
				m_SE = new BarnesHutTree(m_Quadrant.SEQuad());
			};
			m_SE->insertBody(body);
		};
	}
	//If the node is external and contains another body, create BHTrees
	//where the bodies should go, update the node, and end 
	//(do not do anything recursively)
	else if (isExternal() == true)
	{
		//there is only one body in this tree
		if (m_bodyInTree.isInQuadrant(m_Quadrant.NWQuad()))
		{
			if (!m_NW)
			{
				m_NW = new BarnesHutTree(m_Quadrant.NWQuad());
			};
			m_NW->insertBody(m_bodyInTree);
		}
		else if (m_bodyInTree.isInQuadrant(m_Quadrant.NEQuad()))
		{
			if (!m_NE)
			{
				m_NE = new BarnesHutTree(m_Quadrant.NEQuad());
			};
			m_NE->insertBody(m_bodyInTree);
		}
		else if (m_bodyInTree.isInQuadrant(m_Quadrant.SWQuad()))
		{
			if (!m_SW)
			{
				m_SW = new BarnesHutTree(m_Quadrant.SWQuad());
			};
			m_SW->insertBody(m_bodyInTree);
		}
		else if (m_bodyInTree.isInQuadrant(m_Quadrant.SEQuad()))
		{
			if (!m_SE)
			{
				m_SE = new BarnesHutTree(m_Quadrant.SEQuad());
			};
			m_SE->insertBody(m_bodyInTree);
		}
		insertBody(body);
	}
};

const bool BarnesHutTree::isExternal()
{
	if (!m_NW && !m_NE && !m_SW && !m_SE)
	{
		return true;
	}
	else
	{
		return false;
	};
}
void BarnesHutTree::updateForceOnBody(const shared_ptr<Body>& body)
{
	if (isExternal())
	{
		body->addToAccelerationDueToOneBody(m_bodyInTree);
	}
	else if (m_Quadrant.sideLength() / body->twoDimensionalDistanceToOtherBody(m_bodyInTree) < 2)
	{
		body->addToAccelerationDueToOneBody(m_bodyInTree);
	}
	else
	{
		if (m_NW) m_NW->updateForceOnBody(body);
		if (m_NE) m_NE->updateForceOnBody(body);
		if (m_SW) m_SW->updateForceOnBody(body);
		if (m_SE) m_SE->updateForceOnBody(body);
	}
};
