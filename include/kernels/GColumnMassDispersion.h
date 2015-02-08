//
//  GColumnMassDispersion.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/15/15.
//
//

#ifndef GCOLUMNMASSDISPERSION_H
#define GCOLUMNMASSDISPERSION_H

#include "GAnisotropicDiffusion.h"

//Forward Declarations
class GColumnMassDispersion;

template<>
InputParameters validParams<GColumnMassDispersion>();

class GColumnMassDispersion : public GAnisotropicDiffusion
{
public:
	
	GColumnMassDispersion(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
	unsigned int _index;
	MaterialProperty<std::vector<Real> > & _dispersion;
	MaterialProperty<std::vector<Real> > & _molecular_diffusion;
};

#endif //GCOLUMNMASSDISPERSION_H
