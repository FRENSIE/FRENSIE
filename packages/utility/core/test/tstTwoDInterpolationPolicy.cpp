//---------------------------------------------------------------------------//
//!
//! \file   tstTwoDInterpolationPolicy.cpp
//! \author Alex Robinson
//! \brief  2D interpolation policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the linear-linear-linear interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LinLinLin, interpolate_raw_separate_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.0;
  Teuchos::Array<Utility::Pair<double,double> > y_0_grid( 4 );
  y_0_grid[0].first = -10.0;
  y_0_grid[1].first = -1.0;
  y_0_grid[2].first = 1.0;
  y_0_grid[3].first = 10.0;

  Teuchos::Array<Utility::Pair<double,double> > z_0_grid( 4 );
  z_0_grid[0].second = 100.0;
  z_0_grid[1].second = 0.0;
  z_0_grid[2].second = 1.0;
  z_0_grid[3].second = 10.0;

  Teuchos::Array<Utility::Pair<double,double> > y_1_grid( 3 );
  y_1_grid[0].first = -10.0;
  y_1_grid[1].first = -5.0;
  y_1_grid[2].first = 10.0;

  Teuchos::Array<Utility::Pair<double,double> > z_1_grid( 3 );
  z_1_grid[0].second = 50.0;
  z_1_grid[1].second = 10.0;
  z_1_grid[2].second = 5.0;

  double z = Utility::LinLinLin::interpolate<Utility::FIRST,Utility::SECOND>(
							      x0,
							      x1,
							      x,
							      y,
							      y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 4.4166666666667, 1e-12 );

  x = 0.0;

  z = Utility::LinLinLin::interpolate<Utility::FIRST,Utility::SECOND>(
							      x0,
							      x1,
							      x,
							      y,
							      y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.5, 1e-12 );

  x = 1.0;
  
  z = Utility::LinLinLin::interpolate<Utility::FIRST,Utility::SECOND>(
							      x0,
							      x1,
							      x,
							      y,
							      y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 8.3333333333333, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-linear-linear interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LinLinLin, interpolate_raw_combined_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.0;
  Teuchos::Array<Utility::Pair<double,double> > grid_0( 4 );
  grid_0[0]( -10.0, 100.0 );
  grid_0[1]( -1.0, 0.0 );
  grid_0[2]( 1.0, 1.0 );
  grid_0[3]( 10.0, 10.0 );

  Teuchos::Array<Utility::Pair<double,double> > grid_1( 3 );
  grid_1[0]( -10.0, 50.0 );
  grid_1[1]( -5.0, 10.0 );
  grid_1[2]( 10.0, 5.0 );

  double z = Utility::LinLinLin::interpolate<Utility::FIRST,Utility::SECOND>(
							      x0,
							      x1,
							      x,
							      y,
							      grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 4.4166666666667, 1e-12 );

  x = 0.0;

  z = Utility::LinLinLin::interpolate<Utility::FIRST,Utility::SECOND>(
							      x0,
							      x1,
							      x,
							      y,
							      grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 0.5, 1e-12 );

  x = 1.0;
  
  z = Utility::LinLinLin::interpolate<Utility::FIRST,Utility::SECOND>(
							      x0,
							      x1,
							      x,
							      y,
							      grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 8.3333333333333, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-linear-linear interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LinLinLin, interpolate_raw_no_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.0;
  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[0] = -10.0;
  y_0_grid[1] = -1.0;
  y_0_grid[2] = 1.0;
  y_0_grid[3] = 10.0;

  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[0] = 100.0;
  z_0_grid[1] = 0.0;
  z_0_grid[2] = 1.0;
  z_0_grid[3] = 10.0;

  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[0] = -10.0;
  y_1_grid[1] = -5.0;
  y_1_grid[2] = 10.0;

  Teuchos::Array<double> z_1_grid( 3 );
  z_1_grid[0] = 50.0;
  z_1_grid[1] = 10.0;
  z_1_grid[2] = 5.0;

  double z = Utility::LinLinLin::interpolate( x0,
					      x1,
					      x,
					      y,
					      y_0_grid.begin(),
					      y_0_grid.end(),
					      z_0_grid.begin(),
					      z_0_grid.end(),
					      y_1_grid.begin(),
					      y_1_grid.end(),
					      z_1_grid.begin(),
					      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 4.4166666666667, 1e-12 );

  x = 0.0;

  z = Utility::LinLinLin::interpolate( x0,
				       x1,
				       x,
				       y,
				       y_0_grid.begin(),
				       y_0_grid.end(),
				       z_0_grid.begin(),
				       z_0_grid.end(),
				       y_1_grid.begin(),
				       y_1_grid.end(),
				       z_1_grid.begin(),
				       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.5, 1e-12 );

  x = 1.0;
  
  z = Utility::LinLinLin::interpolate( x0,
				       x1,
				       x,
				       y,
				       y_0_grid.begin(),
				       y_0_grid.end(),
				       z_0_grid.begin(),
				       z_0_grid.end(),
				       y_1_grid.begin(),
				       y_1_grid.end(),
				       z_1_grid.begin(),
				       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 8.3333333333333, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid length can be calculated
TEUCHOS_UNIT_TEST( LinLinLin, calculateGridLength )
{
  Teuchos::Array<Utility::Pair<double,double> > tuple_grid( 4 );
  tuple_grid[0].second = -1.0;
  tuple_grid[1].second = 0.0;
  tuple_grid[2].second = 1.0;
  tuple_grid[3].second = 2.0;
  
  double grid_length = 
    Utility::LinLinLin::calculateGridLength<Utility::SECOND>( 
							    tuple_grid.begin(),
							    tuple_grid.end() );

  TEST_EQUALITY_CONST( grid_length, 3.0 );

  Teuchos::Array<double> grid( 4 );
  grid[0] = -1.0;
  grid[1] = 0.0;
  grid[2] = 1.0;
  grid[3] = 2.0;

  grid_length = 
    Utility::LinLinLin::calculateGridLength<Utility::FIRST>( grid.begin(),
							     grid.end() );

  TEST_EQUALITY_CONST( grid_length, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
TEUCHOS_UNIT_TEST( LinLinLin, calculateIntermediateGridLength )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LinLinLin::calculateIntermediateGridLength( 
							   x0, x1, x, L0, L1 );
  
  TEST_FLOATING_EQUALITY( Lx, 4.0, 1e-15 );

  x = 0.0;
  
  Lx = Utility::LinLinLin::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = 1.0;

  Lx = Utility::LinLinLin::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
TEUCHOS_UNIT_TEST( LinLinLin, calculateIntermediateGridMin )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0_min = -10.0, y1_min = 10.0;

  double yx_min = Utility::LinLinLin::calculateIntermediateGridMin(
						   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, 0.0, 1e-15 );

  x = 0.0;

  yx_min = Utility::LinLinLin::calculateIntermediateGridMin(
						   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, -10.0, 1e-15 );

  x = 1.0;

  yx_min = Utility::LinLinLin::calculateIntermediateGridMin(
						   x0, x1, x, y0_min, y1_min );
  
  TEST_FLOATING_EQUALITY( yx_min, 10.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LinLinLin, calculateUnitBaseIndepVar )
{
  double y_min = -1.0, y = 0.0, L = 2.0;

  double eta = Utility::LinLinLin::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.5, 1e-15 );

  y = -1.0;

  eta = Utility::LinLinLin::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-15 );

  y = 1.0;

  eta = Utility::LinLinLin::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LinLinLin, calculateGridIndepVar )
{
  double y_min = -1.0, L = 2.0, eta = 0.5;

  double y =  Utility::LinLinLin::calculateGridIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.0, 1e-15 );

  eta = 0.0;
  
  y = Utility::LinLinLin::calculateGridIndepVar( eta, y_min, L );
  
  TEST_FLOATING_EQUALITY( y, -1.0, 1e-15 );

  eta = 1.0;

  y = Utility::LinLinLin::calculateGridIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the linear-linear-linear unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( LinLinLin, interpolateUnitBase_raw_separate_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.0;
  
  Teuchos::Array<Utility::Pair<double,double> > y_0_grid( 4 );
  y_0_grid[0].second = -2.0;
  y_0_grid[1].second = -1.0;
  y_0_grid[2].second = 1.0;
  y_0_grid[3].second = 2.0;

  Teuchos::Array<Utility::Pair<double,double> > z_0_grid( 4 );

  z_0_grid[0].first = 0.0;
  z_0_grid[1].first = 1.0;
  z_0_grid[2].first = 2.0;
  z_0_grid[3].first = 3.0;

  Teuchos::Array<Utility::Pair<double,double> > y_1_grid( 3 );
  y_1_grid[0].second = -1.0;
  y_1_grid[1].second = 0.0;
  y_1_grid[2].second = 2.0;

  Teuchos::Array<Utility::Pair<double,double> > z_1_grid( 3 );
  z_1_grid[0].first = 1.0;
  z_1_grid[1].first = 2.0;
  z_1_grid[2].first = 3.0;

  double z = 
    Utility::LinLinLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.6938775510205, 1e-12 );

  y = -1.5; // min possible y at x = 0.5
  
  z = Utility::LinLinLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.42857142857143, 1e-12 );

  y = 2.0; // max possible y at x = 0.5

  z = Utility::LinLinLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.0;
  x = 0.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.5, 1e-12 );

  y = -2.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

  y = 2.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.0;
  x = 1.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 2.0, 1e-12 );

  y = -1.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 2.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-linear-linear unit base interpolation policy between 
// four points can be done
TEUCHOS_UNIT_TEST( LinLinLin, interpolateUnitBase_raw_combined_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.0;
  
  Teuchos::Array<Utility::Pair<double,double> > grid_0( 4 );
  grid_0[0]( -2.0, 0.0 );
  grid_0[1]( -1.0, 1.0 );
  grid_0[2]( 1.0, 2.0 );
  grid_0[3]( 2.0, 3.0 );

  Teuchos::Array<Utility::Pair<double,double> > grid_1( 3 );
  grid_1[0]( -1.0, 1.0 );
  grid_1[1]( 0.0, 2.0 );
  grid_1[2]( 2.0, 3.0 );

  double z = 
    Utility::LinLinLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.6938775510205, 1e-12 );

  y = -1.5; // min possible y at x = 0.5
  
  z = Utility::LinLinLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 0.42857142857143, 1e-12 );

  y = 2.0; // max possible y at x = 0.5

  z = Utility::LinLinLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.0;
  x = 0.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.5, 1e-12 );

  y = -2.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

  y = 2.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.0;
  x = 1.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 2.0, 1e-12 );

  y = -1.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 2.0;

  z = Utility::LinLinLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-linear-linear unit base interpolation policy between 
// four points can be done
TEUCHOS_UNIT_TEST( LinLinLin, interpolateUnitBase_raw_no_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.0;
  
  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[0] = -2.0;
  y_0_grid[1] = -1.0;
  y_0_grid[2] = 1.0;
  y_0_grid[3] = 2.0;

  Teuchos::Array<double> z_0_grid( 4 );

  z_0_grid[0] = 0.0;
  z_0_grid[1] = 1.0;
  z_0_grid[2] = 2.0;
  z_0_grid[3] = 3.0;

  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[0] = -1.0;
  y_1_grid[1] = 0.0;
  y_1_grid[2] = 2.0;

  Teuchos::Array<double> z_1_grid( 3 );
  z_1_grid[0] = 1.0;
  z_1_grid[1] = 2.0;
  z_1_grid[2] = 3.0;

  double z = 
    Utility::LinLinLin::interpolateUnitBase( x0,
					     x1,
					     x,
					     y,
					     y_0_grid.begin(),
					     y_0_grid.end(),
					     z_0_grid.begin(),
					     z_0_grid.end(),
					     y_1_grid.begin(),
					     y_1_grid.end(),
					     z_1_grid.begin(),
					     z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.6938775510205, 1e-12 );

  y = -1.5; // min possible y at x = 0.5
  
  z = Utility::LinLinLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );
  
  TEST_FLOATING_EQUALITY( z, 0.42857142857143, 1e-12 );
  
  y = 2.0; // max possible y at x = 0.5

  z = Utility::LinLinLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );
  
  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
  
  y = 0.0;
  x = 0.0;
  
  z = Utility::LinLinLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );
  
  TEST_FLOATING_EQUALITY( z, 1.5, 1e-12 );

  y = -2.0;

  z = Utility::LinLinLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

  y = 2.0;

  z = Utility::LinLinLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.0;
  x = 1.0;

  z = Utility::LinLinLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 2.0, 1e-12 );

  y = -1.0;

  z = Utility::LinLinLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 2.0;

  z = Utility::LinLinLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LinLogLin, interpolate_raw_separate_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 3e-2;
  Teuchos::Array<Utility::Pair<double,double> > y_0_grid( 4 );
  y_0_grid[0].first = 1e-3;
  y_0_grid[1].first = 1e-2;
  y_0_grid[2].first = 1e-1;
  y_0_grid[3].first = 1.0;

  Teuchos::Array<Utility::Pair<double,double> > z_0_grid( 4 );
  z_0_grid[0].second = 100.0;
  z_0_grid[1].second = 0.0;
  z_0_grid[2].second = 1.0;
  z_0_grid[3].second = 10.0;

  Teuchos::Array<Utility::Pair<double,double> > y_1_grid( 3 );
  y_1_grid[0].first = 1e-3;
  y_1_grid[1].first = 1e-1;
  y_1_grid[2].first = 1.0;

  Teuchos::Array<Utility::Pair<double,double> > z_1_grid( 3 );
  z_1_grid[0].second = 50.0;
  z_1_grid[1].second = 10.0;
  z_1_grid[2].second = 5.0;

  double z = Utility::LinLogLin::interpolate<Utility::FIRST,Utility::SECOND>(
							      x0,
							      x1,
							      x,
							      y,
							      y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

  x = 0.0;

  z = Utility::LinLogLin::interpolate<Utility::FIRST,Utility::SECOND>(
							      x0,
							      x1,
							      x,
							      y,
							      y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

  x = 1.0;
  
  z = Utility::LinLogLin::interpolate<Utility::FIRST,Utility::SECOND>(
							      x0,
							      x1,
							      x,
							      y,
							      y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LinLogLin, interpolate_raw_combined_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 3e-2;
  Teuchos::Array<Utility::Pair<double,double> > grid_0( 4 );
  grid_0[0]( 1e-3, 100.0 );
  grid_0[1]( 1e-2, 0.0 );
  grid_0[2]( 1e-1, 1.0 );
  grid_0[3](1.0, 10.0 );

  Teuchos::Array<Utility::Pair<double,double> > grid_1( 3 );
  grid_1[0]( 1e-3, 50.0 );
  grid_1[1]( 1e-1, 10.0 );
  grid_1[2]( 1.0, 5.0 );

  double z = Utility::LinLogLin::interpolate<Utility::FIRST,Utility::SECOND>(
							        x0,
								x1,
								x,
								y,
							        grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

  x = 0.0;

  z = Utility::LinLogLin::interpolate<Utility::FIRST,Utility::SECOND>(
							        x0,
								x1,
								x,
								y,
							        grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

  x = 1.0;
  
  z = Utility::LinLogLin::interpolate<Utility::FIRST,Utility::SECOND>(
							        x0,
								x1,
								x,
								y,
							        grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LinLogLin, interpolate_raw_no_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 3e-2;
  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[0] = 1e-3;
  y_0_grid[1] = 1e-2;
  y_0_grid[2] = 1e-1;
  y_0_grid[3] = 1.0;

  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[0] = 100.0;
  z_0_grid[1] = 0.0;
  z_0_grid[2] = 1.0;
  z_0_grid[3] = 10.0;

  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[0] = 1e-3;
  y_1_grid[1] = 1e-1;
  y_1_grid[2] = 1.0;

  Teuchos::Array<double> z_1_grid( 3 );
  z_1_grid[0] = 50.0;
  z_1_grid[1] = 10.0;
  z_1_grid[2] = 5.0;

  double z = Utility::LinLogLin::interpolate( x0,
					      x1,
					      x,
					      y,
					      y_0_grid.begin(),
					      y_0_grid.end(),
					      z_0_grid.begin(),
					      z_0_grid.end(),
					      y_1_grid.begin(),
					      y_1_grid.end(),
					      z_1_grid.begin(),
					      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

  x = 0.0;

  z = Utility::LinLogLin::interpolate( x0,
				       x1,
				       x,
				       y,
				       y_0_grid.begin(),
				       y_0_grid.end(),
				       z_0_grid.begin(),
				       z_0_grid.end(),
				       y_1_grid.begin(),
				       y_1_grid.end(),
				       z_1_grid.begin(),
				       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

  x = 1.0;
  
  z = Utility::LinLogLin::interpolate( x0,
				       x1,
				       x,
				       y,
				       y_0_grid.begin(),
				       y_0_grid.end(),
				       z_0_grid.begin(),
				       z_0_grid.end(),
				       y_1_grid.begin(),
				       y_1_grid.end(),
				       z_1_grid.begin(),
				       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid length can be calculated
TEUCHOS_UNIT_TEST( LinLogLin, calculateGridLength )
{
  Teuchos::Array<Utility::Trip<double,double,double> > tuple_grid( 4 );
  tuple_grid[0].second = 1e-3;
  tuple_grid[1].second = 1e-2;
  tuple_grid[2].second = 1e-1;
  tuple_grid[3].second = 1.0;
  
  double grid_length = 
    Utility::LinLogLin::calculateGridLength<Utility::SECOND>( 
							    tuple_grid.begin(),
							    tuple_grid.end() );

  TEST_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );

  Teuchos::Array<double> grid( 4 );
  grid[0] = 1e-3;
  grid[1] = 1e-2;
  grid[2] = 1e-1;
  grid[3] = 1.0;

  grid_length = 
    Utility::LinLogLin::calculateGridLength<Utility::FIRST>( grid.begin(),
							     grid.end() );

  TEST_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
TEUCHOS_UNIT_TEST( LinLogLin, calculateIntermediateGridLength )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LinLogLin::calculateIntermediateGridLength( 
							   x0, x1, x, L0, L1 );
  
  TEST_FLOATING_EQUALITY( Lx, 4.0, 1e-15 );

  x = 0.0;
  
  Lx = Utility::LinLogLin::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = 1.0;

  Lx = Utility::LinLogLin::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
TEUCHOS_UNIT_TEST( LinLogLin, calculateIntermediateGridMin )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0_min = 1e-3, y1_min = 1e-2;

  double yx_min = Utility::LinLogLin::calculateIntermediateGridMin(
						   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, 3.1622776601686e-3, 1e-12 );

  x = 0.0;

  yx_min = Utility::LinLogLin::calculateIntermediateGridMin(
						   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, 1e-3, 1e-12 );

  x = 1.0;

  yx_min = Utility::LinLogLin::calculateIntermediateGridMin(
						   x0, x1, x, y0_min, y1_min );
  
  TEST_FLOATING_EQUALITY( yx_min, 1e-2, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LinLogLin, calculateUnitBaseIndepVar )
{
  double y_min = 1e-3, y = 1e-2, L = 3.0;

  double eta = Utility::LinLogLin::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = 1e-3;

  eta = Utility::LinLogLin::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 0.020085536923187;

  eta = Utility::LinLogLin::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LinLogLin, calculateGridIndepVar )
{
  double y_min = 1e-3, L = 3.0, eta = 0.5;

  double y =  Utility::LinLogLin::calculateGridIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.0044816890703382, 1e-12 );

  eta = 0.0;
  
  y = Utility::LinLogLin::calculateGridIndepVar( eta, y_min, L );
  
  TEST_FLOATING_EQUALITY( y, 1e-3, 1e-12 );

  eta = 1.0;

  y = Utility::LinLogLin::calculateGridIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.020085536923187, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( LinLogLin, interpolateUnitBase_raw_separate_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.03;
  
  Teuchos::Array<Utility::Pair<double,double> > y_0_grid( 4 );
  y_0_grid[0].second = 1e-3;
  y_0_grid[1].second = 1e-2;
  y_0_grid[2].second = 1e-1;
  y_0_grid[3].second = 1.0;

  Teuchos::Array<Utility::Pair<double,double> > z_0_grid( 4 );
  z_0_grid[0].first = 0.0;
  z_0_grid[1].first = 1.0;
  z_0_grid[2].first = 2.0;
  z_0_grid[3].first = 3.0;

  Teuchos::Array<Utility::Pair<double,double> > y_1_grid( 3 );
  y_1_grid[0].second = 1e-2;
  y_1_grid[1].second = 1e-1;
  y_1_grid[2].second = 1.0;

  Teuchos::Array<Utility::Pair<double,double> > z_1_grid( 3 );
  z_1_grid[0].first = 1.0;
  z_1_grid[1].first = 2.0;
  z_1_grid[2].first = 3.0;

  double z = 
    Utility::LinLogLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

  y = 0.0031622776601684; // min possible y at x = 0.5
  
  z = Utility::LinLogLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.4, 1e-12 );

  y = 1.0; // max possible y at x = 0.5

  z = Utility::LinLogLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.03;
  x = 0.0;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-3;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  UTILITY_TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.03;
  x = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-2;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::SECOND,Utility::FIRST>( 
							      x0,
							      x1,
							      x,
							      y,
						              y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( LinLogLin, interpolateUnitBase_raw_combined_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.03;
  
  Teuchos::Array<Utility::Pair<double,double> > grid_0( 4 );
  grid_0[0]( 1e-3, 0.0 );
  grid_0[1]( 1e-2, 1.0 );
  grid_0[2]( 1e-1, 2.0 );
  grid_0[3]( 1.0, 3.0 );

  Teuchos::Array<Utility::Pair<double,double> > grid_1( 3 );
  grid_1[0]( 1e-2, 1.0 );
  grid_1[1]( 1e-1, 2.0 );
  grid_1[2]( 1.0, 3.0 );

  double z = 
    Utility::LinLogLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

  y = 0.0031622776601684; // min possible y at x = 0.5
  
  z = Utility::LinLogLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 0.4, 1e-12 );

  y = 1.0; // max possible y at x = 0.5

  z = Utility::LinLogLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );
  

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.03;
  x = 0.0;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-3;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  UTILITY_TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.03;
  x = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-2;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<Utility::FIRST,Utility::SECOND>( 
							        x0,
								x1,
								x,
								y,
						                grid_0.begin(),
								grid_0.end(),
								grid_1.begin(),
								grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( LinLogLin, interpolateUnitBase_raw_no_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.03;
  
  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[0] = 1e-3;
  y_0_grid[1] = 1e-2;
  y_0_grid[2] = 1e-1;
  y_0_grid[3] = 1.0;

  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[0] = 0.0;
  z_0_grid[1] = 1.0;
  z_0_grid[2] = 2.0;
  z_0_grid[3] = 3.0;

  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[0] = 1e-2;
  y_1_grid[1] = 1e-1;
  y_1_grid[2] = 1.0;

  Teuchos::Array<double> z_1_grid( 3 );
  z_1_grid[0] = 1.0;
  z_1_grid[1] = 2.0;
  z_1_grid[2] = 3.0;

  double z = Utility::LinLogLin::interpolateUnitBase( x0,
						      x1,
						      x,
						      y,
						      y_0_grid.begin(),
						      y_0_grid.end(),
						      z_0_grid.begin(),
						      z_0_grid.end(),
						      y_1_grid.begin(),
						      y_1_grid.end(),
						      z_1_grid.begin(),
						      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

  y = 0.0031622776601684; // min possible y at x = 0.5
  
  z = Utility::LinLogLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.4, 1e-12 );

  y = 1.0; // max possible y at x = 0.5

  z = Utility::LinLogLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.03;
  x = 0.0;

  z = Utility::LinLogLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-3;

  z = Utility::LinLogLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  UTILITY_TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.03;
  x = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-2;

  z = Utility::LinLogLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );
    
  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// end tstTwoDInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
