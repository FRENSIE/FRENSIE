//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectroatomicReaction> ace_excitation_reaction;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationElectroatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getReactionType(),
		       MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationElectroatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getThresholdEnergy(),
                       1.000000000000E-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationElectroatomicReaction, getNumberOfEmittedElectrons_ace )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedElectrons(1e-3),
		       0u );

  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedElectrons(20.0),
		       0u );      
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationElectroatomicReaction, getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedPhotons(1e-3),
		       0u );

  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedPhotons(20.0),
		       0u );      
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationElectroatomicReaction, getCrossSection_ace )
{
  double cross_section = 
    ace_excitation_reaction->getCrossSection( 9.000000000000E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );
  
  cross_section =
    ace_excitation_reaction->getCrossSection( 4.000000000000E-04 );
  
  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = 
    ace_excitation_reaction->getCrossSection( 2.000000000000E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation reaction can be simulated
TEUCHOS_UNIT_TEST( AtomicExcitationElectroatomicReaction, react_ace )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.000000000000e-03 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  double final_energy = (electron.getEnergy() - 9.32298000000E-06);

  ace_excitation_reaction->react( electron, bank, shell_of_interaction );

  TEST_FLOATING_EQUALITY( electron.getEnergy(), final_energy, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
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
  
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  
  // Extract the energy grid and cross section
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );
  
  Teuchos::ArrayView<const double> raw_excitation_cross_section = 
    xss_data_extractor->extractExcitationCrossSection();
  
  Teuchos::ArrayView<const double>::iterator start = 
    std::find_if( raw_excitation_cross_section.begin(),
                  raw_excitation_cross_section.end(),
                  notEqualZero );

  Teuchos::ArrayRCP<double> excitation_cross_section;
  excitation_cross_section.assign( start, raw_excitation_cross_section.end() );

  unsigned excitation_threshold_index = 
    energy_grid.size() - excitation_cross_section.size();

  // Extract the atomic excitation information data block (EXCIT)
  Teuchos::ArrayView<const double> excit_block(
				      xss_data_extractor->extractEXCITBlock() );
  
  // Extract the number of tabulated energies
  int size = excit_block.size()/2;

  // Extract the energy grid for atomic excitation energy loss
  Teuchos::Array<double> excitation_energy_grid(excit_block(0,size));

  // Extract the energy loss for atomic excitation
  Teuchos::Array<double> excitation_energy_loss(excit_block(size,size));

  // Create the energy loss distributions
  Teuchos::RCP<Utility::OneDDistribution> energy_loss_function;
  
  energy_loss_function.reset( 
  new Utility::TabularDistribution<Utility::LinLin>( excitation_energy_grid,
		                                     excitation_energy_loss ) );

  Teuchos::RCP<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
                      excitation_energy_loss_distribution;

  excitation_energy_loss_distribution.reset( 
    new MonteCarlo::AtomicExcitationElectronScatteringDistribution( 
                      energy_loss_function ) );

  
  
  // Create the reaction
  ace_excitation_reaction.reset(
    new MonteCarlo::AtomicExcitationElectroatomicReaction<Utility::LinLin>(
				      energy_grid,
				      excitation_cross_section,
				      excitation_threshold_index,
				      excitation_energy_loss_distribution ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

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
// end tstAtomicExcitationElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
