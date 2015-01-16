//
//  DGHeatFluxLimitedBC.C
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#include "DGHeatFluxLimitedBC.h"

template<>
InputParameters validParams<DGHeatFluxLimitedBC>()
{
	InputParameters params = validParams<DGFluxLimitedBC>();
	params.addParam<Real>("input_temperature","Inlet temperature of column (K)");
	
	return params;
}

DGHeatFluxLimitedBC::DGHeatFluxLimitedBC(const std::string & name, InputParameters parameters) :
DGFluxLimitedBC(name, parameters),
_input_temperature(getParam<Real>("input_temperature")),
_vel(getMaterialProperty<Real>("velocity")),
_gas_density(getMaterialProperty<Real>("gas_density")),
_gas_heat_capacity(getMaterialProperty<Real>("gas_heat_capacity")),
_conductivity(getMaterialProperty<Real>("conductivity"))
{
	
}

Real
DGHeatFluxLimitedBC::computeQpResidual()
{
	_velocity(0)=0.0;
	_velocity(1)=_vel[_qp]*_gas_heat_capacity[_qp]*_gas_density[_qp];
	_velocity(2)=0.0;
	
	_Diffusion(0,0) =  _conductivity[_qp];
	_Diffusion(0,1) = std::pow(std::pow(_conductivity[_qp],2.0) + std::pow(_conductivity[_qp],2.0),0.5);
	_Diffusion(0,2) = 0.0;
	
	_Diffusion(1,0) = std::pow(std::pow(_conductivity[_qp],2.0) + std::pow(_conductivity[_qp],2.0),0.5);
	_Diffusion(1,1) = _conductivity[_qp];
	_Diffusion(1,2) = 0.0;
	
	_Diffusion(2,0) = 0.0;
	_Diffusion(2,1) = 0.0;
	_Diffusion(2,2) = 0.0;
	
	_u_input = _input_temperature;
	
	return DGFluxLimitedBC::computeQpResidual();
}

Real
DGHeatFluxLimitedBC::computeQpJacobian()
{
	_velocity(0)=0.0;
	_velocity(1)=_vel[_qp]*_gas_heat_capacity[_qp]*_gas_density[_qp];
	_velocity(2)=0.0;
	
	_Diffusion(0,0) =  _conductivity[_qp];
	_Diffusion(0,1) = std::pow(std::pow(_conductivity[_qp],2.0) + std::pow(_conductivity[_qp],2.0),0.5);
	_Diffusion(0,2) = 0.0;
	
	_Diffusion(1,0) = std::pow(std::pow(_conductivity[_qp],2.0) + std::pow(_conductivity[_qp],2.0),0.5);
	_Diffusion(1,1) = _conductivity[_qp];
	_Diffusion(1,2) = 0.0;
	
	_Diffusion(2,0) = 0.0;
	_Diffusion(2,1) = 0.0;
	_Diffusion(2,2) = 0.0;
	
	_u_input = _input_temperature;
	
	return DGFluxLimitedBC::computeQpJacobian();
}


