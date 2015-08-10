#include "ColumnTemperatureIC.h"

template<> InputParameters validParams<ColumnTemperatureIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredParam<Real>("initial_temperature","The value of the initial temperature in the column (K).");
  return params;
}

ColumnTemperatureIC::ColumnTemperatureIC(const InputParameters & parameters) :
InitialCondition(parameters),
_TC_IC(getParam<Real>("initial_temperature"))
{
  
}

Real ColumnTemperatureIC::value(const Point & p)
{
  return _TC_IC;
}