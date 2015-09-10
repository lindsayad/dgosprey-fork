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
_magpie_perturbation(getMaterialProperty< MAGPIE_DATA >("magpie_perturbation"))
{
}

Real
MAGPIE_Perturbation::computeValue()
{
	return _magpie_perturbation[_qp].gpast_dat[_index].q;
}

