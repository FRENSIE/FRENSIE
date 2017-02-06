//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  Simulation properties factory unit tests
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
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_SimulationPropertiesFactory.hpp"
#include "MonteCarlo_ElectronSecondaryInterpolationType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::ParameterList properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the properties can be parsed and set
TEUCHOS_UNIT_TEST( SimulationPropertiesFactory, createProperties )
{
  std::shared_ptr<const MonteCarlo::SimulationProperties> parsed_properties =
    MonteCarlo::SimulationPropertiesFactory::createProperties( properties, &out );

  // General Properties
  TEST_EQUALITY_CONST( parsed_properties->getParticleMode(),
                       MonteCarlo::NEUTRON_PHOTON_MODE );
  TEST_EQUALITY_CONST( parsed_properties->getNumberOfHistories(), 10 );
  TEST_EQUALITY_CONST( parsed_properties->getSurfaceFluxEstimatorAngleCosineCutoff(),
                       0.1 );
  TEST_ASSERT( !parsed_properties->displayWarnings() );
  TEST_ASSERT( parsed_properties->isImplicitCaptureModeOn() );
  TEST_EQUALITY_CONST( parsed_properties->getNumberOfBatchesPerProcessor(), 25 );

  // Neutron Properties
  TEST_EQUALITY_CONST( parsed_properties->getFreeGasThreshold(), 600.0 );
  TEST_EQUALITY_CONST( parsed_properties->getMinNeutronEnergy(), 1e-2 );
  TEST_EQUALITY_CONST( parsed_properties->getMaxNeutronEnergy(), 10.0 );
  TEST_ASSERT( !parsed_properties->isUnresolvedResonanceProbabilityTableModeOn() );

  // Photon Properties
  TEST_EQUALITY_CONST( parsed_properties->getMinPhotonEnergy(), 1e-2 );
  TEST_EQUALITY_CONST( parsed_properties->getMaxPhotonEnergy(), 10.0 );
  TEST_EQUALITY_CONST( parsed_properties->getKahnSamplingCutoffEnergy(), 2.5 );
  TEST_EQUALITY_CONST( parsed_properties->getNumberOfPhotonHashGridBins(), 500 );
  TEST_EQUALITY_CONST( parsed_properties->getIncoherentModelType(),
                       MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  TEST_ASSERT( !parsed_properties->isAtomicRelaxationModeOn( MonteCarlo::PHOTON ) );
  TEST_ASSERT( parsed_properties->isDetailedPairProductionModeOn() );
  TEST_ASSERT( parsed_properties->isPhotonuclearInteractionModeOn() );
  
  // Adjoint Photon Properties
  TEST_EQUALITY_CONST( parsed_properties->getMinAdjointPhotonEnergy(), 1e-2 );
  TEST_EQUALITY_CONST( parsed_properties->getMaxAdjointPhotonEnergy(), 10.0 );
  TEST_EQUALITY_CONST( parsed_properties->getNumberOfAdjointPhotonHashGridBins(),
                       500 );
  TEST_EQUALITY_CONST( parsed_properties->getIncoherentAdjointModelType(),
                       MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );
  TEST_EQUALITY_CONST( parsed_properties->getCriticalAdjointPhotonLineEnergies().size(), 3 );
  TEST_EQUALITY_CONST( parsed_properties->getCriticalAdjointPhotonLineEnergies()[0], 0.1 );
  TEST_EQUALITY_CONST( parsed_properties->getCriticalAdjointPhotonLineEnergies()[1], 1.0 );
  TEST_EQUALITY_CONST( parsed_properties->getCriticalAdjointPhotonLineEnergies()[2], 10.0 );
  
  // Electron Properties
  TEST_EQUALITY_CONST( parsed_properties->getMinElectronEnergy(), 1e-2 );
  TEST_EQUALITY_CONST( parsed_properties->getMaxElectronEnergy(), 10.0 );
  TEST_ASSERT( !parsed_properties->isAtomicRelaxationModeOn( MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !parsed_properties->isElasticModeOn() );
  TEST_ASSERT( !parsed_properties->isElectroionizationModeOn() );
  TEST_ASSERT( !parsed_properties->isBremsstrahlungModeOn() );
  TEST_ASSERT( !parsed_properties->isAtomicExcitationModeOn() );
  TEST_ASSERT( !parsed_properties->isWeightedInterpolationModeOn() );
  TEST_EQUALITY_CONST( parsed_properties->getSecondaryInterpolationMethod(),
                       MonteCarlo::LIN_LIN_LIN );
  TEST_EQUALITY_CONST(
             parsed_properties->getBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::DIPOLE_DISTRIBUTION );
  TEST_EQUALITY_CONST( parsed_properties->getElasticCutoffAngleCosine(), 0.9 );
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
// end tstSimulationPropertiesFactory.cpp
//---------------------------------------------------------------------------//
