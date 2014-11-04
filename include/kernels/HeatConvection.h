#ifndef HEATCONVECTION_H
#define HEATCONVECTION_H

#include "Kernel.h"

// Forward Declaration
class HeatConvection;


template<>
InputParameters validParams<HeatConvection>();

class HeatConvection : public Kernel
{
public:
  
  HeatConvection(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
  RealVectorValue _vel;
  
private:
  int _dir;
  MaterialProperty<Real> & _velocity;
  MaterialProperty<Real> & _gas_density;
  MaterialProperty<Real> & _gas_heat_capacity;
};

#endif // HEATCONVECTION_H
