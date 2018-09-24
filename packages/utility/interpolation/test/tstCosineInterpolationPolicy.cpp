//---------------------------------------------------------------------------//
//!
//! \file   tstCosineInterpolationPolicy.cpp
//! \author Luke Kersting
//! \brief  Cosine interpolation policy unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// FRENSIE Includes
#include "Utility_CosineInterpolationPolicy.hpp"
#include "Utility_DataProcessingPolicy.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests Variables.
//---------------------------------------------------------------------------//

double delta = 1e-10;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LogLogCos, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogLogCos::getInterpolationType(),
                       Utility::LOGLOGCOS_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogLogCos >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGCOSLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogLogCos, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogLogCos::isIndepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogLogCos::isIndepVarInValidRange( -1.0 - 1e-10 ) );
  FRENSIE_CHECK( Utility::LogLogCos::isIndepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LogLogCos::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogLogCos::isIndepVarInValidRange( 1.0 - 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogLogCos::isIndepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LogLogCos::isIndepVarInValidRange( 1.0 + 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogLogCos::isIndepVarInValidRange( std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogLogCos, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogLogCos::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogLogCos::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogLogCos::isDepVarInValidRange(
                  std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LogLogCos::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
FRENSIE_UNIT_TEST( LogLogCos, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 ),
                                  Utility::LogLogCos::processIndepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogLogCos::processIndepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1e-15 ),
                                  Utility::LogLogCos::processIndepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogLogCos, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogLogCos::processDepVar( 1.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogLogCos, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, Utility::LogLogCos::recoverProcessedIndepVar(
                          std::log( 2.0 ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0, Utility::LogLogCos::recoverProcessedIndepVar(
                          0.0 ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, Utility::LogLogCos::recoverProcessedIndepVar(
                          std::log( 0.0 ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogLogCos, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                                  Utility::LogLogCos::recoverProcessedDepVar( 0.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogLogCos, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLength( -0.5, 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLength( -1.0, 1.0 - 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogLogCos, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.5, L = 35.0;

  double eta = Utility::LogLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(4)/35.0, 1e-12 );

  y = -1.0;

  eta = Utility::LogLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 1.0/3.0;

  eta = Utility::LogLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(3)/35.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogLogCos, calculateIndepVar )
{
  double y_min = -1.0, L = 35.0, eta = std::log(4)/35.0;

  double y =  Utility::LogLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-12 );

  eta = 0.0;

  y = Utility::LogLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  eta = std::log(3)/35.0;

  y = Utility::LogLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0/3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogLogCos, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLengthProcessed( std::log(1.0), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLengthProcessed( std::log(0.5), std::log(1.5) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLengthProcessed( std::log(1e-15), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogLogCos, calculateUnitBaseIndepVarProcessed )
{
  double processed_y_min = Utility::LogLogCos::processIndepVar(0.999999);
  double y = Utility::LogLogCos::processIndepVar(0.5);
  double L = std::log(2e6);

  double eta =
        Utility::LogLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(5e5)/L, 1e-10 );

  y = Utility::LogLogCos::processIndepVar(-1.0);

  eta = Utility::LogLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-10 );

  y = Utility::LogLogCos::processIndepVar(0.999999);

  eta = Utility::LogLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogLogCos, calculateProcessedIndepVar )
{
  double processed_y_min = Utility::LogLogCos::processIndepVar(0.999999);
  double L = std::log(2e6), eta = std::log(5e5)/L;

  double y = Utility::LogLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LogLogCos::processIndepVar(0.5), 1e-10 );

  eta = 1.0;

  y = Utility::LogLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LogLogCos::processIndepVar(-1.0), 1e-10 );

  eta = 0.0;

  y = Utility::LogLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LogLogCos::processIndepVar(0.999999),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogLogCos, interpolate_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 10.0, y1 = 1000.0;

  double y = Utility::LogLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 5.4719294941049760e+01, 1e-15 );

  x = -0.5;

  y = Utility::LogLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  x = 0.5;

  y = Utility::LogLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogLogCos, interpolate_processed )
{
  double processed_x0 =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + 0.5 );
  double processed_x1 =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 - 0.5 );
  double processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 - 0.0 );
  double processed_y0 =
    Utility::LogLogDataProcessing::processDependentVar( 10.0 );
  double processed_y1 =
    Utility::LogLogDataProcessing::processDependentVar( 1000.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x0 - processed_x1);

  double y = Utility::LogLogCos::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 5.4719294941049760e+01, 1e-15 );

  processed_x = Utility::LogLogDataProcessing::processIndependentVar( 1.0 + 0.5 );

  y = Utility::LogLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  processed_x = Utility::LogLogDataProcessing::processIndependentVar( 1.0 - 0.5 );

  y = Utility::LogLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogLogCos, interpolateAndProcess_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 10.0, y1 = 1000.0;

  double log_y = Utility::LogLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 5.4719294941049760e+01 ), 1e-15 );

  x = -0.5;

  log_y = Utility::LogLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );

  x = 0.5;

  log_y = Utility::LogLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogLogCos, interpolateAndProcess_processed )
{
  double processed_x1 =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + 0.5 );
  double processed_x0 =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 - 0.5 );
  double processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 - 0.0 );
  double processed_y1 =
    Utility::LogLogDataProcessing::processDependentVar( 10.0 );
  double processed_y0 =
    Utility::LogLogDataProcessing::processDependentVar( 1000.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double log_y = Utility::LogLogCos::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 5.4719294941049760e+01 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + 0.5 );

  log_y = Utility::LogLogCos::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 - 0.5 );

  log_y = Utility::LogLogCos::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LogCosLin, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogCosLin::getInterpolationType(),
                       Utility::LOGCOSLIN_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogCosLin >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LINLOGCOS_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogCosLin, isIndepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LogCosLin::isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LogCosLin::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLin::isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogCosLin, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogCosLin::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogCosLin::isDepVarInValidRange( -1.0 - 1e-10 ) );
  FRENSIE_CHECK( Utility::LogCosLin::isDepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LogCosLin::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLin::isDepVarInValidRange( 1.0 - 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogCosLin::isDepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LogCosLin::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( LogCosLin, processIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LogCosLin::processIndepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LogCosLin::processIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LogCosLin::processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogCosLin, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 ),
                                  Utility::LogCosLin::processDepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogCosLin::processDepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1e-15 ),
                                  Utility::LogCosLin::processDepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLin, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LogCosLin::recoverProcessedIndepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LogCosLin::recoverProcessedIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LogCosLin::recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLin, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                          Utility::LogCosLin::recoverProcessedDepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLin, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLength( -4.0, -1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLength( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLength( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLin, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LogCosLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LogCosLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LogCosLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLin, calculateIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LogCosLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::LogCosLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LogCosLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLin, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLengthProcessed( -4.0, -1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLengthProcessed( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLengthProcessed( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLengthProcessed( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLin, calculateUnitBaseIndepVarProcessed )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LogCosLin::calculateUnitBaseIndepVarProcessed(
                                                                 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LogCosLin::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LogCosLin::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLin, calculateProcessedIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LogCosLin::calculateProcessedIndepVar(
                                                               eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::LogCosLin::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LogCosLin::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLin, interpolate_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = -0.5, y1 = 0.5;

  double y = Utility::LogCosLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459621556140e-01, 1e-15 );

  x = 0.0;

  y = Utility::LogCosLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  x = 1.0;

  y = Utility::LogCosLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLin, interpolate_processed )
{
  double processed_x0 =
    Utility::LogLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 =
    Utility::LogLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x =
    Utility::LogLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 =
    Utility::LogLinDataProcessing::processDependentVar( 1.0 + 0.5 );
  double processed_y1 =
    Utility::LogLinDataProcessing::processDependentVar( 1.0 - 0.5 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::LogCosLin::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459621556140e-01, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::LogCosLin::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 1.0 );

  y = Utility::LogCosLin::interpolate( processed_x0,
                                    processed_x,
                                    processed_y0,
                                    processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLin, interpolateAndProcess_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = -0.5, y1 = 0.5;

  double log_y = Utility::LogCosLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 1.3397459621556140e-01 ), 1e-15 );

  x = 0.0;

  log_y = Utility::LogCosLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + 0.5 ), 1e-15 );

  x = 1.0;

  log_y = Utility::LogCosLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLin, interpolateAndProcess_processed )
{
  double processed_x0 =
    Utility::LogLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 =
    Utility::LogLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x =
    Utility::LogLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 =
    Utility::LogLinDataProcessing::processDependentVar( 0.1 );
  double processed_y1 =
    Utility::LogLinDataProcessing::processDependentVar( 10.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double log_y = Utility::LogCosLin::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  FRENSIE_CHECK_SMALL( log_y, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 0.0 );

  log_y = Utility::LogCosLin::interpolateAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 0.1 ), 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 1.0 );

  log_y = Utility::LogCosLin::interpolateAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LinLogCos, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LinLogCos::getInterpolationType(),
                       Utility::LINLOGCOS_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LinLogCos >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGCOSLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LinLogCos, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LinLogCos::isIndepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LinLogCos::isIndepVarInValidRange( -1.0 - 1e-10 ) );
  FRENSIE_CHECK( Utility::LinLogCos::isIndepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LinLogCos::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinLogCos::isIndepVarInValidRange( 1.0 - 1e-15 ) );
  FRENSIE_CHECK( !Utility::LinLogCos::isIndepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LinLogCos::isIndepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LinLogCos, isDepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LinLogCos::isDepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LinLogCos::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinLogCos::isDepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
FRENSIE_UNIT_TEST( LinLogCos, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 ),
                                  Utility::LinLogCos::processIndepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LinLogCos::processIndepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1e-15 ),
                                  Utility::LinLogCos::processIndepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LinLogCos, processDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLogCos::processDepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLogCos::processDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLogCos::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LinLogCos, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, Utility::LinLogCos::recoverProcessedIndepVar(
                          std::log( 2.0 ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0, Utility::LinLogCos::recoverProcessedIndepVar(
                          0.0 ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, Utility::LinLogCos::recoverProcessedIndepVar(
                          std::log( 0.0 ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LinLogCos, recoverProcessedDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLogCos::recoverProcessedDepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLogCos::recoverProcessedDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLogCos::recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinLogCos, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLength( -0.5, 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLength( -1.0, 1.0 - 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinLogCos, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.5, L = 35.0;

  double eta = Utility::LinLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(4)/35.0, 1e-12 );

  y = -1.0;

  eta = Utility::LinLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 1.0/3.0;

  eta = Utility::LinLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(3)/35.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinLogCos, calculateIndepVar )
{
  double y_min = -1.0, L = 35.0, eta = std::log(4)/35.0;

  double y =  Utility::LinLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-12 );

  eta = 0.0;

  y = Utility::LinLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  eta = std::log(3)/35.0;

  y = Utility::LinLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0/3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinLogCos, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLengthProcessed( std::log(1.0), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLengthProcessed( std::log(0.5), std::log(1.5) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLengthProcessed( std::log(1e-15), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinLogCos, calculateUnitBaseIndepVarProcessed )
{
  double processed_y_min = Utility::LinLogCos::processIndepVar(0.999999);
  double y = Utility::LinLogCos::processIndepVar(0.5);
  double L = std::log(2e6);

  double eta =
        Utility::LinLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(5e5)/L, 1e-10 );

  y = Utility::LinLogCos::processIndepVar(-1.0);

  eta = Utility::LinLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-10 );

  y = Utility::LinLogCos::processIndepVar(0.999999);

  eta = Utility::LinLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinLogCos, calculateProcessedIndepVar )
{
  double processed_y_min = Utility::LinLogCos::processIndepVar(0.999999);
  double L = std::log(2e6), eta = std::log(5e5)/L;

  double y = Utility::LinLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LinLogCos::processIndepVar(0.5), 1e-10 );

  eta = 1.0;

  y = Utility::LinLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LinLogCos::processIndepVar(-1.0), 1e-10 );

  eta = 0.0;

  y = Utility::LinLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LinLogCos::processIndepVar(0.999999),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLogCos, interpolate_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.6907024642854258e-01, 1e-15 );

  x = -0.5;

  y = Utility::LinLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 0.5;

  y = Utility::LinLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinLogCos, interpolate_processed )
{
  double processed_x0 =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + 0.5 );
  double processed_x1 =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 - 0.5);
  double processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 - 0.0 );
  double processed_y0 =
    Utility::LinLogDataProcessing::processDependentVar( 0.0 );
  double processed_y1 =
    Utility::LinLogDataProcessing::processDependentVar( 1.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x0 - processed_x1);

  double y = Utility::LinLogCos::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.6907024642854258e-01, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + 0.5 );

  y = Utility::LinLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 - 0.5 );

  y = Utility::LinLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLogCos, interpolateAndProcess_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.6907024642854258e-01, 1e-15 );

  x = -0.5;

  y = Utility::LinLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 0.5;

  y = Utility::LinLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-LogCos interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinLogCos, interpolateAndProcess_processed )
{
  double processed_x0 =
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );
  double processed_x1 =
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );
  double processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 );
  double processed_y0 =
    Utility::LinLogDataProcessing::processDependentVar( 0.0 );
  double processed_y1 =
    Utility::LinLogDataProcessing::processDependentVar( 1.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::LinLogCos::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LinLogCos::interpolateAndProcess( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LinLogCos::interpolateAndProcess( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that interpolation type can be returned
FRENSIE_UNIT_TEST( LogCosLog, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogCosLog::getInterpolationType(),
                       Utility::LOGCOSLOG_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogCosLog >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGLOGCOS_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogCosLog, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogCosLog::isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogCosLog::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLog::isIndepVarInValidRange(
                                        std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LogCosLog::isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogCosLog, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogCosLog::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogCosLog::isDepVarInValidRange( -1.0 - 1e-10 ) );
  FRENSIE_CHECK( Utility::LogCosLog::isDepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LogCosLog::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLog::isDepVarInValidRange( 1.0 - 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogCosLog::isDepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LogCosLog::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( LogCosLog, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogCosLog::processIndepVar( 1.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogCosLog, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 ),
                                  Utility::LogCosLog::processDepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogCosLog::processDepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1e-15 ),
                                  Utility::LogCosLog::processDepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLog, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                          Utility::LogCosLog::recoverProcessedIndepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLog, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                          Utility::LogCosLog::recoverProcessedDepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLog, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogCosLog::calculateUnitBaseGridLength( 1e-3, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLog, calculateUnitBaseIndepVar )
{
  double y_min = 1e-3, y = 1e-2, L = 3.0;

  double eta = Utility::LogCosLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = 1e-3;

  eta = Utility::LogCosLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 0.020085536923187;

  eta = Utility::LogCosLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLog, calculateIndepVar )
{
  double y_min = 1e-3, L = 3.0, eta = 0.5;

  double y =  Utility::LogCosLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0044816890703382, 1e-12 );

  eta = 0.0;

  y = Utility::LogCosLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1e-3, 1e-12 );

  eta = 1.0;

  y = Utility::LogCosLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.020085536923187, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLog, calculateUnitBaseGridLengthProcessed )
{
  double grid_length = Utility::LogCosLog::calculateUnitBaseGridLengthProcessed(
                                                         std::log(1e-3), std::log(1.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLog, calculateUnitBaseIndepVarProcessed )
{
  double y_min = Utility::LogCosLog::processIndepVar(1e-3);
  double y = Utility::LogCosLog::processIndepVar(1e-2);
  double L = 3.0;

  double eta = Utility::LogCosLog::calculateUnitBaseIndepVarProcessed(
                                                                 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = Utility::LogCosLog::processIndepVar(1e-3);

  eta = Utility::LogCosLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = Utility::LogCosLog::processIndepVar(0.020085536923187);

  eta = Utility::LogCosLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLog, calculateProcessedIndepVar )
{
  double y_min = Utility::LogCosLog::processIndepVar(1e-3);
  double L = 3.0, eta = 0.5;

  double y = Utility::LogCosLog::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                 y,
                 Utility::LogCosLog::processIndepVar(0.0044816890703382),
                 1e-12 );

  eta = 0.0;

  y = Utility::LogCosLog::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LogCosLog::processIndepVar(1e-3),
                          1e-12 );

  eta = 1.0;

  y = Utility::LogCosLog::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                  y,
                  Utility::LogCosLog::processIndepVar(0.020085536923187),
                  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLog, interpolate_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = -0.5, y1 = 0.5;

  double y = Utility::LogCosLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459621556140e-01, 1e-15 );

  x = 0.1;

  y = Utility::LogCosLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  x = 10.0;

  y = Utility::LogCosLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLog, interpolate_processed )
{
  double processed_x0 =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );
  double processed_x1 =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );
  double processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 );
  double processed_y0 =
    Utility::LogLogDataProcessing::processDependentVar( 1.0 + 0.5 );
  double processed_y1 =
    Utility::LogLogDataProcessing::processDependentVar( 1.0 - 0.5 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::LogCosLog::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459621556118e-01, 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LogCosLog::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LogCosLog::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLog, interpolateAndProcess_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = -0.5, y1 = 0.5;

  double log_y = Utility::LogCosLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 1.3397459621556140e-01 ), 1e-15 );

  x = 0.1;

  log_y = Utility::LogCosLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + 0.5 ), 1e-15 );

  x = 10.0;

  log_y = Utility::LogCosLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLog, interpolateAndProcess_processed )
{
  double processed_x0 =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );
  double processed_x1 =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );
  double processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 );
  double processed_y0 =
    Utility::LogLogDataProcessing::processDependentVar( 1.0 + 0.5 );
  double processed_y1 =
    Utility::LogLogDataProcessing::processDependentVar( 1.0 - 0.5 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double log_y = Utility::LogCosLog::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 1.3397459621556118e-01 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  log_y = Utility::LogCosLog::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + 0.5 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  log_y = Utility::LogCosLog::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 0.5 ), 1e-15 );
}


//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LogNudgedLogCos, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogNudgedLogCos::getInterpolationType(),
                          Utility::LOGNUDGEDLOGCOS_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogNudgedLogCos >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                          Utility::NUDGEDLOGCOSLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogNudgedLogCos, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogNudgedLogCos::isIndepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogNudgedLogCos::isIndepVarInValidRange( -1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::LogNudgedLogCos::isIndepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LogNudgedLogCos::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogNudgedLogCos::isIndepVarInValidRange( 1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::LogNudgedLogCos::isIndepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LogNudgedLogCos::isIndepVarInValidRange( 1.0 + 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogNudgedLogCos::isIndepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogNudgedLogCos, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogNudgedLogCos::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogNudgedLogCos::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogNudgedLogCos::isDepVarInValidRange(
                  std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LogNudgedLogCos::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
FRENSIE_UNIT_TEST( LogNudgedLogCos, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 + delta ),
                                  Utility::LogNudgedLogCos::processIndepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1.0 + delta ),
                                  Utility::LogNudgedLogCos::processIndepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( delta ),
                                  Utility::LogNudgedLogCos::processIndepVar( 1.0 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogNudgedLogCos, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogNudgedLogCos::processDepVar( 1.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogNudgedLogCos, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, Utility::LogNudgedLogCos::recoverProcessedIndepVar(
                          std::log( 2.0 + delta ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0, Utility::LogNudgedLogCos::recoverProcessedIndepVar(
                          std::log( 1.0 + delta ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, Utility::LogNudgedLogCos::recoverProcessedIndepVar(
                          std::log( delta ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogNudgedLogCos, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                                  Utility::LogNudgedLogCos::recoverProcessedDepVar( 0.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogNudgedLogCos, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogNudgedLogCos::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (2.0+delta)/(1.0+delta) ), 1e-15 );

  grid_length =
    Utility::LogNudgedLogCos::calculateUnitBaseGridLength( -0.5, 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (1.5+delta)/(0.5+delta) ), 1e-15 );

  grid_length =
    Utility::LogNudgedLogCos::calculateUnitBaseGridLength( -1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (2.0+delta)/delta ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogNudgedLogCos, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.5, L = 35.0;

  double eta = Utility::LogNudgedLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log((2+delta)/(0.5+delta))/35.0, 1e-12 );

  y = -1.0;

  eta = Utility::LogNudgedLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 1.0;

  eta = Utility::LogNudgedLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log((2.0+delta)/delta)/35.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogNudgedLogCos, calculateIndepVar )
{
  double y_min = -1.0, L = 35.0, eta = std::log((2+delta)/(0.5+delta))/35.0;

  double y =  Utility::LogNudgedLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-12 );

  eta = 0.0;

  y = Utility::LogNudgedLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  eta = std::log((2.0+delta)/delta)/35.0;

  y = Utility::LogNudgedLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogNudgedLogCos, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LogNudgedLogCos::calculateUnitBaseGridLengthProcessed( std::log(1.0), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LogNudgedLogCos::calculateUnitBaseGridLengthProcessed( std::log(0.5), std::log(1.5) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LogNudgedLogCos::calculateUnitBaseGridLengthProcessed( std::log(1e-15), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogNudgedLogCos, calculateUnitBaseIndepVarProcessed )
{
  double processed_y_min = Utility::LogNudgedLogCos::processIndepVar(1.0);
  double y = Utility::LogNudgedLogCos::processIndepVar(0.5);
  double L = std::log((2.0+delta)/delta);

  double eta =
        Utility::LogNudgedLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log((0.5+delta)/delta)/L, 1e-10 );

  y = Utility::LogNudgedLogCos::processIndepVar(-1.0);

  eta = Utility::LogNudgedLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-10 );

  y = Utility::LogNudgedLogCos::processIndepVar(1.0);

  eta = Utility::LogNudgedLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogNudgedLogCos, calculateProcessedIndepVar )
{
  double processed_y_min = Utility::LogNudgedLogCos::processIndepVar(1.0);
  double L = std::log((2.0+delta)/delta), eta = std::log((0.5+delta)/delta)/L;

  double y = Utility::LogNudgedLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LogNudgedLogCos::processIndepVar(0.5), 1e-10 );

  eta = 1.0;

  y = Utility::LogNudgedLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LogNudgedLogCos::processIndepVar(-1.0), 1e-10 );

  eta = 0.0;

  y = Utility::LogNudgedLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LogNudgedLogCos::processIndepVar(1.0),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogNudgedLogCos, interpolate_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 10.0, y1 = 1000.0;

  double y = Utility::LogNudgedLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 5.47192949446913E1, 1e-15 );

  x = -0.5;

  y = Utility::LogNudgedLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  x = 0.5;

  y = Utility::LogNudgedLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogNudgedLogCos, interpolate_processed )
{
  double processed_x0 =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta + 0.5 );
  double processed_x1 =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta - 0.5 );
  double processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta - 0.0 );
  double processed_y0 =
    Utility::LogLogDataProcessing::processDependentVar( 10.0 );
  double processed_y1 =
    Utility::LogLogDataProcessing::processDependentVar( 1000.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x0 - processed_x1);

  double y = Utility::LogNudgedLogCos::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 5.47192949446913E1, 1e-15 );

  processed_x = Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta + 0.5 );

  y = Utility::LogNudgedLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  processed_x = Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta - 0.5 );

  y = Utility::LogNudgedLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogNudgedLogCos, interpolateAndProcess_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 10.0, y1 = 1000.0;

  double log_y = Utility::LogNudgedLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 5.47192949446913E1 ), 1e-15 );

  x = -0.5;

  log_y = Utility::LogNudgedLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );

  x = 0.5;

  log_y = Utility::LogNudgedLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogNudgedLogCos, interpolateAndProcess_processed )
{
  double processed_x1 =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta + 0.5 );
  double processed_x0 =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta - 0.5 );
  double processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta - 0.0 );
  double processed_y1 =
    Utility::LogLogDataProcessing::processDependentVar( 10.0 );
  double processed_y0 =
    Utility::LogLogDataProcessing::processDependentVar( 1000.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double log_y = Utility::LogNudgedLogCos::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 5.47192949446913E1 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta + 0.5 );

  log_y = Utility::LogNudgedLogCos::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta - 0.5 );

  log_y = Utility::LogNudgedLogCos::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( NudgedLogCosLin, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::NudgedLogCosLin::getInterpolationType(),
                       Utility::NUDGEDLOGCOSLIN_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::NudgedLogCosLin >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LINNUDGEDLOGCOS_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( NudgedLogCosLin, isIndepVarInValidRange )
{
  FRENSIE_CHECK( Utility::NudgedLogCosLin::isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::NudgedLogCosLin::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::NudgedLogCosLin::isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( NudgedLogCosLin, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::NudgedLogCosLin::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::NudgedLogCosLin::isDepVarInValidRange( -1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::NudgedLogCosLin::isDepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::NudgedLogCosLin::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::NudgedLogCosLin::isDepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::NudgedLogCosLin::isDepVarInValidRange( 1.0 + 1e-15 ) );
  FRENSIE_CHECK( !Utility::NudgedLogCosLin::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( NudgedLogCosLin, processIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::NudgedLogCosLin::processIndepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::NudgedLogCosLin::processIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::NudgedLogCosLin::processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( NudgedLogCosLin, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 + delta ),
                                  Utility::NudgedLogCosLin::processDepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1.0 + delta ),
                                  Utility::NudgedLogCosLin::processDepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( delta ),
                                  Utility::NudgedLogCosLin::processDepVar( 1.0 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( NudgedLogCosLin, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::NudgedLogCosLin::recoverProcessedIndepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::NudgedLogCosLin::recoverProcessedIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::NudgedLogCosLin::recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( NudgedLogCosLin, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                          Utility::NudgedLogCosLin::recoverProcessedDepVar( std::log( delta ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( NudgedLogCosLin, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::NudgedLogCosLin::calculateUnitBaseGridLength( -4.0, -1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::NudgedLogCosLin::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::NudgedLogCosLin::calculateUnitBaseGridLength( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::NudgedLogCosLin::calculateUnitBaseGridLength( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( NudgedLogCosLin, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::NudgedLogCosLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::NudgedLogCosLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::NudgedLogCosLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( NudgedLogCosLin, calculateIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::NudgedLogCosLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::NudgedLogCosLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::NudgedLogCosLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( NudgedLogCosLin, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::NudgedLogCosLin::calculateUnitBaseGridLengthProcessed( -4.0, -1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::NudgedLogCosLin::calculateUnitBaseGridLengthProcessed( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::NudgedLogCosLin::calculateUnitBaseGridLengthProcessed( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::NudgedLogCosLin::calculateUnitBaseGridLengthProcessed( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( NudgedLogCosLin, calculateUnitBaseIndepVarProcessed )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::NudgedLogCosLin::calculateUnitBaseIndepVarProcessed(
                                                                 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::NudgedLogCosLin::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::NudgedLogCosLin::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( NudgedLogCosLin, calculateProcessedIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::NudgedLogCosLin::calculateProcessedIndepVar(
                                                               eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::NudgedLogCosLin::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::NudgedLogCosLin::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( NudgedLogCosLin, interpolate_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = -0.5, y1 = 0.5;

  double y = Utility::NudgedLogCosLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459620009144e-01, 1e-15 );

  x = 0.0;

  y = Utility::NudgedLogCosLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  x = 1.0;

  y = Utility::NudgedLogCosLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( NudgedLogCosLin, interpolate_processed )
{
  double processed_x0 =
    Utility::LogLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 =
    Utility::LogLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x =
    Utility::LogLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 =
    Utility::LogLinDataProcessing::processDependentVar( 1.0 + delta + 0.5 );
  double processed_y1 =
    Utility::LogLinDataProcessing::processDependentVar( 1.0 + delta - 0.5 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::NudgedLogCosLin::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459620009144e-01, 1e-14 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::NudgedLogCosLin::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 1.0 );

  y = Utility::NudgedLogCosLin::interpolate( processed_x0,
                                    processed_x,
                                    processed_y0,
                                    processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( NudgedLogCosLin, interpolateAndProcess_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = -0.5, y1 = 0.5;

  double log_y = Utility::NudgedLogCosLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 1.3397459620009144e-01 ), 1e-15 );

  x = 0.0;

  log_y = Utility::NudgedLogCosLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta + 0.5 ), 1e-15 );

  x = 1.0;

  log_y = Utility::NudgedLogCosLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( NudgedLogCosLin, interpolateAndProcess_processed )
{
  double processed_x0 =
    Utility::LogLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 =
    Utility::LogLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x =
    Utility::LogLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 =
    Utility::LogLinDataProcessing::processDependentVar( 0.1 );
  double processed_y1 =
    Utility::LogLinDataProcessing::processDependentVar( 10.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double log_y = Utility::NudgedLogCosLin::interpolateAndProcess( processed_x0,
                                                         processed_x,
                                                         processed_y0,
                                                         processed_slope );

  FRENSIE_CHECK_SMALL( log_y, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 0.0 );

  log_y = Utility::NudgedLogCosLin::interpolateAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 0.1 ), 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 1.0 );

  log_y = Utility::NudgedLogCosLin::interpolateAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LinNudgedLogCos, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LinNudgedLogCos::getInterpolationType(),
                       Utility::LINNUDGEDLOGCOS_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LinNudgedLogCos >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::NUDGEDLOGCOSLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LinNudgedLogCos, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LinNudgedLogCos::isIndepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LinNudgedLogCos::isIndepVarInValidRange( -1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::LinNudgedLogCos::isIndepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LinNudgedLogCos::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinNudgedLogCos::isIndepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LinNudgedLogCos::isIndepVarInValidRange( 1.0 + 1e-15 ) );
  FRENSIE_CHECK( !Utility::LinNudgedLogCos::isIndepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LinNudgedLogCos, isDepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LinNudgedLogCos::isDepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LinNudgedLogCos::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinNudgedLogCos::isDepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
FRENSIE_UNIT_TEST( LinNudgedLogCos, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 + delta ),
                                  Utility::LinNudgedLogCos::processIndepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1.0 + delta ),
                                  Utility::LinNudgedLogCos::processIndepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1.0 + delta - 1.0 ),
                                  Utility::LinNudgedLogCos::processIndepVar( 1.0 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LinNudgedLogCos, processDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinNudgedLogCos::processDepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinNudgedLogCos::processDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinNudgedLogCos::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LinNudgedLogCos, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, Utility::LinNudgedLogCos::recoverProcessedIndepVar(
                          std::log( 2.0 + delta ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0, Utility::LinNudgedLogCos::recoverProcessedIndepVar(
                          std::log( 1.0 + delta ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, Utility::LinNudgedLogCos::recoverProcessedIndepVar(
                          std::log( 1.0 + delta - 1.0 ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LinNudgedLogCos, recoverProcessedDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinNudgedLogCos::recoverProcessedDepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinNudgedLogCos::recoverProcessedDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinNudgedLogCos::recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinNudgedLogCos, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LinNudgedLogCos::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (2.0 + delta)/(1.0 + delta) ), 1e-15 );

  grid_length =
    Utility::LinNudgedLogCos::calculateUnitBaseGridLength( -0.5, 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (3.0/2.0 + delta)/(0.5 + delta) ), 1e-15 );

  grid_length =
    Utility::LinNudgedLogCos::calculateUnitBaseGridLength( -1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (2.0 + delta)/delta ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinNudgedLogCos, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.5, L = 35.0;

  double eta = Utility::LinNudgedLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log((2+delta)/(0.5+delta))/35.0, 1e-12 );

  y = -1.0;

  eta = Utility::LinNudgedLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 1.0;

  eta = Utility::LinNudgedLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log( (2.0+delta)/delta)/35.0, 1e-8 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinNudgedLogCos, calculateIndepVar )
{
  double y_min = -1.0, L = 35.0, eta = std::log((2+delta)/(0.5+delta))/35.0;

  double y =  Utility::LinNudgedLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-12 );

  eta = 0.0;

  y = Utility::LinNudgedLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  eta = std::log((2.0+delta)/delta)/35.0;

  y = Utility::LinNudgedLogCos::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinNudgedLogCos, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LinNudgedLogCos::calculateUnitBaseGridLengthProcessed( std::log(1.0), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LinNudgedLogCos::calculateUnitBaseGridLengthProcessed( std::log(0.5), std::log(1.5) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LinNudgedLogCos::calculateUnitBaseGridLengthProcessed( std::log(1e-15), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinNudgedLogCos, calculateUnitBaseIndepVarProcessed )
{
  double processed_y_min = Utility::LinNudgedLogCos::processIndepVar(1.0);
  double y = Utility::LinNudgedLogCos::processIndepVar(0.5);
  double L = std::log((2.0+delta)/delta);

  double eta =
        Utility::LinNudgedLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log((0.5+delta)/delta)/L, 1e-12 );

  y = Utility::LinNudgedLogCos::processIndepVar(-1.0);

  eta = Utility::LinNudgedLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );

  y = Utility::LinNudgedLogCos::processIndepVar(1.0);

  eta = Utility::LinNudgedLogCos::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinNudgedLogCos, calculateProcessedIndepVar )
{
  double processed_y_min = Utility::LinNudgedLogCos::processIndepVar(1.0);
  double L = std::log((2.0+delta)/delta), eta = std::log((0.5+delta)/delta)/L;

  double y = Utility::LinNudgedLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LinNudgedLogCos::processIndepVar(0.5), 1e-10 );

  eta = 1.0;

  y = Utility::LinNudgedLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LinNudgedLogCos::processIndepVar(-1.0), 1e-10 );

  eta = 0.0;

  y = Utility::LinNudgedLogCos::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LinNudgedLogCos::processIndepVar(1.0),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LinNudgedLogCos, interpolate_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinNudgedLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.690702464429940E-1, 1e-14 );

  x = -0.5;

  y = Utility::LinNudgedLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 0.5;

  y = Utility::LinNudgedLogCos::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinNudgedLogCos, interpolate_processed )
{
  double processed_x0 =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + delta + 0.5 );
  double processed_x1 =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + delta - 0.5);
  double processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + delta - 0.0 );
  double processed_y0 =
    Utility::LinLogDataProcessing::processDependentVar( 0.0 );
  double processed_y1 =
    Utility::LinLogDataProcessing::processDependentVar( 1.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x0 - processed_x1);

  double y = Utility::LinNudgedLogCos::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.690702464429940E-1, 1e-14 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + delta + 0.5 );

  y = Utility::LinNudgedLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + delta - 0.5 );

  y = Utility::LinNudgedLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LinNudgedLogCos, interpolateAndProcess_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinNudgedLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.690702464429940E-1, 1e-14 );

  x = -0.5;

  y = Utility::LinNudgedLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 0.5;

  y = Utility::LinNudgedLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-LogCos interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinNudgedLogCos, interpolateAndProcess_processed )
{
  double processed_x0 =
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );
  double processed_x1 =
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );
  double processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 );
  double processed_y0 =
    Utility::LinLogDataProcessing::processDependentVar( 0.0 );
  double processed_y1 =
    Utility::LinLogDataProcessing::processDependentVar( 1.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::LinNudgedLogCos::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LinNudgedLogCos::interpolateAndProcess( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LinNudgedLogCos::interpolateAndProcess( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that interpolation type can be returned
FRENSIE_UNIT_TEST( NudgedLogCosLog, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::NudgedLogCosLog::getInterpolationType(),
                       Utility::NUDGEDLOGCOSLOG_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::NudgedLogCosLog >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGNUDGEDLOGCOS_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( NudgedLogCosLog, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::NudgedLogCosLog::isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::NudgedLogCosLog::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::NudgedLogCosLog::isIndepVarInValidRange(
                                        std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::NudgedLogCosLog::isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( NudgedLogCosLog, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::NudgedLogCosLog::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::NudgedLogCosLog::isDepVarInValidRange( -1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::NudgedLogCosLog::isDepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::NudgedLogCosLog::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::NudgedLogCosLog::isDepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::NudgedLogCosLog::isDepVarInValidRange( 1.0 + 1e-15 ) );
  FRENSIE_CHECK( !Utility::NudgedLogCosLog::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( NudgedLogCosLog, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::NudgedLogCosLog::processIndepVar( 1.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( NudgedLogCosLog, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 + delta ),
                                  Utility::NudgedLogCosLog::processDepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(1.0 + delta),
                                  Utility::NudgedLogCosLog::processDepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(delta),
                                  Utility::NudgedLogCosLog::processDepVar( 1.0 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( NudgedLogCosLog, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                          Utility::NudgedLogCosLog::recoverProcessedIndepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( NudgedLogCosLog, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                          Utility::NudgedLogCosLog::recoverProcessedDepVar( std::log(delta) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( NudgedLogCosLog, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::NudgedLogCosLog::calculateUnitBaseGridLength( 1e-3, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( NudgedLogCosLog, calculateUnitBaseIndepVar )
{
  double y_min = 1e-3, y = 1e-2, L = 3.0;

  double eta = Utility::NudgedLogCosLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = 1e-3;

  eta = Utility::NudgedLogCosLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 0.020085536923187;

  eta = Utility::NudgedLogCosLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( NudgedLogCosLog, calculateIndepVar )
{
  double y_min = 1e-3, L = 3.0, eta = 0.5;

  double y =  Utility::NudgedLogCosLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0044816890703382, 1e-12 );

  eta = 0.0;

  y = Utility::NudgedLogCosLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1e-3, 1e-12 );

  eta = 1.0;

  y = Utility::NudgedLogCosLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.020085536923187, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( NudgedLogCosLog, calculateUnitBaseGridLengthProcessed )
{
  double grid_length = Utility::NudgedLogCosLog::calculateUnitBaseGridLengthProcessed(
                                                         std::log(1e-3), std::log(1.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( NudgedLogCosLog, calculateUnitBaseIndepVarProcessed )
{
  double y_min = Utility::NudgedLogCosLog::processIndepVar(1e-3);
  double y = Utility::NudgedLogCosLog::processIndepVar(1e-2);
  double L = 3.0;

  double eta = Utility::NudgedLogCosLog::calculateUnitBaseIndepVarProcessed(
                                                                 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = Utility::NudgedLogCosLog::processIndepVar(1e-3);

  eta = Utility::NudgedLogCosLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = Utility::NudgedLogCosLog::processIndepVar(0.020085536923187);

  eta = Utility::NudgedLogCosLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( NudgedLogCosLog, calculateProcessedIndepVar )
{
  double y_min = Utility::NudgedLogCosLog::processIndepVar(1e-3);
  double L = 3.0, eta = 0.5;

  double y = Utility::NudgedLogCosLog::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                 y,
                 Utility::NudgedLogCosLog::processIndepVar(0.0044816890703382),
                 1e-12 );

  eta = 0.0;

  y = Utility::NudgedLogCosLog::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::NudgedLogCosLog::processIndepVar(1e-3),
                          1e-12 );

  eta = 1.0;

  y = Utility::NudgedLogCosLog::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                  y,
                  Utility::NudgedLogCosLog::processIndepVar(0.020085536923187),
                  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( NudgedLogCosLog, interpolate_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = -0.5, y1 = 0.5;

  double y = Utility::NudgedLogCosLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459620009144e-01, 1e-15 );

  x = 0.1;

  y = Utility::NudgedLogCosLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  x = 10.0;

  y = Utility::NudgedLogCosLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( NudgedLogCosLog, interpolate_processed )
{
  double processed_x0 =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );
  double processed_x1 =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );
  double processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 );
  double processed_y0 =
    Utility::LogLogDataProcessing::processDependentVar( 1.0 + delta + 0.5 );
  double processed_y1 =
    Utility::LogLogDataProcessing::processDependentVar( 1.0 + delta - 0.5 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::NudgedLogCosLog::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459620009144e-01, 1e-14 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::NudgedLogCosLog::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::NudgedLogCosLog::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( NudgedLogCosLog, interpolateAndProcess_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = -0.5, y1 = 0.5;

  double log_y = Utility::NudgedLogCosLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 1.3397459620009144e-01 ), 1e-15 );

  x = 0.1;

  log_y = Utility::NudgedLogCosLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta + 0.5 ), 1e-15 );

  x = 10.0;

  log_y = Utility::NudgedLogCosLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( NudgedLogCosLog, interpolateAndProcess_processed )
{
  double processed_x0 =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );
  double processed_x1 =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );
  double processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 );
  double processed_y0 =
    Utility::LogLogDataProcessing::processDependentVar( 1.0 + delta + 0.5 );
  double processed_y1 =
    Utility::LogLogDataProcessing::processDependentVar( 1.0 + delta - 0.5 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double log_y = Utility::NudgedLogCosLog::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 1.3397459620009144e-01 ), 1e-14 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  log_y = Utility::NudgedLogCosLog::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta + 0.5 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  log_y = Utility::NudgedLogCosLog::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstCosineInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
