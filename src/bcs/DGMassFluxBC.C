//
//  DGMassFluxBC.C
//  DGOSPREY
//
//  Created by aladshaw3 on 1/15/15.
//
//

#include "DGMassFluxBC.h"

template<>
InputParameters validParams<DGMassFluxBC>()
{
	InputParameters params = validParams<DGFluxBC>();
	
	params.addParam<Real>("input_temperature","Inlet temperature of column (K)");
	params.addParam<Real>("input_pressure","Inlet pressure of column (kPa)");
	params.addParam<Real>("input_molefraction","Inlet mole fraction of the gas");
	params.addParam<unsigned int>("index", 0, "The index of the coupling variable. Must be given in same order of appearance as in the FlowProperties Material block. Indexing starts from 0. 0 is default value.");
	
	return params;
}

DGMassFluxBC::DGMassFluxBC(const std::string & name, InputParameters parameters) :
DGFluxBC(name, parameters),
_input_temperature(getParam<Real>("input_temperature")),
_input_pressure(getParam<Real>("input_pressure")),
_input_molefraction(getParam<Real>("input_molefraction")),
_vel(getMaterialProperty<Real>("velocity")),
_index(getParam<unsigned int>("index")),
_dispersion(getMaterialProperty<std::vector<Real> >("dispersion")),
_molecular_diffusion(getMaterialProperty<std::vector<Real> >("molecular_diffusion"))
{
	/*
	std::cout << _dispersion[_qp].size() << std::endl;
	_velocity(0)=0.0;
	_velocity(1)=_vel[_qp];
	_velocity(2)=0.0;
	
	_Diffusion(0,0) =  _molecular_diffusion[_qp][_index];
	_Diffusion(0,1) = std::pow(std::pow(_molecular_diffusion[_qp][_index],2.0) + std::pow(_dispersion[_qp][_index],2.0),0.5);
	_Diffusion(0,2) = 0.0;
	
	_Diffusion(1,0) = std::pow(std::pow(_molecular_diffusion[_qp][_index],2.0) + std::pow(_dispersion[_qp][_index],2.0),0.5);
	_Diffusion(1,1) = _dispersion[_qp][_index];
	_Diffusion(1,2) = 0.0;
	
	_Diffusion(2,0) = 0.0;
	_Diffusion(2,1) = 0.0;
	_Diffusion(2,2) = 0.0;
	
	_u_input = (_input_pressure * _input_molefraction) / (8.3144621 * _input_temperature);
	 */
}

Real
DGMassFluxBC::computeQpResidual()
{
	_velocity(0)=0.0;
	_velocity(1)=_vel[_qp];
	_velocity(2)=0.0;
	
	_Diffusion(0,0) =  _molecular_diffusion[_qp][_index];
	_Diffusion(0,1) = std::pow(std::pow(_molecular_diffusion[_qp][_index],2.0) + std::pow(_dispersion[_qp][_index],2.0),0.5);
	_Diffusion(0,2) = 0.0;
	
	_Diffusion(1,0) = std::pow(std::pow(_molecular_diffusion[_qp][_index],2.0) + std::pow(_dispersion[_qp][_index],2.0),0.5);
	_Diffusion(1,1) = _dispersion[_qp][_index];
	_Diffusion(1,2) = 0.0;
	
	_Diffusion(2,0) = 0.0;
	_Diffusion(2,1) = 0.0;
	_Diffusion(2,2) = 0.0;
	
	_u_input = (_input_pressure * _input_molefraction) / (8.3144621 * _input_temperature);
		
	return DGFluxBC::computeQpResidual();
}

Real
DGMassFluxBC::computeQpJacobian()
{
	_velocity(0)=0.0;
	_velocity(1)=_vel[_qp];
	_velocity(2)=0.0;
	
	_Diffusion(0,0) =  _molecular_diffusion[_qp][_index];
	_Diffusion(0,1) = std::pow(std::pow(_molecular_diffusion[_qp][_index],2.0) + std::pow(_dispersion[_qp][_index],2.0),0.5);
	_Diffusion(0,2) = 0.0;
	
	_Diffusion(1,0) = std::pow(std::pow(_molecular_diffusion[_qp][_index],2.0) + std::pow(_dispersion[_qp][_index],2.0),0.5);
	_Diffusion(1,1) = _dispersion[_qp][_index];
	_Diffusion(1,2) = 0.0;
	
	_Diffusion(2,0) = 0.0;
	_Diffusion(2,1) = 0.0;
	_Diffusion(2,2) = 0.0;
	
	_u_input = (_input_pressure * _input_molefraction) / (8.3144621 * _input_temperature);
	
	return DGFluxBC::computeQpJacobian();
}

