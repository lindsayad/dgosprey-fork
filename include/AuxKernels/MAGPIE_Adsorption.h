//----------------------------------------
//  Created by Austin Ladshaw on 08/10/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "AuxKernel.h"
#include "flock.h"

#ifndef MAGPIE_Adsorption_H
#define MAGPIE_Adsorption_H

class MAGPIE_Adsorption;

template<>
InputParameters validParams<MAGPIE_Adsorption>();

class MAGPIE_Adsorption : public AuxKernel
{
public:
	MAGPIE_Adsorption(const InputParameters & parameters);
	
protected:
	virtual Real computeValue();
private:
	unsigned int _index;
	const MaterialProperty< MAGPIE_DATA > & _magpie_dat;
	const MaterialProperty< Real > & _temp_q;
	
};

#endif
