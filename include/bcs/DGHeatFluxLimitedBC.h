//
//  DGHeatFluxLimitedBC.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#ifndef DGHEATFLUXLIMITEDBC_H
#define DGHEATFLUXLIMITEDBC_H

#include "DGFluxLimitedBC.h"

//Forward Declarations
class DGHeatFluxLimitedBC;

template<>
InputParameters validParams<DGHeatFluxLimitedBC>();

class DGHeatFluxLimitedBC : public DGFluxLimitedBC
{
public:
	DGHeatFluxLimitedBC(const InputParameters & parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
	Real _input_temperature;
	
	const MaterialProperty<Real> & _vel;
	const MaterialProperty<Real> & _gas_density;
	const MaterialProperty<Real> & _gas_heat_capacity;
	const MaterialProperty<Real> & _conductivity;
	
};

#endif //DGHEATFLUXLIMITEDBC_H
