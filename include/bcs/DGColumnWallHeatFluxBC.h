//
//  DGColumnWallHeatFluxBC.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#ifndef DGCOLUMNWALLHEATFLUXBC_H
#define DGCOLUMNWALLHEATFLUXBC_H

#include "DGFluxBC.h"

//Forward Declarations
class DGColumnWallHeatFluxBC;

template<>
InputParameters validParams<DGColumnWallHeatFluxBC>();

class DGColumnWallHeatFluxBC : public DGFluxBC
{
public:
	DGColumnWallHeatFluxBC(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
  	VariableValue & _wall_temp;
	
	MaterialProperty<Real> & _bed_wall_transfer_coeff;
	MaterialProperty<Real> & _conductivity;
	
};

#endif //DGCOLUMNWALLHEATFLUXBC_H
