#ifndef DGDISPERSION_H
#define DGDISPERSION_H

#include "DGKernel.h"
#include <cmath>

//Forward Declarations
class DGDispersion;

template<>
InputParameters validParams<DGDispersion>();

class DGDispersion : public DGKernel
{
public:
  DGDispersion(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);
  
  Real _epsilon;
  Real _sigma;
private:
  int _index;
  MaterialProperty<std::vector<Real> > & _dispersion;
};

#endif //DGDISPERSION_H