//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellIncoherentPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Subshell incoherent photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotoatomicReaction>
  basic_subshell_incoherent_reaction;

std::shared_ptr<MonteCarlo::PhotoatomicReaction>
  detailed_subshell_incoherent_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentPhotoatomicReaction,
		   getNumberOfEmittedPhotons )
{
  FRENSIE_CHECK_EQUAL(
     basic_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 1e-3 ),
     0u );

  FRENSIE_CHECK_EQUAL(
      basic_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 8.82e-2 ),
      0u );

  FRENSIE_CHECK_EQUAL(
      basic_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 8.83e-2 ),
      1u );

  FRENSIE_CHECK_EQUAL(
	 basic_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 20.0 ),
	 1u );

  FRENSIE_CHECK_EQUAL(
  detailed_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 1e-3 ),
  0u );

  FRENSIE_CHECK_EQUAL(
   detailed_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 8.82e-2 ),
   0u );

  FRENSIE_CHECK_EQUAL(
   detailed_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 8.83e-2 ),
   1u );

  FRENSIE_CHECK_EQUAL(
      detailed_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 20.0 ),
      1u );
}

//---------------------------------------------------------------------------//
// Check that the subshell can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentPhotoatomicReaction,
		   getNumberOfEmittedElectrons )
{
  FRENSIE_CHECK_EQUAL(
     basic_subshell_incoherent_reaction->getNumberOfEmittedElectrons( 1e-3 ),
     0u );

  FRENSIE_CHECK_EQUAL(
      basic_subshell_incoherent_reaction->getNumberOfEmittedElectrons( 8.82e-2 ),
      0u );

  FRENSIE_CHECK_EQUAL(
      basic_subshell_incoherent_reaction->getNumberOfEmittedElectrons( 8.83e-2 ),
      1u );

  FRENSIE_CHECK_EQUAL(
	 basic_subshell_incoherent_reaction->getNumberOfEmittedElectrons( 20.0 ),
	 1u );

  FRENSIE_CHECK_EQUAL(
  detailed_subshell_incoherent_reaction->getNumberOfEmittedElectrons( 1e-3 ),
  0u );

  FRENSIE_CHECK_EQUAL(
   detailed_subshell_incoherent_reaction->getNumberOfEmittedElectrons( 8.82e-2 ),
   0u );

  FRENSIE_CHECK_EQUAL(
   detailed_subshell_incoherent_reaction->getNumberOfEmittedElectrons( 8.83e-2 ),
   1u );

  FRENSIE_CHECK_EQUAL(
      detailed_subshell_incoherent_reaction->getNumberOfEmittedElectrons( 20.0 ),
      1u );
}

//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( basic_subshell_incoherent_reaction->getReactionType(),
		       MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION);

  FRENSIE_CHECK_EQUAL(detailed_subshell_incoherent_reaction->getReactionType(),
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION);
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
		      basic_subshell_incoherent_reaction->getThresholdEnergy(),
		      8.82899999999999935e-02,
		      1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		   detailed_subshell_incoherent_reaction->getThresholdEnergy(),
		   8.82899999999999935e-02,
		   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, getCrossSection )
{
  double cross_section =
    basic_subshell_incoherent_reaction->getCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    basic_subshell_incoherent_reaction->getCrossSection( 8.82e-2 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    basic_subshell_incoherent_reaction->getCrossSection( 8.82899999999999935e-02 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    basic_subshell_incoherent_reaction->getCrossSection( 8.82900086220703151e-02 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.25526576584511952e-09, 1e-6 );

  cross_section =
    basic_subshell_incoherent_reaction->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.03100615156834802e-02, 1e-6 );

  cross_section =
    detailed_subshell_incoherent_reaction->getCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    detailed_subshell_incoherent_reaction->getCrossSection( 8.82e-2 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    detailed_subshell_incoherent_reaction->getCrossSection( 8.82899999999999935e-02 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    detailed_subshell_incoherent_reaction->getCrossSection( 8.82900086220703151e-02 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.25526576584511952e-09, 1e-6 );

  cross_section =
    detailed_subshell_incoherent_reaction->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.03100615156834802e-02, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the interaction subshell can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, getSubshell )
{
  typedef MonteCarlo::SubshellIncoherentPhotoatomicReaction<Utility::LinLin,false> Reaction;

  std::shared_ptr<Reaction> derived_basic_reaction =
    std::dynamic_pointer_cast<Reaction>( basic_subshell_incoherent_reaction );

  FRENSIE_CHECK_EQUAL( derived_basic_reaction->getSubshell(),
		       Data::K_SUBSHELL );

  std::shared_ptr<Reaction> derived_detailed_reaction =
    std::dynamic_pointer_cast<Reaction>(detailed_subshell_incoherent_reaction);

  FRENSIE_CHECK_EQUAL( derived_basic_reaction->getSubshell(),
		       Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energy can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentPhotoatomicReaction,
		   getSubshellBindingEnergy )
{
  typedef MonteCarlo::SubshellIncoherentPhotoatomicReaction<Utility::LinLin,false> Reaction;

  std::shared_ptr<Reaction> derived_basic_reaction =
    std::dynamic_pointer_cast<Reaction>( basic_subshell_incoherent_reaction );

  FRENSIE_CHECK_EQUAL( derived_basic_reaction->getSubshellBindingEnergy(),
		       8.82899999999999935e-02 );

  std::shared_ptr<Reaction> derived_detailed_reaction =
    std::dynamic_pointer_cast<Reaction>(detailed_subshell_incoherent_reaction);

  FRENSIE_CHECK_EQUAL( derived_basic_reaction->getSubshellBindingEnergy(),
		       8.82899999999999935e-02 );
}

//---------------------------------------------------------------------------//
// Check that the basic incoherent reaction can be simulated
FRENSIE_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, react_basic )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_subshell_incoherent_reaction->react( photon,
					     bank,
					     shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
			  19.50173181484825,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(),
			  0.9996898054103247,
			  1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(),
                                   0.024905681252821114,
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the detailed incoherent reaction can be simulated
FRENSIE_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, react_detailed )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // select pz = 0.0
  fake_stream[4] = 0.0; // azimuthal_angle = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  detailed_subshell_incoherent_reaction->react( photon,
						bank,
						shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
			  19.50173181484825,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(),
			  0.9996898054103247,
			  1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(),
                                   -0.024905681252821114,
                                   1e-12 );
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
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( test_native_file_name );

    // Extract the photon energy grid
    std::shared_ptr<std::vector<double> > photon_energy_grid(
             new std::vector<double>( data_container.getPhotonEnergyGrid() ) );

    // Extract the subshell impulse approx incoherent cross section
    std::shared_ptr<std::vector<double> > subshell_incoherent_cs(
       new std::vector<double>( data_container.getImpulseApproxSubshellIncoherentCrossSection(1) ) );

    size_t threshold_index =
      data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1);

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

    std::shared_ptr<const Utility::UnivariateDistribution> occupation_number_s1_dist(
			    new Utility::TabularDistribution<Utility::LinLin>(
						    occupation_number_grid_s1,
						    occupation_number_s1 ) );

    // Create the subshell incoherent distributions
    std::shared_ptr<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
      basic_distribution( new MonteCarlo::SubshellIncoherentPhotonScatteringDistribution(
			  Data::convertENDFDesignatorToSubshellEnum( 1 ),
			  data_container.getSubshellOccupancy( 1 ),
			  data_container.getSubshellBindingEnergy( 1 ),
			  occupation_number_s1_dist,
			  3.0 ) );

    std::shared_ptr<const MonteCarlo::SubshellDopplerBroadenedPhotonEnergyDistribution>
      doppler_dist( new MonteCarlo::StandardSubshellDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::FullComptonProfilePolicy>(
		    Data::convertENDFDesignatorToSubshellEnum( 1 ),
		    data_container.getSubshellOccupancy( 1 ),
		    data_container.getSubshellBindingEnergy( 1 ),
		    compton_profile_s1_dist ) );

    std::shared_ptr<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
      detailed_distribution( new MonteCarlo::DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution(
						     doppler_dist,
						     occupation_number_s1_dist,
						     3.0 ) );

    // Create the subshell incoherent reaction
    basic_subshell_incoherent_reaction.reset(
         new MonteCarlo::SubshellIncoherentPhotoatomicReaction<Utility::LinLin,false>(
			                                photon_energy_grid,
			                                subshell_incoherent_cs,
							threshold_index,
							basic_distribution ) );

    detailed_subshell_incoherent_reaction.reset(
	 new MonteCarlo::SubshellIncoherentPhotoatomicReaction<Utility::LinLin,false>(
			  photon_energy_grid,
			  subshell_incoherent_cs,
			  threshold_index,
			  detailed_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSubshellIncoherentPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
