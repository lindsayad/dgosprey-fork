//
//  DGMassFluxLimitedBC.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/15/15.
//
//

#ifndef DGMASSFLUXLIMITEDBC_H
#define DGMASSFLUXLIMITEDBC_H

#include "DGFluxLimitedBC.h"

//Forward Declarations
class DGMassFluxLimitedBC;

template<>
InputParameters validParams<DGMassFluxLimitedBC>();

class DGMassFluxLimitedBC : public DGFluxLimitedBC
{
public:
	DGMassFluxLimitedBC(const InputParameters & parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
	Real _input_temperature;
	Real _input_pressure;
	Real _input_molefraction;
	
	const MaterialProperty<Real> & _vel;
	unsigned int _index;
	const MaterialProperty<std::vector<Real> > & _dispersion;
	const MaterialProperty<std::vector<Real> > & _molecular_diffusion;
	
};

#endif //DGMASSFLUXLIMITEDBC_H