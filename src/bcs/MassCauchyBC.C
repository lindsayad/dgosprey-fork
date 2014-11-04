
#include "MassCauchyBC.h"

template<>
InputParameters validParams<MassCauchyBC>()
{
  InputParameters params = validParams<IntegratedBC>();
	params.addParam<Real>("boundary_value",1.0,"Inupt value at the boundary for the coupled variable. (Will be in kPa later)");
  params.addParam<int>("index", 0, "The index of the coupling variable. Must be given in same order of appearance as in the FlowProperties Material block. Indexing starts from 0. 0 is default value.");
  return params;
}

MassCauchyBC::MassCauchyBC(const std::string & name, InputParameters parameters) :
IntegratedBC(name, parameters),
_boundary_value(getParam<Real>("boundary_value")),
_dispersion(getMaterialProperty<std::vector<Real> >("dispersion")),
_velocity(getMaterialProperty<Real>("velocity")),
_index(getParam<int>("index"))
{}

Real
MassCauchyBC::computeQpResidual()
{
  return -_test[_i][_qp]*(_velocity[_qp]/_dispersion[_qp][_index])*(_boundary_value - _u[_qp]);
}

Real
MassCauchyBC::computeQpJacobian()
{
  return _test[_i][_qp]*(_velocity[_qp]/_dispersion[_qp][_index])*_phi[_j][_qp];
}

