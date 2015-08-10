//
//  DGColumnWallHeatFluxLimitedBC.C
//  DGOSPREY
//
//  Created by aladshaw3 on 1/16/15.
//
//

#include "DGColumnWallHeatFluxLimitedBC.h"

template<>
InputParameters validParams<DGColumnWallHeatFluxLimitedBC>()
{
	InputParameters params = validParams<DGFluxLimitedBC>();
	params.addCoupledVar("wall_temp", "Name of the wall temperature variable to couple with");
	
	return params;
}

DGColumnWallHeatFluxLimitedBC::DGColumnWallHeatFluxLimitedBC(const InputParameters & parameters) :
DGFluxLimitedBC(parameters),
_wall_temp(coupledValue("wall_temp")),
_bed_wall_transfer_coeff(getMaterialProperty<Real>("bed_wall_transfer_coeff")),
_conductivity(getMaterialProperty<Real>("conductivity"))
{
	
}

Real
DGColumnWallHeatFluxLimitedBC::computeQpResidual()
{
	_velocity(0)=_bed_wall_transfer_coeff[_qp];
	_velocity(1)=0.0;
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
	
	_u_input = _wall_temp[_qp];
	
	return DGFluxLimitedBC::computeQpResidual();
}

Real
DGColumnWallHeatFluxLimitedBC::computeQpJacobian()
{
	_velocity(0)=_bed_wall_transfer_coeff[_qp];
	_velocity(1)=0.0;
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
	
	_u_input = _wall_temp[_qp];
	
	return DGFluxLimitedBC::computeQpJacobian();
}
