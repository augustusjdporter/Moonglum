#pragma once
#include <vector>
#include <vexcl/vexcl.hpp>

VEX_FUNCTION(cl_double3, calculate_acceleration, (size_t, n)(size_t, i)(double*, m)(cl_double3*, q),
	const double G = 6.67e-11;
const double relax = 0.2*6.99e7;
double4 sum = { 0.0, 0.0, 0.0, 0.0 };

	double4 q_i = q[i];

	for (size_t j = 0; j < n; ++j) 
	{

		//if (j == i) continue;

		double m_j = m[j];

		double4 d = q[j] - q_i;

		double r = length(d);

		sum += G * m_j * d / (r * r * r + relax);

	}
return sum;
);