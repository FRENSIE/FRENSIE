//---------------------------------------------------------------------------//
//!
//! \file   tstLogLogCosLogTwoDInterpolationPolicy.cpp
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
#include "Utility_TupleMemberTraits.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define TUPLE_TYPEDEFS()                                        \
  typedef Utility::Pair<double,double> pair_d_d;                        \
  typedef Utility::Pair<unsigned,double> pair_u_d;                        \
  typedef Utility::Pair<double,unsigned> pair_d_u;                        \
  typedef Utility::Trip<double,double,double> trip_d_d_d;                \
  typedef Utility::Trip<unsigned,double,double> trip_u_d_d;                \
  typedef Utility::Trip<unsigned,double,unsigned> trip_u_d_u;                \
  typedef Utility::Trip<double,double,unsigned> trip_d_d_u;                \
  typedef Utility::Trip<unsigned,unsigned,double> trip_u_u_d;                \
  typedef Utility::Trip<double,unsigned,double> trip_d_u_d;                \
  typedef Utility::Trip<double,unsigned,unsigned> trip_d_u_u;                \
  typedef Utility::Quad<double,double,double,double> quad_d_d_d_d;        \
  typedef Utility::Quad<unsigned,unsigned,double,double> quad_u_u_d_d;        \
  typedef Utility::Quad<unsigned,double,double,unsigned> quad_u_d_d_u;        \
  typedef Utility::Quad<unsigned,double,double,double> quad_u_d_d_d;        \
  typedef Utility::Quad<double,double,double,unsigned> quad_d_d_d_u;        \
  typedef Utility::Quad<double,double,unsigned,unsigned> quad_d_d_u_u;        \
  typedef Utility::Quad<double,unsigned,unsigned,double> quad_d_u_u_d;        \
  typedef Utility::Quad<unsigned,double,unsigned,double> quad_u_d_u_d;        \
  typedef Utility::Quad<unsigned,unsigned,unsigned,double> quad_u_u_u_d; \
  typedef Utility::Quad<unsigned,unsigned,unsigned,unsigned> quad_u_u_u_u; \
  typedef Utility::Quad<double,unsigned,double,unsigned> quad_d_u_d_u;        \
  typedef Utility::Quad<double,double,unsigned,double> quad_d_d_u_d;        \
  typedef Utility::Quad<unsigned,double,unsigned,unsigned> quad_u_d_u_u; \
  typedef Utility::Quad<double,unsigned,double,double> quad_d_u_d_d; \
  typedef Utility::Quad<unsigned,unsigned,double,unsigned> quad_u_u_d_u; \

#define UNIT_TEST_INSTANTIATION_2_TUPLE( type, name ) \
  TUPLE_TYPEDEFS() \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, FIRST, pair_d_d, pair_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, SECOND, pair_d_d, pair_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, SECOND, FIRST, pair_d_d, pair_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, SECOND, SECOND, pair_d_d, pair_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, FIRST, pair_d_u, pair_d_u ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, SECOND, SECOND, pair_u_d, pair_u_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, FIRST, trip_d_d_d, trip_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, SECOND, trip_d_d_d, trip_d_d_u ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, THIRD, trip_d_d_d, trip_u_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, SECOND, FIRST, trip_u_d_d, trip_d_u_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, THIRD, FIRST, trip_d_u_d, trip_d_u_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, THIRD, SECOND, trip_d_u_d, trip_u_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, FIRST, quad_d_d_d_d, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, SECOND, quad_d_d_d_d, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, THIRD, quad_d_d_d_d, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FIRST, FOURTH, quad_d_d_d_d, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, SECOND, FIRST, quad_d_d_d_d, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, THIRD, SECOND, quad_d_d_d_d, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT( type, name, FOURTH, THIRD, quad_u_d_d_d, quad_u_d_d_d ) \

#define UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE( type, name ) \
  TUPLE_TYPEDEFS() \
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, SECOND, pair_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, FIRST, pair_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, SECOND, trip_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, THIRD, trip_d_u_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, FIRST, trip_d_d_u ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, THIRD, trip_u_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, FIRST, trip_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, SECOND, trip_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, SECOND, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, THIRD, quad_d_u_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, FOURTH, quad_d_d_u_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, FIRST, quad_d_d_d_u ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, THIRD, quad_u_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, FOURTH, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, FIRST, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, SECOND, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, FOURTH, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FOURTH, FIRST, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FOURTH, SECOND, quad_d_d_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT( type, name, FOURTH, THIRD, quad_d_u_d_d ) \

#define UNIT_TEST_INSTANTIATION_1_TUPLE( type, name ) \
  TUPLE_TYPEDEFS() \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, pair_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, pair_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, trip_d_u_d ) \
  // UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, trip_d_d_u ) \
  // UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, trip_u_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, quad_d_u_d_d ) \
  // UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, SECOND, quad_d_d_u_d ) \
  // UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, THIRD, quad_d_d_d_u ) \
  // UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FOURTH, quad_u_d_d_d ) \

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL(
                                              LogLogCosLog,
                                              interpolate_separate_tuple_grids,
                                              ymember,
                                              zmember,
                                              ytuple,
                                              ztuple )

{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  Teuchos::Array<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], -1.0 );
  Utility::set<ymember>( y_0_grid[1], 0.0 );
  Utility::set<ymember>( y_0_grid[2], 0.5 );
  Utility::set<ymember>( y_0_grid[3], 0.999999 );

  Teuchos::Array<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 100.0 );
  Utility::set<zmember>( z_0_grid[1], 0.1 );
  Utility::set<zmember>( z_0_grid[2], 1.0 );
  Utility::set<zmember>( z_0_grid[3], 10.0 );

  Teuchos::Array<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], -1.0 );
  Utility::set<ymember>( y_1_grid[1], 0.0 );
  Utility::set<ymember>( y_1_grid[2], 0.999999 );

  Teuchos::Array<ztuple> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_TUPLE( LogLogCosLog, interpolate_separate_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL(
                                              LogLogCosLog,
                                              interpolate_combined_tuple_grids,
                                              ymember,
                                              zmember,
                                              tuple )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  Teuchos::Array<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], -1.0 );
  Utility::set<ymember>( grid_0[1], 0.0 );
  Utility::set<ymember>( grid_0[2], 0.5 );
  Utility::set<ymember>( grid_0[3], 0.999999 );
  Utility::set<zmember>( grid_0[0], 100.0 );
  Utility::set<zmember>( grid_0[1], 0.1 );
  Utility::set<zmember>( grid_0[2], 1.0 );
  Utility::set<zmember>( grid_0[3], 10.0 );

  Teuchos::Array<tuple> grid_1( 3 );
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

  TEST_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

  x = 0.1;

  z = Utility::LogLogCosLog::interpolate<ymember,zmember>( x0,
                                                           x1,
                                                           x,
                                                           y,
                                                           grid_0.begin(),
                                                           grid_0.end(),
                                                           grid_1.begin(),
                                                           grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

  x = 1.0;

  z = Utility::LogLogCosLog::interpolate<ymember,zmember>( x0,
                                                           x1,
                                                           x,
                                                           y,
                                                           grid_0.begin(),
                                                           grid_0.end(),
                                                           grid_1.begin(),
                                                           grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE( LogLogCosLog,
                                          interpolate_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LogLogCosLog, interpolate_no_tuple_grids )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;
  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[0] = -1.0;
  y_0_grid[1] = 0.0;
  y_0_grid[2] = 0.5;
  y_0_grid[3] = 0.999999;

  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[0] = 100.0;
  z_0_grid[1] = 0.1;
  z_0_grid[2] = 1.0;
  z_0_grid[3] = 10.0;

  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[0] = -1.0;
  y_1_grid[1] = 0.0;
  y_1_grid[2] = 0.999999;

  Teuchos::Array<double> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
TEUCHOS_UNIT_TEST( LogLogCosLog, calculateIntermediateGridLength )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3;
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LogLogCosLog::calculateIntermediateGridLength(
                                                           x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 3.9542425094393248, 1e-15 );

  x = 0.1;

  Lx = Utility::LogLogCosLog::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = 1.0;

  Lx = Utility::LogLogCosLog::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
TEUCHOS_UNIT_TEST( LogLogCosLog, calculateIntermediateGridLimit )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3;
  double y0_min = -1.0, y1_min = -1.0;

  double yx_min = Utility::LogLogCosLog::calculateIntermediateGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, -1.0, 1e-15 );

  x = 0.1;

  yx_min = Utility::LogLogCosLog::calculateIntermediateGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, -1.0, 1e-15 );

  x = 1.0;

  yx_min = Utility::LogLogCosLog::calculateIntermediateGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL(
                                      LogLogCosLog,
                                      interpolateUnitBase_separate_tuple_grids,
                                      ymember,
                                      zmember,
                                      ytuple,
                                      ztuple )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  Teuchos::Array<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], -1.0 );
  Utility::set<ymember>( y_0_grid[1], 0.0 );
  Utility::set<ymember>( y_0_grid[2], 0.5 );
  Utility::set<ymember>( y_0_grid[3], 0.999999 );

  Teuchos::Array<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 1e-3 );
  Utility::set<zmember>( z_0_grid[1], 1e-2 );
  Utility::set<zmember>( z_0_grid[2], 1e-1 );
  Utility::set<zmember>( z_0_grid[3], 1.0 );

  Teuchos::Array<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], -1.0 );
  Utility::set<ymember>( y_1_grid[1], 0.0 );
  Utility::set<ymember>( y_1_grid[2], 0.999999 );

  Teuchos::Array<ztuple> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

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

  UTILITY_TEST_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_TUPLE( LogLogCosLog,
                                 interpolateUnitBase_separate_tuple_grids);

//---------------------------------------------------------------------------//
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL(
                                      LogLogCosLog,
                                      interpolateUnitBase_combined_tuple_grids,
                                      ymember,
                                      zmember,
                                      tuple )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  Teuchos::Array<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], -1.0 );
  Utility::set<ymember>( grid_0[1], 0.0 );
  Utility::set<ymember>( grid_0[2], 0.5 );
  Utility::set<ymember>( grid_0[3], 0.999999 );
  Utility::set<zmember>( grid_0[0], 1e-3 );
  Utility::set<zmember>( grid_0[1], 1e-2 );
  Utility::set<zmember>( grid_0[2], 1e-1 );
  Utility::set<zmember>( grid_0[3], 1.0 );

  Teuchos::Array<tuple> grid_1( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

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

  UTILITY_TEST_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE(
                                    LogLogCosLog,
                                    interpolateUnitBase_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( LogLogCosLog, interpolateUnitBase_no_tuple_grids )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.9;

  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[0] = -1.0;
  y_0_grid[1] = 0.0;
  y_0_grid[2] = 0.5;
  y_0_grid[3] = 0.999999;

  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[0] = 1e-3;
  z_0_grid[1] = 1e-2;
  z_0_grid[2] = 1e-1;
  z_0_grid[3] = 1.0;

  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[0] = -1.0;
  y_1_grid[1] = 0.0;
  y_1_grid[2] = 0.999999;

  Teuchos::Array<double> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

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

  UTILITY_TEST_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the dependent variable can be processed
TEUCHOS_UNIT_TEST( LogLogCosLog, processDepVar )
{
  TEST_FLOATING_EQUALITY( log(0.1),
                          Utility::LogLogCosLog::processDepVar(0.1),
                          1e-15 );
  TEST_FLOATING_EQUALITY( log(1.0),
                          Utility::LogLogCosLog::processDepVar( 1.0 ),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LogLogCosLog, recoverProcessedDepVar )
{
  TEST_FLOATING_EQUALITY( 0.1,
                          Utility::LogLogCosLog::recoverProcessedDepVar(log(0.1)),
                          1e-15 );
  TEST_FLOATING_EQUALITY( 1.0,
                          Utility::LogLogCosLog::recoverProcessedDepVar(log(1.0)),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the second independent variable can be processed
TEUCHOS_UNIT_TEST( LogLogCosLog, processSecondIndepVar )
{
  TEST_FLOATING_EQUALITY( log(2.0),
                          Utility::LogLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );
  TEST_FLOATING_EQUALITY( log(1.0-0.999999),
                          Utility::LogLogCosLog::processSecondIndepVar(0.999999),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed second independent variable can be recovered
TEUCHOS_UNIT_TEST( LogLogCosLog, recoverProcessedSecondIndepVar )
{
  TEST_FLOATING_EQUALITY(
                  -1.0,
                  Utility::LogLogCosLog::recoverProcessedSecondIndepVar(log(2.0)),
                  1e-15 );
  TEST_FLOATING_EQUALITY(
                  0.999999,
                  Utility::LogLogCosLog::recoverProcessedSecondIndepVar(log(1.0-0.999999)),
                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the first independent variable can be processed
TEUCHOS_UNIT_TEST( LogLogCosLog, processFirstIndepVar )
{
  TEST_FLOATING_EQUALITY( log(0.1),
                          Utility::LogLogCosLog::processFirstIndepVar(0.1),
                          1e-15 );
  TEST_FLOATING_EQUALITY( log(1.0),
                          Utility::LogLogCosLog::processFirstIndepVar(1.0),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed first independent variable can be processed
TEUCHOS_UNIT_TEST( LogLogCosLog, recoverProcessedFirstIndepVar )
{
  TEST_FLOATING_EQUALITY(
                  0.1,
                  Utility::LogLogCosLog::recoverProcessedFirstIndepVar(log(0.1)),
                  1e-15 );
  TEST_FLOATING_EQUALITY(
                  1.0,
                  Utility::LogLogCosLog::recoverProcessedFirstIndepVar(log(1.0)),
                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL(
                                     LogLogCosLog,
                                     interpolateProcessed_separate_tuple_grids,
                                     ymember,
                                     zmember,
                                     ytuple,
                                     ztuple )

{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);

  Teuchos::Array<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[3],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_0_grid[2],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( y_0_grid[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.5) );
  Utility::set<ymember>( y_0_grid[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );

  Teuchos::Array<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[3],
                         Utility::LogLogCosLog::processDepVar(100.0) );
  Utility::set<zmember>( z_0_grid[2],
                         Utility::LogLogCosLog::processDepVar(0.1) );
  Utility::set<zmember>( z_0_grid[1],
                         Utility::LogLogCosLog::processDepVar(1.0) );
  Utility::set<zmember>( z_0_grid[0],
                         Utility::LogLogCosLog::processDepVar(10.0) );

  Teuchos::Array<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[2],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_1_grid[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( y_1_grid[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );

  Teuchos::Array<ztuple> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_TUPLE( LogLogCosLog,
                                 interpolateProcessed_separate_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL(
                                     LogLogCosLog,
                                     interpolateProcessed_combined_tuple_grids,
                                     ymember,
                                     zmember,
                                     tuple )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);

  Teuchos::Array<tuple> grid_0( 4 );
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

  Teuchos::Array<tuple> grid_1( 3 );
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

  TEST_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE(
                                   LogLogCosLog,
                                   interpolateProcessed_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the log-logcos-log interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LogLogCosLog, interpolateProcessed_no_tuple_grids )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);

  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[3] = Utility::LogLogCosLog::processSecondIndepVar(-1.0);
  y_0_grid[2] = Utility::LogLogCosLog::processSecondIndepVar(0.0);
  y_0_grid[1] = Utility::LogLogCosLog::processSecondIndepVar(0.5);
  y_0_grid[0] = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[3] = Utility::LogLogCosLog::processDepVar(100.0);
  z_0_grid[2] = Utility::LogLogCosLog::processDepVar(0.1);
  z_0_grid[1] = Utility::LogLogCosLog::processDepVar(1.0);
  z_0_grid[0] = Utility::LogLogCosLog::processDepVar(10.0);

  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[2] = Utility::LogLogCosLog::processSecondIndepVar(-1.0);
  y_1_grid[1] = Utility::LogLogCosLog::processSecondIndepVar(0.0);
  y_1_grid[0] = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  Teuchos::Array<double> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 2.0801924668549385, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129951, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3.4064603452870852, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
TEUCHOS_UNIT_TEST( LogLogCosLog, calculateIntermediateGridLengthProcessed )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LogLogCosLog::calculateIntermediateGridLengthProcessed(
                                                           x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 3.9542425094393248, 1e-15 );

  x = Utility::LogLogCosLog::processFirstIndepVar(0.1);

  Lx = Utility::LogLogCosLog::calculateIntermediateGridLengthProcessed(
                                                           x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = Utility::LogLogCosLog::processFirstIndepVar(1.0);

  Lx = Utility::LogLogCosLog::calculateIntermediateGridLengthProcessed(
                                                           x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
TEUCHOS_UNIT_TEST( LogLogCosLog, calculateIntermediateProcessedGridLimit )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y0_min = Utility::LogLogCosLog::processSecondIndepVar(-1.0);
  double y1_min = Utility::LogLogCosLog::processSecondIndepVar(-1.0);

  double yx_min = Utility::LogLogCosLog::calculateIntermediateProcessedGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min,
                          Utility::LogLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );

  x = Utility::LogLogCosLog::processFirstIndepVar(0.1);

  yx_min = Utility::LogLogCosLog::calculateIntermediateProcessedGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min,
                          Utility::LogLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );

  x = Utility::LogLogCosLog::processFirstIndepVar(1.0);

  yx_min = Utility::LogLogCosLog::calculateIntermediateProcessedGridLimit(
                                                   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min,
                          Utility::LogLogCosLog::processSecondIndepVar(-1.0),
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL(
                             LogLogCosLog,
                             interpolateProcessedUnitBase_separate_tuple_grids,
                             ymember,
                             zmember,
                             ytuple,
                             ztuple )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);
  double fuzzy_tol = 1e-4;

  Teuchos::Array<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[3],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_0_grid[2],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( y_0_grid[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.5) );
  Utility::set<ymember>( y_0_grid[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );

  Teuchos::Array<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[3],
                         Utility::LogLogCosLog::processDepVar(1e-3) );
  Utility::set<zmember>( z_0_grid[2],
                         Utility::LogLogCosLog::processDepVar(1e-2) );
  Utility::set<zmember>( z_0_grid[1],
                         Utility::LogLogCosLog::processDepVar(1e-1) );
  Utility::set<zmember>( z_0_grid[0],
                         Utility::LogLogCosLog::processDepVar(1.0) );

  Teuchos::Array<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[2],
                         Utility::LogLogCosLog::processSecondIndepVar(-1.0) );
  Utility::set<ymember>( y_1_grid[1],
                         Utility::LogLogCosLog::processSecondIndepVar(0.0) );
  Utility::set<ymember>( y_1_grid[0],
                         Utility::LogLogCosLog::processSecondIndepVar(0.999999) );

  Teuchos::Array<ztuple> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

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

  UTILITY_TEST_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_TUPLE(
                           LogLogCosLog,
                           interpolateProcessedUnitBase_separate_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL(
                             LogLogCosLog,
                             interpolateProcessedUnitBase_combined_tuple_grids,
                             ymember,
                             zmember,
                             tuple )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);

  Teuchos::Array<tuple> grid_0( 4 );
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

  Teuchos::Array<tuple> grid_1( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

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

  UTILITY_TEST_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE(
                           LogLogCosLog,
                           interpolateProcessedUnitBase_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the log-logcos-log unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( LogLogCosLog, interpolateProcessedUnitBase_no_tuple_grids )
{
  double x0 = Utility::LogLogCosLog::processFirstIndepVar(0.1);
  double x1 = Utility::LogLogCosLog::processFirstIndepVar(1.0);
  double x = Utility::LogLogCosLog::processFirstIndepVar(0.3);
  double y = Utility::LogLogCosLog::processSecondIndepVar(0.9);

  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[3] = Utility::LogLogCosLog::processSecondIndepVar(-1.0);
  y_0_grid[2] = Utility::LogLogCosLog::processSecondIndepVar(0.0);
  y_0_grid[1] = Utility::LogLogCosLog::processSecondIndepVar(0.5);
  y_0_grid[0] = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[3] = Utility::LogLogCosLog::processDepVar(1e-3);
  z_0_grid[2] = Utility::LogLogCosLog::processDepVar(1e-2);
  z_0_grid[1] = Utility::LogLogCosLog::processDepVar(1e-1);
  z_0_grid[0] = Utility::LogLogCosLog::processDepVar(1.0);

  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[2] = Utility::LogLogCosLog::processSecondIndepVar(-1.0);
  y_1_grid[1] = Utility::LogLogCosLog::processSecondIndepVar(0.0);
  y_1_grid[0] = Utility::LogLogCosLog::processSecondIndepVar(0.999999);

  Teuchos::Array<double> z_1_grid( 3 );
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

  TEST_FLOATING_EQUALITY( z, 1.3920360807059723e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 3e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.3263204908129952e-01, 1e-12 );

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

  UTILITY_TEST_FLOATING_EQUALITY( z, 1e-3, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.4677992676232424e-01, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1e-2, 1e-12 );

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

  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// end tstLogLogCosLogTwoDInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
