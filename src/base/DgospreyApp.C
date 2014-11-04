#include "DgospreyApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

#include "VectorCauchyBC.h"
#include "LinearDrivingForce.h"
#include "BedProperties.h"
#include "AdsorbentProperties.h"
#include "FlowProperties.h"
#include "RetardedTimeDerivative.h"
#include "Advection.h"
#include "Dispersion.h"
#include "MassCauchyBC.h"
#include "BedWallHeatTransfer.h"
#include "WallAmbientHeatTransfer.h"
#include "WallHeatAccumulation.h"
#include "FluidHeatTransfer.h"
#include "HeatConductivity.h"
#include "HeatConvection.h"
#include "BedHeatAccumulation.h"
#include "HeatCauchyBC.h"
#include "CFLDT.h"
#include "WaveFront.h"
#include "MinElementSize.h"
#include "CFLConditionApproximation.h"
#include "TotalColumnPressure.h"
#include "TotalPressureIC.h"
#include "ColumnTemperatureIC.h"
#include "ConcentrationIC.h"
#include "CoupledMassBC.h"
#include "DGDispersion.h"
#include "DGConcentrationIC.h"
//#include "ElementVariablePostprocessor.h"
#include "ConservativeAdvection.h"
#include "DGConservativeAdvection.h"
#include "DGCoupledMassBC.h"
#include "DGMassOutFlowBC.h"
#include "MassPenalty.h"


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
  registerBoundaryCondition(VectorCauchyBC);
	registerKernel(LinearDrivingForce);
	registerMaterial(BedProperties);
  registerMaterial(AdsorbentProperties);
  registerMaterial(FlowProperties);
  registerKernel(RetardedTimeDerivative);
  registerKernel(Advection);
  registerKernel(Dispersion);
  registerBoundaryCondition(MassCauchyBC);
  registerKernel(BedWallHeatTransfer);
  registerKernel(WallAmbientHeatTransfer);
  registerKernel(WallHeatAccumulation);
  registerKernel(FluidHeatTransfer);
  registerKernel(HeatConductivity);
  registerKernel(HeatConvection);
  registerKernel(BedHeatAccumulation);
  registerBoundaryCondition(HeatCauchyBC);
  registerExecutioner(CFLDT);
  registerPostprocessor(WaveFront);
  registerPostprocessor(MinElementSize);
  registerExecutioner(CFLConditionApproximation);
  registerAux(TotalColumnPressure);
  registerInitialCondition(TotalPressureIC);
  registerInitialCondition(ColumnTemperatureIC);
  registerInitialCondition(ConcentrationIC);
  registerBoundaryCondition(CoupledMassBC);
  registerDGKernel(DGDispersion);
  registerInitialCondition(DGConcentrationIC);
  //registerPostprocessor(ElementVariablePostprocessor);
  registerKernel(ConservativeAdvection);
  registerDGKernel(DGConservativeAdvection);
  registerBoundaryCondition(DGCoupledMassBC);
  registerBoundaryCondition(DGMassOutFlowBC);
  registerKernel(MassPenalty);
}

void
DgospreyApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
