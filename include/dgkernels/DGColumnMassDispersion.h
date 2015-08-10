//
//  DGColumnMassDispersion.h
//  DGOSPREY
//
//  Created by aladshaw3 on 1/15/15.
//
//
#include "DGAnisotropicDiffusion.h"

#ifndef DGCOLUMNMASSDISPERSION_H
#define DGCOLUMNMASSDISPERSION_H

//Forward Declarations
class DGColumnMassDispersion;

template<>
InputParameters validParams<DGColumnMassDispersion>();

class DGColumnMassDispersion : public DGAnisotropicDiffusion
{
public:
	DGColumnMassDispersion(const InputParameters & parameters);
	
protected:
	virtual Real computeQpResidual(Moose::DGResidualType type);
	virtual Real computeQpJacobian(Moose::DGJacobianType type);
	
private:
	unsigned int _index;
	const MaterialProperty<std::vector<Real> > & _dispersion;
	const MaterialProperty<std::vector<Real> > & _molecular_diffusion;
};

#endif