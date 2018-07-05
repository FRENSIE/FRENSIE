//---------------------------------------------------------------------------//
//!
//! \file   tstBasicCartesianCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Basic Cartesian coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_Vector.hpp"
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
// Check that the local spatial coordinate system type can be returned
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   getLocalSpatialCoordinateSystemType )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  FRENSIE_CHECK_EQUAL( policy->getLocalSpatialCoordinateSystemType(),
                       Utility::CARTESIAN_SPATIAL_COORDINATE_SYSTEM );
}

//---------------------------------------------------------------------------//
// Check if the primary spatial coordinate is valid
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   isPrimarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isPrimarySpatialCoordinateValid(
                                  -std::numeric_limits<double>::infinity() ) );

  FRENSIE_CHECK( policy->isPrimarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isPrimarySpatialCoordinateValid(
                                   std::numeric_limits<double>::infinity() ) );
}

//---------------------------------------------------------------------------//
// Check if the secondary spatial coordinate is valid
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   isSecondarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isSecondarySpatialCoordinateValid(
                                  -std::numeric_limits<double>::infinity() ) );

  FRENSIE_CHECK( policy->isSecondarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isSecondarySpatialCoordinateValid(
                                   std::numeric_limits<double>::infinity() ) );
}

//---------------------------------------------------------------------------//
// Check if the tertiary spatial coordinate is valid
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   isTertiarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isTertiarySpatialCoordinateValid(
                                  -std::numeric_limits<double>::infinity() ) );

  FRENSIE_CHECK( policy->isTertiarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isTertiarySpatialCoordinateValid(
                                   std::numeric_limits<double>::infinity() ) );
}

//---------------------------------------------------------------------------//
// Check that the local directional coordinate system type can be returned
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   getLocalDirectionalCoordinateSystemType )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  FRENSIE_CHECK_EQUAL( policy->getLocalDirectionalCoordinateSystemType(),
                       Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM );
}

//---------------------------------------------------------------------------//
// Check if the primary directional coordinate is valid
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   isPrimaryDirectionalCoordinateValid )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isPrimaryDirectionalCoordinateValid( -1.0 ) );

  FRENSIE_CHECK( policy->isPrimaryDirectionalCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isPrimaryDirectionalCoordinateValid( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check if the secondary directional coordinate is valid
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   isSecondaryDirectionalCoordinateValid )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isSecondaryDirectionalCoordinateValid( -1.0 ) );

  FRENSIE_CHECK( policy->isSecondaryDirectionalCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isSecondaryDirectionalCoordinateValid( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check if the tertiary directional coordinate is valid
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   isTertiaryDirectionalCoordinateValid )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  FRENSIE_CHECK( policy->isTertiaryDirectionalCoordinateValid( -1.0 ) );

  FRENSIE_CHECK( policy->isTertiaryDirectionalCoordinateValid( 0.0 ) );
                                                       
  
  FRENSIE_CHECK( policy->isTertiaryDirectionalCoordinateValid( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the input directional coordinates can be converted to Cartesian
// coordinates
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  std::vector<double> input_position( 3 );
  input_position[0] = 1.0;
  input_position[1] = 1.0;
  input_position[2] = 1.0;

  std::vector<double> output_position( 3 );

  policy->convertToCartesianSpatialCoordinates( input_position.data(),
                                                output_position.data() );

  FRENSIE_CHECK_EQUAL( input_position, output_position );

  input_position[0] = 2.0;
  input_position[1] = -1.0;
  input_position[2] = 0.1;

  policy->convertToCartesianSpatialCoordinates( input_position[0],
                                                input_position[1],
                                                input_position[2],
                                                output_position[0],
                                                output_position[1],
                                                output_position[2] );

  FRENSIE_CHECK_EQUAL( input_position, output_position );
}

//---------------------------------------------------------------------------//
// Check that the input Cartesian coordinates can be converted to the
// spatial coordinates
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  std::vector<double> input_position( 3 );
  input_position[0] = 1.0;
  input_position[1] = 1.0;
  input_position[2] = 1.0;

  std::vector<double> output_position( 3 );

  policy->convertFromCartesianSpatialCoordinates( input_position.data(),
                                                  output_position.data());

  FRENSIE_CHECK_EQUAL( input_position, output_position );

  input_position[0] = 2.0;
  input_position[1] = -1.0;
  input_position[2] = 0.1;

  policy->convertToCartesianSpatialCoordinates( input_position[0],
                                                input_position[1],
                                                input_position[2],
                                                output_position[0],
                                                output_position[1],
                                                output_position[2] );

  FRENSIE_CHECK_EQUAL( input_position, output_position );
}

//---------------------------------------------------------------------------//
// Check that the input directional coordinates can be converted to Cartesian
// coordinates
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   convertToCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  std::vector<double> input_direction( 3 );
  input_direction[0] = 1.0/sqrt(3.0);
  input_direction[1] = 1.0/sqrt(3.0);
  input_direction[2] = 1.0/sqrt(3.0);

  std::vector<double> output_direction( 3 );

  policy->convertToCartesianDirectionalCoordinates(
                                                input_direction.data(),
                                                output_direction.data() );

  FRENSIE_CHECK_EQUAL( input_direction, output_direction );

  input_direction[0] = 1.0/sqrt(2.0);
  input_direction[1] = -1.0/sqrt(2.0);
  input_direction[2] = 0.0;

  policy->convertToCartesianDirectionalCoordinates(
                                                input_direction.data(),
                                                output_direction.data() );

  FRENSIE_CHECK_EQUAL( input_direction, output_direction );
}

//---------------------------------------------------------------------------//
// Check that the input Cartesian coordinates can be converted to the
// directional coordinates
FRENSIE_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   convertFromCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  std::vector<double> input_direction( 3 );
  input_direction[0] = 1.0/sqrt(3.0);
  input_direction[1] = 1.0/sqrt(3.0);
  input_direction[2] = 1.0/sqrt(3.0);

  std::vector<double> output_direction( 3 );

  policy->convertFromCartesianDirectionalCoordinates(
                                                input_direction.data(),
                                                output_direction.data() );

  FRENSIE_CHECK_EQUAL( input_direction, output_direction );

  input_direction[0] = 1.0/sqrt(2.0);
  input_direction[1] = -1.0/sqrt(2.0);
  input_direction[2] = 0.0;

  policy->convertFromCartesianDirectionalCoordinates(
                                                input_direction.data(),
                                                output_direction.data() );

  FRENSIE_CHECK_EQUAL( input_direction, output_direction );
}

//---------------------------------------------------------------------------//
// Check that a policy can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( BasicCartesianCoordinateConversionPolicy,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_basic_cartesian_coordinate_conversion_policy" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Utility::BasicCartesianCoordinateConversionPolicy concrete_policy;

    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      shared_spatial_policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

    std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
      shared_directional_policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_policy ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_spatial_policy ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_directional_policy ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::BasicCartesianCoordinateConversionPolicy concrete_policy;
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    shared_spatial_policy;
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    shared_directional_policy;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_policy ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_spatial_policy ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_directional_policy ) );

  iarchive.reset();

  {
    std::vector<double> input_position( 3 );
    input_position[0] = 1.0;
    input_position[1] = 1.0;
    input_position[2] = 1.0;
    
    std::vector<double> output_position( 3 );
    
    concrete_policy.convertFromCartesianSpatialCoordinates(
                                                       input_position.data(),
                                                       output_position.data());
    
    FRENSIE_CHECK_EQUAL( input_position, output_position );

    std::vector<double> input_direction( 3 );
    input_direction[0] = 1.0/sqrt(3.0);
    input_direction[1] = 1.0/sqrt(3.0);
    input_direction[2] = 1.0/sqrt(3.0);
    
    std::vector<double> output_direction( 3 );
    
    concrete_policy.convertFromCartesianDirectionalCoordinates(
                                                     input_direction.data(),
                                                     output_direction.data() );

    FRENSIE_CHECK_EQUAL( input_direction, output_direction );
  }

  {
    std::vector<double> input_position( 3 );
    input_position[0] = 1.0;
    input_position[1] = 1.0;
    input_position[2] = 1.0;
    
    std::vector<double> output_position( 3 );
    
    shared_spatial_policy->convertFromCartesianSpatialCoordinates(
                                                       input_position.data(),
                                                       output_position.data());
    
    FRENSIE_CHECK_EQUAL( input_position, output_position );
  }

  {
    std::vector<double> input_direction( 3 );
    input_direction[0] = 1.0/sqrt(3.0);
    input_direction[1] = 1.0/sqrt(3.0);
    input_direction[2] = 1.0/sqrt(3.0);
    
    std::vector<double> output_direction( 3 );
    
    shared_directional_policy->convertFromCartesianDirectionalCoordinates(
                                                     input_direction.data(),
                                                     output_direction.data() );

    FRENSIE_CHECK_EQUAL( input_direction, output_direction );
  }
}

//---------------------------------------------------------------------------//
// end tstBasicCartesianCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
