//---------------------------------------------------------------------------//
//!
//! \file   tstScatteringCenterPropertiesDatabaseImpl.cpp
//! \author Alex Robinson
//! \brief  Scattering center properties database impl unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesDatabaseImpl.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "TestNuclearDataProperties.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using Utility::Units::amu;
using Utility::Units::MeV;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that atom properties can be initialized
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabaseImpl,
                   initializeAtomProperties )
{
  Data::ScatteringCenterPropertiesDatabaseImpl database;
  
  FRENSIE_CHECK( !database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1000 ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1001 ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1002 ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1003 ) );

  FRENSIE_CHECK_NO_THROW( database.initializeAtomProperties( Data::H_ATOM, 1.0 ) );

  FRENSIE_CHECK( database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1000 ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1001 ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1002 ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1003 ) );

  // Check the other initialization signatures
  { 
    Data::AtomProperties& atom_properties =
      database.initializeAtomProperties( Data::He_ATOM, 4.0 );

    FRENSIE_CHECK_EQUAL( atom_properties.atom(), Data::He_ATOM );
    FRENSIE_CHECK_EQUAL( atom_properties.atomicWeightRatio(), 4.0 );
  }

  {
    Data::AtomProperties& atom_properties =
      database.initializeAtomProperties( Data::Li_ATOM, 6.0*amu );

    FRENSIE_CHECK_EQUAL( atom_properties.atom(), Data::Li_ATOM );
    FRENSIE_CHECK_EQUAL( atom_properties.atomicWeight(), 6.0*amu );
  }

  {
    Data::AtomProperties& atom_properties =
      database.initializeAtomProperties( 5010, 10.0 );

    FRENSIE_CHECK_EQUAL( atom_properties.atom(), Data::B_ATOM );
    FRENSIE_CHECK_EQUAL( atom_properties.atomicWeightRatio(), 10.0 );
  }

  {
    Data::AtomProperties& atom_properties =
      database.initializeAtomProperties( 6012, 12.0*amu );

    FRENSIE_CHECK_EQUAL( atom_properties.atom(), Data::C_ATOM );
    FRENSIE_CHECK_EQUAL( atom_properties.atomicWeight(), 12.0*amu );
  }
}

//---------------------------------------------------------------------------//
// Check that atom properties can be returned
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabaseImpl, getAtomProperties )
{
  Data::ScatteringCenterPropertiesDatabaseImpl database;
  
  FRENSIE_CHECK( !database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1000 ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1001 ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1002 ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1003 ) );

  database.initializeAtomProperties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1000 ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1001 ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1002 ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1003 ) );
  
  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::H_ATOM );
  
  FRENSIE_CHECK_EQUAL( atom_properties.atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( atom_properties.atomicWeight(), 1.0*amu );
  FRENSIE_CHECK( &atom_properties == &database.getAtomProperties( 1000 ) );
  FRENSIE_CHECK( &atom_properties == &database.getAtomProperties( 1001 ) );
  FRENSIE_CHECK( &atom_properties == &database.getAtomProperties( 1002 ) );
  FRENSIE_CHECK( &atom_properties == &database.getAtomProperties( 1003 ) );

  // Initializing again will simply return the available atom properties
  FRENSIE_CHECK( &atom_properties ==
                 &database.initializeAtomProperties( 1000, 1.0*amu ) );
}

//---------------------------------------------------------------------------//
// Check that nuclide properties can be initialized
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabaseImpl,
                   initializeNuclideProperties )
{
  Data::ScatteringCenterPropertiesDatabaseImpl database;
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1001 ) );

  FRENSIE_CHECK_NO_THROW( database.initializeNuclideProperties( 1001, 1.0 ) );

  FRENSIE_CHECK( database.doNuclidePropertiesExist( 1001 ) );

  // Check the other initialization signatures
  {
    Data::NuclideProperties& nuclide_properties =
      database.initializeNuclideProperties( 1002, 2.0 );

    FRENSIE_CHECK_EQUAL( nuclide_properties.zaid(), Data::ZAID( 1002 ) );
    FRENSIE_CHECK_EQUAL( nuclide_properties.atomicWeightRatio(), 2.0 );
  }

  {
    Data::NuclideProperties& nuclide_properties =
      database.initializeNuclideProperties( 1003, 3.0*amu );

    FRENSIE_CHECK_EQUAL( nuclide_properties.zaid(), Data::ZAID( 1003 ) );
    FRENSIE_CHECK_EQUAL( nuclide_properties.atomicWeight(), 3.0*amu );
  }
}

//---------------------------------------------------------------------------//
// Check that nuclide properties can be returned
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabaseImpl, getNuclideProperties )
{
  Data::ScatteringCenterPropertiesDatabaseImpl database;
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1001 ) );

  database.initializeNuclideProperties( 1001, 1.0 );

  FRENSIE_CHECK( database.doNuclidePropertiesExist( 1001 ) );
  
  Data::NuclideProperties& nuclide_properties =
    database.getNuclideProperties( 1001 );
  
  FRENSIE_CHECK_EQUAL( nuclide_properties.zaid(), Data::ZAID(1001) );
  FRENSIE_CHECK_EQUAL( nuclide_properties.atomicWeightRatio(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that atom properties can be removed
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabaseImpl,
                   removeAtomProperties )
{
  Data::ScatteringCenterPropertiesDatabaseImpl database;

  FRENSIE_CHECK( !database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1000 ) );

  database.initializeAtomProperties( Data::H_ATOM, 1.0 );

  FRENSIE_CHECK( database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1000 ) );

  database.removeAtomProperties( Data::H_ATOM );

  FRENSIE_CHECK( !database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1000 ) );

  database.initializeAtomProperties( 1000, 1.0 );

  FRENSIE_CHECK( database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1000 ) );

  database.removeAtomProperties( 1000 );

  FRENSIE_CHECK( !database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1000 ) );
}

//---------------------------------------------------------------------------//
// Check that nuclide properties can be removed
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabaseImpl,
                   removeNuclideProperties )
{
  Data::ScatteringCenterPropertiesDatabaseImpl database;
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1001 ) );

  database.initializeNuclideProperties( 1001, 1.0 );

  FRENSIE_CHECK( database.doNuclidePropertiesExist( 1001 ) );

  database.removeNuclideProperties( 1001 );

  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1001 ) );
}

//---------------------------------------------------------------------------//
// Check that empty properties can be removed
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabaseImpl,
                   removeEmptyProperties )
{
  Data::ScatteringCenterPropertiesDatabaseImpl database;

  FRENSIE_CHECK( !database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1000 ) );

  database.initializeAtomProperties( Data::H_ATOM, 1.0 );

  FRENSIE_CHECK( database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1000 ) );
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1001 ) );

  database.initializeNuclideProperties( 1001, 1.0 );

  FRENSIE_CHECK( database.doNuclidePropertiesExist( 1001 ) );

  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1002 ) );

  {
    Data::NuclideProperties& h2_properties =
      database.initializeNuclideProperties( 1002, 2.0 );

    std::shared_ptr<const Data::NuclearDataProperties> test_data(
              new Data::TestNuclearDataProperties<Data::NuclearDataProperties>(
                                     1002,
                                     2.0,
                                     0.0*MeV,
                                     Data::NuclearDataProperties::ACE_FILE,
                                     0 ) );

    h2_properties.setNuclearDataProperties( test_data );
  }

  database.removeEmptyProperties();

  FRENSIE_CHECK( database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( database.doAtomPropertiesExist( 1000 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1001 ) );
  FRENSIE_CHECK( database.doNuclidePropertiesExist( 1002 ) );

  database.removeEmptyProperties( true );

  FRENSIE_CHECK( !database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 1000 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1001 ) );
  FRENSIE_CHECK( database.doNuclidePropertiesExist( 1002 ) );
}

//---------------------------------------------------------------------------//
// Check that the atoms can be listed
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabaseImpl, listAtoms )
{
  Data::ScatteringCenterPropertiesDatabaseImpl database;

  database.initializeAtomProperties( Data::H_ATOM, 1.0 );
  database.initializeAtomProperties( Data::He_ATOM, 4.0 );

  std::ostringstream oss;

  database.listAtoms( oss );

  FRENSIE_CHECK( oss.str().find( "H" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "He" ) < oss.str().size() );
  
  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// Check that zaids can be listed
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesDatabaseImpl, listZaids )
{
  Data::ScatteringCenterPropertiesDatabaseImpl database;

  database.initializeNuclideProperties( 1000, 1.0 );
  database.initializeNuclideProperties( 1001, 1.0 );
  database.initializeNuclideProperties( 2000, 4.0 );
  database.initializeNuclideProperties( 2004, 4.0 );

  std::ostringstream oss;

  database.listZaids( oss );

  FRENSIE_CHECK( oss.str().find( "1000" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "1001" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2000" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2004" ) < oss.str().size() );
  
  oss.str( "" );
  oss.clear();

  database.listZaids( Data::H_ATOM, oss );

  FRENSIE_CHECK( oss.str().find( "1000" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "1001" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2000" ) >= oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2004" ) >= oss.str().size() );

  oss.str( "" );
  oss.clear();

  database.listZaids( Data::He_ATOM, oss );

  FRENSIE_CHECK( oss.str().find( "1000" ) >= oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "1001" ) >= oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2000" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "2004" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the database can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ScatteringCenterPropertiesDatabaseImpl,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_scattering_center_database_impl" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Data::ScatteringCenterPropertiesDatabaseImpl database;

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

  Data::ScatteringCenterPropertiesDatabaseImpl database;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( database ) );

  FRENSIE_REQUIRE( database.doAtomPropertiesExist( Data::H_ATOM ) );
  FRENSIE_CHECK_EQUAL( database.getAtomProperties( 1000 ).atomicWeightRatio(), 1.0 );

  FRENSIE_REQUIRE( database.doNuclidePropertiesExist( 1001 ) );
  FRENSIE_CHECK_EQUAL( database.getNuclideProperties( 1001 ).atomicWeightRatio(), 1.0 );

  FRENSIE_REQUIRE( database.doAtomPropertiesExist( Data::He_ATOM ) );
  FRENSIE_CHECK_EQUAL( database.getAtomProperties( 2000 ).atomicWeightRatio(), 4.0 );

  FRENSIE_REQUIRE( database.doNuclidePropertiesExist( 2004 ) );
  FRENSIE_CHECK_EQUAL( database.getNuclideProperties( 2004 ).atomicWeightRatio(), 4.0 );
}

//---------------------------------------------------------------------------//
// end tstScatteringCenterPropertiesDatabaseImpl.hpp
//---------------------------------------------------------------------------//
