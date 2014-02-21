//---------------------------------------------------------------------------//
//!
//! \file   tstInterpolationPolicy.cpp
//! \author Alex Robinson
//! \brief  Interpolation policy unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "InterpolationPolicy.hpp"
#include "DataProcessingPolicy.hpp"

//---------------------------------------------------------------------------//
// Check that linear-linear interpolation between two points can be done
TEUCHOS_UNIT_TEST( LinLin, interpolate_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 5.0, y1 = 10.0;

  double y = FACEMC::LinLin::interpolate( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 7.5 );

  x = 0.0;

  y = FACEMC::LinLin::interpolate( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 5.0 );

  x = 1.0;
  
  y = FACEMC::LinLin::interpolate( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that linear-linear interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LinLin, interpolate_processed )
{
  double processed_x0 = 
    FACEMC::LinLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 = 
    FACEMC::LinLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x = 
    FACEMC::LinLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 = 
    FACEMC::LinLinDataProcessing::processDependentVar( 5.0 );
  double processed_y1 = 
    FACEMC::LinLinDataProcessing::processDependentVar( 10.0 );

  double processed_slope = 
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = FACEMC::LinLin::interpolate( processed_x0,
					  processed_x,
					  processed_y0,
					  processed_slope );

  TEST_EQUALITY_CONST( y, 7.5 );

  processed_x = FACEMC::LinLinDataProcessing::processIndependentVar( 0.0 );

  y = FACEMC::LinLin::interpolate( processed_x0,
				   processed_x,
				   processed_y0,
				   processed_slope );
  
  TEST_EQUALITY_CONST( y, 5.0 );

  processed_x = FACEMC::LinLinDataProcessing::processIndependentVar( 1.0 );
  
  y = FACEMC::LinLin::interpolate( processed_x0,
				   processed_x,
				   processed_y0,
				   processed_slope );

  TEST_EQUALITY_CONST( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that Log-Linear interpolation between two points can be done
TEUCHOS_UNIT_TEST( LogLin, interpolate_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 0.1, y1 = 10.0;

  double y = FACEMC::LogLin::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
  
  x = 0.0;

  y = FACEMC::LogLin::interpolate( x0, x1, x, y0, y1 );
  
  TEST_FLOATING_EQUALITY( y, 0.1, 1e-15 );

  x = 1.0;

  y = FACEMC::LogLin::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 10.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogLin, interpolate_processed )
{
  double processed_x0 = 
    FACEMC::LogLinDataProcessing::processIndependentVar( 0.0 );
  double processed_x1 = 
    FACEMC::LogLinDataProcessing::processIndependentVar( 1.0 );
  double processed_x = 
    FACEMC::LogLinDataProcessing::processIndependentVar( 0.5 );
  double processed_y0 = 
    FACEMC::LogLinDataProcessing::processDependentVar( 0.1 );
  double processed_y1 = 
    FACEMC::LogLinDataProcessing::processDependentVar( 10.0 );

  double processed_slope = 
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = FACEMC::LogLin::interpolate( processed_x0,
					  processed_x,
					  processed_y0,
					  processed_slope );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );

  processed_x = FACEMC::LogLinDataProcessing::processIndependentVar( 0.0 );

  y = FACEMC::LogLin::interpolate( processed_x0,
				   processed_x,
				   processed_y0,
				   processed_slope );

  TEST_FLOATING_EQUALITY( y, 0.1, 1e-15 );

  processed_x = FACEMC::LogLinDataProcessing::processIndependentVar( 1.0 );

  y = FACEMC::LogLin::interpolate( processed_x0,
				   processed_x,
				   processed_y0,
				   processed_slope );

  TEST_FLOATING_EQUALITY( y, 10.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two points can be done
TEUCHOS_UNIT_TEST( LinLog, interpolate_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = 0.0, y1 = 1.0;

  double y = FACEMC::LinLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  x = 0.1;

  y = FACEMC::LinLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 10.0;

  y = FACEMC::LinLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LinLog, interpolate_processed )
{
  double processed_x0 = 
    FACEMC::LinLogDataProcessing::processIndependentVar( 0.1 );
  double processed_x1 = 
    FACEMC::LinLogDataProcessing::processIndependentVar( 10.0 );
  double processed_x = 
    FACEMC::LinLogDataProcessing::processIndependentVar( 1.0 );
  double processed_y0 = 
    FACEMC::LinLogDataProcessing::processDependentVar( 0.0 );
  double processed_y1 = 
    FACEMC::LinLogDataProcessing::processDependentVar( 1.0 );

  double processed_slope = 
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = FACEMC::LinLog::interpolate( processed_x0,
					  processed_x,
					  processed_y0,
					  processed_slope );

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );
  
  processed_x = 
    FACEMC::LinLogDataProcessing::processIndependentVar( 0.1 );

  y = FACEMC::LinLog::interpolate( processed_x0,
				   processed_x,
				   processed_y0,
				   processed_slope );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x = 
    FACEMC::LinLogDataProcessing::processIndependentVar( 10.0 );

  y = FACEMC::LinLog::interpolate( processed_x0,
				   processed_x,
				   processed_y0,
				   processed_slope );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two points can be done
TEUCHOS_UNIT_TEST( LogLog, interpolate_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = 10.0, y1 = 1000.0;

  double y = FACEMC::LogLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 100.0, 1e-15 );

  x = 0.1;

  y = FACEMC::LogLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  x = 10.0;

  y = FACEMC::LogLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogLog, interpolate_processed )
{
  double processed_x0 = 
    FACEMC::LogLogDataProcessing::processIndependentVar( 0.1 );
  double processed_x1 = 
    FACEMC::LogLogDataProcessing::processIndependentVar( 10.0 );
  double processed_x = 
    FACEMC::LogLogDataProcessing::processIndependentVar( 1.0 );
  double processed_y0 = 
    FACEMC::LogLogDataProcessing::processDependentVar( 10.0 );
  double processed_y1 = 
    FACEMC::LogLogDataProcessing::processDependentVar( 1000.0 );

  double processed_slope = 
    (processed_y1 - processed_y0)/(processed_x1 - processed_x0);

  double y = FACEMC::LogLog::interpolate( processed_x0,
					  processed_x,
					  processed_y0,
					  processed_slope );

  TEST_FLOATING_EQUALITY( y, 100.0, 1e-15 );
  
  processed_x = 
    FACEMC::LogLogDataProcessing::processIndependentVar( 0.1 );

  y = FACEMC::LogLog::interpolate( processed_x0,
				   processed_x,
				   processed_y0,
				   processed_slope );

  TEST_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  processed_x = 
    FACEMC::LogLogDataProcessing::processIndependentVar( 10.0 );

  y = FACEMC::LogLog::interpolate( processed_x0,
				   processed_x,
				   processed_y0,
				   processed_slope );

  TEST_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
