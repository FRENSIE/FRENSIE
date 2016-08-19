//---------------------------------------------------------------------------//
//!
//! \file   tstTripletProductionPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Triplet production photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_TripletProductionPhotoatomicReaction.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotoatomicReaction> basic_tp_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( TripletProductionPhotoatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( basic_tp_reaction->getReactionType(),
                       MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( TripletProductionPhotoatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( basic_tp_reaction->getThresholdEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the reaction can be returned
TEUCHOS_UNIT_TEST( TripletProductionPhotoatomicReaction,
                   getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( basic_tp_reaction->getNumberOfEmittedPhotons( 1e-4 ),
                       0u );

  TEST_EQUALITY_CONST( basic_tp_reaction->getNumberOfEmittedPhotons(
                                     basic_tp_reaction->getThresholdEnergy() ),
                       2u );

  TEST_EQUALITY_CONST( basic_tp_reaction->getNumberOfEmittedPhotons( 20.0 ),
                       2u );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( TripletProductionPhotoatomicReaction,
                   getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( basic_tp_reaction->getNumberOfEmittedElectrons( 1e-4 ),
                       0u );

  TEST_EQUALITY_CONST( basic_tp_reaction->getNumberOfEmittedElectrons(
                                     basic_tp_reaction->getThresholdEnergy() ),
                       2u );

  TEST_EQUALITY_CONST( basic_tp_reaction->getNumberOfEmittedElectrons( 20.0 ),
                       2u );
}

//---------------------------------------------------------------------------//
// Check that the triplet production cross section can be returned
TEUCHOS_UNIT_TEST( TripletProductionPhotoatomicReaction, getCrossSection )
{
  double cross_section = basic_tp_reaction->getCrossSection( 1e-3 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = basic_tp_reaction->getCrossSection(
                                     basic_tp_reaction->getThresholdEnergy() );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = basic_tp_reaction->getCrossSection( 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.186299999999999993, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the triplet production reaction can be returned
TEUCHOS_UNIT_TEST( TripletProductionPhotoatomicReaction, react )
{
  Teuchos::RCP<MonteCarlo::PhotonState> photon( new MonteCarlo::PhotonState(0));
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setEnergy( 3.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType subshell;

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_tp_reaction->react( *photon, bank, subshell );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Check the bank size
  TEST_EQUALITY_CONST( bank.size(), 3 );

  // Check the subshell
  TEST_EQUALITY_CONST( subshell, Data::UNKNOWN_SUBSHELL );

  // Check the initial photon (which is now an annihilation photon)
  TEST_EQUALITY_CONST( photon->getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  UTILITY_TEST_FLOATING_EQUALITY( photon->getZDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon->getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon->getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( photon->getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( photon->getGenerationNumber(), 1 );

  // Check the first generated electron
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY_CONST( bank.top().getZDirection(), 1.0 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 0.6593340599133334, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( bank.top().getGenerationNumber(), 1 );

  bank.pop();

  // Check the second generated electron
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY_CONST( bank.top().getZDirection(), 1.0 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 0.6593340599133334, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( bank.top().getGenerationNumber(), 1 );
  
  bank.pop();

  // Check the second annihilation photon
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( bank.top().getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( bank.top().getGenerationNumber(), 1 );
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

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer 
      data_container( test_native_file_name );

    // Extract the photon energy grid
    Teuchos::ArrayRCP<double> photon_energy_grid;
    photon_energy_grid.assign( data_container.getPhotonEnergyGrid().begin(),
			       data_container.getPhotonEnergyGrid().end() );

    // Extract the triplet production cross section
    Teuchos::ArrayRCP<double> triplet_production_cs;
    triplet_production_cs.assign(
                     data_container.getTripletProductionCrossSection().begin(),
                     data_container.getTripletProductionCrossSection().end() );

    unsigned threshold_index =
      data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

    basic_tp_reaction.reset(
      new MonteCarlo::TripletProductionPhotoatomicReaction<Utility::LinLin,false>(
                                                         photon_energy_grid,
                                                         triplet_production_cs,
                                                         threshold_index,
                                                         false ) );
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
// end tstTripletProductionPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
