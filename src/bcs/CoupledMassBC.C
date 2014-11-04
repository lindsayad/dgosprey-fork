
#include "CoupledMassBC.h"

template<>
InputParameters validParams<CoupledMassBC>()
{
  InputParameters params = validParams<MassCauchyBC>();
  params.addRequiredCoupledVar("temperature","Coupled variable for temperature");
  params.addRequiredCoupledVar("pressure","Coupled variable for total pressure");
  params.addParam<Real>("input_mole_frac","The mole fraction of the gas species at the inlet of the column.");
  return params;
}

CoupledMassBC::CoupledMassBC(const std::string & name, InputParameters parameters) :
MassCauchyBC(name, parameters),
_temperature(coupledValue("temperature")),
_total_pressure(coupledValue("pressure")),
_y_o(getParam<Real>("input_mole_frac"))
{}

Real
CoupledMassBC::computeQpResidual()
{
  MassCauchyBC::_boundary_value = (_total_pressure[_qp] * _y_o) / (8.3144621 * _temperature[_qp]);
  return MassCauchyBC::computeQpResidual();
}

Real
CoupledMassBC::computeQpJacobian()
{
  return MassCauchyBC::computeQpJacobian();
}

