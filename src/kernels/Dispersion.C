#include "Dispersion.h"

template<>
InputParameters validParams<Dispersion>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<int>("index", 0, "The index of the coupling variable. Must be given in same order of appearance as in the FlowProperties Material block. Indexing starts from 0. 0 is default value.");
  return params;
}

Dispersion::Dispersion(const InputParameters & parameters) :
Kernel(parameters),
_index(getParam<int>("index")),
_dispersion(getMaterialProperty<std::vector<Real> >("dispersion"))
{
}

Real
Dispersion::computeQpResidual()
{
  return _dispersion[_qp][_index]*_grad_test[_i][_qp]*_grad_u[_qp];
}

Real
Dispersion::computeQpJacobian()
{
  return _dispersion[_qp][_index]*_grad_test[_i][_qp]*_grad_phi[_j][_qp];
}
