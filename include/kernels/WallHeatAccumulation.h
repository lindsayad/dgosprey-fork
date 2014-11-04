#ifndef WALLHEATACCUMULATION_H
#define WALLHEATACCUMULATION_H

#include "TimeDerivative.h"

//Forward Declarations
class WallHeatAccumulation;

template<>
InputParameters validParams<WallHeatAccumulation>();

class WallHeatAccumulation : public TimeDerivative
{
public:
  
  WallHeatAccumulation(const std::string & name,
                         InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  MaterialProperty<Real> & _wall_density;
  MaterialProperty<Real> & _wall_heat_capacity;
};

#endif //WALLHEATACCUMULATION_H
