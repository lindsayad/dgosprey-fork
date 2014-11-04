#include "DGConservativeAdvection.h"

template<>
InputParameters validParams<DGConservativeAdvection>()
{
  InputParameters params = validParams<DGKernel>();
  params.addParam<int>("dir", 0, "Denotes the flow direction used in the mesh (0 = x, 1 = y, 2 = z) for the 1D fixed bed.");
  return params;
}

DGConservativeAdvection::DGConservativeAdvection(const std::string & name, InputParameters parameters) :
DGKernel(name, parameters),
_dir(getParam<int>("dir")),
_velocity(getMaterialProperty<Real>("velocity"))
{
  _vel(0)=0.0;
  _vel(1)=0.0;
  _vel(2)=0.0;
}

Real
DGConservativeAdvection::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;
  _vel(_dir) = _velocity[_qp];
  
  switch (type)
  {
    case Moose::Element:
      if ( (_vel * _normals[_qp]) >= 0.0)
        r += (_vel * _normals[_qp]) * _u[_qp] * _test[_i][_qp];
      else
        r += (_vel * _normals[_qp]) * _u_neighbor[_qp] * _test[_i][_qp];
      break;
      
    case Moose::Neighbor:
      if ( (_vel * _normals[_qp]) >= 0.0)
        r += -(_vel * _normals[_qp]) * _u[_qp] * _test_neighbor[_i][_qp];
      else
        r += -(_vel * _normals[_qp]) * _u_neighbor[_qp] * _test_neighbor[_i][_qp];
      break;
  }

  return r;
}

Real
DGConservativeAdvection::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;
  _vel(_dir) = _velocity[_qp];
  
  switch (type)
  {
      
    case Moose::ElementElement:
      if ( (_vel * _normals[_qp]) >= 0.0)
        r += (_vel * _normals[_qp]) * _phi[_j][_qp] * _test[_i][_qp];
      else
        r += 0.0;
      break;
      
    case Moose::ElementNeighbor:
      if ( (_vel * _normals[_qp]) >= 0.0)
        r += 0.0;
      else
        r += (_vel * _normals[_qp]) * _phi_neighbor[_j][_qp] * _test[_i][_qp];
      break;
      
    case Moose::NeighborElement:
      if ( (_vel * _normals[_qp]) >= 0.0)
        r += -(_vel * _normals[_qp]) * _phi[_j][_qp] * _test_neighbor[_i][_qp];
      else
        r += 0.0;
      break;
      
    case Moose::NeighborNeighbor:
      if ( (_vel * _normals[_qp]) >= 0.0)
        r += 0.0;
      else
        r += -(_vel * _normals[_qp]) * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
      break;
  }

  return r;
}
