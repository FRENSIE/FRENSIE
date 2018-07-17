//---------------------------------------------------------------------------//
//!
//! \file   tstBasicCylindricalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Basic cylindrical coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"
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
FRENSIE_UNIT_TEST( BasicCylindricalCoordinateConversionPolicy,
                   getLocalSpatialCoordinateSystemType )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
              new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  FRENSIE_CHECK_EQUAL( policy->getLocalSpatialCoordinateSystemType(),
                       Utility::CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM );
}

//---------------------------------------------------------------------------//
// Check if the primary spatial coordinate is valid
FRENSIE_UNIT_TEST( BasicCylindricalCoordinateConversionPolicy,
                   isPrimarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
              new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isPrimarySpatialCoordinateValid( 0.0 ) );
  
  FRENSIE_CHECK( policy->isPrimarySpatialCoordinateValid(
                                   std::numeric_limits<double>::infinity() ) );
}

//---------------------------------------------------------------------------//
// Check if the secondary spatial coordinate is valid
FRENSIE_UNIT_TEST( BasicCylindricalCoordinateConversionPolicy,
                   isSecondarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
              new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isSecondarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isSecondarySpatialCoordinateValid(
                                          2*Utility::PhysicalConstants::pi ) );
}

//---------------------------------------------------------------------------//
// Check if the tertiary spatial coordinate is valid
FRENSIE_UNIT_TEST( BasicCylindricalCoordinateConversionPolicy,
                   isTertiarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
              new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isTertiarySpatialCoordinateValid(
                                  -std::numeric_limits<double>::infinity() ) );

  FRENSIE_CHECK( policy->isTertiarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isTertiarySpatialCoordinateValid(
                                   std::numeric_limits<double>::infinity() ) );
}

//---------------------------------------------------------------------------//
// Check that the local cylindrical spatial coordinates can be converted to
// global Cartesian spatial coordinates
FRENSIE_UNIT_TEST( BasicCylindricalSpatialCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
              new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  // Z-axis
  std::array<double,3> local_cylindrical_position = {0.0, 0.0, 2.0};

  std::array<double,3> global_cartesian_position;

  std::array<double,3> ref_global_cartesian_position = {0.0, 0.0, 2.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-15 );

  // Neg. z-axis
  local_cylindrical_position = {0.0, 0.0, -2.0};
  ref_global_cartesian_position = {0.0, 0.0, -2.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-15 );

  // Y-axis
  local_cylindrical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};
  ref_global_cartesian_position = {0.0, 2.0, 0.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( global_cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-15 );

  // Neg. y-axis
  local_cylindrical_position = {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};
  ref_global_cartesian_position = {0.0, -2.0, 0.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( global_cartesian_position.data(), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-15 );

  // X-axis
  local_cylindrical_position = {2.0, 0.0, 0.0};
  ref_global_cartesian_position = {2.0, 0.0, 0.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-15 );

  // Neg. x-axis
  local_cylindrical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};
  ref_global_cartesian_position = {-2.0, 0.0, 0.0};

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.data(),
                                       global_cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( global_cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-15 );
  
  // Off axis
  local_cylindrical_position =
    {sqrt(2.0), Utility::PhysicalConstants::pi/4, 1.0};
  ref_global_cartesian_position = {1.0, 1.0, 1.0};

  policy->convertToCartesianSpatialCoordinates( local_cylindrical_position[0],
                                                local_cylindrical_position[1],
                                                local_cylindrical_position[2],
                                                global_cartesian_position[0],
                                                global_cartesian_position[1],
                                                global_cartesian_position[2] );

  FRENSIE_CHECK_FLOATING_EQUALITY( global_cartesian_position,
                                   ref_global_cartesian_position,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local cylindrical spatial coordinates
FRENSIE_UNIT_TEST( BasicCylindricalSpatialCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
              new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  // Z-axis
  std::array<double,3> global_cartesian_position = {0.0, 0.0, 2.0};
  
  std::array<double,3> local_cylindrical_position;

  std::array<double,3> ref_local_cylindrical_position = {0.0, 0.0, 2.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-15 );

  // Neg. z-axis
  global_cartesian_position = {0.0, 0.0, -2.0};
  ref_local_cylindrical_position = {0.0, 0.0, -2.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-15 );

  // Y-axis
  global_cartesian_position = {0.0, 2.0, 0.0};
  ref_local_cylindrical_position =
    {2.0, Utility::PhysicalConstants::pi/2, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-15 );

  // Neg. y-axis
  global_cartesian_position = {0.0, -2.0, 0.0};
  ref_local_cylindrical_position =
    {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-15 );

  // X-axis
  global_cartesian_position = {2.0, 0.0, 0.0};
  ref_local_cylindrical_position = {2.0, 0.0, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-15 );

  // Neg. x-axis
  global_cartesian_position = {-2.0, 0.0, 0.0};
  ref_local_cylindrical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-15 );

  // Off axis
  global_cartesian_position = {1.0, 1.0, 1.0};
  ref_local_cylindrical_position =
    {sqrt(2.0), Utility::PhysicalConstants::pi/4, 1.0};

  policy->convertFromCartesianSpatialCoordinates(
                                               global_cartesian_position[0],
                                               global_cartesian_position[1],
                                               global_cartesian_position[2],
                                               local_cylindrical_position[0],
                                               local_cylindrical_position[1],
                                               local_cylindrical_position[2] );
                                       

  FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                   ref_local_cylindrical_position,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a policy can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( BasicCylindricalSpatialCoordinateConversionPolicy,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_basic_cylindrical_spatial_coordinate_conversion_policy" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Utility::BasicCylindricalSpatialCoordinateConversionPolicy concrete_policy;
    
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      shared_policy(
              new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_policy ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_policy ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::BasicCylindricalSpatialCoordinateConversionPolicy concrete_policy;
    
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    shared_policy;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_policy ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_policy ) );

  iarchive.reset();

  {
    // Z-axis
    std::array<double,3> global_cartesian_position = {0.0, 0.0, 2.0};
    
    std::array<double,3> local_cylindrical_position;
    
    std::array<double,3> ref_local_cylindrical_position = {0.0, 0.0, 2.0};
    
    concrete_policy.convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // Neg. z-axis
    global_cartesian_position = {0.0, 0.0, -2.0};
    ref_local_cylindrical_position = {0.0, 0.0, -2.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // Y-axis
    global_cartesian_position = {0.0, 2.0, 0.0};
    ref_local_cylindrical_position =
      {2.0, Utility::PhysicalConstants::pi/2, 0.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // Neg. y-axis
    global_cartesian_position = {0.0, -2.0, 0.0};
    ref_local_cylindrical_position =
      {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // X-axis
    global_cartesian_position = {2.0, 0.0, 0.0};
    ref_local_cylindrical_position = {2.0, 0.0, 0.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // Neg. x-axis
    global_cartesian_position = {-2.0, 0.0, 0.0};
    ref_local_cylindrical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // Off axis
    global_cartesian_position = {1.0, 1.0, 1.0};
    ref_local_cylindrical_position =
      {sqrt(2.0), Utility::PhysicalConstants::pi/4, 1.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                               global_cartesian_position[0],
                                               global_cartesian_position[1],
                                               global_cartesian_position[2],
                                               local_cylindrical_position[0],
                                               local_cylindrical_position[1],
                                               local_cylindrical_position[2] );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );
  }

  {
    // Z-axis
    std::array<double,3> global_cartesian_position = {0.0, 0.0, 2.0};
    
    std::array<double,3> local_cylindrical_position;
    
    std::array<double,3> ref_local_cylindrical_position = {0.0, 0.0, 2.0};
    
    shared_policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // Neg. z-axis
    global_cartesian_position = {0.0, 0.0, -2.0};
    ref_local_cylindrical_position = {0.0, 0.0, -2.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // Y-axis
    global_cartesian_position = {0.0, 2.0, 0.0};
    ref_local_cylindrical_position =
      {2.0, Utility::PhysicalConstants::pi/2, 0.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // Neg. y-axis
    global_cartesian_position = {0.0, -2.0, 0.0};
    ref_local_cylindrical_position =
      {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // X-axis
    global_cartesian_position = {2.0, 0.0, 0.0};
    ref_local_cylindrical_position = {2.0, 0.0, 0.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // Neg. x-axis
    global_cartesian_position = {-2.0, 0.0, 0.0};
    ref_local_cylindrical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.data(),
                                      local_cylindrical_position.data() );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );

    // Off axis
    global_cartesian_position = {1.0, 1.0, 1.0};
    ref_local_cylindrical_position =
      {sqrt(2.0), Utility::PhysicalConstants::pi/4, 1.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                               global_cartesian_position[0],
                                               global_cartesian_position[1],
                                               global_cartesian_position[2],
                                               local_cylindrical_position[0],
                                               local_cylindrical_position[1],
                                               local_cylindrical_position[2] );
                                       

    FRENSIE_CHECK_FLOATING_EQUALITY( local_cylindrical_position,
                                     ref_local_cylindrical_position,
                                     1e-15 );
  }
}

//---------------------------------------------------------------------------//
// end tstBasicCylindricalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
