//---------------------------------------------------------------------------//
//!
//! \file   tstStandardInterpolator.cpp
//! \author Alex Robinson
//! \brief  The standard interpolator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_StandardInterpolator.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_BarnUnit.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

using boost::units::quantity;
using Utility::Units::MegaElectronVolt;
using Utility::Units::MeV;
using Utility::Units::Barn;
using Utility::Units::barn;
using Utility::Units::barns;

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

typedef quantity<MegaElectronVolt> EnergyQuantity;
typedef quantity<Barn> BarnQuantity;
typedef Utility::QuantityTraits<EnergyQuantity> EnergyQT;
typedef Utility::QuantityTraits<BarnQuantity> BarnQT;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an instance of the interpolator can be retrieved
TEUCHOS_UNIT_TEST( StandardInterpolator, getInstance )
{
  std::shared_ptr<const Utility::Interpolator<double> > linlin_instance =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_ASSERT( linlin_instance.get() != NULL );

  std::shared_ptr<const Utility::Interpolator<double> > loglin_instance =
    Utility::StandardInterpolator<Utility::LogLin,double>::getInstance();

  TEST_ASSERT( loglin_instance.get() != NULL );
  TEST_ASSERT( loglin_instance != linlin_instance );

  std::shared_ptr<const Utility::Interpolator<double> > linlog_instance =
    Utility::StandardInterpolator<Utility::LinLog,double>::getInstance();

  TEST_ASSERT( linlog_instance.get() != NULL );
  TEST_ASSERT( linlog_instance != loglin_instance );
  TEST_ASSERT( linlog_instance != linlin_instance );

  std::shared_ptr<const Utility::Interpolator<double> > loglog_instance =
    Utility::StandardInterpolator<Utility::LogLog,double>::getInstance();

  TEST_ASSERT( loglog_instance.get() != NULL );
  TEST_ASSERT( loglog_instance != linlog_instance );
  TEST_ASSERT( loglog_instance != loglin_instance );
  TEST_ASSERT( loglog_instance != linlin_instance );
}

//---------------------------------------------------------------------------//
// Check that an instance of the unit-aware interpolator can be retrieved
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator, getInstance )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > linlin_instance =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( linlin_instance.get() != NULL );

  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > loglin_instance =
    Utility::StandardUnitAwareInterpolator<Utility::LogLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( loglin_instance.get() != NULL );
  TEST_ASSERT( loglin_instance != linlin_instance );

  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > linlog_instance =
    Utility::StandardUnitAwareInterpolator<Utility::LinLog,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( linlog_instance.get() != NULL );
  TEST_ASSERT( linlog_instance != loglin_instance );
  TEST_ASSERT( linlog_instance != linlin_instance );

  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > loglog_instance =
    Utility::StandardUnitAwareInterpolator<Utility::LogLog,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( loglog_instance.get() != NULL );
  TEST_ASSERT( loglog_instance != linlog_instance );
  TEST_ASSERT( loglog_instance != loglin_instance );
  TEST_ASSERT( loglog_instance != linlin_instance );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, getInterpolationType )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_EQUALITY_CONST( interpolator->getInterpolationType(),
                       Utility::LINLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin, getInterpolationType )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_EQUALITY_CONST( interpolator->getInterpolationType(),
                       Utility::LINLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, isIndepVarInValidRange )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_ASSERT( interpolator->isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( interpolator->isIndepVarInValidRange( 0.0 ) );
  TEST_ASSERT( interpolator->isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin,
                   isIndepVarInValidRange )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( interpolator->isIndepVarInValidRange(
                                   -std::numeric_limits<double>::max()*MeV ) );
  TEST_ASSERT( interpolator->isIndepVarInValidRange( 0.0*MeV ) );
  TEST_ASSERT( interpolator->isIndepVarInValidRange(
                                    std::numeric_limits<double>::max()*MeV ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of an dependent variable can be tested
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, isDepVarInValidRange )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_ASSERT( interpolator->isDepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( interpolator->isDepVarInValidRange( 0.0 ) );
  TEST_ASSERT( interpolator->isDepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin, isDepVarInValidRange )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( interpolator->isDepVarInValidRange(
                                  -std::numeric_limits<double>::max()*barn ) );
  TEST_ASSERT( interpolator->isDepVarInValidRange( 0.0*barn ) );
  TEST_ASSERT( interpolator->isDepVarInValidRange(
                                   std::numeric_limits<double>::max()*barn ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, processIndepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_EQUALITY_CONST( -1.0, interpolator->processIndepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, interpolator->processIndepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, interpolator->processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin, processIndepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_EQUALITY_CONST( -1.0, interpolator->processIndepVar( -1.0*MeV ) );
  TEST_EQUALITY_CONST( 0.0, interpolator->processIndepVar( 0.0*MeV ) );
  TEST_EQUALITY_CONST( 1.0, interpolator->processIndepVar( 1.0*MeV ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, processDepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_EQUALITY_CONST( -1.0, interpolator->processDepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, interpolator->processDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, interpolator->processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin, processDepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_EQUALITY_CONST( -1.0, interpolator->processDepVar( -1.0*barn ) );
  TEST_EQUALITY_CONST( 0.0, interpolator->processDepVar( 0.0*barn ) );
  TEST_EQUALITY_CONST( 1.0, interpolator->processDepVar( 1.0*barn ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, recoverProcessedIndepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_EQUALITY_CONST( -1.0, interpolator->recoverProcessedIndepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, interpolator->recoverProcessedIndepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, interpolator->recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin,
                   recoverProcessedIndepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_EQUALITY_CONST( -1.0*MeV, interpolator->recoverProcessedIndepVar(-1.0));
  TEST_EQUALITY_CONST( 0.0*MeV, interpolator->recoverProcessedIndepVar( 0.0 ));
  TEST_EQUALITY_CONST( 1.0*MeV, interpolator->recoverProcessedIndepVar( 1.0 ));
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, recoverProcessedDepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_EQUALITY_CONST( -1.0, interpolator->recoverProcessedDepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, interpolator->recoverProcessedDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, interpolator->recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin,
                   recoverProcessedDepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_EQUALITY_CONST(-1.0*barn, interpolator->recoverProcessedDepVar( -1.0 ));
  TEST_EQUALITY_CONST( 0.0*barn, interpolator->recoverProcessedDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0*barn, interpolator->recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that inerpolation between two points can be done
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, interpolate )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();
  
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 5.0, y1 = 10.0;

  double y = interpolator->interpolate( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 7.5 );

  x = 0.0;

  y = interpolator->interpolate( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 5.0 );

  x = 1.0;

  y = interpolator->interpolate( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two points can be done
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin, interpolate )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();
  
  quantity<MegaElectronVolt,double> e0 = 0.0*MeV, e1 = 1.0*MeV, e = 0.5*MeV;
  quantity<Barn,double> cs0 = 5.0*barns, cs1 = 10.0*barns;

  quantity<Barn,double> cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  TEST_EQUALITY_CONST( cs, 7.5*barns );

  e = 0.0*MeV;

  cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  TEST_EQUALITY_CONST( cs, 5.0*barns );

  e = 1.0*MeV;
  
  cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  TEST_EQUALITY_CONST( cs, 10.0*barns );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, interpolateProcessed )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  double processed_x0 = interpolator->processIndepVar( 0.0 );
  double processed_x1 = interpolator->processIndepVar( 1.0 );
  double processed_x = interpolator->processIndepVar( 0.5 );

  double processed_y0 = interpolator->processDepVar( 5.0 );
  double processed_y1 = interpolator->processDepVar( 10.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = interpolator->interpolateProcessed( processed_x0,
                                                 processed_x,
                                                 processed_y0,
                                                 processed_slope );

  TEST_EQUALITY_CONST( y, 7.5 );

  processed_x = interpolator->processIndepVar( 0.0 );

  y = interpolator->interpolateProcessed( processed_x0,
                                          processed_x,
                                          processed_y0,
                                          processed_slope );

  TEST_EQUALITY_CONST( y, 5.0 );

  processed_x = interpolator->processIndepVar( 1.0 );

  y = interpolator->interpolateProcessed( processed_x0,
                                          processed_x,
                                          processed_y0,
                                          processed_slope );

  TEST_EQUALITY_CONST( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin, interpolateProcessed )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  double processed_e0 = interpolator->processIndepVar( 0.0*MeV );
  double processed_e1 = interpolator->processIndepVar( 1.0*MeV );
  double processed_e = interpolator->processIndepVar( 0.5*MeV );

  double processed_cs0 = interpolator->processDepVar( 5.0*barns );
  double processed_cs1 = interpolator->processDepVar( 10.0*barns );

  double processed_slope =
    (processed_cs1 - processed_cs0)/(processed_e1 - processed_e0);

  quantity<Barn,double> cs =
    interpolator->interpolateProcessed( processed_e0,
                                        processed_e,
                                        processed_cs0,
                                        processed_slope );

  TEST_EQUALITY_CONST( cs, 7.5*barns );

  processed_e = interpolator->processIndepVar( 0.0*MeV );

  cs = interpolator->interpolateProcessed( processed_e0,
                                           processed_e,
                                           processed_cs0,
                                           processed_slope );

  TEST_EQUALITY_CONST( cs, 5.0*barns );

  processed_e = interpolator->processIndepVar( 1.0*MeV );

  cs = interpolator->interpolateProcessed( processed_e0,
                                           processed_e,
                                           processed_cs0,
                                           processed_slope );

  TEST_EQUALITY_CONST( cs, 10.0*barns );
}

//---------------------------------------------------------------------------//
// Check that lin-lin interpolation between two points can be done
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, interpolateAndProcess )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 5.0, y1 = 10.0;

  double processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1);

  TEST_EQUALITY_CONST( processed_y, 7.5 );

  x = 0.0;

  processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( processed_y, 5.0 );

  x = 1.0;

  processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( processed_y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two points can be done
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin,
                   interpolateAndProcess )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();
  
  quantity<MegaElectronVolt,double> e0 = 0.0*MeV, e1 = 1.0*MeV, e = 0.5*MeV;
  quantity<Barn,double> cs0 = 5.0*barns, cs1 = 10.0*barns;

  double processed_cs =
    interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  TEST_EQUALITY_CONST( processed_cs, 7.5 );

  e = 0.0*MeV;

  processed_cs = interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  TEST_EQUALITY_CONST( processed_cs, 5.0 );

  e = 1.0*MeV;
  
  processed_cs = interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  TEST_EQUALITY_CONST( processed_cs, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin,
                   interpolateProcessedAndProcess )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  double processed_x0 = interpolator->processIndepVar( 0.0 );
  double processed_x1 = interpolator->processIndepVar( 1.0 );
  double processed_x = interpolator->processIndepVar( 0.5 );

  double processed_y0 = interpolator->processDepVar( 5.0 );
  double processed_y1 = interpolator->processDepVar( 10.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double processed_y =
    interpolator->interpolateProcessedAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  TEST_EQUALITY_CONST( processed_y, 7.5 );

  processed_x = interpolator->processIndepVar( 0.0 );

  processed_y = interpolator->interpolateProcessedAndProcess( processed_x0,
                                                              processed_x,
                                                              processed_y0,
                                                              processed_slope);

  TEST_EQUALITY_CONST( processed_y, 5.0 );

  processed_x = interpolator->processIndepVar( 1.0 );

  processed_y = interpolator->interpolateProcessedAndProcess( processed_x0,
                                                              processed_x,
                                                              processed_y0,
                                                              processed_slope);

  TEST_EQUALITY_CONST( processed_y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin,
                   interpolateProcessedAndProcess )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  double processed_e0 = interpolator->processIndepVar( 0.0*MeV );
  double processed_e1 = interpolator->processIndepVar( 1.0*MeV );
  double processed_e = interpolator->processIndepVar( 0.5*MeV );

  double processed_cs0 = interpolator->processDepVar( 5.0*barns );
  double processed_cs1 = interpolator->processDepVar( 10.0*barns );

  double processed_slope =
    (processed_cs1 - processed_cs0)/(processed_e1 - processed_e0);

  double processed_cs =
    interpolator->interpolateProcessedAndProcess( processed_e0,
                                                  processed_e,
                                                  processed_cs0,
                                                  processed_slope );

  TEST_EQUALITY_CONST( processed_cs, 7.5 );

  processed_e = interpolator->processIndepVar( 0.0*MeV );

  processed_cs = interpolator->interpolateProcessedAndProcess(processed_e0,
                                                              processed_e,
                                                              processed_cs0,
                                                              processed_slope);

  TEST_EQUALITY_CONST( processed_cs, 5.0 );

  processed_e = interpolator->processIndepVar( 1.0*MeV );

  processed_cs = interpolator->interpolateProcessedAndProcess(processed_e0,
                                                              processed_e,
                                                              processed_cs0,
                                                              processed_slope);

  TEST_EQUALITY_CONST( processed_cs, 10.0 );
}

//---------------------------------------------------------------------------//
// end tstStandardInterpolator.cpp
//---------------------------------------------------------------------------//
