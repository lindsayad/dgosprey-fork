#ifndef HEATCAUCHYBC_H
#define HEATCAUCHYBC_H

#include "IntegratedBC.h"

//libMesh includes
#include "libmesh/vector_value.h"


//Forward Declarations
class HeatCauchyBC;

template<>
InputParameters validParams<HeatCauchyBC>();

class HeatCauchyBC : public IntegratedBC
{
public:
  HeatCauchyBC(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
private:
  MaterialProperty<Real> & _conductivity;
  MaterialProperty<Real> & _velocity;
  MaterialProperty<Real> & _gas_density;
  MaterialProperty<Real> & _gas_heat_capacity;
  Real _boundary_value;
};

#endif //HEATCAUCHYBC_H