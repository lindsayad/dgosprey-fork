#include "HeatConductivity.h"

template<>
InputParameters validParams<HeatConductivity>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

HeatConductivity::HeatConductivity(const std::string & name, InputParameters parameters) :
Kernel(name, parameters),
_conductivity(getMaterialProperty<Real>("conductivity"))
{
}

Real
HeatConductivity::computeQpResidual()
{
  return _conductivity[_qp]*_grad_test[_i][_qp]*_grad_u[_qp];
}

Real
HeatConductivity::computeQpJacobian()
{
  return _conductivity[_qp]*_grad_test[_i][_qp]*_grad_phi[_j][_qp];
}
