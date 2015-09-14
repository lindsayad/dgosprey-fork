//----------------------------------------
//  Created by Austin Ladshaw on 08/10/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "AuxKernel.h"
#include "flock.h"

#ifndef MAGPIE_AdsorptionHeat_H
#define MAGPIE_AdsorptionHeat_H

class MAGPIE_AdsorptionHeat;

template<>
InputParameters validParams<MAGPIE_AdsorptionHeat>();

class MAGPIE_AdsorptionHeat : public AuxKernel
{
public:
	MAGPIE_AdsorptionHeat(const InputParameters & parameters);
	
protected:
	virtual Real computeValue();
private:
	unsigned int _index;
	const MaterialProperty< MAGPIE_DATA > & _magpie_dat;
	VariableValue & _solid_conc;
	
};

#endif