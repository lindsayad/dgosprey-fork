
#include "DGCoupledMassBC.h"

template<>
InputParameters validParams<DGCoupledMassBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("inlet_temperature","Coupled variable for temperature (K)");
  params.addRequiredParam<Real>("inlet_pressure","Coupled variable for total pressure (kPa)");
  params.addParam<Real>("input_mole_frac","The mole fraction of the gas species at the inlet of the column.");
	params.addParam<int>("index", 0, "The index of the coupling variable. Must be given in same order of appearance as in the FlowProperties Material block. Indexing starts from 0. 0 is default value.");
  params.addParam<int>("dir",0,"Denotes the flow direction used in the mesh (0 = x, 1 = y, 2 = z) for the 1D fixed bed.");
  return params;
}

DGCoupledMassBC::DGCoupledMassBC(const std::string & name, InputParameters parameters) :
IntegratedBC(name, parameters),
_inlet_temperature(getParam<Real>("inlet_temperature")),
_inlet_pressure(getParam<Real>("inlet_pressure")),
_y_o(getParam<Real>("input_mole_frac")),
_dispersion(getMaterialProperty<std::vector<Real> >("dispersion")),
_velocity(getMaterialProperty<Real>("velocity")),
_index(getParam<int>("index")),
_dir(getParam<int>("dir"))
{
	_vel(0) = 0.0;
  _vel(1) = 0.0;
  _vel(2) = 0.0;
}

Real
DGCoupledMassBC::computeQpResidual()
{
  _vel(_dir) = _velocity[_qp];
  Real _u_in = (_inlet_pressure * _y_o) / (8.3144621 * _inlet_temperature);
  //return -_test[_i][_qp]*((_vel*_normals[_qp])/_dispersion[_qp][_index])*(_u_in - _u[_qp]);
  return _test[_i][_qp]*(_vel*_normals[_qp])*_u_in; //this works!!!
}

Real
DGCoupledMassBC::computeQpJacobian()
{
  _vel(_dir) = _velocity[_qp];
  //return _test[_i][_qp]*((_vel*_normals[_qp])/_dispersion[_qp][_index])*_phi[_j][_qp];
  return 0.0;
}

