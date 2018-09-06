//---------------------------------------------------------------------------//
//!
//! \file   tstLinLogLinTwoDInterpolationPolicy.cpp
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
// Check that the linear-log-linear interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LinLogLin,
                                   interpolate_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 3e-2;
  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], 1e-3 );
  Utility::set<ymember>( y_0_grid[1], 1e-2 );
  Utility::set<ymember>( y_0_grid[2], 1e-1 );
  Utility::set<ymember>( y_0_grid[3], 1.0 );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 100.0 );
  Utility::set<zmember>( z_0_grid[1], 0.0 );
  Utility::set<zmember>( z_0_grid[2], 1.0 );
  Utility::set<zmember>( z_0_grid[3], 10.0 );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], 1e-3 );
  Utility::set<ymember>( y_1_grid[1], 1e-1 );
  Utility::set<ymember>( y_1_grid[2], 1.0 );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 50.0 );
  Utility::set<zmember>( z_1_grid[1], 10.0 );
  Utility::set<zmember>( z_1_grid[2], 5.0 );

  double z = Utility::LinLogLin::interpolate<ymember,zmember>(x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

  x = 0.0;

  z = Utility::LinLogLin::interpolate<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

  x = 1.0;

  z = Utility::LinLogLin::interpolate<ymember,zmember>( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LinLogLin,
                                   interpolate_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 3e-2;
  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], 1e-3 );
  Utility::set<ymember>( grid_0[1], 1e-2 );
  Utility::set<ymember>( grid_0[2], 1e-1 );
  Utility::set<ymember>( grid_0[3], 1.0 );
  Utility::set<zmember>( grid_0[0], 100.0 );
  Utility::set<zmember>( grid_0[1], 0.0 );
  Utility::set<zmember>( grid_0[2], 1.0 );
  Utility::set<zmember>( grid_0[3], 10.0 );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], 1e-3 );
  Utility::set<ymember>( grid_1[1], 1e-1 );
  Utility::set<ymember>( grid_1[2], 1.0 );
  Utility::set<zmember>( grid_1[0], 50.0 );
  Utility::set<zmember>( grid_1[1], 10.0 );
  Utility::set<zmember>( grid_1[2], 5.0 );

  double z = Utility::LinLogLin::interpolate<ymember,zmember>( x0,
                                   x1,
                                   x,
                                   y,
                                   grid_0.begin(),
                                   grid_0.end(),
                                   grid_1.begin(),
                                   grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

  x = 0.0;

  z = Utility::LinLogLin::interpolate<ymember,zmember>( x0,
                            x1,
                            x,
                            y,
                            grid_0.begin(),
                            grid_0.end(),
                            grid_1.begin(),
                            grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

  x = 1.0;

  z = Utility::LinLogLin::interpolate<ymember,zmember>( x0,
                            x1,
                            x,
                            y,
                            grid_0.begin(),
                            grid_0.end(),
                            grid_1.begin(),
                            grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST( LinLogLin, interpolate_no_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 3e-2;
  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = 1e-3;
  y_0_grid[1] = 1e-2;
  y_0_grid[2] = 1e-1;
  y_0_grid[3] = 1.0;

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = 100.0;
  z_0_grid[1] = 0.0;
  z_0_grid[2] = 1.0;
  z_0_grid[3] = 10.0;

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = 1e-3;
  y_1_grid[1] = 1e-1;
  y_1_grid[2] = 1.0;

  std::vector<double> z_1_grid( 3 );
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
FRENSIE_UNIT_TEST( LinLogLin, calculateIntermediateGridLength )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LinLogLin::calculateIntermediateGridLength(
                               x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 4.0, 1e-15 );

  x = 0.0;

  Lx = Utility::LinLogLin::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = 1.0;

  Lx = Utility::LinLogLin::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
FRENSIE_UNIT_TEST( LinLogLin, calculateIntermediateGridLimit )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0_min = 1e-3, y1_min = 1e-2;

  double yx_min = Utility::LinLogLin::calculateIntermediateGridLimit(
                           x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, 3.1622776601686e-3, 1e-12 );

  x = 0.0;

  yx_min = Utility::LinLogLin::calculateIntermediateGridLimit(
                           x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, 1e-3, 1e-12 );

  x = 1.0;

  yx_min = Utility::LinLogLin::calculateIntermediateGridLimit(
                           x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min, 1e-2, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LinLogLin,
                                   interpolateUnitBase_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.03;

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], 1e-3 );
  Utility::set<ymember>( y_0_grid[1], 1e-2 );
  Utility::set<ymember>( y_0_grid[2], 1e-1 );
  Utility::set<ymember>( y_0_grid[3], 1.0 );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 0.0 );
  Utility::set<zmember>( z_0_grid[1], 1.0 );
  Utility::set<zmember>( z_0_grid[2], 2.0 );
  Utility::set<zmember>( z_0_grid[3], 3.0 );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], 1e-2 );
  Utility::set<ymember>( y_1_grid[1], 1e-1 );
  Utility::set<ymember>( y_1_grid[2], 1.0 );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 1.0 );
  Utility::set<zmember>( z_1_grid[1], 2.0 );
  Utility::set<zmember>( z_1_grid[2], 3.0 );

  double z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

  y = 0.0031622776601684; // min possible y at x = 0.5

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.4, 1e-12 );

  y = 1.0; // max possible y at x = 0.5

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.03;
  x = 0.0;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-3;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_SMALL( z, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.03;
  x = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-2;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>(
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

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LinLogLin,
                                   interpolateUnitBase_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.03;

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], 1e-3 );
  Utility::set<ymember>( grid_0[1], 1e-2 );
  Utility::set<ymember>( grid_0[2], 1e-1 );
  Utility::set<ymember>( grid_0[3], 1.0 );
  Utility::set<zmember>( grid_0[0], 0.0 );
  Utility::set<zmember>( grid_0[1], 1.0 );
  Utility::set<zmember>( grid_0[2], 2.0 );
  Utility::set<zmember>( grid_0[3], 3.0 );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], 1e-2 );
  Utility::set<ymember>( grid_1[1], 1e-1 );
  Utility::set<ymember>( grid_1[2], 1.0 );
  Utility::set<zmember>( grid_1[0], 1.0 );
  Utility::set<zmember>( grid_1[1], 2.0 );
  Utility::set<zmember>( grid_1[2], 3.0 );

  double z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>(
                                    x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

  y = 0.0031622776601684; // min possible y at x = 0.5

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.4, 1e-12 );

  y = 1.0; // max possible y at x = 0.5

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );


  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.03;
  x = 0.0;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-3;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_SMALL( z, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.03;
  x = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-2;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST( LinLogLin, interpolateUnitBase_no_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.03;

  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = 1e-3;
  y_0_grid[1] = 1e-2;
  y_0_grid[2] = 1e-1;
  y_0_grid[3] = 1.0;

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = 0.0;
  z_0_grid[1] = 1.0;
  z_0_grid[2] = 2.0;
  z_0_grid[3] = 3.0;

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = 1e-2;
  y_1_grid[1] = 1e-1;
  y_1_grid[2] = 1.0;

  std::vector<double> z_1_grid( 3 );
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.4, 1e-12 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

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

  FRENSIE_CHECK_SMALL( z, 1e-12 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the dependent variable can be processed
FRENSIE_UNIT_TEST( LinLogLin, processDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLogLin::processDepVar( -1.0 ) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLogLin::processDepVar( 0.0 ) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLogLin::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
FRENSIE_UNIT_TEST( LinLogLin, recoverProcessedDepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLogLin::recoverProcessedDepVar(-1.0));
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLogLin::recoverProcessedDepVar(0.0) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLogLin::recoverProcessedDepVar(1.0) );
}

//---------------------------------------------------------------------------//
// Check that the second independent variable can be processed
FRENSIE_UNIT_TEST( LinLogLin, processSecondIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(0.1),
			  Utility::LinLogLin::processSecondIndepVar(0.1),
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::log(1.0),
			  Utility::LinLogLin::processSecondIndepVar(1.0),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed second independent variable can be recovered
FRENSIE_UNIT_TEST( LinLogLin, recoverProcessedSecondIndepVar )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
		  0.1,
		  Utility::LinLogLin::recoverProcessedSecondIndepVar(std::log(0.1)),
		  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		  1.0,
		  Utility::LinLogLin::recoverProcessedSecondIndepVar(std::log(1.0)),
		  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the first independent variable can be processed
FRENSIE_UNIT_TEST( LinLogLin, processFirstIndepVar )
{
  FRENSIE_CHECK_EQUAL( -1.0, Utility::LinLogLin::processFirstIndepVar(-1.0) );
  FRENSIE_CHECK_EQUAL( 0.0, Utility::LinLogLin::processFirstIndepVar(0.0) );
  FRENSIE_CHECK_EQUAL( 1.0, Utility::LinLogLin::processFirstIndepVar(1.0) );
}

//---------------------------------------------------------------------------//
// Check that a processed first independent variable can be processed
FRENSIE_UNIT_TEST( LinLogLin, recoverProcessedFirstIndepVar )
{
  FRENSIE_CHECK_EQUAL(
		     -1.0,
		     Utility::LinLogLin::recoverProcessedFirstIndepVar(-1.0) );
  FRENSIE_CHECK_EQUAL(0.0,
		      Utility::LinLogLin::recoverProcessedFirstIndepVar(0.0) );
  FRENSIE_CHECK_EQUAL(1.0,
		      Utility::LinLogLin::recoverProcessedFirstIndepVar(1.0) );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LinLogLin,
                                   interpolateProcessed_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(3e-2);

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0],
             Utility::LinLogLin::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( y_0_grid[1],
             Utility::LinLogLin::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( y_0_grid[2],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_0_grid[3],
             Utility::LinLogLin::processSecondIndepVar(1.0) );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 100.0 );
  Utility::set<zmember>( z_0_grid[1], 0.0 );
  Utility::set<zmember>( z_0_grid[2], 1.0 );
  Utility::set<zmember>( z_0_grid[3], 10.0 );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0],
             Utility::LinLogLin::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( y_1_grid[1],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_1_grid[2],
             Utility::LinLogLin::processSecondIndepVar(1.0) );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 50.0 );
  Utility::set<zmember>( z_1_grid[1], 10.0 );
  Utility::set<zmember>( z_1_grid[2], 5.0 );

  double z = Utility::LinLogLin::interpolateProcessed<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

  x = 0.0;

  z = Utility::LinLogLin::interpolateProcessed<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

  x = 1.0;

  z = Utility::LinLogLin::interpolateProcessed<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LinLogLin,
                                   interpolateProcessed_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(3e-2);

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0],
             Utility::LinLogLin::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( grid_0[1],
             Utility::LinLogLin::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( grid_0[2],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( grid_0[3],
             Utility::LinLogLin::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_0[0], 100.0 );
  Utility::set<zmember>( grid_0[1], 0.0 );
  Utility::set<zmember>( grid_0[2], 1.0 );
  Utility::set<zmember>( grid_0[3], 10.0 );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0],
             Utility::LinLogLin::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( grid_1[1],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( grid_1[2],
             Utility::LinLogLin::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_1[0], 50.0 );
  Utility::set<zmember>( grid_1[1], 10.0 );
  Utility::set<zmember>( grid_1[2], 5.0 );

  double z = Utility::LinLogLin::interpolateProcessed<ymember,zmember>(
                                   x0,
                                   x1,
                                   x,
                                   y,
                                   grid_0.begin(),
                                   grid_0.end(),
                                   grid_1.begin(),
                                   grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

  x = 0.0;

  z = Utility::LinLogLin::interpolateProcessed<ymember,zmember>(
                            x0,
                            x1,
                            x,
                            y,
                            grid_0.begin(),
                            grid_0.end(),
                            grid_1.begin(),
                            grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

  x = 1.0;

  z = Utility::LinLogLin::interpolateProcessed<ymember,zmember>(
                            x0,
                            x1,
                            x,
                            y,
                            grid_0.begin(),
                            grid_0.end(),
                            grid_1.begin(),
                            grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
FRENSIE_UNIT_TEST( LinLogLin, interpolateProcessed_no_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(3e-2);

  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = Utility::LinLogLin::processSecondIndepVar(1e-3);
  y_0_grid[1] = Utility::LinLogLin::processSecondIndepVar(1e-2);
  y_0_grid[2] = Utility::LinLogLin::processSecondIndepVar(1e-1);
  y_0_grid[3] = Utility::LinLogLin::processSecondIndepVar(1.0);

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = 100.0;
  z_0_grid[1] = 0.0;
  z_0_grid[2] = 1.0;
  z_0_grid[3] = 10.0;

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = Utility::LinLogLin::processSecondIndepVar(1e-3);
  y_1_grid[1] = Utility::LinLogLin::processSecondIndepVar(1e-1);
  y_1_grid[2] = Utility::LinLogLin::processSecondIndepVar(1.0);

  std::vector<double> z_1_grid( 3 );
  z_1_grid[0] = 50.0;
  z_1_grid[1] = 10.0;
  z_1_grid[2] = 5.0;

  double z = Utility::LinLogLin::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

  x = 0.0;

  z = Utility::LinLogLin::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

  x = 1.0;

  z = Utility::LinLogLin::interpolateProcessed( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
FRENSIE_UNIT_TEST( LinLogLin, calculateIntermediateGridLengthProcessed )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LinLogLin::calculateIntermediateGridLengthProcessed(
                               x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 4.0, 1e-15 );

  x = 0.0;

  Lx = Utility::LinLogLin::calculateIntermediateGridLengthProcessed(
                               x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = 1.0;

  Lx = Utility::LinLogLin::calculateIntermediateGridLengthProcessed(
                               x0, x1, x, L0, L1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
FRENSIE_UNIT_TEST( LinLogLin, calculateIntermediateProcessedGridLimit )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0_min = Utility::LinLogLin::processSecondIndepVar(1e-3);
  double y1_min = Utility::LinLogLin::processSecondIndepVar(1e-2);

  double yx_min = Utility::LinLogLin::calculateIntermediateProcessedGridLimit(
                           x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		 yx_min,
		 Utility::LinLogLin::processSecondIndepVar(3.1622776601686e-3),
		 1e-12 );

  x = 0.0;

  yx_min = Utility::LinLogLin::calculateIntermediateProcessedGridLimit(
                           x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min,
			  Utility::LinLogLin::processSecondIndepVar(1e-3),
			  1e-12 );

  x = 1.0;

  yx_min = Utility::LinLogLin::calculateIntermediateProcessedGridLimit(
                           x0, x1, x, y0_min, y1_min );

  FRENSIE_CHECK_FLOATING_EQUALITY( yx_min,
			  Utility::LinLogLin::processSecondIndepVar(1e-2),
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LinLogLin,
                                   interpolateProcessedUnitBase_separate_tuple_grids,
                                   TestTwoTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, ytuple );
  FETCH_TEMPLATE_PARAM( 2, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 3, ztuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(0.03);

  std::vector<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0],
             Utility::LinLogLin::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( y_0_grid[1],
             Utility::LinLogLin::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( y_0_grid[2],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_0_grid[3],
             Utility::LinLogLin::processSecondIndepVar(1.0) );

  std::vector<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 0.0 );
  Utility::set<zmember>( z_0_grid[1], 1.0 );
  Utility::set<zmember>( z_0_grid[2], 2.0 );
  Utility::set<zmember>( z_0_grid[3], 3.0 );

  std::vector<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0],
             Utility::LinLogLin::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( y_1_grid[1],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_1_grid[2],
             Utility::LinLogLin::processSecondIndepVar(1.0) );

  std::vector<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 1.0 );
  Utility::set<zmember>( z_1_grid[1], 2.0 );
  Utility::set<zmember>( z_1_grid[2], 3.0 );

  double z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

  // min possible y at x = 0.5
  y = Utility::LinLogLin::processSecondIndepVar(0.0031622776601684);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.4, 1e-12 );

  // max possible y at x = 0.5
  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(0.03);
  x = 0.0;

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1e-3);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_SMALL( z, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(0.03);
  x = 1.0;

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1e-2);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>(
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( LinLogLin,
                                   interpolateProcessedUnitBase_combined_tuple_grids,
                                   TestTupleTwoElementTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedYMember );
  FETCH_TEMPLATE_PARAM( 1, WrappedZMember );
  FETCH_TEMPLATE_PARAM( 2, tuple );

  constexpr const size_t ymember = WrappedYMember::value;
  constexpr const size_t zmember = WrappedZMember::value;
  
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(0.03);

  std::vector<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0],
             Utility::LinLogLin::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( grid_0[1],
             Utility::LinLogLin::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( grid_0[2],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( grid_0[3],
             Utility::LinLogLin::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_0[0], 0.0 );
  Utility::set<zmember>( grid_0[1], 1.0 );
  Utility::set<zmember>( grid_0[2], 2.0 );
  Utility::set<zmember>( grid_0[3], 3.0 );

  std::vector<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0],
             Utility::LinLogLin::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( grid_1[1],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( grid_1[2],
             Utility::LinLogLin::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_1[0], 1.0 );
  Utility::set<zmember>( grid_1[1], 2.0 );
  Utility::set<zmember>( grid_1[2], 3.0 );

  double z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>(
                                    x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

  // min possible y at x = 0.5
  y = Utility::LinLogLin::processSecondIndepVar(0.0031622776601684);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.4, 1e-12 );

  // max possible y at x = 0.5
  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );


  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(0.03);
  x = 0.0;

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1e-3);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_SMALL( z, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(0.03);
  x = 1.0;

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1e-2);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
FRENSIE_UNIT_TEST( LinLogLin, interpolateProcessedUnitBase_no_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(0.03);

  std::vector<double> y_0_grid( 4 );
  y_0_grid[0] = Utility::LinLogLin::processSecondIndepVar(1e-3);
  y_0_grid[1] = Utility::LinLogLin::processSecondIndepVar(1e-2);
  y_0_grid[2] = Utility::LinLogLin::processSecondIndepVar(1e-1);
  y_0_grid[3] = Utility::LinLogLin::processSecondIndepVar(1.0);

  std::vector<double> z_0_grid( 4 );
  z_0_grid[0] = 0.0;
  z_0_grid[1] = 1.0;
  z_0_grid[2] = 2.0;
  z_0_grid[3] = 3.0;

  std::vector<double> y_1_grid( 3 );
  y_1_grid[0] = Utility::LinLogLin::processSecondIndepVar(1e-2);
  y_1_grid[1] = Utility::LinLogLin::processSecondIndepVar(1e-1);
  y_1_grid[2] = Utility::LinLogLin::processSecondIndepVar(1.0);

  std::vector<double> z_1_grid( 3 );
  z_1_grid[0] = 1.0;
  z_1_grid[1] = 2.0;
  z_1_grid[2] = 3.0;

  double z = Utility::LinLogLin::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

  // min possible y at x = 0.5
  y = Utility::LinLogLin::processSecondIndepVar(0.0031622776601684);

  z = Utility::LinLogLin::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 0.4, 1e-12 );

  // max possible y at x = 0.5
  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(0.03);
  x = 0.0;

  z = Utility::LinLogLin::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1e-3);

  z = Utility::LinLogLin::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_SMALL( z, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(0.03);
  x = 1.0;

  z = Utility::LinLogLin::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1e-2);

  z = Utility::LinLogLin::interpolateProcessedUnitBase( x0,
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

  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase( x0,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// end tstLinLogLinTwoDInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
