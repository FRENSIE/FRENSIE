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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_CosineInterpolationPolicy.hpp"
#include "Utility_DataProcessingPolicy.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
TEUCHOS_UNIT_TEST( LogLogCos, getInterpolationType )
{
  TEST_EQUALITY_CONST( Utility::LogLogCos::getInterpolationType(),
                       Utility::LOGLOGCOS_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogLogCos>::InterpPolicy InverseInterp;
  TEST_EQUALITY_CONST( InverseInterp::getInterpolationType(),
                       Utility::LOGCOSLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( LogLogCos, isIndepVarInValidRange )
{
  TEST_ASSERT( !Utility::LogLogCos::isIndepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( !Utility::LogLogCos::isIndepVarInValidRange( -1.0 - 1e-10 ) );
  TEST_ASSERT( Utility::LogLogCos::isIndepVarInValidRange( -1.0 ) );
  TEST_ASSERT( Utility::LogLogCos::isIndepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LogLogCos::isIndepVarInValidRange( 1.0 - 1e-15 ) );
  TEST_ASSERT( !Utility::LogLogCos::isIndepVarInValidRange( 1.0 ) );
  TEST_ASSERT( !Utility::LogLogCos::isIndepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
TEUCHOS_UNIT_TEST( LogLogCos, isDepVarInValidRange )
{
  TEST_ASSERT( !Utility::LogLogCos::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( !Utility::LogLogCos::isDepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LogLogCos::isDepVarInValidRange(
                  std::numeric_limits<double>::min() ) );
  TEST_ASSERT( Utility::LogLogCos::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
TEUCHOS_UNIT_TEST( LogLogCos, processIndepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( log( 2.0 ),
                                  Utility::LogLogCos::processIndepVar( -1.0 ),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 0.0,
                                  Utility::LogLogCos::processIndepVar( 0.0 ),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( log( 1e-15 ),
                                  Utility::LogLogCos::processIndepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
TEUCHOS_UNIT_TEST( LogLogCos, processDepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( 0.0,
                                  Utility::LogLogCos::processDepVar( 1.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
TEUCHOS_UNIT_TEST( LogLogCos, recoverProcessedIndepVar )
{
  TEST_FLOATING_EQUALITY( -1.0, Utility::LogLogCos::recoverProcessedIndepVar(
                          log( 2.0 ) ),
                          1e-15 );
  TEST_FLOATING_EQUALITY( 0.0, Utility::LogLogCos::recoverProcessedIndepVar(
                          0.0 ),
                          1e-15 );
  TEST_FLOATING_EQUALITY( 1.0, Utility::LogLogCos::recoverProcessedIndepVar(
                          log( 0.0 ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LogLogCos, recoverProcessedDepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( 1.0,
                                  Utility::LogLogCos::recoverProcessedDepVar( 0.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
TEUCHOS_UNIT_TEST( LogLogCos, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLength( -1.0, 0.0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLength( -0.5, 0.5 );

  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLength( -1.0, 1.0 - 1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LogLogCos, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.5, L = 35.0;

  double eta = Utility::LogLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, log(4)/35.0, 1e-12 );

  y = -1.0;

  eta = Utility::LogLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 1.0/3.0;

  eta = Utility::LogLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, log(3)/35.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LogLogCos, calculateIndepVar )
{
  double y_min = -1.0, L = 35.0, eta = log(4)/35.0;

  double y =  Utility::LogLogCos::calculateIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-12 );

  eta = 0.0;
  
  y = Utility::LogLogCos::calculateIndepVar( eta, y_min, L );
  
  TEST_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  eta = log(3)/35.0;

  y = Utility::LogLogCos::calculateIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 1.0/3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
TEUCHOS_UNIT_TEST( LogLogCos, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLengthProcessed( log(2.0), log(1.0) );
  
  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLengthProcessed( log(1.5), log(0.5) );

  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LogLogCos::calculateUnitBaseGridLengthProcessed( log(2.0), log(1e-15) );

  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LogLogCos, calculateUnitBaseIndepVarProcessed )
{
  double y_min = Utility::LogLogCos::processIndepVar(-1.0);
  double y = Utility::LogLogCos::processIndepVar(0.5);
  double L = 35.0;

  double eta =
        Utility::LogLogCos::calculateUnitBaseIndepVarProcessed( y_min, y, L );

  TEST_FLOATING_EQUALITY( eta, log(4)/35.0, 1e-12 );

  y = Utility::LogLogCos::processIndepVar(-1.0);

  eta = Utility::LogLogCos::calculateUnitBaseIndepVarProcessed( y_min, y, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = Utility::LogLogCos::processIndepVar(1.0/3.0);

  eta = Utility::LogLogCos::calculateUnitBaseIndepVarProcessed( y_min, y, L );

  TEST_FLOATING_EQUALITY( eta, log(3)/35.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LogLogCos, calculateProcessedIndepVar )
{
  double y_min = Utility::LogLogCos::processIndepVar(-1.0);
  double L = 35.0, eta = log(4)/35.0;

  double y = Utility::LogLogCos::calculateProcessedIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, Utility::LogLogCos::processIndepVar(0.5), 1e-12 );

  eta = 0.0;

  y = Utility::LogLogCos::calculateProcessedIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, Utility::LogLogCos::processIndepVar(-1.0), 1e-12 );

  eta = log(3)/35.0;

  y = Utility::LogLogCos::calculateProcessedIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y,
                          Utility::LogLogCos::processIndepVar(1.0/3.0),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
TEUCHOS_UNIT_TEST( LogLogCos, interpolate_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 10.0, y1 = 1000.0;

  double y = Utility::LogLogCos::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 5.4719294941049760e+01, 1e-15 );

  x = -0.5;

  y = Utility::LogLogCos::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  x = 0.5;

  y = Utility::LogLogCos::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogLogCos, interpolate_processed )
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

  TEST_FLOATING_EQUALITY( y, 5.4719294941049760e+01, 1e-15 );

  processed_x = Utility::LogLogDataProcessing::processIndependentVar( 1.0 + 0.5 );

  y = Utility::LogLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  TEST_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  processed_x = Utility::LogLogDataProcessing::processIndependentVar( 1.0 - 0.5 );

  y = Utility::LogLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  TEST_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
TEUCHOS_UNIT_TEST( LogLogCos, interpolateAndProcess_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 10.0, y1 = 1000.0;

  double log_y = Utility::LogLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 5.4719294941049760e+01 ), 1e-15 );

  x = -0.5;

  log_y = Utility::LogLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 10.0 ), 1e-15 );

  x = 0.5;

  log_y = Utility::LogLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogLogCos, interpolateAndProcess_processed )
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
    (processed_y0 - processed_y1)/(processed_x1 - processed_x0);

  double log_y = Utility::LogLogCos::interpolateAndProcess( processed_x0,
                                                            processed_x,
                                                            processed_y0,
                                                            processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 5.4719294941049760e+01 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 + 0.5 );

  log_y = Utility::LogLogCos::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 10.0 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 - 0.5 );

  log_y = Utility::LogLogCos::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
TEUCHOS_UNIT_TEST( LogCosLin, getInterpolationType )
{
  TEST_EQUALITY_CONST( Utility::LogCosLin::getInterpolationType(),
                       Utility::LOGCOSLIN_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogCosLin>::InterpPolicy InverseInterp;
  TEST_EQUALITY_CONST( InverseInterp::getInterpolationType(),
                       Utility::LINLOGCOS_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( LogCosLin, isIndepVarInValidRange )
{
  TEST_ASSERT( Utility::LogCosLin::isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( Utility::LogCosLin::isIndepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LogCosLin::isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
TEUCHOS_UNIT_TEST( LogCosLin, isDepVarInValidRange )
{
  TEST_ASSERT( !Utility::LogCosLin::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( !Utility::LogCosLin::isDepVarInValidRange( -1.0 - 1e-10 ) );
  TEST_ASSERT( Utility::LogCosLin::isDepVarInValidRange( -1.0 ) );
  TEST_ASSERT( Utility::LogCosLin::isDepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LogCosLin::isDepVarInValidRange( 1.0 - 1e-15 ) );
  TEST_ASSERT( !Utility::LogCosLin::isDepVarInValidRange( 1.0 ) );
  TEST_ASSERT( !Utility::LogCosLin::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
TEUCHOS_UNIT_TEST( LogCosLin, processIndepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LogCosLin::processIndepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, Utility::LogCosLin::processIndepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LogCosLin::processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
TEUCHOS_UNIT_TEST( LogCosLin, processDepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( log( 2.0 ),
                                  Utility::LogCosLin::processDepVar( -1.0 ),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 0.0,
                                  Utility::LogCosLin::processDepVar( 0.0 ),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( log( 1e-15 ),
                                  Utility::LogCosLin::processDepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
TEUCHOS_UNIT_TEST( LogCosLin, recoverProcessedIndepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LogCosLin::recoverProcessedIndepVar(-1.0) );
  TEST_EQUALITY_CONST( 0.0, Utility::LogCosLin::recoverProcessedIndepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LogCosLin::recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LogCosLin, recoverProcessedDepVar )
{
  TEST_FLOATING_EQUALITY( 0.0,
                          Utility::LogCosLin::recoverProcessedDepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
TEUCHOS_UNIT_TEST( LogCosLin, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLength( -4.0, -1.0 );
  
  TEST_EQUALITY_CONST( grid_length, 3.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLength( -1.0, 0.0 );

  TEST_EQUALITY_CONST( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLength( 0.0, 1.0 );

  TEST_EQUALITY_CONST( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLength( 1.0, 4.0 );

  TEST_EQUALITY_CONST( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LogCosLin, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LogCosLin::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LogCosLin::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LogCosLin::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LogCosLin, calculateIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LogCosLin::calculateIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::LogCosLin::calculateIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LogCosLin::calculateIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
TEUCHOS_UNIT_TEST( LogCosLin, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLengthProcessed( -4.0, -1.0 );
  
  TEST_EQUALITY_CONST( grid_length, 3.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLengthProcessed( -1.0, 0.0 );

  TEST_EQUALITY_CONST( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLengthProcessed( 0.0, 1.0 );

  TEST_EQUALITY_CONST( grid_length, 1.0 );

  grid_length =
    Utility::LogCosLin::calculateUnitBaseGridLengthProcessed( 1.0, 4.0 );

  TEST_EQUALITY_CONST( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LogCosLin, calculateUnitBaseIndepVarProcessed )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LogCosLin::calculateUnitBaseIndepVarProcessed(
                                                                 y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LogCosLin::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LogCosLin::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LogCosLin, calculateProcessedIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LogCosLin::calculateProcessedIndepVar(
                                                               eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::LogCosLin::calculateProcessedIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LogCosLin::calculateProcessedIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
TEUCHOS_UNIT_TEST( LogCosLin, interpolate_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = -0.5, y1 = 0.5;

  double y = Utility::LogCosLin::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1.3397459621556140e-01, 1e-15 );

  x = 0.0;

  y = Utility::LogCosLin::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  x = 1.0;

  y = Utility::LogCosLin::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogCosLin, interpolate_processed )
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

  double y = Utility::LogCosLin::interpolate( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  TEST_FLOATING_EQUALITY( y, 1.3397459621556140e-01, 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::LogCosLin::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  TEST_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 1.0 );

  y = Utility::LogCosLin::interpolate( processed_x0,
                                    processed_x,
                                    processed_y0,
                                    processed_slope );

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
TEUCHOS_UNIT_TEST( LogCosLin, interpolateAndProcess_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = -0.5, y1 = 0.5;

  double log_y = Utility::LogCosLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  UTILITY_TEST_FLOATING_EQUALITY( log_y, log( 1.0 - 1.3397459621556140e-01 ), 1e-15 );

  x = 0.0;

  log_y = Utility::LogCosLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 1.0 + 0.5 ), 1e-15 );

  x = 1.0;

  log_y = Utility::LogCosLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 1.0 - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogCosLin, interpolateAndProcess_processed )
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

  double log_y = Utility::LogCosLin::interpolateAndProcess( processed_x0,
                                                         processed_x,
                                                         processed_y0,
                                                         processed_slope );

  UTILITY_TEST_FLOATING_EQUALITY( log_y, 0.0, 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 0.0 );

  log_y = Utility::LogCosLin::interpolateAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 0.1 ), 1e-15 );

  processed_x = Utility:: LogLinDataProcessing::processIndependentVar( 1.0 );

  log_y = Utility::LogCosLin::interpolateAndProcess( processed_x0,
                                                  processed_x,
                                                  processed_y0,
                                                  processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 10.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
TEUCHOS_UNIT_TEST( LinLogCos, getInterpolationType )
{
  TEST_EQUALITY_CONST( Utility::LinLogCos::getInterpolationType(),
                       Utility::LINLOGCOS_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LinLogCos>::InterpPolicy InverseInterp;
  TEST_EQUALITY_CONST( InverseInterp::getInterpolationType(),
                       Utility::LOGCOSLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( LinLogCos, isIndepVarInValidRange )
{
  TEST_ASSERT( !Utility::LinLogCos::isIndepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( !Utility::LinLogCos::isIndepVarInValidRange( -1.0 - 1e-10 ) );
  TEST_ASSERT( Utility::LinLogCos::isIndepVarInValidRange( -1.0 ) );
  TEST_ASSERT( Utility::LinLogCos::isIndepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LinLogCos::isIndepVarInValidRange( 1.0 - 1e-15 ) );
  TEST_ASSERT( !Utility::LinLogCos::isIndepVarInValidRange( 1.0 ) );
  TEST_ASSERT( !Utility::LinLogCos::isIndepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
TEUCHOS_UNIT_TEST( LinLogCos, isDepVarInValidRange )
{
  TEST_ASSERT( Utility::LinLogCos::isDepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( Utility::LinLogCos::isDepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LinLogCos::isDepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
TEUCHOS_UNIT_TEST( LinLogCos, processIndepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( log( 2.0 ),
                                  Utility::LinLogCos::processIndepVar( -1.0 ),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 0.0,
                                  Utility::LinLogCos::processIndepVar( 0.0 ),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( log( 1e-15 ),
                                  Utility::LinLogCos::processIndepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
TEUCHOS_UNIT_TEST( LinLogCos, processDepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLogCos::processDepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLogCos::processDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLogCos::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
TEUCHOS_UNIT_TEST( LinLogCos, recoverProcessedIndepVar )
{
  TEST_FLOATING_EQUALITY( -1.0, Utility::LinLogCos::recoverProcessedIndepVar(
                          log( 2.0 ) ),
                          1e-15 );
  TEST_FLOATING_EQUALITY( 0.0, Utility::LinLogCos::recoverProcessedIndepVar(
                          0.0 ),
                          1e-15 );
  TEST_FLOATING_EQUALITY( 1.0, Utility::LinLogCos::recoverProcessedIndepVar(
                          log( 0.0 ) ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LinLogCos, recoverProcessedDepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLogCos::recoverProcessedDepVar(-1.0) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLogCos::recoverProcessedDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLogCos::recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
TEUCHOS_UNIT_TEST( LinLogCos, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLength( -1.0, 0.0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLength( -0.5, 0.5 );

  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLength( -1.0, 1.0 - 1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LinLogCos, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.5, L = 35.0;

  double eta = Utility::LinLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, log(4)/35.0, 1e-12 );

  y = -1.0;

  eta = Utility::LinLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 1.0/3.0;

  eta = Utility::LinLogCos::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, log(3)/35.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LinLogCos, calculateIndepVar )
{
  double y_min = -1.0, L = 35.0, eta = log(4)/35.0;

  double y =  Utility::LinLogCos::calculateIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-12 );

  eta = 0.0;
  
  y = Utility::LinLogCos::calculateIndepVar( eta, y_min, L );
  
  TEST_FLOATING_EQUALITY( y, -1.0, 1e-12 );

  eta = log(3)/35.0;

  y = Utility::LinLogCos::calculateIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 1.0/3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
TEUCHOS_UNIT_TEST( LinLogCos, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLengthProcessed( log(2.0), log(1.0) );
  
  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 2.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLengthProcessed( log(1.5), log(0.5) );

  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 3.0 ), 1e-15 );

  grid_length =
    Utility::LinLogCos::calculateUnitBaseGridLengthProcessed( log(2.0), log(1e-15) );

  UTILITY_TEST_FLOATING_EQUALITY( grid_length, log( 2e15 ), 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LinLogCos, calculateUnitBaseIndepVarProcessed )
{
  double y_min = Utility::LinLogCos::processIndepVar(-1.0);
  double y = Utility::LinLogCos::processIndepVar(0.5);
  double L = 35.0;

  double eta =
        Utility::LinLogCos::calculateUnitBaseIndepVarProcessed( y_min, y, L );

  TEST_FLOATING_EQUALITY( eta, log(4)/35.0, 1e-12 );

  y = Utility::LinLogCos::processIndepVar(-1.0);

  eta = Utility::LinLogCos::calculateUnitBaseIndepVarProcessed( y_min, y, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = Utility::LinLogCos::processIndepVar(1.0/3.0);

  eta = Utility::LinLogCos::calculateUnitBaseIndepVarProcessed( y_min, y, L );

  TEST_FLOATING_EQUALITY( eta, log(3)/35.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LinLogCos, calculateProcessedIndepVar )
{
  double y_min = Utility::LogLogCos::processIndepVar(-1.0);
  double L = 35.0, eta = log(4)/35.0;

  double y = Utility::LogLogCos::calculateProcessedIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, Utility::LogLogCos::processIndepVar(0.5), 1e-12 );

  eta = 0.0;

  y = Utility::LogLogCos::calculateProcessedIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, Utility::LogLogCos::processIndepVar(-1.0), 1e-12 );

  eta = log(3)/35.0;

  y = Utility::LogLogCos::calculateProcessedIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y,
                          Utility::LogLogCos::processIndepVar(1.0/3.0),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
TEUCHOS_UNIT_TEST( LinLogCos, interpolate_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLogCos::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 3.6907024642854258e-01, 1e-15 );

  x = -0.5;

  y = Utility::LinLogCos::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 0.5;

  y = Utility::LinLogCos::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LinLogCos, interpolate_processed )
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

  TEST_FLOATING_EQUALITY( y, 3.6907024642854258e-01, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 + 0.5 );

  y = Utility::LinLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 1.0 - 0.5 );

  y = Utility::LinLogCos::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
TEUCHOS_UNIT_TEST( LinLogCos, interpolateAndProcess_raw )
{
  double x0 = -0.5, x1 = 0.5, x = 0.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 3.6907024642854258e-01, 1e-15 );

  x = -0.5;

  y = Utility::LinLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 0.5;

  y = Utility::LinLogCos::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LinLogCos, interpolateAndProcess_processed )
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

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LinLogCos::interpolateAndProcess( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LinLogCos::interpolateAndProcess( processed_x0,
                                              processed_x,
                                              processed_y0,
                                              processed_slope );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that interpolation type can be returned
TEUCHOS_UNIT_TEST( LogCosLog, getInterpolationType )
{
  TEST_EQUALITY_CONST( Utility::LogCosLog::getInterpolationType(),
                       Utility::LOGCOSLOG_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogCosLog>::InterpPolicy InverseInterp;
  TEST_EQUALITY_CONST( InverseInterp::getInterpolationType(),
                       Utility::LOGLOGCOS_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( LogCosLog, isIndepVarInValidRange )
{
  TEST_ASSERT( !Utility::LogCosLog::isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( !Utility::LogCosLog::isIndepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LogCosLog::isIndepVarInValidRange(
                                        std::numeric_limits<double>::min() ) );
  TEST_ASSERT( Utility::LogCosLog::isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
TEUCHOS_UNIT_TEST( LogCosLog, isDepVarInValidRange )
{
  TEST_ASSERT( !Utility::LogCosLog::isDepVarInValidRange(
                  -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( !Utility::LogCosLog::isDepVarInValidRange( -1.0 - 1e-10 ) );
  TEST_ASSERT( Utility::LogCosLog::isDepVarInValidRange( -1.0 ) );
  TEST_ASSERT( Utility::LogCosLog::isDepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LogCosLog::isDepVarInValidRange( 1.0 - 1e-15 ) );
  TEST_ASSERT( !Utility::LogCosLog::isDepVarInValidRange( 1.0 ) );
  TEST_ASSERT( !Utility::LogCosLog::isDepVarInValidRange(
                  std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
TEUCHOS_UNIT_TEST( LogCosLog, processIndepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( 0.0,
                                  Utility::LogCosLog::processIndepVar( 1.0 ),
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
TEUCHOS_UNIT_TEST( LogCosLog, processDepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( log( 2.0 ),
                                  Utility::LogCosLog::processDepVar( -1.0 ),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 0.0,
                                  Utility::LogCosLog::processDepVar( 0.0 ),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( log( 1e-15 ),
                                  Utility::LogCosLog::processDepVar( 1.0 - 1e-15 ),
                                  1e-4 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
TEUCHOS_UNIT_TEST( LogCosLog, recoverProcessedIndepVar )
{
  TEST_FLOATING_EQUALITY( 1.0,
                          Utility::LogCosLog::recoverProcessedIndepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LogCosLog, recoverProcessedDepVar )
{
  TEST_FLOATING_EQUALITY( 0.0,
                          Utility::LogCosLog::recoverProcessedDepVar( 0.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
TEUCHOS_UNIT_TEST( LogCosLog, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogCosLog::calculateUnitBaseGridLength( 1e-3, 1.0 );

  TEST_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );     
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LogCosLog, calculateUnitBaseIndepVar )
{
  double y_min = 1e-3, y = 1e-2, L = 3.0;

  double eta = Utility::LogCosLog::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = 1e-3;

  eta = Utility::LogCosLog::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 0.020085536923187;

  eta = Utility::LogCosLog::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LogCosLog, calculateIndepVar )
{
  double y_min = 1e-3, L = 3.0, eta = 0.5;

  double y =  Utility::LogCosLog::calculateIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.0044816890703382, 1e-12 );

  eta = 0.0;
  
  y = Utility::LogCosLog::calculateIndepVar( eta, y_min, L );
  
  TEST_FLOATING_EQUALITY( y, 1e-3, 1e-12 );

  eta = 1.0;

  y = Utility::LogCosLog::calculateIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.020085536923187, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
TEUCHOS_UNIT_TEST( LogCosLog, calculateUnitBaseGridLengthProcessed )
{
  double grid_length = Utility::LogCosLog::calculateUnitBaseGridLengthProcessed(
                                                         log(1e-3), log(1.0) );

  TEST_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );     
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LogCosLog, calculateUnitBaseIndepVarProcessed )
{
  double y_min = Utility::LogCosLog::processIndepVar(1e-3);
  double y = Utility::LogCosLog::processIndepVar(1e-2);
  double L = 3.0;

  double eta = Utility::LogCosLog::calculateUnitBaseIndepVarProcessed(
                                                                 y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = Utility::LogCosLog::processIndepVar(1e-3);

  eta = Utility::LogCosLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = Utility::LogCosLog::processIndepVar(0.020085536923187);

  eta = Utility::LogCosLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LogCosLog, calculateProcessedIndepVar )
{
  double y_min = Utility::LogCosLog::processIndepVar(1e-3);
  double L = 3.0, eta = 0.5;

  double y = Utility::LogCosLog::calculateProcessedIndepVar(
                                                               eta, y_min, L );

  TEST_FLOATING_EQUALITY(
                 y,
                 Utility::LogCosLog::processIndepVar(0.0044816890703382),
                 1e-12 );

  eta = 0.0;

  y = Utility::LogCosLog::calculateProcessedIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y,
                          Utility::LogCosLog::processIndepVar(1e-3),
                          1e-12 );

  eta = 1.0;

  y = Utility::LogCosLog::calculateProcessedIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY(
                  y,
                  Utility::LogCosLog::processIndepVar(0.020085536923187),
                  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
TEUCHOS_UNIT_TEST( LogCosLog, interpolate_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = -0.5, y1 = 0.5;

  double y = Utility::LogCosLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1.3397459621556140e-01, 1e-15 );

  x = 0.1;

  y = Utility::LogCosLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  x = 10.0;

  y = Utility::LogCosLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogCosLog, interpolate_processed )
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

  TEST_FLOATING_EQUALITY( y, 1.3397459621556118e-01, 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LogCosLog::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  TEST_FLOATING_EQUALITY( y, -0.5, 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LogCosLog::interpolate( processed_x0,
                                       processed_x,
                                       processed_y0,
                                       processed_slope );

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
TEUCHOS_UNIT_TEST( LogCosLog, interpolateAndProcess_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = -0.5, y1 = 0.5;

  double log_y = Utility::LogCosLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 1.0 - 1.3397459621556140e-01 ), 1e-15 );

  x = 0.1;

  log_y = Utility::LogCosLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 1.0 + 0.5 ), 1e-15 );

  x = 10.0;

  log_y = Utility::LogCosLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 1.0 - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogCosLog, interpolateAndProcess_processed )
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

  TEST_FLOATING_EQUALITY( log_y, log( 1.0 - 1.3397459621556118e-01 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  log_y = Utility::LogCosLog::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 1.0 + 0.5 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  log_y = Utility::LogCosLog::interpolateAndProcess( processed_x0,
                                                     processed_x,
                                                     processed_y0,
                                                     processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 1.0 - 0.5 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstCosineInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
