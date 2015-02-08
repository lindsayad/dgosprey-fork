#ifndef BEDHEATACCUMULATION_H
#define BEDHEATACCUMULATION_H

#include "TimeDerivative.h"

//Forward Declarations
class BedHeatAccumulation;

template<>
InputParameters validParams<BedHeatAccumulation>();

class BedHeatAccumulation : public TimeDerivative
{
public:
  
  BedHeatAccumulation(const std::string & name,
                       InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
	MaterialProperty<Real> & _heat_retardation;
};

#endif // BEDHEATACCUMULATION_H
