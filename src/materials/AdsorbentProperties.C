#include "AdsorbentProperties.h"

template<>
// input parameters are the parameters that are constant and not calculated from other parameters
InputParameters validParams<AdsorbentProperties>()
{
  InputParameters params = validParams<Material>();
  
  params.addParam<Real>("binder_fraction","Binder fraction of the adsorbent pellet");
  params.addParam<Real>("binder_porosity","Porosity of the binder material in the adsorbent pellet");
  params.addParam<Real>("crystal_radius","Radius of the adsorbent crystals in the binder matrix (um)");
  params.addParam<Real>("pellet_diameter","Diameter of the adsorbent pellet (cm)");
  params.addParam<Real>("macropore_radius","Nominal pore size of the macropores in the binder material (cm)");
  params.addParam<Real>("rhos","Density of the adsorbent pellet (g/cm^3)");
  params.addParam<Real>("hs","Pellet heat capacity (J/g/K)");
  params.addCoupledVar("temperature","Coupled variable for temperature");
  params.addCoupledVar("coupled_gases", "Gas concentrations variables being coupled");
  
  return params;
}

AdsorbentProperties::AdsorbentProperties(const std::string & name,
                             InputParameters parameters)
:Material(name, parameters),

_binder_fraction(getParam<Real>("binder_fraction")),
_binder_porosity(getParam<Real>("binder_porosity")),
_crystal_radius(getParam<Real>("crystal_radius")),
_pellet_diameter(getParam<Real>("pellet_diameter")),
_macropore_radius(getParam<Real>("macropore_radius")),
_rhos(getParam<Real>("rhos")),
_hs(getParam<Real>("hs")),
_pellet_density(declareProperty<Real>("pellet_density")),
_pellet_heat_capacity(declareProperty<Real>("pellet_heat_capacity")),
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
	 */
}

void
AdsorbentProperties::computeQpProperties()
{
  //For constant bed properties...
  //std::cout << "here " << _qp << std::endl;
  _pellet_density[_qp] = _rhos;
  _pellet_heat_capacity[_qp] = _hs;
  //Note: some of these may vary with space or temperature or concentration, but for now we assume constant
}
