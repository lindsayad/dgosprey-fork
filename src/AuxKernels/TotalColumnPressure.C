#include "TotalColumnPressure.h"

template<>
InputParameters validParams<TotalColumnPressure>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("temperature","Coupled variable for temperature");
  params.addCoupledVar("coupled_gases", "Gas concentrations variables being coupled");
  return params;
}

TotalColumnPressure::TotalColumnPressure(const InputParameters & parameters) :
AuxKernel(parameters),
_temperature(coupledValue("temperature"))
{
  unsigned int n = coupledComponents("coupled_gases");
	_index.resize(n);
	_gas_conc.resize(n);
	
	for (unsigned int i = 0; i<_gas_conc.size(); ++i)
	{
		_index[i] = coupled("coupled_gases",i); 
		_gas_conc[i] = &coupledValue("coupled_gases",i);
	}

}

Real
TotalColumnPressure::computeValue()
{
	Real _PT = 0.0;
  
  for (unsigned int i = 0; i<_gas_conc.size(); ++i)
  {
    _PT = _PT + ( (*_gas_conc[i])[_qp] * 8.3144621 * _temperature[_qp] );
  }
  
  return _PT;
}
