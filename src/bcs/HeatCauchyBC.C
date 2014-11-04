
#include "HeatCauchyBC.h"

template<>
InputParameters validParams<HeatCauchyBC>()
{
  InputParameters params = validParams<IntegratedBC>();
	params.addParam<Real>("boundary_value",298.15,"Inupt value at the boundary for the coupled variable.");
  return params;
}

HeatCauchyBC::HeatCauchyBC(const std::string & name, InputParameters parameters) :
IntegratedBC(name, parameters),
_conductivity(getMaterialProperty<Real>("conductivity")),
_velocity(getMaterialProperty<Real>("velocity")),
_gas_density(getMaterialProperty<Real>("gas_density")),
_gas_heat_capacity(getMaterialProperty<Real>("gas_heat_capacity")),
_boundary_value(getParam<Real>("boundary_value"))
{}

Real
HeatCauchyBC::computeQpResidual()
{
  return -_test[_i][_qp]*((_velocity[_qp] * _gas_density[_qp] * _gas_heat_capacity[_qp])/_conductivity[_qp])*(_boundary_value - _u[_qp]);
}

Real
HeatCauchyBC::computeQpJacobian()
{
  return _test[_i][_qp]*((_velocity[_qp] * _gas_density[_qp] * _gas_heat_capacity[_qp])/_conductivity[_qp])*_phi[_j][_qp];
}

