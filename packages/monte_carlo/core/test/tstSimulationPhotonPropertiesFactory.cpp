//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationPhotonPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties factory unit tests
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
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "MonteCarlo_SimulationPhotonPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::ParameterList properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the properties can be parsed and set
TEUCHOS_UNIT_TEST( SimulationPhotonPropertiesFactory, initializeProperties )
{
  Teuchos::ParameterList photon_properties =
    properties.get<Teuchos::ParameterList>( "Photon Properties" );

  MonteCarlo::SimulationPhotonProperties properties;

  MonteCarlo::SimulationPhotonPropertiesFactory::initializeProperties(
                                                             photon_properties,
                                                             properties );

  TEST_EQUALITY_CONST( properties.getMinPhotonEnergy(), 1e-2 );
  TEST_EQUALITY_CONST( properties.getMaxPhotonEnergy(), 10.0 );
  TEST_EQUALITY_CONST( properties.getKahnSamplingCutoffEnergy(), 2.5 );
  TEST_EQUALITY_CONST( properties.getNumberOfPhotonHashGridBins(), 500 );
  TEST_EQUALITY_CONST( properties.getIncoherentModelType(),
                       MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  TEST_ASSERT( !properties.isAtomicRelaxationModeOn() );
  TEST_ASSERT( properties.isDetailedPairProductionModeOn() );
  TEST_ASSERT( properties.isPhotonuclearInteractionModeOn() );
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
// end tstSimulationPhotonPropertiesFactory.cpp
//---------------------------------------------------------------------------//
