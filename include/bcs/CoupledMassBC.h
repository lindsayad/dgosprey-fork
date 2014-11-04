#ifndef COUPLEDMASSBC_H
#define COUPLEDMASSBC_H

#include "MassCauchyBC.h"

//Forward Declarations
class CoupledMassBC;

template<>
InputParameters validParams<CoupledMassBC>();

class CoupledMassBC : public MassCauchyBC
{
public:
  CoupledMassBC(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
private:
  VariableValue & _temperature;
  VariableValue & _total_pressure;
	Real _y_o;
  
};

#endif //COUPLEDMASSBC_H