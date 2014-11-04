#include "MassPenalty.h"

template<>
InputParameters validParams<MassPenalty>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("penalty", 1.0, "Weight of the penalty.  Penalty = a*(lower - variable) for variable<lower, and zero otherwise.  Care should be taken with this parameter choice.  Determine the typical size of your residual (usually rho*perm*(gradP - rho*g)/visc), then typically you want the penalty to ensure p>lower*(1-1E-6), so for the PPP formulation you typically Penalty = a*1E-6*|p|.  I recommend that Penalty = 1E-3*residual, yielding a = 1E3*residual/|P|. ");
  params.addParam<Real>("lower_bound",0.0,"Value of the lower bound for the variable of interest.");
  return params;
}

MassPenalty::MassPenalty(const std::string & name,
                                             InputParameters parameters) :
Kernel(name,parameters),
_penalty(getParam<Real>("penalty")),
_lower_bound(getParam<Real>("lower_bound"))
{
}


Real
MassPenalty::computeQpResidual()
{
  if (_u[_qp] < _lower_bound)
    {
      return _test[_i][_qp]*_penalty*(_lower_bound - _u[_qp]);
      //return _test[_i][_qp]*_penalty*_u[_qp];
      //return _penalty;
    }
  return 0.0;
}

Real
MassPenalty::computeQpJacobian()
{
  if (_u[_qp] < _lower_bound)
    {
      return -_test[_i][_qp]*_penalty*_phi[_j][_qp];
      //return _test[_i][_qp]*_penalty*_phi[_j][_qp];
      //return 0.0;
    }
  return 0.0;
}


