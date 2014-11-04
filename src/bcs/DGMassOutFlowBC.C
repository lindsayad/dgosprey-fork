
#include "DGMassOutFlowBC.h"

template<>
InputParameters validParams<DGMassOutFlowBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<int>("dir",0,"Denotes the flow direction used in the mesh (0 = x, 1 = y, 2 = z) for the 1D fixed bed.");
  return params;
}

DGMassOutFlowBC::DGMassOutFlowBC(const std::string & name, InputParameters parameters) :
IntegratedBC(name, parameters),
_velocity(getMaterialProperty<Real>("velocity")),
_dir(getParam<int>("dir"))
{
	_vel(0) = 0.0;
  _vel(1) = 0.0;
  _vel(2) = 0.0;
}

Real
DGMassOutFlowBC::computeQpResidual()
{
  _vel(_dir) = _velocity[_qp];
  return _test[_i][_qp]*(_vel*_normals[_qp])*_u[_qp];
}

Real
DGMassOutFlowBC::computeQpJacobian()
{
  return _test[_i][_qp]*(_vel*_normals[_qp])*_phi[_j][_qp];
}

