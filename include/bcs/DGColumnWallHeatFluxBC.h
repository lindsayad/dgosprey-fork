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
	DGColumnWallHeatFluxBC(const InputParameters & parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
  	VariableValue & _wall_temp;
	
	const MaterialProperty<Real> & _bed_wall_transfer_coeff;
	const MaterialProperty<Real> & _conductivity;
	
};

#endif //DGCOLUMNWALLHEATFLUXBC_H
