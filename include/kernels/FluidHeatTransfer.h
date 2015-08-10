#include "Kernel.h"

#ifndef FLUIDHEATTRANSFER_H
#define FLUIDHEATTRANSFER_H

class FluidHeatTransfer;

template<>
InputParameters validParams<FluidHeatTransfer>();

class FluidHeatTransfer : public Kernel
{
public:
  FluidHeatTransfer(const InputParameters & parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  const MaterialProperty<Real> & _bed_wall_transfer_coeff;
  const MaterialProperty<Real> & _inner_dia;
  const MaterialProperty<Real> & _porosity;
  
  VariableValue & _wall_temp;
  
};
#endif //FLUIDHEATTRANSFER_H