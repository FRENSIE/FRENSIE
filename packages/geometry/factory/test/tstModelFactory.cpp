//---------------------------------------------------------------------------//
//!
//! \file   tstModelFactory.cpp
//! \author Alex Robinson
//! \brief  Model factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_ModelFactory.hpp"
#include "Geometry_Config.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<const Teuchos::ParameterList> dagmc_model_data;
Teuchos::RCP<const Teuchos::ParameterList> root_model_data;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a DagMC model can be created
TEUCHOS_UNIT_TEST( ModelFactory, createModel_dagmc )
{
#ifdef HAVE_FRENSIE_DAGMC
  std::shared_ptr<const Geometry::Model> model;

  TEST_NOTHROW( model = Geometry::ModelFactory::createModel( *dagmc_model_data ) );
  TEST_ASSERT( model.get() != NULL );
#else // HAVE_FRENSIE_DAGMC
  TEST_THROW( model = Geomtry::ModelFactory::createModel( *dagmc_model_data ),
              std::runtime_error );
#endif // end HAVE_FRANSIE_DAGMC
}

//---------------------------------------------------------------------------//
// Check that a Root model can be created
TEUCHOS_UNIT_TEST( ModelFactory, createModel_root )
{
#ifdef HAVE_FRENSIE_ROOT
  std::shared_ptr<const Geometry::Model> model;

  TEST_NOTHROW( model = Geometry::ModelFactory::createModel( *root_model_data ) );
  TEST_ASSERT( model.get() != NULL );
#else // HAVE_FRENSIE_ROOT
  TEST_THROW( model = Geometry::ModelFactory::createModel( *root_model_data ),
              std::runtime_error );
#endif // end HAVE_FRENSIE_ROOT
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string dagmc_xml_file_name, root_xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_dagmc_xml_file",
                   &dagmc_xml_file_name,
                   "DagMC model xml file name" );
  clp().setOption( "test_root_xml_file",
                   &root_xml_file_name,
                   "Root model xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Load the model data files
  dagmc_model_data =
    Teuchos::getParametersFromXmlFile( dagmc_xml_file_name );

  root_model_data =
    Teuchos::getParametersFromXmlFile( root_xml_file_name );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstModelFactory.cpp
//---------------------------------------------------------------------------//

