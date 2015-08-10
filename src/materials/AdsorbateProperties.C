//----------------------------------------
//  Created by Austin Ladshaw on 08/10/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "AdsorbateProperties.h"

template<>
// input parameters are the parameters that are constant and not calculated from other parameters
InputParameters validParams<AdsorbateProperties>()
{
	InputParameters params = validParams<Material>();

	params.addCoupledVar("coupled_gases", "Gas concentrations variables being coupled");
	
	params.addParam<std::vector<int> >("number_sites","The number of adsorption sites for each species in GSTA isotherm");
	params.addParam<std::vector<Real> >("maximum_capacity","The adsorption capacity for each species in the GSTA isotherm (mol/kg)");
	params.addParam<std::vector<Real> >("molar_volume","The van der Waals molar volume of each species (mol/cm^3)");
	params.addParam<std::vector<Real> >("enthalpy_site_1","The molar enthalpy of the species on site 1");
	params.addParam<std::vector<Real> >("enthalpy_site_2","The molar enthalpy of the species on site 2");
	params.addParam<std::vector<Real> >("enthalpy_site_3","The molar enthalpy of the species on site 3");
	params.addParam<std::vector<Real> >("enthalpy_site_4","The molar enthalpy of the species on site 4");
	params.addParam<std::vector<Real> >("enthalpy_site_5","The molar enthalpy of the species on site 5");
	params.addParam<std::vector<Real> >("enthalpy_site_6","The molar enthalpy of the species on site 6");
	
	params.addParam<std::vector<Real> >("entropy_site_1","The molar entropy of the species on site 1");
	params.addParam<std::vector<Real> >("entropy_site_2","The molar entropy of the species on site 2");
	params.addParam<std::vector<Real> >("entropy_site_3","The molar entropy of the species on site 3");
	params.addParam<std::vector<Real> >("entropy_site_4","The molar entropy of the species on site 4");
	params.addParam<std::vector<Real> >("entropy_site_5","The molar entropy of the species on site 5");
	params.addParam<std::vector<Real> >("entropy_site_6","The molar entropy of the species on site 6");
	
	
	return params;
}

AdsorbateProperties::AdsorbateProperties(const InputParameters & parameters)
:Material(parameters),

_num_sites(getParam<std::vector<int> >("number_sites")),
_max_capacity(getParam<std::vector<Real> >("maximum_capacity")),
_molar_volume(getParam<std::vector<Real> >("molar_volume")),
_enthalpy_1(getParam<std::vector<Real> >("enthalpy_site_1")),
_enthalpy_2(getParam<std::vector<Real> >("enthalpy_site_2")),
_enthalpy_3(getParam<std::vector<Real> >("enthalpy_site_3")),
_enthalpy_4(getParam<std::vector<Real> >("enthalpy_site_4")),
_enthalpy_5(getParam<std::vector<Real> >("enthalpy_site_5")),
_enthalpy_6(getParam<std::vector<Real> >("enthalpy_site_6")),

_entropy_1(getParam<std::vector<Real> >("entropy_site_1")),
_entropy_2(getParam<std::vector<Real> >("entropy_site_2")),
_entropy_3(getParam<std::vector<Real> >("entropy_site_3")),
_entropy_4(getParam<std::vector<Real> >("entropy_site_4")),
_entropy_5(getParam<std::vector<Real> >("entropy_site_5")),
_entropy_6(getParam<std::vector<Real> >("entropy_site_6"))

{
	unsigned int n = coupledComponents("coupled_gases");
	_index.resize(n);
	_gas_conc.resize(n);
	
	for (unsigned int i = 0; i<_gas_conc.size(); ++i)
	{
		_index[i] = coupled("coupled_gases",i); //may only be useful for compute Jacobian Off Diagonal (see ~/projects/truck/moose/modules/chemical_reactions/ .../ CoupledConvectionReactionSub.C)
		_gas_conc[i] = &coupledValue("coupled_gases",i);
	}
	/*
	 Note: When using _gas_conc[i], it must be appropriately dereferenced as follows...
	 (*_gas_conc[i])[_qp] = concentration of species i at node _qp
	 */
}

void
AdsorbateProperties::computeQpProperties()
{
	//Nothing to compute, we just use this object for storage and comunication with other files
}

