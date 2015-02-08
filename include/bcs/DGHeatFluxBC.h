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
	DGHeatFluxBC(const std::string & name, InputParameters parameters);
	
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

#endif //DGHEATFLUXBC_H
