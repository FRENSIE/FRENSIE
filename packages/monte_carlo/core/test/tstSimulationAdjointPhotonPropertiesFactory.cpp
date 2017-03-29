//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationAdjointPhotonPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties factory unit tests
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
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "MonteCarlo_SimulationAdjointPhotonPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::ParameterList properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the properties can be parsed and set
TEUCHOS_UNIT_TEST( SimulationAdjointPhotonPropertiesFactory,
                   initializeProperties )
{
  Teuchos::ParameterList adjoint_photon_properties =
    properties.get<Teuchos::ParameterList>( "Adjoint Photon Properties" );

  MonteCarlo::SimulationAdjointPhotonProperties properties;

  MonteCarlo::SimulationAdjointPhotonPropertiesFactory::initializeProperties(
                                                     adjoint_photon_properties,
                                                     properties );

  TEST_EQUALITY_CONST( properties.getMinAdjointPhotonEnergy(), 1e-2 );
  TEST_EQUALITY_CONST( properties.getMaxAdjointPhotonEnergy(), 10.0 );
  TEST_EQUALITY_CONST( properties.getNumberOfAdjointPhotonHashGridBins(),
                       500 );
  TEST_EQUALITY_CONST( properties.getIncoherentAdjointModelType(),
                       MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );
  TEST_EQUALITY_CONST( properties.getCriticalAdjointPhotonLineEnergies().size(), 3 );
  TEST_EQUALITY_CONST( properties.getCriticalAdjointPhotonLineEnergies()[0], 0.1 );
  TEST_EQUALITY_CONST( properties.getCriticalAdjointPhotonLineEnergies()[1], 1.0 );
  TEST_EQUALITY_CONST( properties.getCriticalAdjointPhotonLineEnergies()[2], 10.0 );
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
// end tstSimulationAdjointPhotonPropertiesFactory.cpp
//---------------------------------------------------------------------------//
