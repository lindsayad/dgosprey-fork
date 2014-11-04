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
  
  RetardedTimeDerivative(const std::string & name,
                     InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  int _index;
  MaterialProperty<std::vector<Real> > & _retardation;
};

#endif //RETARDEDTIMEDERIVATIVE_H
