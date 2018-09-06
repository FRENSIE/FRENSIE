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
FRENSIE_UNIT_TEST( LogLogCos_false, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogLogCos<false>::getInterpolationType(),
                       Utility::LOGLOGCOS_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogLogCos<false> >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGCOSLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogLogCos_false, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogLogCos<false>::isIndepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogLogCos<false>::isIndepVarInValidRange( -1.0 - 1e-10 ) );
  FRENSIE_CHECK( Utility::LogLogCos<false>::isIndepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LogLogCos<false>::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogLogCos<false>::isIndepVarInValidRange( 1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::LogLogCos<false>::isIndepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LogLogCos<false>::isIndepVarInValidRange( 1.0 + 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogLogCos<false>::isIndepVarInValidRange( std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogLogCos_false, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogLogCos<false>::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogLogCos<false>::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogLogCos<false>::isDepVarInValidRange(
                  std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LogLogCos<false>::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
FRENSIE_UNIT_TEST( LogLogCos_false, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 ),
                                  Utility::LogLogCos<false>::processIndepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogLogCos<false>::processIndepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1e-15 ),
                                  Utility::LogLogCos<false>::processIndepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogLogCos_false, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogLogCos<false>::processDepVar( 1.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogLogCos_false, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, Utility::LogLogCos<false>::recoverProcessedIndepVar(
                          std::log( 2.0 ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0, Utility::LogLogCos<false>::recoverProcessedIndepVar(
                          0.0 ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, Utility::LogLogCos<false>::recoverProcessedIndepVar(
                          std::log( 0.0 ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogLogCos_false, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                                  Utility::LogLogCos<false>::recoverProcessedDepVar( 0.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogLogCos_false, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogLogCos<false>::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos<false>::calculateUnitBaseGridLength( -0.5, 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos<false>::calculateUnitBaseGridLength( -1.0, 1.0 - 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogLogCos_false, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.5, L = 35.0;

  double eta = Utility::LogLogCos<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(4)/35.0, 1e-12 );

  y = -1.0;

  eta = Utility::LogLogCos<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 1.0/3.0;

  eta = Utility::LogLogCos<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(3)/35.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogLogCos_false, calculateIndepVar )
{
  double y_min = -1.0, L = 35.0, eta = std::log(4)/35.0;

  double y =  Utility::LogLogCos<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-12 );

  eta = 0.0;

  y = Utility::LogLogCos<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  eta = std::log(3)/35.0;

  y = Utility::LogLogCos<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0/3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogLogCos_false, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LogLogCos<false>::calculateUnitBaseGridLengthProcessed( std::log(1.0), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos<false>::calculateUnitBaseGridLengthProcessed( std::log(0.5), std::log(1.5) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos<false>::calculateUnitBaseGridLengthProcessed( std::log(1e-15), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogLogCos_false, calculateUnitBaseIndepVarProcessed )
{
  double processed_y_min = Utility::LogLogCos<false>::processIndepVar(0.999999);
  double y = Utility::LogLogCos<false>::processIndepVar(0.5);
  double L = std::log(2e6);

  double eta =
        Utility::LogLogCos<false>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(5e5)/L, 1e-10 );

  y = Utility::LogLogCos<false>::processIndepVar(-1.0);

  eta = Utility::LogLogCos<false>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-10 );

  y = Utility::LogLogCos<false>::processIndepVar(0.999999);

  eta = Utility::LogLogCos<false>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogLogCos_false, calculateProcessedIndepVar )
{
  double processed_y_min = Utility::LogLogCos<false>::processIndepVar(0.999999);
  double L = std::log(2e6), eta = std::log(5e5)/L;

  double y = Utility::LogLogCos<false>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LogLogCos<false>::processIndepVar(0.5), 1e-10 );

  eta = 1.0;

  y = Utility::LogLogCos<false>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LogLogCos<false>::processIndepVar(-1.0), 1e-10 );

  eta = 0.0;

  y = Utility::LogLogCos<false>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LogLogCos<false>::processIndepVar(0.999999),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogLogCos_false, interpolate_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 10.0, y1 = 1000.0;

  double y = Utility::LogLogCos<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 5.4719294941049760e+01, 1e-15 );

  x = -0.5;

  y = Utility::LogLogCos<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  x = 0.5;

  y = Utility::LogLogCos<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogLogCos_false, interpolate_processed )
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

  double y = Utility::LogLogCos<false>::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 5.4719294941049760e+01, 1e-15 );

  processed_x = Utility::LogLogDataProcessing::processIndependentVar( 1.0 + 0.5 );

  y = Utility::LogLogCos<false>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  processed_x = Utility::LogLogDataProcessing::processIndependentVar( 1.0 - 0.5 );

  y = Utility::LogLogCos<false>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogLogCos_false, interpolateAndProcess_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 10.0, y1 = 1000.0;

  double log_y = Utility::LogLogCos<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 5.4719294941049760e+01 ), 1e-15 );

  x = -0.5;

  log_y = Utility::LogLogCos<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );

  x = 0.5;

  log_y = Utility::LogLogCos<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogLogCos_false, interpolateAndProcess_processed )
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

  double log_y = Utility::LogLogCos<false>::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 5.4719294941049760e+01 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + 0.5 );

  log_y = Utility::LogLogCos<false>::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 - 0.5 );

  log_y = Utility::LogLogCos<false>::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LogCosLin_false, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogCosLin<false>::getInterpolationType(),
                       Utility::LOGCOSLIN_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogCosLin<false> >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LINLOGCOS_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogCosLin_false, isIndepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LogCosLin<false>::isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LogCosLin<false>::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLin<false>::isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogCosLin_false, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogCosLin<false>::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogCosLin<false>::isDepVarInValidRange( -1.0 - 1e-10 ) );
  FRENSIE_CHECK( Utility::LogCosLin<false>::isDepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LogCosLin<false>::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLin<false>::isDepVarInValidRange( 1.0 - 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogCosLin<false>::isDepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LogCosLin<false>::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( LogCosLin_false, processIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LogCosLin<false>::processIndepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LogCosLin<false>::processIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LogCosLin<false>::processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogCosLin_false, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 ),
                                  Utility::LogCosLin<false>::processDepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogCosLin<false>::processDepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1e-15 ),
                                  Utility::LogCosLin<false>::processDepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLin_false, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LogCosLin<false>::recoverProcessedIndepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LogCosLin<false>::recoverProcessedIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LogCosLin<false>::recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLin_false, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                          Utility::LogCosLin<false>::recoverProcessedDepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLin_false, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogCosLin<false>::calculateUnitBaseGridLength( -4.0, -1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::LogCosLin<false>::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin<false>::calculateUnitBaseGridLength( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin<false>::calculateUnitBaseGridLength( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLin_false, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LogCosLin<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LogCosLin<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LogCosLin<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLin_false, calculateIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LogCosLin<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::LogCosLin<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LogCosLin<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLin_false, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LogCosLin<false>::calculateUnitBaseGridLengthProcessed( -4.0, -1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::LogCosLin<false>::calculateUnitBaseGridLengthProcessed( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin<false>::calculateUnitBaseGridLengthProcessed( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin<false>::calculateUnitBaseGridLengthProcessed( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLin_false, calculateUnitBaseIndepVarProcessed )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LogCosLin<false>::calculateUnitBaseIndepVarProcessed(
                                                                 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LogCosLin<false>::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LogCosLin<false>::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLin_false, calculateProcessedIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LogCosLin<false>::calculateProcessedIndepVar(
                                                               eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::LogCosLin<false>::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LogCosLin<false>::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLin_false, interpolate_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = -0.5, y1 = 0.5;

  double y = Utility::LogCosLin<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459621556140e-01, 1e-15 );

  x = 0.0;

  y = Utility::LogCosLin<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  x = 1.0;

  y = Utility::LogCosLin<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLin_false, interpolate_processed )
{
  double processed_x0 =
    Utility:: LogLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 =
    Utility:: LogLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x =
    Utility:: LogLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 =
    Utility:: LogLinDataProcessing::processDependentVar( 1.0 + 0.5 );
  double processed_y1 =
    Utility:: LogLinDataProcessing::processDependentVar( 1.0 - 0.5 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::LogCosLin<false>::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459621556140e-01, 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::LogCosLin<false>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 1.0 );

  y = Utility::LogCosLin<false>::interpolate( processed_x0,
                                    processed_x,
                                    processed_y0,
                                    processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLin_false, interpolateAndProcess_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = -0.5, y1 = 0.5;

  double log_y = Utility::LogCosLin<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 1.3397459621556140e-01 ), 1e-15 );

  x = 0.0;

  log_y = Utility::LogCosLin<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + 0.5 ), 1e-15 );

  x = 1.0;

  log_y = Utility::LogCosLin<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLin_false, interpolateAndProcess_processed )
{
  double processed_x0 =
    Utility:: LogLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 =
    Utility:: LogLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x =
    Utility:: LogLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 =
    Utility:: LogLinDataProcessing::processDependentVar( 0.1 );
  double processed_y1 =
    Utility:: LogLinDataProcessing::processDependentVar( 10.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double log_y = Utility::LogCosLin<false>::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  FRENSIE_CHECK_SMALL( log_y, 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 0.0 );

  log_y = Utility::LogCosLin<false>::interpolateAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 0.1 ), 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 1.0 );

  log_y = Utility::LogCosLin<false>::interpolateAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LinLogCos_false, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LinLogCos<false>::getInterpolationType(),
                       Utility::LINLOGCOS_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LinLogCos<false> >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGCOSLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LinLogCos_false, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LinLogCos<false>::isIndepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LinLogCos<false>::isIndepVarInValidRange( -1.0 - 1e-10 ) );
  FRENSIE_CHECK( Utility::LinLogCos<false>::isIndepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LinLogCos<false>::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinLogCos<false>::isIndepVarInValidRange( 1.0 - 1e-15 ) );
  FRENSIE_CHECK( !Utility::LinLogCos<false>::isIndepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LinLogCos<false>::isIndepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LinLogCos_false, isDepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LinLogCos<false>::isDepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LinLogCos<false>::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinLogCos<false>::isDepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
FRENSIE_UNIT_TEST( LinLogCos_false, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 ),
                                  Utility::LinLogCos<false>::processIndepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LinLogCos<false>::processIndepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1e-15 ),
                                  Utility::LinLogCos<false>::processIndepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LinLogCos_false, processDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLogCos<false>::processDepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLogCos<false>::processDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLogCos<false>::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LinLogCos_false, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, Utility::LinLogCos<false>::recoverProcessedIndepVar(
                          std::log( 2.0 ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0, Utility::LinLogCos<false>::recoverProcessedIndepVar(
                          0.0 ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, Utility::LinLogCos<false>::recoverProcessedIndepVar(
                          std::log( 0.0 ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LinLogCos_false, recoverProcessedDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLogCos<false>::recoverProcessedDepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLogCos<false>::recoverProcessedDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLogCos<false>::recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinLogCos_false, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LinLogCos<false>::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos<false>::calculateUnitBaseGridLength( -0.5, 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos<false>::calculateUnitBaseGridLength( -1.0, 1.0 - 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinLogCos_false, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.5, L = 35.0;

  double eta = Utility::LinLogCos<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(4)/35.0, 1e-12 );

  y = -1.0;

  eta = Utility::LinLogCos<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 1.0/3.0;

  eta = Utility::LinLogCos<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(3)/35.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinLogCos_false, calculateIndepVar )
{
  double y_min = -1.0, L = 35.0, eta = std::log(4)/35.0;

  double y =  Utility::LinLogCos<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-12 );

  eta = 0.0;

  y = Utility::LinLogCos<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  eta = std::log(3)/35.0;

  y = Utility::LinLogCos<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0/3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinLogCos_false, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LinLogCos<false>::calculateUnitBaseGridLengthProcessed( std::log(1.0), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos<false>::calculateUnitBaseGridLengthProcessed( std::log(0.5), std::log(1.5) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos<false>::calculateUnitBaseGridLengthProcessed( std::log(1e-15), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinLogCos_false, calculateUnitBaseIndepVarProcessed )
{
  double processed_y_min = Utility::LinLogCos<false>::processIndepVar(0.999999);
  double y = Utility::LinLogCos<false>::processIndepVar(0.5);
  double L = std::log(2e6);

  double eta =
        Utility::LinLogCos<false>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log(5e5)/L, 1e-10 );

  y = Utility::LinLogCos<false>::processIndepVar(-1.0);

  eta = Utility::LinLogCos<false>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-10 );

  y = Utility::LinLogCos<false>::processIndepVar(0.999999);

  eta = Utility::LinLogCos<false>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinLogCos_false, calculateProcessedIndepVar )
{
  double processed_y_min = Utility::LinLogCos<false>::processIndepVar(0.999999);
  double L = std::log(2e6), eta = std::log(5e5)/L;

  double y = Utility::LinLogCos<false>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LinLogCos<false>::processIndepVar(0.5), 1e-10 );

  eta = 1.0;

  y = Utility::LinLogCos<false>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LinLogCos<false>::processIndepVar(-1.0), 1e-10 );

  eta = 0.0;

  y = Utility::LinLogCos<false>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LinLogCos<false>::processIndepVar(0.999999),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLogCos_false, interpolate_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLogCos<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.6907024642854258e-01, 1e-15 );

  x = -0.5;

  y = Utility::LinLogCos<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 0.5;

  y = Utility::LinLogCos<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinLogCos_false, interpolate_processed )
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

  double y = Utility::LinLogCos<false>::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.6907024642854258e-01, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + 0.5 );

  y = Utility::LinLogCos<false>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 - 0.5 );

  y = Utility::LinLogCos<false>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLogCos_false, interpolateAndProcess_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLogCos<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.6907024642854258e-01, 1e-15 );

  x = -0.5;

  y = Utility::LinLogCos<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 0.5;

  y = Utility::LinLogCos<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-LogCos interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinLogCos_false, interpolateAndProcess_processed )
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

  double y = Utility::LinLogCos<false>::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LinLogCos<false>::interpolateAndProcess( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LinLogCos<false>::interpolateAndProcess( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that interpolation type can be returned
FRENSIE_UNIT_TEST( LogCosLog_false, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogCosLog<false>::getInterpolationType(),
                       Utility::LOGCOSLOG_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogCosLog<false> >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGLOGCOS_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogCosLog_false, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogCosLog<false>::isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogCosLog<false>::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLog<false>::isIndepVarInValidRange(
                                        std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LogCosLog<false>::isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogCosLog_false, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogCosLog<false>::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogCosLog<false>::isDepVarInValidRange( -1.0 - 1e-10 ) );
  FRENSIE_CHECK( Utility::LogCosLog<false>::isDepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LogCosLog<false>::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLog<false>::isDepVarInValidRange( 1.0 - 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogCosLog<false>::isDepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LogCosLog<false>::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( LogCosLog_false, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogCosLog<false>::processIndepVar( 1.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogCosLog_false, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 ),
                                  Utility::LogCosLog<false>::processDepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogCosLog<false>::processDepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1e-15 ),
                                  Utility::LogCosLog<false>::processDepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLog_false, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                          Utility::LogCosLog<false>::recoverProcessedIndepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLog_false, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                          Utility::LogCosLog<false>::recoverProcessedDepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLog_false, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogCosLog<false>::calculateUnitBaseGridLength( 1e-3, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLog_false, calculateUnitBaseIndepVar )
{
  double y_min = 1e-3, y = 1e-2, L = 3.0;

  double eta = Utility::LogCosLog<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = 1e-3;

  eta = Utility::LogCosLog<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 0.020085536923187;

  eta = Utility::LogCosLog<false>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLog_false, calculateIndepVar )
{
  double y_min = 1e-3, L = 3.0, eta = 0.5;

  double y =  Utility::LogCosLog<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0044816890703382, 1e-12 );

  eta = 0.0;

  y = Utility::LogCosLog<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1e-3, 1e-12 );

  eta = 1.0;

  y = Utility::LogCosLog<false>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.020085536923187, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLog_false, calculateUnitBaseGridLengthProcessed )
{
  double grid_length = Utility::LogCosLog<false>::calculateUnitBaseGridLengthProcessed(
                                                         std::log(1e-3), std::log(1.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLog_false, calculateUnitBaseIndepVarProcessed )
{
  double y_min = Utility::LogCosLog<false>::processIndepVar(1e-3);
  double y = Utility::LogCosLog<false>::processIndepVar(1e-2);
  double L = 3.0;

  double eta = Utility::LogCosLog<false>::calculateUnitBaseIndepVarProcessed(
                                                                 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = Utility::LogCosLog<false>::processIndepVar(1e-3);

  eta = Utility::LogCosLog<false>::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = Utility::LogCosLog<false>::processIndepVar(0.020085536923187);

  eta = Utility::LogCosLog<false>::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLog_false, calculateProcessedIndepVar )
{
  double y_min = Utility::LogCosLog<false>::processIndepVar(1e-3);
  double L = 3.0, eta = 0.5;

  double y = Utility::LogCosLog<false>::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                 y,
                 Utility::LogCosLog<false>::processIndepVar(0.0044816890703382),
                 1e-12 );

  eta = 0.0;

  y = Utility::LogCosLog<false>::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LogCosLog<false>::processIndepVar(1e-3),
                          1e-12 );

  eta = 1.0;

  y = Utility::LogCosLog<false>::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                  y,
                  Utility::LogCosLog<false>::processIndepVar(0.020085536923187),
                  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLog_false, interpolate_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = -0.5, y1 = 0.5;

  double y = Utility::LogCosLog<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459621556140e-01, 1e-15 );

  x = 0.1;

  y = Utility::LogCosLog<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  x = 10.0;

  y = Utility::LogCosLog<false>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLog_false, interpolate_processed )
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

  double y = Utility::LogCosLog<false>::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459621556118e-01, 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LogCosLog<false>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LogCosLog<false>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLog_false, interpolateAndProcess_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = -0.5, y1 = 0.5;

  double log_y = Utility::LogCosLog<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 1.3397459621556140e-01 ), 1e-15 );

  x = 0.1;

  log_y = Utility::LogCosLog<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + 0.5 ), 1e-15 );

  x = 10.0;

  log_y = Utility::LogCosLog<false>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLog_false, interpolateAndProcess_processed )
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

  double log_y = Utility::LogCosLog<false>::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 1.3397459621556118e-01 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  log_y = Utility::LogCosLog<false>::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + 0.5 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  log_y = Utility::LogCosLog<false>::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 - 0.5 ), 1e-15 );
}


//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LogLogCos_true, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogLogCos<true>::getInterpolationType(),
                          Utility::LOGLOGCOS_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogLogCos<true> >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                          Utility::LOGCOSLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogLogCos_true, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogLogCos<true>::isIndepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogLogCos<true>::isIndepVarInValidRange( -1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::LogLogCos<true>::isIndepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LogLogCos<true>::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogLogCos<true>::isIndepVarInValidRange( 1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::LogLogCos<true>::isIndepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LogLogCos<true>::isIndepVarInValidRange( 1.0 + 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogLogCos<true>::isIndepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogLogCos_true, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogLogCos<true>::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogLogCos<true>::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogLogCos<true>::isDepVarInValidRange(
                  std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LogLogCos<true>::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
FRENSIE_UNIT_TEST( LogLogCos_true, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 + delta ),
                                  Utility::LogLogCos<true>::processIndepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1.0 + delta ),
                                  Utility::LogLogCos<true>::processIndepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( delta ),
                                  Utility::LogLogCos<true>::processIndepVar( 1.0 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogLogCos_true, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogLogCos<true>::processDepVar( 1.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogLogCos_true, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, Utility::LogLogCos<true>::recoverProcessedIndepVar(
                          std::log( 2.0 + delta ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0, Utility::LogLogCos<true>::recoverProcessedIndepVar(
                          std::log( 1.0 + delta ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, Utility::LogLogCos<true>::recoverProcessedIndepVar(
                          std::log( delta ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogLogCos_true, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                                  Utility::LogLogCos<true>::recoverProcessedDepVar( 0.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogLogCos_true, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogLogCos<true>::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (2.0+delta)/(1.0+delta) ), 1e-15 );

  grid_length =
    Utility::LogLogCos<true>::calculateUnitBaseGridLength( -0.5, 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (1.5+delta)/(0.5+delta) ), 1e-15 );

  grid_length =
    Utility::LogLogCos<true>::calculateUnitBaseGridLength( -1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (2.0+delta)/delta ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogLogCos_true, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.5, L = 35.0;

  double eta = Utility::LogLogCos<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log((2+delta)/(0.5+delta))/35.0, 1e-12 );

  y = -1.0;

  eta = Utility::LogLogCos<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 1.0;

  eta = Utility::LogLogCos<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log((2.0+delta)/delta)/35.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogLogCos_true, calculateIndepVar )
{
  double y_min = -1.0, L = 35.0, eta = std::log((2+delta)/(0.5+delta))/35.0;

  double y =  Utility::LogLogCos<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-12 );

  eta = 0.0;

  y = Utility::LogLogCos<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  eta = std::log((2.0+delta)/delta)/35.0;

  y = Utility::LogLogCos<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogLogCos_true, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LogLogCos<true>::calculateUnitBaseGridLengthProcessed( std::log(1.0), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos<true>::calculateUnitBaseGridLengthProcessed( std::log(0.5), std::log(1.5) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos<true>::calculateUnitBaseGridLengthProcessed( std::log(1e-15), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogLogCos_true, calculateUnitBaseIndepVarProcessed )
{
  double processed_y_min = Utility::LogLogCos<true>::processIndepVar(1.0);
  double y = Utility::LogLogCos<true>::processIndepVar(0.5);
  double L = std::log((2.0+delta)/delta);

  double eta =
        Utility::LogLogCos<true>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log((0.5+delta)/delta)/L, 1e-10 );

  y = Utility::LogLogCos<true>::processIndepVar(-1.0);

  eta = Utility::LogLogCos<true>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-10 );

  y = Utility::LogLogCos<true>::processIndepVar(1.0);

  eta = Utility::LogLogCos<true>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogLogCos_true, calculateProcessedIndepVar )
{
  double processed_y_min = Utility::LogLogCos<true>::processIndepVar(1.0);
  double L = std::log((2.0+delta)/delta), eta = std::log((0.5+delta)/delta)/L;

  double y = Utility::LogLogCos<true>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LogLogCos<true>::processIndepVar(0.5), 1e-10 );

  eta = 1.0;

  y = Utility::LogLogCos<true>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LogLogCos<true>::processIndepVar(-1.0), 1e-10 );

  eta = 0.0;

  y = Utility::LogLogCos<true>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LogLogCos<true>::processIndepVar(1.0),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogLogCos_true, interpolate_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 10.0, y1 = 1000.0;

  double y = Utility::LogLogCos<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 5.47192949446913E1, 1e-15 );

  x = -0.5;

  y = Utility::LogLogCos<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  x = 0.5;

  y = Utility::LogLogCos<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogLogCos_true, interpolate_processed )
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

  double y = Utility::LogLogCos<true>::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 5.47192949446913E1, 1e-15 );

  processed_x = Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta + 0.5 );

  y = Utility::LogLogCos<true>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  processed_x = Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta - 0.5 );

  y = Utility::LogLogCos<true>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogLogCos_true, interpolateAndProcess_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 10.0, y1 = 1000.0;

  double log_y = Utility::LogLogCos<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 5.47192949446913E1 ), 1e-15 );

  x = -0.5;

  log_y = Utility::LogLogCos<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );

  x = 0.5;

  log_y = Utility::LogLogCos<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogLogCos_true, interpolateAndProcess_processed )
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

  double log_y = Utility::LogLogCos<true>::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 5.47192949446913E1 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta + 0.5 );

  log_y = Utility::LogLogCos<true>::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + delta - 0.5 );

  log_y = Utility::LogLogCos<true>::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LogCosLin_true, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogCosLin<true>::getInterpolationType(),
                       Utility::LOGCOSLIN_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogCosLin<true> >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LINLOGCOS_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogCosLin_true, isIndepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LogCosLin<true>::isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LogCosLin<true>::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLin<true>::isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogCosLin_true, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogCosLin<true>::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogCosLin<true>::isDepVarInValidRange( -1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::LogCosLin<true>::isDepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LogCosLin<true>::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLin<true>::isDepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LogCosLin<true>::isDepVarInValidRange( 1.0 + 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogCosLin<true>::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( LogCosLin_true, processIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LogCosLin<true>::processIndepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LogCosLin<true>::processIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LogCosLin<true>::processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogCosLin_true, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 + delta ),
                                  Utility::LogCosLin<true>::processDepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1.0 + delta ),
                                  Utility::LogCosLin<true>::processDepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( delta ),
                                  Utility::LogCosLin<true>::processDepVar( 1.0 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLin_true, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LogCosLin<true>::recoverProcessedIndepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LogCosLin<true>::recoverProcessedIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LogCosLin<true>::recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLin_true, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                          Utility::LogCosLin<true>::recoverProcessedDepVar( std::log( delta ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLin_true, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogCosLin<true>::calculateUnitBaseGridLength( -4.0, -1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::LogCosLin<true>::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin<true>::calculateUnitBaseGridLength( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin<true>::calculateUnitBaseGridLength( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLin_true, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LogCosLin<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LogCosLin<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LogCosLin<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLin_true, calculateIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LogCosLin<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::LogCosLin<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LogCosLin<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLin_true, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LogCosLin<true>::calculateUnitBaseGridLengthProcessed( -4.0, -1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::LogCosLin<true>::calculateUnitBaseGridLengthProcessed( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin<true>::calculateUnitBaseGridLengthProcessed( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin<true>::calculateUnitBaseGridLengthProcessed( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLin_true, calculateUnitBaseIndepVarProcessed )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LogCosLin<true>::calculateUnitBaseIndepVarProcessed(
                                                                 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LogCosLin<true>::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LogCosLin<true>::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLin_true, calculateProcessedIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LogCosLin<true>::calculateProcessedIndepVar(
                                                               eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::LogCosLin<true>::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LogCosLin<true>::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLin_true, interpolate_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = -0.5, y1 = 0.5;

  double y = Utility::LogCosLin<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459620009144e-01, 1e-15 );

  x = 0.0;

  y = Utility::LogCosLin<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  x = 1.0;

  y = Utility::LogCosLin<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLin_true, interpolate_processed )
{
  double processed_x0 =
    Utility:: LogLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 =
    Utility:: LogLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x =
    Utility:: LogLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 =
    Utility:: LogLinDataProcessing::processDependentVar( 1.0 + delta + 0.5 );
  double processed_y1 =
    Utility:: LogLinDataProcessing::processDependentVar( 1.0 + delta - 0.5 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::LogCosLin<true>::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459620009144e-01, 1e-14 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::LogCosLin<true>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 1.0 );

  y = Utility::LogCosLin<true>::interpolate( processed_x0,
                                    processed_x,
                                    processed_y0,
                                    processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLin_true, interpolateAndProcess_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = -0.5, y1 = 0.5;

  double log_y = Utility::LogCosLin<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 1.3397459620009144e-01 ), 1e-15 );

  x = 0.0;

  log_y = Utility::LogCosLin<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta + 0.5 ), 1e-15 );

  x = 1.0;

  log_y = Utility::LogCosLin<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLin_true, interpolateAndProcess_processed )
{
  double processed_x0 =
    Utility:: LogLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 =
    Utility:: LogLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x =
    Utility:: LogLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 =
    Utility:: LogLinDataProcessing::processDependentVar( 0.1 );
  double processed_y1 =
    Utility:: LogLinDataProcessing::processDependentVar( 10.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double log_y = Utility::LogCosLin<true>::interpolateAndProcess( processed_x0,
                                                         processed_x,
                                                         processed_y0,
                                                         processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, 0.0, 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 0.0 );

  log_y = Utility::LogCosLin<true>::interpolateAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 0.1 ), 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 1.0 );

  log_y = Utility::LogCosLin<true>::interpolateAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LinLogCos_true, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LinLogCos<true>::getInterpolationType(),
                       Utility::LINLOGCOS_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LinLogCos<true> >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGCOSLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LinLogCos_true, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LinLogCos<true>::isIndepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LinLogCos<true>::isIndepVarInValidRange( -1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::LinLogCos<true>::isIndepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LinLogCos<true>::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinLogCos<true>::isIndepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LinLogCos<true>::isIndepVarInValidRange( 1.0 + 1e-15 ) );
  FRENSIE_CHECK( !Utility::LinLogCos<true>::isIndepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LinLogCos_true, isDepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LinLogCos<true>::isDepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LinLogCos<true>::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinLogCos<true>::isDepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
FRENSIE_UNIT_TEST( LinLogCos_true, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 + delta ),
                                  Utility::LinLogCos<true>::processIndepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1.0 + delta ),
                                  Utility::LinLogCos<true>::processIndepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 1.0 + delta - 1.0 ),
                                  Utility::LinLogCos<true>::processIndepVar( 1.0 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LinLogCos_true, processDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLogCos<true>::processDepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLogCos<true>::processDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLogCos<true>::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LinLogCos_true, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, Utility::LinLogCos<true>::recoverProcessedIndepVar(
                          std::log( 2.0 + delta ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0, Utility::LinLogCos<true>::recoverProcessedIndepVar(
                          std::log( 1.0 + delta ) ),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0, Utility::LinLogCos<true>::recoverProcessedIndepVar(
                          std::log( 1.0 + delta - 1.0 ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LinLogCos_true, recoverProcessedDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLogCos<true>::recoverProcessedDepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLogCos<true>::recoverProcessedDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLogCos<true>::recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinLogCos_true, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LinLogCos<true>::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (2.0 + delta)/(1.0 + delta) ), 1e-15 );

  grid_length =
    Utility::LinLogCos<true>::calculateUnitBaseGridLength( -0.5, 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (3.0/2.0 + delta)/(0.5 + delta) ), 1e-15 );

  grid_length =
    Utility::LinLogCos<true>::calculateUnitBaseGridLength( -1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( (2.0 + delta)/delta ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinLogCos_true, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.5, L = 35.0;

  double eta = Utility::LinLogCos<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log((2+delta)/(0.5+delta))/35.0, 1e-12 );

  y = -1.0;

  eta = Utility::LinLogCos<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 1.0;

  eta = Utility::LinLogCos<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log( (2.0+delta)/delta)/35.0, 1e-8 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinLogCos_true, calculateIndepVar )
{
  double y_min = -1.0, L = 35.0, eta = std::log((2+delta)/(0.5+delta))/35.0;

  double y =  Utility::LinLogCos<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-12 );

  eta = 0.0;

  y = Utility::LinLogCos<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  eta = std::log((2.0+delta)/delta)/35.0;

  y = Utility::LinLogCos<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinLogCos_true, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LinLogCos<true>::calculateUnitBaseGridLengthProcessed( std::log(1.0), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos<true>::calculateUnitBaseGridLengthProcessed( std::log(0.5), std::log(1.5) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos<true>::calculateUnitBaseGridLengthProcessed( std::log(1e-15), std::log(2.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, std::log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinLogCos_true, calculateUnitBaseIndepVarProcessed )
{
  double processed_y_min = Utility::LinLogCos<true>::processIndepVar(1.0);
  double y = Utility::LinLogCos<true>::processIndepVar(0.5);
  double L = std::log((2.0+delta)/delta);

  double eta =
        Utility::LinLogCos<true>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, std::log((0.5+delta)/delta)/L, 1e-12 );

  y = Utility::LinLogCos<true>::processIndepVar(-1.0);

  eta = Utility::LinLogCos<true>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );

  y = Utility::LinLogCos<true>::processIndepVar(1.0);

  eta = Utility::LinLogCos<true>::calculateUnitBaseIndepVarProcessed( y, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinLogCos_true, calculateProcessedIndepVar )
{
  double processed_y_min = Utility::LinLogCos<true>::processIndepVar(1.0);
  double L = std::log((2.0+delta)/delta), eta = std::log((0.5+delta)/delta)/L;

  double y = Utility::LinLogCos<true>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LinLogCos<true>::processIndepVar(0.5), 1e-10 );

  eta = 1.0;

  y = Utility::LinLogCos<true>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, Utility::LinLogCos<true>::processIndepVar(-1.0), 1e-10 );

  eta = 0.0;

  y = Utility::LinLogCos<true>::calculateProcessedIndepVar( eta, processed_y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LinLogCos<true>::processIndepVar(1.0),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLogCos_true, interpolate_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLogCos<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.690702464429940E-1, 1e-14 );

  x = -0.5;

  y = Utility::LinLogCos<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 0.5;

  y = Utility::LinLogCos<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinLogCos_true, interpolate_processed )
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

  double y = Utility::LinLogCos<true>::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.690702464429940E-1, 1e-14 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + delta + 0.5 );

  y = Utility::LinLogCos<true>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + delta - 0.5 );

  y = Utility::LinLogCos<true>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLogCos_true, interpolateAndProcess_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLogCos<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 3.690702464429940E-1, 1e-14 );

  x = -0.5;

  y = Utility::LinLogCos<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 0.5;

  y = Utility::LinLogCos<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-LogCos interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinLogCos_true, interpolateAndProcess_processed )
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

  double y = Utility::LinLogCos<true>::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LinLogCos<true>::interpolateAndProcess( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LinLogCos<true>::interpolateAndProcess( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that interpolation type can be returned
FRENSIE_UNIT_TEST( LogCosLog_true, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogCosLog<true>::getInterpolationType(),
                       Utility::LOGCOSLOG_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogCosLog<true> >::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGLOGCOS_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogCosLog_true, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogCosLog<true>::isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogCosLog<true>::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLog<true>::isIndepVarInValidRange(
                                        std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LogCosLog<true>::isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogCosLog_true, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogCosLog<true>::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogCosLog<true>::isDepVarInValidRange( -1.0 - 1e-15 ) );
  FRENSIE_CHECK( Utility::LogCosLog<true>::isDepVarInValidRange( -1.0 ) );
  FRENSIE_CHECK( Utility::LogCosLog<true>::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogCosLog<true>::isDepVarInValidRange( 1.0 ) );
  FRENSIE_CHECK( !Utility::LogCosLog<true>::isDepVarInValidRange( 1.0 + 1e-15 ) );
  FRENSIE_CHECK( !Utility::LogCosLog<true>::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( LogCosLog_true, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
                                  Utility::LogCosLog<true>::processIndepVar( 1.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogCosLog_true, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log( 2.0 + delta ),
                                  Utility::LogCosLog<true>::processDepVar( -1.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(1.0 + delta),
                                  Utility::LogCosLog<true>::processDepVar( 0.0 ),
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(delta),
                                  Utility::LogCosLog<true>::processDepVar( 1.0 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLog_true, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                          Utility::LogCosLog<true>::recoverProcessedIndepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogCosLog_true, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                          Utility::LogCosLog<true>::recoverProcessedDepVar( std::log(delta) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLog_true, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogCosLog<true>::calculateUnitBaseGridLength( 1e-3, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLog_true, calculateUnitBaseIndepVar )
{
  double y_min = 1e-3, y = 1e-2, L = 3.0;

  double eta = Utility::LogCosLog<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = 1e-3;

  eta = Utility::LogCosLog<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 0.020085536923187;

  eta = Utility::LogCosLog<true>::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLog_true, calculateIndepVar )
{
  double y_min = 1e-3, L = 3.0, eta = 0.5;

  double y =  Utility::LogCosLog<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0044816890703382, 1e-12 );

  eta = 0.0;

  y = Utility::LogCosLog<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1e-3, 1e-12 );

  eta = 1.0;

  y = Utility::LogCosLog<true>::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.020085536923187, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogCosLog_true, calculateUnitBaseGridLengthProcessed )
{
  double grid_length = Utility::LogCosLog<true>::calculateUnitBaseGridLengthProcessed(
                                                         std::log(1e-3), std::log(1.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogCosLog_true, calculateUnitBaseIndepVarProcessed )
{
  double y_min = Utility::LogCosLog<true>::processIndepVar(1e-3);
  double y = Utility::LogCosLog<true>::processIndepVar(1e-2);
  double L = 3.0;

  double eta = Utility::LogCosLog<true>::calculateUnitBaseIndepVarProcessed(
                                                                 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = Utility::LogCosLog<true>::processIndepVar(1e-3);

  eta = Utility::LogCosLog<true>::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = Utility::LogCosLog<true>::processIndepVar(0.020085536923187);

  eta = Utility::LogCosLog<true>::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogCosLog_true, calculateProcessedIndepVar )
{
  double y_min = Utility::LogCosLog<true>::processIndepVar(1e-3);
  double L = 3.0, eta = 0.5;

  double y = Utility::LogCosLog<true>::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                 y,
                 Utility::LogCosLog<true>::processIndepVar(0.0044816890703382),
                 1e-12 );

  eta = 0.0;

  y = Utility::LogCosLog<true>::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
                          Utility::LogCosLog<true>::processIndepVar(1e-3),
                          1e-12 );

  eta = 1.0;

  y = Utility::LogCosLog<true>::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                  y,
                  Utility::LogCosLog<true>::processIndepVar(0.020085536923187),
                  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLog_true, interpolate_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = -0.5, y1 = 0.5;

  double y = Utility::LogCosLog<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459620009144e-01, 1e-15 );

  x = 0.1;

  y = Utility::LogCosLog<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  x = 10.0;

  y = Utility::LogCosLog<true>::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLog_true, interpolate_processed )
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

  double y = Utility::LogCosLog<true>::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.3397459620009144e-01, 1e-14 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LogCosLog<true>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LogCosLog<true>::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogCosLog_true, interpolateAndProcess_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = -0.5, y1 = 0.5;

  double log_y = Utility::LogCosLog<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 1.3397459620009144e-01 ), 1e-15 );

  x = 0.1;

  log_y = Utility::LogCosLog<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta + 0.5 ), 1e-15 );

  x = 10.0;

  log_y = Utility::LogCosLog<true>::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogCosLog_true, interpolateAndProcess_processed )
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

  double log_y = Utility::LogCosLog<true>::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 1.3397459620009144e-01 ), 1e-14 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  log_y = Utility::LogCosLog<true>::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta + 0.5 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  log_y = Utility::LogCosLog<true>::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1.0 + delta - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstCosineInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
