#ifndef DGFLUXBC_H
#define DGFLUXBC_H

#include "IntegratedBC.h"

//libMesh includes
#include "libmesh/vector_value.h"

//Forward Declarations
class DGFluxBC;

template<>
InputParameters validParams<DGFluxBC>();

class DGFluxBC : public IntegratedBC
{
public:
	DGFluxBC(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
	RealVectorValue _velocity;
private:
	Real _vx;
	Real _vy;
	Real _vz;
	
	Real _u_input;
	
};

#endif //DGFLUXBC_H