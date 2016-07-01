#include "BarnesHutTree3D.h"

BarnesHutTree3D::BarnesHutTree3D() : m_Quadrant(0.0, 0.0, 0.0, 0.0)
{
	m_NW = NULL;
	m_SW = NULL;
	m_NE = NULL;
	m_SE = NULL;

	m_topNW = NULL;
	m_topSW = NULL;
	m_topNE = NULL;
	m_topSE = NULL;
}

BarnesHutTree3D::BarnesHutTree3D(const Quadrant3D quadrant) : m_Quadrant(quadrant)
{
	m_NW = NULL;
	m_SW = NULL;
	m_NE = NULL;
	m_SE = NULL;

	m_topNW = NULL;
	m_topSW = NULL;
	m_topNE = NULL;
	m_topSE = NULL;
}

BarnesHutTree3D::~BarnesHutTree3D()
{
	if (m_NW != NULL)
	{
		delete m_NW;
		m_NW = NULL;
	};
	if (m_SW != NULL)
	{
		delete m_SW;
		m_SW = NULL;
	};
	if (m_NE != NULL)
	{
		delete m_NE;
		m_NE = NULL;
	};
	if (m_SE != NULL)
	{
		delete m_SE;
		m_SE = NULL;
	};

	if (m_topNW != NULL)
	{
		delete m_topNW;
		m_topNW = NULL;
	};
	if (m_topSW != NULL)
	{
		delete m_topSW;
		m_topSW = NULL;
	};
	if (m_topNE != NULL)
	{
		delete m_topNE;
		m_topNE = NULL;
	};
	if (m_topSE != NULL)
	{
		delete m_topSE;
		m_topSE = NULL;
	};
}

void BarnesHutTree3D::insertBody(const Body& body)
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
		m_bodyInTree.set_mass(newMass);
		if (body.isInQuadrant(m_Quadrant.NWQuad()))
		{
			if (!m_NW)
			{
				m_NW = new BarnesHutTree3D(m_Quadrant.NWQuad());
			}
			m_NW->insertBody(body);
		}
		else if (body.isInQuadrant(m_Quadrant.NEQuad()))
		{
			if (!m_NE)
			{
				m_NE = new BarnesHutTree3D(m_Quadrant.NEQuad());
			}
			m_NE->insertBody(body);
		}
		else if (body.isInQuadrant(m_Quadrant.SWQuad()))
		{
			if (!m_SW)
			{
				m_SW = new BarnesHutTree3D(m_Quadrant.SWQuad());
			}
			m_SW->insertBody(body);
		}
		else if (body.isInQuadrant(m_Quadrant.SEQuad()))
		{
			if (!m_SE)
			{
				m_SE = new BarnesHutTree3D(m_Quadrant.SEQuad());
			};
			m_SE->insertBody(body);
		}
		else if (body.isInQuadrant(m_Quadrant.topNWQuad()))
		{
			if (!m_topNW)
			{
				m_topNW = new BarnesHutTree3D(m_Quadrant.topNWQuad());
			}
			m_topNW->insertBody(body);
		}
		else if (body.isInQuadrant(m_Quadrant.topNEQuad()))
		{
			if (!m_topNE)
			{
				m_topNE = new BarnesHutTree3D(m_Quadrant.topNEQuad());
			}
			m_topNE->insertBody(body);
		}
		else if (body.isInQuadrant(m_Quadrant.topSWQuad()))
		{
			if (!m_topSW)
			{
				m_topSW = new BarnesHutTree3D(m_Quadrant.topSWQuad());
			}
			m_topSW->insertBody(body);
		}
		else if (body.isInQuadrant(m_Quadrant.topSEQuad()))
		{
			if (!m_topSE)
			{
				m_topSE = new BarnesHutTree3D(m_Quadrant.topSEQuad());
			};
			m_topSE->insertBody(body);
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
				m_NW = new BarnesHutTree3D(m_Quadrant.NWQuad());
			};
			m_NW->insertBody(m_bodyInTree);
		}
		else if (m_bodyInTree.isInQuadrant(m_Quadrant.NEQuad()))
		{
			if (!m_NE)
			{
				m_NE = new BarnesHutTree3D(m_Quadrant.NEQuad());
			};
			m_NE->insertBody(m_bodyInTree);
		}
		else if (m_bodyInTree.isInQuadrant(m_Quadrant.SWQuad()))
		{
			if (!m_SW)
			{
				m_SW = new BarnesHutTree3D(m_Quadrant.SWQuad());
			};
			m_SW->insertBody(m_bodyInTree);
		}
		else if (m_bodyInTree.isInQuadrant(m_Quadrant.SEQuad()))
		{
			if (!m_SE)
			{
				m_SE = new BarnesHutTree3D(m_Quadrant.SEQuad());
			};
		}
		else if (m_bodyInTree.isInQuadrant(m_Quadrant.topNWQuad()))
		{
			if (!m_topNW)
			{
				m_topNW = new BarnesHutTree3D(m_Quadrant.topNWQuad());
			};
			m_topNW->insertBody(m_bodyInTree);
		}
		else if (m_bodyInTree.isInQuadrant(m_Quadrant.topNEQuad()))
		{
			if (!m_topNE)
			{
				m_topNE = new BarnesHutTree3D(m_Quadrant.topNEQuad());
			};
			m_topNE->insertBody(m_bodyInTree);
		}
		else if (m_bodyInTree.isInQuadrant(m_Quadrant.topSWQuad()))
		{
			if (!m_topSW)
			{
				m_topSW = new BarnesHutTree3D(m_Quadrant.topSWQuad());
			};
			m_topSW->insertBody(m_bodyInTree);
		}
		else if (m_bodyInTree.isInQuadrant(m_Quadrant.topSEQuad()))
		{
			if (!m_topSE)
			{
				m_topSE = new BarnesHutTree3D(m_Quadrant.topSEQuad());
			};
			m_topSE->insertBody(m_bodyInTree);
		}
		insertBody(body);
	}
};

const bool BarnesHutTree3D::isExternal() const
{
	if (!m_NW && !m_NE && !m_SW && !m_SE && !m_topNW && !m_topNE && !m_topSW && !m_topSE)
	{
		return true;
	}
	else
	{
		return false;
	};
}

void BarnesHutTree3D::updateForceOnBody(const shared_ptr<Body>& body) const
{
	if (isExternal())
	{
		body->addToAccelerationDueToOneBody(m_bodyInTree);
	}
	else if (m_Quadrant.sideLength() / body->threeDimensionalDistanceToOtherBody(m_bodyInTree) < 0.5)
	{
		body->addToAccelerationDueToOneBody(m_bodyInTree);
	}
	else
	{
		if (m_NW) m_NW->updateForceOnBody(body);
		if (m_NE) m_NE->updateForceOnBody(body);
		if (m_SW) m_SW->updateForceOnBody(body);
		if (m_SE) m_SE->updateForceOnBody(body);
		if (m_topNW) m_topNW->updateForceOnBody(body);
		if (m_topNE) m_topNE->updateForceOnBody(body);
		if (m_topSW) m_topSW->updateForceOnBody(body);
		if (m_topSE) m_topSE->updateForceOnBody(body);
	}
};
