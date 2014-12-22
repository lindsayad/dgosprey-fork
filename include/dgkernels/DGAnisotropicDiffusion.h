#ifndef DGANISOTROPICDIFFUSION_H
#define DGANISOTROPICDIFFUSION_H

#include "DGKernel.h"
#include <cmath>

//Forward Declarations
class DGAnisotropicDiffusion;

template<>
InputParameters validParams<DGAnisotropicDiffusion>();

class DGAnisotropicDiffusion : public DGKernel
{
public:
	DGAnisotropicDiffusion(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual(Moose::DGResidualType type);
	virtual Real computeQpJacobian(Moose::DGJacobianType type);
	
	Real _epsilon;
	Real _sigma;
	RealTensorValue _Diffusion;
	
private:
	Real _Dxx, _Dxy, _Dxz;
	Real _Dyx, _Dyy, _Dyz;
	Real _Dzx, _Dzy, _Dzz;
};

#endif //DGANISOTROPICDIFFUSION_H