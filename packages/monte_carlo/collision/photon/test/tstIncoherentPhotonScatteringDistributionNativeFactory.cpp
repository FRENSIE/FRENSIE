//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentPhotonScatteringDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  Incoherent photon scattering distribution native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<const MonteCarlo::IncoherentPhotonScatteringDistribution>
  distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a Klein-Nishina distribution can be created
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionNativeFactory,
		   createKleinNishinaDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createDistribution(
					       *data_container,
					       distribution,
					       MonteCarlo::KN_INCOHERENT_MODEL,
					       3.0 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.9893440508834e-1, 1e-12 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 9.2395260201544e-2, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic incoherent distribution can be created
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionNativeFactory,
		   createIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createDistribution(
                                               *data_container,
					       distribution,
					       MonteCarlo::WH_INCOHERENT_MODEL,
					       3.0 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 7.57217551794289268, 1e-15 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  fake_stream[3] = 0.2; // select M3 subshell
  fake_stream[4] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::M3_SUBSHELL );
}



//---------------------------------------------------------------------------//
// Check that the Doppler broadened incoherent dist. can be created
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionNativeFactory,
		   createCFPDopplerBroadenedIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createDistribution(
		 *data_container,
		 distribution,
		 MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		 3.0 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 7.57217551794289268, 1e-12 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  fake_stream[3] = 0.005; // select first shell for collision
  fake_stream[4] = 0.5; // select pz = 0.0
  fake_stream[5] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a subshell incoherent distribution can be created
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionNativeFactory,
		   createSubshellIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createDistribution(
					  *data_container,
					  distribution,
					  MonteCarlo::IMPULSE_INCOHERENT_MODEL,
					  3.0,
					  1 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.182031495370433727, 1e-6 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction);

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a Doppler broadened subshell incoherent distribution can be
// created
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionNativeFactory,
		   createDopplerBroadenedSubshellIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createDistribution(
			  *data_container,
			  distribution,
			  MonteCarlo::FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL,
			  3.0,
			  1 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // select pz = 0.0
  fake_stream[4] = 0.0; // azimuthal_angle = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction);

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );
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
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
						     test_native_file_name ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstIncoherentPhotonScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
