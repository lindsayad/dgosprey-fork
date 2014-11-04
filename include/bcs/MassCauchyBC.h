#ifndef MASSCAUCHYBC_H
#define MASSCAUCHYBC_H

#include "IntegratedBC.h"

//libMesh includes
#include "libmesh/vector_value.h"


//Forward Declarations
class MassCauchyBC;

template<>
InputParameters validParams<MassCauchyBC>();

class MassCauchyBC : public IntegratedBC
{
public:
  MassCauchyBC(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  Real _boundary_value;
private:
  MaterialProperty<std::vector<Real> > & _dispersion;
  MaterialProperty<Real> & _velocity;
  int _index;
};

#endif //MASSCAUCHYBC_H