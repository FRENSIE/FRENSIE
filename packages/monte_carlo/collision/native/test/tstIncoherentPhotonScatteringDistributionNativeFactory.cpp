//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentPhotonScatteringDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  Incoherent photon scattering distribution native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> data_container;
Teuchos::RCP<const MonteCarlo::IncoherentPhotonScatteringDistribution> 
  distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a Klein-Nishina distribution can be created
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionNativeFactory,
		   createKleinNishinaDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createKleinNishinaDistribution(
							          distribution,
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
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionNativeFactory,
		   createIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createIncoherentDistribution( 
                                                               *data_container,
							       distribution,
							       3.0 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 7.57217551794289268, 1e-15 );
  
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
// Check that an advanced Doppler broadened incoherent dist. can be created
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionNativeFactory,
		   createAdvancedDopplerBroadenedIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createAdvancedDopplerBroadenedIncoherentDistribution( 
							       *data_container,
							       distribution,
							       3.0 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 7.57217551794289268, 1e-12 );

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
  fake_stream[5] = 0.0; // azimuthal_angle = pi
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a subshell incoherent distribution can be created
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionNativeFactory,
		   createSubshellIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createSubshellIncoherentDistribution(
							       *data_container,
							       1,
							       distribution,
							       3.0 );

  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.18204031443868224, 1e-6 );

  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

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

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a Doppler broadened subshell incoherent distribution can be
// created
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistributionNativeFactory,
		   createDopplerBroadenedSubshellIncoherentDistribution )
{
  MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createDopplerBroadenedSubshellIncoherentDistribution(
							       *data_container,
							       1,
							       distribution,
							       3.0 );
  
  // Test distribution properties
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // select pz = 0.0
  fake_stream[4] = 0.0; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction);

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer( 
						     test_native_file_name ) );

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
// end tstIncoherentPhotonScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
