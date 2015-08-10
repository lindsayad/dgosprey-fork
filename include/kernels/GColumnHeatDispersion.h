//
//  GColumnHeatDispersion.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#ifndef GCOLUMNHEATDISPERSION_H
#define GCOLUMNHEATDISPERSION_H

#include "GAnisotropicDiffusion.h"

//Forward Declarations
class GColumnHeatDispersion;

template<>
InputParameters validParams<GColumnHeatDispersion>();

class GColumnHeatDispersion : public GAnisotropicDiffusion
{
public:
	
	GColumnHeatDispersion(const InputParameters & parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
private:
	const MaterialProperty<Real> & _conductivity;
};

#endif //GCOLUMNHEATDISPERSION_H
