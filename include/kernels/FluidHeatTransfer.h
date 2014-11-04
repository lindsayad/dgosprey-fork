#include "Kernel.h"

#ifndef FLUIDHEATTRANSFER_H
#define FLUIDHEATTRANSFER_H

class FluidHeatTransfer;

template<>
InputParameters validParams<FluidHeatTransfer>();

class FluidHeatTransfer : public Kernel
{
public:
  FluidHeatTransfer(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
	MaterialProperty<Real> & _bed_wall_transfer_coeff;
  MaterialProperty<Real> & _inner_dia;
  MaterialProperty<Real> & _porosity;
  
  VariableValue & _wall_temp;
  
};
#endif //FLUIDHEATTRANSFER_H