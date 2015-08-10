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
	VariableValue & _temperature;
	VariableValue & _total_pressure;
	std::vector<unsigned int> _index;
	std::vector<VariableValue *> _gas_conc;
	MAGPIE_DATA magpie_dat;
	
};

#endif
