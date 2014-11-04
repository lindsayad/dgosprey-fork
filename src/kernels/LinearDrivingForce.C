#include "LinearDrivingForce.h"
#include "Material.h"

template<>
InputParameters validParams<LinearDrivingForce>()
{
  InputParameters params = validParams<Kernel>();
	params.addParam<bool>("gaining","True if driving force is a gaining term and false if driving force is a loss term");
	params.addParam<Real>("coefficient","Coefficient multiplied by driving force");
	params.addParam<Real>("driving_value","Value of driving force for the conserved quantity");
  params.addCoupledVar("coupled", "Coupled variable of the conserved quantity");
  return params;
}


LinearDrivingForce::LinearDrivingForce(const std::string & name, InputParameters parameters)
  :Kernel(name,parameters),
   _gaining(getParam<bool>("gaining")),
   _coef(getParam<Real>("coefficient")),
   _driving_value(getParam<Real>("driving_value")),
   _var(coupledValue("coupled"))
{
}

Real LinearDrivingForce::computeQpResidual()
{
  if (_gaining == false)
  	return -_test[_i][_qp] * _coef * (_driving_value - _var[_qp]);
  else
	return _test[_i][_qp] * _coef * (_driving_value - _var[_qp]);
  
}

Real LinearDrivingForce::computeQpJacobian()
{
  return 0.0; //In this case, Jacobian is zero because var is not necessarily u
  /*
   If _var == _u (i.e. same variable),
   then
   return +/- _test[_i][_qp] * _coef * _phi[_j][_qp]
   
   May want to check for equality of variable or hard code different versions
   */
}

