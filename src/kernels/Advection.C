#include "Advection.h"

template<>
InputParameters validParams<Advection>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<int>("dir", 0, "Denotes the flow direction used in the mesh (0 = x, 1 = y, 2 = z) for the 1D fixed bed.");
  return params;
}

Advection::Advection(const std::string & name,
                       InputParameters parameters) :
Kernel(name, parameters),
_dir(getParam<int>("dir")),
_velocity(getMaterialProperty<Real>("velocity"))

{
  _vel(0)=0.0;
  _vel(1)=0.0;
  _vel(2)=0.0;
}

Real Advection::computeQpResidual()
{
  _vel(_dir) = _velocity[_qp];
  return _test[_i][_qp]*(_vel*_grad_u[_qp]);
}

Real Advection::computeQpJacobian()
{
  _vel(_dir) = _velocity[_qp];
  return _test[_i][_qp]*(_vel*_grad_phi[_j][_qp]);
}