#ifndef WAVEFRONT_H
#define WAVEFRONT_H

#include "NodalPostprocessor.h"

class WaveFront;

template<>
InputParameters validParams<WaveFront>();

class WaveFront : public NodalPostprocessor
{
public:
  WaveFront(const std::string & name, InputParameters parameters);
  virtual ~WaveFront();
  
  virtual void initialize();
  virtual void execute();
  virtual Real getValue();
  virtual void threadJoin(const UserObject & y);
  
protected:
  MaterialProperty<Real> & _velocity;
  MaterialProperty<Real> & _gas_density;
  MaterialProperty<Real> & _gas_heat_capacity;
  Real _max_wfs;
  
};

#endif /* WAVEFRONT_H */