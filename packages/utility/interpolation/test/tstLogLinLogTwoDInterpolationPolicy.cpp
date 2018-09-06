//---------------------------------------------------------------------------//
//!
//! \file   tstLogLinLogTwoDInterpolationPolicy.cpp
//! \author Alex Robinson
//! \brief  2D interpolation policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef std::tuple<
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double>,
             std::integral_constant<size_t,0>,std::tuple<double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double>,
             std::integral_constant<size_t,1>,std::tuple<double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::tuple<double,double>,
             std::integral_constant<size_t,0>,std::tuple<double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::tuple<double,double>,
             std::integral_constant<size_t,1>,std::tuple<double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,unsigned>,
             std::integral_constant<size_t,0>,std::tuple<double,unsigned> >,
  std::tuple<std::integral_constant<size_t,1>,std::tuple<unsigned,double>,
             std::integral_constant<size_t,1>,std::tuple<unsigned,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double,double>,
             std::integral_constant<size_t,0>,std::tuple<double,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double,double>,
             std::integral_constant<size_t,1>,std::tuple<double,double,unsigned> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double,double>,
             std::integral_constant<size_t,2>,std::tuple<unsigned,double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::tuple<unsigned,double,double>,
             std::integral_constant<size_t,0>,std::tuple<double,unsigned,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::tuple<double,unsigned,double>,
             std::integral_constant<size_t,0>,std::tuple<double,unsigned,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::tuple<double,unsigned,double>,
             std::integral_constant<size_t,1>,std::tuple<unsigned,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double,double,double>,
             std::integral_constant<size_t,0>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double,double,double>,
             std::integral_constant<size_t,2>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double,double,double>,
             std::integral_constant<size_t,3>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::tuple<double,double,double,double>,
             std::integral_constant<size_t,0>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::tuple<double,double,double,double>,
             std::integral_constant<size_t,1>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,3>,std::tuple<unsigned,double,double,double>,
             std::integral_constant<size_t,2>,std::tuple<unsigned,double,double,double> >
  > TestTwoTupleTwoElementTypes;

typedef std::tuple<
  std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,1>,std::tuple<double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,0>,std::tuple<double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,1>,std::tuple<double,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,2>,std::tuple<double,unsigned,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,0>,std::tuple<double,double,unsigned> >,
  std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,2>,std::tuple<unsigned,double,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,0>,std::tuple<double,double,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,1>,std::tuple<double,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,1>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,2>,std::tuple<double,unsigned,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,3>,std::tuple<double,double,unsigned,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,0>,std::tuple<double,double,double,unsigned> >,
  std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,2>,std::tuple<unsigned,double,double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,3>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,0>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,1>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,3>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,3>,std::integral_constant<size_t,0>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,3>,std::integral_constant<size_t,1>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,3>,std::integral_constant<size_t,2>,std::tuple<double,unsigned,double,double> >
  > TestTupleTwoElementTypes;

typedef std::tuple<
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::tuple<double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,unsigned,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::tuple<double,double,unsigned> >,
  std::tuple<std::integral_constant<size_t,2>,std::tuple<unsigned,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,unsigned,double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::tuple<double,double,unsigned,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::tuple<double,double,double,unsigned> >,
  std::tuple<std::integral_constant<size_t,3>,std::tuple<unsigned,double,double,double> >
  > TestTupleElementTypes;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the log-linear-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLinLog,
                                   interpolate_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.0;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], -10.0 );
  Utility::set<ymember>( y_0_grid[1], -1.0 );
  Utility::set<ymember>( y_0_grid[2], 1.0 );
  Utility::set<ymember>( y_0_grid[3], 10.0 );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 100.0 );
  Utility::set<zmember>( z_0_grid[1], 0.1 );
  Utility::set<zmember>( z_0_grid[2], 1.0 );
  Utility::set<zmember>( z_0_grid[3], 10.0 );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], -10.0 );
  Utility::set<ymember>( y_1_grid[1], -5.0 );
  Utility::set<ymember>( y_1_grid[2], 10.0 );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 50.0 );
  Utility::set<zmember>( z_1_grid[1], 5.0 );
  Utility::set<zmember>( z_1_grid[2], 0.5 );

  double z = Utility::LogLinLog::interpolate<ymember,zmember>(x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.8184905217915075, 1e-12 );

  x = 0.1;

  z = Utility::LogLinLog::interpolate<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.316227766016838, 1e-12 );

  x = 1.0;

  z = Utility::LogLinLog::interpolate<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.320794416806389, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLinLog,
                                   interpolate_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.0;

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], -10.0 );
  Utility::set<ymember>( grid_0[1], -1.0 );
  Utility::set<ymember>( grid_0[2], 1.0 );
  Utility::set<ymember>( grid_0[3], 10.0 );
  Utility::set<zmember>( grid_0[0], 100.0 );
  Utility::set<zmember>( grid_0[1], 0.1 );
  Utility::set<zmember>( grid_0[2], 1.0 );
  Utility::set<zmember>( grid_0[3], 10.0 );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], -10.0 );
  Utility::set<ymember>( grid_1[1], -5.0 );
  Utility::set<ymember>( grid_1[2], 10.0 );
  Utility::set<zmember>( grid_1[0], 50.0 );
  Utility::set<zmember>( grid_1[1], 5.0 );
  Utility::set<zmember>( grid_1[2], 0.5 );

  double z = Utility::LogLinLog::interpolate<ymember,zmember>(x0,
							      x1,
							      x,
							      y,
							      grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.8184905217915075, 1e-12 );

  x = 0.1;

  z = Utility::LogLinLog::interpolate<ymember,zmember>( x0,
							x1,
							x,
							y,
							grid_0.begin(),
							grid_0.end(),
							grid_1.begin(),
							grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.316227766016838, 1e-12 );

  x = 1.0;

  z = Utility::LogLinLog::interpolate<ymember,zmember>( x0,
							x1,
							x,
							y,
							grid_0.begin(),
							grid_0.end(),
							grid_1.begin(),
							grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.320794416806389, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST( LogLinLog, interpolate_no_tuple_grids )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.0;

  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = -10.0;
  y_0_grid[1] = -1.0;
  y_0_grid[2] = 1.0;
  y_0_grid[3] = 10.0;

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = 100.0;
  z_0_grid[1] = 0.1;
  z_0_grid[2] = 1.0;
  z_0_grid[3] = 10.0;

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = -10.0;
  y_1_grid[1] = -5.0;
  y_1_grid[2] = 10.0;

  std::vector<double> z_1_grid( 3 );
  z_1_grid[0] = 50.0;
  z_1_grid[1] = 5.0;
  z_1_grid[2] = 0.5;

  double z = Utility::LogLinLog::interpolate( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.8184905217915075, 1e-12 );

  x = 0.1;

  z = Utility::LogLinLog::interpolate( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.316227766016838, 1e-12 );

  x = 1.0;

  z = Utility::LogLinLog::interpolate( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.320794416806389, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
FRENSIE_UNIT_TEST( LogLinLog, calculateIntermediateGridLength )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3;
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LogLinLog::calculateIntermediateGridLength(
							   x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.9542425094393248, 1e-15 );

  x = 0.1;

  Lx = Utility::LogLinLog::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = 1.0;

  Lx = Utility::LogLinLog::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
FRENSIE_UNIT_TEST( LogLinLog, calculateIntermediateGridLimit )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3;
  double y0_min = -10.0, y1_min = 10.0;

  double yx_min = Utility::LogLinLog::calculateIntermediateGridLimit(
						   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, -0.4575749056067533, 1e-15 );

  x = 0.1;

  yx_min = Utility::LogLinLog::calculateIntermediateGridLimit(
						   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, -10.0, 1e-15 );

  x = 1.0;

  yx_min = Utility::LogLinLog::calculateIntermediateGridLimit(
						   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, 10.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLinLog,
                                   interpolateUnitBase_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.0;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], -2.0 );
  Utility::set<ymember>( y_0_grid[1], -1.0 );
  Utility::set<ymember>( y_0_grid[2], 1.0 );
  Utility::set<ymember>( y_0_grid[3], 2.0 );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 1e-3 );
  Utility::set<zmember>( z_0_grid[1], 1e-2 );
  Utility::set<zmember>( z_0_grid[2], 1e-1 );
  Utility::set<zmember>( z_0_grid[3], 1.0 );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], -1.0 );
  Utility::set<ymember>( y_1_grid[1], 0.0 );
  Utility::set<ymember>( y_1_grid[2], 2.0 );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 1e-2 );
  Utility::set<zmember>( z_1_grid[1], 1e-1 );
  Utility::set<zmember>( z_1_grid[2], 1.0 );

  double z =
    Utility::LogLinLog::interpolateUnitBase<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.048200417533359755, 1e-12 );

  y = -1.5228787452803376; // min possible y at x = 0.3

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.00254862034908775, 1e-12 );

  y = 2.0; // max possible y at x = 0.3

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = 0.1;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.0316227766016838, 1e-12 );

  y = -2.0;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = 1.0;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.1, 1e-12 );

  y = -1.0;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLinLog,
                                   interpolateUnitBase_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.0;

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], -2.0 );
  Utility::set<ymember>( grid_0[1], -1.0 );
  Utility::set<ymember>( grid_0[2], 1.0 );
  Utility::set<ymember>( grid_0[3], 2.0 );
  Utility::set<zmember>( grid_0[0], 1e-3 );
  Utility::set<zmember>( grid_0[1], 1e-2 );
  Utility::set<zmember>( grid_0[2], 1e-1 );
  Utility::set<zmember>( grid_0[3], 1.0 );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], -1.0 );
  Utility::set<ymember>( grid_1[1], 0.0 );
  Utility::set<ymember>( grid_1[2], 2.0 );
  Utility::set<zmember>( grid_1[0], 1e-2 );
  Utility::set<zmember>( grid_1[1], 1e-1 );
  Utility::set<zmember>( grid_1[2], 1.0 );

  double z =
    Utility::LogLinLog::interpolateUnitBase<ymember,zmember>( x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.048200417533359755, 1e-12 );

  y = -1.5228787452803376; // min possible y at x = 0.3

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.00254862034908775, 1e-12 );

  y = 2.0; // max possible y at x = 0.3

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = 0.1;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.0316227766016838, 1e-12 );

  y = -2.0;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = 1.0;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.1, 1e-12 );

  y = -1.0;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST( LogLinLog, interpolateUnitBase_no_tuple_grids )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.0;

  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = -2.0;
  y_0_grid[1] = -1.0;
  y_0_grid[2] = 1.0;
  y_0_grid[3] = 2.0;

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = 1e-3;
  z_0_grid[1] = 1e-2;
  z_0_grid[2] = 1e-1;
  z_0_grid[3] = 1.0;

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = -1.0;
  y_1_grid[1] = 0.0;
  y_1_grid[2] = 2.0;

  std::vector<double> z_1_grid( 3 );
  z_1_grid[0] = 1e-2;
  z_1_grid[1] = 1e-1;
  z_1_grid[2] = 1.0;

  double z =
    Utility::LogLinLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.048200417533359755, 1e-12 );

  y = -1.5228787452803376; // min possible y at x = 0.3

  z = Utility::LogLinLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.00254862034908775, 1e-12 );

  y = 2.0; // max possible y at x = 0.3

  z = Utility::LogLinLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = 0.1;

  z = Utility::LogLinLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.0316227766016838, 1e-12 );

  y = -2.0;

  z = Utility::LogLinLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = 1.0;

  z = Utility::LogLinLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.1, 1e-12 );

  y = -1.0;

  z = Utility::LogLinLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the dependent variable can be processed
FRENSIE_UNIT_TEST( LogLinLog, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(0.1),
			  Utility::LogLinLog::processDepVar(0.1),
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(1.0),
			  Utility::LogLinLog::processDepVar( 1.0 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogLinLog, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.1,
			  Utility::LogLinLog::recoverProcessedDepVar(std::log(0.1)),
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
			  Utility::LogLinLog::recoverProcessedDepVar(std::log(1.0)),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the second independent variable can be processed
FRENSIE_UNIT_TEST( LogLinLog, processSecondIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LogLinLog::processSecondIndepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LogLinLog::processSecondIndepVar(0.0) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LogLinLog::processSecondIndepVar(1.0) );
}

//---------------------------------------------------------------------------//
// Check that a processed second independent variable can be processed
FRENSIE_UNIT_TEST( LogLinLog, recoverProcessedSecondIndepVar )
{
  FRENSIE_CHECK_EQUAL(
		    -1.0,
		    Utility::LogLinLog::recoverProcessedSecondIndepVar(-1.0) );
  FRENSIE_CHECK_EQUAL(
		     0.0,
		     Utility::LogLinLog::recoverProcessedSecondIndepVar(0.0) );
  FRENSIE_CHECK_EQUAL(1.0,
		      Utility::LogLinLog::recoverProcessedSecondIndepVar(1.0));
}

//---------------------------------------------------------------------------//
// Check that the first independent variable can be processed
FRENSIE_UNIT_TEST( LogLinLog, processFirstIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(0.1),
			  Utility::LogLinLog::processFirstIndepVar(0.1),
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(1.0),
			  Utility::LogLinLog::processFirstIndepVar(1.0),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed first independent variable can be recovered
FRENSIE_UNIT_TEST( LogLinLog, recoverProcessedFirstIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
		  0.1,
		  Utility::LogLinLog::recoverProcessedFirstIndepVar(std::log(0.1)),
		  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		  1.0,
		  Utility::LogLinLog::recoverProcessedFirstIndepVar(std::log(1.0)),
		  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLinLog,
                                   interpolateProcessed_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = Utility::LogLinLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLinLog::processFirstIndepVar(1.0);
  double x = Utility::LogLinLog::processFirstIndepVar(0.3);
  double y = 0.0;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], -10.0 );
  Utility::set<ymember>( y_0_grid[1], -1.0 );
  Utility::set<ymember>( y_0_grid[2], 1.0 );
  Utility::set<ymember>( y_0_grid[3], 10.0 );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0],
			 Utility::LogLinLog::processDepVar(100.0) );
  Utility::set<zmember>( z_0_grid[1],
			 Utility::LogLinLog::processDepVar(0.1) );
  Utility::set<zmember>( z_0_grid[2],
			 Utility::LogLinLog::processDepVar(1.0) );
  Utility::set<zmember>( z_0_grid[3],
			 Utility::LogLinLog::processDepVar(10.0) );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], -10.0 );
  Utility::set<ymember>( y_1_grid[1], -5.0 );
  Utility::set<ymember>( y_1_grid[2], 10.0 );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0],
			 Utility::LogLinLog::processDepVar(50.0) );
  Utility::set<zmember>( z_1_grid[1],
			 Utility::LogLinLog::processDepVar(5.0) );
  Utility::set<zmember>( z_1_grid[2],
			 Utility::LogLinLog::processDepVar(0.5) );

  double z = Utility::LogLinLog::interpolateProcessed<ymember,zmember>(x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.8184905217915075, 1e-12 );

  x = Utility::LogLinLog::processFirstIndepVar(0.1);

  z = Utility::LogLinLog::interpolateProcessed<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.316227766016838, 1e-12 );

  x = Utility::LogLinLog::processFirstIndepVar(1.0);

  z = Utility::LogLinLog::interpolateProcessed<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.320794416806389, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLinLog,
                                   interpolateProcessed_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = Utility::LogLinLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLinLog::processFirstIndepVar(1.0);
  double x = Utility::LogLinLog::processFirstIndepVar(0.3);
  double y = 0.0;

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], -10.0 );
  Utility::set<ymember>( grid_0[1], -1.0 );
  Utility::set<ymember>( grid_0[2], 1.0 );
  Utility::set<ymember>( grid_0[3], 10.0 );
  Utility::set<zmember>( grid_0[0],
			 Utility::LogLinLog::processDepVar(100.0) );
  Utility::set<zmember>( grid_0[1],
			 Utility::LogLinLog::processDepVar(0.1) );
  Utility::set<zmember>( grid_0[2],
			 Utility::LogLinLog::processDepVar(1.0) );
  Utility::set<zmember>( grid_0[3],
			 Utility::LogLinLog::processDepVar(10.0) );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], -10.0 );
  Utility::set<ymember>( grid_1[1], -5.0 );
  Utility::set<ymember>( grid_1[2], 10.0 );
  Utility::set<zmember>( grid_1[0],
			 Utility::LogLinLog::processDepVar(50.0) );
  Utility::set<zmember>( grid_1[1],
			 Utility::LogLinLog::processDepVar(5.0) );
  Utility::set<zmember>( grid_1[2],
			 Utility::LogLinLog::processDepVar(0.5) );

  double z = Utility::LogLinLog::interpolateProcessed<ymember,zmember>(x0,
							      x1,
							      x,
							      y,
							      grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.8184905217915075, 1e-12 );

  x = Utility::LogLinLog::processFirstIndepVar(0.1);

  z = Utility::LogLinLog::interpolateProcessed<ymember,zmember>( x0,
							x1,
							x,
							y,
							grid_0.begin(),
							grid_0.end(),
							grid_1.begin(),
							grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.316227766016838, 1e-12 );

  x = Utility::LogLinLog::processFirstIndepVar(1.0);

  z = Utility::LogLinLog::interpolateProcessed<ymember,zmember>( x0,
							x1,
							x,
							y,
							grid_0.begin(),
							grid_0.end(),
							grid_1.begin(),
							grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.320794416806389, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST( LogLinLog, interpolateProcessed_no_tuple_grids )
{
  double x0 = Utility::LogLinLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLinLog::processFirstIndepVar(1.0);
  double x = Utility::LogLinLog::processFirstIndepVar(0.3);
  double y = 0.0;

  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = -10.0;
  y_0_grid[1] = -1.0;
  y_0_grid[2] = 1.0;
  y_0_grid[3] = 10.0;

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = Utility::LogLinLog::processDepVar(100.0);
  z_0_grid[1] = Utility::LogLinLog::processDepVar(0.1);
  z_0_grid[2] = Utility::LogLinLog::processDepVar(1.0);
  z_0_grid[3] = Utility::LogLinLog::processDepVar(10.0);

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = -10.0;
  y_1_grid[1] = -5.0;
  y_1_grid[2] = 10.0;

  std::vector<double> z_1_grid( 3 );
  z_1_grid[0] = Utility::LogLinLog::processDepVar(50.0);
  z_1_grid[1] = Utility::LogLinLog::processDepVar(5.0);
  z_1_grid[2] = Utility::LogLinLog::processDepVar(0.5);

  double z = Utility::LogLinLog::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.8184905217915075, 1e-12 );

  x = Utility::LogLinLog::processFirstIndepVar(0.1);

  z = Utility::LogLinLog::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.316227766016838, 1e-12 );

  x = Utility::LogLinLog::processFirstIndepVar(1.0);

  z = Utility::LogLinLog::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.320794416806389, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
FRENSIE_UNIT_TEST( LogLinLog, calculateIntermediateGridLengthProcessed )
{
  double x0 = Utility::LogLinLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLinLog::processFirstIndepVar(1.0);
  double x = Utility::LogLinLog::processFirstIndepVar(0.3);
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LogLinLog::calculateIntermediateGridLengthProcessed(
							   x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.9542425094393248, 1e-15 );

  x = Utility::LogLinLog::processFirstIndepVar(0.1);

  Lx = Utility::LogLinLog::calculateIntermediateGridLengthProcessed(
							   x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = Utility::LogLinLog::processFirstIndepVar(1.0);

  Lx = Utility::LogLinLog::calculateIntermediateGridLengthProcessed(
							   x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
FRENSIE_UNIT_TEST( LogLinLog, calculateIntermediateProcessedGridLimit )
{
  double x0 = Utility::LogLinLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLinLog::processFirstIndepVar(1.0);
  double x = Utility::LogLinLog::processFirstIndepVar(0.3);
  double y0_min = -10.0, y1_min = 10.0;

  double yx_min = Utility::LogLinLog::calculateIntermediateProcessedGridLimit(
						   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, -0.4575749056067533, 1e-15 );

  x = Utility::LogLinLog::processFirstIndepVar(0.1);

  yx_min = Utility::LogLinLog::calculateIntermediateProcessedGridLimit(
						   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, -10.0, 1e-15 );

  x = Utility::LogLinLog::processFirstIndepVar(1.0);

  yx_min = Utility::LogLinLog::calculateIntermediateProcessedGridLimit(
						   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, 10.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLinLog,
                                   interpolateProcessedUnitBase_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = Utility::LogLinLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLinLog::processFirstIndepVar(1.0);
  double x = Utility::LogLinLog::processFirstIndepVar(0.3);
  double y = 0.0;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], -2.0 );
  Utility::set<ymember>( y_0_grid[1], -1.0 );
  Utility::set<ymember>( y_0_grid[2], 1.0 );
  Utility::set<ymember>( y_0_grid[3], 2.0 );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0],
			 Utility::LogLinLog::processDepVar(1e-3) );
  Utility::set<zmember>( z_0_grid[1],
			 Utility::LogLinLog::processDepVar(1e-2) );
  Utility::set<zmember>( z_0_grid[2],
			 Utility::LogLinLog::processDepVar(1e-1) );
  Utility::set<zmember>( z_0_grid[3],
			 Utility::LogLinLog::processDepVar(1.0) );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], -1.0 );
  Utility::set<ymember>( y_1_grid[1], 0.0 );
  Utility::set<ymember>( y_1_grid[2], 2.0 );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0],
			 Utility::LogLinLog::processDepVar(1e-2) );
  Utility::set<zmember>( z_1_grid[1],
			 Utility::LogLinLog::processDepVar(1e-1) );
  Utility::set<zmember>( z_1_grid[2],
			 Utility::LogLinLog::processDepVar(1.0) );

  double z =
    Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.048200417533359755, 1e-12 );

  y = -1.5228787452803376; // min possible y at x = 0.3

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.00254862034908775, 1e-12 );

  y = 2.0; // max possible y at x = 0.3

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = Utility::LogLinLog::processFirstIndepVar(0.1);

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.0316227766016838, 1e-12 );

  y = -2.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = Utility::LogLinLog::processFirstIndepVar(1.0);

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.1, 1e-12 );

  y = -1.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLinLog,
                                   interpolateProcessedUnitBase_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = Utility::LogLinLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLinLog::processFirstIndepVar(1.0);
  double x = Utility::LogLinLog::processFirstIndepVar(0.3);
  double y = 0.0;

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], -2.0 );
  Utility::set<ymember>( grid_0[1], -1.0 );
  Utility::set<ymember>( grid_0[2], 1.0 );
  Utility::set<ymember>( grid_0[3], 2.0 );
  Utility::set<zmember>( grid_0[0],
			 Utility::LogLinLog::processDepVar(1e-3) );
  Utility::set<zmember>( grid_0[1],
			 Utility::LogLinLog::processDepVar(1e-2) );
  Utility::set<zmember>( grid_0[2],
			 Utility::LogLinLog::processDepVar(1e-1) );
  Utility::set<zmember>( grid_0[3],
			 Utility::LogLinLog::processDepVar(1.0) );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], -1.0 );
  Utility::set<ymember>( grid_1[1], 0.0 );
  Utility::set<ymember>( grid_1[2], 2.0 );
  Utility::set<zmember>( grid_1[0],
			 Utility::LogLinLog::processDepVar(1e-2) );
  Utility::set<zmember>( grid_1[1],
			 Utility::LogLinLog::processDepVar(1e-1) );
  Utility::set<zmember>( grid_1[2],
			 Utility::LogLinLog::processDepVar(1.0) );

  double z =
    Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.048200417533359755, 1e-12 );

  y = -1.5228787452803376; // min possible y at x = 0.3

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.00254862034908775, 1e-12 );

  y = 2.0; // max possible y at x = 0.3

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = Utility::LogLinLog::processFirstIndepVar(0.1);

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.0316227766016838, 1e-12 );

  y = -2.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = Utility::LogLinLog::processFirstIndepVar(1.0);

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.1, 1e-12 );

  y = -1.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-linear-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST( LogLinLog, interpolateProcessedUnitBase_no_tuple_grids )
{
  double x0 = Utility::LogLinLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLinLog::processFirstIndepVar(1.0);
  double x = Utility::LogLinLog::processFirstIndepVar(0.3);
  double y = 0.0;

  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = -2.0;
  y_0_grid[1] = -1.0;
  y_0_grid[2] = 1.0;
  y_0_grid[3] = 2.0;

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = Utility::LogLinLog::processDepVar(1e-3);
  z_0_grid[1] = Utility::LogLinLog::processDepVar(1e-2);
  z_0_grid[2] = Utility::LogLinLog::processDepVar(1e-1);
  z_0_grid[3] = Utility::LogLinLog::processDepVar(1.0);

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = -1.0;
  y_1_grid[1] = 0.0;
  y_1_grid[2] = 2.0;

  std::vector<double> z_1_grid( 3 );
  z_1_grid[0] = Utility::LogLinLog::processDepVar(1e-2);
  z_1_grid[1] = Utility::LogLinLog::processDepVar(1e-1);
  z_1_grid[2] = Utility::LogLinLog::processDepVar(1.0);

  double z =
    Utility::LogLinLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.048200417533359755, 1e-12 );

  y = -1.5228787452803376; // min possible y at x = 0.3

  z = Utility::LogLinLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.00254862034908775, 1e-12 );

  y = 2.0; // max possible y at x = 0.3

  z = Utility::LogLinLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = Utility::LogLinLog::processFirstIndepVar(0.1);

  z = Utility::LogLinLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.0316227766016838, 1e-12 );

  y = -2.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.0;
  x = Utility::LogLinLog::processFirstIndepVar(1.0);

  z = Utility::LogLinLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.1, 1e-12 );

  y = -1.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

  y = 2.0;

  z = Utility::LogLinLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// end tstLogLinLogTwoDInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
