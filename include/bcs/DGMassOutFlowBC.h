#ifndef DGMASSOUTFLOWBC_H
#define DGMASSOUTFLOWBC_H

#include "IntegratedBC.h"

//libMesh includes
#include "libmesh/vector_value.h"

//Forward Declarations
class DGMassOutFlowBC;

template<>
InputParameters validParams<DGMassOutFlowBC>();

class DGMassOutFlowBC : public IntegratedBC
{
public:
  DGMassOutFlowBC(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  RealVectorValue _vel;
private:
  MaterialProperty<Real> & _velocity;
  int _dir;
  
};

#endif //DGMASSOUTFLOWBC_H