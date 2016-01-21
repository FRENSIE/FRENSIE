//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  Subshell Doppler broadened photon energy distribution
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
#include <memory>
  
// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>
  distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( SubshellDopplerBroadenedPhotonEnergyDistribution,
		   sample )
{
  double incoming_energy = 20.0, scattering_angle_cosine = 0.0;
  double outgoing_energy;
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // select pz = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( incoming_energy,
			scattering_angle_cosine,
			outgoing_energy,
			shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();
  
  TEST_FLOATING_EQUALITY( outgoing_energy, 0.4982681851517501, 1e-12 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom main funciton
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
    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum> > raw_compton_profile(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
                                                       compton_profile_grid_s1,
						       compton_profile_s1 ) );

    std::shared_ptr<MonteCarlo::ComptonProfile> compton_profile_s1_dist( 
           new MonteCarlo::StandardComptonProfile<Utility::Units::MeCMomentum>(
                                                       raw_compton_profile ) );
   
    // Create the Doppler broadened energy distribution
    distribution.reset( new MonteCarlo::StandardSubshellDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::FullComptonProfilePolicy>(
		    MonteCarlo::convertENDFDesignatorToSubshellEnum( 1 ),
		    data_container.getSubshellOccupancy( 1 ),
		    data_container.getSubshellBindingEnergy( 1 ),
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
// end tstSubshellDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
