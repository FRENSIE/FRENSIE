//---------------------------------------------------------------------------//
//!
//! \file   tstRootModelIArchive.cpp
//! \author Alex Robinson
//! \brief  Root model class initialization from input archive
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <fstream>
#include <memory>

// Boost Includes
#include <boost/archive/xml_iarchive.hpp>

// FRENSIE Includes
#include "Geometry_RootModel.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<std::ifstream> archive_istream;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a model can be initialized from an archive
FRENSIE_UNIT_TEST( RootModel, iarchive )
{
  Utility::JustInTimeInitializer::getInstance().activate();
  
  std::unique_ptr<boost::archive::xml_iarchive>
    iarchive( new boost::archive::xml_iarchive( *archive_istream ) );

  std::shared_ptr<Geometry::RootModel> model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( model ) );

  iarchive.reset();

  FRENSIE_REQUIRE( !model->isInitialized() );

  const Geometry::RootModelProperties& cached_properties =
    model->getModelProperties();

  FRENSIE_CHECK( cached_properties.getModelFileName().find( "basic_root_geometry.root" ) <
                 cached_properties.getModelFileName().size() );

  // Initialize the model
  FRENSIE_CHECK_EQUAL( Utility::JustInTimeInitializer::getInstance().getNumberOfObjects(), 1 );

  FRENSIE_REQUIRE_NO_THROW( Utility::JustInTimeInitializer::getInstance().initializeObjectsAndClear() );

  // Get all cells
  Geometry::Model::CellIdSet cells;

  model->getCells( cells, true, true );

  FRENSIE_REQUIRE_EQUAL( cells.size(), 3 );
  FRENSIE_REQUIRE( cells.count( 1 ) );
  FRENSIE_REQUIRE( cells.count( 2 ) );
  FRENSIE_REQUIRE( cells.count( 3 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( model->getCellVolume( 1 ),
                                   934.550153050213*cgs::cubic_centimeter,
                                   1e-9 );

  FRENSIE_CHECK_FLOATING_EQUALITY( model->getCellVolume( 2 ),
                                   65.4498469497874*cgs::cubic_centimeter,
                                   1e-9 );

  FRENSIE_CHECK_FLOATING_EQUALITY( model->getCellVolume( 3 ),
                                   1744.0*cgs::cubic_centimeter,
                                   1e-9 );

  FRENSIE_CHECK( model->getModelProperties().getModelFileName().find( "basic_root_geometry.root" ) < model->getModelProperties().getModelFileName().size() );
  FRENSIE_CHECK_EQUAL( model->getModelProperties().getMaterialPropertyName(), "mat" );
  FRENSIE_CHECK_EQUAL( model->getModelProperties().getVoidMaterialName(), "void" );
  FRENSIE_CHECK_EQUAL( model->getModelProperties().getTerminalMaterialName(), "graveyard" );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_root_model_archive_name;
std::string reset_path;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_archive_file",
                                        test_root_model_archive_name, "",
                                        "Test root model xml archive name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "reset_path",
                                        reset_path, "",
                                        "The path that will be used to "
                                        "instead of the archived model path" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  archive_istream.reset( new std::ifstream( test_root_model_archive_name ) );

  if( !reset_path.empty() )
    Geometry::RootModelProperties::setDefaultFilePath( reset_path );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstRootModelIArchive.cpp
//---------------------------------------------------------------------------//
