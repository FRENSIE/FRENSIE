//---------------------------------------------------------------------------//
//!
//! \file   tstPhaseSpaceDimension.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types.
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if the spatial dimension enum can be converted to a phase space
// dimension enum
FRENSIE_UNIT_TEST( PhaseSpaceDimension,
                   convertSpatialDimensionToPhaseSpaceDimension )
{
  MonteCarlo::PhaseSpaceDimension dimension =
    MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::X_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::PRIMARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::Y_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::SECONDARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::Z_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::TERTIARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::R_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::PRIMARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::SECONDARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::TERTIARY_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check if a directional dimension enum can be converted to a phase space
// dimension enum
FRENSIE_UNIT_TEST( PhaseSpaceDimension,
                   convertDirectionalDimensionToPhaseSpaceDimension )
{
  MonteCarlo::PhaseSpaceDimension dimension =
    MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::U_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::V_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::W_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::R_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check if the dimension enum can be converted to a name
FRENSIE_UNIT_TEST( PhaseSpaceDimension, toString )
{
  std::string dimension_name =
    Utility::toString( MonteCarlo::PRIMARY_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Primary Spatial Dimension" );

  dimension_name = Utility::toString( MonteCarlo::SECONDARY_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Secondary Spatial Dimension" );

  dimension_name = Utility::toString( MonteCarlo::TERTIARY_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Tertiary Spatial Dimension" );

  dimension_name = Utility::toString( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Primary Directional Dimension" );

  dimension_name = Utility::toString( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Secondary Directional Dimension" );

  dimension_name = Utility::toString( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Tertiary Directional Dimension" );

  dimension_name = Utility::toString( MonteCarlo::ENERGY_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Energy Dimension" );

  dimension_name = Utility::toString( MonteCarlo::TIME_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Time Dimension" );
  
  dimension_name = Utility::toString( MonteCarlo::WEIGHT_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Weight Dimension" );

  dimension_name = Utility::toString( MonteCarlo::SOURCE_ENERGY_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Source Energy Dimension" );

  dimension_name = Utility::toString( MonteCarlo::SOURCE_TIME_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Source Time Dimension" );
  
  dimension_name = Utility::toString( MonteCarlo::SOURCE_WEIGHT_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Source Weight Dimension" );
}

//---------------------------------------------------------------------------//
// Check if a dimension enum can be placed in a stream
FRENSIE_UNIT_TEST( PhaseSpaceDimension, stream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::PRIMARY_SPATIAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Primary Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SECONDARY_SPATIAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Secondary Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TERTIARY_SPATIAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Tertiary Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Primary Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Secondary Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Tertiary Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ENERGY_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Energy Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TIME_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Time Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::WEIGHT_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Weight Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SOURCE_ENERGY_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Source Energy Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SOURCE_TIME_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Source Time Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SOURCE_WEIGHT_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Source Weight Dimension" );
}

//---------------------------------------------------------------------------//
// Check that an enum can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhaseSpaceDimension,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_phase_space_dimension_enum" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::PhaseSpaceDimension dimension_1 =
      MonteCarlo::PRIMARY_SPATIAL_DIMENSION;

    MonteCarlo::PhaseSpaceDimension dimension_2 =
      MonteCarlo::SECONDARY_SPATIAL_DIMENSION;

    MonteCarlo::PhaseSpaceDimension dimension_3 =
      MonteCarlo::TERTIARY_SPATIAL_DIMENSION;

    MonteCarlo::PhaseSpaceDimension dimension_4 =
      MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION;

    MonteCarlo::PhaseSpaceDimension dimension_5 =
      MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION;

    MonteCarlo::PhaseSpaceDimension dimension_6 =
      MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION;

    MonteCarlo::PhaseSpaceDimension dimension_7 =
      MonteCarlo::ENERGY_DIMENSION;
    
    MonteCarlo::PhaseSpaceDimension dimension_8 =
      MonteCarlo::TIME_DIMENSION;

    MonteCarlo::PhaseSpaceDimension dimension_9 =
      MonteCarlo::WEIGHT_DIMENSION;

    MonteCarlo::PhaseSpaceDimension dimension_10 =
      MonteCarlo::SOURCE_ENERGY_DIMENSION;
    
    MonteCarlo::PhaseSpaceDimension dimension_11 =
      MonteCarlo::SOURCE_TIME_DIMENSION;

    MonteCarlo::PhaseSpaceDimension dimension_12 =
      MonteCarlo::SOURCE_WEIGHT_DIMENSION;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_1) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_2) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_3) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_4) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_5) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_6) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_7) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_8) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_9) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_10) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_11) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dimension_12) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::PhaseSpaceDimension dimension_1, dimension_2, dimension_3,
    dimension_4, dimension_5, dimension_6, dimension_7, dimension_8,
    dimension_9, dimension_10, dimension_11, dimension_12;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_1) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_2) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_3) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_4) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_5) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_6) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_7) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_8) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_9) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_10) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_11) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dimension_12) );

  iarchive.reset();

  FRENSIE_CHECK_EQUAL( dimension_1, MonteCarlo::PRIMARY_SPATIAL_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_2, MonteCarlo::SECONDARY_SPATIAL_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_3, MonteCarlo::TERTIARY_SPATIAL_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_4, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_5, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_6, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_7, MonteCarlo::ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_8, MonteCarlo::TIME_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_9, MonteCarlo::WEIGHT_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_10, MonteCarlo::SOURCE_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_11, MonteCarlo::SOURCE_TIME_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_12, MonteCarlo::SOURCE_WEIGHT_DIMENSION );
}

//---------------------------------------------------------------------------//
// end tstPhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
