#include "RetardedTimeDerivative.h"

template<>
InputParameters validParams<RetardedTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addParam<int>("index", 0, "The index of the coupling variable. Must be given in same order of appearance as in the FlowProperties Material block. Indexing starts from 0. 0 is default value.");
  return params;
}


RetardedTimeDerivative::RetardedTimeDerivative(const std::string & name,
                                       InputParameters parameters)
:TimeDerivative(name,parameters),
_index(getParam<int>("index")),
_retardation(getMaterialProperty<std::vector<Real> >("retardation"))
{

}

Real
RetardedTimeDerivative::computeQpResidual()
{
  return _retardation[_qp][_index] * TimeDerivative::computeQpResidual();
}

Real
RetardedTimeDerivative::computeQpJacobian()
{
  return _retardation[_qp][_index] * TimeDerivative::computeQpJacobian();
}
