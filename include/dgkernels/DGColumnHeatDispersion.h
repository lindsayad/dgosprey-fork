//
//  DGColumnHeatDispersion.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#include "DGAnisotropicDiffusion.h"

#ifndef DGCOLUMNHEATDISPERSION_H
#define DGCOLUMNHEATDISPERSION_H

//Forward Declarations
class DGColumnHeatDispersion;

template<>
InputParameters validParams<DGColumnHeatDispersion>();

class DGColumnHeatDispersion : public DGAnisotropicDiffusion
{
public:
	DGColumnHeatDispersion(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual(Moose::DGResidualType type);
	virtual Real computeQpJacobian(Moose::DGJacobianType type);
	
private:
	MaterialProperty<Real> & _conductivity;
};

#endif
