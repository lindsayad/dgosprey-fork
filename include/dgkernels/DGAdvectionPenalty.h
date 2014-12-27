#ifndef DGADVECTIONPENALTY_H
#define DGADVECTIONPENALTY_H

#include "DGKernel.h"
#include <cmath>

//Forward Declarations
class DGAdvectionPenalty;

template<>
InputParameters validParams<DGAdvectionPenalty>();

class DGAdvectionPenalty : public DGKernel
{
public:
	DGAdvectionPenalty(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual(Moose::DGResidualType type);
	virtual Real computeQpJacobian(Moose::DGJacobianType type);
	
	RealVectorValue _velocity;	//Vector of velocity
	
private:
	//Dimensional components of velocity vector
	Real _vx;
	Real _vy;
	Real _vz;
};

#endif //DGADVECTIONPENALTY_H