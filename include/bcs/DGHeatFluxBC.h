//
//  DGHeatFluxBC.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#ifndef DGHEATFLUXBC_H
#define DGHEATFLUXBC_H

#include "DGFluxBC.h"

//Forward Declarations
class DGHeatFluxBC;

template<>
InputParameters validParams<DGHeatFluxBC>();

class DGHeatFluxBC : public DGFluxBC
{
public:
	DGHeatFluxBC(const InputParameters & parameters);
	
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

#endif //DGHEATFLUXBC_H
