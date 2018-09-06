//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomicReactionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  Photoatomic reaction factory using native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<std::vector<double> > energy_grid;
std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher;
std::shared_ptr<const MonteCarlo::PhotoatomicReaction> reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an incoherent reaction without Doppler data can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createIncoherentReaction_no_doppler )
{
  std::vector<std::shared_ptr<const MonteCarlo::PhotoatomicReaction> >
    reactions;

  MonteCarlo::PhotoatomicReactionNativeFactory::createIncoherentReactions(
					       *data_container,
					       energy_grid,
					       grid_searcher,
					       reactions,
					       MonteCarlo::WH_INCOHERENT_MODEL,
					       3.0 );

  // Test the reaction properties
  FRENSIE_CHECK_EQUAL( reactions.size(), 1 );
  FRENSIE_CHECK_EQUAL( reactions[0]->getReactionType(),
		       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions[0]->getThresholdEnergy(),
		       1e-3 );

  // Test that the stored cross section is correct
  double cross_section = reactions[0]->getCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.23509999999967790e+00, 1e-15 );

  cross_section = reactions[0]->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.47834228852720528e+00, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that an incoherent reaction with Doppler data can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createIncoherentReaction_doppler )
{
  std::vector<std::shared_ptr<const MonteCarlo::PhotoatomicReaction> >
    reactions;

  MonteCarlo::PhotoatomicReactionNativeFactory::createIncoherentReactions(
		 *data_container,
		 energy_grid,
		 grid_searcher,
		 reactions,
		 MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		 3.0 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reactions.size(), 1 );
  FRENSIE_CHECK_EQUAL( reactions[0]->getReactionType(),
		       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions[0]->getThresholdEnergy(),
		       0.001 );

  // Test that the stored cross section is correct
  double cross_section = reactions[0]->getCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.23509999999967790e+00, 1e-15 );

  cross_section = reactions[0]->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.47834228852720528e+00, 1e-15 );

  // Test that Doppler broadening is done
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  // Set up the random number stream
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  fake_stream[3] = 0.08; // select L3 shell for collision
  fake_stream[4] = 0.5; // select pz = 0.0
  fake_stream[5] = 0.0; // azimuthal_angle = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  reactions[0]->react( photon, bank, shell_of_interaction );

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
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::L3_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the subshell incoherent reactions w/o Doppler data can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createSubshellIncoherentReactions_no_doppler )
{
  std::vector<std::shared_ptr<const MonteCarlo::PhotoatomicReaction> > reactions;

  MonteCarlo::PhotoatomicReactionNativeFactory::createIncoherentReactions(
					  *data_container,
					  energy_grid,
					  grid_searcher,
					  reactions,
					  MonteCarlo::IMPULSE_INCOHERENT_MODEL,
					  3.0 );

  FRENSIE_CHECK_EQUAL( reactions.size(), 24 );

  // Test the first shell's reaction properties
  FRENSIE_CHECK_EQUAL(reactions.front()->getReactionType(),
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.front()->getThresholdEnergy(),
		       8.82899999999999935e-02 );

  double cross_section = reactions.front()->getCrossSection(
                                                     8.82899999999999935e-02 );

  FRENSIE_CHECK_SMALL( cross_section, 1e-6 );

  cross_section = reactions.front()->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.03100615156834802e-02, 1e-6 );

  // Check the last shell's reaction properties
  FRENSIE_CHECK_EQUAL(reactions.back()->getReactionType(),
		      MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION);
  FRENSIE_CHECK_EQUAL( reactions.back()->getThresholdEnergy(),
		       1e-3 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.198065568410027426, 1e-6 );

  cross_section = reactions.back()->getCrossSection( 20.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0402322921484711687, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the subshell incoherent reactions w/Doppler data can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createSubshellIncoherentReactions_doppler )
{
  std::vector<std::shared_ptr<const MonteCarlo::PhotoatomicReaction> > reactions;

  MonteCarlo::PhotoatomicReactionNativeFactory::createIncoherentReactions(
			  *data_container,
			  energy_grid,
			  grid_searcher,
			  reactions,
			  MonteCarlo::FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL,
			  3.0 );

  FRENSIE_CHECK_EQUAL( reactions.size(), 24 );

  // Test the first shell's reaction properties
  FRENSIE_CHECK_EQUAL(reactions.front()->getReactionType(),
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.front()->getThresholdEnergy(),
		       8.82899999999999935e-02 );

  double cross_section = reactions.front()->getCrossSection(
                                                     8.82899999999999935e-02 );
						     
  FRENSIE_CHECK_SMALL( cross_section, 1e-6 );

  cross_section = reactions.front()->getCrossSection( 20.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0603100048795882984, 1e-9 );

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // select pz = 0.0
  fake_stream[4] = 0.0; // azimuthal_angle = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  reactions.front()->react( photon, bank, shell_of_interaction );

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

  // Check the last shell's reaction properties
  FRENSIE_CHECK_EQUAL(reactions.back()->getReactionType(),
		      MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION);
  FRENSIE_CHECK_EQUAL( reactions.back()->getThresholdEnergy(),
		       1e-3 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.198065568410027426, 1e-6 );

  cross_section = reactions.back()->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0402322921484711687, 1e-9 );

  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  bank.pop();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  reactions.back()->react( photon, bank, shell_of_interaction );

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
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::P3_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a coherent reaction can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createCoherentReaction )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createCoherentReaction(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reaction );

  // Test the reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       1e-3 );

  // Test that the stored cross section is valid
  double cross_section = reaction->getCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = reaction->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );
}

//---------------------------------------------------------------------------//
// Check that a pair production reaction can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createPairProductionReaction )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createPairProductionReaction(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reaction,
							       false );

  // Test the reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       2*Utility::PhysicalConstants::electron_rest_mass_energy );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = reaction->getCrossSection(
                     2*Utility::PhysicalConstants::electron_rest_mass_energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );

  cross_section = reaction->getCrossSection( 20.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 18.5899999999999999, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a triplet production reaction can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionNativeFactory,
                   createTripletProductionReaction )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createTripletProductionReaction(
                                                               *data_container,
                                                               energy_grid,
							       grid_searcher,
							       reaction,
							       false );
  
  // Test the reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       4*Utility::PhysicalConstants::electron_rest_mass_energy );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = reaction->getCrossSection(
                     4*Utility::PhysicalConstants::electron_rest_mass_energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );

  cross_section = reaction->getCrossSection( 20.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.186299999999999993, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a total photoelectric reaction can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createTotalPhotoelectricReaction )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createTotalPhotoelectricReaction(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reaction );

  // Test the reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       1e-3 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = reaction->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the subshell photoelectric reactions can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createSubshellPhotoelectricReactions )
{
  std::vector<std::shared_ptr<const MonteCarlo::PhotoatomicReaction> > reactions;

  MonteCarlo::PhotoatomicReactionNativeFactory::createSubshellPhotoelectricReactions(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reactions );

  FRENSIE_CHECK_EQUAL( reactions.size(), 24 );

  // Test the first shell's reaction properties
  FRENSIE_CHECK_EQUAL(
		   reactions.front()->getReactionType(),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.front()->getThresholdEnergy(),
		       8.82899999999999935e-02 );

  double cross_section = reactions.front()->getCrossSection(
                                                     8.82899999999999935e-02 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.95582145812230942e+03, 1e-15 );

  cross_section = reactions.front()->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.61425467896072372e-02, 1e-15 );

  // Test the last shell's reaction properties
  FRENSIE_CHECK_EQUAL(
		  reactions.back()->getReactionType(),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.back()->getThresholdEnergy(),
		       1e-3 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.38175550850533909e+02, 1e-24 );

  cross_section = reactions.back()->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.03007633456089762e-07, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the heating photoatomic reaction can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createHeatingReaction )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createHeatingReaction(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reaction );

  // Test the reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::HEATING_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       1e-3 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.98732853633727512e-04, 1e-15 );

  cross_section = reaction->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.84633231171998133e+01, 1e-15 );
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
    data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
						     test_native_file_name ) );

    // Extract the common energy grid
    energy_grid.reset( new std::vector<double>( data_container->getPhotonEnergyGrid() ) );

    // Create the hash-based grid searcher
    grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
					     energy_grid,
					     energy_grid->front(),
					     energy_grid->back(),
					     100 ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotoatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
