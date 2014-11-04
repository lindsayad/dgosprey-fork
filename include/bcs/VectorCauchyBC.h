#ifndef VECTORCAUCHYBC_H
#define VECTORCAUCHYBC_H

#include "IntegratedBC.h"

//libMesh includes
#include "libmesh/vector_value.h"


//Forward Declarations
class VectorCauchyBC;

template<>
InputParameters validParams<VectorCauchyBC>();

/**
 Implements the mass transfer boundary condition based on diffusive and advective fluxes into the domain.
 
 grad(u) = (velocity/diffusion) * (u_in - u)
 */
class VectorCauchyBC : public IntegratedBC
{
public:
  VectorCauchyBC(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  const RealVectorValue & _velocity;
  Real _diffusion;
  Real _u_in;
  VariableValue & _u_bound;
};

#endif //VECTORCAUCHYBC_H
