#include "ConcentrationIC.h"

template<> InputParameters validParams<ConcentrationIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredParam<Real>("initial_mole_frac","The initial mole fraction of the gas species in the column. Note: All mole fractions must sum to one, otherwise errors will occur that will not be caught!!!");
  params.addRequiredCoupledVar("temperature","Coupled variable for temperature");
  params.addRequiredCoupledVar("pressure","Coupled variable for total pressure");
  return params;
}

ConcentrationIC::ConcentrationIC(const std::string & name, InputParameters parameters) :
InitialCondition(name,parameters),
_y_IC(getParam<Real>("initial_mole_frac")),
_temperature(coupledValue("temperature")),
_total_pressure(coupledValue("pressure"))
{
  
}

Real ConcentrationIC::value(const Point & p)
{
  //Note: we will not check to ensure the mole fraction is valid. This may cause error.
	//std::cout << "size ============> " << _total_pressure.size() << std::endl;
  return (_total_pressure[_qp] * _y_IC) / (8.3144621 * _temperature[_qp]);
}