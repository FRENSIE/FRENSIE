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

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>
  distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( SubshellDopplerBroadenedPhotonEnergyDistribution,
		   sample )
{
  double incoming_energy = 20.0, scattering_angle_cosine = 0.0;
  double outgoing_energy;
  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // select pz = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( incoming_energy,
			scattering_angle_cosine,
			outgoing_energy,
			shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.4982681851517501, 1e-12 );
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
  {
    Data::ElectronPhotonRelaxationDataContainer data_container( test_native_file_name );

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
    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum> > raw_compton_profile(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
                                                       compton_profile_grid_s1,
						       compton_profile_s1 ) );

    std::shared_ptr<MonteCarlo::ComptonProfile> compton_profile_s1_dist(
           new MonteCarlo::StandardComptonProfile<Utility::Units::MeCMomentum>(
                                                       raw_compton_profile ) );

    // Create the Doppler broadened energy distribution
    distribution.reset( new MonteCarlo::StandardSubshellDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::FullComptonProfilePolicy>(
		    Data::convertENDFDesignatorToSubshellEnum( 1 ),
		    data_container.getSubshellOccupancy( 1 ),
		    data_container.getSubshellBindingEnergy( 1 ),
		    compton_profile_s1_dist ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSubshellDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
