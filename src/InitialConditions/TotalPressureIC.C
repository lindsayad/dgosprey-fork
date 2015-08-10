#include "TotalPressureIC.h"

template<> InputParameters validParams<TotalPressureIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredParam<Real>("initial_pressure","The value of the initial pressure in the column (kPa).");
  return params;
}

TotalPressureIC::TotalPressureIC(const InputParameters & parameters) :
InitialCondition(parameters),
_PT_IC(getParam<Real>("initial_pressure"))
{
  
}

Real TotalPressureIC::value(const Point & p)
{
  return _PT_IC;
}