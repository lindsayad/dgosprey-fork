//
//  GColumnMassAdvection.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/15/15.
//
//

#ifndef GCOLUMNMASSADVECTION_H
#define GCOLUMNMASSADVECTION_H

#include "GAdvection.h"

// Forward Declaration
class GColumnMassAdvection;


template<>
InputParameters validParams<GColumnMassAdvection>();

class GColumnMassAdvection : public GAdvection
{
public:
	
	GColumnMassAdvection(const std::string & name, InputParameters parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
	MaterialProperty<Real> & _vel;
	
};

#endif // GCOLUMNMASSADVECTION_H
