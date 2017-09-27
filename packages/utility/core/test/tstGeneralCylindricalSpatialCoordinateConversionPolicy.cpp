//---------------------------------------------------------------------------//
//!
//! \file tstGeneralCylindricalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  General cylindrical spatial coordinate conversion policy tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Utility_GeneralCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the local cylindrical spatial coordinates can be converted to
// global Cartesian spatial coordinates
FRENSIE_UNIT_TEST( GeneralCylindricalSpatialCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  // Local z-axis
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
             new Utility::GeneralCylindricalSpatialCoordinateConversionPolicy(
                               std::vector<double>({2.0, -1.0, 0.1}).data(),
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );
  
  std::array<double,3> local_cylindrical_position = {0.0, 0.0, 2.0};

  std::array<double,3> global_cartesian_position;
  std::array<double,3> ref_global_cartesian_position =
    {2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );

  // Local neg. z-axis
  local_cylindrical_position = {0.0, 0.0, -2.0};
  ref_global_cartesian_position =
    {-2.0/sqrt(3.0)+2.0, -2.0/sqrt(3.0)-1.0, -2.0/sqrt(3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );

  // Local y-axis
  local_cylindrical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};
  ref_global_cartesian_position = {-sqrt(2.0)+2.0, sqrt(2.0)-1.0, 0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );

  // Local neg. y-axis
  local_cylindrical_position = {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};
  ref_global_cartesian_position = {sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );

  // Local x-axis
  local_cylindrical_position = {2.0, 0.0, 0.0};
  ref_global_cartesian_position =
    {2.0/sqrt(6.0)+2.0, 2.0/sqrt(6.0)-1.0, -sqrt(8.0/3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );

  // Local neg. x-axis
  local_cylindrical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};
  ref_global_cartesian_position =
    {-2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );  
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local cylindrical spatial coordinates
FRENSIE_UNIT_TEST( GeneralCylindricalSpatialCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  // Local z-axis
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
             new Utility::GeneralCylindricalSpatialCoordinateConversionPolicy(
                               std::vector<double>({2.0, -1.0, 0.1}).data(),
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

  std::array<double,3> global_cartesian_position =
    {2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1};

  std::array<double,3> local_cylindrical_position;
  std::array<double,3> ref_local_cylindrical_position = {0.0, 0.0, 2.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-14 );

  // Local neg. z-axis
  global_cartesian_position =
    {-2.0/sqrt(3.0)+2.0, -2.0/sqrt(3.0)-1.0, -2.0/sqrt(3.0)+0.1};
  ref_local_cylindrical_position = {0.0, 0.0, -2.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-14 );

  // Local y-axis
  global_cartesian_position = {-sqrt(2.0)+2.0, sqrt(2.0)-1.0, 0.1};
  ref_local_cylindrical_position =
    {2.0, Utility::PhysicalConstants::pi/2, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-14 );

  // Local neg. y-axis
  global_cartesian_position = {sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1};
  ref_local_cylindrical_position =
    {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-14 );

  // Local x-axis
  global_cartesian_position =
    {2.0/sqrt(6.0)+2.0, 2.0/sqrt(6.0)-1.0, -sqrt(8.0/3.0)+0.1};
  ref_local_cylindrical_position = {2.0, 0.0, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-14 );
  
  // Local neg. x-axis
  global_cartesian_position =
    {-2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1};
  ref_local_cylindrical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-14 );
}

//---------------------------------------------------------------------------//
// tstGeneralCylindricalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
