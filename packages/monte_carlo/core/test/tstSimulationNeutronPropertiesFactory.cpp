//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationNeutronPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation neutron properties factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "MonteCarlo_SimulationNeutronPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::ParameterList properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the properties can be parsed and set
TEUCHOS_UNIT_TEST( SimulationNeutronPropertiesFactory, initializeProperties )
{
  Teuchos::ParameterList neutron_properties =
      properties.get<Teuchos::ParameterList>( "Neutron Properties" );

  MonteCarlo::SimulationNeutronProperties properties;

  MonteCarlo::SimulationNeutronPropertiesFactory::initializeProperties(
                                                            neutron_properties,
                                                            properties );

  TEST_EQUALITY_CONST( properties.getFreeGasThreshold(), 600.0 );
  TEST_EQUALITY_CONST( properties.getMinNeutronEnergy(), 1e-2 );
  TEST_EQUALITY_CONST( properties.getMaxNeutronEnergy(), 10.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_properties_xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_properties_xml_file",
                   &test_properties_xml_file_name,
                   "Test properties.xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Read in the xml file storing the simulation properties
  Teuchos::updateParametersFromXmlFile( test_properties_xml_file_name,
                                        Teuchos::inoutArg( properties ) );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSimulationNeutronPropertiesFactory.cpp
//---------------------------------------------------------------------------//
