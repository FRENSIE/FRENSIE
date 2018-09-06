//---------------------------------------------------------------------------//
//!
//! \file   tstScatteringCenterPropertiesDatabase.cpp
//! \author Alex Robinson
//! \brief  Scattering center properties database unit tests
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "FRENSIE_config.hpp"

//---------------------------------------------------------------------------//
// Tests.
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

  FRENSIE_REQUIRE( database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK_EQUAL( database.getAtomProperties( 1000 ).atomicWeightRatio(), 1.0 );

  FRENSIE_REQUIRE( database.doNuclidePropertiesExist( 1001 ) );
  FRENSIE_CHECK_EQUAL( database.getNuclideProperties( 1001 ).atomicWeightRatio(), 1.0 );

  FRENSIE_REQUIRE( database.doAtomPropertiesExist( Data::He_ATOM ) );
  FRENSIE_CHECK_EQUAL( database.getAtomProperties( 2000 ).atomicWeightRatio(), 4.0 );

  FRENSIE_REQUIRE( database.doNuclidePropertiesExist( 2004 ) );
  FRENSIE_CHECK_EQUAL( database.getNuclideProperties( 2004 ).atomicWeightRatio(), 4.0 );
}

FRENSIE_DATA_UNIT_TEST_INST( ScatteringCenterPropertiesDatabase,
                             archive_constructor )
{
  COLUMNS()         << "name";
  NEW_ROW( "xml" )  << "test_scattering_center_database.xml";
  NEW_ROW( "txt" )  << "test_scattering_center_database.txt";
  NEW_ROW( "bin" )  << "test_scattering_center_database.bin";
#ifdef HAVE_FRENSIE_HDF5
  NEW_ROW( "h5fa" ) << "test_scattering_center_database.h5fa";
#endif
}

//---------------------------------------------------------------------------//
// end tstScatteringCenterPropertiesDatabase.cpp
//---------------------------------------------------------------------------//
