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
#include <functional>

// FRENSIE Includes
#include "Utility_TwoDGridGenerator.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_List.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

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
FRENSIE_UNIT_TEST( TwoDGridGenerator, set_verbose_mode )
{
  TestTwoDGridGenerator<Utility::LinLinLin> generator;

  FRENSIE_CHECK( !generator.isVerboseModeOn() );

  generator.setVerboseModeOn();

  FRENSIE_CHECK( generator.isVerboseModeOn() );

  generator.setVerboseModeOff();

  FRENSIE_CHECK( !generator.isVerboseModeOn() );
}

//---------------------------------------------------------------------------//
// Check if exceptions/warnings on dirty convergence can be set
FRENSIE_UNIT_TEST( TwoDGridGenerator, dirty_convergence_handling )
{
  TestTwoDGridGenerator<Utility::LinLinLin> generator;

  FRENSIE_CHECK( !generator.isExceptionThrownOnDirtyConvergence() );

  generator.throwExceptionOnDirtyConvergence();

  FRENSIE_CHECK( generator.isExceptionThrownOnDirtyConvergence() );

  generator.warnOnDirtyConvergence();

  FRENSIE_CHECK( !generator.isExceptionThrownOnDirtyConvergence() );
}

//---------------------------------------------------------------------------//
// Check that the convergence tolerance can be set
FRENSIE_UNIT_TEST( TwoDGridGenerator, setConvergenceTolerance )
{
  TestTwoDGridGenerator<Utility::LinLinLin> generator;

  FRENSIE_CHECK_EQUAL( generator.getConvergenceTolerance(), 0.001 );

  generator.setConvergenceTolerance( 0.0001 );

  FRENSIE_CHECK_EQUAL( generator.getConvergenceTolerance(), 0.0001 );
}

//---------------------------------------------------------------------------//
// Check that the absolute difference tolerance can be set
FRENSIE_UNIT_TEST( TwoDGridGenerator, setAbsoluteDifferenceTolerance )
{
  TestTwoDGridGenerator<Utility::LinLinLin> generator;

  FRENSIE_CHECK_EQUAL( generator.getAbsoluteDifferenceTolerance(), 1e-12 );

  generator.setAbsoluteDifferenceTolerance( 1e-14 );

  FRENSIE_CHECK_EQUAL( generator.getAbsoluteDifferenceTolerance(), 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the distance tolerance can be set
FRENSIE_UNIT_TEST( TwoDGridGenerator, setDistanceTolerance )
{
  TestTwoDGridGenerator<Utility::LinLinLin> generator;

  FRENSIE_CHECK_EQUAL( generator.getDistanceTolerance(), 1e-14 );

  generator.setDistanceTolerance( 1e-16 );

  FRENSIE_CHECK_EQUAL( generator.getDistanceTolerance(), 1e-16 );
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated in place
FRENSIE_UNIT_TEST( TwoDGridGenerator, generateInPlace_linlinlin )
{
  TestTwoDGridGenerator<Utility::LinLinLin> linlinlin_generator;
  linlinlin_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid( 3 );
    primary_grid[0] = 0.0;
    primary_grid[1] = 10.0;
    primary_grid[2] = 20.0;

    linlinlin_generator.generateInPlace( primary_grid, xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );
  }

  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid( 3 );
    primary_grid[0] = 0.0;
    primary_grid[1] = 10.0;
    primary_grid[2] = 20.0;

    linlinlin_generator.generateInPlace( primary_grid, xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );
  }

  // Generate a grid using the std::list
  {
    std::list<double> primary_grid;
    primary_grid.push_back( 0.0 );
    primary_grid.push_back( 10.0 );
    primary_grid.push_back( 20.0 );

    linlinlin_generator.generateInPlace( primary_grid, xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );
  }

  // Generate a grid using the std::deque
  {
    std::deque<double> primary_grid;
    primary_grid.push_back( 0.0 );
    primary_grid.push_back( 10.0 );
    primary_grid.push_back( 20.0 );

    linlinlin_generator.generateInPlace( primary_grid, xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );
  }
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated in place
FRENSIE_UNIT_TEST( TwoDGridGenerator, generateInPlace_loglinlin )
{
  TestTwoDGridGenerator<Utility::LogLinLin> loglinlin_generator;
  loglinlin_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid for the xTimesy function
  std::vector<double> primary_grid( 3 );
  primary_grid[0] = 1e-3;
  primary_grid[1] = 10.0;
  primary_grid[2] = 20.0;

  loglinlin_generator.generateInPlace( primary_grid, xTimesy );

  FRENSIE_CHECK_EQUAL( primary_grid.size(), 1232 );

  // Generate a grid for the x2Plusy2 function
  primary_grid.resize( 3 );
  primary_grid[0] = 1e-3;
  primary_grid[1] = 10.0;
  primary_grid[2] = 20.0;

  loglinlin_generator.generateInPlace( primary_grid, x2Plusy2 );

  FRENSIE_CHECK_EQUAL( primary_grid.size(), 78 );

  // Generate a grid for the norm functor
  primary_grid.resize( 3 );
  primary_grid[0] = 1e-3;
  primary_grid[1] = 10.0;
  primary_grid[2] = 20.0;

  Normal normal( 10.0 );

  loglinlin_generator.setAbsoluteDifferenceTolerance( 1e-90 );
  loglinlin_generator.generateInPlace( primary_grid, normal );

  FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated in place
FRENSIE_UNIT_TEST( TwoDGridGenerator, generateInPlace_logloglog )
{
  TestTwoDGridGenerator<Utility::LogLogLog> logloglog_generator;
  logloglog_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid for the xTimesy function
  std::vector<double> primary_grid( 3 );
  primary_grid[0] = 1e-3;
  primary_grid[1] = 10.0;
  primary_grid[2] = 20.0;

  logloglog_generator.setAbsoluteDifferenceTolerance( 1e-90 );
  logloglog_generator.generateInPlace( primary_grid, xTimesy );

  FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );

  // Generate a grid for the x2Plusy2 function
  primary_grid.resize( 3 );
  primary_grid[0] = 1e-3;
  primary_grid[1] = 10.0;
  primary_grid[2] = 20.0;

  logloglog_generator.setAbsoluteDifferenceTolerance( 1e-90 );
  logloglog_generator.generateInPlace( primary_grid, x2Plusy2 );

  FRENSIE_CHECK_EQUAL( primary_grid.size(), 153 );
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated and evaluated in place
FRENSIE_UNIT_TEST( TwoDGridGenerator, generateAndEvaluateInPlace_linlinlin )
{
  TestTwoDGridGenerator<Utility::LinLinLin> linlinlin_generator;
  linlinlin_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid( 3 );
    primary_grid[0] = 0.0;
    primary_grid[1] = 10.0;
    primary_grid[2] = 20.0;

    std::vector<std::vector<double> >
      secondary_grids, evaluated_function;

    linlinlin_generator.generateAndEvaluateInPlace( primary_grid,
                                                    secondary_grids,
                                                    evaluated_function,
                                                    xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );

    FRENSIE_CHECK_EQUAL( secondary_grids.size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[2].size(), 3 );

    FRENSIE_CHECK_EQUAL( evaluated_function.size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[2].size(), 3 );
  }

  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid( 3 );
    primary_grid[0] = 0.0;
    primary_grid[1] = 10.0;
    primary_grid[2] = 20.0;

    std::vector<std::vector<double> > secondary_grids;
    std::vector<std::vector<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluateInPlace( primary_grid,
                                                    secondary_grids,
                                                    evaluated_function,
                                                    xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );

    FRENSIE_CHECK_EQUAL( secondary_grids.size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[2].size(), 3 );

    FRENSIE_CHECK_EQUAL( evaluated_function.size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[2].size(), 3 );
  }

  // Generate a grid using the std::list
  {
    std::list<double> primary_grid;
    primary_grid.push_back( 0.0 );
    primary_grid.push_back( 10.0 );
    primary_grid.push_back( 20.0 );

    std::vector<std::list<double> > secondary_grids;
    std::list<std::vector<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluateInPlace( primary_grid,
                                                    secondary_grids,
                                                    evaluated_function,
                                                    xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );

    FRENSIE_CHECK_EQUAL( secondary_grids.size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[2].size(), 3 );

    FRENSIE_CHECK_EQUAL( evaluated_function.size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function.front().size(), 3 );
    evaluated_function.pop_front();
    FRENSIE_CHECK_EQUAL( evaluated_function.front().size(), 3 );
    evaluated_function.pop_front();
    FRENSIE_CHECK_EQUAL( evaluated_function.front().size(), 3 );
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

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );

    FRENSIE_CHECK_EQUAL( secondary_grids.size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[2].size(), 3 );

    FRENSIE_CHECK_EQUAL( evaluated_function.size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[2].size(), 3 );
  }
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated
FRENSIE_UNIT_TEST( TwoDGridGenerator, generate_linlinlin )
{
  TestTwoDGridGenerator<Utility::LinLinLin> linlinlin_generator;
  linlinlin_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid, initial_primary_grid( 3 );
    initial_primary_grid[0] = 0.0;
    initial_primary_grid[1] = 10.0;
    initial_primary_grid[2] = 20.0;

    linlinlin_generator.generate( primary_grid,
                                  initial_primary_grid,
                                  xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );
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

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );
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

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );
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

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );
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

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );
  }
}

//---------------------------------------------------------------------------//
// Check that the primary grid can be generated and evaluated
FRENSIE_UNIT_TEST( TwoDGridGenerator, generateAndEvaluate )
{
  TestTwoDGridGenerator<Utility::LinLinLin> linlinlin_generator;
  linlinlin_generator.throwExceptionOnDirtyConvergence();

  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid, initial_primary_grid( 3 );
    initial_primary_grid[0] = 0.0;
    initial_primary_grid[1] = 10.0;
    initial_primary_grid[2] = 20.0;

    std::vector<std::vector<double> >
      secondary_grids, evaluated_function;

    linlinlin_generator.generateAndEvaluate( primary_grid,
                                             secondary_grids,
                                             evaluated_function,
                                             initial_primary_grid,
                                             xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );

    FRENSIE_CHECK_EQUAL( secondary_grids.size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[2].size(), 3 );

    FRENSIE_CHECK_EQUAL( evaluated_function.size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[2].size(), 3 );
  }

  // Generate a grid using the std::vector
  {
    std::vector<double> primary_grid, initial_primary_grid( 3 );
    initial_primary_grid[0] = 0.0;
    initial_primary_grid[1] = 10.0;
    initial_primary_grid[2] = 20.0;

    std::vector<std::vector<double> > secondary_grids;
    std::vector<std::vector<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluate( primary_grid,
                                             secondary_grids,
                                             evaluated_function,
                                             initial_primary_grid,
                                             xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );

    FRENSIE_CHECK_EQUAL( secondary_grids.size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[2].size(), 3 );

    FRENSIE_CHECK_EQUAL( evaluated_function.size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[2].size(), 3 );
  }

  // Generate a grid using the std::list
  {
    std::list<double> primary_grid, initial_primary_grid;
    initial_primary_grid.push_back( 0.0 );
    initial_primary_grid.push_back( 10.0 );
    initial_primary_grid.push_back( 20.0 );

    std::vector<std::list<double> > secondary_grids;
    std::list<std::vector<double> > evaluated_function;

    linlinlin_generator.generateAndEvaluate( primary_grid,
                                             secondary_grids,
                                             evaluated_function,
                                             initial_primary_grid,
                                             xPlusy );

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );

    FRENSIE_CHECK_EQUAL( secondary_grids.size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[2].size(), 3 );

    FRENSIE_CHECK_EQUAL( evaluated_function.size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function.front().size(), 3 );
    evaluated_function.pop_front();
    FRENSIE_CHECK_EQUAL( evaluated_function.front().size(), 3 );
    evaluated_function.pop_front();
    FRENSIE_CHECK_EQUAL( evaluated_function.front().size(), 3 );
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

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );

    FRENSIE_CHECK_EQUAL( secondary_grids.size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[2].size(), 3 );

    FRENSIE_CHECK_EQUAL( evaluated_function.size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[2].size(), 3 );
  }

  // Generate a grid using mix containers
  {
    std::list<double> primary_grid;
    std::deque<double> initial_primary_grid;
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

    FRENSIE_CHECK_EQUAL( primary_grid.size(), 3 );

    FRENSIE_CHECK_EQUAL( secondary_grids.size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( secondary_grids[2].size(), 3 );

    FRENSIE_CHECK_EQUAL( evaluated_function.size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[0].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[1].size(), 3 );
    FRENSIE_CHECK_EQUAL( evaluated_function[2].size(), 3 );
  }
}

//---------------------------------------------------------------------------//
// end tstTwoDGridGenerator.cpp
//---------------------------------------------------------------------------//
