//---------------------------------------------------------------------------//
//!
//! \file   tstMaterialDefinitionDatabase.cpp
//! \author Alex Robinson
//! \brief  Material definition database unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types.
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a material definition can be created
FRENSIE_UNIT_TEST( MaterialDefinitionDatabase, addDefinition )
{
  MonteCarlo::MaterialDefinitionDatabase database;

  FRENSIE_CHECK( !database.doesDefinitionExist( "1" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( 1 ) );
  
  database.addDefinition( 1, {"H", "O"}, {2.0, 1.0} );

  FRENSIE_CHECK( database.doesDefinitionExist( "1" ) );
  FRENSIE_CHECK( database.doesDefinitionExist( 1 ) );

  FRENSIE_CHECK( !database.doesDefinitionExist( "D2O" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( 2 ) );

  database.addDefinition( "D2O", 2, {"H2", "O"}, {2.0, 1.0} );

  FRENSIE_CHECK( database.doesDefinitionExist( "D2O" ) );
  FRENSIE_CHECK( database.doesDefinitionExist( 2 ) );

  // Invalid definition - not enough fractions
  FRENSIE_CHECK_THROW( database.addDefinition( 10, {"H", "O"}, {1.0} ),
                       std::runtime_error );

  // Invalid definition - too many fractions
  FRENSIE_CHECK_THROW( database.addDefinition( 10, {"H"}, {1.0, 2.0} ),
                       std::runtime_error );

  // Invalid definition - name is not unique
  FRENSIE_CHECK_THROW( database.addDefinition( "D2O", 10, {"H2", "0"}, {2.0, 1.0} ),
                       std::runtime_error );

  // Invalid definition - id is not unique
  FRENSIE_CHECK_THROW( database.addDefinition( "Dummy", 2, {"H"}, {1.0} ),
                       std::runtime_error );

  MonteCarlo::MaterialDefinitionDatabase::MaterialDefinitionArray definition( 3 );
  Utility::get<0>( definition[0] ) = "H1";
  Utility::get<1>( definition[0] ) = -0.3;

  Utility::get<0>( definition[1] ) = "C12";
  Utility::get<1>( definition[1] ) = -0.6;

  Utility::get<0>( definition[2] ) = "O16";
  Utility::get<1>( definition[2] ) = -0.1;

  FRENSIE_CHECK( !database.doesDefinitionExist( "3" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( 3 ) );

  database.addDefinition( 3, definition );

  FRENSIE_CHECK( database.doesDefinitionExist( "3" ) );
  FRENSIE_CHECK( database.doesDefinitionExist( 3 ) );

  definition.clear();
  definition.resize( 1 );

  Utility::get<0>( definition[0] ) = "U238";
  Utility::get<1>( definition[1] ) = 1.0;

  FRENSIE_CHECK( !database.doesDefinitionExist( "Depleted Uranium" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( 4 ) );

  database.addDefinition( "Depleted Uranium", 4, definition );

  FRENSIE_CHECK( database.doesDefinitionExist( "Depleted Uranium" ) );
  FRENSIE_CHECK( database.doesDefinitionExist( 4 ) );

  // Invalid definition - empty
  definition.clear();
  
  FRENSIE_CHECK_THROW( database.addDefinition( 10, definition ),
                       std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that a material definition can be returned
FRENSIE_UNIT_TEST( MaterialDefinitionDatabase, getDefinition )
{
  MonteCarlo::MaterialDefinitionDatabase database;

  FRENSIE_CHECK_THROW( database.getDefinition( "1" ), std::runtime_error );
  FRENSIE_CHECK_THROW( database.getDefinition( 1 ), std::runtime_error );
  
  database.addDefinition( 1, {"H", "O"}, {2.0, 1.0} );

  MonteCarlo::MaterialDefinitionDatabase::MaterialDefinitionArray
    reference_definition( 2 );

  Utility::get<0>( reference_definition[0] ) = "H";
  Utility::get<0>( reference_definition[1] ) = "O";

  Utility::get<1>( reference_definition[0] ) = 2.0;
  Utility::get<1>( reference_definition[1] ) = 1.0;

  FRENSIE_CHECK_EQUAL( database.getDefinition( "1" ), reference_definition );
  FRENSIE_CHECK_EQUAL( database.getDefinition( 1 ), reference_definition );
  FRENSIE_CHECK( &database.getDefinition( "1" ) ==
                 &database.getDefinition( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the material id associated with a material name can be returned
FRENSIE_UNIT_TEST( MaterialDefinitionDatabase, getMaterialId )
{
  MonteCarlo::MaterialDefinitionDatabase database;

  FRENSIE_CHECK_THROW( database.getMaterialId( "1" ), std::runtime_error );
  FRENSIE_CHECK_THROW( database.getMaterialId( "D2O" ), std::runtime_error );

  database.addDefinition( 1, {"H", "O"}, {2.0, 1.0} );
  database.addDefinition( "D2O", 2, {"H2", "O16"}, {2.0, 1.0} );

  FRENSIE_CHECK_EQUAL( database.getMaterialId( "1" ), 1 );
  FRENSIE_CHECK_EQUAL( database.getMaterialId( "D2O" ), 2 );
}

//---------------------------------------------------------------------------//
// Check that a material definition name associated with a material id can
// be returned
FRENSIE_UNIT_TEST( MaterialDefinitionDatabase, getMaterialName )
{
  MonteCarlo::MaterialDefinitionDatabase database;

  FRENSIE_CHECK_THROW( database.getMaterialName( 1 ), std::runtime_error );
  FRENSIE_CHECK_THROW( database.getMaterialName( 2 ), std::runtime_error );

  database.addDefinition( 1, {"H", "O"}, {2.0, 1.0} );
  database.addDefinition( "D2O", 2, {"H2", "O16"}, {2.0, 1.0} );

  FRENSIE_CHECK_EQUAL( database.getMaterialName( 1 ), "1" );
  FRENSIE_CHECK_EQUAL( database.getMaterialName( 2 ), "D2O" );
}

//---------------------------------------------------------------------------//
// Check that a material definition can be removed
FRENSIE_UNIT_TEST( MaterialDefinitionDatabase, removeDefinition )
{
  MonteCarlo::MaterialDefinitionDatabase database;

  FRENSIE_CHECK( !database.doesDefinitionExist( "1" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( 1 ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( "D2O" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( 2 ) );
  
  database.addDefinition( 1, {"H", "O"}, {2.0, 1.0} );
  database.addDefinition( "D2O", 2, {"H2", "O"}, {2.0, 1.0} );

  FRENSIE_CHECK( database.doesDefinitionExist( "1" ) );
  FRENSIE_CHECK( database.doesDefinitionExist( 1 ) );
  FRENSIE_CHECK( database.doesDefinitionExist( "D2O" ) );
  FRENSIE_CHECK( database.doesDefinitionExist( 2 ) );

  database.removeDefinition( 1 );

  FRENSIE_CHECK( !database.doesDefinitionExist( "1" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( 1 ) );
  FRENSIE_CHECK( database.doesDefinitionExist( "D2O" ) );
  FRENSIE_CHECK( database.doesDefinitionExist( 2 ) );

  database.removeDefinition( "D2O" );

  FRENSIE_CHECK( !database.doesDefinitionExist( "1" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( 1 ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( "D2O" ) );
  FRENSIE_CHECK( !database.doesDefinitionExist( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that the material definitions can be iterated over
FRENSIE_UNIT_TEST( MaterialDefinitionDatabase, iterate )
{
  MonteCarlo::MaterialDefinitionDatabase database;
  
  database.addDefinition( 1, {"H", "O"}, {2.0, 1.0} );
  database.addDefinition( "D2O", 2, {"H2", "O"}, {2.0, 1.0} );
  
  MonteCarlo::MaterialDefinitionDatabase::MaterialDefinitionIterator
    material_def_it = database.begin();

  FRENSIE_CHECK_EQUAL( std::distance( material_def_it, database.end() ), 2 );

  std::advance( material_def_it, 2 );

  FRENSIE_CHECK( material_def_it == database.end() );
}

//---------------------------------------------------------------------------//
// Check that the material ids can be returned
FRENSIE_UNIT_TEST( MaterialDefinitionDatabase, getMaterialIds )
{
  MonteCarlo::MaterialDefinitionDatabase database;
  
  database.addDefinition( 1, {"H", "O"}, {2.0, 1.0} );
  database.addDefinition( "D2O", 2, {"H2", "O"}, {2.0, 1.0} );
  
  MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet material_ids;

  database.getMaterialIds( material_ids );

  FRENSIE_CHECK_EQUAL( material_ids.size(), 2 );
  FRENSIE_CHECK( material_ids.count( 1 ) );
  FRENSIE_CHECK( material_ids.count( 2 ) );

  material_ids.clear();

  material_ids = database.getMaterialIds();

  FRENSIE_CHECK_EQUAL( material_ids.size(), 2 );
  FRENSIE_CHECK( material_ids.count( 1 ) );
  FRENSIE_CHECK( material_ids.count( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that the unique scattering center names can be returned
FRENSIE_UNIT_TEST( MaterialDefinitionDatabase, getUniqueScatteringCenterNames )
{
  MonteCarlo::MaterialDefinitionDatabase database;
  
  database.addDefinition( 1, {"H", "O"}, {2.0, 1.0} );
  database.addDefinition( "D2O", 2, {"H2", "O"}, {2.0, 1.0} );

  MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet
    unique_scattering_center_names = database.getUniqueScatteringCenterNames();

  FRENSIE_CHECK_EQUAL( unique_scattering_center_names.size(), 3 );
  FRENSIE_CHECK( unique_scattering_center_names.count( "H" ) );
  FRENSIE_CHECK( unique_scattering_center_names.count( "H2" ) );
  FRENSIE_CHECK( unique_scattering_center_names.count( "O" ) );

  unique_scattering_center_names = database.getUniqueScatteringCenterNames(
                                                       std::set<size_t>({2}) );

  FRENSIE_CHECK_EQUAL( unique_scattering_center_names.size(), 2 );
  FRENSIE_CHECK( unique_scattering_center_names.count( "H2" ) );
  FRENSIE_CHECK( unique_scattering_center_names.count( "O" ) );
  
  database.addDefinition( 3, {"H", "C", "O"}, {4, 1, 1} );

  unique_scattering_center_names.clear();

  database.getUniqueScatteringCenterNames( unique_scattering_center_names );

  FRENSIE_CHECK_EQUAL( unique_scattering_center_names.size(), 4 );
  FRENSIE_CHECK( unique_scattering_center_names.count( "H" ) );
  FRENSIE_CHECK( unique_scattering_center_names.count( "H2" ) );
  FRENSIE_CHECK( unique_scattering_center_names.count( "O" ) );
  FRENSIE_CHECK( unique_scattering_center_names.count( "C" ) );

  unique_scattering_center_names.clear();

  database.getUniqueScatteringCenterNames( std::unordered_set<int>({3}),
                                           unique_scattering_center_names );
                                           

  FRENSIE_CHECK_EQUAL( unique_scattering_center_names.size(), 3 );
  FRENSIE_CHECK( unique_scattering_center_names.count( "H" ) );
  FRENSIE_CHECK( unique_scattering_center_names.count( "O" ) );
  FRENSIE_CHECK( unique_scattering_center_names.count( "C" ) );
}

//---------------------------------------------------------------------------//
// Check that the database can be placed in a stream
FRENSIE_UNIT_TEST( MaterialDefinitionDatabase, toStream )
{
  MonteCarlo::MaterialDefinitionDatabase database;
  
  database.addDefinition( 1, {"H", "O"}, {2.0, 1.0} );
  database.addDefinition( "D2O", 2, {"H2", "O"}, {2.0, 1.0} );
  database.addDefinition( 3, {"H", "C", "O"}, {4, 1, 1} );

  FRENSIE_CHECK_NO_THROW( std::cout << "\n" << database << std::endl; );
}

//---------------------------------------------------------------------------//
// Check that a database can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MaterialDefinitionDatabase,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_material_definition_database" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::MaterialDefinitionDatabase database;
  
    database.addDefinition( 1, {"H", "O"}, {2.0, 1.0} );
    database.addDefinition( "D2O", 2, {"H2", "O"}, {2.0, 1.0} );
    database.addDefinition( 3, {"H", "C", "O"}, {4, 1, 1} );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(database) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::MaterialDefinitionDatabase database;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(database) );

  iarchive.reset();

  FRENSIE_REQUIRE( database.doesDefinitionExist( "1" ) );
  FRENSIE_REQUIRE( database.doesDefinitionExist( 1 ) );
  FRENSIE_CHECK_EQUAL( database.getDefinition( 1 ).size(), 2 );
  
  FRENSIE_REQUIRE( database.doesDefinitionExist( "D2O" ) );
  FRENSIE_REQUIRE( database.doesDefinitionExist( 2 ) );
  FRENSIE_CHECK_EQUAL( database.getDefinition( 2 ).size(), 2 );

  
  FRENSIE_REQUIRE( database.doesDefinitionExist( "3" ) );
  FRENSIE_REQUIRE( database.doesDefinitionExist( 3 ) );
  FRENSIE_CHECK_EQUAL( database.getDefinition( 3 ).size(), 3 );
}

//---------------------------------------------------------------------------//
// end tstMaterialDefinitionDatabase.cpp
//---------------------------------------------------------------------------//
