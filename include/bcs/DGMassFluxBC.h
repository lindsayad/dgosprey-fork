//
//  DGMassFluxBC.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/15/15.
//
//

#ifndef DGMASSFLUXBC_H
#define DGMASSFLUXBC_H

#include "DGFluxBC.h"

//Forward Declarations
class DGMassFluxBC;

template<>
InputParameters validParams<DGMassFluxBC>();

class DGMassFluxBC : public DGFluxBC
{
public:
	DGMassFluxBC(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
	Real _input_temperature;
	Real _input_pressure;
	Real _input_molefraction;
	
	MaterialProperty<Real> & _vel;
	unsigned int _index;
	MaterialProperty<std::vector<Real> > & _dispersion;
	MaterialProperty<std::vector<Real> > & _molecular_diffusion;
	
};

#endif //DGMASSFLUXBC_H