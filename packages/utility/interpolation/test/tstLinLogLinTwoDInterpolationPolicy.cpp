//---------------------------------------------------------------------------//
//!
//! \file   tstLinLogLinTwoDInterpolationPolicy.cpp
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
// Instantiation macros.
//---------------------------------------------------------------------------//
#define TUPLE_TYPEDEFS()                    \
  typedef Utility::Pair<double,double> pair_d_d;            \
  typedef Utility::Pair<unsigned,double> pair_u_d;            \
  typedef Utility::Pair<double,unsigned> pair_d_u;            \
  typedef Utility::Trip<double,double,double> trip_d_d_d;        \
  typedef Utility::Trip<unsigned,double,double> trip_u_d_d;        \
  typedef Utility::Trip<unsigned,double,unsigned> trip_u_d_u;        \
  typedef Utility::Trip<double,double,unsigned> trip_d_d_u;        \
  typedef Utility::Trip<unsigned,unsigned,double> trip_u_u_d;        \
  typedef Utility::Trip<double,unsigned,double> trip_d_u_d;        \
  typedef Utility::Trip<double,unsigned,unsigned> trip_d_u_u;        \
  typedef Utility::Quad<double,double,double,double> quad_d_d_d_d;    \
  typedef Utility::Quad<unsigned,unsigned,double,double> quad_u_u_d_d;    \
  typedef Utility::Quad<unsigned,double,double,unsigned> quad_u_d_d_u;    \
  typedef Utility::Quad<unsigned,double,double,double> quad_u_d_d_d;    \
  typedef Utility::Quad<double,double,double,unsigned> quad_d_d_d_u;    \
  typedef Utility::Quad<double,double,unsigned,unsigned> quad_d_d_u_u;    \
  typedef Utility::Quad<double,unsigned,unsigned,double> quad_d_u_u_d;    \
  typedef Utility::Quad<unsigned,double,unsigned,double> quad_u_d_u_d;    \
  typedef Utility::Quad<unsigned,unsigned,unsigned,double> quad_u_u_u_d; \
  typedef Utility::Quad<unsigned,unsigned,unsigned,unsigned> quad_u_u_u_u; \
  typedef Utility::Quad<double,unsigned,double,unsigned> quad_d_u_d_u;    \
  typedef Utility::Quad<double,double,unsigned,double> quad_d_d_u_d;    \
  typedef Utility::Quad<unsigned,double,unsigned,unsigned> quad_u_d_u_u; \
  typedef Utility::Quad<double,unsigned,double,double> quad_d_u_d_d; \
  typedef Utility::Quad<unsigned,unsigned,double,unsigned> quad_u_u_d_u; \

#define UNIT_TEST_INSTANTIATION_2_TUPLE( type, name ) \
  TUPLE_TYPEDEFS() \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, FIRST, pair_d_d, pair_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, SECOND, pair_d_d, pair_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, SECOND, FIRST, pair_d_d, pair_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, SECOND, SECOND, pair_d_d, pair_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, FIRST, pair_d_u, pair_d_u ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, SECOND, SECOND, pair_u_d, pair_u_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, FIRST, trip_d_d_d, trip_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, SECOND, trip_d_d_d, trip_d_d_u ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, THIRD, trip_d_d_d, trip_u_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, SECOND, FIRST, trip_u_d_d, trip_d_u_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, THIRD, FIRST, trip_d_u_d, trip_d_u_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, THIRD, SECOND, trip_d_u_d, trip_u_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, FIRST, quad_d_d_d_d, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, SECOND, quad_d_d_d_d, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, THIRD, quad_d_d_d_d, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, FOURTH, quad_d_d_d_d, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, SECOND, FIRST, quad_d_d_d_d, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, THIRD, SECOND, quad_d_d_d_d, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FOURTH, THIRD, quad_u_d_d_d, quad_u_d_d_d ) \

#define UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE( type, name ) \
  TUPLE_TYPEDEFS() \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, SECOND, pair_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, FIRST, pair_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, SECOND, trip_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, THIRD, trip_d_u_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, FIRST, trip_d_d_u ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, THIRD, trip_u_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, FIRST, trip_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, SECOND, trip_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, SECOND, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, THIRD, quad_d_u_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, FOURTH, quad_d_d_u_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, FIRST, quad_d_d_d_u ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, THIRD, quad_u_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, FOURTH, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, FIRST, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, SECOND, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, FOURTH, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FOURTH, FIRST, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FOURTH, SECOND, quad_d_d_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FOURTH, THIRD, quad_d_u_d_d ) \

#define UNIT_TEST_INSTANTIATION_1_TUPLE( type, name ) \
  TUPLE_TYPEDEFS() \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, pair_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, pair_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, trip_d_u_d ) \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, trip_d_d_u ) \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, trip_u_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, quad_d_u_d_d ) \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, quad_d_d_u_d ) \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, quad_d_d_d_u ) \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FOURTH, quad_u_d_d_d ) \

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL(
                          LinLogLin,
                          interpolate_separate_tuple_grids,
                          ymember,
                          zmember,
                          ytuple,
                          ztuple )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 3e-2;
  Teuchos::Array<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], 1e-3 );
  Utility::set<ymember>( y_0_grid[1], 1e-2 );
  Utility::set<ymember>( y_0_grid[2], 1e-1 );
  Utility::set<ymember>( y_0_grid[3], 1.0 );

  Teuchos::Array<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 100.0 );
  Utility::set<zmember>( z_0_grid[1], 0.0 );
  Utility::set<zmember>( z_0_grid[2], 1.0 );
  Utility::set<zmember>( z_0_grid[3], 10.0 );

  Teuchos::Array<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], 1e-3 );
  Utility::set<ymember>( y_1_grid[1], 1e-1 );
  Utility::set<ymember>( y_1_grid[2], 1.0 );

  Teuchos::Array<ztuple> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_TUPLE( LinLogLin,
                 interpolate_separate_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL(
                          LinLogLin,
                          interpolate_combined_tuple_grids,
                          ymember,
                          zmember,
                          tuple )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 3e-2;
  Teuchos::Array<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], 1e-3 );
  Utility::set<ymember>( grid_0[1], 1e-2 );
  Utility::set<ymember>( grid_0[2], 1e-1 );
  Utility::set<ymember>( grid_0[3], 1.0 );
  Utility::set<zmember>( grid_0[0], 100.0 );
  Utility::set<zmember>( grid_0[1], 0.0 );
  Utility::set<zmember>( grid_0[2], 1.0 );
  Utility::set<zmember>( grid_0[3], 10.0 );

  Teuchos::Array<tuple> grid_1( 3 );
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

  TEST_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

  x = 0.0;

  z = Utility::LinLogLin::interpolate<ymember,zmember>( x0,
                            x1,
                            x,
                            y,
                            grid_0.begin(),
                            grid_0.end(),
                            grid_1.begin(),
                            grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

  x = 1.0;

  z = Utility::LinLogLin::interpolate<ymember,zmember>( x0,
                            x1,
                            x,
                            y,
                            grid_0.begin(),
                            grid_0.end(),
                            grid_1.begin(),
                            grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE( LinLogLin,
                      interpolate_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LinLogLin, interpolate_no_tuple_grids )
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
TEUCHOS_UNIT_TEST( LinLogLin, calculateIntermediateGridLimit )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0_min = 1e-3, y1_min = 1e-2;

  double yx_min = Utility::LinLogLin::calculateIntermediateGridLimit(
                           x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, 3.1622776601686e-3, 1e-12 );

  x = 0.0;

  yx_min = Utility::LinLogLin::calculateIntermediateGridLimit(
                           x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, 1e-3, 1e-12 );

  x = 1.0;

  yx_min = Utility::LinLogLin::calculateIntermediateGridLimit(
                           x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, 1e-2, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL(
                      LinLogLin,
                      interpolateUnitBase_separate_tuple_grids,
                      ymember,
                      zmember,
                      ytuple,
                      ztuple )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.03;

  Teuchos::Array<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], 1e-3 );
  Utility::set<ymember>( y_0_grid[1], 1e-2 );
  Utility::set<ymember>( y_0_grid[2], 1e-1 );
  Utility::set<ymember>( y_0_grid[3], 1.0 );

  Teuchos::Array<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 0.0 );
  Utility::set<zmember>( z_0_grid[1], 1.0 );
  Utility::set<zmember>( z_0_grid[2], 2.0 );
  Utility::set<zmember>( z_0_grid[3], 3.0 );

  Teuchos::Array<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], 1e-2 );
  Utility::set<ymember>( y_1_grid[1], 1e-1 );
  Utility::set<ymember>( y_1_grid[2], 1.0 );

  Teuchos::Array<ztuple> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 0.4, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

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

  UTILITY_TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_TUPLE( LinLogLin,
                 interpolateUnitBase_separate_tuple_grids);

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL(
                      LinLogLin,
                      interpolateUnitBase_combined_tuple_grids,
                      ymember,
                      zmember,
                      tuple )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5, y = 0.03;

  Teuchos::Array<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], 1e-3 );
  Utility::set<ymember>( grid_0[1], 1e-2 );
  Utility::set<ymember>( grid_0[2], 1e-1 );
  Utility::set<ymember>( grid_0[3], 1.0 );
  Utility::set<zmember>( grid_0[0], 0.0 );
  Utility::set<zmember>( grid_0[1], 1.0 );
  Utility::set<zmember>( grid_0[2], 2.0 );
  Utility::set<zmember>( grid_0[3], 3.0 );

  Teuchos::Array<tuple> grid_1( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

  y = 0.0031622776601684; // min possible y at x = 0.5

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 0.4, 1e-12 );

  y = 1.0; // max possible y at x = 0.5

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
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

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-3;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  UTILITY_TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
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

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = 1e-2;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = 1.0;

  z = Utility::LinLogLin::interpolateUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE(
                        LinLogLin,
                    interpolateUnitBase_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( LinLogLin, interpolateUnitBase_no_tuple_grids )
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
// Check that the dependent variable can be processed
TEUCHOS_UNIT_TEST( LinLogLin, processDepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLogLin::processDepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLogLin::processDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLogLin::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LinLogLin, recoverProcessedDepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLogLin::recoverProcessedDepVar(-1.0));
  TEST_EQUALITY_CONST( 0.0, Utility::LinLogLin::recoverProcessedDepVar(0.0) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLogLin::recoverProcessedDepVar(1.0) );
}

//---------------------------------------------------------------------------//
// Check that the second independent variable can be processed
TEUCHOS_UNIT_TEST( LinLogLin, processSecondIndepVar )
{
  TEST_FLOATING_EQUALITY( log(0.1),
              Utility::LinLogLin::processSecondIndepVar(0.1),
              1e-15 );
  TEST_FLOATING_EQUALITY( log(1.0),
              Utility::LinLogLin::processSecondIndepVar(1.0),
              1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed second independent variable can be recovered
TEUCHOS_UNIT_TEST( LinLogLin, recoverProcessedSecondIndepVar )
{
  TEST_FLOATING_EQUALITY(
          0.1,
          Utility::LinLogLin::recoverProcessedSecondIndepVar(log(0.1)),
          1e-15 );
  TEST_FLOATING_EQUALITY(
          1.0,
          Utility::LinLogLin::recoverProcessedSecondIndepVar(log(1.0)),
          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the first independent variable can be processed
TEUCHOS_UNIT_TEST( LinLogLin, processFirstIndepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLogLin::processFirstIndepVar(-1.0) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLogLin::processFirstIndepVar(0.0) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLogLin::processFirstIndepVar(1.0) );
}

//---------------------------------------------------------------------------//
// Check that a processed first independent variable can be processed
TEUCHOS_UNIT_TEST( LinLogLin, recoverProcessedFirstIndepVar )
{
  TEST_EQUALITY_CONST(
             -1.0,
             Utility::LinLogLin::recoverProcessedFirstIndepVar(-1.0) );
  TEST_EQUALITY_CONST(0.0,
              Utility::LinLogLin::recoverProcessedFirstIndepVar(0.0) );
  TEST_EQUALITY_CONST(1.0,
              Utility::LinLogLin::recoverProcessedFirstIndepVar(1.0) );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL(
                     LinLogLin,
                     interpolateProcessed_separate_tuple_grids,
                     ymember,
                     zmember,
                     ytuple,
                     ztuple )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(3e-2);

  Teuchos::Array<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0],
             Utility::LinLogLin::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( y_0_grid[1],
             Utility::LinLogLin::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( y_0_grid[2],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_0_grid[3],
             Utility::LinLogLin::processSecondIndepVar(1.0) );

  Teuchos::Array<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 100.0 );
  Utility::set<zmember>( z_0_grid[1], 0.0 );
  Utility::set<zmember>( z_0_grid[2], 1.0 );
  Utility::set<zmember>( z_0_grid[3], 10.0 );

  Teuchos::Array<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0],
             Utility::LinLogLin::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( y_1_grid[1],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_1_grid[2],
             Utility::LinLogLin::processSecondIndepVar(1.0) );

  Teuchos::Array<ztuple> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_TUPLE( LinLogLin,
                 interpolateProcessed_separate_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL(
                     LinLogLin,
                     interpolateProcessed_combined_tuple_grids,
                     ymember,
                     zmember,
                     tuple )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(3e-2);

  Teuchos::Array<tuple> grid_0( 4 );
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

  Teuchos::Array<tuple> grid_1( 3 );
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

  TEST_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE(
                   LinLogLin,
                   interpolateProcessed_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-linear interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LinLogLin, interpolateProcessed_no_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(3e-2);

  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[0] = Utility::LinLogLin::processSecondIndepVar(1e-3);
  y_0_grid[1] = Utility::LinLogLin::processSecondIndepVar(1e-2);
  y_0_grid[2] = Utility::LinLogLin::processSecondIndepVar(1e-1);
  y_0_grid[3] = Utility::LinLogLin::processSecondIndepVar(1.0);

  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[0] = 100.0;
  z_0_grid[1] = 0.0;
  z_0_grid[2] = 1.0;
  z_0_grid[3] = 10.0;

  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[0] = Utility::LinLogLin::processSecondIndepVar(1e-3);
  y_1_grid[1] = Utility::LinLogLin::processSecondIndepVar(1e-1);
  y_1_grid[2] = Utility::LinLogLin::processSecondIndepVar(1.0);

  Teuchos::Array<double> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 10.467348080163, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 0.47712125471965, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 20.457574905607, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
TEUCHOS_UNIT_TEST( LinLogLin, calculateIntermediateGridLengthProcessed )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LinLogLin::calculateIntermediateGridLengthProcessed(
                               x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 4.0, 1e-15 );

  x = 0.0;

  Lx = Utility::LinLogLin::calculateIntermediateGridLengthProcessed(
                               x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = 1.0;

  Lx = Utility::LinLogLin::calculateIntermediateGridLengthProcessed(
                               x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
TEUCHOS_UNIT_TEST( LinLogLin, calculateIntermediateProcessedGridLimit )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y0_min = Utility::LinLogLin::processSecondIndepVar(1e-3);
  double y1_min = Utility::LinLogLin::processSecondIndepVar(1e-2);

  double yx_min = Utility::LinLogLin::calculateIntermediateProcessedGridLimit(
                           x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY(
         yx_min,
         Utility::LinLogLin::processSecondIndepVar(3.1622776601686e-3),
         1e-12 );

  x = 0.0;

  yx_min = Utility::LinLogLin::calculateIntermediateProcessedGridLimit(
                           x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min,
              Utility::LinLogLin::processSecondIndepVar(1e-3),
              1e-12 );

  x = 1.0;

  yx_min = Utility::LinLogLin::calculateIntermediateProcessedGridLimit(
                           x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min,
              Utility::LinLogLin::processSecondIndepVar(1e-2),
              1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL(
                 LinLogLin,
                 interpolateProcessedUnitBase_separate_tuple_grids,
                 ymember,
                 zmember,
                 ytuple,
                 ztuple )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(0.03);

  Teuchos::Array<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0],
             Utility::LinLogLin::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( y_0_grid[1],
             Utility::LinLogLin::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( y_0_grid[2],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_0_grid[3],
             Utility::LinLogLin::processSecondIndepVar(1.0) );

  Teuchos::Array<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 0.0 );
  Utility::set<zmember>( z_0_grid[1], 1.0 );
  Utility::set<zmember>( z_0_grid[2], 2.0 );
  Utility::set<zmember>( z_0_grid[3], 3.0 );

  Teuchos::Array<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0],
             Utility::LinLogLin::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( y_1_grid[1],
             Utility::LinLogLin::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_1_grid[2],
             Utility::LinLogLin::processSecondIndepVar(1.0) );

  Teuchos::Array<ztuple> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 0.4, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

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

  UTILITY_TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_TUPLE(
               LinLogLin,
               interpolateProcessedUnitBase_separate_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL(
                 LinLogLin,
                 interpolateProcessedUnitBase_combined_tuple_grids,
                 ymember,
                 zmember,
                 tuple )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(0.03);

  Teuchos::Array<tuple> grid_0( 4 );
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

  Teuchos::Array<tuple> grid_1( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 0.4, 1e-12 );

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


  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1e-3);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  UTILITY_TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1e-2);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = Utility::LinLogLin::processSecondIndepVar(1.0);

  z = Utility::LinLogLin::interpolateProcessedUnitBase<ymember,zmember>( x0,
                                x1,
                                x,
                                y,
                                        grid_0.begin(),
                                grid_0.end(),
                                grid_1.begin(),
                                grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE(
                        LinLogLin,
                    interpolateProcessedUnitBase_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-linear unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( LinLogLin, interpolateProcessedUnitBase_no_tuple_grids )
{
  double x0 = 0.0, x1 = 1.0, x = 0.5;
  double y = Utility::LinLogLin::processSecondIndepVar(0.03);

  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[0] = Utility::LinLogLin::processSecondIndepVar(1e-3);
  y_0_grid[1] = Utility::LinLogLin::processSecondIndepVar(1e-2);
  y_0_grid[2] = Utility::LinLogLin::processSecondIndepVar(1e-1);
  y_0_grid[3] = Utility::LinLogLin::processSecondIndepVar(1.0);

  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[0] = 0.0;
  z_0_grid[1] = 1.0;
  z_0_grid[2] = 2.0;
  z_0_grid[3] = 3.0;

  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[0] = Utility::LinLogLin::processSecondIndepVar(1e-2);
  y_1_grid[1] = Utility::LinLogLin::processSecondIndepVar(1e-1);
  y_1_grid[2] = Utility::LinLogLin::processSecondIndepVar(1.0);

  Teuchos::Array<double> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.4162061049085, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 0.4, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

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

  UTILITY_TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4771212547197, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// end tstLinLogLinTwoDInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
