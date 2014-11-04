#include "CFLConditionApproximation.h"

template<>
InputParameters validParams<CFLConditionApproximation>()
{
  InputParameters params = validParams<TimeStepper>();
  params.addRequiredParam<PostprocessorName>("mesh_size", "The name of the postprocessor calculating the minium mesh size.");
  params.addRequiredParam<PostprocessorName>("wave_front","Name of postprocessor calculating the maximum wave front velocity.");
  return params;
}

CFLConditionApproximation::CFLConditionApproximation(const std::string & name, InputParameters parameters) :
TimeStepper(name, parameters),
PostprocessorInterface(parameters),
_min_mesh(getPostprocessorValue("mesh_size")),
_max_speed(getPostprocessorValue("wave_front"))
{
}

Real
CFLConditionApproximation::computeInitialDT()
{
  return 0.1/(8.0*8.0);
}

Real
CFLConditionApproximation::computeDT()
{
  if (std::isinf(_max_speed))
    return _min_mesh / (8.0 * 10.0);
  else
  	return _min_mesh / (8.0 * _max_speed);
}