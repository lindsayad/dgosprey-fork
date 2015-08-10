#include "FluidHeatTransfer.h"

template<>
InputParameters validParams<FluidHeatTransfer>()
{
  InputParameters params = validParams<Kernel>();
  params.addCoupledVar("coupled", "Name of the wall temperature variable to be coupled.");
  return params;
}


FluidHeatTransfer::FluidHeatTransfer(const InputParameters & parameters)
:Kernel(parameters),
_bed_wall_transfer_coeff(getMaterialProperty<Real>("bed_wall_transfer_coeff")),
_inner_dia(getMaterialProperty<Real>("inner_dia")),
_porosity(getMaterialProperty<Real>("porosity")),
_wall_temp(coupledValue("coupled"))
{
}

Real FluidHeatTransfer::computeQpResidual()
{
  Real _coef = (4.0 * _bed_wall_transfer_coeff[_qp]) / ( _inner_dia[_qp] );

  return -_test[_i][_qp] * _coef * (_wall_temp[_qp] - _u[_qp]);
}

Real FluidHeatTransfer::computeQpJacobian()
{
  Real _coef = (4.0 * _bed_wall_transfer_coeff[_qp]) / ( _inner_dia[_qp] );
  
  return _test[_i][_qp] * _coef * _phi[_j][_qp];
}

