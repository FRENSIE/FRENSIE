//---------------------------------------------------------------------------//
//!
//! \file   tstLinLogLogTwoDInterpolationPolicy.cpp
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
#define TUPLE_TYPEDEFS()					\
  typedef Utility::Pair<double,double> pair_d_d;			\
  typedef Utility::Pair<unsigned,double> pair_u_d;			\
  typedef Utility::Pair<double,unsigned> pair_d_u;			\
  typedef Utility::Trip<double,double,double> trip_d_d_d;		\
  typedef Utility::Trip<unsigned,double,double> trip_u_d_d;		\
  typedef Utility::Trip<unsigned,double,unsigned> trip_u_d_u;		\
  typedef Utility::Trip<double,double,unsigned> trip_d_d_u;		\
  typedef Utility::Trip<unsigned,unsigned,double> trip_u_u_d;		\
  typedef Utility::Trip<double,unsigned,double> trip_d_u_d;		\
  typedef Utility::Trip<double,unsigned,unsigned> trip_d_u_u;		\
  typedef Utility::Quad<double,double,double,double> quad_d_d_d_d;	\
  typedef Utility::Quad<unsigned,unsigned,double,double> quad_u_u_d_d;	\
  typedef Utility::Quad<unsigned,double,double,unsigned> quad_u_d_d_u;	\
  typedef Utility::Quad<unsigned,double,double,double> quad_u_d_d_d;	\
  typedef Utility::Quad<double,double,double,unsigned> quad_d_d_d_u;	\
  typedef Utility::Quad<double,double,unsigned,unsigned> quad_d_d_u_u;	\
  typedef Utility::Quad<double,unsigned,unsigned,double> quad_d_u_u_d;	\
  typedef Utility::Quad<unsigned,double,unsigned,double> quad_u_d_u_d;	\
  typedef Utility::Quad<unsigned,unsigned,unsigned,double> quad_u_u_u_d; \
  typedef Utility::Quad<unsigned,unsigned,unsigned,unsigned> quad_u_u_u_u; \
  typedef Utility::Quad<double,unsigned,double,unsigned> quad_d_u_d_u;	\
  typedef Utility::Quad<double,double,unsigned,double> quad_d_d_u_d;	\
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
// Check that the linear-log-log interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL( 
					      LinLogLog, 
					      interpolate_separate_tuple_grids,
					      ymember,
					      zmember,
					      ytuple,
					      ztuple )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 3e-2;
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

  double z = Utility::LinLogLog::interpolate<ymember,zmember>(x0,
							      x1,
							      x,
							      y,
							      y_0_grid.begin(),
							      y_0_grid.end(),
							      z_0_grid.begin(),
							      z_0_grid.end(),
							      y_1_grid.begin(),
							      y_1_grid.end(),
							      z_1_grid.begin(),
							      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 10.010220370498972, 1e-12 );

  x = 0.1;

  z = Utility::LinLogLog::interpolate<ymember,zmember>( x0,
							x1,
							x,
							y,
							y_0_grid.begin(),
							y_0_grid.end(),
							z_0_grid.begin(),
							z_0_grid.end(),
							y_1_grid.begin(),
							y_1_grid.end(),
							z_1_grid.begin(),
							z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.4771212547196622, 1e-12 );

  x = 1.0;
  
  z = Utility::LinLogLog::interpolate<ymember,zmember>( x0,
							x1,
							x,
							y,
							y_0_grid.begin(),
							y_0_grid.end(),
							z_0_grid.begin(),
							z_0_grid.end(),
							y_1_grid.begin(),
							y_1_grid.end(),
							z_1_grid.begin(),
							z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 20.45757490560676, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_TUPLE( LinLogLog, interpolate_separate_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-log interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL( 
					      LinLogLog, 
					      interpolate_combined_tuple_grids,
					      ymember,
					      zmember,
					      tuple )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 3e-2;
  
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

  double z = Utility::LinLogLog::interpolate<ymember,zmember>(x0,
							      x1,
							      x,
							      y,
							      grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
  
  TEST_FLOATING_EQUALITY( z, 10.010220370498972, 1e-12 );

  x = 0.1;

  z = Utility::LinLogLog::interpolate<ymember,zmember>( x0,
							x1,
							x,
							y,
							grid_0.begin(),
							grid_0.end(),
							grid_1.begin(),
							grid_1.end() );
							
  TEST_FLOATING_EQUALITY( z, 0.4771212547196622, 1e-12 );

  x = 1.0;
  
  z = Utility::LinLogLog::interpolate<ymember,zmember>( x0,
							x1,
							x,
							y,
							grid_0.begin(),
							grid_0.end(),
							grid_1.begin(),
							grid_1.end() );
							
  TEST_FLOATING_EQUALITY( z, 20.45757490560676, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE( LinLogLog, 
					  interpolate_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-log interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LinLogLog, 
		   interpolate_no_tuple_grids )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 3e-2;
  
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

  double z = Utility::LinLogLog::interpolate( x0,
					      x1,
					      x,
					      y,
					      y_0_grid.begin(),
					      y_0_grid.end(),
					      z_0_grid.begin(),
					      z_0_grid.end(),
					      y_1_grid.begin(),
					      y_1_grid.end(),
					      z_1_grid.begin(),
					      z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 10.010220370498972, 1e-12 );

  x = 0.1;

  z = Utility::LinLogLog::interpolate( x0,
				       x1,
				       x,
				       y,
				       y_0_grid.begin(),
				       y_0_grid.end(),
				       z_0_grid.begin(),
				       z_0_grid.end(),
				       y_1_grid.begin(),
				       y_1_grid.end(),
				       z_1_grid.begin(),
				       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.4771212547196622, 1e-12 );

  x = 1.0;
  
  z = Utility::LinLogLog::interpolate( x0,
				       x1,
				       x,
				       y,
				       y_0_grid.begin(),
				       y_0_grid.end(),
				       z_0_grid.begin(),
				       z_0_grid.end(),
				       y_1_grid.begin(),
				       y_1_grid.end(),
				       z_1_grid.begin(),
				       z_1_grid.end() );
  
  TEST_FLOATING_EQUALITY( z, 20.45757490560676, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid length can be calculated
UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_DECL( LinLogLog, 
						  calculateGridLength,
						  member,
						  tuple )
{
  Teuchos::Array<tuple> tuple_grid( 4 );
  Utility::set<member>( tuple_grid[0], 1e-3 );
  Utility::set<member>( tuple_grid[1], 1e-2 );
  Utility::set<member>( tuple_grid[2], 1e-1 );
  Utility::set<member>( tuple_grid[3], 1.0 );
    
  double grid_length = Utility::LinLogLog::calculateGridLength<member>(
							    tuple_grid.begin(),
							    tuple_grid.end() );

  TEST_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

UNIT_TEST_INSTANTIATION_1_TUPLE( LinLogLog, calculateGridLength );

//---------------------------------------------------------------------------//
// Check that the grid length can be calculated
TEUCHOS_UNIT_TEST( LinLogLog, calculateGridLength_no_tuple )
{
  Teuchos::Array<double> grid( 4 );
  grid[0] = 1e-3;
  grid[1] = 1e-2;
  grid[2] = 1e-1;
  grid[3] = 1.0;

  double grid_length = 
    Utility::LinLogLog::calculateGridLength<Utility::FIRST>( grid.begin(),
							     grid.end() );

  TEST_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
TEUCHOS_UNIT_TEST( LinLogLog, calculateIntermediateGridLength )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3;
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LinLogLog::calculateIntermediateGridLength( 
							   x0, x1, x, L0, L1 );
  
  TEST_FLOATING_EQUALITY( Lx, 3.9542425094393248, 1e-15 );

  x = 0.1;
  
  Lx = Utility::LinLogLog::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = 1.0;

  Lx = Utility::LinLogLog::calculateIntermediateGridLength(x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
TEUCHOS_UNIT_TEST( LinLogLog, calculateIntermediateGridLimit )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3;
  double y0_min = 1e-3, y1_min = 1e-2;

  double yx_min = Utility::LinLogLog::calculateIntermediateGridLimit(
						   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, 3e-3, 1e-15 );

  x = 0.1;

  yx_min = Utility::LinLogLog::calculateIntermediateGridLimit(
						   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, 1e-3, 1e-15 );

  x = 1.0;

  yx_min = Utility::LinLogLog::calculateIntermediateGridLimit(
						   x0, x1, x, y0_min, y1_min );
  
  TEST_FLOATING_EQUALITY( yx_min, 1e-2, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LinLogLog, calculateUnitBaseIndepVar )
{
  double y_min = 1e-3, y = 1e-2, L = 3.0;

  double eta = Utility::LinLogLog::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = 1e-3;

  eta = Utility::LinLogLog::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = 0.020085536923187;

  eta = Utility::LinLogLog::calculateUnitBaseIndepVar( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LinLogLog, calculateGridIndepVar )
{
  double y_min = 1e-3, L = 3.0, eta = 0.5;

  double y =  Utility::LinLogLog::calculateGridIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.0044816890703382, 1e-12 );

  eta = 0.0;
  
  y = Utility::LinLogLog::calculateGridIndepVar( eta, y_min, L );
  
  TEST_FLOATING_EQUALITY( y, 1e-3, 1e-12 );

  eta = 1.0;

  y = Utility::LinLogLog::calculateGridIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY( y, 0.020085536923187, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-log unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL( 
				      LinLogLog, 
				      interpolateUnitBase_separate_tuple_grids,
				      ymember,
				      zmember,
				      ytuple,
				      ztuple )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.05;
  
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
  
  double z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

  TEST_FLOATING_EQUALITY( z, 1.6479753906804104, 1e-12 );

  y = 0.003; // min possible y at x = 0.3
  
  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

  TEST_FLOATING_EQUALITY( z, 0.3782355815650946, 1e-12 );

  y = 1.0; // max possible y at x = 0.5

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

  y = 0.05;
  x = 0.1;

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = 1e-3;

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

  y = 0.05;
  x = 1.0;

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = 1e-2;

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

UNIT_TEST_INSTANTIATION_2_TUPLE( LinLogLog, 
				 interpolateUnitBase_separate_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-log unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL( 
				      LinLogLog, 
				      interpolateUnitBase_combined_tuple_grids,
				      ymember,
				      zmember,
				      tuple )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.05;
  
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
  
  double z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
							      
  TEST_FLOATING_EQUALITY( z, 1.6479753906804104, 1e-12 );

  y = 0.003; // min possible y at x = 0.3
  
  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
							      
  TEST_FLOATING_EQUALITY( z, 0.3782355815650946, 1e-12 );

  y = 1.0; // max possible y at x = 0.5

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
  
  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.05;
  x = 0.1;

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
							      
  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = 1e-3;

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
  
  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = 0.05;
  x = 1.0;

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = 1e-2;

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

  z = Utility::LinLogLog::interpolateUnitBase<ymember,zmember>(
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

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE( 
			            LinLogLog,
				    interpolateUnitBase_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-log unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( LinLogLog, interpolateUnitBase_no_tuple_grids )
{
  double x0 = 0.1, x1 = 1.0, x = 0.3, y = 0.05;
  
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
  
  double z = Utility::LinLogLog::interpolateUnitBase( x0,
						      x1,
						      x,
						      y,
						      y_0_grid.begin(),
						      y_0_grid.end(),
						      z_0_grid.begin(),
						      z_0_grid.end(),
						      y_1_grid.begin(),
						      y_1_grid.end(),
						      z_1_grid.begin(),
						      z_1_grid.end() );
  
  TEST_FLOATING_EQUALITY( z, 1.6479753906804104, 1e-12 );

  y = 0.003; // min possible y at x = 0.3
  
  z = Utility::LinLogLog::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 0.3782355815650946, 1e-12 );

  y = 1.0; // max possible y at x = 0.5

  z = Utility::LinLogLog::interpolateUnitBase( x0,
					       x1,
					       x,
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

  y = 0.05;
  x = 0.1;

  z = Utility::LinLogLog::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = 1e-3;

  z = Utility::LinLogLog::interpolateUnitBase( x0,
					       x1,
					       x,
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

  z = Utility::LinLogLog::interpolateUnitBase( x0,
					       x1,
					       x,
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

  y = 0.05;
  x = 1.0;

  z = Utility::LinLogLog::interpolateUnitBase( x0,
					       x1,
					       x,
					       y,
					       y_0_grid.begin(),
					       y_0_grid.end(),
					       z_0_grid.begin(),
					       z_0_grid.end(),
					       y_1_grid.begin(),
					       y_1_grid.end(),
					       z_1_grid.begin(),
					       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = 1e-2;

  z = Utility::LinLogLog::interpolateUnitBase( x0,
					       x1,
					       x,
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

  z = Utility::LinLogLog::interpolateUnitBase( x0,
					       x1,
					       x,
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
TEUCHOS_UNIT_TEST( LinLogLog, processDepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLogLog::processDepVar( -1.0 ) );
  TEST_EQUALITY_CONST( 0.0, Utility::LinLogLog::processDepVar( 0.0 ) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLogLog::processDepVar( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a processed dependent variable can be recovered
TEUCHOS_UNIT_TEST( LinLogLog, recoverProcessedDepVar )
{
  TEST_EQUALITY_CONST( -1.0, Utility::LinLogLog::recoverProcessedDepVar(-1.0));
  TEST_EQUALITY_CONST( 0.0, Utility::LinLogLog::recoverProcessedDepVar(0.0) );
  TEST_EQUALITY_CONST( 1.0, Utility::LinLogLog::recoverProcessedDepVar(1.0) );
}

//---------------------------------------------------------------------------//
// Check that the second independent variable can be processed
TEUCHOS_UNIT_TEST( LinLogLog, processSecondIndepVar )
{
  TEST_FLOATING_EQUALITY( log(0.1), 
			  Utility::LinLogLog::processSecondIndepVar(0.1),
			  1e-15 );
  TEST_FLOATING_EQUALITY( log(1.0), 
			  Utility::LinLogLog::processSecondIndepVar(1.0),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed second independent variable can be recovered
TEUCHOS_UNIT_TEST( LinLogLog, recoverProcessedSecondIndepVar )
{
  TEST_FLOATING_EQUALITY( 
		  0.1, 
		  Utility::LinLogLog::recoverProcessedSecondIndepVar(log(0.1)),
		  1e-15 );
  TEST_FLOATING_EQUALITY( 
		  1.0, 
		  Utility::LinLogLog::recoverProcessedSecondIndepVar(log(1.0)),
		  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the first independent variable can be processed
TEUCHOS_UNIT_TEST( LinLogLog, processFirstIndepVar )
{
  TEST_FLOATING_EQUALITY( log(0.1), 
			  Utility::LinLogLog::processFirstIndepVar(0.1),
			  1e-15 );
  TEST_FLOATING_EQUALITY( log(1.0), 
			  Utility::LinLogLog::processFirstIndepVar(1.0),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a processed first independent variable can be processed
TEUCHOS_UNIT_TEST( LinLogLog, recoverProcessedFirstIndepVar )
{
  TEST_FLOATING_EQUALITY( 
		  0.1, 
		  Utility::LinLogLog::recoverProcessedFirstIndepVar(log(0.1)),
		  1e-15 );
  TEST_FLOATING_EQUALITY( 
		  1.0, 
		  Utility::LinLogLog::recoverProcessedFirstIndepVar(log(1.0)),
		  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-log interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL( 
				     LinLogLog, 
				     interpolateProcessed_separate_tuple_grids,
				     ymember,
				     zmember,
				     ytuple,
				     ztuple )
{
  double x0 = Utility::LinLogLog::processFirstIndepVar(0.1);
  double x1 = Utility::LinLogLog::processFirstIndepVar(1.0);
  double x = Utility::LinLogLog::processFirstIndepVar(0.3);
  double y = Utility::LinLogLog::processSecondIndepVar(3e-2);
  
  Teuchos::Array<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], 
			 Utility::LinLogLog::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( y_0_grid[1], 
			 Utility::LinLogLog::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( y_0_grid[2], 
			 Utility::LinLogLog::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_0_grid[3], 
			 Utility::LinLogLog::processSecondIndepVar(1.0) );
  
  Teuchos::Array<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 100.0 );
  Utility::set<zmember>( z_0_grid[1], 0.0 );
  Utility::set<zmember>( z_0_grid[2], 1.0 );
  Utility::set<zmember>( z_0_grid[3], 10.0 );
  
  Teuchos::Array<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], 
			 Utility::LinLogLog::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( y_1_grid[1], 
			 Utility::LinLogLog::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_1_grid[2], 
			 Utility::LinLogLog::processSecondIndepVar(1.0) );
  
  Teuchos::Array<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 50.0 );
  Utility::set<zmember>( z_1_grid[1], 10.0 );
  Utility::set<zmember>( z_1_grid[2], 5.0 );

  double z = Utility::LinLogLog::interpolateProcessed<ymember,zmember>(
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

  TEST_FLOATING_EQUALITY( z, 10.010220370498972, 1e-12 );

  x = Utility::LinLogLog::processFirstIndepVar(0.1);

  z = Utility::LinLogLog::interpolateProcessed<ymember,zmember>( 
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

  TEST_FLOATING_EQUALITY( z, 0.4771212547196622, 1e-12 );

  x = Utility::LinLogLog::processFirstIndepVar(1.0);
  
  z = Utility::LinLogLog::interpolateProcessed<ymember,zmember>( 
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

  TEST_FLOATING_EQUALITY( z, 20.45757490560676, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_TUPLE( LinLogLog, 
				 interpolateProcessed_separate_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-log interpolation policy between four points
// can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL( 
				     LinLogLog, 
				     interpolateProcessed_combined_tuple_grids,
				     ymember,
				     zmember,
				     tuple )
{
  double x0 = Utility::LinLogLog::processFirstIndepVar(0.1);
  double x1 = Utility::LinLogLog::processFirstIndepVar(1.0);
  double x = Utility::LinLogLog::processFirstIndepVar(0.3);
  double y = Utility::LinLogLog::processSecondIndepVar(3e-2);
  
  Teuchos::Array<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], 
			 Utility::LinLogLog::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( grid_0[1], 
			 Utility::LinLogLog::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( grid_0[2], 
			 Utility::LinLogLog::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( grid_0[3], 
			 Utility::LinLogLog::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_0[0], 100.0 );
  Utility::set<zmember>( grid_0[1], 0.0 );
  Utility::set<zmember>( grid_0[2], 1.0 );
  Utility::set<zmember>( grid_0[3], 10.0 );
  
  Teuchos::Array<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], 
			 Utility::LinLogLog::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( grid_1[1], 
			 Utility::LinLogLog::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( grid_1[2], 
			 Utility::LinLogLog::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_1[0], 50.0 );
  Utility::set<zmember>( grid_1[1], 10.0 );
  Utility::set<zmember>( grid_1[2], 5.0 );

  double z = Utility::LinLogLog::interpolateProcessed<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
							      grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
  
  TEST_FLOATING_EQUALITY( z, 10.010220370498972, 1e-12 );

  x = Utility::LinLogLog::processFirstIndepVar(0.1);

  z = Utility::LinLogLog::interpolateProcessed<ymember,zmember>( 
							x0,
							x1,
							x,
							y,
							grid_0.begin(),
							grid_0.end(),
							grid_1.begin(),
							grid_1.end() );
							
  TEST_FLOATING_EQUALITY( z, 0.4771212547196622, 1e-12 );

  x = Utility::LinLogLog::processFirstIndepVar(1.0);
  
  z = Utility::LinLogLog::interpolateProcessed<ymember,zmember>( 
							x0,
							x1,
							x,
							y,
							grid_0.begin(),
							grid_0.end(),
							grid_1.begin(),
							grid_1.end() );
							
  TEST_FLOATING_EQUALITY( z, 20.45757490560676, 1e-12 );
}

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE( 
				   LinLogLog, 
				   interpolateProcessed_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-log interpolation policy between four points
// can be done
TEUCHOS_UNIT_TEST( LinLogLog, 
		   interpolateProcessed_no_tuple_grids )
{
  double x0 = Utility::LinLogLog::processFirstIndepVar(0.1);
  double x1 = Utility::LinLogLog::processFirstIndepVar(1.0);
  double x = Utility::LinLogLog::processFirstIndepVar(0.3);
  double y = Utility::LinLogLog::processSecondIndepVar(3e-2);
  
  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[0] = Utility::LinLogLog::processSecondIndepVar(1e-3);
  y_0_grid[1] = Utility::LinLogLog::processSecondIndepVar(1e-2);
  y_0_grid[2] = Utility::LinLogLog::processSecondIndepVar(1e-1);
  y_0_grid[3] = Utility::LinLogLog::processSecondIndepVar(1.0);
  
  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[0] = 100.0;
  z_0_grid[1] = 0.0;
  z_0_grid[2] = 1.0;
  z_0_grid[3] = 10.0;
  
  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[0] = Utility::LinLogLog::processSecondIndepVar(1e-3);
  y_1_grid[1] = Utility::LinLogLog::processSecondIndepVar(1e-1);
  y_1_grid[2] = Utility::LinLogLog::processSecondIndepVar(1.0);
  
  Teuchos::Array<double> z_1_grid( 3 );
  z_1_grid[0] = 50.0;
  z_1_grid[1] = 10.0;
  z_1_grid[2] = 5.0;

  double z = Utility::LinLogLog::interpolateProcessed( x0,
						       x1,
						       x,
						       y,
						       y_0_grid.begin(),
						       y_0_grid.end(),
						       z_0_grid.begin(),
						       z_0_grid.end(),
						       y_1_grid.begin(),
						       y_1_grid.end(),
						       z_1_grid.begin(),
						       z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 10.010220370498972, 1e-12 );

  x = Utility::LinLogLog::processFirstIndepVar(0.1);

  z = Utility::LinLogLog::interpolateProcessed( x0,
						x1,
						x,
						y,
						y_0_grid.begin(),
						y_0_grid.end(),
						z_0_grid.begin(),
						z_0_grid.end(),
						y_1_grid.begin(),
						y_1_grid.end(),
						z_1_grid.begin(),
						z_1_grid.end() );
  
  TEST_FLOATING_EQUALITY( z, 0.4771212547196622, 1e-12 );

  x = Utility::LinLogLog::processFirstIndepVar(1.0);
  
  z = Utility::LinLogLog::interpolateProcessed( x0,
						x1,
						x,
						y,
						y_0_grid.begin(),
						y_0_grid.end(),
						z_0_grid.begin(),
						z_0_grid.end(),
						y_1_grid.begin(),
						y_1_grid.end(),
						z_1_grid.begin(),
						z_1_grid.end() );
  
  TEST_FLOATING_EQUALITY( z, 20.45757490560676, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid length can be calculated
UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_DECL( LinLogLog, 
						  calculateGridLengthProcessed,
						  member,
						  tuple )
{
  Teuchos::Array<tuple> tuple_grid( 4 );
  Utility::set<member>( tuple_grid[0], 
			Utility::LinLogLog::processSecondIndepVar(1e-3) );
  Utility::set<member>( tuple_grid[1], 
			Utility::LinLogLog::processSecondIndepVar(1e-2) );
  Utility::set<member>( tuple_grid[2], 
			Utility::LinLogLog::processSecondIndepVar(1e-1) );
  Utility::set<member>( tuple_grid[3], 
			Utility::LinLogLog::processSecondIndepVar(1.0) );
    
  double grid_length = 
    Utility::LinLogLog::calculateGridLengthProcessed<member>(
							    tuple_grid.begin(),
							    tuple_grid.end() );

  TEST_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

UNIT_TEST_INSTANTIATION_1_TUPLE( LinLogLog, calculateGridLengthProcessed );

//---------------------------------------------------------------------------//
// Check that the grid length can be calculated
TEUCHOS_UNIT_TEST( LinLogLog, calculateGridLengthProcessed_no_tuple )
{
  Teuchos::Array<double> grid( 4 );
  grid[0] = Utility::LinLogLog::processSecondIndepVar(1e-3);
  grid[1] = Utility::LinLogLog::processSecondIndepVar(1e-2);
  grid[2] = Utility::LinLogLog::processSecondIndepVar(1e-1);
  grid[3] = Utility::LinLogLog::processSecondIndepVar(1.0);

  double grid_length = 
    Utility::LinLogLog::calculateGridLengthProcessed<Utility::FIRST>( 
								 grid.begin(),
								 grid.end() );

  TEST_FLOATING_EQUALITY( grid_length, 6.9077552789821, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid length can be calculated
TEUCHOS_UNIT_TEST( LinLogLog, calculateIntermediateGridLengthProcessed )
{
  double x0 = Utility::LinLogLog::processFirstIndepVar(0.1);
  double x1 = Utility::LinLogLog::processFirstIndepVar(1.0);
  double x = Utility::LinLogLog::processFirstIndepVar(0.3);
  double L0 = 3.0, L1 = 5.0;

  double Lx = Utility::LinLogLog::calculateIntermediateGridLengthProcessed( 
							   x0, x1, x, L0, L1 );
  
  TEST_FLOATING_EQUALITY( Lx, 3.9542425094393248, 1e-15 );

  x = Utility::LinLogLog::processFirstIndepVar(0.1);
  
  Lx = Utility::LinLogLog::calculateIntermediateGridLengthProcessed(
							   x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 3.0, 1e-15 );

  x = Utility::LinLogLog::processFirstIndepVar(1.0);

  Lx = Utility::LinLogLog::calculateIntermediateGridLengthProcessed(
							   x0, x1, x, L0, L1 );

  TEST_FLOATING_EQUALITY( Lx, 5.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the intermediate grid min value can be calculated
TEUCHOS_UNIT_TEST( LinLogLog, calculateIntermediateProcessedGridLimit )
{
  double x0 = Utility::LinLogLog::processFirstIndepVar(0.1);
  double x1 = Utility::LinLogLog::processFirstIndepVar(1.0);
  double x = Utility::LinLogLog::processFirstIndepVar(0.3);
  double y0_min = Utility::LinLogLog::processSecondIndepVar(1e-3);
  double y1_min = Utility::LinLogLog::processSecondIndepVar(1e-2);

  double yx_min = Utility::LinLogLog::calculateIntermediateProcessedGridLimit(
						   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, 
			  Utility::LinLogLog::processSecondIndepVar(3e-3),
			  1e-15 );

  x = Utility::LinLogLog::processFirstIndepVar(0.1);

  yx_min = Utility::LinLogLog::calculateIntermediateProcessedGridLimit(
						   x0, x1, x, y0_min, y1_min );

  TEST_FLOATING_EQUALITY( yx_min, 
			  Utility::LinLogLog::processSecondIndepVar(1e-3),
			  1e-15 );

  x = Utility::LinLogLog::processFirstIndepVar(1.0);

  yx_min = Utility::LinLogLog::calculateIntermediateProcessedGridLimit(
						   x0, x1, x, y0_min, y1_min );
  
  TEST_FLOATING_EQUALITY( yx_min, 
			  Utility::LinLogLog::processSecondIndepVar(1e-2),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the unit base independent can be calculated
TEUCHOS_UNIT_TEST( LinLogLog, calculateUnitBaseIndepVarProcessed )
{
  double y_min = Utility::LinLogLog::processSecondIndepVar(1e-3);
  double y = Utility::LinLogLog::processSecondIndepVar(1e-2);
  double L = 3.0;

  double eta = Utility::LinLogLog::calculateUnitBaseIndepVarProcessed( 
								 y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.76752836433133, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(1e-3);

  eta = Utility::LinLogLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 0.0, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(0.020085536923187);

  eta = Utility::LinLogLog::calculateUnitBaseIndepVarProcessed( y, y_min, L );

  TEST_FLOATING_EQUALITY( eta, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid independent y variable can be calculated given a
// unit base independent variable
TEUCHOS_UNIT_TEST( LinLogLog, calculateProcessedGridIndepVar )
{
  double y_min = Utility::LinLogLog::processSecondIndepVar(1e-3);
  double L = 3.0, eta = 0.5;

  double y =  Utility::LinLogLog::calculateProcessedGridIndepVar( 
							       eta, y_min, L );

  TEST_FLOATING_EQUALITY( 
		 y, 
		 Utility::LinLogLog::processSecondIndepVar(0.0044816890703382),
		 1e-12 );

  eta = 0.0;
  
  y = Utility::LinLogLog::calculateProcessedGridIndepVar( eta, y_min, L );
  
  TEST_FLOATING_EQUALITY( y, 
			  Utility::LinLogLog::processSecondIndepVar(1e-3),
			  1e-12 );

  eta = 1.0;

  y = Utility::LinLogLog::calculateProcessedGridIndepVar( eta, y_min, L );

  TEST_FLOATING_EQUALITY(
		  y, 
		  Utility::LinLogLog::processSecondIndepVar(0.020085536923187),
		  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the linear-log-log unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL( 
			     LinLogLog, 
			     interpolateProcessedUnitBase_separate_tuple_grids,
			     ymember,
			     zmember,
			     ytuple,
			     ztuple )
{
  double x0 = Utility::LinLogLog::processFirstIndepVar(0.1);
  double x1 = Utility::LinLogLog::processFirstIndepVar(1.0);
  double x = Utility::LinLogLog::processFirstIndepVar(0.3);
  double y = Utility::LinLogLog::processSecondIndepVar(0.05);
  
  Teuchos::Array<ytuple> y_0_grid( 4 );
  Utility::set<ymember>( y_0_grid[0], 
			 Utility::LinLogLog::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( y_0_grid[1], 
			 Utility::LinLogLog::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( y_0_grid[2], 
			 Utility::LinLogLog::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_0_grid[3], 
			 Utility::LinLogLog::processSecondIndepVar(1.0) );
  
  Teuchos::Array<ztuple> z_0_grid( 4 );
  Utility::set<zmember>( z_0_grid[0], 0.0 );
  Utility::set<zmember>( z_0_grid[1], 1.0 );
  Utility::set<zmember>( z_0_grid[2], 2.0 );
  Utility::set<zmember>( z_0_grid[3], 3.0 );
  
  Teuchos::Array<ytuple> y_1_grid( 3 );
  Utility::set<ymember>( y_1_grid[0], 
			 Utility::LinLogLog::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( y_1_grid[1], 
			 Utility::LinLogLog::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( y_1_grid[2], 
			 Utility::LinLogLog::processSecondIndepVar(1.0) );
  
  Teuchos::Array<ztuple> z_1_grid( 3 );
  Utility::set<zmember>( z_1_grid[0], 1.0 );
  Utility::set<zmember>( z_1_grid[1], 2.0 );
  Utility::set<zmember>( z_1_grid[2], 3.0 );
  
  double z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  TEST_FLOATING_EQUALITY( z, 1.6479753906804104, 1e-12 );

  // min possible y at x = 0.3
  y = Utility::LinLogLog::processSecondIndepVar(0.003); 
  
  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  TEST_FLOATING_EQUALITY( z, 0.3782355815650946, 1e-12 );

  // max possible y at x = 0.5
  y = Utility::LinLogLog::processSecondIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LinLogLog::processSecondIndepVar(0.05);
  x = Utility::LinLogLog::processFirstIndepVar(0.1);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(1e-3);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LinLogLog::processSecondIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LinLogLog::processSecondIndepVar(0.05);
  x = Utility::LinLogLog::processFirstIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(1e-2);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
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

  y = Utility::LinLogLog::processSecondIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
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
			   LinLogLog, 
			   interpolateProcessedUnitBase_separate_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-log unit base interpolation policy between
// four points can be done
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL( 
			     LinLogLog, 
			     interpolateProcessedUnitBase_combined_tuple_grids,
			     ymember,
			     zmember,
			     tuple )
{
  double x0 = Utility::LinLogLog::processFirstIndepVar(0.1);
  double x1 = Utility::LinLogLog::processFirstIndepVar(1.0);
  double x = Utility::LinLogLog::processFirstIndepVar(0.3);
  double y = Utility::LinLogLog::processSecondIndepVar(0.05);
  
  Teuchos::Array<tuple> grid_0( 4 );
  Utility::set<ymember>( grid_0[0], 
			 Utility::LinLogLog::processSecondIndepVar(1e-3) );
  Utility::set<ymember>( grid_0[1], 
			 Utility::LinLogLog::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( grid_0[2], 
			 Utility::LinLogLog::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( grid_0[3], 
			 Utility::LinLogLog::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_0[0], 0.0 );
  Utility::set<zmember>( grid_0[1], 1.0 );
  Utility::set<zmember>( grid_0[2], 2.0 );
  Utility::set<zmember>( grid_0[3], 3.0 );
  
  Teuchos::Array<tuple> grid_1( 3 );
  Utility::set<ymember>( grid_1[0], 
			 Utility::LinLogLog::processSecondIndepVar(1e-2) );
  Utility::set<ymember>( grid_1[1], 
			 Utility::LinLogLog::processSecondIndepVar(1e-1) );
  Utility::set<ymember>( grid_1[2], 
			 Utility::LinLogLog::processSecondIndepVar(1.0) );
  Utility::set<zmember>( grid_1[0], 1.0 );
  Utility::set<zmember>( grid_1[1], 2.0 );
  Utility::set<zmember>( grid_1[2], 3.0 );
  
  double z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
							      
  TEST_FLOATING_EQUALITY( z, 1.6479753906804104, 1e-12 );

  // min possible y at x = 0.3
  y = Utility::LinLogLog::processSecondIndepVar(0.003);
  
  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
							      
  TEST_FLOATING_EQUALITY( z, 0.3782355815650946, 1e-12 );

  // max possible y at x = 0.5
  y = Utility::LinLogLog::processSecondIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
  
  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(0.05);
  x = Utility::LinLogLog::processFirstIndepVar(0.1);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
							      
  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(1e-3);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
							      
  UTILITY_TEST_FLOATING_EQUALITY( z, 0.0, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
  
  TEST_FLOATING_EQUALITY( z, 3.0, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(0.05);
  x = Utility::LinLogLog::processFirstIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );

  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(1e-2);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
							      x0,
							      x1,
							      x,
							      y,
						              grid_0.begin(),
							      grid_0.end(),
							      grid_1.begin(),
							      grid_1.end() );
							      
  TEST_FLOATING_EQUALITY( z, 1.0, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase<ymember,zmember>(
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

UNIT_TEST_INSTANTIATION_2_MEMBER_1_TUPLE( 
			   LinLogLog,
			   interpolateProcessedUnitBase_combined_tuple_grids );

//---------------------------------------------------------------------------//
// Check that the linear-log-log unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( LinLogLog, interpolateProcessedUnitBase_no_tuple_grids )
{
  double x0 = Utility::LinLogLog::processFirstIndepVar(0.1);
  double x1 = Utility::LinLogLog::processFirstIndepVar(1.0);
  double x = Utility::LinLogLog::processFirstIndepVar(0.3);
  double y = Utility::LinLogLog::processSecondIndepVar(0.05);
  
  Teuchos::Array<double> y_0_grid( 4 );
  y_0_grid[0] = Utility::LinLogLog::processSecondIndepVar(1e-3);
  y_0_grid[1] = Utility::LinLogLog::processSecondIndepVar(1e-2);
  y_0_grid[2] = Utility::LinLogLog::processSecondIndepVar(1e-1);
  y_0_grid[3] = Utility::LinLogLog::processSecondIndepVar(1.0);
  
  Teuchos::Array<double> z_0_grid( 4 );
  z_0_grid[0] = 0.0;
  z_0_grid[1] = 1.0;
  z_0_grid[2] = 2.0;
  z_0_grid[3] = 3.0;
  
  Teuchos::Array<double> y_1_grid( 3 );
  y_1_grid[0] = Utility::LinLogLog::processSecondIndepVar(1e-2);
  y_1_grid[1] = Utility::LinLogLog::processSecondIndepVar(1e-1);
  y_1_grid[2] = Utility::LinLogLog::processSecondIndepVar(1.0);
  
  Teuchos::Array<double> z_1_grid( 3 );
  z_1_grid[0] = 1.0;
  z_1_grid[1] = 2.0;
  z_1_grid[2] = 3.0;
  
  double z = Utility::LinLogLog::interpolateProcessedUnitBase( 
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
  
  TEST_FLOATING_EQUALITY( z, 1.6479753906804104, 1e-12 );

  // min possible y at x = 0.3
  y = Utility::LinLogLog::processSecondIndepVar(0.003);
  
  z = Utility::LinLogLog::interpolateProcessedUnitBase( x0,
							x1,
							x,
							y,
							y_0_grid.begin(),
							y_0_grid.end(),
							z_0_grid.begin(),
							z_0_grid.end(),
							y_1_grid.begin(),
							y_1_grid.end(),
							z_1_grid.begin(),
							z_1_grid.end() );
  
  TEST_FLOATING_EQUALITY( z, 0.3782355815650946, 1e-12 );

  // max possible y at x = 0.5
  y = Utility::LinLogLog::processSecondIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase( x0,
							x1,
							x,
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

  y = Utility::LinLogLog::processSecondIndepVar(0.05);
  x = Utility::LinLogLog::processFirstIndepVar(0.1);

  z = Utility::LinLogLog::interpolateProcessedUnitBase( x0,
							x1,
							x,
							y,
							y_0_grid.begin(),
							y_0_grid.end(),
							z_0_grid.begin(),
							z_0_grid.end(),
							y_1_grid.begin(),
							y_1_grid.end(),
							z_1_grid.begin(),
							z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(1e-3);

  z = Utility::LinLogLog::interpolateProcessedUnitBase( x0,
							x1,
							x,
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

  y = Utility::LinLogLog::processSecondIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase( x0,
							x1,
							x,
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

  y = Utility::LinLogLog::processSecondIndepVar(0.05);
  x = Utility::LinLogLog::processFirstIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase( x0,
							x1,
							x,
							y,
							y_0_grid.begin(),
							y_0_grid.end(),
							z_0_grid.begin(),
							z_0_grid.end(),
							y_1_grid.begin(),
							y_1_grid.end(),
							z_1_grid.begin(),
							z_1_grid.end() );

  TEST_FLOATING_EQUALITY( z, 1.6989700043360187, 1e-12 );

  y = Utility::LinLogLog::processSecondIndepVar(1e-2);

  z = Utility::LinLogLog::interpolateProcessedUnitBase( x0,
							x1,
							x,
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

  y = Utility::LinLogLog::processSecondIndepVar(1.0);

  z = Utility::LinLogLog::interpolateProcessedUnitBase( x0,
							x1,
							x,
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
// end tstLinLogLogTwoDInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
