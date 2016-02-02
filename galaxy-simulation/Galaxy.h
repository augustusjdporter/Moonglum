#include "../system.h"

class Galaxy : public System
{
public:
	~Galaxy();

	Galaxy(const int& numberOfStars,
		   const double& massStars,
		   const int& numberOfGas,
		   const double& massGas,
		   const double& massBlackHole,
		   const double& xScaleHeight, 
		   const double& yScaleHeight, 
		   const double& zScaleHeight,
		   const double& velocity,
		   const double& velocityDispersion);
	
private:
	Galaxy();
};