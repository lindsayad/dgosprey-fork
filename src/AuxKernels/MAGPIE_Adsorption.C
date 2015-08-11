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
_magpie_dat(getMaterialProperty<MAGPIE_DATA>("magpie_data"))
{
}

Real
MAGPIE_Adsorption::computeValue()
{
	return _magpie_dat[_qp].gpast_dat[_index].q;
}
