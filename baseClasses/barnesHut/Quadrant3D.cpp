#include "Quadrant3D.h"

//Default should never be used
Quadrant3D::Quadrant3D()
{
	//cout << "default constructor" << endl;
}

Quadrant3D::Quadrant3D(const double & xMin, const double & yMin, const double& zMin, const double & sideLength)
	: m_xMin(xMin), m_yMin(yMin), m_zMin(zMin), m_sideLength(sideLength)
{
	//std::cout << "Quadrant constructor." << endl;
}

Quadrant3D::~Quadrant3D()
{
}

const double & Quadrant3D::xMin() const
{
	return m_xMin;
}

const double & Quadrant3D::yMin() const
{
	return m_yMin;
}

const double & Quadrant3D::zMin() const
{
	return m_zMin;
}

const double & Quadrant3D::sideLength() const
{
	return m_sideLength;
}

const bool Quadrant3D::isPointInQuadrant(const double & x, const double & y, const double& z) const
{
	if ((x >= m_xMin) && (x < m_xMin + m_sideLength) && (y >= m_yMin) && (y < m_yMin + m_sideLength) && (z >= m_zMin) && (z < m_zMin + m_sideLength))
	{
		return true;
	}
	else
	{
		return false;
	};
}

const Quadrant3D Quadrant3D::NWQuad()
{
	return Quadrant3D(m_xMin, m_yMin + m_sideLength / 2, m_zMin, m_sideLength / 2);
}

const Quadrant3D Quadrant3D::NEQuad()
{
	return Quadrant3D(m_xMin + m_sideLength / 2, m_yMin + m_sideLength / 2, m_zMin, m_sideLength / 2);
}

const Quadrant3D Quadrant3D::SWQuad()
{
	return Quadrant3D(m_xMin, m_yMin, m_zMin, m_sideLength / 2);
}

const Quadrant3D Quadrant3D::SEQuad()
{
	return Quadrant3D(m_xMin + m_sideLength / 2, m_yMin, m_zMin, m_sideLength / 2);
}

const Quadrant3D Quadrant3D::topNWQuad()
{
	return Quadrant3D(m_xMin, m_yMin + m_sideLength / 2, m_zMin + m_sideLength/2, m_sideLength / 2);
}

const Quadrant3D Quadrant3D::topNEQuad()
{
	return Quadrant3D(m_xMin + m_sideLength / 2, m_yMin + m_sideLength / 2, m_zMin + m_sideLength / 2, m_sideLength / 2);
}

const Quadrant3D Quadrant3D::topSWQuad()
{
	return Quadrant3D(m_xMin, m_yMin, m_zMin + m_sideLength / 2, m_sideLength / 2);
}

const Quadrant3D Quadrant3D::topSEQuad()
{
	return Quadrant3D(m_xMin + m_sideLength / 2, m_yMin, m_zMin + m_sideLength / 2, m_sideLength / 2);
}