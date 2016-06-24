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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_DataProcessingPolicy.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
TEUCHOS_UNIT_TEST( LinLin, getInterpolationType )
{
  TEST_EQUALITY_CONST( Utility::LinLin::getInterpolationType(),
                       Utility::LINLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( LinLin, isIndepVarInValidRange )
{
  TEST_ASSERT( Utility::LinLin::isIndepVarInValidRange( 
				       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( Utility::LinLin::isIndepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LinLin::isIndepVarInValidRange( 
				        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
TEUCHOS_UNIT_TEST( LinLin, isDepVarInValidRange )
{
  TEST_ASSERT( Utility::LinLin::isDepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( Utility::LinLin::isDepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LinLin::isDepVarInValidRange( 
					std::numeric_limits<double>::max() ) );
}
 
//---------------------------------------------------------------------------//
// Check an independent variable can be processed
TEUCHOS_UNIT_TEST( LinLin, processIndepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLin::processIndepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLin::processIndepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLin::processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
TEUCHOS_UNIT_TEST( LinLin, processDepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLin::processDepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLin::processDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLin::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
TEUCHOS_UNIT_TEST( LinLin, recoverProcessedIndepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLin::recoverProcessedIndepVar(-1.0) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLin::recoverProcessedIndepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLin::recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LinLin, recoverProcessedDepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLin::recoverProcessedDepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLin::recoverProcessedDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLin::recoverProcessedDepVar( 1.0 ) );
}

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
// Check that Linear-Linear interpolation between two points can be done
TEUCHOS_UNIT_TEST( LinLin, interpolateAndProcess_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 5.0, y1 = 10.0;

  double y = Utility::LinLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 7.5 );

  x = 0.0;

  y = Utility::LinLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 5.0 );

  x = 1.0;
  
  y = Utility::LinLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_EQUALITY_CONST( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that linear-linear interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LinLin, interpolateAndProcess_processed )
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

  TEST_EQUALITY_CONST( y, 7.5 );

  processed_x = Utility::LinLinDataProcessing::processIndependentVar( 0.0 );

  y = Utility::LinLin::interpolateAndProcess( processed_x0,
					      processed_x,
					      processed_y0,
					      processed_slope );
  
  TEST_EQUALITY_CONST( y, 5.0 );

  processed_x = Utility::LinLinDataProcessing::processIndependentVar( 1.0 );
  
  y = Utility::LinLin::interpolateAndProcess( processed_x0,
					      processed_x,
					      processed_y0,
					      processed_slope );

  TEST_EQUALITY_CONST( y, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
TEUCHOS_UNIT_TEST( LogLin, getInterpolationType )
{
  TEST_EQUALITY_CONST( Utility::LogLin::getInterpolationType(),
                       Utility::LOGLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( LogLin, isIndepVarInValidRange )
{
  TEST_ASSERT( Utility::LogLin::isIndepVarInValidRange( 
				       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( Utility::LogLin::isIndepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LogLin::isIndepVarInValidRange( 
				        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
TEUCHOS_UNIT_TEST( LogLin, isDepVarInValidRange )
{
  TEST_ASSERT( !Utility::LogLin::isDepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( !Utility::LogLin::isDepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LogLin::isDepVarInValidRange( 
					std::numeric_limits<double>::min() ) );
  TEST_ASSERT( Utility::LogLin::isDepVarInValidRange( 
					std::numeric_limits<double>::max() ) );
}
 
//---------------------------------------------------------------------------//
// Check an independent variable can be processed
TEUCHOS_UNIT_TEST( LogLin, processIndepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LogLin::processIndepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, Utility::LogLin::processIndepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LogLin::processIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
TEUCHOS_UNIT_TEST( LogLin, processDepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( 0.0, 
				  Utility::LogLin::processDepVar( 1.0 ),
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
TEUCHOS_UNIT_TEST( LogLin, recoverProcessedIndepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LogLin::recoverProcessedIndepVar(-1.0) );
  TEST_EQUALITY_CONST( 0.0, Utility::LogLin::recoverProcessedIndepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LogLin::recoverProcessedIndepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LogLin, recoverProcessedDepVar )
{
  TEST_FLOATING_EQUALITY( 1.0, 
			  Utility::LogLin::recoverProcessedDepVar( 0.0 ),
			  1e-15 );
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
// Check that Log-Linear interpolation between two points can be done
TEUCHOS_UNIT_TEST( LogLin, interpolateAndProcess_raw )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0 = 0.1, y1 = 10.0;

  double log_y = Utility::LogLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  UTILITY_TEST_FLOATING_EQUALITY( log_y, 0.0, 1e-15 );
  
  x = 0.0;

  log_y = Utility::LogLin::interpolateAndProcess( x0, x1, x, y0, y1 );
  
  TEST_FLOATING_EQUALITY( log_y, log( 0.1 ), 1e-15 );

  x = 1.0;

  log_y = Utility::LogLin::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 10.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that log-linear interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogLin, interpolateAndProcess_processed )
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

  UTILITY_TEST_FLOATING_EQUALITY( log_y, 0.0, 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 0.0 );

  log_y = Utility::LogLin::interpolateAndProcess( processed_x0,
						  processed_x,
						  processed_y0,
						  processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 0.1 ), 1e-15 );

  processed_x = Utility::LogLinDataProcessing::processIndependentVar( 1.0 );

  log_y = Utility::LogLin::interpolateAndProcess( processed_x0,
						  processed_x,
						  processed_y0,
						  processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 10.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interpolation type can be returned
TEUCHOS_UNIT_TEST( LinLog, getInterpolationType )
{
  TEST_EQUALITY_CONST( Utility::LinLog::getInterpolationType(),
                       Utility::LINLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( LinLog, isIndepVarInValidRange )
{
  TEST_ASSERT( !Utility::LinLog::isIndepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( !Utility::LinLog::isIndepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LinLog::isIndepVarInValidRange( 
					std::numeric_limits<double>::min() ) );
  TEST_ASSERT( Utility::LinLog::isIndepVarInValidRange( 
					std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
TEUCHOS_UNIT_TEST( LinLog, isDepVarInValidRange )
{
  TEST_ASSERT( Utility::LinLog::isDepVarInValidRange( 
				       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( Utility::LinLog::isDepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LinLog::isDepVarInValidRange( 
				        std::numeric_limits<double>::max() ) );
}
 
//---------------------------------------------------------------------------//
// Check an independent variable can be processed
TEUCHOS_UNIT_TEST( LinLog, processIndepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( 0.0, 
				  Utility::LinLog::processIndepVar( 1.0 ),
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
TEUCHOS_UNIT_TEST( LinLog, processDepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLog::processDepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLog::processDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLog::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
TEUCHOS_UNIT_TEST( LinLog, recoverProcessedIndepVar )
{
  TEST_FLOATING_EQUALITY( 1.0, 
			  Utility::LinLog::recoverProcessedIndepVar( 0.0 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LinLog, recoverProcessedDepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLog::recoverProcessedDepVar(-1.0) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLog::recoverProcessedDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLog::recoverProcessedDepVar( 1.0 ) );
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
// Check that Linear-Log interpolation between two points can be done
TEUCHOS_UNIT_TEST( LinLog, interpolateAndProcess_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = 0.0, y1 = 1.0;

  double y = Utility::LinLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );

  x = 0.1;

  y = Utility::LinLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  x = 10.0;

  y = Utility::LinLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Linear-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LinLog, interpolateAndProcess_processed )
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

  TEST_FLOATING_EQUALITY( y, 0.5, 1e-15 );
  
  processed_x = 
    Utility::LinLogDataProcessing::processIndependentVar( 0.1 );

  y = Utility::LinLog::interpolateAndProcess( processed_x0,
					      processed_x,
					      processed_y0,
					      processed_slope );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  processed_x = 
    Utility::LinLogDataProcessing::processIndependentVar( 10.0 );

  y = Utility::LinLog::interpolateAndProcess( processed_x0,
					      processed_x,
					      processed_y0,
					      processed_slope );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that interpolation type can be returned
TEUCHOS_UNIT_TEST( LogLog, getInterpolationType )
{
  TEST_EQUALITY_CONST( Utility::LogLog::getInterpolationType(),
                       Utility::LOGLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( LogLog, isIndepVarInValidRange )
{
  TEST_ASSERT( !Utility::LogLog::isIndepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( !Utility::LogLog::isIndepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LogLog::isIndepVarInValidRange( 
					std::numeric_limits<double>::min() ) );
  TEST_ASSERT( Utility::LogLog::isIndepVarInValidRange( 
					std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of a dependent variable can be tested
TEUCHOS_UNIT_TEST( LogLog, isDepVarInValidRange )
{
  TEST_ASSERT( !Utility::LogLog::isDepVarInValidRange(
				       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( !Utility::LogLog::isDepVarInValidRange( 0.0 ) );
  TEST_ASSERT( Utility::LogLog::isDepVarInValidRange( 
					std::numeric_limits<double>::min() ) );
  TEST_ASSERT( Utility::LogLog::isDepVarInValidRange( 
					std::numeric_limits<double>::max() ) );
}
 
//---------------------------------------------------------------------------//
// Check an independent variable can be processed
TEUCHOS_UNIT_TEST( LogLog, processIndepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( 0.0, 
				  Utility::LogLog::processIndepVar( 1.0 ),
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a dependent variable can be processed
TEUCHOS_UNIT_TEST( LogLog, processDepVar )
{
  UTILITY_TEST_FLOATING_EQUALITY( 0.0, 
				  Utility::LogLog::processDepVar( 1.0 ),
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed independent variable can be recovered
TEUCHOS_UNIT_TEST( LogLog, recoverProcessedIndepVar )
{
  TEST_FLOATING_EQUALITY( 1.0, 
			  Utility::LogLog::recoverProcessedIndepVar( 0.0 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LogLog, recoverProcessedDepVar )
{
  TEST_FLOATING_EQUALITY( 1.0, 
			  Utility::LogLog::recoverProcessedDepVar( 0.0 ),
			  1e-15 );
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
// Check that Log-Log interpolation between two points can be done
TEUCHOS_UNIT_TEST( LogLog, interpolateAndProcess_raw )
{
  double x0 = 0.1, x1 = 10.0, x = 1.0;
  double y0 = 10.0, y1 = 1000.0;

  double log_y = Utility::LogLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 100.0 ), 1e-15 );

  x = 0.1;

  log_y = Utility::LogLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 10.0 ), 1e-15 );

  x = 10.0;

  log_y = Utility::LogLog::interpolateAndProcess( x0, x1, x, y0, y1 );

  TEST_FLOATING_EQUALITY( log_y, log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that Log-Log interpolation between two processed points can be
// done
TEUCHOS_UNIT_TEST( LogLog, interpolateAndProcess_processed )
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

  TEST_FLOATING_EQUALITY( log_y, log( 100.0 ), 1e-15 );
  
  processed_x = 
    Utility::LogLogDataProcessing::processIndependentVar( 0.1 );

  log_y = Utility::LogLog::interpolateAndProcess( processed_x0,
					processed_x,
					processed_y0,
					processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 10.0 ), 1e-15 );

  processed_x = 
    Utility::LogLogDataProcessing::processIndependentVar( 10.0 );

  log_y = Utility::LogLog::interpolateAndProcess( processed_x0,
						  processed_x,
						  processed_y0,
						  processed_slope );

  TEST_FLOATING_EQUALITY( log_y, log( 1000.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
