#include "MinElementSize.h"

template<>
InputParameters validParams<MinElementSize>()
{
  InputParameters params = validParams<ElementIntegralPostprocessor>();
  return params;
}

MinElementSize::MinElementSize(const std::string & name, InputParameters parameters) :
ElementIntegralPostprocessor(name, parameters),
_qp(0),
_min_size(0)
{}

void
MinElementSize::initialize()
{
  _min_size = computeIntegral();
}

void
MinElementSize::execute()
{
  _min_size = std::min(_min_size,computeIntegral());
}

Real
MinElementSize::getValue()
{
  return _min_size;
}

void
MinElementSize::threadJoin(const UserObject & y) //NOTE: This function was causing hang-ups so it may have to be disabled 
{
  const MinElementSize & pps = static_cast<const MinElementSize &>(y);
  _min_size = std::min(_min_size,pps._integral_value);
}

Real
MinElementSize::computeQpIntegral()
{
  return 1.0; //We set this to 1 such that the integral returns the size of the element being operated on
}

Real
MinElementSize::computeIntegral()
{
  return ElementIntegralPostprocessor::computeIntegral();
}
