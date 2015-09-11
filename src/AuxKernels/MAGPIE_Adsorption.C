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
_magpie_dat(getMaterialProperty< MAGPIE_DATA >("magpie_data"))
{
}

Real
MAGPIE_Adsorption::computeValue()
{
	MAGPIE_DATA magpie_copy;
	magpie_copy = _magpie_dat[_qp];
	
	//Call MAGPIE Simulation for Unperturbed data
	if (_magpie_dat[_qp].gsta_dat[_index].qmax > 0.0)
	{
		int success = 0;
		success = MAGPIE( (void *)&magpie_copy );
		if (success < 0 || success > 3) {mError(simulation_fail);}
		else success = 0;
	
		return magpie_copy.gpast_dat[_index].q;
		
		//Temporary override to demonstrate LDF kinetics
		//double k = magpie_copy.gpast_dat[_index].q * 0.008;
		//double qe = magpie_copy.gpast_dat[_index].q;
		//return (_u_old[_qp] + (_dt*k*qe))/(1.0+(_dt*k));
	}
	else
	{
		return 0.0;
	}
}
