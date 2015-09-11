//----------------------------------------
//  Created by Austin Ladshaw on 08/10/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "Material.h"
#include "flock.h"

#ifndef MAGPIEADSORBATEPROPERTIES_H
#define MAGPIEADSORBATEPROPERTIES_H

//Forward Declarations
class MagpieAdsorbateProperties;

template<>
InputParameters validParams<MagpieAdsorbateProperties>();

class MagpieAdsorbateProperties : public Material
{
public:
	MagpieAdsorbateProperties(const InputParameters & parameters);
	
protected:
	virtual void computeQpProperties();
	
private:
	
	std::vector<unsigned int> _index;
	VariableValue & _temperature;
	VariableValue & _total_pressure;
	std::vector<VariableValue *> _gas_conc;
	
	std::vector<int> _num_sites;
	std::vector<Real> _max_capacity;
	std::vector<Real> _molar_volume;
	
	std::vector<Real> _enthalpy_1;
	std::vector<Real> _enthalpy_2;
	std::vector<Real> _enthalpy_3;
	std::vector<Real> _enthalpy_4;
	std::vector<Real> _enthalpy_5;
	std::vector<Real> _enthalpy_6;
	
	std::vector<Real> _entropy_1;
	std::vector<Real> _entropy_2;
	std::vector<Real> _entropy_3;
	std::vector<Real> _entropy_4;
	std::vector<Real> _entropy_5;
	std::vector<Real> _entropy_6;
	
	MaterialProperty< MAGPIE_DATA > & _magpie_dat;
};

#endif //MAGPIEADSORBATEPROPERTIES_H
