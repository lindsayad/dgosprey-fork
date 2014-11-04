#include "DGDispersion.h"

template<>
InputParameters validParams<DGDispersion>()
{
  InputParameters params = validParams<DGKernel>();
  params.addParam<Real>("sigma", 1.0, "sigma");
  params.addParam<Real>("epsilon", 1.0, "epsilon");
  params.addParam<int>("index", 0, "The index of the coupling variable. Must be given in same order of appearance as in the FlowProperties Material block. Indexing starts from 0. 0 is default value.");
  return params;
}

DGDispersion::DGDispersion(const std::string & name, InputParameters parameters) :
DGKernel(name, parameters),
_epsilon(getParam<Real>("epsilon")),
_sigma(getParam<Real>("sigma")),
_index(getParam<int>("index")),
_dispersion(getMaterialProperty<std::vector<Real> >("dispersion"))
{
}

Real
DGDispersion::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;
  
  const unsigned int elem_b_order = static_cast<unsigned int> (_var.getOrder());
  const double h_elem = _current_elem->volume()/_current_side_elem->volume() * 1./std::pow(elem_b_order, 2.);
  
  switch (type)
  {
    case Moose::Element:
      r += 0.5 * _dispersion[_qp][_index] * (- _grad_u[_qp] * _normals[_qp] * _test[_i][_qp] + _epsilon * _grad_test[_i][_qp] * _normals[_qp] * _u[_qp]);
      r += _sigma / h_elem * _u[_qp] * _test[_i][_qp];
      
      r += 0.5 * _dispersion[_qp][_index] * (-_grad_u_neighbor[_qp] * _normals[_qp] * _test[_i][_qp] - _epsilon * _grad_test[_i][_qp] * _normals[_qp] * _u_neighbor[_qp]);
      r += - _sigma / h_elem * _u_neighbor[_qp] * _test[_i][_qp];
      break;
      
    case Moose::Neighbor:
      r += 0.5 * _dispersion[_qp][_index] * (_grad_u[_qp] * _normals[_qp] + _grad_u_neighbor[_qp] * _normals[_qp]) * _test_neighbor[_i][_qp];
      r += _epsilon * 0.5 * _dispersion[_qp][_index] * _grad_test_neighbor[_i][_qp] * _normals[_qp] * (_u[_qp] - _u_neighbor[_qp]);
      r -= _sigma / h_elem * (_u[_qp] - _u_neighbor[_qp]) * _test_neighbor[_i][_qp];
      break;
  }
  
  return r;
}

Real
DGDispersion::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;
  
  const unsigned int elem_b_order = static_cast<unsigned int> (_var.getOrder());
  const double h_elem = _current_elem->volume()/_current_side_elem->volume() * 1./std::pow(elem_b_order, 2.);
  
  switch (type)
  {
      
    case Moose::ElementElement:
      r -= 0.5 * _dispersion[_qp][_index] * _grad_phi[_j][_qp] * _normals[_qp] * _test[_i][_qp];
      r += _epsilon * 0.5 * _dispersion[_qp][_index] * _grad_test[_i][_qp] * _normals[_qp] * _phi[_j][_qp];
      r += _sigma / h_elem * _phi[_j][_qp] * _test[_i][_qp];
      break;
      
    case Moose::ElementNeighbor:
      r -= 0.5 * _dispersion[_qp][_index] * _grad_phi_neighbor[_j][_qp] * _normals[_qp] * _test[_i][_qp];
      r -= _epsilon * 0.5 * _dispersion[_qp][_index] * _grad_test[_i][_qp] * _normals[_qp] * _phi_neighbor[_j][_qp];
      r -= _sigma / h_elem * _phi_neighbor[_j][_qp] * _test[_i][_qp];
      break;
      
    case Moose::NeighborElement:
      r += 0.5 * _dispersion[_qp][_index] * _grad_phi[_j][_qp] * _normals[_qp] * _test_neighbor[_i][_qp];
      r += _epsilon * 0.5 * _dispersion[_qp][_index] * _grad_test_neighbor[_i][_qp] * _normals[_qp] * _phi[_j][_qp];
      r -= _sigma / h_elem * _phi[_j][_qp] * _test_neighbor[_i][_qp];
      break;
      
    case Moose::NeighborNeighbor:
      r += 0.5 * _dispersion[_qp][_index] * _grad_phi_neighbor[_j][_qp] * _normals[_qp] * _test_neighbor[_i][_qp];
      r -= _epsilon * 0.5 * _dispersion[_qp][_index] * _grad_test_neighbor[_i][_qp] * _normals[_qp] * _phi_neighbor[_j][_qp];
      r += _sigma / h_elem * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
      break;
  }
  
  return r;
}
