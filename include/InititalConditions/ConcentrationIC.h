#ifndef CONCENTRATIONIC_H
#define	CONCENTRATIONIC_H

#include "InitialCondition.h"

class ConcentrationIC;

template<> InputParameters validParams<ConcentrationIC>();

class ConcentrationIC : public InitialCondition
{
public:
  ConcentrationIC(const InputParameters & parameters);
  virtual Real value(const Point & p);
  
private:
  Real _y_IC;
  VariableValue & _temperature;
  VariableValue & _total_pressure;
};

#endif //CONCENTRATIONIC_H
