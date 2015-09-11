//----------------------------------------
//  Created by Austin Ladshaw on 09/10/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "AuxKernel.h"
#include "flock.h"

#ifndef MAGPIE_Perturbation_H
#define MAGPIE_Perturbation_H

class MAGPIE_Perturbation;

template<>
InputParameters validParams<MAGPIE_Perturbation>();

class MAGPIE_Perturbation : public AuxKernel
{
public:
	MAGPIE_Perturbation(const InputParameters & parameters);
	
protected:
	virtual Real computeValue();
private:
	unsigned int _index;
	const MaterialProperty< MAGPIE_DATA > & _magpie_dat;
	
};

#endif
