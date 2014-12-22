#ifndef DGADVECTION_H
#define DGADVECTION_H

#include "DGKernel.h"
#include <cmath>

//Forward Declarations
class DGAdvection;

template<>
InputParameters validParams<DGAdvection>();

class DGAdvection : public DGKernel
{
public:
	DGAdvection(const std::string & name, InputParameters parameters);
	
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

#endif //DGADVECTION_H