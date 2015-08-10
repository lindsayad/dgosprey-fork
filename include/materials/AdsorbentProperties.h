#include "Material.h"

#ifndef ADSORBENTPROPERTIES_H
#define ADSORBENTPROPERTIES_H

//Forward Declarations
class AdsorbentProperties;

template<>
InputParameters validParams<AdsorbentProperties>();

class AdsorbentProperties : public Material
{
public:
	AdsorbentProperties(const InputParameters & parameters);
	
protected:
	virtual void computeQpProperties();
	
private:
  Real _binder_fraction;
  Real _binder_porosity; //Note: tortuosity will be 1/porosity
  Real _crystal_radius;
  Real _pellet_diameter;
  Real _macropore_radius;
  Real _rhos;
  Real _hs;
  
  MaterialProperty<Real> & _pellet_density;
  MaterialProperty<Real> & _pellet_heat_capacity;
	
  VariableValue & _temperature;
	std::vector<unsigned int> _index;
	std::vector<VariableValue *> _gas_conc;
	
};


#endif //ADSORBENTPROPERTIES_H
