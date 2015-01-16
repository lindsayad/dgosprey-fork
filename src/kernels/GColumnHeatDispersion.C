//
//  GColumnHeatDispersion.C
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#include "GColumnHeatDispersion.h"

template<>
InputParameters validParams<GColumnHeatDispersion>()
{
	InputParameters params = validParams<GAnisotropicDiffusion>();
	return params;
}

GColumnHeatDispersion::GColumnHeatDispersion(const std::string & name, InputParameters parameters) :
GAnisotropicDiffusion(name, parameters),
_conductivity(getMaterialProperty<Real>("conductivity"))
{
	
}

Real
GColumnHeatDispersion::computeQpResidual()
{
	_Diffusion(0,0) =  _conductivity[_qp];
	_Diffusion(0,1) = std::pow(std::pow(_conductivity[_qp],2.0) + std::pow(_conductivity[_qp],2.0),0.5);
	_Diffusion(0,2) = 0.0;
	
	_Diffusion(1,0) = std::pow(std::pow(_conductivity[_qp],2.0) + std::pow(_conductivity[_qp],2.0),0.5);
	_Diffusion(1,1) = _conductivity[_qp];
	_Diffusion(1,2) = 0.0;
	
	_Diffusion(2,0) = 0.0;
	_Diffusion(2,1) = 0.0;
	_Diffusion(2,2) = 0.0;
	
	return GAnisotropicDiffusion::computeQpResidual();
}

Real
GColumnHeatDispersion::computeQpJacobian()
{
	_Diffusion(0,0) =  _conductivity[_qp];
	_Diffusion(0,1) = std::pow(std::pow(_conductivity[_qp],2.0) + std::pow(_conductivity[_qp],2.0),0.5);
	_Diffusion(0,2) = 0.0;
	
	_Diffusion(1,0) = std::pow(std::pow(_conductivity[_qp],2.0) + std::pow(_conductivity[_qp],2.0),0.5);
	_Diffusion(1,1) = _conductivity[_qp];
	_Diffusion(1,2) = 0.0;
	
	_Diffusion(2,0) = 0.0;
	_Diffusion(2,1) = 0.0;
	_Diffusion(2,2) = 0.0;
	
	return GAnisotropicDiffusion::computeQpJacobian();
}


