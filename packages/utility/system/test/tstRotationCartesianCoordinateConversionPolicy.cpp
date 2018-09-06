//---------------------------------------------------------------------------//
//!
//! \file   tstRotationCartesianCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Rotation Cartesian coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Utility_RotationCartesianCoordinateConversionPolicy.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the local Cartesian spatial coordinates can be converted to
// global Cartesian spatial coordinates
FRENSIE_UNIT_TEST( RotationCartesianCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
   new Utility::RotationCartesianCoordinateConversionPolicy(
                                                            std::vector<double>({1.0, 1.0, 1.0}).data() ) );

  // Local z-axis
  std::array<double,3> local_position = {0.0, 0.0, 2.0};

  std::array<double,3> global_position;
  std::array<double,3> ref_global_position =
    {2.0/sqrt(3.0), 2.0/sqrt(3.0), 2.0/sqrt(3.0)};
  
  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-15 );

  // Local neg. z-axis
  local_position = {0.0, 0.0, -2.0};
  ref_global_position = {-2.0/sqrt(3.0), -2.0/sqrt(3.0), -2.0/sqrt(3.0)};

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-15 );

  // Local y-axis
  local_position = {0.0, 2.0, 0.0};
  ref_global_position = {-sqrt(2.0), sqrt(2.0), 0.0};

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-15 );

  // Local neg. y-axis
  local_position = {0.0, -2.0, 0.0};
  ref_global_position = {sqrt(2.0), -sqrt(2.0), 0.0};

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-15 );

  // Local x-axis
  local_position = {2.0, 0.0, 0.0};
  ref_global_position = {2.0/sqrt(6.0), 2.0/sqrt(6.0), -sqrt(8.0/3.0)};

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-15 );

  // Local neg. x-axis
  local_position = {-2.0, 0.0, 0.0};
  ref_global_position = {-2.0/sqrt(6.0), -2.0/sqrt(6.0), sqrt(8.0/3.0)};

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local Cartesian spatial coordinates
FRENSIE_UNIT_TEST( RotationCartesianCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
   new Utility::RotationCartesianCoordinateConversionPolicy(
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

  // To local x-axis
  std::array<double,3> global_position =
    {2.0/sqrt(6.0), 2.0/sqrt(6.0), -sqrt(8.0/3.0)};

  std::array<double,3> local_position;
  std::array<double,3> ref_local_position = {2.0, 0.0, 0.0};
  
  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );

  // To local neg. x-axis
  global_position = {-2.0/sqrt(6.0), -2.0/sqrt(6.0), sqrt(8.0/3.0)};
  ref_local_position = {-2.0, 0.0, 0.0};

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );

  // To local y-axis
  global_position = {-sqrt(2.0), sqrt(2.0), 0.0};
  ref_local_position = {0.0, 2.0, 0.0};

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );

  // To local neg. y-axis
  global_position = {sqrt(2.0), -sqrt(2.0), 0.0};
  ref_local_position = {0.0, -2.0, 0.0};

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );

  // To local z-axis
  global_position = {2.0/sqrt(3.0), 2.0/sqrt(3.0), 2.0/sqrt(3.0)};
  ref_local_position = {0.0, 0.0, 2.0};

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );

  // To local neg. z-axis
  global_position = {-2.0/sqrt(3.0), -2.0/sqrt(3.0), -2.0/sqrt(3.0)};
  ref_local_position = {0.0, 0.0, -2.0};

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the local Cartesian directional coordinates can be converted to
// global Cartesian directional coordinates
FRENSIE_UNIT_TEST( RotationCartesianCoordinateConversionPolicy,
                   convertToCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
   new Utility::RotationCartesianCoordinateConversionPolicy(
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

  // Local z-axis
  std::array<double,3> local_direction = {0.0, 0.0, 1.0};

  std::array<double,3> global_direction;
  std::array<double,3> ref_global_direction =
    {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
  
  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.data(),
                                                global_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_direction, ref_global_direction, 1e-15 );

  // Local neg. z-axis
  local_direction = {0.0, 0.0, -1.0};
  ref_global_direction = {-1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0)};

  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.data(),
                                                global_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_direction, ref_global_direction, 1e-15 );

  // Local y-axis
  local_direction = {0.0, 1.0, 0.0};
  ref_global_direction = {-sqrt(2.0)/2, sqrt(2.0)/2, 0.0};

  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.data(),
                                                global_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_direction, ref_global_direction, 1e-15 );

  // Local neg. y-axis
  local_direction = {0.0, -1.0, 0.0};
  ref_global_direction = {sqrt(2.0)/2, -sqrt(2.0)/2, 0.0};

  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.data(),
                                                global_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_direction, ref_global_direction, 1e-15 );

  // Local x-axis
  local_direction = {1.0, 0.0, 0.0};
  ref_global_direction = {1.0/sqrt(6.0), 1.0/sqrt(6.0), -sqrt(2.0/3.0)};

  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.data(),
                                                global_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_direction, ref_global_direction, 1e-15 );

  // Local neg. x-axis
  local_direction = {-1.0, 0.0, 0.0};
  ref_global_direction = {-1.0/sqrt(6.0), -1.0/sqrt(6.0), sqrt(2.0/3.0)};

  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.data(),
                                                global_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_direction, ref_global_direction, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian directional coordinates can be converted to
// local Cartesian directional coordinates
FRENSIE_UNIT_TEST( RotationCartesianCoordinateConversionPolicy,
                   convertFromCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
   new Utility::RotationCartesianCoordinateConversionPolicy(
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

  // To local x-axis
  std::array<double,3> global_direction =
    {1.0/sqrt(6.0), 1.0/sqrt(6.0), -sqrt(2.0/3.0)};

  std::array<double,3> local_direction;
  std::array<double,3> ref_local_direction = {1.0, 0.0, 0.0};
  
  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );

  // To local neg. x-axis
  global_direction = {-1.0/sqrt(6.0), -1.0/sqrt(6.0), sqrt(2.0/3.0)};
  ref_local_direction = {-1.0, 0.0, 0.0};

  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );

  // To local y-axis
  global_direction = {-sqrt(2.0)/2, sqrt(2.0)/2, 0.0};
  ref_local_direction = {0.0, 1.0, 0.0};

  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );

  // To local neg. y-axis
  global_direction = {sqrt(2.0)/2, -sqrt(2.0)/2, 0.0};
  ref_local_direction = {0.0, -1.0, 0.0};

  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );

  // To local z-axis
  global_direction = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
  ref_local_direction = {0.0, 0.0, 1.0};

  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );

  // To local neg. z-axis
  global_direction = {-1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0)};
  ref_local_direction = {0.0, 0.0, -1.0};

  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a policy can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( RotationCartesianCoordinateConversionPolicy,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_rotation_cartesian_coordinate_conversion_policy" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Utility::RotationCartesianCoordinateConversionPolicy
      concrete_policy( std::vector<double>({1.0, 1.0, 1.0}).data() );

    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      shared_spatial_policy(
         new Utility::RotationCartesianCoordinateConversionPolicy(
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );
    
    std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
      shared_directional_policy(
         new Utility::RotationCartesianCoordinateConversionPolicy(
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_policy ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_spatial_policy ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_directional_policy ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::RotationCartesianCoordinateConversionPolicy
    concrete_policy( std::vector<double>({0.0, 0.0, 1.0}).data() );

  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    shared_spatial_policy;
  
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    shared_directional_policy;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_policy ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_spatial_policy ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_directional_policy ) );
  
  iarchive.reset();

  {
    // To local x-axis
    std::array<double,3> global_position =
      {2.0/sqrt(6.0), 2.0/sqrt(6.0), -sqrt(8.0/3.0)};
    
    std::array<double,3> local_position;
    std::array<double,3> ref_local_position = {2.0, 0.0, 0.0};
  
    concrete_policy.convertFromCartesianSpatialCoordinates( global_position.data(),
                                                            local_position.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
    
    // To local neg. x-axis
    global_position = {-2.0/sqrt(6.0), -2.0/sqrt(6.0), sqrt(8.0/3.0)};
    ref_local_position = {-2.0, 0.0, 0.0};
    
    concrete_policy.convertFromCartesianSpatialCoordinates( global_position.data(),
                                                            local_position.data() );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
    
    // To local y-axis
    global_position = {-sqrt(2.0), sqrt(2.0), 0.0};
    ref_local_position = {0.0, 2.0, 0.0};
    
    concrete_policy.convertFromCartesianSpatialCoordinates( global_position.data(),
                                                            local_position.data() );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
    
    // To local neg. y-axis
    global_position = {sqrt(2.0), -sqrt(2.0), 0.0};
    ref_local_position = {0.0, -2.0, 0.0};
    
    concrete_policy.convertFromCartesianSpatialCoordinates( global_position.data(),
                                                            local_position.data() );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
    
    // To local z-axis
    global_position = {2.0/sqrt(3.0), 2.0/sqrt(3.0), 2.0/sqrt(3.0)};
    ref_local_position = {0.0, 0.0, 2.0};
    
    concrete_policy.convertFromCartesianSpatialCoordinates( global_position.data(),
                                                            local_position.data() );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
    
    // To local neg. z-axis
    global_position = {-2.0/sqrt(3.0), -2.0/sqrt(3.0), -2.0/sqrt(3.0)};
    ref_local_position = {0.0, 0.0, -2.0};
    
    concrete_policy.convertFromCartesianSpatialCoordinates( global_position.data(),
                                                            local_position.data() );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );

    // To local x-axis
    std::array<double,3> global_direction =
      {1.0/sqrt(6.0), 1.0/sqrt(6.0), -sqrt(2.0/3.0)};
    
    std::array<double,3> local_direction;
    std::array<double,3> ref_local_direction = {1.0, 0.0, 0.0};
  
    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );

    // To local neg. x-axis
    global_direction = {-1.0/sqrt(6.0), -1.0/sqrt(6.0), sqrt(2.0/3.0)};
    ref_local_direction = {-1.0, 0.0, 0.0};

    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );
    
    // To local y-axis
    global_direction = {-sqrt(2.0)/2, sqrt(2.0)/2, 0.0};
    ref_local_direction = {0.0, 1.0, 0.0};
    
    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );

    // To local neg. y-axis
    global_direction = {sqrt(2.0)/2, -sqrt(2.0)/2, 0.0};
    ref_local_direction = {0.0, -1.0, 0.0};
    
    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );
    
    // To local z-axis
    global_direction = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
    ref_local_direction = {0.0, 0.0, 1.0};
    
    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );
    
    // To local neg. z-axis
    global_direction = {-1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0)};
    ref_local_direction = {0.0, 0.0, -1.0};
    
    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );
  }

  {
    // To local x-axis
    std::array<double,3> global_position =
      {2.0/sqrt(6.0), 2.0/sqrt(6.0), -sqrt(8.0/3.0)};
    
    std::array<double,3> local_position;
    std::array<double,3> ref_local_position = {2.0, 0.0, 0.0};
  
    shared_spatial_policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                                   local_position.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
    
    // To local neg. x-axis
    global_position = {-2.0/sqrt(6.0), -2.0/sqrt(6.0), sqrt(8.0/3.0)};
    ref_local_position = {-2.0, 0.0, 0.0};
    
    shared_spatial_policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                                   local_position.data() );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
    
    // To local y-axis
    global_position = {-sqrt(2.0), sqrt(2.0), 0.0};
    ref_local_position = {0.0, 2.0, 0.0};
    
    shared_spatial_policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                                   local_position.data() );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
    
    // To local neg. y-axis
    global_position = {sqrt(2.0), -sqrt(2.0), 0.0};
    ref_local_position = {0.0, -2.0, 0.0};
    
    shared_spatial_policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                                   local_position.data() );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
    
    // To local z-axis
    global_position = {2.0/sqrt(3.0), 2.0/sqrt(3.0), 2.0/sqrt(3.0)};
    ref_local_position = {0.0, 0.0, 2.0};
    
    shared_spatial_policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                                   local_position.data() );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
    
    // To local neg. z-axis
    global_position = {-2.0/sqrt(3.0), -2.0/sqrt(3.0), -2.0/sqrt(3.0)};
    ref_local_position = {0.0, 0.0, -2.0};
    
    shared_spatial_policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                                   local_position.data() );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
  }

  {
    // To local x-axis
    std::array<double,3> global_direction =
      {1.0/sqrt(6.0), 1.0/sqrt(6.0), -sqrt(2.0/3.0)};
    
    std::array<double,3> local_direction;
    std::array<double,3> ref_local_direction = {1.0, 0.0, 0.0};
  
    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );

    // To local neg. x-axis
    global_direction = {-1.0/sqrt(6.0), -1.0/sqrt(6.0), sqrt(2.0/3.0)};
    ref_local_direction = {-1.0, 0.0, 0.0};

    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );
    
    // To local y-axis
    global_direction = {-sqrt(2.0)/2, sqrt(2.0)/2, 0.0};
    ref_local_direction = {0.0, 1.0, 0.0};
    
    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );

    // To local neg. y-axis
    global_direction = {sqrt(2.0)/2, -sqrt(2.0)/2, 0.0};
    ref_local_direction = {0.0, -1.0, 0.0};
    
    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );
    
    // To local z-axis
    global_direction = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
    ref_local_direction = {0.0, 0.0, 1.0};
    
    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );
    
    // To local neg. z-axis
    global_direction = {-1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0)};
    ref_local_direction = {0.0, 0.0, -1.0};
    
    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.data(),
                                                 local_direction.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_direction, ref_local_direction, 1e-15 );
  }
}

//---------------------------------------------------------------------------//
// end tstRotationCartesianCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
