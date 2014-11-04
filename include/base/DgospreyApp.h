#ifndef DGOSPREYAPP_H
#define DGOSPREYAPP_H

#include "MooseApp.h"

class DgospreyApp;

template<>
InputParameters validParams<DgospreyApp>();

class DgospreyApp : public MooseApp
{
public:
  DgospreyApp(const std::string & name, InputParameters parameters);
  virtual ~DgospreyApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* DGOSPREYAPP_H */
