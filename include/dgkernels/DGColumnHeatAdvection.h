//
//  DGColumnHeatAdvection.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#include "DGAdvection.h"

#ifndef DGCOLUMNHEATADVECTION_H
#define DGCOLUMNHEATADVECTION_H

//Forward Declarations
class DGColumnHeatAdvection;

template<>
InputParameters validParams<DGColumnHeatAdvection>();

class DGColumnHeatAdvection : public DGAdvection
{
public:
	DGColumnHeatAdvection(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual(Moose::DGResidualType type);
	virtual Real computeQpJacobian(Moose::DGJacobianType type);
	
private:
	MaterialProperty<Real> & _vel;
	MaterialProperty<Real> & _gas_density;
	MaterialProperty<Real> & _gas_heat_capacity;
};

#endif