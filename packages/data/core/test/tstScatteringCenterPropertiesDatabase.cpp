//---------------------------------------------------------------------------//
//!
//! \file   tstScatteringCenterPropertiesDatabase.cpp
//! \author Alex Robinson
//! \brief  Scattering center properties cache unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using Utility::Units::amu;

typedef std::tuple<
  std::tuple<boost::archive::xml_oarchive,boost::archive::xml_iarchive>,
  std::tuple<boost::archive::text_oarchive,boost::archive::text_iarchive>,
  std::tuple<boost::archive::binary_oarchive,boost::archive::binary_iarchive>,
  std::tuple<Utility::HDF5OArchive,Utility::HDF5IArchive>,
  std::tuple<boost::archive::polymorphic_oarchive*,boost::archive::polymorphic_iarchive*>
  > TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that atom properties can be initialized
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabase,
                   initializeAtomProperties )
{
  Data::ScatteringCenterPropertiesDatabase database;
  
  FRENSIE_CHECK( !database.doPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doPropertiesExist( 1000 ) );

  FRENSIE_CHECK_NO_THROW( database.initializeAtomProperties( Data::H_ATOM, 1.0 ) );

  FRENSIE_CHECK( database.doPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( database.doPropertiesExist( 1000 ) );
}

//---------------------------------------------------------------------------//
// Check that atom properties can be returned
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabase, getAtomProperties )
{
  Data::ScatteringCenterPropertiesDatabase database;
  
  FRENSIE_CHECK( !database.doPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doPropertiesExist( 1000 ) );

  database.initializeAtomProperties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( database.doPropertiesExist( 1000 ) );
  
  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::H_ATOM );
  
  FRENSIE_CHECK( !atom_properties.isNuclide() );
  FRENSIE_CHECK_EQUAL( atom_properties.zaid(), Data::ZAID(1000) );
  FRENSIE_CHECK_EQUAL( atom_properties.atomicWeight(), 1.0*amu );
}

//---------------------------------------------------------------------------//
// Check that nuclide properties can be initialized
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabase,
                   initializeNuclideProperties )
{
  Data::ScatteringCenterPropertiesDatabase database;
  
  FRENSIE_CHECK( !database.doPropertiesExist( 1001 ) );

  FRENSIE_CHECK_NO_THROW( database.initializeAtomProperties( 1001, 1.0 ) );

  FRENSIE_CHECK( database.doPropertiesExist( 1001 ) );
}

//---------------------------------------------------------------------------//
// Check that nuclide properties can be returned
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabase, getNuclideProperties )
{
  Data::ScatteringCenterPropertiesDatabase database;
  
  FRENSIE_CHECK( !database.doPropertiesExist( 1001 ) );

  database.initializeNuclideProperties( 1001, 1.0 );

  FRENSIE_CHECK( database.doPropertiesExist( 1001 ) );
  
  Data::NuclideProperties& nuclide_properties =
    database.getNuclideProperties( 1001 );
  
  FRENSIE_CHECK( nuclide_properties.isNuclide() );
  FRENSIE_CHECK_EQUAL( nuclide_properties.zaid(), Data::ZAID(1001) );
  FRENSIE_CHECK_EQUAL( nuclide_properties.atomicWeightRatio(), 1.0 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( 1001 );

  FRENSIE_CHECK( atom_properties.isNuclide() );
  FRENSIE_CHECK_EQUAL( atom_properties.zaid(), Data::ZAID(1001) );
  FRENSIE_CHECK_EQUAL( atom_properties.atomicWeightRatio(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that properties can be removed
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabase, removeProperties )
{
  Data::ScatteringCenterPropertiesDatabase database;

  FRENSIE_CHECK( !database.doPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doPropertiesExist( 1000 ) );

  database.initializeAtomProperties( Data::H_ATOM, 1.0 );

  FRENSIE_CHECK( database.doPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( database.doPropertiesExist( 1000 ) );

  database.removeProperties( 1000 );

  FRENSIE_CHECK( !database.doPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doPropertiesExist( 1000 ) );
  
  FRENSIE_CHECK( !database.doPropertiesExist( 1001 ) );

  database.initializeNuclideProperties( 1001, 1.0 );

  FRENSIE_CHECK( database.doPropertiesExist( 1001 ) );

  database.removeProperties( 1001 );

  FRENSIE_CHECK( !database.doPropertiesExist( 1001 ) );
}

//---------------------------------------------------------------------------//
// Check that properties zaids can be listed
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabase, listPropertiesZaids )
{
  Data::ScatteringCenterPropertiesDatabase database;

  database.initializeAtomProperties( Data::H_ATOM, 1.0 );
  database.initializeNuclideProperties( 1001, 1.0 );
  database.initializeAtomProperties( Data::He_ATOM, 4.0 );
  database.initializeNuclideProperties( 2004, 4.0 );

  std::ostringstream oss;

  database.listPropertiesZaids( oss );

  FRENSIE_CHECK( oss.str().find( "1000" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "1001" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2000" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2004" ) < oss.str().size() );
  
  oss.str( "" );
  oss.clear();

  database.listPropertiesZaids( Data::H_ATOM, oss );

  FRENSIE_CHECK( oss.str().find( "1000" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "1001" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2000" ) >= oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2004" ) >= oss.str().size() );

  oss.str( "" );
  oss.clear();

  database.listPropertiesZaids( Data::He_ATOM, oss );

  FRENSIE_CHECK( oss.str().find( "1000" ) >= oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "1001" ) >= oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2000" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2004" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the database can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ScatteringCenterPropertiesDatabase,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_scattering_center_database" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Data::ScatteringCenterPropertiesDatabase database;

    database.initializeAtomProperties( Data::H_ATOM, 1.0 );
    database.initializeNuclideProperties( 1001, 1.0 );
    database.initializeAtomProperties( Data::He_ATOM, 4.0 );
    database.initializeNuclideProperties( 2004, 4.0 );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( database ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Data::ScatteringCenterPropertiesDatabase database;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( database ) );

  FRENSIE_REQUIRE( database.doPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK_EQUAL( database.getAtomProperties( 1000 ).atomicWeightRatio(), 1.0 );

  FRENSIE_REQUIRE( database.doPropertiesExist( 1001 ) );
  FRENSIE_CHECK_EQUAL( database.getNuclideProperties( 1001 ).atomicWeightRatio(), 1.0 );

  FRENSIE_REQUIRE( database.doPropertiesExist( Data::He_ATOM ) );
  FRENSIE_CHECK_EQUAL( database.getAtomProperties( 2000 ).atomicWeightRatio(), 4.0 );

  FRENSIE_REQUIRE( database.doPropertiesExist( 2004 ) );
  FRENSIE_CHECK_EQUAL( database.getNuclideProperties( 2004 ).atomicWeightRatio(), 4.0 );
}

//---------------------------------------------------------------------------//
// Check that the database can be constructed from an archive
FRENSIE_DATA_UNIT_TEST_DECL( ScatteringCenterPropertiesDatabase,
                             archive_constructor )
{
  FETCH_FROM_TABLE( std::string, name );
  
  {
    Data::ScatteringCenterPropertiesDatabase database;

    database.initializeAtomProperties( Data::H_ATOM, 1.0 );
    database.initializeNuclideProperties( 1001, 1.0 );
    database.initializeAtomProperties( Data::He_ATOM, 4.0 );
    database.initializeNuclideProperties( 2004, 4.0 );
    
    database.saveToFile( name, true );
  }

  Data::ScatteringCenterPropertiesDatabase database( name );

  FRENSIE_REQUIRE( database.doPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK_EQUAL( database.getAtomProperties( 1000 ).atomicWeightRatio(), 1.0 );

  FRENSIE_REQUIRE( database.doPropertiesExist( 1001 ) );
  FRENSIE_CHECK_EQUAL( database.getNuclideProperties( 1001 ).atomicWeightRatio(), 1.0 );

  FRENSIE_REQUIRE( database.doPropertiesExist( Data::He_ATOM ) );
  FRENSIE_CHECK_EQUAL( database.getAtomProperties( 2000 ).atomicWeightRatio(), 4.0 );

  FRENSIE_REQUIRE( database.doPropertiesExist( 2004 ) );
  FRENSIE_CHECK_EQUAL( database.getNuclideProperties( 2004 ).atomicWeightRatio(), 4.0 );
}

FRENSIE_DATA_UNIT_TEST_INST( ScatteringCenterPropertiesDatabase,
                             archive_constructor )
{
  COLUMNS()         << "name";
  NEW_ROW( "xml" )  << "test_scattering_center_database.xml";
  NEW_ROW( "txt" )  << "test_scattering_center_database.txt";
  NEW_ROW( "bin" )  << "test_scattering_center_database.bin";
  NEW_ROW( "h5fa" ) << "test_scattering_center_database.bin";
}

//---------------------------------------------------------------------------//
// end tstScatteringCenterPropertiesDatabase.hpp
//---------------------------------------------------------------------------//
