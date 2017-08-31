//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationElectronPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation electron properties factory unit tests
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
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "MonteCarlo_SimulationElectronPropertiesFactory.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::ParameterList properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the properties can be parsed and set
TEUCHOS_UNIT_TEST( SimulationElectronPropertiesFactory, initializeProperties )
{
  Teuchos::ParameterList electron_properties =
      properties.get<Teuchos::ParameterList>( "Electron Properties" );

  MonteCarlo::SimulationElectronProperties properties;

  MonteCarlo::SimulationElectronPropertiesFactory::initializeProperties(
                                                           electron_properties,
                                                           properties );

  TEST_EQUALITY_CONST( properties.getMinElectronEnergy(), 1e-2 );
  TEST_EQUALITY_CONST( properties.getMaxElectronEnergy(), 10.0 );
  TEST_EQUALITY_CONST( properties.getNumberOfElectronHashGridBins(), 400 );
  TEST_EQUALITY_CONST( properties.getElectronEvaluationTolerance(), 1e-5 );
  TEST_ASSERT( !properties.isCorrelatedSamplingModeOn() );
  TEST_ASSERT( !properties.isUnitBasedInterpolationModeOn() );
  TEST_ASSERT( !properties.isAtomicRelaxationModeOn() );
  TEST_ASSERT( !properties.isElasticModeOn() );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       MonteCarlo::LINLINLIN_INTERPOLATION );
  TEST_EQUALITY_CONST( properties.getElasticElectronDistributionMode(),
                       MonteCarlo::HYBRID_DISTRIBUTION );
  TEST_EQUALITY_CONST( properties.getElasticCutoffAngleCosine(), 0.9 );
  TEST_ASSERT( !properties.isElectroionizationModeOn() );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       MonteCarlo::LINLINLIN_INTERPOLATION );
  TEST_ASSERT( !properties.isBremsstrahlungModeOn() );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       MonteCarlo::LINLINLIN_INTERPOLATION );
  TEST_EQUALITY_CONST(
             properties.getBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::DIPOLE_DISTRIBUTION );
  TEST_ASSERT( !properties.isAtomicExcitationModeOn() );
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
// end tstSimulationElectronPropertiesFactory.cpp
//---------------------------------------------------------------------------//
