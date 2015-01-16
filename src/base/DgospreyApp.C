#include "DgospreyApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

#include "LinearDrivingForce.h"
#include "BedProperties.h"
#include "AdsorbentProperties.h"
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

DgospreyApp::DgospreyApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
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

void
DgospreyApp::registerApps()
{
  registerApp(DgospreyApp);
}

void
DgospreyApp::registerObjects(Factory & factory)
{
	registerKernel(LinearDrivingForce);
	registerMaterial(BedProperties);
  registerMaterial(AdsorbentProperties);
  registerMaterial(FlowProperties);
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
}

void
DgospreyApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
