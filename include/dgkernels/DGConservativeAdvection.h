#ifndef DGCONSERVATIVEADVECTION_H
#define DGCONSERVATIVEADVECTION_H

#include "DGKernel.h"
#include <cmath>

//Forward Declarations
class DGConservativeAdvection;

template<>
InputParameters validParams<DGConservativeAdvection>();

class DGConservativeAdvection : public DGKernel
{
public:
  DGConservativeAdvection(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);
  
  RealVectorValue _vel;
  
private:
  int _dir;
  MaterialProperty<Real> & _velocity;
};

#endif //DGCONSERVATIVEADVECTION_H