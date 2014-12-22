
#include "DGFluxBC.h"

template<>
InputParameters validParams<DGFluxBC>()
{
	InputParameters params = validParams<IntegratedBC>();
	params.addRequiredParam<Real>("vx", "x-component of velocity vector");
	params.addParam<Real>("vy",0,"y-component of velocity vector");
	params.addParam<Real>("vz",0,"z-component of velocity vector");
	params.addParam<Real>("u_input", 1.0, "input value of u");
	return params;
}

DGFluxBC::DGFluxBC(const std::string & name, InputParameters parameters) :
IntegratedBC(name, parameters),
_vx(getParam<Real>("vx")),
_vy(getParam<Real>("vy")),
_vz(getParam<Real>("vz")),
_u_input(getParam<Real>("u_input"))
{
	_velocity(0)=_vx;
	_velocity(1)=_vy;
	_velocity(2)=_vz;
}

Real
DGFluxBC::computeQpResidual()
{
	if (_velocity*_normals[_qp] >= 0.0)
		return _test[_i][_qp]*(_velocity*_normals[_qp])*_u[_qp];
	else
		return _test[_i][_qp]*(_velocity*_normals[_qp])*_u_input;
}

Real
DGFluxBC::computeQpJacobian()
{
	if (_velocity*_normals[_qp] >= 0.0)
		return _test[_i][_qp]*(_velocity*_normals[_qp])*_phi[_j][_qp];
	else
		return 0.0;
}

