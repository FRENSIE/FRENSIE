//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationAdjointElectronPropertiesFactory.cpp
//! \author Luke Kersting
//! \brief  Simulation adjoint electron properties factory unit tests
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
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
#include "MonteCarlo_SimulationAdjointElectronPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::ParameterList properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the properties can be parsed and set
TEUCHOS_UNIT_TEST( SimulationAdjointElectronPropertiesFactory,
                   initializeProperties )
{
  Teuchos::ParameterList adjoint_electron_properties =
    properties.get<Teuchos::ParameterList>( "Adjoint Electron Properties" );

  MonteCarlo::SimulationAdjointElectronProperties properties;

  MonteCarlo::SimulationAdjointElectronPropertiesFactory::initializeProperties(
                                                     adjoint_electron_properties,
                                                     properties );

  TEST_EQUALITY_CONST( properties.getMinAdjointElectronEnergy(), 1e-2 );
  TEST_EQUALITY_CONST( properties.getMaxAdjointElectronEnergy(), 10.0 );
  TEST_ASSERT( properties.isAdjointElasticModeOn() );
  TEST_EQUALITY_CONST( properties.getAdjointElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );
  TEST_EQUALITY_CONST( properties.getAdjointCoupledElasticSamplingMode(),
                       MonteCarlo::ONE_D_UNION );
  TEST_ASSERT( !properties.isAdjointElectroionizationModeOn() );
  TEST_ASSERT( !properties.isAdjointAtomicExcitationModeOn() );
  TEST_ASSERT( properties.isAdjointBremsstrahlungModeOn() );
  TEST_EQUALITY_CONST(
             properties.getAdjointBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::DIPOLE_DISTRIBUTION );
  TEST_EQUALITY_CONST( properties.getAdjointElasticCutoffAngleCosine(),
                       0.9 );
  TEST_EQUALITY_CONST( properties.getNumberOfAdjointElectronHashGridBins(),
                       400 );
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
// end tstSimulationAdjointElectronPropertiesFactory.cpp
//---------------------------------------------------------------------------//
