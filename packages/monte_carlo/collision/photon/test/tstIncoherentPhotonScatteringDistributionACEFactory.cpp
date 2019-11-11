//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Incoherent photon scattering distribution ACE factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor;
std::shared_ptr<const MonteCarlo::IncoherentPhotonScatteringDistribution>
  distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a Klein-Nishina distribution can be created
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
		   createKleinNishinaDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionACEFactory::createDistribution(
					       *xss_data_extractor,
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
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
		   createIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionACEFactory::createDistribution(
					       *xss_data_extractor,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

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
// Check that the Doppler broadened incoherent distribution can be created
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
		   createDHPDopplerBroadenedHybridIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionACEFactory::createDistribution(
		 *xss_data_extractor,
		 distribution,
		 MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		 3.0 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  fake_stream[3] = 0.005; // select first shell for collision - old
  fake_stream[4] = 0.005; // select first shell for collision - endf
  fake_stream[5] = 6.427713151861e-01; // select pz = 0.291894102792
  fake_stream[6] = 0.25; // select energy loss
  fake_stream[7] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the Doppler broadened incoherent distribution can be created
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
		   createDFPDopplerBroadenedHybridIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionACEFactory::createDistribution(
		 *xss_data_extractor,
		 distribution,
		 MonteCarlo::DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		 3.0 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  fake_stream[3] = 0.005; // select first shell for collision - old
  fake_stream[4] = 0.005; // select first shell for collision - endf
  fake_stream[5] = 0.5; // select pz = 0.0
  fake_stream[6] = 0.5; // azimuthal_angle = pi

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
// Check that the Doppler broadened incoherent distribution can be created
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
		   createCHPDopplerBroadenedHybridIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionACEFactory::createDistribution(
		 *xss_data_extractor,
		 distribution,
		 MonteCarlo::COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		 3.0 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  fake_stream[3] = 0.005; // select first shell for collision
  fake_stream[4] = 6.427713151861e-01; // select pz = 0.291894102792
  fake_stream[5] = 0.25; // select energy loss
  fake_stream[6] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a basic Doppler broadened incoherent distribution can be created
FRENSIE_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
		   createCFPDopplerBroadenedHybridIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionACEFactory::createDistribution(
		 *xss_data_extractor,
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

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

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
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start_line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Create a file handler and data extractor
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.12p",
						  test_ace_file_start_line ) );
    
    xss_data_extractor.reset( new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstIncoherentPhotonScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
