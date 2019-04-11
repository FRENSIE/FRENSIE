//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentAdjointPhotonScatteringDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  Incoherent adjoint photon scattering distribution native factory
//!         unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::AdjointElectronPhotonRelaxationDataContainer>
  data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a Klein-Nishina distribution can be created
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistributionNativeFactory,
                   createKleinNishinaDistribution )
{
  std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    distribution;

  MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                            *data_container,
                            distribution,
                            MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL,
                            MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                            20.0 );

  // Test the distribution
  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK_EQUAL( distribution->getMaxEnergy(), 20.0 );
  
  // Evaluate the distribution at the min energy (E = 1e-3 MeV)
  double dist_value = distribution->evaluate( 1e-3, -1.0 );
 
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.498938241600864918, 1e-15 );

  dist_value = distribution->evaluate( 1e-3, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );

  // Evaluate the distribution at E = 1.0 MeV
  dist_value = distribution->evaluate( 1.0, 0.5145510353765 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.818399835538855, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.9 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4634138962142929, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );

  // Evaluate the distribution at the max energy (E = 20.0 MeV)
  dist_value = distribution->evaluate( 20.0, 1.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a Waller-Hartree incoherent distribution can be created
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistributionNativeFactory,
                   createWallerHartreeDistribution )
{
  std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    distribution;

  MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                            *data_container,
                            distribution,
                            MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                            MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                            20.0 );
  
  // Test the distribution
  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK_EQUAL( distribution->getMaxEnergy(), 20.0 );
  
  // Evaluate the distribution at the min energy (E = 1e-3 MeV)
  double dist_value = distribution->evaluate( 1e-3, -1.0 );
 
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.853837503637913553, 1e-15 );

  dist_value = distribution->evaluate( 1e-3, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Evaluate the distribution at E = 1.0 MeV
  dist_value = distribution->evaluate( 1.0, 0.5145510353765 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 67.4575976975439602, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.9 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 6.48779098171434399, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Evaluate the distribution at the max energy (E = 20.0 MeV)
  dist_value = distribution->evaluate( 20.0, 1.0 );
  
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a subshell incoherent distribution can be created
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistributionNativeFactory,
                   createSubshellDistribution_base )
{
  std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    distribution;

  MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                            *data_container,
                            distribution,
                            MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL,
                            MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                            20.0,
                            Data::K_SUBSHELL );
  
  // Test the distribution
  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK_EQUAL( distribution->getMaxEnergy(), 20.0 );
  
  // Evaluate the distribution below the min energy (E = 1e-3 MeV)
  double dist_value = distribution->evaluate( 1e-3, -1.0 );
    
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate( 1e-3, 1.0 );
  
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Evaluate the distribution at the min energy (E = 1.8285e-3 MeV)
  dist_value = distribution->evaluate( 0.0018155071938000074, -1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate( 0.0018155071938000074, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Evaluate the distribution at E = 1.0 MeV
  dist_value = distribution->evaluate( 1.0, 0.5145510353765 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 9.636799671077708851, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.9 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.9267587548171207779, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  // Evaluate the distribution at the max energy (E = 20.0 MeV)
  dist_value = distribution->evaluate( 20.0, 1.0 );
  
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Check that a sample can be made
  std::vector<double> fake_stream( 26 );
  
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept x
  fake_stream[6] = 0.32; // reject mu
  fake_stream[7] = 0.15; // branch 1
  fake_stream[8] = 0.22986680137273696; // select x = 0.95
  fake_stream[9] = 0.245; // accept x
  fake_stream[10] = 0.31; // accept mu

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle_cosine;
  
  distribution->sample(
                    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
                    outgoing_energy,
                    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a subshell incoherent distribution can be created
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistributionNativeFactory,
                   createSubshellDistribution )
{
  std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>
    distribution;

  MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
                            *data_container,
                            distribution,
                            MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL,
                            MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                            20.0,
                            Data::K_SUBSHELL );
  
  // Test the distribution
  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK_EQUAL( distribution->getMaxEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( distribution->getSubshell(), Data::K_SUBSHELL );
  FRENSIE_CHECK_EQUAL( distribution->getSubshellOccupancy(), 2 );
  FRENSIE_CHECK_EQUAL( distribution->getSubshellBindingEnergy(), 1.8285e-3 );
  
  // Evaluate the distribution at the min energy (E = 1e-3 MeV)
  double dist_value = distribution->evaluate( 1e-3, -1.0 );
    
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate( 1e-3, 1.0 );
  
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Evaluate the distribution at the min energy (E = 1.8285e-3 MeV)
  dist_value = distribution->evaluate( 0.0018155071938000074, -1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate( 0.0018155071938000074, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Evaluate the distribution at E = 1.0 MeV
  dist_value = distribution->evaluate( 1.0, 0.5145510353765 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 9.636799671077708851, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.9 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.9267587548171207779, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  // Evaluate the distribution at the max energy (E = 20.0 MeV)
  dist_value = distribution->evaluate( 20.0, 1.0 );
  
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Check that a sample can be made
  std::vector<double> fake_stream( 26 );
  
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept x
  fake_stream[6] = 0.32; // reject mu
  fake_stream[7] = 0.15; // branch 1
  fake_stream[8] = 0.22986680137273696; // select x = 0.95
  fake_stream[9] = 0.245; // accept x
  fake_stream[10] = 0.31; // accept mu

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle_cosine;
  
  distribution->sample(
                    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
                    outgoing_energy,
                    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a Doppler broadened subshell incoherent dist. can be created
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistributionNativeFactory,
                   createDopplerBroadenedSubshellDistribution_base )
{
  std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    distribution;

  MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                            *data_container,
                            distribution,
                            MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL,
                            MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                            20.0,
                            Data::K_SUBSHELL );
  
  // Test the distribution
  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK_EQUAL( distribution->getMaxEnergy(), 20.0 );
  
  // Evaluate the distribution at the min energy (E = 1e-3 MeV)
  double dist_value = distribution->evaluate( 1e-3, -1.0 );
    
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 7.16614513178088125e-05, 1e-15 );

  dist_value = distribution->evaluate( 1e-3, 1.0 );
  
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Evaluate the distribution at E = 1.0 MeV
  dist_value = distribution->evaluate( 1.0, 0.5145510353765 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.8183422986505029, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.9 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.926433751496189117, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Evaluate the distribution at the max energy (E = 20.0 MeV)
  dist_value = distribution->evaluate( 20.0, 1.0 );
  
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Check that a sample can be made
  std::vector<double> fake_stream( 30 );
  
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept x
  fake_stream[6] = 0.32; // reject mu
  fake_stream[7] = 0.15; // branch 1
  fake_stream[8] = 0.22986680137273696; // select x = 0.95
  fake_stream[9] = 0.245; // accept x
  fake_stream[10] = 0.31; // accept mu
  fake_stream[11] = 0.5; // pz = -0.04935286011127609

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle_cosine;

  distribution->sample(
                    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
                    outgoing_energy,
                    scattering_angle_cosine );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.057653411316070699, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a Doppler broadened subshell incoherent dist. can be created
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistributionNativeFactory,
                   createDopplerBroadenedSubshellDistribution )
{
  std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    distribution;

  MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                            *data_container,
                            distribution,
                            MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL,
                            MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                            20.0,
                            Data::K_SUBSHELL );
  
  // Test the distribution
  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK_EQUAL( distribution->getMaxEnergy(), 20.0 );
  
  // Evaluate the distribution at the min energy (E = 1e-3 MeV)
  double dist_value = distribution->evaluate( 1e-3, -1.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 7.16614513178088125e-05, 1e-15 );

  dist_value = distribution->evaluate( 1e-3, 1.0 );
  
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Evaluate the distribution at E = 1.0 MeV
  dist_value = distribution->evaluate( 1.0, 0.5145510353765 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.8183422986505029, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.9 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.926433751496189117, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Evaluate the distribution at the max energy (E = 20.0 MeV)
  dist_value = distribution->evaluate( 20.0, 1.0 );
  
  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  // Check that a sample can be made
  std::vector<double> fake_stream( 30 );
  
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept x
  fake_stream[6] = 0.32; // reject mu
  fake_stream[7] = 0.15; // branch 1
  fake_stream[8] = 0.22986680137273696; // select x = 0.95
  fake_stream[9] = 0.245; // accept x
  fake_stream[10] = 0.31; // accept mu
  fake_stream[11] = 0.5; // pz = -0.04935286011127609

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle_cosine;

  distribution->sample(
                    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
                    outgoing_energy,
                    scattering_angle_cosine );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.057653411316070699, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a Doppler broadened subshell incoherent dist. can be created
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistributionNativeFactory,
                   createSubshellDistribution_exception_handling )
{
  std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>
    distribution;

  FRENSIE_CHECK_THROW( MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
                            *data_container,
                            distribution,
                            MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL,
                            MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                            20.0,
                            Data::K_SUBSHELL ),
                       std::logic_error );

  FRENSIE_CHECK_THROW( MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
                            *data_container,
                            distribution,
                            MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                            MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                            20.0,
                            Data::K_SUBSHELL ),
                       std::logic_error );

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
// end tstIncoherentAdjointPhotonScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
