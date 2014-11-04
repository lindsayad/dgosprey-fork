#include "TotalColumnPressure.h"

template<>
InputParameters validParams<TotalColumnPressure>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("temperature","Coupled variable for temperature");
  params.addCoupledVar("coupled_gases", "Gas concentrations variables being coupled");
  return params;
}

TotalColumnPressure::TotalColumnPressure(const std::string & name, InputParameters parameters) :
AuxKernel(name, parameters),
_temperature(coupledValue("temperature"))
{
  unsigned int n = coupledComponents("coupled_gases");
	_index.resize(n);
	_gas_conc.resize(n);
	
	for (unsigned int i = 0; i<_gas_conc.size(); ++i)
	{
		_index[i] = coupled("coupled_gases",i); //may only be useful for compute Jacobian Off Diagonal (see ~/projects/truck/moose/modules/chemical_reactions/ .../ CoupledConvectionReactionSub.C)
		_gas_conc[i] = &coupledValue("coupled_gases",i);
	}
	/*
	 Note: When using _gas_conc[i], it must be appropriately dereferenced as follows...
	 (*_gas_conc[i])[_qp] = concentration of species i at node _qp
	 */
}

Real
TotalColumnPressure::computeValue()
{
	Real _PT = 0.0;
  
  for (unsigned int i = 0; i<_gas_conc.size(); ++i)
  {
    Real _tmp = 0.0;
    if ((*_gas_conc[i])[_qp] < 0.0) //This catches negative concentrations and sets them to zero
      _tmp = 0.0;
    else														//NOTE: We have not assigned a tolerance here, so this may be unstable
      _tmp = (*_gas_conc[i])[_qp];
    _PT = _PT + ( _tmp * 8.3144621 * _temperature[_qp] );
  }
  
  return _PT;
}
