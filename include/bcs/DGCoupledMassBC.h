#ifndef DGCOUPLEDMASSBC_H
#define DGCOUPLEDMASSBC_H

#include "IntegratedBC.h"

//libMesh includes
#include "libmesh/vector_value.h"

//Forward Declarations
class DGCoupledMassBC;

template<>
InputParameters validParams<DGCoupledMassBC>();

class DGCoupledMassBC : public IntegratedBC
{
public:
  DGCoupledMassBC(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  RealVectorValue _vel;
private:
  Real _inlet_temperature;
  Real _inlet_pressure;
	Real _y_o;
  MaterialProperty<std::vector<Real> > & _dispersion;
  MaterialProperty<Real> & _velocity;
  int _index;
  int _dir;
  
};

#endif //DGCOUPLEDMASSBC_H