//---------------------------------------------------------------------------//
//!
//! \file   tstLogLogCosLogTwoDInterpolationPolicy.cpp
//! \author Alex Robinson
//! \brief  2D interpolation policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Test Variables
//---------------------------------------------------------------------------//
double delta = 1e-10;

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
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_false,
                                   interpolate_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], -1.0 );
  Utility::set<ymember>( y_0_grid[1], 0.0 );
  Utility::set<ymember>( y_0_grid[2], 0.5 );
  Utility::set<ymember>( y_0_grid[3], 0.999999 );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 100.0 );
  Utility::set<zmember>( z_0_grid[1], 0.1 );
  Utility::set<zmember>( z_0_grid[2], 1.0 );
  Utility::set<zmember>( z_0_grid[3], 10.0 );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], -1.0 );
  Utility::set<ymember>( y_1_grid[1], 0.0 );
  Utility::set<ymember>( y_1_grid[2], 0.999999 );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 50.0 );
  Utility::set<zmember>( z_1_grid[1], 5.0 );
  Utility::set<zmember>( z_1_grid[2], 0.5 );

  double z =
    Utility::LogLogCosLog::interpolate<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

  x = 0.1;

  z = Utility::LogLogCosLog::interpolate<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

  x = 1.0;

  z = Utility::LogLogCosLog::interpolate<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_false,
                                   interpolate_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], -1.0 );
  Utility::set<ymember>( grid_0[1], 0.0 );
  Utility::set<ymember>( grid_0[2], 0.5 );
  Utility::set<ymember>( grid_0[3], 0.999999 );
  Utility::set<zmember>( grid_0[0], 100.0 );
  Utility::set<zmember>( grid_0[1], 0.1 );
  Utility::set<zmember>( grid_0[2], 1.0 );
  Utility::set<zmember>( grid_0[3], 10.0 );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], -1.0 );
  Utility::set<ymember>( grid_1[1], 0.0 );
  Utility::set<ymember>( grid_1[2], 0.999999 );
  Utility::set<zmember>( grid_1[0], 50.0 );
  Utility::set<zmember>( grid_1[1], 5.0 );
  Utility::set<zmember>( grid_1[2], 0.5 );

  double z =
    Utility::LogLogCosLog::interpolate<ymember,zmember>(x0,
                                                        x1,
                                                        x,
                                                        y,
                                                        grid_0.begin(),
                                                        grid_0.end(),
                                                        grid_1.begin(),
                                                        grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

  x = 0.1;

  z = Utility::LogLogCosLog::interpolate<ymember,zmember>( x0,
                                                           x1,
                                                           x,
                                                           y,
                                                           grid_0.begin(),
                                                           grid_0.end(),
                                                           grid_1.begin(),
                                                           grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

  x = 1.0;

  z = Utility::LogLogCosLog::interpolate<ymember,zmember>( x0,
                                                           x1,
                                                           x,
                                                           y,
                                                           grid_0.begin(),
                                                           grid_0.end(),
                                                           grid_1.begin(),
                                                           grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST( LogLogCosLog_false, interpolate_no_tuple_grids )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;
  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = -1.0;
  y_0_grid[1] = 0.0;
  y_0_grid[2] = 0.5;
  y_0_grid[3] = 0.999999;

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = 100.0;
  z_0_grid[1] = 0.1;
  z_0_grid[2] = 1.0;
  z_0_grid[3] = 10.0;

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = -1.0;
  y_1_grid[1] = 0.0;
  y_1_grid[2] = 0.999999;

  std::vector<double> z_1_grid( 3 );
  z_1_grid[0] = 50.0;
  z_1_grid[1] = 5.0;
  z_1_grid[2] = 0.5;

  double z = Utility::LogLogCosLog::interpolate( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

  x = 0.1;

  z = Utility::LogLogCosLog::interpolate( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

  x = 1.0;

  z = Utility::LogLogCosLog::interpolate( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
FRENSIE_UNIT_TEST( LogLogCosLog_false, calculateIntermediateGridLength )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3;
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LogLogCosLog::calculateIntermediateGridLength(
                                                           x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.9542425094393248, 1e-15 );

  x = 0.1;

  Lx = Utility::LogLogCosLog::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = 1.0;

  Lx = Utility::LogLogCosLog::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
FRENSIE_UNIT_TEST( LogLogCosLog_false, calculateIntermediateGridLimit )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3;
  double y0_min = -1.0, y1_min = -1.0;

  double yx_min = Utility::LogLogCosLog::calculateIntermediateGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, -1.0, 1e-15 );

  x = 0.1;

  yx_min = Utility::LogLogCosLog::calculateIntermediateGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, -1.0, 1e-15 );

  x = 1.0;

  yx_min = Utility::LogLogCosLog::calculateIntermediateGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_false,
                                   interpolateUnitBase_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], -1.0 );
  Utility::set<ymember>( y_0_grid[1], 0.0 );
  Utility::set<ymember>( y_0_grid[2], 0.5 );
  Utility::set<ymember>( y_0_grid[3], 0.999999 );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 1e-3 );
  Utility::set<zmember>( z_0_grid[1], 1e-2 );
  Utility::set<zmember>( z_0_grid[2], 1e-1 );
  Utility::set<zmember>( z_0_grid[3], 1.0 );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], -1.0 );
  Utility::set<ymember>( y_1_grid[1], 0.0 );
  Utility::set<ymember>( y_1_grid[2], 0.999999 );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 1e-2 );
  Utility::set<zmember>( z_1_grid[1], 1e-1 );
  Utility::set<zmember>( z_1_grid[2], 1.0 );

  double z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

  y = -1.0; // min possible y at x = 0.3

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  y = 0.999999; // max possible y at x = 0.3

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  y = 0.9;
  x = 0.1;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

  y = -1.0;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  y = 1.0;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  y = 0.9;
  x = 1.0;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

  y = -1.0;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  y = 0.999999;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
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
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_false,
                                   interpolateUnitBase_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], -1.0 );
  Utility::set<ymember>( grid_0[1], 0.0 );
  Utility::set<ymember>( grid_0[2], 0.5 );
  Utility::set<ymember>( grid_0[3], 0.999999 );
  Utility::set<zmember>( grid_0[0], 1e-3 );
  Utility::set<zmember>( grid_0[1], 1e-2 );
  Utility::set<zmember>( grid_0[2], 1e-1 );
  Utility::set<zmember>( grid_0[3], 1.0 );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], -1.0 );
  Utility::set<ymember>( grid_1[1], 0.0 );
  Utility::set<ymember>( grid_1[2], 0.999999 );
  Utility::set<zmember>( grid_1[0], 1e-2 );
  Utility::set<zmember>( grid_1[1], 1e-1 );
  Utility::set<zmember>( grid_1[2], 1.0 );

  double z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

  y = -1.0; // min possible y at x = 0.3

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  y = 0.999999; // max possible y at x = 0.3

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.9;
  x = 0.1;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

  y = -1.0;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

  y = 0.999999;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.9;
  x = 1.0;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

  y = -1.0;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

  y = 0.999999;

  z = Utility::LogLogCosLog::interpolateUnitBase<ymember,zmember>(
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
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST( LogLogCosLog_false, interpolateUnitBase_no_tuple_grids )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = -1.0;
  y_0_grid[1] = 0.0;
  y_0_grid[2] = 0.5;
  y_0_grid[3] = 0.999999;

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = 1e-3;
  z_0_grid[1] = 1e-2;
  z_0_grid[2] = 1e-1;
  z_0_grid[3] = 1.0;

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = -1.0;
  y_1_grid[1] = 0.0;
  y_1_grid[2] = 0.999999;

  std::vector<double> z_1_grid( 3 );
  z_1_grid[0] = 1e-2;
  z_1_grid[1] = 1e-1;
  z_1_grid[2] = 1.0;

  double z = Utility::LogLogCosLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

  y = -1.0; // min possible y at x = 0.3

  z = Utility::LogLogCosLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  y = 0.999999; // max possible y at x = 0.3

  z = Utility::LogLogCosLog::interpolateUnitBase( x0,
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

  y = 0.9;
  x = 0.1;

  z = Utility::LogLogCosLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

  y = -1.0;

  z = Utility::LogLogCosLog::interpolateUnitBase( x0,
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

  y = 0.999999;

  z = Utility::LogLogCosLog::interpolateUnitBase( x0,
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

  y = 0.9;
  x = 1.0;

  z = Utility::LogLogCosLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

  y = -1.0;

  z = Utility::LogLogCosLog::interpolateUnitBase( x0,
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

  y = 0.999999;

  z = Utility::LogLogCosLog::interpolateUnitBase( x0,
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
FRENSIE_UNIT_TEST( LogLogCosLog_false, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(0.1),
                          Utility::LogLogCosLog::processDepVar(0.1),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(1.0),
                          Utility::LogLogCosLog::processDepVar( 1.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogLogCosLog_false, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.1,
                          Utility::LogLogCosLog::recoverProcessedDepVar(std::log(0.1)),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                          Utility::LogLogCosLog::recoverProcessedDepVar(std::log(1.0)),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the second independent variable can be processed
FRENSIE_UNIT_TEST( LogLogCosLog_false, processSecondIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(2.0),
                          Utility::LogLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(1.0-0.999999),
                          Utility::LogLogCosLog::processSecondIndepVar(0.999999),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed second independent variable can be recovered
FRENSIE_UNIT_TEST( LogLogCosLog_false, recoverProcessedSecondIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
                  -1.0,
                  Utility::LogLogCosLog::recoverProcessedSecondIndepVar(std::log(2.0)),
                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                  0.999999,
                  Utility::LogLogCosLog::recoverProcessedSecondIndepVar(std::log(1.0-0.999999)),
                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the first independent variable can be processed
FRENSIE_UNIT_TEST( LogLogCosLog_false, processFirstIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(0.1),
                          Utility::LogLogCosLog::processFirstIndepVar(0.1),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(1.0),
                          Utility::LogLogCosLog::processFirstIndepVar(1.0),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed first independent variable can be processed
FRENSIE_UNIT_TEST( LogLogCosLog_false, recoverProcessedFirstIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
                  0.1,
                  Utility::LogLogCosLog::recoverProcessedFirstIndepVar(std::log(0.1)),
                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                  1.0,
                  Utility::LogLogCosLog::recoverProcessedFirstIndepVar(std::log(1.0)),
                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_false,
                                   interpolateProcessed_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[3],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_0_grid[2],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( y_0_grid[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.5) );
  Utility::set<ymember>( y_0_grid[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[3],
                         Utility::LogLogCosLog::processDepVar(100.0) );
  Utility::set<zmember>( z_0_grid[2],
                         Utility::LogLogCosLog::processDepVar(0.1) );
  Utility::set<zmember>( z_0_grid[1],
                         Utility::LogLogCosLog::processDepVar(1.0) );
  Utility::set<zmember>( z_0_grid[0],
                         Utility::LogLogCosLog::processDepVar(10.0) );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[2],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_1_grid[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( y_1_grid[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[2],
                         Utility::LogLogCosLog::processDepVar(50.0) );
  Utility::set<zmember>( z_1_grid[1],
                         Utility::LogLogCosLog::processDepVar(5.0) );
  Utility::set<zmember>( z_1_grid[0],
                         Utility::LogLogCosLog::processDepVar(0.5) );

  double z = Utility::LogLogCosLog::interpolateProcessed<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

  x = Utility::LogLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogLogCosLog::interpolateProcessed<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

  x = Utility::LogLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogLogCosLog::interpolateProcessed<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_false,
                                   interpolateProcessed_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[3],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( grid_0[2],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( grid_0[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.5) );
  Utility::set<ymember>( grid_0[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<zmember>( grid_0[3],
                         Utility::LogLogCosLog::processDepVar(100.0) );
  Utility::set<zmember>( grid_0[2],
                         Utility::LogLogCosLog::processDepVar(0.1) );
  Utility::set<zmember>( grid_0[1],
                         Utility::LogLogCosLog::processDepVar(1.0) );
  Utility::set<zmember>( grid_0[0],
                         Utility::LogLogCosLog::processDepVar(10.0) );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[2],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( grid_1[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( grid_1[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<zmember>( grid_1[2],
                         Utility::LogLogCosLog::processDepVar(50.0) );
  Utility::set<zmember>( grid_1[1],
                         Utility::LogLogCosLog::processDepVar(5.0) );
  Utility::set<zmember>( grid_1[0],
                         Utility::LogLogCosLog::processDepVar(0.5) );

  double z = Utility::LogLogCosLog::interpolateProcessed<ymember,zmember>(
                                                        x0,
                                                        x1,
                                                        x,
                                                        y,
                                                        grid_0.begin(),
                                                        grid_0.end(),
                                                        grid_1.begin(),
                                                        grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

  x = Utility::LogLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogLogCosLog::interpolateProcessed<ymember,zmember>(
                                                        x0,
                                                        x1,
                                                        x,
                                                        y,
                                                        grid_0.begin(),
                                                        grid_0.end(),
                                                        grid_1.begin(),
                                                        grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

  x = Utility::LogLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogLogCosLog::interpolateProcessed<ymember,zmember>(
                                                        x0,
                                                        x1,
                                                        x,
                                                        y,
                                                        grid_0.begin(),
                                                        grid_0.end(),
                                                        grid_1.begin(),
                                                        grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST( LogLogCosLog_false, interpolateProcessed_no_tuple_grids )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);

  std::vector<double> y_0_grid( 4 );
  y_0_grid[3] = Utility::LogLogCosLog::processSecondIndepVar(-1.0);
  y_0_grid[2] = Utility::LogLogCosLog::processSecondIndepVar(0.0);
  y_0_grid[1] = Utility::LogLogCosLog::processSecondIndepVar(0.5);
  y_0_grid[0] = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  std::vector<double> z_0_grid( 4 );
  z_0_grid[3] = Utility::LogLogCosLog::processDepVar(100.0);
  z_0_grid[2] = Utility::LogLogCosLog::processDepVar(0.1);
  z_0_grid[1] = Utility::LogLogCosLog::processDepVar(1.0);
  z_0_grid[0] = Utility::LogLogCosLog::processDepVar(10.0);

  std::vector<double> y_1_grid( 3 );
  y_1_grid[2] = Utility::LogLogCosLog::processSecondIndepVar(-1.0);
  y_1_grid[1] = Utility::LogLogCosLog::processSecondIndepVar(0.0);
  y_1_grid[0] = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  std::vector<double> z_1_grid( 3 );
  z_1_grid[2] = Utility::LogLogCosLog::processDepVar(50.0);
  z_1_grid[1] = Utility::LogLogCosLog::processDepVar(5.0);
  z_1_grid[0] = Utility::LogLogCosLog::processDepVar(0.5);

  double z = Utility::LogLogCosLog::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

  x = Utility::LogLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogLogCosLog::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

  x = Utility::LogLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogLogCosLog::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
FRENSIE_UNIT_TEST( LogLogCosLog_false, calculateIntermediateGridLengthProcessed )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LogLogCosLog::calculateIntermediateGridLengthProcessed(
                                                           x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.9542425094393248, 1e-15 );

  x = Utility::LogLogCosLog::processFirstIndepVar(0.1);

  Lx = Utility::LogLogCosLog::calculateIntermediateGridLengthProcessed(
                                                           x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = Utility::LogLogCosLog::processFirstIndepVar(1.0);

  Lx = Utility::LogLogCosLog::calculateIntermediateGridLengthProcessed(
                                                           x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
FRENSIE_UNIT_TEST( LogLogCosLog_false, calculateIntermediateProcessedGridLimit )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y0_min = Utility::LogLogCosLog::processSecondIndepVar(-1.0);
  double y1_min = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  double yx_min = Utility::LogLogCosLog::calculateIntermediateProcessedGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min,
                          Utility::LogLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );

  x = Utility::LogLogCosLog::processFirstIndepVar(0.1);

  yx_min = Utility::LogLogCosLog::calculateIntermediateProcessedGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min,
                          Utility::LogLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );

  x = Utility::LogLogCosLog::processFirstIndepVar(1.0);

  yx_min = Utility::LogLogCosLog::calculateIntermediateProcessedGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min,
                          Utility::LogLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                             LogLogCosLog_false,
                             interpolateProcessedUnitBase_separate_tuple_grids,
                             TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);
  double fuzzy_tol = 1e-4;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[3],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_0_grid[2],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( y_0_grid[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.5) );
  Utility::set<ymember>( y_0_grid[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[3],
                         Utility::LogLogCosLog::processDepVar(1e-3) );
  Utility::set<zmember>( z_0_grid[2],
                         Utility::LogLogCosLog::processDepVar(1e-2) );
  Utility::set<zmember>( z_0_grid[1],
                         Utility::LogLogCosLog::processDepVar(1e-1) );
  Utility::set<zmember>( z_0_grid[0],
                         Utility::LogLogCosLog::processDepVar(1.0) );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[2],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_1_grid[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( y_1_grid[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[2],
                         Utility::LogLogCosLog::processDepVar(1e-2) );
  Utility::set<zmember>( z_1_grid[1],
                         Utility::LogLogCosLog::processDepVar(1e-1) );
  Utility::set<zmember>( z_1_grid[0],
                         Utility::LogLogCosLog::processDepVar(1.0) );

  double z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

  // max possible processed y at x = 0.3
  y = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  // max possible processed y + fuzzy bound at x = 0.3
  y = Utility::LogLogCosLog::processSecondIndepVar(-1.0)*(1.0 + fuzzy_tol);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  // min possible processed y at x = 0.3
  y = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LogLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

  y = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LogLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

  y = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                             LogLogCosLog_false,
                             interpolateProcessedUnitBase_combined_tuple_grids,
                             TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[3],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( grid_0[2],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( grid_0[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.5) );
  Utility::set<ymember>( grid_0[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<zmember>( grid_0[3],
                         Utility::LogLogCosLog::processDepVar(1e-3) );
  Utility::set<zmember>( grid_0[2],
                         Utility::LogLogCosLog::processDepVar(1e-2) );
  Utility::set<zmember>( grid_0[1],
                         Utility::LogLogCosLog::processDepVar(1e-1) );
  Utility::set<zmember>( grid_0[0],
                         Utility::LogLogCosLog::processDepVar(1.0) );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[2],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( grid_1[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( grid_1[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<zmember>( grid_1[2],
                         Utility::LogLogCosLog::processDepVar(1e-2) );
  Utility::set<zmember>( grid_1[1],
                         Utility::LogLogCosLog::processDepVar(1e-1) );
  Utility::set<zmember>( grid_1[0],
                         Utility::LogLogCosLog::processDepVar(1.0) );

  double z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

  // min possible y at x = 0.3
  y = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  // max possible y at x = 0.3
  y = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = Utility::LogLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

  y = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

  y = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = Utility::LogLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

  y = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

  y = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST( LogLogCosLog_false, interpolateProcessedUnitBase_no_tuple_grids )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);

  std::vector<double> y_0_grid( 4 );
  y_0_grid[3] = Utility::LogLogCosLog::processSecondIndepVar(-1.0);
  y_0_grid[2] = Utility::LogLogCosLog::processSecondIndepVar(0.0);
  y_0_grid[1] = Utility::LogLogCosLog::processSecondIndepVar(0.5);
  y_0_grid[0] = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  std::vector<double> z_0_grid( 4 );
  z_0_grid[3] = Utility::LogLogCosLog::processDepVar(1e-3);
  z_0_grid[2] = Utility::LogLogCosLog::processDepVar(1e-2);
  z_0_grid[1] = Utility::LogLogCosLog::processDepVar(1e-1);
  z_0_grid[0] = Utility::LogLogCosLog::processDepVar(1.0);

  std::vector<double> y_1_grid( 3 );
  y_1_grid[2] = Utility::LogLogCosLog::processSecondIndepVar(-1.0);
  y_1_grid[1] = Utility::LogLogCosLog::processSecondIndepVar(0.0);
  y_1_grid[0] = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  std::vector<double> z_1_grid( 3 );
  z_1_grid[2] = Utility::LogLogCosLog::processDepVar(1e-2);
  z_1_grid[1] = Utility::LogLogCosLog::processDepVar(1e-1);
  z_1_grid[0] = Utility::LogLogCosLog::processDepVar(1.0);

  double z = Utility::LogLogCosLog::interpolateProcessedUnitBase(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

  // min possible y at x = 0.3
  y = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  // max possible y at x = 0.5
  y = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase( x0,
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

  y = Utility::LogLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

  y = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase( x0,
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

  y = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase( x0,
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

  y = Utility::LogLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

  y = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase( x0,
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

  y = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  z = Utility::LogLogCosLog::interpolateProcessedUnitBase( x0,
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
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_true,
                                   interpolate_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], -1.0 );
  Utility::set<ymember>( y_0_grid[1], 0.0 );
  Utility::set<ymember>( y_0_grid[2], 0.999999 );
  Utility::set<ymember>( y_0_grid[3], 1.0 );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 100.0 );
  Utility::set<zmember>( z_0_grid[1], 0.1 );
  Utility::set<zmember>( z_0_grid[2], 1.0 );
  Utility::set<zmember>( z_0_grid[3], 10.0 );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], -1.0 );
  Utility::set<ymember>( y_1_grid[1], 0.999999 );
  Utility::set<ymember>( y_1_grid[2], 1.0 );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 50.0 );
  Utility::set<zmember>( z_1_grid[1], 5.0 );
  Utility::set<zmember>( z_1_grid[2], 0.5 );

  double z =
    Utility::LogNudgedLogCosLog::interpolate<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.8895869164792762, 1e-12 );

  x = 0.1;

  z = Utility::LogNudgedLogCosLog::interpolate<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505051e-01, 1e-12 );

  x = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolate<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.1080617677478831e+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_true,
                                   interpolate_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], -1.0 );
  Utility::set<ymember>( grid_0[1], 0.0 );
  Utility::set<ymember>( grid_0[2], 0.999999 );
  Utility::set<ymember>( grid_0[3], 1.0 );
  Utility::set<zmember>( grid_0[0], 100.0 );
  Utility::set<zmember>( grid_0[1], 0.1 );
  Utility::set<zmember>( grid_0[2], 1.0 );
  Utility::set<zmember>( grid_0[3], 10.0 );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], -1.0 );
  Utility::set<ymember>( grid_1[1], 0.999999 );
  Utility::set<ymember>( grid_1[2], 1.0 );
  Utility::set<zmember>( grid_1[0], 50.0 );
  Utility::set<zmember>( grid_1[1], 5.0 );
  Utility::set<zmember>( grid_1[2], 0.5 );

  double z =
    Utility::LogNudgedLogCosLog::interpolate<ymember,zmember>(x0,
                                                        x1,
                                                        x,
                                                        y,
                                                        grid_0.begin(),
                                                        grid_0.end(),
                                                        grid_1.begin(),
                                                        grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.8895869164792762, 1e-12 );

  x = 0.1;

  z = Utility::LogNudgedLogCosLog::interpolate<ymember,zmember>( x0,
                                                           x1,
                                                           x,
                                                           y,
                                                           grid_0.begin(),
                                                           grid_0.end(),
                                                           grid_1.begin(),
                                                           grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505051e-01, 1e-12 );

  x = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolate<ymember,zmember>( x0,
                                                           x1,
                                                           x,
                                                           y,
                                                           grid_0.begin(),
                                                           grid_0.end(),
                                                           grid_1.begin(),
                                                           grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.1080617677478831e+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST( LogLogCosLog_true, interpolate_no_tuple_grids )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;
  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = -1.0;
  y_0_grid[1] = 0.0;
  y_0_grid[2] = 0.999999;
  y_0_grid[3] = 1.0;

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = 100.0;
  z_0_grid[1] = 0.1;
  z_0_grid[2] = 1.0;
  z_0_grid[3] = 10.0;

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = -1.0;
  y_1_grid[1] = 0.999999;
  y_1_grid[2] = 1.0;

  std::vector<double> z_1_grid( 3 );
  z_1_grid[0] = 50.0;
  z_1_grid[1] = 5.0;
  z_1_grid[2] = 0.5;

  double z = Utility::LogNudgedLogCosLog::interpolate( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.8895869164792762, 1e-12 );

  x = 0.1;

  z = Utility::LogNudgedLogCosLog::interpolate( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505051e-01, 1e-12 );

  x = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolate( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.1080617677478831e+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
FRENSIE_UNIT_TEST( LogLogCosLog_true, calculateIntermediateGridLength )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3;
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LogNudgedLogCosLog::calculateIntermediateGridLength(
                                                           x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.9542425094393248, 1e-15 );

  x = 0.1;

  Lx = Utility::LogNudgedLogCosLog::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = 1.0;

  Lx = Utility::LogNudgedLogCosLog::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
FRENSIE_UNIT_TEST( LogLogCosLog_true, calculateIntermediateGridLimit )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3;
  double y0_min = -1.0, y1_min = -1.0;

  double yx_min = Utility::LogNudgedLogCosLog::calculateIntermediateGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, -1.0, 1e-15 );

  x = 0.1;

  yx_min = Utility::LogNudgedLogCosLog::calculateIntermediateGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, -1.0, 1e-15 );

  x = 1.0;

  yx_min = Utility::LogNudgedLogCosLog::calculateIntermediateGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_true,
                                   interpolateUnitBase_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], -1.0 );
  Utility::set<ymember>( y_0_grid[1], 0.0 );
  Utility::set<ymember>( y_0_grid[2], 0.999999 );
  Utility::set<ymember>( y_0_grid[3], 1.0 );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 1e-3 );
  Utility::set<zmember>( z_0_grid[1], 1e-2 );
  Utility::set<zmember>( z_0_grid[2], 1e-1 );
  Utility::set<zmember>( z_0_grid[3], 1.0 );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], -1.0 );
  Utility::set<ymember>( y_1_grid[1], 0.999999 );
  Utility::set<ymember>( y_1_grid[2], 1.0 );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 1e-2 );
  Utility::set<zmember>( z_1_grid[1], 1e-1 );
  Utility::set<zmember>( z_1_grid[2], 1.0 );

  double z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.5334275379752840e-02, 1e-12 );

  y = -1.0; // min possible y at x = 0.3

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  y = 1.0; // max possible y at x = 0.3

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  y = 0.9;
  x = 0.1;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505061e-02, 1e-12 );

  y = -1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  y = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  y = 0.9;
  x = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.6087196373909353e-02, 1e-12 );

  y = -1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
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

  y = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
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
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_true,
                                   interpolateUnitBase_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], -1.0 );
  Utility::set<ymember>( grid_0[1], 0.0 );
  Utility::set<ymember>( grid_0[2], 0.999999 );
  Utility::set<ymember>( grid_0[3], 1.0 );
  Utility::set<zmember>( grid_0[0], 1e-3 );
  Utility::set<zmember>( grid_0[1], 1e-2 );
  Utility::set<zmember>( grid_0[2], 1e-1 );
  Utility::set<zmember>( grid_0[3], 1.0 );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], -1.0 );
  Utility::set<ymember>( grid_1[1], 0.999999 );
  Utility::set<ymember>( grid_1[2], 1.0 );
  Utility::set<zmember>( grid_1[0], 1e-2 );
  Utility::set<zmember>( grid_1[1], 1e-1 );
  Utility::set<zmember>( grid_1[2], 1.0 );

  double z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.5334275379752840e-02, 1e-12 );

  y = -1.0; // min possible y at x = 0.3

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  y = 1.0; // max possible y at x = 0.3

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.9;
  x = 0.1;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505061e-02, 1e-12 );

  y = -1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

  y = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 0.9;
  x = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.6087196373909353e-02, 1e-12 );

  y = -1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

  y = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase<ymember,zmember>(
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
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST( LogLogCosLog_true, interpolateUnitBase_no_tuple_grids )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = -1.0;
  y_0_grid[1] = 0.0;
  y_0_grid[2] = 0.999999;
  y_0_grid[3] = 1.0;

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = 1e-3;
  z_0_grid[1] = 1e-2;
  z_0_grid[2] = 1e-1;
  z_0_grid[3] = 1.0;

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = -1.0;
  y_1_grid[1] = 0.999999;
  y_1_grid[2] = 1.0;

  std::vector<double> z_1_grid( 3 );
  z_1_grid[0] = 1e-2;
  z_1_grid[1] = 1e-1;
  z_1_grid[2] = 1.0;

  double z = Utility::LogNudgedLogCosLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.5334275379752840e-02, 1e-12 );

  y = -1.0; // min possible y at x = 0.3

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  y = 1.0; // max possible y at x = 0.3

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase( x0,
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

  y = 0.9;
  x = 0.1;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505061e-02, 1e-12 );

  y = -1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase( x0,
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

  y = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase( x0,
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

  y = 0.9;
  x = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.6087196373909353e-02, 1e-12 );

  y = -1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase( x0,
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

  y = 1.0;

  z = Utility::LogNudgedLogCosLog::interpolateUnitBase( x0,
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
FRENSIE_UNIT_TEST( LogLogCosLog_true, processDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(0.1),
                          Utility::LogNudgedLogCosLog::processDepVar(0.1),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(1.0),
                          Utility::LogNudgedLogCosLog::processDepVar( 1.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LogLogCosLog_true, recoverProcessedDepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 0.1,
                          Utility::LogNudgedLogCosLog::recoverProcessedDepVar(std::log(0.1)),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0,
                          Utility::LogNudgedLogCosLog::recoverProcessedDepVar(std::log(1.0)),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the second independent variable can be processed
FRENSIE_UNIT_TEST( LogLogCosLog_true, processSecondIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(2.0 + delta),
                          Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(delta),
                          Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed second independent variable can be recovered
FRENSIE_UNIT_TEST( LogLogCosLog_true, recoverProcessedSecondIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
                  -1.0,
                  Utility::LogNudgedLogCosLog::recoverProcessedSecondIndepVar(std::log(2.0+delta)),
                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                  1.0,
                  Utility::LogNudgedLogCosLog::recoverProcessedSecondIndepVar(std::log(delta)),
                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the first independent variable can be processed
FRENSIE_UNIT_TEST( LogLogCosLog_true, processFirstIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(0.1),
                          Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1),
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(1.0),
                          Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed first independent variable can be processed
FRENSIE_UNIT_TEST( LogLogCosLog_true, recoverProcessedFirstIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
                  0.1,
                  Utility::LogNudgedLogCosLog::recoverProcessedFirstIndepVar(std::log(0.1)),
                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                  1.0,
                  Utility::LogNudgedLogCosLog::recoverProcessedFirstIndepVar(std::log(1.0)),
                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_true,
                                   interpolateProcessed_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[3],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_0_grid[2],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( y_0_grid[1],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<ymember>( y_0_grid[0],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0) );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[3],
                         Utility::LogNudgedLogCosLog::processDepVar(100.0) );
  Utility::set<zmember>( z_0_grid[2],
                         Utility::LogNudgedLogCosLog::processDepVar(0.1) );
  Utility::set<zmember>( z_0_grid[1],
                         Utility::LogNudgedLogCosLog::processDepVar(1.0) );
  Utility::set<zmember>( z_0_grid[0],
                         Utility::LogNudgedLogCosLog::processDepVar(10.0) );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[2],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_1_grid[1],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<ymember>( y_1_grid[0],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0) );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[2],
                         Utility::LogNudgedLogCosLog::processDepVar(50.0) );
  Utility::set<zmember>( z_1_grid[1],
                         Utility::LogNudgedLogCosLog::processDepVar(5.0) );
  Utility::set<zmember>( z_1_grid[0],
                         Utility::LogNudgedLogCosLog::processDepVar(0.5) );

  double z = Utility::LogNudgedLogCosLog::interpolateProcessed<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.8895869164792762, 1e-12 );

  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogNudgedLogCosLog::interpolateProcessed<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505051e-01, 1e-12 );

  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessed<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.1080617677478831e+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LogLogCosLog_true,
                                   interpolateProcessed_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[3],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( grid_0[2],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( grid_0[1],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<ymember>( grid_0[0],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_0[3],
                         Utility::LogNudgedLogCosLog::processDepVar(100.0) );
  Utility::set<zmember>( grid_0[2],
                         Utility::LogNudgedLogCosLog::processDepVar(0.1) );
  Utility::set<zmember>( grid_0[1],
                         Utility::LogNudgedLogCosLog::processDepVar(1.0) );
  Utility::set<zmember>( grid_0[0],
                         Utility::LogNudgedLogCosLog::processDepVar(10.0) );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[2],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( grid_1[1],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<ymember>( grid_1[0],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_1[2],
                         Utility::LogNudgedLogCosLog::processDepVar(50.0) );
  Utility::set<zmember>( grid_1[1],
                         Utility::LogNudgedLogCosLog::processDepVar(5.0) );
  Utility::set<zmember>( grid_1[0],
                         Utility::LogNudgedLogCosLog::processDepVar(0.5) );

  double z = Utility::LogNudgedLogCosLog::interpolateProcessed<ymember,zmember>(
                                                        x0,
                                                        x1,
                                                        x,
                                                        y,
                                                        grid_0.begin(),
                                                        grid_0.end(),
                                                        grid_1.begin(),
                                                        grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.8895869164792762, 1e-12 );

  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogNudgedLogCosLog::interpolateProcessed<ymember,zmember>(
                                                        x0,
                                                        x1,
                                                        x,
                                                        y,
                                                        grid_0.begin(),
                                                        grid_0.end(),
                                                        grid_1.begin(),
                                                        grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505051e-01, 1e-12 );

  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessed<ymember,zmember>(
                                                        x0,
                                                        x1,
                                                        x,
                                                        y,
                                                        grid_0.begin(),
                                                        grid_0.end(),
                                                        grid_1.begin(),
                                                        grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.1080617677478831e+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST( LogLogCosLog_true, interpolateProcessed_no_tuple_grids )
{
  double x0 = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);

  std::vector<double> y_0_grid( 4 );
  y_0_grid[3] = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);
  y_0_grid[2] = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.0);
  y_0_grid[1] = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999);
  y_0_grid[0] = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  std::vector<double> z_0_grid( 4 );
  z_0_grid[3] = Utility::LogNudgedLogCosLog::processDepVar(100.0);
  z_0_grid[2] = Utility::LogNudgedLogCosLog::processDepVar(0.1);
  z_0_grid[1] = Utility::LogNudgedLogCosLog::processDepVar(1.0);
  z_0_grid[0] = Utility::LogNudgedLogCosLog::processDepVar(10.0);

  std::vector<double> y_1_grid( 3 );
  y_1_grid[2] = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);
  y_1_grid[1] = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999);
  y_1_grid[0] = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  std::vector<double> z_1_grid( 3 );
  z_1_grid[2] = Utility::LogNudgedLogCosLog::processDepVar(50.0);
  z_1_grid[1] = Utility::LogNudgedLogCosLog::processDepVar(5.0);
  z_1_grid[0] = Utility::LogNudgedLogCosLog::processDepVar(0.5);

  double z = Utility::LogNudgedLogCosLog::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.8895869164792762, 1e-12 );

  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogNudgedLogCosLog::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505051e-01, 1e-12 );

  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.1080617677478831e+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
FRENSIE_UNIT_TEST( LogLogCosLog_true, calculateIntermediateGridLengthProcessed )
{
  double x0 = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.3);
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LogNudgedLogCosLog::calculateIntermediateGridLengthProcessed(
                                                           x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.9542425094393248, 1e-15 );

  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);

  Lx = Utility::LogNudgedLogCosLog::calculateIntermediateGridLengthProcessed(
                                                           x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);

  Lx = Utility::LogNudgedLogCosLog::calculateIntermediateGridLengthProcessed(
                                                           x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
FRENSIE_UNIT_TEST( LogLogCosLog_true, calculateIntermediateProcessedGridLimit )
{
  double x0 = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.3);
  double y0_min = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);
  double y1_min = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);

  double yx_min = Utility::LogNudgedLogCosLog::calculateIntermediateProcessedGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min,
                          Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );

  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);

  yx_min = Utility::LogNudgedLogCosLog::calculateIntermediateProcessedGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min,
                          Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );

  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);

  yx_min = Utility::LogNudgedLogCosLog::calculateIntermediateProcessedGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min,
                          Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                             LogLogCosLog_true,
                             interpolateProcessedUnitBase_separate_tuple_grids,
                             TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);
  double fuzzy_tol = 1e-4;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[3],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_0_grid[2],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( y_0_grid[1],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<ymember>( y_0_grid[0],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0) );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[3],
                         Utility::LogNudgedLogCosLog::processDepVar(1e-3) );
  Utility::set<zmember>( z_0_grid[2],
                         Utility::LogNudgedLogCosLog::processDepVar(1e-2) );
  Utility::set<zmember>( z_0_grid[1],
                         Utility::LogNudgedLogCosLog::processDepVar(1e-1) );
  Utility::set<zmember>( z_0_grid[0],
                         Utility::LogNudgedLogCosLog::processDepVar(1.0) );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[2],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_1_grid[1],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<ymember>( y_1_grid[0],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0) );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[2],
                         Utility::LogNudgedLogCosLog::processDepVar(1e-2) );
  Utility::set<zmember>( z_1_grid[1],
                         Utility::LogNudgedLogCosLog::processDepVar(1e-1) );
  Utility::set<zmember>( z_1_grid[0],
                         Utility::LogNudgedLogCosLog::processDepVar(1.0) );

  double z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.5334275379752840e-02, 1e-12 );

  // max possible processed y at x = 0.3
  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  // max possible processed y + fuzzy bound at x = 0.3
  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0)*(1.0 + fuzzy_tol);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  // min possible processed y at x = 0.3
  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505061e-02, 1e-12 );

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.6087196373909353e-02, 1e-12 );

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                             LogLogCosLog_true,
                             interpolateProcessedUnitBase_combined_tuple_grids,
                             TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;

  double x0 = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[3],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( grid_0[2],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( grid_0[1],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<ymember>( grid_0[0],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_0[3],
                         Utility::LogNudgedLogCosLog::processDepVar(1e-3) );
  Utility::set<zmember>( grid_0[2],
                         Utility::LogNudgedLogCosLog::processDepVar(1e-2) );
  Utility::set<zmember>( grid_0[1],
                         Utility::LogNudgedLogCosLog::processDepVar(1e-1) );
  Utility::set<zmember>( grid_0[0],
                         Utility::LogNudgedLogCosLog::processDepVar(1.0) );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[2],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( grid_1[1],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999) );
  Utility::set<ymember>( grid_1[0],
                         Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_1[2],
                         Utility::LogNudgedLogCosLog::processDepVar(1e-2) );
  Utility::set<zmember>( grid_1[1],
                         Utility::LogNudgedLogCosLog::processDepVar(1e-1) );
  Utility::set<zmember>( grid_1[0],
                         Utility::LogNudgedLogCosLog::processDepVar(1.0) );

  double z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.5334275379752840e-02, 1e-12 );

  // min possible y at x = 0.3
  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  // max possible y at x = 0.3
  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505061e-02, 1e-12 );

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.6087196373909353e-02, 1e-12 );

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
                                                              x0,
                                                              x1,
                                                              x,
                                                              y,
                                                              grid_0.begin(),
                                                              grid_0.end(),
                                                              grid_1.begin(),
                                                              grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase<ymember,zmember>(
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
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST( LogLogCosLog_true, interpolateProcessedUnitBase_no_tuple_grids )
{
  double x0 = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);

  std::vector<double> y_0_grid( 4 );
  y_0_grid[3] = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);
  y_0_grid[2] = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.0);
  y_0_grid[1] = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999);
  y_0_grid[0] = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  std::vector<double> z_0_grid( 4 );
  z_0_grid[3] = Utility::LogNudgedLogCosLog::processDepVar(1e-3);
  z_0_grid[2] = Utility::LogNudgedLogCosLog::processDepVar(1e-2);
  z_0_grid[1] = Utility::LogNudgedLogCosLog::processDepVar(1e-1);
  z_0_grid[0] = Utility::LogNudgedLogCosLog::processDepVar(1.0);

  std::vector<double> y_1_grid( 3 );
  y_1_grid[2] = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);
  y_1_grid[1] = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.999999);
  y_1_grid[0] = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  std::vector<double> z_1_grid( 3 );
  z_1_grid[2] = Utility::LogNudgedLogCosLog::processDepVar(1e-2);
  z_1_grid[1] = Utility::LogNudgedLogCosLog::processDepVar(1e-1);
  z_1_grid[0] = Utility::LogNudgedLogCosLog::processDepVar(1.0);

  double z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.5334275379752840e-02, 1e-12 );

  // min possible y at x = 0.3
  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

  // max possible y at x = 0.5
  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase( x0,
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

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(0.1);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4678033444505061e-02, 1e-12 );

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase( x0,
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

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase( x0,
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

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(0.9);
  x = Utility::LogNudgedLogCosLog::processFirstIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.6087196373909353e-02, 1e-12 );

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(-1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase( x0,
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

  y = Utility::LogNudgedLogCosLog::processSecondIndepVar(1.0);

  z = Utility::LogNudgedLogCosLog::interpolateProcessedUnitBase( x0,
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
// end tstLogLogCosLogTwoDInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
