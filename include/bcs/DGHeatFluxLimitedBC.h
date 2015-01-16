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
	DGHeatFluxLimitedBC(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
	Real _input_temperature;
	
	MaterialProperty<Real> & _vel;
	MaterialProperty<Real> & _gas_density;
	MaterialProperty<Real> & _gas_heat_capacity;
	MaterialProperty<Real> & _conductivity;
	
};

#endif //DGHEATFLUXLIMITEDBC_H
