#ifndef HEATCONDUCTIVITY_H
#define HEATCONDUCTIVITY_H

#include "Kernel.h"

//Forward Declarations
class HeatConductivity;

template<>
InputParameters validParams<HeatConductivity>();

class HeatConductivity : public Kernel
{
public:
  
  HeatConductivity(const InputParameters & parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  const MaterialProperty<Real> & _conductivity;
  const MaterialProperty<Real> & _porosity;
};

#endif //HEATCONDUCTIVITY_H