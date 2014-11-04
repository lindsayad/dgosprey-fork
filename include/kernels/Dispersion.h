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
  
  Dispersion(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  int _index;
  MaterialProperty<std::vector<Real> > & _dispersion;
};

#endif //DISPERSION_H