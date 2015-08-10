#include "Kernel.h"

#ifndef BEDWALLHEATTRANSFER_H
#define BEDWALLHEATTRANSFER_H

class BedWallHeatTransfer;

template<>
InputParameters validParams<BedWallHeatTransfer>();

class BedWallHeatTransfer : public Kernel
{
public:
  BedWallHeatTransfer(const InputParameters & parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
  const MaterialProperty<Real> & _bed_wall_transfer_coeff;
  const MaterialProperty<Real> & _inner_dia;
  const MaterialProperty<Real> & _outer_dia;
  
  VariableValue & _column_temp;
  
};
#endif //BEDWALLHEATTRANSFER_H