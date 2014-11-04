#include "Kernel.h"

#ifndef LINEARDRIVINGFORCE_H
#define LINEARDRIVINGFORCE_H

class LinearDrivingForce;

template<>
InputParameters validParams<LinearDrivingForce>();

class LinearDrivingForce : public Kernel
{
public:
  LinearDrivingForce(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian(); 

private:
	bool _gaining;
	Real _coef;
	Real _driving_value;
	VariableValue & _var;

};
#endif //LINEARDRIVINGFORCE_H
