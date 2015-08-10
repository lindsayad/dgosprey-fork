#ifndef TOTALCOLUMNPRESSURE_H
#define TOTALCOLUMNPRESSURE_H

#include "AuxKernel.h"


//Forward Declarations
class TotalColumnPressure;

template<>
InputParameters validParams<TotalColumnPressure>();

class TotalColumnPressure : public AuxKernel
{
public:
  TotalColumnPressure(const InputParameters & parameters);
  
protected:
  virtual Real computeValue();
private:
	VariableValue & _temperature;
	std::vector<unsigned int> _index;
	std::vector<VariableValue *> _gas_conc;
  
};

#endif //TOTALCOLUMNPRESSURE_H
