#ifndef CFLCONDITIONAPPROXIMATION_H
#define CFLCONDITIONAPPROXIMATION_H

#include "TimeStepper.h"
#include "PostprocessorInterface.h"

class CFLConditionApproximation;

template<>
InputParameters validParams<CFLConditionApproximation>();

class CFLConditionApproximation :

public TimeStepper,
public PostprocessorInterface
{
public:
  CFLConditionApproximation(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeInitialDT();
  virtual Real computeDT();
  
  const PostprocessorValue & _min_mesh;
  const PostprocessorValue & _max_speed;
};


#endif /* CFLCONDITIONAPPROXIMATION_H */