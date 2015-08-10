#include "Material.h"
#include "flock.h"

#ifndef FLOWPROPERTIES_H
#define FLOWPROPERTIES_H

//Forward Declarations
class FlowProperties;

template<>
InputParameters validParams<FlowProperties>();

class FlowProperties : public Material
{
public:
	FlowProperties(const InputParameters & parameters);
	
protected:
	virtual void computeQpProperties();
	
private:
	std::vector<Real> _molecular_wieght;
	std::vector<Real> _comp_heat_capacity;
	std::vector<Real> _comp_ref_viscosity;
	std::vector<Real> _comp_ref_temp;
	std::vector<Real> _comp_Sutherland_const;
	Real _flow_rate;
	Real _column_length;
  
	MaterialProperty<Real> & _velocity;
	MaterialProperty<Real> & _gas_density;
	MaterialProperty<Real> & _gas_viscosity;
	MaterialProperty<Real> & _gas_heat_capacity;
	MaterialProperty<Real> & _gas_molecular_wieght;
	
	const MaterialProperty<Real> & _inner_dia;
	const MaterialProperty<Real> & _porosity;
	const MaterialProperty<Real> & _pellet_density;
	const MaterialProperty<Real> & _pellet_heat_capacity;
	
	MaterialProperty<Real> & _heat_retardation;
	MaterialProperty<std::vector<Real> > & _molecular_diffusion;
	MaterialProperty<std::vector<Real> > & _dispersion;
	MaterialProperty<std::vector<Real> > & _retardation;
  	
  	VariableValue & _temperature;
	VariableValue & _total_pressure;
	std::vector<unsigned int> _index;
	std::vector<VariableValue *> _gas_conc;
	
};


#endif //FLOWPROPERTIES_H