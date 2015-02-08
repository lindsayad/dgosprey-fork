//
//  DGColumnWallHeatFluxLimitedBC.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#ifndef DGCOLUMNWALLHEATFLUXLIMITEDBC_H
#define DGCOLUMNWALLHEATFLUXLIMITEDBC_H

#include "DGFluxLimitedBC.h"

//Forward Declarations
class DGColumnWallHeatFluxLimitedBC;

template<>
InputParameters validParams<DGColumnWallHeatFluxLimitedBC>();

class DGColumnWallHeatFluxLimitedBC : public DGFluxLimitedBC
{
public:
	DGColumnWallHeatFluxLimitedBC(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
  	VariableValue & _wall_temp;
	
	MaterialProperty<Real> & _bed_wall_transfer_coeff;
	MaterialProperty<Real> & _conductivity;
	
};

#endif //DGCOLUMNWALLHEATFLUXLIMITEDBC_H
