#ifndef MINELEMENTSIZE_H
#define MINELEMENTSIZE_H

#include "ElementIntegralPostprocessor.h"

//Forward Declarations
class MinElementSize;

template<>
InputParameters validParams<MinElementSize>();

class MinElementSize : public ElementIntegralPostprocessor
{
public:
  MinElementSize(const std::string & name, InputParameters parameters);
  
  virtual void initialize();
  virtual void execute();
  virtual void threadJoin(const UserObject & y);
  virtual Real getValue();
  
protected:
  virtual Real computeQpIntegral();
  virtual Real computeIntegral();
  
  unsigned int _qp;
  
  Real _min_size;
};

#endif //MINELEMENTSIZE_H