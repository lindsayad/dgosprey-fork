#ifndef BEDHEATACCUMULATION_H
#define BEDHEATACCUMULATION_H

#include "TimeDerivative.h"

//Forward Declarations
class BedHeatAccumulation;

template<>
InputParameters validParams<BedHeatAccumulation>();

class BedHeatAccumulation : public TimeDerivative
{
public:
  
  BedHeatAccumulation(const std::string & name,
                       InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  MaterialProperty<Real> & _gas_density;
  MaterialProperty<Real> & _gas_heat_capacity;
  MaterialProperty<Real> & _pellet_density;
  MaterialProperty<Real> & _pellet_heat_capacity;
  MaterialProperty<Real> & _porosity;
};

#endif // BEDHEATACCUMULATION_H
