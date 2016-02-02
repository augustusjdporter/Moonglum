#ifndef DARKMATTERHALO_H
#define DARKMATTERHALO_H

#include "../system.h"

class DarkMatterHalo : public System
{
public:
	DarkMatterHalo(const int& numberOfBodies,
				   const double& mass, 
				   const double& xScaleHeight, 
				   const double& yScaleHeight, 
				   const double& zScaleHeight);

	~DarkMatterHalo();
	
private:
	DarkMatterHalo();
};

#endif