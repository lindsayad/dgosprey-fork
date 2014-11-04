#include "Kernel.h"

#ifndef WALLAMBIENTHEATTRANSFER_H
#define WALLAMBIENTHEATTRANSFER_H

class WallAmbientHeatTransfer;

template<>
InputParameters validParams<WallAmbientHeatTransfer>();

class WallAmbientHeatTransfer : public Kernel
{
public:
  WallAmbientHeatTransfer(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
	MaterialProperty<Real> & _wall_exterior_transfer_coeff;
  MaterialProperty<Real> & _inner_dia;
  MaterialProperty<Real> & _outer_dia;
  
  VariableValue & _ambient_temp;
  
};
#endif //WALLAMBIENTHEATTRANSFER_H