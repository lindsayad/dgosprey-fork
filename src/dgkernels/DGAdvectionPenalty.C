#include "DGAdvectionPenalty.h"

template<>
InputParameters validParams<DGAdvectionPenalty>()
{
	InputParameters params = validParams<DGKernel>();
	params.addParam<Real>("vx",0,"x-component of velocity vector");
	params.addParam<Real>("vy",0,"y-component of velocity vector");
	params.addParam<Real>("vz",0,"z-component of velocity vector");
	return params;
}

DGAdvectionPenalty::DGAdvectionPenalty(const std::string & name, InputParameters parameters) :
DGKernel(name, parameters),
_vx(getParam<Real>("vx")),
_vy(getParam<Real>("vy")),
_vz(getParam<Real>("vz"))
{
	_velocity(0)=_vx;
	_velocity(1)=_vy;
	_velocity(2)=_vz;
}

Real
DGAdvectionPenalty::computeQpResidual(Moose::DGResidualType type)
{
	Real r = 0;
	const unsigned int elem_b_order = static_cast<unsigned int> (_var.getOrder());
	const double h_elem = _current_elem->volume()/_current_side_elem->volume() * 1./std::pow(elem_b_order, 2.);
	
	switch (type)
	{
		case Moose::Element:
			//Output
			if ( (_velocity * _normals[_qp]) >= 0.0)
			{
				r += (_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_u[_qp] - _grad_u_neighbor[_qp]) * _normals[_qp] * _test[_i][_qp];
				r += (_velocity * _normals[_qp]) * (_u[_qp] - _u_neighbor[_qp]) * _test[_i][_qp];
			}
			//Input
			else
			{
				r += (_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_u[_qp] - _grad_u_neighbor[_qp]) * _normals[_qp]  * _test[_i][_qp];
				r += (_velocity * _normals[_qp]) * (_u[_qp] - _u_neighbor[_qp]) * _test[_i][_qp];
			}
			break;
			
		case Moose::Neighbor:
			if ( (_velocity * _normals[_qp]) >= 0.0)
			{
				r += -(_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_u[_qp] - _grad_u_neighbor[_qp]) * _normals[_qp] * _test_neighbor[_i][_qp];
				r += -(_velocity * _normals[_qp]) * (_u[_qp] - _u_neighbor[_qp]) * _test_neighbor[_i][_qp];
			}
			else
			{
				r += -(_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_u[_qp] - _grad_u_neighbor[_qp]) * _normals[_qp] * _test_neighbor[_i][_qp];
				r += -(_velocity * _normals[_qp]) * (_u[_qp] - _u_neighbor[_qp]) * _test_neighbor[_i][_qp];
			}
			break;
	}
	return r;
}

Real
DGAdvectionPenalty::computeQpJacobian(Moose::DGJacobianType type)
{
	Real r = 0;
	const unsigned int elem_b_order = static_cast<unsigned int> (_var.getOrder());
	const double h_elem = _current_elem->volume()/_current_side_elem->volume() * 1./std::pow(elem_b_order, 2.);
	
	switch (type)
	{
			
		case Moose::ElementElement:
			if ( (_velocity * _normals[_qp]) >= 0.0)
			{
				r += (_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_phi[_j][_qp] - _grad_phi_neighbor[_j][_qp]) * _normals[_qp] * _test[_i][_qp];
				r += (_velocity * _normals[_qp]) * (_phi[_j][_qp] - _phi_neighbor[_j][_qp]) * _test[_i][_qp];
			}
			else
			{
				r += (_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_phi[_j][_qp] - _grad_phi_neighbor[_j][_qp]) * _normals[_qp] * _test[_i][_qp];
				r += (_velocity * _normals[_qp]) * (_phi[_j][_qp] - _phi_neighbor[_j][_qp]) * _test[_i][_qp];
			}
			break;
			
		case Moose::ElementNeighbor:
			if ( (_velocity * _normals[_qp]) >= 0.0)
			{
				r += (_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_phi[_j][_qp] - _grad_phi_neighbor[_j][_qp]) * _normals[_qp] * _test[_i][_qp];
				r += (_velocity * _normals[_qp]) * (_phi[_j][_qp] - _phi_neighbor[_j][_qp]) * _test[_i][_qp];;
			}
			else
			{
				r += (_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_phi[_j][_qp] - _grad_phi_neighbor[_j][_qp]) * _normals[_qp] * _test[_i][_qp];
				r += (_velocity * _normals[_qp]) * (_phi[_j][_qp] - _phi_neighbor[_j][_qp]) * _test[_i][_qp];
			}
			break;
			
		case Moose::NeighborElement:
			if ( (_velocity * _normals[_qp]) >= 0.0)
			{
				r += -(_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_phi[_j][_qp] - _grad_phi_neighbor[_j][_qp]) * _normals[_qp] * _test_neighbor[_i][_qp];
				r += -(_velocity * _normals[_qp]) * (_phi[_j][_qp] - _phi_neighbor[_j][_qp]) * _test_neighbor[_i][_qp];
			}
			else
			{
				r += -(_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_phi[_j][_qp] - _grad_phi_neighbor[_j][_qp]) * _normals[_qp] * _test_neighbor[_i][_qp];
				r += -(_velocity * _normals[_qp]) * (_phi[_j][_qp] - _phi_neighbor[_j][_qp]) * _test_neighbor[_i][_qp];
			}
			break;
			
		case Moose::NeighborNeighbor:
			if ( (_velocity * _normals[_qp]) >= 0.0)
			{
				r += -(_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_phi[_j][_qp] - _grad_phi_neighbor[_j][_qp]) * _normals[_qp] * _test_neighbor[_i][_qp];
				r += -(_velocity * _normals[_qp]) * (_phi[_j][_qp] - _phi_neighbor[_j][_qp]) * _test_neighbor[_i][_qp];
			}
			else
			{
				r += -(_velocity * _normals[_qp]) * 1.0 * h_elem * (_grad_phi[_j][_qp] - _grad_phi_neighbor[_j][_qp]) * _normals[_qp] * _test_neighbor[_i][_qp];
				r += -(_velocity * _normals[_qp]) * (_phi[_j][_qp] - _phi_neighbor[_j][_qp]) * _test_neighbor[_i][_qp];
			}
			break;
	}
	return r;
}
