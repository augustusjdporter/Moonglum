#include "Quadrant.h"

//Default should never be used
Quadrant::Quadrant()
{
	//cout << "default constructor" << endl;
}

Quadrant::Quadrant(const double & xMin, const double & yMin, const double & sideLength)
	: m_xMin(xMin), m_yMin(yMin), m_sideLength(sideLength)
{
	//std::cout << "Quadrant constructor." << endl;
}

Quadrant::~Quadrant()
{
}

const double & Quadrant::xMin() const
{
	return m_xMin;
}

const double & Quadrant::yMin() const
{
	return m_yMin;
}

const double & Quadrant::sideLength() const
{
	return m_sideLength;
}

const bool Quadrant::isPointInQuadrant(const double & x, const double & y) const
{
	if ((x >= m_xMin) && (x < m_xMin + m_sideLength) && (y >= m_yMin) && (y < m_yMin + m_sideLength))
	{
		return true;
	}
	else
	{
		return false;
	};
}

const Quadrant Quadrant::NWQuad()
{
	return Quadrant(m_xMin, m_yMin+m_sideLength/2, m_sideLength/2);
}

const Quadrant Quadrant::NEQuad()
{
	return Quadrant(m_xMin + m_sideLength / 2, m_yMin + m_sideLength / 2, m_sideLength / 2);
}

const Quadrant Quadrant::SWQuad()
{
	return Quadrant(m_xMin, m_yMin, m_sideLength / 2);
}

const Quadrant Quadrant::SEQuad()
{
	return Quadrant(m_xMin + m_sideLength / 2, m_yMin, m_sideLength / 2);
}
