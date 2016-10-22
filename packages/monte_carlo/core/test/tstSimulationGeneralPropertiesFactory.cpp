//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationGeneralPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties factory unit tests
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
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "MonteCarlo_SimulationGeneralPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::ParameterList properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the properties can be parsed and set
TEUCHOS_UNIT_TEST( SimulationGeneralPropertiesFactory, initializeProperties )
{
  Teuchos::ParameterList general_properties =
    properties.get<Teuchos::ParameterList>( "General Properties" );
  
  MonteCarlo::SimulationGeneralProperties properties;

  MonteCarlo::SimulationGeneralPropertiesFactory::initializeProperties(
                                                            general_properties,
                                                            properties );

  TEST_EQUALITY_CONST( properties.getParticleMode(),
		       MonteCarlo::NEUTRON_PHOTON_MODE );
  TEST_EQUALITY_CONST( properties.getNumberOfHistories(), 10 );
  TEST_EQUALITY_CONST( properties.getSurfaceFluxEstimatorAngleCosineCutoff(),
		       0.1 );
  TEST_ASSERT( !properties.displayWarnings() );
  TEST_ASSERT( properties.isImplicitCaptureModeOn() );
  TEST_EQUALITY_CONST( properties.getNumberOfBatchesPerProcessor(), 25 );
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
// end tstSimulationGeneralPropertiesFactory.cpp
//---------------------------------------------------------------------------//
