//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCNavigatorIArchive.cpp
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
#include "Geometry_DagMCNavigator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<std::ifstream> archive_istream;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a model can be initialized from an archive
FRENSIE_UNIT_TEST( DagMCNavigator, iarchive )
{
  std::unique_ptr<boost::archive::xml_iarchive>
    iarchive( new boost::archive::xml_iarchive( *archive_istream ) );

  std::shared_ptr<Geometry::DagMCNavigator> navigator;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( navigator ) );

  FRENSIE_CHECK_EQUAL( navigator->getCellContainingInternalRay(), 82 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[0], -40.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[1], -40.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[2], 108.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_navigator_archive_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_archive_file",
                                        test_dagmc_navigator_archive_name, "",
                                        "Test dagmc navigator xml archive name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  archive_istream.reset( new std::ifstream( test_dagmc_navigator_archive_name ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDagMCNavigatorIArchive.cpp
//---------------------------------------------------------------------------//
