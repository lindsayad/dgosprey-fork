#ifndef DISPERSION_H
#define DISPERSION_H

#include "Kernel.h"

//Forward Declarations
class Dispersion;

template<>
InputParameters validParams<Dispersion>();

class Dispersion : public Kernel
{
public:
  
  Dispersion(const InputParameters & parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  int _index;
  const MaterialProperty<std::vector<Real> > & _dispersion;
};

#endif //DISPERSION_H