//
//  GColumnMassDispersion.C
//  DGOSPREY
//
//  Created by aladshaw3 on 1/15/15.
//
//

#include "GColumnMassDispersion.h"

template<>
InputParameters validParams<GColumnMassDispersion>()
{
	InputParameters params = validParams<GAnisotropicDiffusion>();
	params.addParam<unsigned int>("index", 0, "The index of the coupling variable. Must be given in same order of appearance as in the FlowProperties Material block. Indexing starts from 0. 0 is default value.");
	return params;
}

GColumnMassDispersion::GColumnMassDispersion(const std::string & name, InputParameters parameters) :
GAnisotropicDiffusion(name, parameters),
_index(getParam<unsigned int>("index")),
_dispersion(getMaterialProperty<std::vector<Real> >("dispersion")),
_molecular_diffusion(getMaterialProperty<std::vector<Real> >("molecular_diffusion"))
{

}

Real
GColumnMassDispersion::computeQpResidual()
{
	_Diffusion(0,0) =  _molecular_diffusion[_qp][_index];
	_Diffusion(0,1) = std::pow(std::pow(_molecular_diffusion[_qp][_index],2.0) + std::pow(_dispersion[_qp][_index],2.0),0.5);
	_Diffusion(0,2) = 0.0;
	
	_Diffusion(1,0) = std::pow(std::pow(_molecular_diffusion[_qp][_index],2.0) + std::pow(_dispersion[_qp][_index],2.0),0.5);
	_Diffusion(1,1) = _dispersion[_qp][_index];
	_Diffusion(1,2) = 0.0;
	
	_Diffusion(2,0) = 0.0;
	_Diffusion(2,1) = 0.0;
	_Diffusion(2,2) = 0.0;
	
	return GAnisotropicDiffusion::computeQpResidual();
}

Real
GColumnMassDispersion::computeQpJacobian()
{
	_Diffusion(0,0) =  _molecular_diffusion[_qp][_index];
	_Diffusion(0,1) = std::pow(std::pow(_molecular_diffusion[_qp][_index],2.0) + std::pow(_dispersion[_qp][_index],2.0),0.5);
	_Diffusion(0,2) = 0.0;
	
	_Diffusion(1,0) = std::pow(std::pow(_molecular_diffusion[_qp][_index],2.0) + std::pow(_dispersion[_qp][_index],2.0),0.5);
	_Diffusion(1,1) = _dispersion[_qp][_index];
	_Diffusion(1,2) = 0.0;
	
	_Diffusion(2,0) = 0.0;
	_Diffusion(2,1) = 0.0;
	_Diffusion(2,2) = 0.0;
	
	return GAnisotropicDiffusion::computeQpJacobian();
}

