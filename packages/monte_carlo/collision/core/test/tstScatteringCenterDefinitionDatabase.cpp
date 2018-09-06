//---------------------------------------------------------------------------//
//!
//! \file   tstScatteringCenterDefinitionDatabase.cpp
//! \author Alex Robinson
//! \brief  Scattering center definition database unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "Data_NativeEPRPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRElectroatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointElectroatomicDataProperties.hpp"
#include "Data_ACENuclearDataProperties.hpp"
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Data_ACEPhotonuclearDataProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types.
//---------------------------------------------------------------------------//

using Utility::Units::MeV;
using Utility::Units::amu;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a scattering center definition can be created
FRENSIE_UNIT_TEST( ScatteringCenterDefinitionDatabase,
                   createDefinition )
{
  MonteCarlo::ScatteringCenterDefinitionDatabase database;

  database.createDefinition( 1000 );

  FRENSIE_CHECK( database.doesDefinitionExist( "H" ) );

  database.createDefinition( "H1 @ 293.1K", 1001 );

  FRENSIE_CHECK( database.doesDefinitionExist( "H1 @ 293.1K" ) );

  FRENSIE_CHECK_THROW( database.createDefinition( "H" ),
                       std::runtime_error );
  FRENSIE_CHECK_THROW( database.createDefinition( "H1 @ 293.1K" ),
                       std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that a scattering center definition alias can be created
FRENSIE_UNIT_TEST( ScatteringCenterDefinitionDatabase,
                   createDefinitionAlias )
{
  MonteCarlo::ScatteringCenterDefinitionDatabase database;

  FRENSIE_CHECK_THROW( database.createDefinitionAlias( "H1 @ 293.1K", "H1" ),
                       std::runtime_error );
  
  database.createDefinition( "H1 @ 293.1K", 1001 );
  database.createDefinitionAlias( "H1 @ 293.1K", "H1" );

  FRENSIE_CHECK( !database.isDefinitionNameAnAlias( "dummy" ) );
  FRENSIE_CHECK( !database.isDefinitionNameAnAlias( "H1 @ 293.1K" ) );
  FRENSIE_CHECK( database.isDefinitionNameAnAlias( "H1" ) );
}

//---------------------------------------------------------------------------//
// Check that a scattering center definition alias can be resolved
FRENSIE_UNIT_TEST( ScatteringCenterDefinitionDatabase,
                   resolveDefinitionAlias )
{
  MonteCarlo::ScatteringCenterDefinitionDatabase database;
  
  FRENSIE_CHECK_THROW( database.resolveDefinitionAlias( "H1" ),
                       std::runtime_error );

  database.createDefinition( "H1 @ 293.1K", 1001 );
  database.createDefinitionAlias( "H1 @ 293.1K", "H1" );

  FRENSIE_CHECK_EQUAL( database.resolveDefinitionAlias( "H1" ),
                       "H1 @ 293.1K" );
}

//---------------------------------------------------------------------------//
// Check that a scattering center definition can be returned
FRENSIE_UNIT_TEST( ScatteringCenterDefinitionDatabase, getDefinition )
{
  MonteCarlo::ScatteringCenterDefinitionDatabase database;

  FRENSIE_CHECK_THROW( database.getDefinition( "H1 @ 293.1K" ),
                       std::runtime_error );

  MonteCarlo::ScatteringCenterDefinition& definition =
    database.createDefinition( "H1 @ 293.1K", 1001 );

  FRENSIE_CHECK( &definition == &database.getDefinition( "H1 @ 293.1K" ) );

  database.createDefinitionAlias( "H1 @ 293.1K", "H1" );

  // Access the definition through an alias
  FRENSIE_CHECK( &definition == &database.getDefinition( "H1" ) );
}

//---------------------------------------------------------------------------//
// Check that a scattering center definition can be removed
FRENSIE_UNIT_TEST( ScatteringCenterDefinitionDatabase, removeDefinition )
{
  MonteCarlo::ScatteringCenterDefinitionDatabase database;

  FRENSIE_CHECK_NO_THROW( database.removeDefinition( "H1 @ 293.1K" ) );

  database.createDefinition( "H1 @ 293.1K", 1001 );
  database.createDefinitionAlias( "H1 @ 293.1K", "H1" );

  FRENSIE_CHECK( database.doesDefinitionExist( "H1 @ 293.1K" ) );
  FRENSIE_CHECK( database.doesDefinitionExist( "H1" ) );

  database.removeDefinition( "H1" );

  FRENSIE_CHECK( database.doesDefinitionExist( "H1 @ 293.1K" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( "H1" ) );

  database.removeDefinition( "H1 @ 293.1K" );

  FRENSIE_CHECK( !database.doesDefinitionExist( "H1 @ 293.1K" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( "H1" ) );
}

//---------------------------------------------------------------------------//
// Check that a database can be placed in a stream
FRENSIE_UNIT_TEST( ScatteringCenterDefinitionDatabase, toStream )
{
  MonteCarlo::ScatteringCenterDefinitionDatabase database;

  database.createDefinition( 1000 );
  database.createDefinition( "H1 @ 293.1K", 1001 );
  database.createDefinitionAlias( "H1 @ 293.1K", "H1" );

  FRENSIE_CHECK_NO_THROW( std::cout << "\n" << database << std::endl );
}

//---------------------------------------------------------------------------//
// Check that a database can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ScatteringCenterDefinitionDatabase,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_scattering_center_definition_database" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::ScatteringCenterDefinitionDatabase database;

    database.createDefinition( 1000 );
    database.createDefinition( "H1 @ 293.1K", 1001 );
    
    MonteCarlo::ScatteringCenterDefinition& h_definition =
      database.getDefinition( "H" );

    MonteCarlo::ScatteringCenterDefinition& h1_definition =
      database.getDefinition( "H1 @ 293.1K" );

    {
      std::shared_ptr<const Data::PhotoatomicDataProperties> properties(
               new Data::NativeEPRPhotoatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

      h_definition.setDataProperties( properties );
      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> properties(
               new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

      h_definition.setDataProperties( properties );
      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::ElectroatomicDataProperties> properties(
               new Data::NativeEPRElectroatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

      h_definition.setDataProperties( properties );
      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::AdjointElectroatomicDataProperties> properties(
               new Data::NativeEPRAdjointElectroatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

      h_definition.setDataProperties( properties );
      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::NuclearDataProperties> properties(
               new Data::ACENuclearDataProperties(
                                             1.0,
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.71c" ) );

      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::ThermalNuclearDataProperties> properties(
               new Data::ACEThermalNuclearDataProperties(
                                             {1001, 1002, 8016},
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "ltwtr.71t" ) );

      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::PhotonuclearDataProperties> properties(
               new Data::ACEPhotonuclearDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.10u" ) );

      h1_definition.setDataProperties( properties );
    }
    
    database.createDefinitionAlias( "H1 @ 293.1K", "H1" );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( database ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::ScatteringCenterDefinitionDatabase database;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( database ) );

  iarchive.reset();

  FRENSIE_REQUIRE( database.doesDefinitionExist( "H" ) );

  MonteCarlo::ScatteringCenterDefinition& h_definition =
    database.getDefinition( "H" );

  FRENSIE_CHECK_EQUAL( h_definition.getName(), "H" );
  FRENSIE_CHECK_EQUAL( h_definition.getZAID(), Data::ZAID(1000) );
  FRENSIE_CHECK( h_definition.hasPhotoatomicDataProperties() );
  FRENSIE_CHECK( h_definition.hasAdjointPhotoatomicDataProperties() );
  FRENSIE_CHECK( h_definition.hasElectroatomicDataProperties() );
  FRENSIE_CHECK( h_definition.hasAdjointElectroatomicDataProperties() );
  FRENSIE_CHECK( !h_definition.hasNuclearDataProperties() );
  FRENSIE_CHECK( !h_definition.hasAdjointNuclearDataProperties() );
  FRENSIE_CHECK( !h_definition.hasThermalNuclearDataProperties() );
  FRENSIE_CHECK( !h_definition.hasAdjointThermalNuclearDataProperties() );
  FRENSIE_CHECK( !h_definition.hasPhotonuclearDataProperties() );
  FRENSIE_CHECK( !h_definition.hasAdjointPhotonuclearDataProperties() );
  
  FRENSIE_REQUIRE( database.doesDefinitionExist( "H1 @ 293.1K" ) );
  
  MonteCarlo::ScatteringCenterDefinition& h1_definition =
    database.getDefinition( "H1" );

  FRENSIE_CHECK_EQUAL( h1_definition.getName(), "H1 @ 293.1K" );
  FRENSIE_CHECK_EQUAL( h1_definition.getZAID(), Data::ZAID(1001) );
  FRENSIE_CHECK( h1_definition.hasPhotoatomicDataProperties() );
  FRENSIE_CHECK( h1_definition.hasAdjointPhotoatomicDataProperties() );
  FRENSIE_CHECK( h1_definition.hasElectroatomicDataProperties() );
  FRENSIE_CHECK( h1_definition.hasAdjointElectroatomicDataProperties() );
  FRENSIE_CHECK( h1_definition.hasNuclearDataProperties() );
  FRENSIE_CHECK( !h1_definition.hasAdjointNuclearDataProperties() );
  FRENSIE_CHECK( h1_definition.hasThermalNuclearDataProperties() );
  FRENSIE_CHECK( !h1_definition.hasAdjointThermalNuclearDataProperties() );
  FRENSIE_CHECK( h1_definition.hasPhotonuclearDataProperties() );
  FRENSIE_CHECK( !h1_definition.hasAdjointPhotonuclearDataProperties() );
  
  FRENSIE_REQUIRE( database.doesDefinitionExist( "H1" ) );
  FRENSIE_REQUIRE( database.isDefinitionNameAnAlias( "H1" ) );
  FRENSIE_CHECK_EQUAL( database.resolveDefinitionAlias( "H1" ),
                       "H1 @ 293.1K" );
}

//---------------------------------------------------------------------------//
// end tstScatteringCenterDefinitionDatabase.cpp
//---------------------------------------------------------------------------//
