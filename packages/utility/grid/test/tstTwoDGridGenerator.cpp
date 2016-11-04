//---------------------------------------------------------------------------//
//!
//! \file   tstTwoDGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Two-dimensional grid generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <functional>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_TwoDGridGenerator.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_SortAlgorithms.hpp"

//---------------------------------------------------------------------------//
// Testing Classes
//---------------------------------------------------------------------------//
template<typename TwoDInterpPolicy>
class TestTwoDGridGenerator : public Utility::TwoDGridGenerator<TwoDInterpPolicy>
{

public:

  // Constructor
  TestTwoDGridGenerator()
    : Utility::TwoDGridGenerator<TwoDInterpPolicy>()
  { /* ... */ }

  // Destructor
  ~TestTwoDGridGenerator()
  { /* ... */ }

  // Initialize secondary grid at a primary grid point
  void initializeSecondaryGrid( std::vector<double>& secondary_grid,
                                const double primary_grid_point ) const
  {
    secondary_grid.resize( 3 );
    
    secondary_grid[0] = 1.0;
    secondary_grid[1] = 10.0;
    secondary_grid[2] = 20.0;
  }
};

//---------------------------------------------------------------------------//
// Testing Functions/Functors
//---------------------------------------------------------------------------//
double xPlusy( const double x, const double y )
{
  return x+y;
}

double xTimesy( const double x, const double y )
{
  return x*y;
}

double x2Plusy2( const double x, const double y )
{
  return x*x + y*y;
}

struct Normal
{
  Normal( const double peak )
    : d_peak( peak )
  { /* ... */ }

  double operator()( const double x, const double y ) const
  {
    return exp( -(fabs(x-d_peak) + fabs(y-d_peak)) );
  }

private:

  double d_peak;
};

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check if verbose mode can be set
TEUCHOS_UNIT_TEST( TwoDGridGenerator, set_verbose_mode )
{
  TestTwoDGridGenerator<Utility::LinLinLin> generator;

  TEST_ASSERT( !generator.isVerboseModeOn() );

  generator.setVerboseModeOn();

  TEST_ASSERT( generator.isVerboseModeOn() );

  generator.setVerboseModeOff();

  TEST_ASSERT( !generator.isVerboseModeOn() );
}

//---------------------------------------------------------------------------//
// Check if exceptions/warnigs on dirty convergence can be set
TEUCHOS_UNIT_TEST( TwoDGridGenerator, dirty_convergence_handling )
{
  TestTwoDGridGenerator<Utility::LinLinLin> generator;

  TEST_ASSERT( !generator.isExceptionThrownOnDirtyConvergence() );

  generator.throwExceptionOnDirtyConvergence();

  TEST_ASSERT( generator.isExceptionThrownOnDirtyConvergence() );

  generator.warnOnDirtyConvergence();

  TEST_ASSERT( !generator.isExceptionThrownOnDirtyConvergence() );
}

//---------------------------------------------------------------------------//
// Check that the convergence tolerance can be set
TEUCHOS_UNIT_TEST( TwoDGridGenerator, setConvergenceTolerance )
{
  TestTwoDGridGenerator<Utility::LinLinLin> generator;

  TEST_EQUALITY_CONST( generator.getConvergenceTolerance(), 0.001 );

  generator.setConvergenceTolerance( 0.0001 );

  TEST_EQUALITY_CONST( generator.getConvergenceTolerance(), 0.0001 );
}

//---------------------------------------------------------------------------//
// Check that the absolute difference tolerance can be set
TEUCHOS_UNIT_TEST( TwoDGridGenerator, setAbsoluteDifferenceTolerance )
{
  TestTwoDGridGenerator<Utility::LinLinLin> generator;

  TEST_EQUALITY_CONST( generator.getAbsoluteDifferenceTolerance(), 1e-12 );

  generator.setAbsoluteDifferenceTolerance( 1e-14 );

  TEST_EQUALITY_CONST( generator.getAbsoluteDifferenceTolerance(), 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the distance tolerance can be set
TEUCHOS_UNIT_TEST( TwoDGridGenerator, setDistanceTolerance )
{
  TestTwoDGridGenerator<Utility::LinLinLin> generator;

  TEST_EQUALITY_CONST( generator.getDistanceTolerance(), 1e-14 );

  generator.setDistanceTolerance( 1e-16 );

  TEST_EQUALITY_CONST( generator.getDistanceTolerance(), 1e-16 );
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated in place
TEUCHOS_UNIT_TEST( TwoDGridGenerator, generateInPlace_linlinlin )
{
  TestTwoDGridGenerator<Utility::LinLinLin> linlinlin_generator;
  linlinlin_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid using the Teuchos::Array
  {
    Teuchos::Array<double> primary_grid( 3 );
    primary_grid[0] = 0.0;
    primary_grid[1] = 10.0;
    primary_grid[2] = 20.0;
    
    linlinlin_generator.generateInPlace( primary_grid, xPlusy );
    
    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
  }

  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid( 3 );
    primary_grid[0] = 0.0;
    primary_grid[1] = 10.0;
    primary_grid[2] = 20.0;

    linlinlin_generator.generateInPlace( primary_grid, xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
  }

  // Generate a grid using the std::list
  {
    std::list<double> primary_grid;
    primary_grid.push_back( 0.0 );
    primary_grid.push_back( 10.0 );
    primary_grid.push_back( 20.0 );

    linlinlin_generator.generateInPlace( primary_grid, xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
  }

  // Generate a grid using the std::deque
  {
    std::deque<double> primary_grid;
    primary_grid.push_back( 0.0 );
    primary_grid.push_back( 10.0 );
    primary_grid.push_back( 20.0 );

    linlinlin_generator.generateInPlace( primary_grid, xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
  }
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated in place
TEUCHOS_UNIT_TEST( TwoDGridGenerator, generateInPlace_loglinlin )
{
  TestTwoDGridGenerator<Utility::LogLinLin> loglinlin_generator;
  loglinlin_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid for the xTimesy function
  Teuchos::Array<double> primary_grid( 3 );
  primary_grid[0] = 1e-3;
  primary_grid[1] = 10.0;
  primary_grid[2] = 20.0;

  loglinlin_generator.generateInPlace( primary_grid, xTimesy );

  TEST_EQUALITY_CONST( primary_grid.size(), 1232 );

  // Generate a grid for the x2Plusy2 function
  primary_grid.resize( 3 );
  primary_grid[0] = 1e-3;
  primary_grid[1] = 10.0;
  primary_grid[2] = 20.0;
  
  loglinlin_generator.generateInPlace( primary_grid, x2Plusy2 );

  TEST_EQUALITY_CONST( primary_grid.size(), 78 );

  // Generate a grid for the norm functor
  primary_grid.resize( 3 );
  primary_grid[0] = 1e-3;
  primary_grid[1] = 10.0;
  primary_grid[2] = 20.0;
  
  Normal normal( 10.0 );

  loglinlin_generator.setAbsoluteDifferenceTolerance( 1e-90 );
  loglinlin_generator.generateInPlace( primary_grid, normal );

  TEST_EQUALITY_CONST( primary_grid.size(), 3 );
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated in place
TEUCHOS_UNIT_TEST( TwoDGridGenerator, generateInPlace_logloglog )
{
  TestTwoDGridGenerator<Utility::LogLogLog> logloglog_generator;
  logloglog_generator.throwExceptionOnDirtyConvergence();
  
  // Generate a grid for the xTimesy function
  Teuchos::Array<double> primary_grid( 3 );
  primary_grid[0] = 1e-3;
  primary_grid[1] = 10.0;
  primary_grid[2] = 20.0;
  
  logloglog_generator.setAbsoluteDifferenceTolerance( 1e-90 );
  logloglog_generator.generateInPlace( primary_grid, xTimesy );

  TEST_EQUALITY_CONST( primary_grid.size(), 3 );

  // Generate a grid for the x2Plusy2 function
  primary_grid.resize( 3 );
  primary_grid[0] = 1e-3;
  primary_grid[1] = 10.0;
  primary_grid[2] = 20.0;

  logloglog_generator.setAbsoluteDifferenceTolerance( 1e-90 );
  logloglog_generator.generateInPlace( primary_grid, x2Plusy2 );

  TEST_EQUALITY_CONST( primary_grid.size(), 153 );
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated and evaluated in place
TEUCHOS_UNIT_TEST( TwoDGridGenerator, generateAndEvaluateInPlace_linlinlin )
{
  TestTwoDGridGenerator<Utility::LinLinLin> linlinlin_generator;
  linlinlin_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid using the Teuchos::Array
  {
    std::vector<double> primary_grid( 3 );
    primary_grid[0] = 0.0;
    primary_grid[1] = 10.0;
    primary_grid[2] = 20.0;

    Teuchos::Array<Teuchos::Array<double> >
      secondary_grids, evaluated_function;
    
    linlinlin_generator.generateAndEvaluateInPlace( primary_grid,
                                                    secondary_grids,
                                                    evaluated_function,
                                                    xPlusy );
    
    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
    
    TEST_EQUALITY_CONST( secondary_grids.size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[0].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[1].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[2].size(), 3 );
    
    TEST_EQUALITY_CONST( evaluated_function.size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[0].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[1].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[2].size(), 3 );
  }
  
  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid( 3 );
    primary_grid[0] = 0.0;
    primary_grid[1] = 10.0;
    primary_grid[2] = 20.0;

    std::vector<Teuchos::Array<double> > secondary_grids;
    Teuchos::Array<std::vector<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluateInPlace( primary_grid,
                                                    secondary_grids,
                                                    evaluated_function,
                                                    xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
    
    TEST_EQUALITY_CONST( secondary_grids.size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[0].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[1].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[2].size(), 3 );
    
    TEST_EQUALITY_CONST( evaluated_function.size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[0].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[1].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[2].size(), 3 );
  }

  // Generate a grid using the std::list
  {
    std::list<double> primary_grid;
    primary_grid.push_back( 0.0 );
    primary_grid.push_back( 10.0 );
    primary_grid.push_back( 20.0 );

    Teuchos::Array<std::list<double> > secondary_grids;
    std::list<std::vector<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluateInPlace( primary_grid,
                                                    secondary_grids,
                                                    evaluated_function,
                                                    xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
    
    TEST_EQUALITY_CONST( secondary_grids.size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[0].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[1].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[2].size(), 3 );
    
    TEST_EQUALITY_CONST( evaluated_function.size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function.front().size(), 3 );
    evaluated_function.pop_front();
    TEST_EQUALITY_CONST( evaluated_function.front().size(), 3 );
    evaluated_function.pop_front();
    TEST_EQUALITY_CONST( evaluated_function.front().size(), 3 );
  }

  // Generate a grid using the std::deque
  {
    std::deque<double> primary_grid;
    primary_grid.push_back( 0.0 );
    primary_grid.push_back( 10.0 );
    primary_grid.push_back( 20.0 );

    std::vector<std::deque<double> > secondary_grids;
    std::deque<std::list<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluateInPlace( primary_grid,
                                                    secondary_grids,
                                                    evaluated_function,
                                                    xPlusy );
    
    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
    
    TEST_EQUALITY_CONST( secondary_grids.size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[0].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[1].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[2].size(), 3 );
    
    TEST_EQUALITY_CONST( evaluated_function.size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[0].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[1].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[2].size(), 3 );
  }
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated
TEUCHOS_UNIT_TEST( TwoDGridGenerator, generate_linlinlin )
{
  TestTwoDGridGenerator<Utility::LinLinLin> linlinlin_generator;
  linlinlin_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid using the Teuchos::Array
  {
    Teuchos::Array<double> primary_grid, initial_primary_grid( 3 );
    initial_primary_grid[0] = 0.0;
    initial_primary_grid[1] = 10.0;
    initial_primary_grid[2] = 20.0;
    
    linlinlin_generator.generate( primary_grid,
                                  initial_primary_grid,
                                  xPlusy );
    
    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
  }

  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid, initial_primary_grid( 3 );
    initial_primary_grid[0] = 0.0;
    initial_primary_grid[1] = 10.0;
    initial_primary_grid[2] = 20.0;

    linlinlin_generator.generate( primary_grid,
                                  initial_primary_grid,
                                  xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
  }

  // Generate a grid using the std::list
  {
    std::list<double> primary_grid, initial_primary_grid;
    initial_primary_grid.push_back( 0.0 );
    initial_primary_grid.push_back( 10.0 );
    initial_primary_grid.push_back( 20.0 );

    linlinlin_generator.generate( primary_grid,
                                  initial_primary_grid,
                                  xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
  }

  // Generate a grid using the std::deque
  {
    std::deque<double> primary_grid, initial_primary_grid;
    initial_primary_grid.push_back( 0.0 );
    initial_primary_grid.push_back( 10.0 );
    initial_primary_grid.push_back( 20.0 );

    linlinlin_generator.generate( primary_grid,
                                  initial_primary_grid,
                                  xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
  }

  // Generate a grid using mixed containers
  {
    std::vector<double> primary_grid;
    std::list<double> initial_primary_grid;
    initial_primary_grid.push_back( 0.0 );
    initial_primary_grid.push_back( 10.0 );
    initial_primary_grid.push_back( 20.0 );

    linlinlin_generator.generate( primary_grid,
                                  initial_primary_grid,
                                  xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
  }
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated and evaluated
TEUCHOS_UNIT_TEST( TwoDGridGenerator, generateAndEvaluate )
{
  TestTwoDGridGenerator<Utility::LinLinLin> linlinlin_generator;
  linlinlin_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid using the Teuchos::Array
  {
    Teuchos::Array<double> primary_grid, initial_primary_grid( 3 );
    initial_primary_grid[0] = 0.0;
    initial_primary_grid[1] = 10.0;
    initial_primary_grid[2] = 20.0;

    Teuchos::Array<Teuchos::Array<double> >
      secondary_grids, evaluated_function;
    
    linlinlin_generator.generateAndEvaluate( primary_grid,
                                             secondary_grids,
                                             evaluated_function,
                                             initial_primary_grid,
                                             xPlusy );
    
    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
    
    TEST_EQUALITY_CONST( secondary_grids.size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[0].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[1].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[2].size(), 3 );
    
    TEST_EQUALITY_CONST( evaluated_function.size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[0].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[1].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[2].size(), 3 );
  }
  
  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid, initial_primary_grid( 3 );
    initial_primary_grid[0] = 0.0;
    initial_primary_grid[1] = 10.0;
    initial_primary_grid[2] = 20.0;

    std::vector<Teuchos::Array<double> > secondary_grids;
    Teuchos::Array<std::vector<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluate( primary_grid,
                                             secondary_grids,
                                             evaluated_function,
                                             initial_primary_grid,
                                             xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
    
    TEST_EQUALITY_CONST( secondary_grids.size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[0].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[1].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[2].size(), 3 );
    
    TEST_EQUALITY_CONST( evaluated_function.size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[0].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[1].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[2].size(), 3 );
  }

  // Generate a grid using the std::list
  {
    std::list<double> primary_grid, initial_primary_grid;
    initial_primary_grid.push_back( 0.0 );
    initial_primary_grid.push_back( 10.0 );
    initial_primary_grid.push_back( 20.0 );

    Teuchos::Array<std::list<double> > secondary_grids;
    std::list<std::vector<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluate( primary_grid,
                                             secondary_grids,
                                             evaluated_function,
                                             initial_primary_grid,
                                             xPlusy );

    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
    
    TEST_EQUALITY_CONST( secondary_grids.size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[0].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[1].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[2].size(), 3 );
    
    TEST_EQUALITY_CONST( evaluated_function.size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function.front().size(), 3 );
    evaluated_function.pop_front();
    TEST_EQUALITY_CONST( evaluated_function.front().size(), 3 );
    evaluated_function.pop_front();
    TEST_EQUALITY_CONST( evaluated_function.front().size(), 3 );
  }

  // Generate a grid using the std::deque
  {
    std::deque<double> primary_grid, initial_primary_grid;
    initial_primary_grid.push_back( 0.0 );
    initial_primary_grid.push_back( 10.0 );
    initial_primary_grid.push_back( 20.0 );
    
    std::vector<std::deque<double> > secondary_grids;
    std::deque<std::list<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluate( primary_grid,
                                             secondary_grids,
                                             evaluated_function,
                                             initial_primary_grid,
                                             xPlusy );
    
    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
    
    TEST_EQUALITY_CONST( secondary_grids.size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[0].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[1].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[2].size(), 3 );
    
    TEST_EQUALITY_CONST( evaluated_function.size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[0].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[1].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[2].size(), 3 );
  }

  // Generate a grid using mix containers
  {
    std::list<double> primary_grid;
    std::deque<double> initial_primary_grid;
    initial_primary_grid.push_back( 0.0 );
    initial_primary_grid.push_back( 10.0 );
    initial_primary_grid.push_back( 20.0 );
    
    Teuchos::Array<std::deque<double> > secondary_grids;
    std::deque<std::list<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluate( primary_grid,
                                             secondary_grids,
                                             evaluated_function,
                                             initial_primary_grid,
                                             xPlusy );
    
    TEST_EQUALITY_CONST( primary_grid.size(), 3 );
    
    TEST_EQUALITY_CONST( secondary_grids.size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[0].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[1].size(), 3 );
    TEST_EQUALITY_CONST( secondary_grids[2].size(), 3 );
    
    TEST_EQUALITY_CONST( evaluated_function.size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[0].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[1].size(), 3 );
    TEST_EQUALITY_CONST( evaluated_function[2].size(), 3 );
  }
}

//---------------------------------------------------------------------------//
// end tstTwoDGridGenerator.cpp
//---------------------------------------------------------------------------//
