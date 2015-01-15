#include "HeatConductivity.h"

template<>
InputParameters validParams<HeatConductivity>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

HeatConductivity::HeatConductivity(const std::string & name, InputParameters parameters) :
Kernel(name, parameters),
_conductivity(getMaterialProperty<Real>("conductivity")),
_porosity(getMaterialProperty<Real>("porosity"))
{
}

Real
HeatConductivity::computeQpResidual()
{
  return _porosity[_qp]*_conductivity[_qp]*_grad_test[_i][_qp]*_grad_u[_qp];
}

Real
HeatConductivity::computeQpJacobian()
{
  return _porosity[_qp]*_conductivity[_qp]*_grad_test[_i][_qp]*_grad_phi[_j][_qp];
}
