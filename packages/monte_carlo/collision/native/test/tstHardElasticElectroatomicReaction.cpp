//---------------------------------------------------------------------------//
//!
//! \file   tstHardElasticElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  HardElastic electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_HardElasticElectroatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectroatomicReaction> ace_bremsstrahlung_reaction;

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
TEUCHOS_UNIT_TEST( HardElasticElectroatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_bremsstrahlung_reaction->getReactionType(),
		       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( HardElasticElectroatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_bremsstrahlung_reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( HardElasticElectroatomicReaction, getNumberOfEmittedElectrons_ace )
{
  TEST_EQUALITY_CONST( ace_bremsstrahlung_reaction->getNumberOfEmittedElectrons(1e-3),
		       1u );

  TEST_EQUALITY_CONST( ace_bremsstrahlung_reaction->getNumberOfEmittedElectrons(20.0),
		       1u );      
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( HardElasticElectroatomicReaction, getCrossSection_ace )
{
  double cross_section = 
    ace_bremsstrahlung_reaction->getCrossSection( exp(-1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );
  
  cross_section =
    ace_bremsstrahlung_reaction->getCrossSection( exp( -1.364234411496E+01 ) );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section = 
    ace_bremsstrahlung_reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung reaction can be simulated
TEUCHOS_UNIT_TEST( HardElasticElectroatomicReaction, react_ace )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::SubshellType shell_of_interaction;

  ace_bremsstrahlung_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_ASSERT( electron.getZDirection() < 1.0 );
  TEST_ASSERT( bank.empty() );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );
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
  
  Teuchos::ArrayView<const double> raw_bremsstrahlung_cross_section = 
    xss_data_extractor->extractHardElasticCrossSection();
  
  Teuchos::ArrayView<const double>::iterator start = 
    std::find_if( raw_bremsstrahlung_cross_section.begin(),
                  raw_bremsstrahlung_cross_section.end(),
                  notEqualZero );

  Teuchos::ArrayRCP<double> bremsstrahlung_cross_section;
  bremsstrahlung_cross_section.assign( start, raw_bremsstrahlung_cross_section.end() );

  unsigned bremsstrahlung_threshold_index = 
    energy_grid.size() - bremsstrahlung_cross_section.size();

  // Create the form factor
  Teuchos::ArrayView<const double>  jcohe_block = 
    xss_data_extractor->extractJCOHEBlock();

  unsigned form_factor_size = jcohe_block.size()/3;

  Teuchos::Array<double> recoil_momentum_squared( 
                                          jcohe_block( 0, form_factor_size ) );

  Teuchos::Array<double> form_factor_squared(
                         jcohe_block( 2*form_factor_size, form_factor_size ) );

  for( unsigned i = 0; i < form_factor_size; ++i )
  {
    recoil_momentum_squared[i] *= 
      recoil_momentum_squared[i]*1e16; // convert from A^-2 to cm^-2
    
    form_factor_squared[i] *= form_factor_squared[i];
  }
    
  Teuchos::RCP<Utility::OneDDistribution> form_factor(
                             new Utility::TabularDistribution<Utility::LogLog>(
                                                       recoil_momentum_squared,
						       form_factor_squared ) );
  
  // Create the reaction
  ace_bremsstrahlung_reaction.reset(
		new MonteCarlo::HardElasticElectroatomicReaction<Utility::LogLog>(
						      energy_grid,
						      bremsstrahlung_cross_section,
						      bremsstrahlung_threshold_index,
						      form_factor ) );

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
// end tstHardElasticElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
