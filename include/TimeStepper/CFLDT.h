#ifndef CFLDT_H
#define CFLDT_H

#include "TimeStepper.h"

class CFLDT;

template<>
InputParameters validParams<CFLDT>();

class CFLDT : public TimeStepper
{
public:
  CFLDT(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeInitialDT();
  virtual Real computeDT();
  
private:
  Real _length; //Note: it would be better to do this agnositically to determine min mesh size
  int _nodes;
  Real _flow_rate;
  Real _din;
  Real _eb;
};


#endif //CFLDT_H
