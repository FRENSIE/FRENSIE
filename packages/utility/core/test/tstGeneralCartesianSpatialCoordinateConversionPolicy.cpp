//---------------------------------------------------------------------------//
//!
//! \file   tstGeneralCartesianSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  General Cartesian spatial coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the local Cartesian spatial coordinates can be converted to
// global Cartesian spatial coordinates
TEUCHOS_UNIT_TEST( GeneralCartesianSpatialCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
   new Utility::GeneralCartesianSpatialCoordinateConversionPolicy(
                                 Teuchos::tuple( 2.0, -1.0, 0.1 ).getRawPtr(),
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

  // Local z-axis
  Teuchos::Tuple<double,3> local_position = Teuchos::tuple( 0.0, 0.0, 2.0 );

  Teuchos::Tuple<double,3> global_position;
  Teuchos::Tuple<double,3> ref_global_position =
    Teuchos::tuple( 2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1 );
  
  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-14 );

  // Local neg. z-axis
  local_position = Teuchos::tuple( 0.0, 0.0, -2.0 );
  ref_global_position =
    Teuchos::tuple( -2.0/sqrt(3.0)+2.0, -2.0/sqrt(3.0)-1.0, -2.0/sqrt(3.0)+0.1 );

  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-14 );

  // Local y-axis
  local_position = Teuchos::tuple( 0.0, 2.0, 0.0 );
  ref_global_position = Teuchos::tuple( -sqrt(2.0)+2.0, sqrt(2.0)-1.0, 0.1 );

  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-14 );

  // Local neg. y-axis
  local_position = Teuchos::tuple( 0.0, -2.0, 0.0 );
  ref_global_position = Teuchos::tuple( sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1 );

  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-14 );

  // Local x-axis
  local_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_global_position =
    Teuchos::tuple( 2.0/sqrt(6.0)+2.0, 2.0/sqrt(6.0)-1.0, -sqrt(8.0/3.0)+0.1 );

  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-14 );

  // Local neg. x-axis
  local_position = Teuchos::tuple( -2.0, 0.0, 0.0 );
  ref_global_position =
    Teuchos::tuple( -2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1 );

  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local Cartesian spatial coordinates
TEUCHOS_UNIT_TEST( GeneralCartesianSpatialCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
   new Utility::GeneralCartesianSpatialCoordinateConversionPolicy(
                                 Teuchos::tuple(2.0, -1.0, 0.1).getRawPtr(),
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

  // To local x-axis
  Teuchos::Tuple<double,3> global_position =
    Teuchos::tuple( 2.0/sqrt(6.0)+2.0, 2.0/sqrt(6.0)-1.0, -sqrt(8.0/3.0)+0.1 );

  Teuchos::Tuple<double,3> local_position;
  Teuchos::Tuple<double,3> ref_local_position =
    Teuchos::tuple( 2.0, 0.0, 0.0 );
  
  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-14 );

  // To local neg. x-axis
  global_position =
    Teuchos::tuple( -2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1 );
  ref_local_position = Teuchos::tuple( -2.0, 0.0, 0.0 );

  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-14 );

  // To local y-axis
  global_position = Teuchos::tuple( -sqrt(2.0)+2.0, sqrt(2.0)-1.0, 0.1 );
  ref_local_position = Teuchos::tuple( 0.0, 2.0, 0.0 );

  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-14 );

  // To local neg. y-axis
  global_position = Teuchos::tuple( sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1 );
  ref_local_position = Teuchos::tuple( 0.0, -2.0, 0.0 );

  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-14 );

  // To local z-axis
  global_position =
    Teuchos::tuple( 2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1 );
  ref_local_position = Teuchos::tuple( 0.0, 0.0, 2.0 );

  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-14 );

  // To local neg. z-axis
  global_position =
    Teuchos::tuple( -2.0/sqrt(3.0)+2.0, -2.0/sqrt(3.0)-1.0, -2.0/sqrt(3.0)+0.1 );
  ref_local_position = Teuchos::tuple( 0.0, 0.0, -2.0 );

  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-14 );
}

//---------------------------------------------------------------------------//
// end tstGeneralCartesianSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
