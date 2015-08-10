#include "DgospreyApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

#include "LinearDrivingForce.h"
#include "BedProperties.h"
#include "AdsorbentProperties.h"
#include "AdsorbateProperties.h"
#include "FlowProperties.h"
#include "RetardedTimeDerivative.h"
#include "Dispersion.h"
#include "BedWallHeatTransfer.h"
#include "WallAmbientHeatTransfer.h"
#include "WallHeatAccumulation.h"
#include "FluidHeatTransfer.h"
#include "HeatConductivity.h"
#include "BedHeatAccumulation.h"
#include "TotalColumnPressure.h"
#include "TotalPressureIC.h"
#include "ColumnTemperatureIC.h"
#include "ConcentrationIC.h"
#include "DGConcentrationIC.h"
#include "DGAdvection.h"
#include "DGFluxBC.h"
#include "GAdvection.h"
#include "DGAnisotropicDiffusion.h"
#include "GAnisotropicDiffusion.h"
#include "DGFluxLimitedBC.h"

#include "DGColumnMassAdvection.h"
#include "DGColumnMassDispersion.h"
#include "DGMassFluxBC.h"
#include "DGMassFluxLimitedBC.h"
#include "GColumnMassAdvection.h"
#include "GColumnMassDispersion.h"

#include "DGColumnHeatAdvection.h"
#include "GColumnHeatAdvection.h"
#include "DGColumnHeatDispersion.h"
#include "GColumnHeatDispersion.h"
#include "DGHeatFluxBC.h"
#include "DGHeatFluxLimitedBC.h"
#include "DGColumnWallHeatFluxBC.h"
#include "DGColumnWallHeatFluxLimitedBC.h"


template<>
InputParameters validParams<DgospreyApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

DgospreyApp::DgospreyApp(InputParameters parameters) :
    MooseApp(parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  DgospreyApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  DgospreyApp::associateSyntax(_syntax, _action_factory);
}

DgospreyApp::~DgospreyApp()
{
}

extern "C" void DgospreyApp__registerApps() { DgospreyApp::registerApps(); }
void
DgospreyApp::registerApps()
{
#undef registerApp
#define registerApp(name) AppFactory::instance().reg<name>(#name)
	registerApp(DgospreyApp);
#undef registerApp
#define registerApp(name) AppFactory::instance().regLegacy<name>(#name)
}

void
DgospreyApp::registerObjects(Factory & factory)
{
#undef registerObject
#define registerObject(name) factory.reg<name>(stringifyName(name))
	registerKernel(LinearDrivingForce);
	registerMaterial(BedProperties);
	registerMaterial(AdsorbentProperties);
	registerMaterial(FlowProperties);
	registerMaterial(AdsorbateProperties);
	registerKernel(RetardedTimeDerivative);
	registerKernel(Dispersion);
	registerKernel(BedWallHeatTransfer);
	registerKernel(WallAmbientHeatTransfer);
	registerKernel(WallHeatAccumulation);
	registerKernel(FluidHeatTransfer);
	registerKernel(HeatConductivity);
	registerKernel(BedHeatAccumulation);

	registerAux(TotalColumnPressure);
	registerInitialCondition(TotalPressureIC);
	registerInitialCondition(ColumnTemperatureIC);
	registerInitialCondition(ConcentrationIC);
	registerInitialCondition(DGConcentrationIC);
	
	registerDGKernel(DGAdvection);
	registerBoundaryCondition(DGFluxBC);
	registerKernel(GAdvection);
	registerDGKernel(DGAnisotropicDiffusion);
	registerKernel(GAnisotropicDiffusion);
	registerBoundaryCondition(DGFluxLimitedBC);
	
	registerDGKernel(DGColumnMassAdvection);
	registerDGKernel(DGColumnMassDispersion);
	registerBoundaryCondition(DGMassFluxBC);
	registerBoundaryCondition(DGMassFluxLimitedBC);
	registerKernel(GColumnMassAdvection);
	registerKernel(GColumnMassDispersion);
	
	registerDGKernel(DGColumnHeatAdvection);
	registerKernel(GColumnHeatAdvection);
	registerDGKernel(DGColumnHeatDispersion);
	registerKernel(GColumnHeatDispersion);
	registerBoundaryCondition(DGHeatFluxBC);
	registerBoundaryCondition(DGHeatFluxLimitedBC);
	registerBoundaryCondition(DGColumnWallHeatFluxBC);
	registerBoundaryCondition(DGColumnWallHeatFluxLimitedBC);
#undef registerObject
#define registerObject(name) factory.regLegacy<name>(stringifyName(name))
}

void
DgospreyApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
#undef registerAction
#define registerAction(tplt, action) action_factory.reg<tplt>(stringifyName(tplt), action)
	
	//Register Actions Here
	
#undef registerAction
#define registerAction(tplt, action) action_factory.regLegacy<tplt>(stringifyName(tplt), action)
}
