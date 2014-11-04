#ifndef ADVECTION_H
#define ADVECTION_H

#include "Kernel.h"

// Forward Declaration
class Advection;


template<>
InputParameters validParams<Advection>();

class Advection : public Kernel
{
public:
  
  Advection(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
  RealVectorValue _vel;
  
private:
  int _dir;
  MaterialProperty<Real> & _velocity;
};

#endif // ADVECTION_H
