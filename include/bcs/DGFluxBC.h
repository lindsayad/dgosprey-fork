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
	
	Real _epsilon;
	Real _sigma;
	RealVectorValue _velocity;
	RealTensorValue _Diffusion;
private:
	Real _vx;
	Real _vy;
	Real _vz;
	
	Real _Dxx, _Dxy, _Dxz;
	Real _Dyx, _Dyy, _Dyz;
	Real _Dzx, _Dzy, _Dzz;
	
	Real _u_input;
	
};

#endif //DGFLUXBC_H