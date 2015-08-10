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
  
  WallHeatAccumulation(const InputParameters & parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  const MaterialProperty<Real> & _wall_density;
  const MaterialProperty<Real> & _wall_heat_capacity;
};

#endif //WALLHEATACCUMULATION_H
