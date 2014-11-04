#include "WaveFront.h"

template<>
InputParameters validParams<WaveFront>()
{
  InputParameters params = validParams<NodalPostprocessor>();
  return params;
}

WaveFront::WaveFront(const std::string & name, InputParameters parameters) :
NodalPostprocessor(name, parameters),
_velocity(getMaterialProperty<Real>("velocity")),
_gas_density(getMaterialProperty<Real>("gas_density")),
_gas_heat_capacity(getMaterialProperty<Real>("gas_heat_capacity")),
_max_wfs(0.0)
{
}

WaveFront::~WaveFront()
{
}

void
WaveFront::initialize()
{
	_max_wfs = 0.0;
}

void
WaveFront::execute()
{
  _max_wfs = 0.0;
	_max_wfs = std::max(_max_wfs,_velocity[_qp]);
  _max_wfs = std::max(_max_wfs,(_velocity[_qp]*_gas_heat_capacity[_qp]*_gas_density[_qp]));
  if (std::isinf(_max_wfs) || _t == 0.0)
    _max_wfs = 0.0;
}

Real
WaveFront::getValue()
{
  return _max_wfs;
}

void
WaveFront::threadJoin(const UserObject & y) //Note: This function was causing hang-ups so it may have to be disabled 
{
  const WaveFront & pps = static_cast<const WaveFront &>(y);
  _max_wfs = std::max(_max_wfs, pps._max_wfs);
}