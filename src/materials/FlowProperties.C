#include "FlowProperties.h"

template<>
// input parameters are the parameters that are constant and not calculated from other parameters
InputParameters validParams<FlowProperties>()
{
  InputParameters params = validParams<Material>();
  
  params.addParam<std::vector<Real> >("molecular_wieght","Molecular wieghts of each gas phase component (g/mol)");
  params.addParam<std::vector<Real> >("comp_heat_capacity","Heat capacity of each gas phase component (J/g/K)");
  params.addParam<std::vector<Real> >("comp_ref_viscosity","Reference viscosities for each gas phase component (g/cm/s)");
  params.addParam<std::vector<Real> >("comp_ref_temp","Reference temperature for each gas phase component (K)");
  params.addParam<std::vector<Real> >("comp_Sutherland_const","Sutherland's constant for each gas phase component (K)");
  params.addParam<Real>("flow_rate","Volumetric flow rate in the system (cm^3/hr");
  params.addCoupledVar("temperature","Coupled variable for temperature");
  params.addCoupledVar("coupled_gases", "Gas concentrations variables being coupled");
  
  return params;
}

FlowProperties::FlowProperties(const std::string & name,
                             InputParameters parameters)
:Material(name, parameters),

_molecular_wieght(getParam<std::vector<Real> >("molecular_wieght")),
_comp_heat_capacity(getParam<std::vector<Real> >("comp_heat_capacity")),
_comp_ref_viscosity(getParam<std::vector<Real> >("comp_ref_viscosity")),
_comp_ref_temp(getParam<std::vector<Real> >("comp_ref_temp")),
_comp_Sutherland_const(getParam<std::vector<Real> >("comp_Sutherland_const")),
_flow_rate(getParam<Real>("flow_rate")),
_velocity(declareProperty<Real>("velocity")),
_gas_density(declareProperty<Real>("gas_density")),
_gas_viscosity(declareProperty<Real>("gas_viscosity")),
_gas_heat_capacity(declareProperty<Real>("gas_heat_capacity")),
_gas_molecular_wieght(declareProperty<Real>("gas_molecular_wieght")),
_inner_dia(getMaterialProperty<Real>("inner_dia")),
_porosity(getMaterialProperty<Real>("porosity")),
_molecular_diffusion(declareProperty<std::vector<Real> >("molecular_diffusion")),
_dispersion(declareProperty<std::vector<Real> >("dispersion")),
_retardation(declareProperty<std::vector<Real> >("retardation")),
_temperature(coupledValue("temperature"))

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
   
   Opposite for materials
   _molecular_diffusion[_qp][i] = Dm[_qp][i]
	 */
}

void
FlowProperties::computeQpProperties()
{
  _velocity[_qp] = (_flow_rate / (_porosity[_qp] * (M_PI/4.0) * _inner_dia[_qp] * _inner_dia[_qp]));
  _gas_density[_qp] = 1.0;
  _gas_viscosity[_qp] = 1.0; //change this
  _gas_heat_capacity[_qp] = 1.0; //change this
  _gas_molecular_wieght[_qp] = 1.0; //change this
  
  _molecular_diffusion[_qp].resize(_gas_conc.size());
  _dispersion[_qp].resize(_gas_conc.size());
  _retardation[_qp].resize(_gas_conc.size());
  
  for (unsigned int i = 0; i<_gas_conc.size(); ++i)
  {
    //Don't remember what this was for...
    //(*_molecular_diffusion[i])[_qp] = 1.0;
    //(*_dispersion[i])[_qp] = 1.0;
    //(*_retardation[i])[_qp] = 1.0;
    
    _molecular_diffusion[_qp][i] = 1.0; //change all these
    //_dispersion[_qp][i] = 6.292E-05; //maual override
    _dispersion[_qp][i] = 0.04;        //used in tests
    _retardation[_qp][i] = 1.0; //add adsorption here
  }
  //Manual override for H2O
  //_retardation[_qp][2] = 288475.94; //manual override

}
