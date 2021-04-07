//---------------------------------------------------------------------------//
//!
//! \file   tstBasicSphericalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Basic spherical coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the local spatial coordinate system type can be returned
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   getLocalSpatialCoordinateSystemType )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  FRENSIE_CHECK_EQUAL( policy->getLocalSpatialCoordinateSystemType(),
                       Utility::SPHERICAL_SPATIAL_COORDINATE_SYSTEM );
}

//---------------------------------------------------------------------------//
// Check if the primary spatial coordinate is valid
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isPrimarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isPrimarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isPrimarySpatialCoordinateValid(
                                   std::numeric_limits<double>::infinity() ) );
}

//---------------------------------------------------------------------------//
// Check if the secondary spatial coordinate is valid
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isSecondarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isSecondarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isSecondarySpatialCoordinateValid(
                                          2*Utility::PhysicalConstants::pi ) );
}

//---------------------------------------------------------------------------//
// Check if the tertiary spatial coordinate is valid
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isTertiarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isTertiarySpatialCoordinateValid( -1.0 ) );
  
  FRENSIE_CHECK( policy->isTertiarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isTertiarySpatialCoordinateValid( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the local directional coordinate system type can be returned
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   getLocalDirectionalCoordinateSystemType )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  FRENSIE_CHECK_EQUAL( policy->getLocalDirectionalCoordinateSystemType(),
                       Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM );
}

//---------------------------------------------------------------------------//
// Check if the primary directional coordinate is valid
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isPrimaryDirectionalCoordinateValid )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  FRENSIE_CHECK( !policy->isPrimaryDirectionalCoordinateValid( -0.99 ) );
  FRENSIE_CHECK( policy->isPrimaryDirectionalCoordinateValid( 1.0 ) );
  FRENSIE_CHECK( !policy->isPrimaryDirectionalCoordinateValid( 1.01 ) );
}

//---------------------------------------------------------------------------//
// Check if the secondary directional coordinate is valid
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isSecondaryDirectionalCoordinateValid )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isSecondaryDirectionalCoordinateValid( 0.0 ) );

  FRENSIE_CHECK( policy->isSecondaryDirectionalCoordinateValid(
                                          2*Utility::PhysicalConstants::pi ) );
}

//---------------------------------------------------------------------------//
// Check if the tertiary directional coordinate is valid
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isTertiaryDirectionalCoordinateValid )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isTertiaryDirectionalCoordinateValid( -1.0 ) );

  FRENSIE_CHECK( policy->isTertiaryDirectionalCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isTertiaryDirectionalCoordinateValid( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the local spherical spatial coordinates can be converted to
// global Cartesian spatial coordinates
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  // Z-axis
  std::array<double,3> local_spherical_position = {2.0, 0.0, 1.0};

  std::array<double,3> global_cartesian_position;
  
  std::array<double,3> ref_global_cartesian_position = {0.0, 0.0, 2.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                        ref_global_cartesian_position,
                                        1e-15 );

  // Neg. z-axis
  local_spherical_position = {2.0, 0.0, -1.0};
  ref_global_cartesian_position = {0.0, 0.0, -2.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                        ref_global_cartesian_position,
                                        1e-15 );

  // Y-axis
  local_spherical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};
  ref_global_cartesian_position = {0.0, 2.0, 0.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( global_cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-15 );

  // Neg y-axis
  local_spherical_position = {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};
  ref_global_cartesian_position = {0.0, -2.0, 0.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( global_cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-15 );

  // X-axis
  local_spherical_position = {2.0, 0.0, 0.0};
  ref_global_cartesian_position = {2.0, 0.0, 0.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                        ref_global_cartesian_position,
                                        1e-15 );

  // Neg. x-axis
  local_spherical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};
  ref_global_cartesian_position = {-2.0, 0.0, 0.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.data(),
                                       global_cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( global_cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-15 );

  // Off axis
  local_spherical_position =
    {sqrt(3.0), Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};
  ref_global_cartesian_position = {1.0, 1.0, 1.0};

  policy->convertToCartesianSpatialCoordinates( local_spherical_position[0],
                                                local_spherical_position[1],
                                                local_spherical_position[2],
                                                global_cartesian_position[0],
                                                global_cartesian_position[1],
                                                global_cartesian_position[2] );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                        ref_global_cartesian_position,
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local spherical spatial coordinates
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  // Z-axis
  std::array<double,3> global_cartesian_position = {0.0, 0.0, 2.0};

  std::array<double,3> local_spherical_position;
  
  std::array<double,3> ref_local_spherical_position = {2.0, 0.0, 1.0};

  policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                        ref_local_spherical_position,
                                        1e-15 );

  // Neg. z-axis
  global_cartesian_position = {0.0, 0.0, -2.0};
  ref_local_spherical_position = {2.0, 0.0, -1.0};

  policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                        ref_local_spherical_position,
                                        1e-15 );

  // Y-axis
  global_cartesian_position = {0.0, 2.0, 0.0};
  ref_local_spherical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                        ref_local_spherical_position,
                                        1e-15 );

  // Neg. y-axis
  global_cartesian_position = {0.0, -2.0, 0.0};
  ref_local_spherical_position =
    {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                        ref_local_spherical_position,
                                        1e-15 );

  // X-axis
  global_cartesian_position = {2.0, 0.0, 0.0};
  ref_local_spherical_position = {2.0, 0.0, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                        ref_local_spherical_position,
                                        1e-15 );

  // Off axis
  global_cartesian_position = {1.0, 1.0, 1.0};
  ref_local_spherical_position =
    {sqrt(3.0), Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};

  policy->convertFromCartesianSpatialCoordinates(
                                                 global_cartesian_position[0],
                                                 global_cartesian_position[1],
                                                 global_cartesian_position[2],
                                                 local_spherical_position[0],
                                                 local_spherical_position[1],
                                                 local_spherical_position[2] );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                   ref_local_spherical_position,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the local spherical directional coordinates can be converted
// to global Cartesian directional coordinates
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   convertToCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  // Z-axis
  std::array<double,3> local_spherical_direction = {1.0, 0.0, 1.0};

  std::array<double,3> global_cartesian_direction;
  
  std::array<double,3> ref_global_cartesian_direction = {0.0, 0.0, 1.0};

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.data(),
                                      global_cartesian_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_direction,
                                        ref_global_cartesian_direction,
                                        1e-15 );

  // Neg. z-axis
  local_spherical_direction = {1.0, 0.0, -1.0};
  ref_global_cartesian_direction = {0.0, 0.0, -1.0};

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.data(),
                                      global_cartesian_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_direction,
                                        ref_global_cartesian_direction,
                                        1e-15 );

  // Y-axis
  local_spherical_direction = {1.0, Utility::PhysicalConstants::pi/2, 0.0};
  ref_global_cartesian_direction = {0.0, 1.0, 0.0};

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.data(),
                                      global_cartesian_direction.data() );
  Utility::clearUnitVectorOfRoundingErrors( global_cartesian_direction.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_direction,
                                   ref_global_cartesian_direction,
                                   1e-15 );

  // Neg y-axis
  local_spherical_direction = {1.0, 3*Utility::PhysicalConstants::pi/2, 0.0};
  ref_global_cartesian_direction = {0.0, -1.0, 0.0};

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.data(),
                                      global_cartesian_direction.data() );
  Utility::clearUnitVectorOfRoundingErrors( global_cartesian_direction.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_direction,
                                   ref_global_cartesian_direction,
                                   1e-15 );

  // X-axis
  local_spherical_direction = {1.0, 0.0, 0.0};
  ref_global_cartesian_direction = {1.0, 0.0, 0.0};

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.data(),
                                      global_cartesian_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_direction,
                                        ref_global_cartesian_direction,
                                        1e-15 );

  // Neg. x-axis
  local_spherical_direction = {1.0, Utility::PhysicalConstants::pi, 0.0};
  ref_global_cartesian_direction = {-1.0, 0.0, 0.0};

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.data(),
                                      global_cartesian_direction.data() );
  Utility::clearUnitVectorOfRoundingErrors( global_cartesian_direction.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_direction,
                                   ref_global_cartesian_direction,
                                   1e-15 );

  // Off axis
  local_spherical_direction =
    {1.0/sqrt(3.0), Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};
  ref_global_cartesian_direction =
    {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};

  policy->convertToCartesianDirectionalCoordinates(
                                               local_spherical_direction[0],
                                               local_spherical_direction[1],
                                               local_spherical_direction[2],
                                               global_cartesian_direction[0],
                                               global_cartesian_direction[1],
                                               global_cartesian_direction[2] );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_direction,
                                        ref_global_cartesian_direction,
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian directional coordinates can be converted
// to local spherical directional coordinates
FRENSIE_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   convertFromCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  // Z-axis
  std::array<double,3> global_cartesian_direction = {0.0, 0.0, 1.0};

  std::array<double,3> local_spherical_direction;
  
  std::array<double,3> ref_local_spherical_direction = {1.0, 0.0, 1.0};

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                        ref_local_spherical_direction,
                                        1e-15 );

  // Neg. z-axis
  global_cartesian_direction = {0.0, 0.0, -1.0};
  ref_local_spherical_direction = {1.0, 0.0, -1.0};

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                        ref_local_spherical_direction,
                                        1e-15 );

  // Y-axis
  global_cartesian_direction = {0.0, 1.0, 0.0};
  ref_local_spherical_direction = {1.0, Utility::PhysicalConstants::pi/2, 0.0};

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                        ref_local_spherical_direction,
                                        1e-15 );

  // Neg. y-axis
  global_cartesian_direction = {0.0, -1.0, 0.0};
  ref_local_spherical_direction =
    {1.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                        ref_local_spherical_direction,
                                        1e-15 );

  // X-axis
  global_cartesian_direction = {1.0, 0.0, 0.0};
  ref_local_spherical_direction = {1.0, 0.0, 0.0};

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                        ref_local_spherical_direction,
                                        1e-15 );

  // Off axis
  global_cartesian_direction = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
  ref_local_spherical_direction =
    {1.0, Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};

  policy->convertFromCartesianDirectionalCoordinates(
                                                global_cartesian_direction[0],
                                                global_cartesian_direction[1],
                                                global_cartesian_direction[2],
                                                local_spherical_direction[0],
                                                local_spherical_direction[1],
                                                local_spherical_direction[2] );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                        ref_local_spherical_direction,
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a policy can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( BasicSphericalCoordinateConversionPolicy,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_basic_spherical_coordinate_conversion_policy" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Utility::BasicSphericalCoordinateConversionPolicy concrete_policy;

    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      shared_spatial_policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

    std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
      shared_directional_policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_policy ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_spatial_policy ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_directional_policy ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::BasicSphericalCoordinateConversionPolicy concrete_policy;

  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    shared_spatial_policy;

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    shared_directional_policy;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_policy ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_spatial_policy ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_directional_policy ) );

  iarchive.reset();

  {
    // Z-axis
    std::array<double,3> global_cartesian_position = {0.0, 0.0, 2.0};
    
    std::array<double,3> local_spherical_position;
    
    std::array<double,3> ref_local_spherical_position = {2.0, 0.0, 1.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // Neg. z-axis
    global_cartesian_position = {0.0, 0.0, -2.0};
    ref_local_spherical_position = {2.0, 0.0, -1.0};
    
    concrete_policy.convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // Y-axis
    global_cartesian_position = {0.0, 2.0, 0.0};
    ref_local_spherical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};
    
    concrete_policy.convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // Neg. y-axis
    global_cartesian_position = {0.0, -2.0, 0.0};
    ref_local_spherical_position =
      {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // X-axis
    global_cartesian_position = {2.0, 0.0, 0.0};
    ref_local_spherical_position = {2.0, 0.0, 0.0};
    
    concrete_policy.convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // Off axis
    global_cartesian_position = {1.0, 1.0, 1.0};
    ref_local_spherical_position =
      {sqrt(3.0), Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};
    
    concrete_policy.convertFromCartesianSpatialCoordinates(
                                                 global_cartesian_position[0],
                                                 global_cartesian_position[1],
                                                 global_cartesian_position[2],
                                                 local_spherical_position[0],
                                                 local_spherical_position[1],
                                                 local_spherical_position[2] );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // Z-axis
    std::array<double,3> global_cartesian_direction = {0.0, 0.0, 1.0};

    std::array<double,3> local_spherical_direction;
    
    std::array<double,3> ref_local_spherical_direction = {1.0, 0.0, 1.0};

    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );

    // Neg. z-axis
    global_cartesian_direction = {0.0, 0.0, -1.0};
    ref_local_spherical_direction = {1.0, 0.0, -1.0};

    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );

    // Y-axis
    global_cartesian_direction = {0.0, 1.0, 0.0};
    ref_local_spherical_direction = {1.0, Utility::PhysicalConstants::pi/2, 0.0};
    
    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );

    // Neg. y-axis
    global_cartesian_direction = {0.0, -1.0, 0.0};
    ref_local_spherical_direction =
      {1.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );

    // X-axis
    global_cartesian_direction = {1.0, 0.0, 0.0};
    ref_local_spherical_direction = {1.0, 0.0, 0.0};

    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );

    // Off axis
    global_cartesian_direction = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
    ref_local_spherical_direction =
      {1.0, Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};

    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                                global_cartesian_direction[0],
                                                global_cartesian_direction[1],
                                                global_cartesian_direction[2],
                                                local_spherical_direction[0],
                                                local_spherical_direction[1],
                                                local_spherical_direction[2] );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );
  }

  {
    // Z-axis
    std::array<double,3> global_cartesian_position = {0.0, 0.0, 2.0};
    
    std::array<double,3> local_spherical_position;
    
    std::array<double,3> ref_local_spherical_position = {2.0, 0.0, 1.0};

    shared_spatial_policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // Neg. z-axis
    global_cartesian_position = {0.0, 0.0, -2.0};
    ref_local_spherical_position = {2.0, 0.0, -1.0};
    
    shared_spatial_policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // Y-axis
    global_cartesian_position = {0.0, 2.0, 0.0};
    ref_local_spherical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};
    
    shared_spatial_policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // Neg. y-axis
    global_cartesian_position = {0.0, -2.0, 0.0};
    ref_local_spherical_position =
      {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

    shared_spatial_policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // X-axis
    global_cartesian_position = {2.0, 0.0, 0.0};
    ref_local_spherical_position = {2.0, 0.0, 0.0};
    
    shared_spatial_policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.data(),
                                       local_spherical_position.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );

    // Off axis
    global_cartesian_position = {1.0, 1.0, 1.0};
    ref_local_spherical_position =
      {sqrt(3.0), Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};
    
    shared_spatial_policy->convertFromCartesianSpatialCoordinates(
                                                 global_cartesian_position[0],
                                                 global_cartesian_position[1],
                                                 global_cartesian_position[2],
                                                 local_spherical_position[0],
                                                 local_spherical_position[1],
                                                 local_spherical_position[2] );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_position,
                                     ref_local_spherical_position,
                                     1e-15 );
  }

  {
    // Z-axis
    std::array<double,3> global_cartesian_direction = {0.0, 0.0, 1.0};

    std::array<double,3> local_spherical_direction;
    
    std::array<double,3> ref_local_spherical_direction = {1.0, 0.0, 1.0};

    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );

    // Neg. z-axis
    global_cartesian_direction = {0.0, 0.0, -1.0};
    ref_local_spherical_direction = {1.0, 0.0, -1.0};

    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );

    // Y-axis
    global_cartesian_direction = {0.0, 1.0, 0.0};
    ref_local_spherical_direction = {1.0, Utility::PhysicalConstants::pi/2, 0.0};
    
    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );

    // Neg. y-axis
    global_cartesian_direction = {0.0, -1.0, 0.0};
    ref_local_spherical_direction =
      {1.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );

    // X-axis
    global_cartesian_direction = {1.0, 0.0, 0.0};
    ref_local_spherical_direction = {1.0, 0.0, 0.0};

    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.data(),
                                       local_spherical_direction.data() );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );

    // Off axis
    global_cartesian_direction = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
    ref_local_spherical_direction =
      {1.0, Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};

    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                                global_cartesian_direction[0],
                                                global_cartesian_direction[1],
                                                global_cartesian_direction[2],
                                                local_spherical_direction[0],
                                                local_spherical_direction[1],
                                                local_spherical_direction[2] );

    FRENSIE_CHECK_FLOATING_EQUALITY( local_spherical_direction,
                                     ref_local_spherical_direction,
                                     1e-15 );
  }
}

//---------------------------------------------------------------------------//
// end tstBasicSphericalCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
