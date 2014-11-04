#include "BedHeatAccumulation.h"

template<>
InputParameters validParams<BedHeatAccumulation>()
{
  InputParameters params = validParams<TimeDerivative>();
  return params;
}


BedHeatAccumulation::BedHeatAccumulation(const std::string & name,
                                           InputParameters parameters)
:TimeDerivative(name,parameters),
_gas_density(getMaterialProperty<Real>("wall_density")),
_gas_heat_capacity(getMaterialProperty<Real>("wall_heat_capacity")),
_pellet_density(getMaterialProperty<Real>("pellet_density")),
_pellet_heat_capacity(getMaterialProperty<Real>("pellet_heat_capacity")),
_porosity(getMaterialProperty<Real>("porosity"))
{
  
}

Real
BedHeatAccumulation::computeQpResidual()
{
  Real _coeff = (_gas_heat_capacity[_qp]*_gas_density[_qp]) + ( (_pellet_heat_capacity[_qp]*_pellet_density[_qp]*(1.0-_porosity[_qp])) / _porosity[_qp]);
  return _coeff * TimeDerivative::computeQpResidual();
}

Real
BedHeatAccumulation::computeQpJacobian()
{
  Real _coeff = (_gas_heat_capacity[_qp]*_gas_density[_qp]) + ( (_pellet_heat_capacity[_qp]*_pellet_density[_qp]*(1.0-_porosity[_qp])) / _porosity[_qp]);
  return _coeff * TimeDerivative::computeQpJacobian();
}
