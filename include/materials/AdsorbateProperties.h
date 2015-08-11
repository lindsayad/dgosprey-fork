//----------------------------------------
//  Created by Austin Ladshaw on 08/10/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "Material.h"
#include "flock.h"

#ifndef ADSORBATEPROPERTIES_H
#define ADSORBATEPROPERTIES_H

//Forward Declarations
class AdsorbateProperties;

template<>
InputParameters validParams<AdsorbateProperties>();

class AdsorbateProperties : public Material
{
public:
	AdsorbateProperties(const InputParameters & parameters);
	
protected:
	virtual void computeQpProperties();
	
private:
	
	std::vector<unsigned int> _index;
	VariableValue & _temperature;
	VariableValue & _total_pressure;
	std::vector<VariableValue *> _gas_conc;
	
	int _adsorption_type;
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
	
	MaterialProperty< Real > & _temp_q;
	
};

#endif //ADSORBATEPROPERTIES_H
