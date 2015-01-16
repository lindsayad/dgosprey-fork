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
_heat_retardation(getMaterialProperty<Real>("heat_retardation"))
{
  
}

Real
BedHeatAccumulation::computeQpResidual()
{
  return _heat_retardation[_qp] * TimeDerivative::computeQpResidual();
}

Real
BedHeatAccumulation::computeQpJacobian()
{
  return _heat_retardation[_qp] * TimeDerivative::computeQpJacobian();
}
