//----------------------------------------
//  Created by Austin Ladshaw on 08/10/2015
//  Copyright (c) 2015
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#include "MagpieAdsorbateProperties.h"

template<>
// input parameters are the parameters that are constant and not calculated from other parameters
InputParameters validParams<MagpieAdsorbateProperties>()
{
	InputParameters params = validParams<Material>();

	params.addCoupledVar("temperature","Coupled variable for temperature");
	params.addCoupledVar("total_pressure","Coupled variable for total pressure");
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

MagpieAdsorbateProperties::MagpieAdsorbateProperties(const InputParameters & parameters)
:Material(parameters),

_temperature(coupledValue("temperature")),
_total_pressure(coupledValue("total_pressure")),
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
_entropy_6(getParam<std::vector<Real> >("entropy_site_6")),

_magpie_dat(declareProperty< MAGPIE_DATA >("magpie_data"))
{
	unsigned int n = coupledComponents("coupled_gases");
	_index.resize(n);
	_gas_conc.resize(n);
	
	for (unsigned int i = 0; i<_gas_conc.size(); ++i)
	{
		_index[i] = coupled("coupled_gases",i);
		_gas_conc[i] = &coupledValue("coupled_gases",i);
	}
	
	//Loop over _qp (Note: wanted to do this for initialization, but this didn't work)
	/*
	for (unsigned int _qp=0; _qp<_qrule->n_points(); _qp++)
	{
	
	}
	 */
}

void
MagpieAdsorbateProperties::computeQpProperties()
{	
	//Only setup working space if it has not yet been set up
	if (_magpie_dat[_qp].sys_dat.N != _gas_conc.size())
	{
		_magpie_dat[_qp].sys_dat.N = _gas_conc.size();
		_magpie_dat[_qp].gpast_dat.resize(_magpie_dat[_qp].sys_dat.N);
		_magpie_dat[_qp].gsta_dat.resize(_magpie_dat[_qp].sys_dat.N);
		_magpie_dat[_qp].mspd_dat.resize(_magpie_dat[_qp].sys_dat.N);
	
		for (int i=0; i<_magpie_dat[_qp].sys_dat.N; i++)
		{
			_magpie_dat[_qp].mspd_dat[i].eta.resize(_magpie_dat[_qp].sys_dat.N);
			_magpie_dat[_qp].gpast_dat[i].gama_inf.resize(_magpie_dat[_qp].sys_dat.N);
			_magpie_dat[_qp].gpast_dat[i].po.resize(_magpie_dat[_qp].sys_dat.N);
			
			_magpie_dat[_qp].gsta_dat[i].qmax = _max_capacity[i];
			
			//This species is adsorbable
			if (_magpie_dat[_qp].gsta_dat[i].qmax > 0.0)
			{
				_magpie_dat[_qp].mspd_dat[i].v = _molar_volume[i];
				_magpie_dat[_qp].gsta_dat[i].m = _num_sites[i];
				if (_magpie_dat[_qp].gsta_dat[i].m < 1)
					_magpie_dat[_qp].gsta_dat[i].m = 1;
				if (_magpie_dat[_qp].gsta_dat[i].m > 6)
					_magpie_dat[_qp].gsta_dat[i].m = 6;
				_magpie_dat[_qp].gsta_dat[i].dHo.resize(_magpie_dat[_qp].gsta_dat[i].m);
				_magpie_dat[_qp].gsta_dat[i].dSo.resize(_magpie_dat[_qp].gsta_dat[i].m);
				for (int n=0; n<_magpie_dat[_qp].gsta_dat[i].m; n++)
				{
					if (n == 0)
					{
						_magpie_dat[_qp].gsta_dat[i].dHo[n] = _enthalpy_1[i];
						_magpie_dat[_qp].gsta_dat[i].dSo[n] = _entropy_1[i];
					}
					else if (n == 1)
					{
						_magpie_dat[_qp].gsta_dat[i].dHo[n] = _enthalpy_2[i];
						_magpie_dat[_qp].gsta_dat[i].dSo[n] = _entropy_2[i];
					}
					else if (n == 2)
					{
						_magpie_dat[_qp].gsta_dat[i].dHo[n] = _enthalpy_3[i];
						_magpie_dat[_qp].gsta_dat[i].dSo[n] = _entropy_3[i];
					}
					else if (n == 3)
					{
						_magpie_dat[_qp].gsta_dat[i].dHo[n] = _enthalpy_4[i];
						_magpie_dat[_qp].gsta_dat[i].dSo[n] = _entropy_4[i];
					}
					else if (n == 4)
					{
						_magpie_dat[_qp].gsta_dat[i].dHo[n] = _enthalpy_5[i];
						_magpie_dat[_qp].gsta_dat[i].dSo[n] = _entropy_5[i];
					}
					else if (n == 5)
					{
						_magpie_dat[_qp].gsta_dat[i].dHo[n] = _enthalpy_6[i];
						_magpie_dat[_qp].gsta_dat[i].dSo[n] = _entropy_6[i];
					}
					else
					{
						_magpie_dat[_qp].gsta_dat[i].dHo[n] = 0.0;
						_magpie_dat[_qp].gsta_dat[i].dSo[n] = 0.0;
					}
				}
			}
			//This species will not adsorb
			else
			{
				_magpie_dat[_qp].gsta_dat[i].qmax = 0.0;
				_magpie_dat[_qp].mspd_dat[i].v = 0;
				_magpie_dat[_qp].gsta_dat[i].m = 1;
				_magpie_dat[_qp].gsta_dat[i].dHo.resize(_magpie_dat[_qp].gsta_dat[i].m);
				_magpie_dat[_qp].gsta_dat[i].dSo.resize(_magpie_dat[_qp].gsta_dat[i].m);
				for (int n=0; n<_magpie_dat[_qp].gsta_dat[i].m; n++)
				{
					_magpie_dat[_qp].gsta_dat[i].dHo[n] = 0.0;
					_magpie_dat[_qp].gsta_dat[i].dSo[n] = 0.0;
				}
			}
		}
	}// END if Not Initialized
	
	_magpie_dat[_qp].sys_dat.total_eval = 0;
	_magpie_dat[_qp].sys_dat.avg_norm = 0;
	_magpie_dat[_qp].sys_dat.max_norm = 0;
	_magpie_dat[_qp].sys_dat.Recover = false;
	_magpie_dat[_qp].sys_dat.Carrier = false;
	_magpie_dat[_qp].sys_dat.Ideal = false;
	_magpie_dat[_qp].sys_dat.Output = false;
	
	_magpie_dat[_qp].sys_dat.PT = _total_pressure[_qp];
	_magpie_dat[_qp].sys_dat.T = _temperature[_qp];
	
	double tempPT = 0.0;
	
	//Loop over all gas species
	for (int i=0; i<_magpie_dat[_qp].sys_dat.N; i++)
	{
		double pi = (*_gas_conc[i])[_qp] * 8.3144621 * _temperature[_qp];
		if (pi < 0.0)
			pi = 0.0;
		tempPT = pi + tempPT;	
	}
	_magpie_dat[_qp].sys_dat.PT = tempPT;
	
	for (int i=0; i<_magpie_dat[_qp].sys_dat.N; i++)
	{
		double pi = (*_gas_conc[i])[_qp] * 8.3144621 * _temperature[_qp];
		if (pi < 0.0)
			pi = 0.0;
		
		if (_magpie_dat[_qp].gsta_dat[i].qmax == 0.0)
		{
			_magpie_dat[_qp].sys_dat.Carrier = true;
			_magpie_dat[_qp].gpast_dat[i].y = 0.0;
		}
		else
		{
			_magpie_dat[_qp].gpast_dat[i].y = pi / tempPT;
		}
		
		if (_magpie_dat[_qp].gpast_dat[i].y < 0.0)
			_magpie_dat[_qp].gpast_dat[i].y = 0.0;
	}
	
}

