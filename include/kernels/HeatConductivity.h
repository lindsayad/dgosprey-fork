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
  
  HeatConductivity(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  MaterialProperty<Real> & _conductivity;
};

#endif //HEATCONDUCTIVITY_H