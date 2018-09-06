//---------------------------------------------------------------------------//
//!
//! \file   tstInterpolationPolicy.cpp
//! \author Alex Robinson
//! \brief  Interpolation policy unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_DataProcessingPolicy.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LinLin, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LinLin::getInterpolationType(),
                       Utility::LINLIN_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LinLin>::InterpPolicy InverseInterp;
  
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LINLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LinLin, isIndepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LinLin::isIndepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LinLin::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinLin::isIndepVarInValidRange(
				        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LinLin, isDepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LinLin::isDepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LinLin::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinLin::isDepVarInValidRange(
					std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
FRENSIE_UNIT_TEST( LinLin, processIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLin::processIndepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLin::processIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLin::processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LinLin, processDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLin::processDepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLin::processDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLin::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LinLin, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLin::recoverProcessedIndepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLin::recoverProcessedIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLin::recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LinLin, recoverProcessedDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLin::recoverProcessedDepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLin::recoverProcessedDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLin::recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinLin, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LinLin::calculateUnitBaseGridLength( -4.0, -1.0 );
  
  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::LinLin::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LinLin::calculateUnitBaseGridLength( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LinLin::calculateUnitBaseGridLength( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent variable can be calculated
FRENSIE_UNIT_TEST( LinLin, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LinLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LinLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LinLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinLin, calculateIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LinLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;
  
  y = Utility::LinLin::calculateIndepVar( eta, y_min, L );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LinLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinLin, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LinLin::calculateUnitBaseGridLengthProcessed( -4.0, -1.0 );
  
  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::LinLin::calculateUnitBaseGridLengthProcessed( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LinLin::calculateUnitBaseGridLengthProcessed( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LinLin::calculateUnitBaseGridLengthProcessed( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinLin, calculateUnitBaseIndepVarProcessed )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LinLin::calculateUnitBaseIndepVarProcessed( 
								 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LinLin::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LinLin::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinLin, calculateProcessedIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LinLin::calculateProcessedIndepVar( 
							       eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;
  
  y = Utility::LinLin::calculateProcessedIndepVar( eta, y_min, L );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LinLin::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that linear-linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLin, interpolate_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 5.0, y1 = 10.0;

  double y = Utility::LinLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 7.5 );

  x = 0.0;

  y = Utility::LinLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 5.0 );

  x = 1.0;

  y = Utility::LinLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that linear-linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLin, interpolate_raw_beta )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double beta = ( x - x0 )/( x1 - x0 );
  double y0 = 5.0, y1 = 10.0;

  double y = Utility::LinLin::interpolate( beta, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 7.5 );

  x = 0.0;
  beta = ( x - x0 )/( x1 - x0 );

  y = Utility::LinLin::interpolate( beta, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 5.0 );

  x = 1.0;
  beta = ( x - x0 )/( x1 - x0 );

  y = Utility::LinLin::interpolate( beta, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that linear-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinLin, interpolate_processed )
{
  double processed_x0 =
    Utility::LinLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 =
    Utility::LinLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x =
    Utility::LinLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 =
    Utility::LinLinDataProcessing::processDependentVar( 5.0 );
  double processed_y1 =
    Utility::LinLinDataProcessing::processDependentVar( 10.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::LinLin::interpolate( processed_x0,
					   processed_x,
					   processed_y0,
					   processed_slope );

  FRENSIE_CHECK_EQUAL( y, 7.5 );

  processed_x = Utility::LinLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::LinLin::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  FRENSIE_CHECK_EQUAL( y, 5.0 );

  processed_x = Utility::LinLinDataProcessing::processIndependentVar( 1.0 );

  y = Utility::LinLin::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  FRENSIE_CHECK_EQUAL( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLin, interpolateAndProcess_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 5.0, y1 = 10.0;

  double y = Utility::LinLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 7.5 );

  x = 0.0;

  y = Utility::LinLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 5.0 );

  x = 1.0;

  y = Utility::LinLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_EQUAL( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that linear-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinLin, interpolateAndProcess_processed )
{
  double processed_x0 =
    Utility::LinLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 =
    Utility::LinLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x =
    Utility::LinLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 =
    Utility::LinLinDataProcessing::processDependentVar( 5.0 );
  double processed_y1 =
    Utility::LinLinDataProcessing::processDependentVar( 10.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::LinLin::interpolateAndProcess( processed_x0,
						     processed_x,
						     processed_y0,
						     processed_slope );

  FRENSIE_CHECK_EQUAL( y, 7.5 );

  processed_x = Utility::LinLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::LinLin::interpolateAndProcess( processed_x0,
					      processed_x,
					      processed_y0,
					      processed_slope );

  FRENSIE_CHECK_EQUAL( y, 5.0 );

  processed_x = Utility::LinLinDataProcessing::processIndependentVar( 1.0 );

  y = Utility::LinLin::interpolateAndProcess( processed_x0,
					      processed_x,
					      processed_y0,
					      processed_slope );

  FRENSIE_CHECK_EQUAL( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LogLin, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogLin::getInterpolationType(),
                       Utility::LOGLIN_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogLin>::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LINLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogLin, isIndepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LogLin::isIndepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LogLin::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogLin::isIndepVarInValidRange(
				        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogLin, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogLin::isDepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogLin::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogLin::isDepVarInValidRange(
					std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LogLin::isDepVarInValidRange(
					std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( LogLin, processIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LogLin::processIndepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LogLin::processIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LogLin::processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogLin, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
				  Utility::LogLin::processDepVar( 1.0 ),
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogLin, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LogLin::recoverProcessedIndepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LogLin::recoverProcessedIndepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LogLin::recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogLin, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
			  Utility::LogLin::recoverProcessedDepVar( 0.0 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogLin, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogLin::calculateUnitBaseGridLength( -4.0, -1.0 );
  
  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::LogLin::calculateUnitBaseGridLength( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogLin::calculateUnitBaseGridLength( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogLin::calculateUnitBaseGridLength( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogLin, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LogLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LogLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LogLin::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogLin, calculateIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LogLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::LogLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LogLin::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogLin, calculateUnitBaseGridLengthProcessed )
{
  double grid_length =
    Utility::LogLin::calculateUnitBaseGridLengthProcessed( -4.0, -1.0 );
  
  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );

  grid_length =
    Utility::LogLin::calculateUnitBaseGridLengthProcessed( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogLin::calculateUnitBaseGridLengthProcessed( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 1.0 );

  grid_length =
    Utility::LogLin::calculateUnitBaseGridLengthProcessed( 1.0, 4.0 );

  FRENSIE_CHECK_EQUAL( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogLin, calculateUnitBaseIndepVarProcessed )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LogLin::calculateUnitBaseIndepVarProcessed(
								 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LogLin::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LogLin::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogLin, calculateProcessedIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LogLin::calculateProcessedIndepVar(
							       eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;

  y = Utility::LogLin::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LogLin::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LogLin, interpolate_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 0.1, y1 = 10.0;

  double y = Utility::LogLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );

  x = 0.0;

  y = Utility::LogLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.1, 1e-15 );

  x = 1.0;

  y = Utility::LogLin::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogLin, interpolate_processed )
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

  double y = Utility::LogLin::interpolate( processed_x0,
					   processed_x,
					   processed_y0,
					   processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::LogLin::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.1, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 1.0 );

  y = Utility::LogLin::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
FRENSIE_UNIT_TEST( LogLin, interpolateAndProcess_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 0.1, y1 = 10.0;

  double log_y = Utility::LogLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_SMALL( log_y, 1e-15 );

  x = 0.0;

  log_y = Utility::LogLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 0.1 ), 1e-15 );

  x = 1.0;

  log_y = Utility::LogLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogLin, interpolateAndProcess_processed )
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

  double log_y = Utility::LogLin::interpolateAndProcess( processed_x0,
							 processed_x,
							 processed_y0,
							 processed_slope );

  FRENSIE_CHECK_SMALL( log_y, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 0.0 );

  log_y = Utility::LogLin::interpolateAndProcess( processed_x0,
						  processed_x,
						  processed_y0,
						  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 0.1 ), 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 1.0 );

  log_y = Utility::LogLin::interpolateAndProcess( processed_x0,
						  processed_x,
						  processed_y0,
						  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
FRENSIE_UNIT_TEST( LinLog, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LinLog::getInterpolationType(),
                       Utility::LINLOG_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LinLog>::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LinLog, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LinLog::isIndepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LinLog::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinLog::isIndepVarInValidRange(
					std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LinLog::isIndepVarInValidRange(
					std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LinLog, isDepVarInValidRange )
{
  FRENSIE_CHECK( Utility::LinLog::isDepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( Utility::LinLog::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LinLog::isDepVarInValidRange(
				        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check an independent variable can be processed
FRENSIE_UNIT_TEST( LinLog, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
				  Utility::LinLog::processIndepVar( 1.0 ),
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LinLog, processDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLog::processDepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLog::processDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLog::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LinLog, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
			  Utility::LinLog::recoverProcessedIndepVar( 0.0 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LinLog, recoverProcessedDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLog::recoverProcessedDepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLog::recoverProcessedDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLog::recoverProcessedDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinLog, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LinLog::calculateUnitBaseGridLength( 1e-3, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );     
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinLog, calculateUnitBaseIndepVar )
{
  double y_min = 1e-3, y = 1e-2, L = 3.0;

  double eta = Utility::LinLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = 1e-3;

  eta = Utility::LinLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 0.020085536923187;

  eta = Utility::LinLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinLog, calculateIndepVar )
{
  double y_min = 1e-3, L = 3.0, eta = 0.5;

  double y =  Utility::LinLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0044816890703382, 1e-12 );

  eta = 0.0;

  y = Utility::LinLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1e-3, 1e-12 );

  eta = 1.0;

  y = Utility::LinLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.020085536923187, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LinLog, calculateUnitBaseGridLengthProcessed )
{
  double grid_length = Utility::LinLog::calculateUnitBaseGridLengthProcessed(
                                                         std::log(1e-3), std::log(1.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );     
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LinLog, calculateUnitBaseIndepVarProcessed )
{
  double y_min = Utility::LinLog::processIndepVar(1e-3);
  double y = Utility::LinLog::processIndepVar(1e-2);
  double L = 3.0;

  double eta = Utility::LinLog::calculateUnitBaseIndepVarProcessed(
								 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = Utility::LinLog::processIndepVar(1e-3);

  eta = Utility::LinLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = Utility::LinLog::processIndepVar(0.020085536923187);

  eta = Utility::LinLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LinLog, calculateProcessedIndepVar )
{
  double y_min = Utility::LinLog::processIndepVar(1e-3);
  double L = 3.0, eta = 0.5;

  double y =  Utility::LinLog::calculateProcessedIndepVar(
							       eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		 y,
		 Utility::LinLog::processIndepVar(0.0044816890703382),
		 1e-12 );

  eta = 0.0;

  y = Utility::LinLog::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
			  Utility::LinLog::processIndepVar(1e-3),
			  1e-12 );

  eta = 1.0;

  y = Utility::LinLog::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		  y,
		  Utility::LinLog::processIndepVar(0.020085536923187),
		  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLog, interpolate_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  x = 0.1;

  y = Utility::LinLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 10.0;

  y = Utility::LinLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinLog, interpolate_processed )
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

  double y = Utility::LinLog::interpolate( processed_x0,
					   processed_x,
					   processed_y0,
					   processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LinLog::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LinLog::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LinLog, interpolateAndProcess_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  x = 0.1;

  y = Utility::LinLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 10.0;

  y = Utility::LinLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LinLog, interpolateAndProcess_processed )
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

  double y = Utility::LinLog::interpolateAndProcess( processed_x0,
						     processed_x,
						     processed_y0,
						     processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LinLog::interpolateAndProcess( processed_x0,
					      processed_x,
					      processed_y0,
					      processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x =
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LinLog::interpolateAndProcess( processed_x0,
					      processed_x,
					      processed_y0,
					      processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that interpolation type can be returned
FRENSIE_UNIT_TEST( LogLog, getInterpolationType )
{
  FRENSIE_CHECK_EQUAL( Utility::LogLog::getInterpolationType(),
                       Utility::LOGLOG_INTERPOLATION );

  typedef Utility::InverseInterpPolicy<Utility::LogLog>::InterpPolicy InverseInterp;
  FRENSIE_CHECK_EQUAL( InverseInterp::getInterpolationType(),
                       Utility::LOGLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
FRENSIE_UNIT_TEST( LogLog, isIndepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogLog::isIndepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogLog::isIndepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogLog::isIndepVarInValidRange(
					std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LogLog::isIndepVarInValidRange(
					std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
FRENSIE_UNIT_TEST( LogLog, isDepVarInValidRange )
{
  FRENSIE_CHECK( !Utility::LogLog::isDepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  FRENSIE_CHECK( !Utility::LogLog::isDepVarInValidRange( 0.0 ) );
  FRENSIE_CHECK( Utility::LogLog::isDepVarInValidRange(
					std::numeric_limits<double>::min() ) );
  FRENSIE_CHECK( Utility::LogLog::isDepVarInValidRange(
					std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that an independent variable can be processed
FRENSIE_UNIT_TEST( LogLog, processIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
				  Utility::LogLog::processIndepVar( 1.0 ),
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
FRENSIE_UNIT_TEST( LogLog, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.0,
				  Utility::LogLog::processDepVar( 1.0 ),
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
FRENSIE_UNIT_TEST( LogLog, recoverProcessedIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
			  Utility::LogLog::recoverProcessedIndepVar( 0.0 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogLog, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
			  Utility::LogLog::recoverProcessedDepVar( 0.0 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogLog, calculateUnitBaseGridLength )
{
  double grid_length =
    Utility::LogLog::calculateUnitBaseGridLength( 1e-3, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );     
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogLog, calculateUnitBaseIndepVar )
{
  double y_min = 1e-3, y = 1e-2, L = 3.0;

  double eta = Utility::LogLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = 1e-3;

  eta = Utility::LogLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 0.020085536923187;

  eta = Utility::LogLog::calculateUnitBaseIndepVar( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogLog, calculateIndepVar )
{
  double y_min = 1e-3, L = 3.0, eta = 0.5;

  double y =  Utility::LogLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.0044816890703382, 1e-12 );

  eta = 0.0;
  
  y = Utility::LogLog::calculateIndepVar( eta, y_min, L );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1e-3, 1e-12 );

  eta = 1.0;

  y = Utility::LogLog::calculateIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 0.020085536923187, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base grid length can be calculated
FRENSIE_UNIT_TEST( LogLog, calculateUnitBaseGridLengthProcessed )
{
  double grid_length = Utility::LogLog::calculateUnitBaseGridLengthProcessed(
                                                         std::log(1e-3), std::log(1.0) );

  FRENSIE_CHECK_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );     
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
FRENSIE_UNIT_TEST( LogLog, calculateUnitBaseIndepVarProcessed )
{
  double y_min = Utility::LogLog::processIndepVar(1e-3);
  double y = Utility::LogLog::processIndepVar(1e-2);
  double L = 3.0;

  double eta = Utility::LogLog::calculateUnitBaseIndepVarProcessed(
								 y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = Utility::LogLog::processIndepVar(1e-3);

  eta = Utility::LogLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = Utility::LogLog::processIndepVar(0.020085536923187);

  eta = Utility::LogLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
FRENSIE_UNIT_TEST( LogLog, calculateProcessedIndepVar )
{
  double y_min = Utility::LogLog::processIndepVar(1e-3);
  double L = 3.0, eta = 0.5;

  double y = Utility::LogLog::calculateProcessedIndepVar(
							       eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		 y,
		 Utility::LogLog::processIndepVar(0.0044816890703382),
		 1e-12 );

  eta = 0.0;

  y = Utility::LogLog::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY( y,
			  Utility::LogLog::processIndepVar(1e-3),
			  1e-12 );

  eta = 1.0;

  y = Utility::LogLog::calculateProcessedIndepVar( eta, y_min, L );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		  y,
		  Utility::LogLog::processIndepVar(0.020085536923187),
		  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogLog, interpolate_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = 10.0, y1 = 1000.0;

  double y = Utility::LogLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 100.0, 1e-15 );

  x = 0.1;

  y = Utility::LogLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  x = 10.0;

  y = Utility::LogLog::interpolate( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogLog, interpolate_processed )
{
  double processed_x0 =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );
  double processed_x1 =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );
  double processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 );
  double processed_y0 =
    Utility::LogLogDataProcessing::processDependentVar( 10.0 );
  double processed_y1 =
    Utility::LogLogDataProcessing::processDependentVar( 1000.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = Utility::LogLog::interpolate( processed_x0,
					   processed_x,
					   processed_y0,
					   processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 100.0, 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LogLog::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LogLog::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
FRENSIE_UNIT_TEST( LogLog, interpolateAndProcess_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = 10.0, y1 = 1000.0;

  double log_y = Utility::LogLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 100.0 ), 1e-15 );

  x = 0.1;

  log_y = Utility::LogLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );

  x = 10.0;

  log_y = Utility::LogLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
FRENSIE_UNIT_TEST( LogLog, interpolateAndProcess_processed )
{
  double processed_x0 =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );
  double processed_x1 =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );
  double processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 1.0 );
  double processed_y0 =
    Utility::LogLogDataProcessing::processDependentVar( 10.0 );
  double processed_y1 =
    Utility::LogLogDataProcessing::processDependentVar( 1000.0 );

  double processed_slope =
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double log_y = Utility::LogLog::interpolateAndProcess( processed_x0,
							 processed_x,
							 processed_y0,
							 processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 100.0 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  log_y = Utility::LogLog::interpolateAndProcess( processed_x0,
					processed_x,
					processed_y0,
					processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 10.0 ), 1e-15 );

  processed_x =
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  log_y = Utility::LogLog::interpolateAndProcess( processed_x0,
						  processed_x,
						  processed_y0,
						  processed_slope );

  FRENSIE_CHECK_FLOATING_EQUALITY( log_y, std::log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
