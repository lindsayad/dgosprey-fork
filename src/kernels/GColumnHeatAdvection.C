//
//  GColumnHeatAdvection.C
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#include "GColumnHeatAdvection.h"

template<>
InputParameters validParams<GColumnHeatAdvection>()
{
	InputParameters params = validParams<GAdvection>();
	return params;
}

GColumnHeatAdvection::GColumnHeatAdvection(const std::string & name,
										   InputParameters parameters) :
GAdvection(name, parameters),
_vel(getMaterialProperty<Real>("velocity")),
_gas_density(getMaterialProperty<Real>("gas_density")),
_gas_heat_capacity(getMaterialProperty<Real>("gas_heat_capacity"))

{
	
}

Real GColumnHeatAdvection::computeQpResidual()
{
	_velocity(0)=0.0;
	_velocity(1)=_vel[_qp]*_gas_heat_capacity[_qp]*_gas_density[_qp];
	_velocity(2)=0.0;
	
	return GAdvection::computeQpResidual();
}

Real GColumnHeatAdvection::computeQpJacobian()
{
	_velocity(0)=0.0;
	_velocity(1)=_vel[_qp]*_gas_heat_capacity[_qp]*_gas_density[_qp];
	_velocity(2)=0.0;
	
	return GAdvection::computeQpJacobian();
}
