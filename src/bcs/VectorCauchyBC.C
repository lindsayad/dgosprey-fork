
#include "VectorCauchyBC.h"

template<>
InputParameters validParams<VectorCauchyBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<RealVectorValue>("velocity", RealVectorValue(), "advective flux into the control volume");
	params.addParam<Real>("diffusion",1,"diffusion coefficient into control volume");
	params.addParam<Real>("u_in",1,"input value of conserved quanity into the control volume");
	params.addRequiredCoupledVar("coupled","The coupled variable to u_in");
  return params;
}

VectorCauchyBC::VectorCauchyBC(const std::string & name, InputParameters parameters) :
    IntegratedBC(name, parameters),
    _velocity(getParam<RealVectorValue>("velocity")),
	_diffusion(getParam<Real>("diffusion")),
	_u_in(getParam<Real>("u_in")),
	_u_bound(coupledValue("coupled"))
{}

Real
VectorCauchyBC::computeQpResidual()
{
  if (_diffusion == 0.0)
	  _diffusion = 1e-16; //Actually, 
  return -_test[_i][_qp]*((_velocity*_normals[_qp])/_diffusion)*(_u_in - _u_bound[_qp]);
}

