//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCModelIArchive.cpp
//! \author Alex Robinson
//! \brief  DagMC model class initialization from input archive
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <fstream>
#include <memory>

// Boost Includes
#include <boost/archive/xml_iarchive.hpp>

// FRENSIE Includes
#include "Geometry_DagMCModel.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<std::ifstream> archive_istream;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a model can be initialized from an archive
FRENSIE_UNIT_TEST( DagMCModel, iarchive )
{
  std::unique_ptr<boost::archive::xml_iarchive>
    iarchive( new boost::archive::xml_iarchive( *archive_istream ) );

  std::shared_ptr<Geometry::DagMCModel> model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( model ) );

  Geometry::Model::CellIdSet cells;
  model->getCells( cells, true, true );
  
  FRENSIE_CHECK_EQUAL( cells.size(), 56 );
  FRENSIE_CHECK( cells.count( 1 ) );
  FRENSIE_CHECK( cells.count( 3 ) );
  FRENSIE_CHECK( cells.count( 5 ) );
  FRENSIE_CHECK( cells.count( 7 ) );
  FRENSIE_CHECK( cells.count( 9 ) );
  FRENSIE_CHECK( cells.count( 13 ) );
  FRENSIE_CHECK( cells.count( 19 ) );
  FRENSIE_CHECK( cells.count( 26 ) );
  FRENSIE_CHECK( cells.count( 27 ) );
  FRENSIE_CHECK( cells.count( 28 ) );
  FRENSIE_CHECK( cells.count( 29 ) );
  FRENSIE_CHECK( cells.count( 30 ) );
  FRENSIE_CHECK( cells.count( 31 ) );
  FRENSIE_CHECK( cells.count( 32 ) );
  FRENSIE_CHECK( cells.count( 33 ) );
  FRENSIE_CHECK( cells.count( 34 ) );
  FRENSIE_CHECK( cells.count( 35 ) );
  FRENSIE_CHECK( cells.count( 36 ) );
  FRENSIE_CHECK( cells.count( 37 ) );
  FRENSIE_CHECK( cells.count( 41 ) );
  FRENSIE_CHECK( cells.count( 48 ) );
  FRENSIE_CHECK( cells.count( 49 ) );
  FRENSIE_CHECK( cells.count( 50 ) );
  FRENSIE_CHECK( cells.count( 51 ) );
  FRENSIE_CHECK( cells.count( 52 ) );
  FRENSIE_CHECK( cells.count( 53 ) );
  FRENSIE_CHECK( cells.count( 54 ) );
  FRENSIE_CHECK( cells.count( 55 ) );
  FRENSIE_CHECK( cells.count( 56 ) );
  FRENSIE_CHECK( cells.count( 57 ) );
  FRENSIE_CHECK( cells.count( 58 ) );
  FRENSIE_CHECK( cells.count( 59 ) );
  FRENSIE_CHECK( cells.count( 63 ) );
  FRENSIE_CHECK( cells.count( 70 ) );
  FRENSIE_CHECK( cells.count( 71 ) );
  FRENSIE_CHECK( cells.count( 72 ) );
  FRENSIE_CHECK( cells.count( 73 ) );
  FRENSIE_CHECK( cells.count( 74 ) );
  FRENSIE_CHECK( cells.count( 75 ) );
  FRENSIE_CHECK( cells.count( 76 ) );
  FRENSIE_CHECK( cells.count( 77 ) );
  FRENSIE_CHECK( cells.count( 78 ) );
  FRENSIE_CHECK( cells.count( 79 ) );
  FRENSIE_CHECK( cells.count( 80 ) );
  FRENSIE_CHECK( cells.count( 81 ) );
  FRENSIE_CHECK( cells.count( 82 ) );
  FRENSIE_CHECK( cells.count( 83 ) );
  FRENSIE_CHECK( cells.count( 88 ) );
  FRENSIE_CHECK( cells.count( 136 ) );
  FRENSIE_CHECK( cells.count( 152 ) );
  FRENSIE_CHECK( cells.count( 154 ) );
  FRENSIE_CHECK( cells.count( 166 ) );
  FRENSIE_CHECK( cells.count( 168 ) );
  FRENSIE_CHECK( cells.count( 184 ) );
  FRENSIE_CHECK( cells.count( 188 ) );
  FRENSIE_CHECK( cells.count( 189 ) );

  Geometry::AdvancedModel::SurfaceIdSet surfaces;

  model->getSurfaces( surfaces );

  FRENSIE_CHECK_EQUAL( surfaces.size(), 293 );

  FRENSIE_CHECK_EQUAL( model->getModelProperties().getTerminationCellPropertyName(), "graveyard" );
  FRENSIE_CHECK_EQUAL( model->getModelProperties().getMaterialPropertyName(), "mat" );
  FRENSIE_CHECK_EQUAL( model->getModelProperties().getDensityPropertyName(), "rho" );
  FRENSIE_CHECK_EQUAL( model->getModelProperties().getEstimatorPropertyName(), "tally" );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_model_archive_name;
std::string reset_path;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_archive_file",
                                        test_dagmc_model_archive_name, "",
                                        "Test dagmc model xml archive name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "reset_path",
                                        reset_path, "",
                                        "The path that will be used to "
                                        "instead of the archived model path" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  archive_istream.reset( new std::ifstream( test_dagmc_model_archive_name ) );

  if( !reset_path.empty() )
    Geometry::DagMCModelProperties::setDefaultFilePath( reset_path );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDagMCModelIArchive.cpp
//---------------------------------------------------------------------------//
