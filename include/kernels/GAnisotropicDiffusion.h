#ifndef GANISOTROPICDIFFUSION_H
#define GANISOTROPICDIFFUSION_H

#include "Kernel.h"

//Forward Declarations
class GAnisotropicDiffusion;

template<>
InputParameters validParams<GAnisotropicDiffusion>();

class GAnisotropicDiffusion : public Kernel
{
public:
	
	GAnisotropicDiffusion(const InputParameters & parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
	RealTensorValue _Diffusion;
	
	Real _Dxx, _Dxy, _Dxz;
	Real _Dyx, _Dyy, _Dyz;
	Real _Dzx, _Dzy, _Dzz;
	
private:
	
};

#endif //GANISOTROPICDIFFUSION_H