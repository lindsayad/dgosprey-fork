//----------------------------------------
//  Created by Austin Ladshaw on 08/11/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "MAGPIE_Adsorption.h"

template<>
InputParameters validParams<MAGPIE_Adsorption>()
{
	InputParameters params = validParams<AuxKernel>();
	params.addParam<unsigned int>("index",0,"Index of the species that we are interested in.");
	return params;
}

MAGPIE_Adsorption::MAGPIE_Adsorption(const InputParameters & parameters) :
AuxKernel(parameters),
_index(getParam<unsigned int>("index")),
_magpie_dat(getMaterialProperty< MAGPIE_DATA >("magpie_data")),
_temp_q(getMaterialProperty< Real >("temp_q"))
{
}

Real
MAGPIE_Adsorption::computeValue()
{
	//std::cout << "H2O @ " << _qp << " = " << _magpie_dat[_qp].gpast_dat[_index].q << std::endl;//This is correct, so why is the result wrong?
	
	Real _q = 0.0;
	_q = _magpie_dat[_qp].gpast_dat[_index].q;
	if (_q < 0.0)
		std::cout << "Impossible value = " << _q << std::endl;
	_u[_qp] = _q;
	
	//All values for all _qp in the material are correct, but the postprocessor does not calculate the average correctly
	/*
	for (int n=0; n<_magpie_dat.size(); n++)
	{
		//std::cout << "n = " << n << "\tq = " << _magpie_dat[n].gpast_dat[_index].q << std::endl;
	 
		//Some how u is not being set to the correct value
		//std::cout << "n = " << n << "\tq = " << _u[_qp] << std::endl;
	}
	*/
	
	//By all accounts, this should be working just fine, but it is not even remotely close to working
	_q = _temp_q[_qp];
	return _q;
}
