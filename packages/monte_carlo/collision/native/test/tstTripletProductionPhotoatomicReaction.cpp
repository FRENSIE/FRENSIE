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
  
}

//---------------------------------------------------------------------------//
// Check that the triplet production reaction can be returned
TEUCHOS_UNIT_TEST( TripletProductionPhotoatomicReaction, react )
{
  
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
