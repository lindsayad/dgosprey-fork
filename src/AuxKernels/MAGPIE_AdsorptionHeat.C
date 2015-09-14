//----------------------------------------
//  Created by Austin Ladshaw on 08/11/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "MAGPIE_AdsorptionHeat.h"

template<>
InputParameters validParams<MAGPIE_AdsorptionHeat>()
{
	InputParameters params = validParams<AuxKernel>();
	params.addParam<unsigned int>("index",0,"Index of the species that we are interested in.");
	params.addCoupledVar("solid_conc","Coupled variable for the solid concentration of interest");
	return params;
}

MAGPIE_AdsorptionHeat::MAGPIE_AdsorptionHeat(const InputParameters & parameters) :
AuxKernel(parameters),
_index(getParam<unsigned int>("index")),
_magpie_dat(getMaterialProperty< MAGPIE_DATA >("magpie_data")),
_solid_conc(coupledValue("solid_conc"))
{
}

Real
MAGPIE_AdsorptionHeat::computeValue()
{
	MAGPIE_DATA magpie_copy;
	magpie_copy = _magpie_dat[_qp];
	
	//Call MAGPIE Simulation for Unperturbed data
	if (_magpie_dat[_qp].gsta_dat[_index].qmax > 0.0)
	{
		//int success = 0;
		//success = MAGPIE( (void *)&magpie_copy );
		//if (success < 0 || success > 3) {mError(simulation_fail);}
		//else success = 0;
		
		double pi = magpie_copy.gpast_dat[_index].y * magpie_copy.sys_dat.PT;
		return _solid_conc[_qp] * Qst(pi,(void *)&magpie_copy,_index);
	}
	else
	{
		return 0.0;
	}
}
