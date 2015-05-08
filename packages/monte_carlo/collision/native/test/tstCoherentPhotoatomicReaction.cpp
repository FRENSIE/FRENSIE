//---------------------------------------------------------------------------//
//!
//! \file   tstCoherentPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Coherent photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_EfficientCoherentScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotoatomicReaction> ace_coherent_reaction;

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
TEUCHOS_UNIT_TEST( CoherentPhotoatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_coherent_reaction->getReactionType(),
		       MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( CoherentPhotoatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_coherent_reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( CoherentPhotoatomicReaction, getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST( ace_coherent_reaction->getNumberOfEmittedPhotons(1e-3),
		       1u );

  TEST_EQUALITY_CONST( ace_coherent_reaction->getNumberOfEmittedPhotons(20.0),
		       1u );      
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( CoherentPhotoatomicReaction, getCrossSection_ace )
{
  double cross_section = 
    ace_coherent_reaction->getCrossSection( exp(-1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );
  
  cross_section =
    ace_coherent_reaction->getCrossSection( exp( -1.364234411496E+01 ) );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section = 
    ace_coherent_reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coherent reaction can be simulated
TEUCHOS_UNIT_TEST( CoherentPhotoatomicReaction, react_ace )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::SubshellType shell_of_interaction;

  ace_coherent_reaction->react( photon, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( photon.getEnergy(), 20.0 );
  TEST_ASSERT( photon.getZDirection() < 1.0 );
  TEST_EQUALITY_CONST( photon.getCollisionNumber(), 1 );
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
  energy_grid.deepCopy( xss_data_extractor->extractPhotonEnergyGrid() );
  
  Teuchos::ArrayView<const double> raw_coherent_cross_section = 
    xss_data_extractor->extractCoherentCrossSection();
  
  Teuchos::ArrayView<const double>::iterator start = 
    std::find_if( raw_coherent_cross_section.begin(),
                  raw_coherent_cross_section.end(),
                  notEqualZero );

  Teuchos::ArrayRCP<double> coherent_cross_section;
  coherent_cross_section.assign( start, raw_coherent_cross_section.end() );

  unsigned coherent_threshold_index = 
    energy_grid.size() - coherent_cross_section.size();

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
    
  Teuchos::RCP<Utility::TabularOneDDistribution> form_factor(
                             new Utility::TabularDistribution<Utility::LogLog>(
                                                       recoil_momentum_squared,
						       form_factor_squared ) );

  // Create the coherent scattering distribution
  Teuchos::RCP<const MonteCarlo::CoherentScatteringDistribution> distribution(
		       new MonteCarlo::EfficientCoherentScatteringDistribution(
							       form_factor ) );
  
  // Create the reaction
  ace_coherent_reaction.reset(
		new MonteCarlo::CoherentPhotoatomicReaction<Utility::LogLog>(
						      energy_grid,
						      coherent_cross_section,
						      coherent_threshold_index,
						      distribution ) );

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
// end tstCoherentPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
