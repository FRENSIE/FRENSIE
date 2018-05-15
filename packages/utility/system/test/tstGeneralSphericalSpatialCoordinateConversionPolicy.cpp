//---------------------------------------------------------------------------//
//!
//! \file   tstGeneralSphericalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  General spherical spatial coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the local spherical spatial coordinates can be converted to
// global Cartesian spatial coordinates
FRENSIE_UNIT_TEST( GeneralSphericalSpatialCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
               new Utility::GeneralSphericalSpatialCoordinateConversionPolicy(
                               std::vector<double>({2.0, -1.0, 0.1}).data(),
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

  // Local z-axis
  std::array<double,3> local_spherical_position = {2.0, 0.0, 1.0};

  std::array<double,3> global_cartesian_position;
  std::array<double,3> ref_global_cartesian_position =
    {2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );

  // Local neg. z-axis
  local_spherical_position = {2.0, 0.0, -1.0};
  ref_global_cartesian_position =
    {-2.0/sqrt(3.0)+2.0, -2.0/sqrt(3.0)-1.0, -2.0/sqrt(3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );

  // Local y-axis
  local_spherical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};
  ref_global_cartesian_position = {-sqrt(2.0)+2.0, sqrt(2.0)-1.0, 0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );

  // Local neg. y-axis
  local_spherical_position = {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};
  ref_global_cartesian_position = {sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );

  // Local x-axis
  local_spherical_position = {2.0, 0.0, 0.0};
  ref_global_cartesian_position =
    {2.0/sqrt(6.0)+2.0, 2.0/sqrt(6.0)-1.0, -sqrt(8.0/3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );

  // Local neg. x-axis
  local_spherical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};
  ref_global_cartesian_position =
    {-2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local spherical spatial coordinates
FRENSIE_UNIT_TEST( GeneralSphericalSpatialCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                new Utility::GeneralSphericalSpatialCoordinateConversionPolicy(
                               std::vector<double>({2.0, -1.0, 0.1}).data(),
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

  // Local z-axis
  std::array<double,3> global_cartesian_position =
    {2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1};

  std::array<double,3> local_spherical_position;
  std::array<double,3> ref_local_spherical_position = {2.0, 0.0, 1.0};
  
  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.data(),
                                        local_spherical_position.data() );
                                       
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                   ref_local_spherical_position,
                                   1e-15 );

  // Local neg. z-axis
  global_cartesian_position =
    {-2.0/sqrt(3.0)+2.0, -2.0/sqrt(3.0)-1.0, -2.0/sqrt(3.0)+0.1};
  ref_local_spherical_position = {2.0, 0.0, -1.0};

  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.data(),
                                        local_spherical_position.data() );
                                       
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                   ref_local_spherical_position,
                                   1e-15 );

  // Local y-axis
  global_cartesian_position = {-sqrt(2.0)+2.0, sqrt(2.0)-1.0, 0.1};
  ref_local_spherical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.data(),
                                        local_spherical_position.data() );
                                       
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                   ref_local_spherical_position,
                                   1e-15 );

  // Local neg. y-axis
  global_cartesian_position = {sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1};
  ref_local_spherical_position =
    {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.data(),
                                        local_spherical_position.data() );
                                       
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                   ref_local_spherical_position,
                                   1e-15 );

  // Local x-axis
  global_cartesian_position =
    {2.0/sqrt(6.0)+2.0, 2.0/sqrt(6.0)-1.0, -sqrt(8.0/3.0)+0.1};
  ref_local_spherical_position = {2.0, 0.0, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.data(),
                                        local_spherical_position.data() );
                                       
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                   ref_local_spherical_position,
                                   1e-15 );

  // Local neg. x-axis
  global_cartesian_position =
    {-2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1};
  ref_local_spherical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.data(),
                                        local_spherical_position.data() );
                                       
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                   ref_local_spherical_position,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// end tstGeneralSphericalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
