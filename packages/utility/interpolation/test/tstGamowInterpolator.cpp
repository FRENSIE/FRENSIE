//---------------------------------------------------------------------------//
//!
//! \file   tstGamowInterpolator.cpp
//! \author Alex Robinson
//! \brief  The Gamow interpolator unit tests
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
#include "Utility_GamowInterpolator.hpp"
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
FRENSIE_UNIT_TEST( GamowInterpolator, getExothermicInstance )
{
  std::shared_ptr<const Utility::Interpolator<double> > exothermic_instance =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  FRENSIE_CHECK( exothermic_instance.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that an instance of the interpolator can be retrieved
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, getExothermicInstance )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > exothermic_instance =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  FRENSIE_CHECK( exothermic_instance.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( GamowInterpolator, getInterpolationType )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  FRENSIE_CHECK_EQUAL( interpolator->getInterpolationType(),
                       Utility::GAMOW_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, getInterpolationType )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  FRENSIE_CHECK_EQUAL( interpolator->getInterpolationType(),
                       Utility::GAMOW_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( GamowInterpolator, isIndepVarInValidRange )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  FRENSIE_CHECK( !interpolator->isIndepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !interpolator->isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange(
					std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange(
					std::numeric_limits<double>::max() ) );

  interpolator.reset( new Utility::GamowInterpolator<double>( 1.0 ) );

  FRENSIE_CHECK( !interpolator->isIndepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !interpolator->isIndepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange( 1.0+ 1e-12 ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange(
					std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, isIndepVarInValidRange )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  FRENSIE_CHECK( !interpolator->isIndepVarInValidRange(
                                   -std::numeric_limits<double>::max()*MeV ) );
  FRENSIE_CHECK( !interpolator->isIndepVarInValidRange( 0.0*MeV ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange(
                                    std::numeric_limits<double>::min()*MeV ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange(
                                    std::numeric_limits<double>::max()*MeV ) );

  interpolator.reset( new Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>( 1.0*MeV ) );

  FRENSIE_CHECK( !interpolator->isIndepVarInValidRange(
                                   -std::numeric_limits<double>::max()*MeV ) );
  FRENSIE_CHECK( !interpolator->isIndepVarInValidRange( 1.0*MeV ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange( (1.0+1e-12)*MeV ) );
  FRENSIE_CHECK( interpolator->isIndepVarInValidRange(
                                    std::numeric_limits<double>::max()*MeV ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( GamowInterpolator, isDepVarInValidRange )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  FRENSIE_CHECK( !interpolator->isDepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !interpolator->isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( interpolator->isDepVarInValidRange(
					std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( interpolator->isDepVarInValidRange(
					std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, isDepVarInValidRange )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  FRENSIE_CHECK( !interpolator->isDepVarInValidRange(
				 -std::numeric_limits<double>::max()*barns ) );
  FRENSIE_CHECK( !interpolator->isDepVarInValidRange( 0.0*barn ) );
  FRENSIE_CHECK( interpolator->isDepVarInValidRange(
				  std::numeric_limits<double>::min()*barn ) );
  FRENSIE_CHECK( interpolator->isDepVarInValidRange(
				  std::numeric_limits<double>::max()*barns ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( GamowInterpolator, processIndepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  FRENSIE_CHECK_FLOATING_EQUALITY( 0.1, interpolator->processIndepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, interpolator->processIndepVar( 1.0 ), 1e-15 );

  interpolator.reset( new Utility::GamowInterpolator<double>( 1.0 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( 0.1, interpolator->processIndepVar( 1.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, interpolator->processIndepVar( 2.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, processIndepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  FRENSIE_CHECK_FLOATING_EQUALITY(
                        0.1, interpolator->processIndepVar( 0.1*MeV ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                        1.0, interpolator->processIndepVar( 1.0*MeV ), 1e-15 );

  interpolator.reset( new Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>( 1.0*MeV ) );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                        0.1, interpolator->processIndepVar( 1.1*MeV ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                        1.0, interpolator->processIndepVar( 2.0*MeV ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( GamowInterpolator, processDepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  FRENSIE_CHECK_FLOATING_EQUALITY( 0.1, interpolator->processDepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, interpolator->processDepVar( 1.0 ), 1e-15 );

  interpolator.reset( new Utility::GamowInterpolator<double>( 1.0 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( 0.1, interpolator->processDepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, interpolator->processDepVar( 1.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, processDepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  FRENSIE_CHECK_FLOATING_EQUALITY( 0.1, interpolator->processDepVar( 0.1*barn ), 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, interpolator->processDepVar( 1.0*barn ), 1e-15);

  interpolator.reset( new Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>( 1.0*MeV ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( 0.1, interpolator->processDepVar( 0.1*barn ), 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, interpolator->processDepVar( 1.0*barn ), 1e-15);
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( GamowInterpolator,recoverProcessedIndepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  FRENSIE_CHECK_FLOATING_EQUALITY(
                   0.1, interpolator->recoverProcessedIndepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                   1.0, interpolator->recoverProcessedIndepVar( 1.0 ), 1e-15 );

  interpolator.reset( new Utility::GamowInterpolator<double>( 1.0 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                   1.1, interpolator->recoverProcessedIndepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                   2.0, interpolator->recoverProcessedIndepVar( 1.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, recoverProcessedIndepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  FRENSIE_CHECK_FLOATING_EQUALITY(
               0.1*MeV, interpolator->recoverProcessedIndepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               1.0*MeV, interpolator->recoverProcessedIndepVar( 1.0 ), 1e-15 );

  interpolator.reset( new Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>( 1.0*MeV ) );

  FRENSIE_CHECK_FLOATING_EQUALITY(
               1.1*MeV, interpolator->recoverProcessedIndepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               2.0*MeV, interpolator->recoverProcessedIndepVar( 1.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( GamowInterpolator, recoverProcessedDepVar )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  FRENSIE_CHECK_FLOATING_EQUALITY(
                     0.1, interpolator->recoverProcessedDepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     1.0, interpolator->recoverProcessedDepVar( 1.0 ), 1e-15 );

  interpolator.reset( new Utility::GamowInterpolator<double>( 1.0 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                     0.1, interpolator->recoverProcessedDepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     1.0, interpolator->recoverProcessedDepVar( 1.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, recoverProcessedDepVar )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  FRENSIE_CHECK_FLOATING_EQUALITY(
                0.1*barn, interpolator->recoverProcessedDepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                1.0*barn, interpolator->recoverProcessedDepVar( 1.0 ), 1e-15 );

  interpolator.reset( new Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>( 1.0*MeV ) );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                0.1*barn, interpolator->recoverProcessedDepVar( 0.1 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                1.0*barn, interpolator->recoverProcessedDepVar( 1.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two points can be done
FRENSIE_UNIT_TEST( GamowInterpolator, interpolate )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = 10.0, y1 = 1000.0;

  double y = interpolator->interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1093.9254005049686, 1e-12 );

  x = 0.1;

  y = interpolator->interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-12 );

  x = 10.0;

  y = interpolator->interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-12 );

  interpolator.reset( new Utility::GamowInterpolator<double>( 0.05 ) );

  x = 1.0;

  y = interpolator->interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 2077.3469921631245, 1e-12 );

  x = 0.1;

  y = interpolator->interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-12 );

  x = 10.0;

  y = interpolator->interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two points can be done
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, interpolate )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  quantity<MegaElectronVolt,double> e0 = 0.1*MeV, e1 = 10.0*MeV, e = 1.0*MeV;
  quantity<Barn,double> cs0 = 10.0*barns, cs1 = 1000.0*barns;

  quantity<Barn,double> cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 1093.9254005049686*barns, 1e-12 );

  e = 0.1*MeV;

  cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 10.0*barn, 1e-12 );

  e = 10.0*MeV;

  cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 1000.0*barn, 1e-12 );

  interpolator.reset( new Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>( 0.05*MeV ) );

  e = 1.0*MeV;

  cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 2077.3469921631245*barn, 1e-12 );

  e = 0.1*MeV;

  cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 10.0*barn, 1e-12 );

  e = 10.0*MeV;

  cs = interpolator->interpolate( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 1000.0*barn, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
FRENSIE_UNIT_TEST( GamowInterpolator, interpolateProcessed )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  double processed_x0 = interpolator->processIndepVar( 0.1 );
  double processed_x1 = interpolator->processIndepVar( 10.0 );
  double processed_x = interpolator->processIndepVar( 1.0 );
  double processed_y0 = interpolator->processDepVar( 10.0 );
  double processed_y1 = interpolator->processDepVar( 1000.0 );

  double b_value = std::log( (1000.0*10.0)/(10.0*0.1) )/
    ( 1.0/sqrt(processed_x0) - 1.0/sqrt(processed_x1) );

  double y = interpolator->interpolateProcessed( processed_x0,
                                                 processed_x,
                                                 processed_y0,
                                                 b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1093.9254005049686, 1e-12 );

  processed_x = interpolator->processIndepVar( 0.1 );

  y = interpolator->interpolateProcessed( processed_x0,
                                          processed_x,
                                          processed_y0,
                                          b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-12 );

  processed_x = interpolator->processIndepVar( 10.0 );

  y = interpolator->interpolateProcessed( processed_x0,
                                          processed_x,
                                          processed_y0,
                                          b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-12 );

  interpolator.reset( new Utility::GamowInterpolator<double>( 0.05 ) );

  processed_x0 = interpolator->processIndepVar( 0.1 );
  processed_x1 = interpolator->processIndepVar( 10.0 );
  processed_x = interpolator->processIndepVar( 1.0 );

  b_value = std::log( (1000.0*10.0)/(10.0*0.1) )/
    ( 1.0/sqrt(processed_x0) - 1.0/sqrt(processed_x1) );

  y = interpolator->interpolateProcessed( processed_x0,
                                          processed_x,
                                          processed_y0,
                                          b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 2077.3469921631245, 1e-12 );

  processed_x = interpolator->processIndepVar( 0.1 );

  y = interpolator->interpolateProcessed( processed_x0,
                                          processed_x,
                                          processed_y0,
                                          b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-12 );

  processed_x = interpolator->processIndepVar( 10.0 );

  y = interpolator->interpolateProcessed( processed_x0,
                                          processed_x,
                                          processed_y0,
                                          b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, interpolateProcessed )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  double processed_e0 = interpolator->processIndepVar( 0.1*MeV );
  double processed_e1 = interpolator->processIndepVar( 10.0*MeV );
  double processed_e = interpolator->processIndepVar( 1.0*MeV );
  double processed_cs0 = interpolator->processDepVar( 10.0*barns );
  double processed_cs1 = interpolator->processDepVar( 1000.0*barns );

  double b_value = std::log( (1000.0*10.0)/(10.0*0.1) )/
    ( 1.0/sqrt(processed_e0) - 1.0/sqrt(processed_e1) );

  quantity<Barn,double> cs =
    interpolator->interpolateProcessed( processed_e0,
                                        processed_e,
                                        processed_cs0,
                                        b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 1093.9254005049686*barns, 1e-12 );

  processed_e = interpolator->processIndepVar( 0.1*MeV );

  cs = interpolator->interpolateProcessed( processed_e0,
                                           processed_e,
                                           processed_cs0,
                                           b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 10.0*barns, 1e-12 );

  processed_e = interpolator->processIndepVar( 10.0*MeV );

  cs = interpolator->interpolateProcessed( processed_e0,
                                           processed_e,
                                           processed_cs0,
                                           b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 1000.0*barns, 1e-12 );

  interpolator.reset( new Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>( 0.05*MeV ) );

  processed_e0 = interpolator->processIndepVar( 0.1*MeV );
  processed_e1 = interpolator->processIndepVar( 10.0*MeV );
  processed_e = interpolator->processIndepVar( 1.0*MeV );

  b_value = std::log( (1000.0*10.0)/(10.0*0.1) )/
    ( 1.0/sqrt(processed_e0) - 1.0/sqrt(processed_e1) );

  cs = interpolator->interpolateProcessed( processed_e0,
                                           processed_e,
                                           processed_cs0,
                                           b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 2077.3469921631245*barns, 1e-12 );

  processed_e = interpolator->processIndepVar( 0.1*MeV );

  cs = interpolator->interpolateProcessed( processed_e0,
                                           processed_e,
                                           processed_cs0,
                                           b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 10.0*barns, 1e-12 );

  processed_e = interpolator->processIndepVar( 10.0*MeV );

  cs = interpolator->interpolateProcessed( processed_e0,
                                           processed_e,
                                           processed_cs0,
                                           b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( cs, 1000.0*barns, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two points can be done
FRENSIE_UNIT_TEST( GamowInterpolator, interpolateAndProcess )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = 10.0, y1 = 1000.0;

  double processed_y =
    interpolator->interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 1093.9254005049686, 1e-12 );

  x = 0.1;

  processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 10.0, 1e-12 );

  x = 10.0;

  processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 1000.0, 1e-12 );

  interpolator.reset( new Utility::GamowInterpolator<double>( 0.05 ) );

  x = 1.0;

  processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 2077.3469921631245, 1e-12 );

  x = 0.1;

  processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 10.0, 1e-12 );

  x = 10.0;

  processed_y = interpolator->interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 1000.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two points can be done
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator, interpolateAndProcess )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  quantity<MegaElectronVolt,double> e0 = 0.1*MeV, e1 = 10.0*MeV, e = 1.0*MeV;
  quantity<Barn,double> cs0 = 10.0*barns, cs1 = 1000.0*barns;

  double processed_cs =
    interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 1093.9254005049686, 1e-12 );

  e = 0.1*MeV;

  processed_cs = interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 10.0, 1e-12 );

  e = 10.0*MeV;

  processed_cs = interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 1000.0, 1e-12 );

  interpolator.reset( new Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>( 0.05*MeV ) );

  e = 1.0*MeV;

  processed_cs = interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 2077.3469921631245, 1e-12 );

  e = 0.1*MeV;

  processed_cs = interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 10.0, 1e-12 );

  e = 10.0*MeV;

  processed_cs = interpolator->interpolateAndProcess( e0, e1, e, cs0, cs1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 1000.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
FRENSIE_UNIT_TEST( GamowInterpolator, interpolateProcessedAndProcess )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::GamowInterpolator<double>::getExothermicInstance();

  double processed_x0 = interpolator->processIndepVar( 0.1 );
  double processed_x1 = interpolator->processIndepVar( 10.0 );
  double processed_x = interpolator->processIndepVar( 1.0 );
  double processed_y0 = interpolator->processDepVar( 10.0 );
  double processed_y1 = interpolator->processDepVar( 1000.0 );

  double b_value = std::log( (1000.0*10.0)/(10.0*0.1) )/
    ( 1.0/sqrt(processed_x0) - 1.0/sqrt(processed_x1) );

  double processed_y = interpolator->interpolateProcessedAndProcess(
                                                                  processed_x0,
                                                                  processed_x,
                                                                  processed_y0,
                                                                  b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 1093.9254005049686, 1e-12 );

  processed_x = interpolator->processIndepVar( 0.1 );

  processed_y = interpolator->interpolateProcessedAndProcess( processed_x0,
                                                              processed_x,
                                                              processed_y0,
                                                              b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 10.0, 1e-12 );

  processed_x = interpolator->processIndepVar( 10.0 );

  processed_y = interpolator->interpolateProcessedAndProcess( processed_x0,
                                                              processed_x,
                                                              processed_y0,
                                                              b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 1000.0, 1e-12 );

  interpolator.reset( new Utility::GamowInterpolator<double>( 0.05 ) );

  processed_x0 = interpolator->processIndepVar( 0.1 );
  processed_x1 = interpolator->processIndepVar( 10.0 );
  processed_x = interpolator->processIndepVar( 1.0 );

  b_value = std::log( (1000.0*10.0)/(10.0*0.1) )/
    ( 1.0/sqrt(processed_x0) - 1.0/sqrt(processed_x1) );

  processed_y = interpolator->interpolateProcessedAndProcess( processed_x0,
                                                              processed_x,
                                                              processed_y0,
                                                              b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 2077.3469921631245, 1e-12 );

  processed_x = interpolator->processIndepVar( 0.1 );

  processed_y = interpolator->interpolateProcessedAndProcess( processed_x0,
                                                              processed_x,
                                                              processed_y0,
                                                              b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 10.0, 1e-12 );

  processed_x = interpolator->processIndepVar( 10.0 );

  processed_y = interpolator->interpolateProcessedAndProcess( processed_x0,
                                                              processed_x,
                                                              processed_y0,
                                                              b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_y, 1000.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that interpolation between two processed points can be done
FRENSIE_UNIT_TEST( GamowUnitAwareInterpolator,
                   interpolateProcessedAndProcess )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>::getExothermicInstance();

  double processed_e0 = interpolator->processIndepVar( 0.1*MeV );
  double processed_e1 = interpolator->processIndepVar( 10.0*MeV );
  double processed_e = interpolator->processIndepVar( 1.0*MeV );
  double processed_cs0 = interpolator->processDepVar( 10.0*barns );
  double processed_cs1 = interpolator->processDepVar( 1000.0*barns );

  double b_value = std::log( (1000.0*10.0)/(10.0*0.1) )/
    ( 1.0/sqrt(processed_e0) - 1.0/sqrt(processed_e1) );

  double processed_cs = interpolator->interpolateProcessedAndProcess(
                                                                 processed_e0,
                                                                 processed_e,
                                                                 processed_cs0,
                                                                 b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 1093.9254005049686, 1e-12 );

  processed_e = interpolator->processIndepVar( 0.1*MeV );

  processed_cs = interpolator->interpolateProcessedAndProcess( processed_e0,
                                                               processed_e,
                                                               processed_cs0,
                                                               b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 10.0, 1e-12 );

  processed_e = interpolator->processIndepVar( 10.0*MeV );

  processed_cs = interpolator->interpolateProcessedAndProcess( processed_e0,
                                                               processed_e,
                                                               processed_cs0,
                                                               b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 1000.0, 1e-12 );

  interpolator.reset( new Utility::GamowUnitAwareInterpolator<MegaElectronVolt,Barn,double>( 0.05*MeV ) );

  processed_e0 = interpolator->processIndepVar( 0.1*MeV );
  processed_e1 = interpolator->processIndepVar( 10.0*MeV );
  processed_e = interpolator->processIndepVar( 1.0*MeV );

  b_value = std::log( (1000.0*10.0)/(10.0*0.1) )/
    ( 1.0/sqrt(processed_e0) - 1.0/sqrt(processed_e1) );

  processed_cs = interpolator->interpolateProcessedAndProcess( processed_e0,
                                                               processed_e,
                                                               processed_cs0,
                                                               b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 2077.3469921631245, 1e-12 );

  processed_e = interpolator->processIndepVar( 0.1*MeV );

  processed_cs = interpolator->interpolateProcessedAndProcess( processed_e0,
                                                               processed_e,
                                                               processed_cs0,
                                                               b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 10.0, 1e-12 );

  processed_e = interpolator->processIndepVar( 10.0*MeV );

  processed_cs = interpolator->interpolateProcessedAndProcess( processed_e0,
                                                               processed_e,
                                                               processed_cs0,
                                                               b_value );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_cs, 1000.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// end tstGamowInterpolator.cpp
//---------------------------------------------------------------------------//
