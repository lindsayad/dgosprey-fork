//----------------------------------------
//  Created by Austin Ladshaw on 09/10/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "MAGPIE_Perturbation.h"

template<>
InputParameters validParams<MAGPIE_Perturbation>()
{
	InputParameters params = validParams<AuxKernel>();
	params.addParam<unsigned int>("index",0,"Index of the species that we are interested in.");
	return params;
}

MAGPIE_Perturbation::MAGPIE_Perturbation(const InputParameters & parameters) :
AuxKernel(parameters),
_index(getParam<unsigned int>("index")),
_magpie_dat(getMaterialProperty< MAGPIE_DATA >("magpie_data"))
{
}

Real
MAGPIE_Perturbation::computeValue()
{
	MAGPIE_DATA magpie_copy;
	magpie_copy = _magpie_dat[_qp];
	
	
	//Check for adsorption
	if (_magpie_dat[_qp].gsta_dat[_index].qmax > 0.0)
	{
		//perturn the copy's _index y
		double pi = _magpie_dat[_qp].gpast_dat[_index].y * _magpie_dat[_qp].sys_dat.PT;
		double ci = Cstd(pi,_magpie_dat[_qp].sys_dat.T) + sqrt(DBL_EPSILON);
		double yi = Pstd(ci,_magpie_dat[_qp].sys_dat.T) / _magpie_dat[_qp].sys_dat.PT;
		magpie_copy.gpast_dat[_index].y = yi;
	
	
		int success = 0;
		success = MAGPIE( (void *)&magpie_copy );
		if (success < 0 || success > 3) {mError(simulation_fail);}
		else success = 0;
		
		return magpie_copy.gpast_dat[_index].q;
	}
	else
	{
		return 0.0;
	}
}

