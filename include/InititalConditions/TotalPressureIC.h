#ifndef TOTALPRESSUREIC_H
#define	TOTALPRESSUREIC_H

#include "InitialCondition.h"

class TotalPressureIC;

template<> InputParameters validParams<TotalPressureIC>();

class TotalPressureIC : public InitialCondition
{
public:
  TotalPressureIC(const std::string & name, InputParameters parameters);
  virtual Real value(const Point & p);
  
private:
  Real _PT_IC;
};

#endif //TOTALPRESSUREIC_H
