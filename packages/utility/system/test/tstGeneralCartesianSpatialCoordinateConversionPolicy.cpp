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

// FRENSIE Includes
#include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
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
FRENSIE_UNIT_TEST( GeneralCartesianSpatialCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
   new Utility::GeneralCartesianSpatialCoordinateConversionPolicy(
                               std::vector<double>({2.0, -1.0, 0.1}).data(),
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

  // Local z-axis
  std::array<double,3> local_position = {0.0, 0.0, 2.0};

  std::array<double,3> global_position;
  std::array<double,3> ref_global_position =
    {2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1};
  
  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-14 );

  // Local neg. z-axis
  local_position = {0.0, 0.0, -2.0};
  ref_global_position =
    {-2.0/sqrt(3.0)+2.0, -2.0/sqrt(3.0)-1.0, -2.0/sqrt(3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-14 );

  // Local y-axis
  local_position = {0.0, 2.0, 0.0};
  ref_global_position = {-sqrt(2.0)+2.0, sqrt(2.0)-1.0, 0.1};

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-14 );

  // Local neg. y-axis
  local_position = {0.0, -2.0, 0.0};
  ref_global_position = {sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1};

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-14 );

  // Local x-axis
  local_position = {2.0, 0.0, 0.0};
  ref_global_position =
    {2.0/sqrt(6.0)+2.0, 2.0/sqrt(6.0)-1.0, -sqrt(8.0/3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-14 );

  // Local neg. x-axis
  local_position = {-2.0, 0.0, 0.0};
  ref_global_position =
    {-2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1};

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( global_position, ref_global_position, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local Cartesian spatial coordinates
FRENSIE_UNIT_TEST( GeneralCartesianSpatialCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
   new Utility::GeneralCartesianSpatialCoordinateConversionPolicy(
                               std::vector<double>({2.0, -1.0, 0.1}).data(),
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

  // To local x-axis
  std::array<double,3> global_position =
    {2.0/sqrt(6.0)+2.0, 2.0/sqrt(6.0)-1.0, -sqrt(8.0/3.0)+0.1};

  std::array<double,3> local_position;
  std::array<double,3> ref_local_position = {2.0, 0.0, 0.0};
  
  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

  // To local neg. x-axis
  global_position =
    {-2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1};
  ref_local_position = {-2.0, 0.0, 0.0};

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

  // To local y-axis
  global_position = {-sqrt(2.0)+2.0, sqrt(2.0)-1.0, 0.1};
  ref_local_position = {0.0, 2.0, 0.0};

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

  // To local neg. y-axis
  global_position = {sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1};
  ref_local_position = {0.0, -2.0, 0.0};

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

  // To local z-axis
  global_position = {2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1};
  ref_local_position = {0.0, 0.0, 2.0};

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

  // To local neg. z-axis
  global_position =
    {-2.0/sqrt(3.0)+2.0, -2.0/sqrt(3.0)-1.0, -2.0/sqrt(3.0)+0.1};
  ref_local_position = {0.0, 0.0, -2.0};

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );
  Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that a policy can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( GeneralCartesianSpatialCoordinateConversionPolicy,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_general_cartesian_spatial_coordinate_conversion_policy" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Utility::GeneralCartesianSpatialCoordinateConversionPolicy concrete_policy(
                               std::vector<double>({2.0, -1.0, 0.1}).data(),
                               std::vector<double>({1.0, 1.0, 1.0}).data() );

    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      shared_policy(
            new Utility::GeneralCartesianSpatialCoordinateConversionPolicy(
                               std::vector<double>({2.0, -1.0, 0.1}).data(),
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_policy ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_policy ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::GeneralCartesianSpatialCoordinateConversionPolicy concrete_policy(
                               std::vector<double>({0.0, 0.0, 0.0}).data(),
                               std::vector<double>({0.0, 0.0, 1.0}).data() );

  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    shared_policy;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_policy ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_policy ) );

  iarchive.reset();

  {
    // To local x-axis
    std::array<double,3> global_position =
      {2.0/sqrt(6.0)+2.0, 2.0/sqrt(6.0)-1.0, -sqrt(8.0/3.0)+0.1};
    
    std::array<double,3> local_position;
    std::array<double,3> ref_local_position = {2.0, 0.0, 0.0};
    
    concrete_policy.convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
    Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

    // To local neg. x-axis
    global_position =
      {-2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1};
    ref_local_position = {-2.0, 0.0, 0.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
    Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

    // To local y-axis
    global_position = {-sqrt(2.0)+2.0, sqrt(2.0)-1.0, 0.1};
    ref_local_position = {0.0, 2.0, 0.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

    // To local neg. y-axis
    global_position = {sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1};
    ref_local_position = {0.0, -2.0, 0.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

    // To local z-axis
    global_position = {2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1};
    ref_local_position = {0.0, 0.0, 2.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
    Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

    // To local neg. z-axis
    global_position =
      {-2.0/sqrt(3.0)+2.0, -2.0/sqrt(3.0)-1.0, -2.0/sqrt(3.0)+0.1};
    ref_local_position = {0.0, 0.0, -2.0};

    concrete_policy.convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
    Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );
  }

  {
    // To local x-axis
    std::array<double,3> global_position =
      {2.0/sqrt(6.0)+2.0, 2.0/sqrt(6.0)-1.0, -sqrt(8.0/3.0)+0.1};
    
    std::array<double,3> local_position;
    std::array<double,3> ref_local_position = {2.0, 0.0, 0.0};
    
    shared_policy->convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
    Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

    // To local neg. x-axis
    global_position =
      {-2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1};
    ref_local_position = {-2.0, 0.0, 0.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
    Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

    // To local y-axis
    global_position = {-sqrt(2.0)+2.0, sqrt(2.0)-1.0, 0.1};
    ref_local_position = {0.0, 2.0, 0.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

    // To local neg. y-axis
    global_position = {sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1};
    ref_local_position = {0.0, -2.0, 0.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

    // To local z-axis
    global_position = {2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1};
    ref_local_position = {0.0, 0.0, 2.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
    Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );

    // To local neg. z-axis
    global_position =
      {-2.0/sqrt(3.0)+2.0, -2.0/sqrt(3.0)-1.0, -2.0/sqrt(3.0)+0.1};
    ref_local_position = {0.0, 0.0, -2.0};

    shared_policy->convertFromCartesianSpatialCoordinates(
                                                       global_position.data(),
                                                       local_position.data() );
    Utility::clearVectorOfRoundingErrors( local_position.data(), 1e-15 );
  
    FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-14 );
  }
}
    

//---------------------------------------------------------------------------//
// end tstGeneralCartesianSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
