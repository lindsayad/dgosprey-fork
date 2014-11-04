#include "ConservativeAdvection.h"

template<>
InputParameters validParams<ConservativeAdvection>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<int>("dir", 0, "Denotes the flow direction used in the mesh (0 = x, 1 = y, 2 = z) for the 1D fixed bed.");
  return params;
}

ConservativeAdvection::ConservativeAdvection(const std::string & name,
                     InputParameters parameters) :
Kernel(name, parameters),
_dir(getParam<int>("dir")),
_velocity(getMaterialProperty<Real>("velocity"))

{
  _vel(0)=0.0;
  _vel(1)=0.0;
  _vel(2)=0.0;
}

Real ConservativeAdvection::computeQpResidual()
{
  _vel(_dir) = _velocity[_qp];
  return -_u[_qp]*(_vel*_grad_test[_i][_qp]);
}

Real ConservativeAdvection::computeQpJacobian()
{
  _vel(_dir) = _velocity[_qp];
  return -_phi[_j][_qp]*(_vel*_grad_test[_i][_qp]);
}