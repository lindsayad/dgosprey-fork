//
//  DGColumnMassAdvection.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/15/15.
//
//
#include "DGAdvection.h"

#ifndef DGCOLUMNMASSADVECTION_H
#define DGCOLUMNMASSADVECTION_H

//Forward Declarations
class DGColumnMassAdvection;

template<>
InputParameters validParams<DGColumnMassAdvection>();

class DGColumnMassAdvection : public DGAdvection
{
public:
	DGColumnMassAdvection(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual(Moose::DGResidualType type);
	virtual Real computeQpJacobian(Moose::DGJacobianType type);
	
private:
	MaterialProperty<Real> & _vel;
};

#endif
