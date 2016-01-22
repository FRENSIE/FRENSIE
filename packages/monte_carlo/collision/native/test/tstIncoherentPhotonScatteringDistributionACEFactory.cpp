//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Incoherent photon scattering distribution ACE factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::RCP<const MonteCarlo::IncoherentPhotonScatteringDistribution> 
  distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a Klein-Nishina distribution can be created
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
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
  
  TEST_FLOATING_EQUALITY( dist_value, 4.9893440508834e-1, 1e-12 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 9.2395260201544e-2, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic incoherent distribution can be created
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
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
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );
  
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

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

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::M3_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the Doppler broadened incoherent distribution can be created
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
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
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

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
  
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the Doppler broadened incoherent distribution can be created
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
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
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

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

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the Doppler broadened incoherent distribution can be created
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
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
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

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
  
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a basic Doppler broadened incoherent distribution can be created
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionACEFactory,
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
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

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

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
    xss_data_extractor.reset( new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}
		   
//---------------------------------------------------------------------------//
// end tstIncoherentPhotonScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
