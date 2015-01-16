//
//  GColumnMassAdvection.C
//  DGOSPREY
//
//  Created by aladshaw3 on 1/15/15.
//
//

#include "GColumnMassAdvection.h"

template<>
InputParameters validParams<GColumnMassAdvection>()
{
	InputParameters params = validParams<GAdvection>();
	return params;
}

GColumnMassAdvection::GColumnMassAdvection(const std::string & name,
					   InputParameters parameters) :
GAdvection(name, parameters),
_vel(getMaterialProperty<Real>("velocity"))

{

}

Real GColumnMassAdvection::computeQpResidual()
{
	_velocity(0)=0.0;
	_velocity(1)=_vel[_qp];
	_velocity(2)=0.0;
	
	return GAdvection::computeQpResidual();
}

Real GColumnMassAdvection::computeQpJacobian()
{
	_velocity(0)=0.0;
	_velocity(1)=_vel[_qp];
	_velocity(2)=0.0;
	
	return GAdvection::computeQpJacobian();
}
