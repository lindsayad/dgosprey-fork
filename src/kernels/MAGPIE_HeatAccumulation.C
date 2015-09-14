//----------------------------------------
//  Created by Austin Ladshaw on 09/14/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "MAGPIE_HeatAccumulation.h"

template<>
InputParameters validParams<MAGPIE_HeatAccumulation>()
{
	InputParameters params = validParams<Kernel>();
	params.addCoupledVar("solid_heat","Coupled variable for the solid heat of adsorption of interest");
	return params;
}

MAGPIE_HeatAccumulation::MAGPIE_HeatAccumulation(const InputParameters & parameters) :
Kernel(parameters),
_porosity(getMaterialProperty<Real>("porosity")),
_pellet_density(getMaterialProperty<Real>("pellet_density")),
_solid_heat(coupledValue("solid_heat")),
_solid_heat_old(coupledValueOld("solid_heat")),
_solid_heat_older(coupledValueOlder("solid_heat"))
{

}

Real
MAGPIE_HeatAccumulation::computeQpResidual()
{
	return _pellet_density[_qp]*(1.0-_porosity[_qp])*((_solid_heat[_qp]-_solid_heat_older[_qp])/(2.0*_dt))*_test[_i][_qp];
}

Real
MAGPIE_HeatAccumulation::computeQpJacobian()
{
	return _pellet_density[_qp]*(1.0-_porosity[_qp])*((_solid_heat[_qp]-_solid_heat_older[_qp])/(2.0*_dt))*_phi[_i][_qp];
}

