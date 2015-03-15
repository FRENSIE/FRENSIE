//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brier  Subshell incoherent photon scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
  
// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DirectionHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotonScatteringDistribution>
  basic_subshell_incoherent_distribution;

Teuchos::RCP<MonteCarlo::PhotonScatteringDistribution>
  detailed_subshell_incoherent_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   getSubshell )
{
  Teuchos::RCP<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
    derived_basic_dist = Teuchos::rcp_dynamic_cast<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>( basic_subshell_incoherent_distribution );

  TEST_EQUALITY_CONST( derived_basic_dist->getSubshell(), 
		       MonteCarlo::K_SUBSHELL);

  Teuchos::RCP<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
    derived_detailed_dist = Teuchos::rcp_dynamic_cast<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>( detailed_subshell_incoherent_distribution );
  TEST_EQUALITY_CONST( derived_detailed_dist->getSubshell(),
		       MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the binding energy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   getBindingEnergy )
{
  Teuchos::RCP<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
    derived_basic_dist = Teuchos::rcp_dynamic_cast<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>( basic_subshell_incoherent_distribution );

  TEST_EQUALITY_CONST( derived_basic_dist->getBindingEnergy(), 
		       8.82899999999999935e-02 );

  Teuchos::RCP<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
    derived_detailed_dist = Teuchos::rcp_dynamic_cast<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>( detailed_subshell_incoherent_distribution );
  TEST_EQUALITY_CONST( derived_detailed_dist->getBindingEnergy(),
		       8.82899999999999935e-02 );
}

//---------------------------------------------------------------------------//
// Check that a photon can be scattered incoherently without Doppler broadening
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   scatterPhoton_no_doppler )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_subshell_incoherent_distribution->scatterPhoton( photon,
							 bank,
							 shell_of_interaction);

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top()->getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top()->getEnergy(), 
			  19.50173181484825,
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top()->getZDirection(), 
			  0.9996898054103247, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top()->getYDirection(), 
			  -0.024905681252821114, 
			  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top()->getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a photon can be scattered incoherently with Doppler broadening
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   scatterPhoton_doppler )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // select pz = 0.0
  fake_stream[4] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_subshell_incoherent_distribution->scatterPhoton( photon,
							 bank,
							 shell_of_interaction);

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top()->getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top()->getEnergy(), 
			  19.50173181484825,
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top()->getZDirection(), 
			  0.9996898054103247, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top()->getYDirection(), 
			  -0.024905681252821114, 
			  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top()->getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
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

  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer 
      data_container( test_native_file_name );
    
    // Extract the Compton profile and occupation number for the first subshell
    const std::vector<double>& compton_profile_grid_s1 = 
      data_container.getComptonProfileMomentumGrid( 1 );
    
    const std::vector<double>& compton_profile_s1 = 
      data_container.getComptonProfile( 1 );
    
    const std::vector<double>& occupation_number_grid_s1 = 
      data_container.getOccupationNumberMomentumGrid( 1 );
    
    const std::vector<double>& occupation_number_s1 = 
      data_container.getOccupationNumber( 1 );
    
    // Create the Compton profile and occupation number distributions
    Teuchos::RCP<const Utility::OneDDistribution> compton_profile_s1_dist(
			    new Utility::TabularDistribution<Utility::LinLin>( 
						       compton_profile_grid_s1,
						       compton_profile_s1 ) );

    Teuchos::RCP<const Utility::OneDDistribution> occupation_number_s1_dist(
			    new Utility::TabularDistribution<Utility::LinLin>(
						    occupation_number_grid_s1,
						    occupation_number_s1 ) );

    // Create the subshell incoherent distributions
    basic_subshell_incoherent_distribution.reset(
		new MonteCarlo::SubshellIncoherentPhotonScatteringDistribution(
			  MonteCarlo::convertENDFDesignatorToSubshellEnum( 1 ),
			  data_container.getSubshellBindingEnergy( 1 ),
			  occupation_number_s1_dist ) );

    detailed_subshell_incoherent_distribution.reset(
		new MonteCarlo::SubshellIncoherentPhotonScatteringDistribution(
			  MonteCarlo::convertENDFDesignatorToSubshellEnum( 1 ),
			  data_container.getSubshellBindingEnergy( 1 ),
			  occupation_number_s1_dist,
			  compton_profile_s1_dist ) );
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
// end tstSubshellIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
