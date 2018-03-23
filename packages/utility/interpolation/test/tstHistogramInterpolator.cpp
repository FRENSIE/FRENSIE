//---------------------------------------------------------------------------//
//!
//! \file   tstHistogramInterpolator.cpp
//! \author Alex Robinson
//! \brief  The historgram interpolator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_HistogramInterpolator.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_BarnUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
using Utility::Units::MegaElectronVolt;
using Utility::Units::MeV;
using Utility::Units::Barn;
using Utility::Units::barn;
using Utility::Units::barns;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an instance of the interpolator can be retrieved
FRENSIE_UNIT_TEST( HistogramInterpolator, getInstance )
{
  std::shared_ptr<const Utility::Interpolator<double> > instance =
    Utility::HistogramInterpolator<double>::getInstance();

  FRENSIE_CHECK( instance.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that an instance of the interpolator can be retrieved
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, getInstance )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > instance =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

  FRENSIE_CHECK( instance.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( HistogramInterpolator, getInterpolationType )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

  FRENSIE_CHECK_EQUAL( interpolator->getInterpolationType(),
                       Utility::HISTOGRAM_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, getInterpolationType )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

  FRENSIE_CHECK_EQUAL( interpolator->getInterpolationType(),
                       Utility::HISTOGRAM_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( HistogramInterpolator, isIndepVarInValidRange )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

  FRENSIE_CHECK( interpolator->isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, isIndepVarInValidRange )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

  FRENSIE_CHECK( interpolator->isIndepVarInValidRange(
                                   -std::numeric_limits<double>::max()*MeV ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange( 0.0*MeV ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange(
                                    std::numeric_limits<double>::max()*MeV ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( HistogramInterpolator, isDepVarInValidRange )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

  FRENSIE_CHECK( interpolator->isDepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( interpolator->isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( interpolator->isDepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, isDepVarInValidRange )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

  FRENSIE_CHECK( interpolator->isDepVarInValidRange(
                                  -std::numeric_limits<double>::max()*barn ) );
  FRENSIE_CHECK( interpolator->isDepVarInValidRange( 0.0*barn ) );
  FRENSIE_CHECK( interpolator->isDepVarInValidRange(
                                   std::numeric_limits<double>::max()*barn ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( HistogramInterpolator, processIndepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

  FRENSIE_CHECK_EQUAL( -1.0, interpolator->processIndepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, interpolator->processIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, interpolator->processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, processIndepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

  FRENSIE_CHECK_EQUAL( -1.0, interpolator->processIndepVar( -1.0*MeV ) );
  FRENSIE_CHECK_EQUAL( 0.0, interpolator->processIndepVar( 0.0*MeV ) );
  FRENSIE_CHECK_EQUAL( 1.0, interpolator->processIndepVar( 1.0*MeV ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( HistogramInterpolator, processDepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

  FRENSIE_CHECK_EQUAL( -1.0, interpolator->processDepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, interpolator->processDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, interpolator->processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, processDepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

  FRENSIE_CHECK_EQUAL( -1.0, interpolator->processDepVar( -1.0*barn ) );
  FRENSIE_CHECK_EQUAL( 0.0, interpolator->processDepVar( 0.0*barn ) );
  FRENSIE_CHECK_EQUAL( 1.0, interpolator->processDepVar( 1.0*barn ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( HistogramInterpolator, recoverProcessedIndepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

  FRENSIE_CHECK_EQUAL( -1.0, interpolator->recoverProcessedIndepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, interpolator->recoverProcessedIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, interpolator->recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, recoverProcessedIndepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

  FRENSIE_CHECK_EQUAL( -1.0*MeV, interpolator->recoverProcessedIndepVar(-1.0));
  FRENSIE_CHECK_EQUAL( 0.0*MeV, interpolator->recoverProcessedIndepVar( 0.0 ));
  FRENSIE_CHECK_EQUAL( 1.0*MeV, interpolator->recoverProcessedIndepVar( 1.0 ));
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( HistogramInterpolator, recoverProcessedDepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

  FRENSIE_CHECK_EQUAL( -1.0, interpolator->recoverProcessedDepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, interpolator->recoverProcessedDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, interpolator->recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, recoverProcessedDepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

  FRENSIE_CHECK_EQUAL(-1.0*barn, interpolator->recoverProcessedDepVar( -1.0 ));
  FRENSIE_CHECK_EQUAL( 0.0*barn, interpolator->recoverProcessedDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0*barn, interpolator->recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two points can be done
FRENSIE_UNIT_TEST( HistogramInterpolator, interpolate )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 5.0, y1 = 10.0;

  double y = interpolator->interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 5.0 );

  x = 0.0;

  y = interpolator->interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 5.0 );

  x = 1.0;

  y = interpolator->interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 5.0 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two points can be done
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, interpolate )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

  quantity<MegaElectronVolt,double> e0 = 0.0*MeV, e1 = 1.0*MeV, e = 0.5*MeV;
  quantity<Barn,double> cs0 = 5.0*barns, cs1 = 10.0*barns;

  quantity<Barn,double> cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_EQUAL( cs, 5.0*barns );

  e = 0.0*MeV;

  cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_EQUAL( cs, 5.0*barns );

  e = 1.0*MeV;

  cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_EQUAL( cs, 5.0*barns );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
FRENSIE_UNIT_TEST( HistogramInterpolator, interpolateProcessed )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

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

  FRENSIE_CHECK_EQUAL( y, 5.0 );

  processed_x = interpolator->processIndepVar( 0.0 );

  y = interpolator->interpolateProcessed( processed_x0,
                                          processed_x,
                                          processed_y0,
                                          processed_slope );

  FRENSIE_CHECK_EQUAL( y, 5.0 );

  processed_x = interpolator->processIndepVar( 1.0 );

  y = interpolator->interpolateProcessed( processed_x0,
                                          processed_x,
                                          processed_y0,
                                          processed_slope );

  FRENSIE_CHECK_EQUAL( y, 5.0 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, interpolateProcessed )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

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

  FRENSIE_CHECK_EQUAL( cs, 5.0*barns );

  processed_e = interpolator->processIndepVar( 0.0*MeV );

  cs = interpolator->interpolateProcessed( processed_e0,
                                           processed_e,
                                           processed_cs0,
                                           processed_slope );

  FRENSIE_CHECK_EQUAL( cs, 5.0*barns );

  processed_e = interpolator->processIndepVar( 1.0*MeV );

  cs = interpolator->interpolateProcessed( processed_e0,
                                           processed_e,
                                           processed_cs0,
                                           processed_slope );

  FRENSIE_CHECK_EQUAL( cs, 5.0*barns );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two points can be done
FRENSIE_UNIT_TEST( HistogramInterpolator, interpolateAndProcess )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 5.0, y1 = 10.0;

  double processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1);

  FRENSIE_CHECK_EQUAL( processed_y, 5.0 );

  x = 0.0;

  processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( processed_y, 5.0 );

  x = 1.0;

  processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( processed_y, 5.0 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two points can be done
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator, interpolateAndProcess )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

  quantity<MegaElectronVolt,double> e0 = 0.0*MeV, e1 = 1.0*MeV, e = 0.5*MeV;
  quantity<Barn,double> cs0 = 5.0*barns, cs1 = 10.0*barns;

  double processed_cs =
    interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_EQUAL( processed_cs, 5.0 );

  e = 0.0*MeV;

  processed_cs = interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_EQUAL( processed_cs, 5.0 );

  e = 1.0*MeV;

  processed_cs = interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_EQUAL( processed_cs, 5.0 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
FRENSIE_UNIT_TEST( HistogramInterpolator, interpolateProcessedAndProcess )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::HistogramInterpolator<double>::getInstance();

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

  FRENSIE_CHECK_EQUAL( processed_y, 5.0 );

  processed_x = interpolator->processIndepVar( 0.0 );

  processed_y = interpolator->interpolateProcessedAndProcess( processed_x0,
                                                              processed_x,
                                                              processed_y0,
                                                              processed_slope);

  FRENSIE_CHECK_EQUAL( processed_y, 5.0 );

  processed_x = interpolator->processIndepVar( 1.0 );

  processed_y = interpolator->interpolateProcessedAndProcess( processed_x0,
                                                              processed_x,
                                                              processed_y0,
                                                              processed_slope);

  FRENSIE_CHECK_EQUAL( processed_y, 5.0 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
FRENSIE_UNIT_TEST( HistogramUnitAwareInterpolator,
                   interpolateProcessedAndProcess )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::HistogramUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getInstance();

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

  FRENSIE_CHECK_EQUAL( processed_cs, 5.0 );

  processed_e = interpolator->processIndepVar( 0.0*MeV );

  processed_cs = interpolator->interpolateProcessedAndProcess(processed_e0,
                                                              processed_e,
                                                              processed_cs0,
                                                              processed_slope);

  FRENSIE_CHECK_EQUAL( processed_cs, 5.0 );

  processed_e = interpolator->processIndepVar( 1.0*MeV );

  processed_cs = interpolator->interpolateProcessedAndProcess(processed_e0,
                                                              processed_e,
                                                              processed_cs0,
                                                              processed_slope);

  FRENSIE_CHECK_EQUAL( processed_cs, 5.0 );
}

//---------------------------------------------------------------------------//
// end tstHistogramInterpolator.cpp
//---------------------------------------------------------------------------//
