//----------------------------------------
//  Created by Austin Ladshaw on 09/14/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#ifndef MAGPIE_HeatAccumulation_H
#define MAGPIE_HeatAccumulation_H

#include "Kernel.h"

//Forward Declarations
class MAGPIE_HeatAccumulation;

template<>
InputParameters validParams<MAGPIE_HeatAccumulation>();

class MAGPIE_HeatAccumulation : public Kernel
{
public:
	
	MAGPIE_HeatAccumulation(const InputParameters & parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
	const MaterialProperty<Real> & _porosity;
	const MaterialProperty<Real> & _pellet_density;
	VariableValue & _solid_heat;
	VariableValue & _solid_heat_old;
	VariableValue & _solid_heat_older;
};

#endif