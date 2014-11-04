#include "CFLDT.h"

template<>
InputParameters validParams<CFLDT>()
{
  InputParameters params = validParams<TimeStepper>();
  params.addParam<Real>("length","Size of the fixed bed column. Used to determine mesh size.");
  params.addParam<Real>("nodes","Number of nodes in mesh. Used to determine mesh size.");
  params.addParam<Real>("flow_rate","Gas flow rate into system (cm^3/hr)");
  params.addParam<Real>("din","Wall inner diameter (cm)");
  params.addParam<Real>("eb","Porosity of the bed");
  return params;
}

CFLDT::CFLDT(const std::string & name, InputParameters parameters) :
TimeStepper(name, parameters),
_length(getParam<Real>("length")),
_nodes(getParam<Real>("nodes")),
_flow_rate(getParam<Real>("flow_rate")),
_din(getParam<Real>("din")),
_eb(getParam<Real>("eb"))
{
  
}

Real CFLDT::computeInitialDT()
{
  Real _dz = _length / _nodes;
  Real _vel = (_flow_rate / (_eb * (M_PI/4.0) * _din * _din));
  Real _dt = _dz / (8.0 * _vel);
  
  return std::min(getCurrentDT(),_dt);
}

Real CFLDT::computeDT()
{
  Real _dz = _length / _nodes;
  Real _vel = (_flow_rate / (_eb * (M_PI/4.0) * _din * _din));  
  Real _dt = _dz / (8.0 * _vel);
  
  return std::min(getCurrentDT(),_dt);
}
