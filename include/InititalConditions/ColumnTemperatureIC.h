#ifndef COLUMNTEMPERATUREIC_H
#define	COLUMNTEMPERATUREIC_H

#include "InitialCondition.h"

class ColumnTemperatureIC;

template<> InputParameters validParams<ColumnTemperatureIC>();

class ColumnTemperatureIC : public InitialCondition
{
public:
  ColumnTemperatureIC(const InputParameters & parameters);
  virtual Real value(const Point & p);
  
private:
  Real _TC_IC;
};

#endif //COLUMNTEMPERATUREIC_H
