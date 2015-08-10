#include "Material.h"

#ifndef BEDPROPERTIES_H
#define BEDPROPERTIES_H

//Forward Declarations
class BedProperties;

template<>
InputParameters validParams<BedProperties>();

class BedProperties : public Material
{
public:
  BedProperties(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

private:
  Real _length;
  Real _din;
  Real _dout;
  Real _eb;
  Real _Kz;
  Real _rhow;
  Real _hw;
  Real _Uw;
  Real _Ua;
  MaterialProperty<Real> & _inner_dia;
  MaterialProperty<Real> & _outer_dia;
  MaterialProperty<Real> & _porosity;
  MaterialProperty<Real> & _conductivity;
  MaterialProperty<Real> & _wall_density;
  MaterialProperty<Real> & _wall_heat_capacity;
  MaterialProperty<Real> & _bed_wall_transfer_coeff;
  MaterialProperty<Real> & _wall_exterior_transfer_coeff;
	
  VariableValue & _temperature;
  std::vector<unsigned int> _index;
  std::vector<VariableValue *> _gas_conc;

};

#endif //BEDPROPERTIESL_H
