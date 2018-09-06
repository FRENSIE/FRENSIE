//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation scattering distribution Native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::unique_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
   distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
FRENSIE_UNIT_TEST( AtomicExcitationElectronScatteringDistributionNativeFactory,
                   sample )
{
  MonteCarlo::AtomicExcitationElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
    *data_container,
    distribution );

  double incoming_energy = 1.000000000000e-03;
  double outgoing_energy,scattering_angle_cosine;

  // sample distribution
  distribution->sample( incoming_energy,
                        outgoing_energy,
                        scattering_angle_cosine );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy,
                          1.000000000000e-03- 9.32298000000E-06,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
FRENSIE_UNIT_TEST( AtomicExcitationElectronScatteringDistributionNativeFactory,
                   sampleAndRecordTrials )
{
  MonteCarlo::AtomicExcitationElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
                                                 *data_container,
                                                 distribution );

  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;
  double incoming_energy = 1.000000000000e-03;
  double outgoing_energy,scattering_angle_cosine;

  // sample distribution
  distribution->sampleAndRecordTrials( incoming_energy,
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy,
                          1.000000000000e-03- 9.32298000000E-06,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

}


//---------------------------------------------------------------------------//
// Custom setup
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
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
