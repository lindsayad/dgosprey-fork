#ifndef MASSPENALTY_H
#define MASSPENALTY_H

#include "Kernel.h"

// Forward Declarations
class MassPenalty;

template<>
InputParameters validParams<MassPenalty>();

class MassPenalty : public Kernel
{
public:

  MassPenalty(const std::string & name,
                        InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
private:
  Real _penalty;
  Real _lower_bound;
};

#endif //MASSPENALTY_H
