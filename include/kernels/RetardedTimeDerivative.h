#ifndef RETARDEDTIMEDERIVATIVE_H
#define RETARDEDTIMEDERIVATIVE_H

#include "TimeDerivative.h"

//Forward Declarations
class RetardedTimeDerivative;

template<>
InputParameters validParams<RetardedTimeDerivative>();

class RetardedTimeDerivative : public TimeDerivative
{
public:
  
  RetardedTimeDerivative(const InputParameters & parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  int _index;
  const MaterialProperty<std::vector<Real> > & _retardation;
};

#endif //RETARDEDTIMEDERIVATIVE_H
