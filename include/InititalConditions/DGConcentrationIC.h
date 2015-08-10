#ifndef DGCONCENTRATIONIC_H
#define	DGCONCENTRATIONIC_H

#include "InitialCondition.h"

class DGConcentrationIC;

template<> InputParameters validParams<DGConcentrationIC>();

class DGConcentrationIC : public InitialCondition
{
public:
  DGConcentrationIC(const InputParameters & parameters);
  virtual Real value(const Point & p);
  
private:
  Real _y_IC;
  Real _PT_IC;
  Real _T_IC;
};

#endif //DGCONCENTRATIONIC_H
