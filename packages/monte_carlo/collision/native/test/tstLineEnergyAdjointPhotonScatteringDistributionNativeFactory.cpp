//---------------------------------------------------------------------------//
//!
//! \file   tstLineEnergyAdjointPhotonScatteringDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  Line energy adjoint photon scattering distribution native factory
//!         unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_LineEnergyAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::AdjointElectronPhotonRelaxationDataContainer>
  data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that  a pair production distribution can be created
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistributioNativeFactory,
                   createPairProductionDistribution )
{
  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotonScatteringDistribution>
    distribution;

  double cross_section_value;

  // Create a distribution with max energy = 20.0 MeV
  MonteCarlo::LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createPairProductionDistribution(
                                                           *data_container,
                                                           distribution,
                                                           cross_section_value,
                                                           20.0 );

  // Test the distribution
  TEST_ASSERT( distribution.get() );
  TEST_EQUALITY_CONST( distribution->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( distribution->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( distribution->getMaxOutgoingEnergy(), 20.0 );
  TEST_FLOATING_EQUALITY( cross_section_value, 14.739362127632583, 1e-15 );

  // Create a distribution with max energy = 1.03 MeV
  MonteCarlo::LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createPairProductionDistribution(
                                                           *data_container,
                                                           distribution,
                                                           cross_section_value,
                                                           1.03 );

  // Test the distribution
  TEST_ASSERT( distribution.get() );
  TEST_EQUALITY_CONST( distribution->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( distribution->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( distribution->getMaxOutgoingEnergy(), 1.03 );
  TEST_FLOATING_EQUALITY( cross_section_value, 4.815451815420467e-10, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a triplet production distribution can be created
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistributionNativeFactory,
                   createTripletProductionDistribution )
{
  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotonScatteringDistribution>
    distribution;

  double cross_section_value;

  // Create a distribution with max energy = 20.0 MeV
  MonteCarlo::LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createTripletProductionDistribution(
                                                           *data_container,
                                                           distribution,
                                                           cross_section_value,
                                                           20.0 );

  // Test the distribution
  TEST_ASSERT( distribution.get() );
  TEST_EQUALITY_CONST( distribution->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( distribution->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( distribution->getMaxOutgoingEnergy(), 20.0 );
  TEST_FLOATING_EQUALITY( cross_section_value, 0.6221793747726394, 1e-15 );

  // Create a distribution with max energy = 2.05 MeV
  MonteCarlo::LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createTripletProductionDistribution(
                                                           *data_container,
                                                           distribution,
                                                           cross_section_value,
                                                           2.05 );

  // Test the distribution
  TEST_ASSERT( distribution.get() );
  TEST_EQUALITY_CONST( distribution->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( distribution->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( distribution->getMaxOutgoingEnergy(), 2.05 );
  TEST_FLOATING_EQUALITY( cross_section_value, 1.2123883500190036e-10, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                                                     test_native_file_name ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLineEnergyAdjointPhotonScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
