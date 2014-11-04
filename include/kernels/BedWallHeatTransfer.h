#include "Kernel.h"

#ifndef BEDWALLHEATTRANSFER_H
#define BEDWALLHEATTRANSFER_H

class BedWallHeatTransfer;

template<>
InputParameters validParams<BedWallHeatTransfer>();

class BedWallHeatTransfer : public Kernel
{
public:
  BedWallHeatTransfer(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
private:
	MaterialProperty<Real> & _bed_wall_transfer_coeff;
  MaterialProperty<Real> & _inner_dia;
  MaterialProperty<Real> & _outer_dia;
  
  VariableValue & _column_temp;
  
};
#endif //BEDWALLHEATTRANSFER_H