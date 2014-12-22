
#include "DGFluxBC.h"

template<>
InputParameters validParams<DGFluxBC>()
{
	InputParameters params = validParams<IntegratedBC>();
	params.addParam<Real>("vx",0, "x-component of velocity vector");
	params.addParam<Real>("vy",0,"y-component of velocity vector");
	params.addParam<Real>("vz",0,"z-component of velocity vector");
	params.addParam<Real>("Dxx",0,"xx-component of diffusion tensor");
	params.addParam<Real>("Dxy",0,"xy-component of diffusion tensor");
	params.addParam<Real>("Dxz",0,"xz-component of diffusion tensor");
	params.addParam<Real>("Dyx",0,"yx-component of diffusion tensor");
	params.addParam<Real>("Dyy",0,"yy-component of diffusion tensor");
	params.addParam<Real>("Dyz",0,"yz-component of diffusion tensor");
	params.addParam<Real>("Dzx",0,"zx-component of diffusion tensor");
	params.addParam<Real>("Dzy",0,"zy-component of diffusion tensor");
	params.addParam<Real>("Dzz",0,"zz-component of diffusion tensor");
	params.addParam<Real>("u_input", 1.0, "input value of u");
	return params;
}

DGFluxBC::DGFluxBC(const std::string & name, InputParameters parameters) :
IntegratedBC(name, parameters),
_vx(getParam<Real>("vx")),
_vy(getParam<Real>("vy")),
_vz(getParam<Real>("vz")),
_Dxx(getParam<Real>("Dxx")),
_Dxy(getParam<Real>("Dxy")),
_Dxz(getParam<Real>("Dxz")),
_Dyx(getParam<Real>("Dyx")),
_Dyy(getParam<Real>("Dyy")),
_Dyz(getParam<Real>("Dyz")),
_Dzx(getParam<Real>("Dzx")),
_Dzy(getParam<Real>("Dzy")),
_Dzz(getParam<Real>("Dzz")),
_u_input(getParam<Real>("u_input"))
{
	_velocity(0)=_vx;
	_velocity(1)=_vy;
	_velocity(2)=_vz;
	
	_Diffusion(0,0) = _Dxx;
	_Diffusion(0,1) = _Dxy;
	_Diffusion(0,2) = _Dxz;
	
	_Diffusion(1,0) = _Dyx;
	_Diffusion(1,1) = _Dyy;
	_Diffusion(1,2) = _Dyz;
	
	_Diffusion(2,0) = _Dzx;
	_Diffusion(2,1) = _Dzy;
	_Diffusion(2,2) = _Dzz;
}

Real
DGFluxBC::computeQpResidual()
{
	const unsigned int elem_b_order = static_cast<unsigned int> (_var.getOrder());
	const double h_elem = _current_elem->volume()/_current_side_elem->volume() * 1./std::pow(elem_b_order, 2.);
	
	//std::cout << _Diffusion*_grad_u[_qp] << std::endl;
	//std::cout << _Diffusion << std::endl;
	//std::cout << _grad_u[_qp] << std::endl;
	if ((_velocity - _Diffusion*_grad_u[_qp])*_normals[_qp] >= 0.0)
		return _test[_i][_qp]*((_velocity - _Diffusion*_grad_u[_qp])*_normals[_qp])*_u[_qp];
	else
		return _test[_i][_qp]*((_velocity - _Diffusion*_grad_u[_qp])*_normals[_qp])*_u_input;//Need to edit grad_u
}

Real
DGFluxBC::computeQpJacobian()
{
	const unsigned int elem_b_order = static_cast<unsigned int> (_var.getOrder());
	const double h_elem = _current_elem->volume()/_current_side_elem->volume() * 1./std::pow(elem_b_order, 2.);
	
	if ((_velocity - _Diffusion*_grad_u[_qp])*_normals[_qp] >= 0.0)
		return _test[_i][_qp]*((_velocity - _Diffusion*_grad_phi[_j][_qp])*_normals[_qp])*_phi[_j][_qp];
	else
		return -_test[_i][_qp]*(_Diffusion*_grad_phi[_j][_qp]*_normals[_qp]);//Needs editing
}

