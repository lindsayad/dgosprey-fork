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
  
  BedHeatAccumulation(const InputParameters & parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
	const MaterialProperty<Real> & _heat_retardation;
};

#endif // BEDHEATACCUMULATION_H
