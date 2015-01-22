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

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_DataProcessingPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that linear-linear interpolation between two points can be done
TEUCHOS_UNIT_TEST( LinLin, interpolate_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 5.0, y1 = 10.0;

  double y = Utility::LinLin::interpolate( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 7.5 );

  x = 0.0;

  y = Utility::LinLin::interpolate( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 5.0 );

  x = 1.0;
  
  y = Utility::LinLin::interpolate( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that linear-linear interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LinLin, interpolate_processed )
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

  TEST_EQUALITY_CONST( y, 7.5 );

  processed_x = Utility::LinLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::LinLin::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );
  
  TEST_EQUALITY_CONST( y, 5.0 );

  processed_x = Utility::LinLinDataProcessing::processIndependentVar( 1.0 );
  
  y = Utility::LinLin::interpolate( processed_x0,
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

  double y = Utility::LogLin::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
  
  x = 0.0;

  y = Utility::LogLin::interpolate( x0, x1, x, y0, y1 );
  
  TEST_FLOATING_EQUALITY( y, 0.1, 1e-15 );

  x = 1.0;

  y = Utility::LogLin::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 10.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogLin, interpolate_processed )
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

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::LogLin::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  TEST_FLOATING_EQUALITY( y, 0.1, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 1.0 );

  y = Utility::LogLin::interpolate( processed_x0,
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

  double y = Utility::LinLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  x = 0.1;

  y = Utility::LinLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 10.0;

  y = Utility::LinLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LinLog, interpolate_processed )
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

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );
  
  processed_x = 
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LinLog::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x = 
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LinLog::interpolate( processed_x0,
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

  double y = Utility::LogLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 100.0, 1e-15 );

  x = 0.1;

  y = Utility::LogLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  x = 10.0;

  y = Utility::LogLog::interpolate( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogLog, interpolate_processed )
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

  TEST_FLOATING_EQUALITY( y, 100.0, 1e-15 );
  
  processed_x = 
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LogLog::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  TEST_FLOATING_EQUALITY( y, 10.0, 1e-15 );

  processed_x = 
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LogLog::interpolate( processed_x0,
				    processed_x,
				    processed_y0,
				    processed_slope );

  TEST_FLOATING_EQUALITY( y, 1000.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
