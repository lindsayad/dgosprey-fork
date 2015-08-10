//
//  GColumnHeatAdvection.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#ifndef GCOLUMNHEATADVECTION_H
#define GCOLUMNHEATADVECTION_H

#include "GAdvection.h"

// Forward Declaration
class GColumnHeatAdvection;


template<>
InputParameters validParams<GColumnHeatAdvection>();

class GColumnHeatAdvection : public GAdvection
{
public:
	
	GColumnHeatAdvection(const InputParameters & parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
	const MaterialProperty<Real> & _vel;
	const MaterialProperty<Real> & _gas_density;
	const MaterialProperty<Real> & _gas_heat_capacity;
	
};

#endif // GCOLUMNHEATADVECTION_H