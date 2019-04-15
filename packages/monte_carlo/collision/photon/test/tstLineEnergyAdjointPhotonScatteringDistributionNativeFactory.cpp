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

// FRENSIE Includes
#include "MonteCarlo_LineEnergyAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::AdjointElectronPhotonRelaxationDataContainer>
  data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that  a pair production distribution can be created
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistributioNativeFactory,
                   createPairProductionDistribution )
{
  std::shared_ptr<MonteCarlo::LineEnergyAdjointPhotonScatteringDistribution>
    distribution;

  double cross_section_value;

  // Create a distribution with max energy = 20.0 MeV
  MonteCarlo::LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createPairProductionDistribution(
                                                           *data_container,
                                                           distribution,
                                                           cross_section_value,
                                                           20.0 );

  // Test the distribution
  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK_EQUAL( distribution->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( distribution->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( distribution->getMaxOutgoingEnergy(), 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section_value, 14.739362127632583, 1e-15 );

  // Create a distribution with max energy = 1.03 MeV
  MonteCarlo::LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createPairProductionDistribution(
                                                           *data_container,
                                                           distribution,
                                                           cross_section_value,
                                                           1.03 );

  // Test the distribution
  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK_EQUAL( distribution->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( distribution->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( distribution->getMaxOutgoingEnergy(), 1.03 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section_value, 4.709293491094194530e-10, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a triplet production distribution can be created
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistributionNativeFactory,
                   createTripletProductionDistribution )
{
  std::shared_ptr<MonteCarlo::LineEnergyAdjointPhotonScatteringDistribution>
    distribution;

  double cross_section_value;

  // Create a distribution with max energy = 20.0 MeV
  MonteCarlo::LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createTripletProductionDistribution(
                                                           *data_container,
                                                           distribution,
                                                           cross_section_value,
                                                           20.0 );

  // Test the distribution
  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK_EQUAL( distribution->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( distribution->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( distribution->getMaxOutgoingEnergy(), 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section_value, 0.6221793747726394, 1e-15 );

  // Create a distribution with max energy = 2.05 MeV
  MonteCarlo::LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createTripletProductionDistribution(
                                                           *data_container,
                                                           distribution,
                                                           cross_section_value,
                                                           2.05 );

  // Test the distribution
  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK_EQUAL( distribution->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( distribution->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( distribution->getMaxOutgoingEnergy(), 2.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section_value, 1.2123883500190036e-10, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container
  data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                                                     test_native_file_name ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLineEnergyAdjointPhotonScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
