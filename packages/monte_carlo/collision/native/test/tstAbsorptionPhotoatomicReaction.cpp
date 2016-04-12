//---------------------------------------------------------------------------//
//!
//! \file   tstAbsorptionPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Absorption photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AbsorptionPhotoatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotoatomicReaction> ace_absorption_reaction;

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
TEUCHOS_UNIT_TEST( AbsorptionPhotoatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_absorption_reaction->getReactionType(),
		       MonteCarlo::HEATING_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( AbsorptionPhotoatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_absorption_reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AbsorptionPhotoatomicReaction, 
		   getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST( 
		    ace_absorption_reaction->getNumberOfEmittedPhotons( 1e-3 ),
		    0u );

  TEST_EQUALITY_CONST(
		    ace_absorption_reaction->getNumberOfEmittedPhotons( 20.0 ),
		    0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( AbsorptionPhotoatomicReaction, getCrossSection_ace )
{
  double cross_section = 
    ace_absorption_reaction->getCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 9.916958825662E-07, 1e-12 );

  cross_section = 
    ace_absorption_reaction->getCrossSection( exp( 1.151292546497E+01 ) );
  
  TEST_FLOATING_EQUALITY( cross_section, 9.999864243970E+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be simulated
TEUCHOS_UNIT_TEST( AbsorptionPhotoatomicReaction, react_ace )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_absorption_reaction->react( photon, bank, shell_of_interaction );

  TEST_ASSERT( photon.isGone() );
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
  
  {
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
    
    Teuchos::ArrayView<const double> raw_heating_cross_section = 
      xss_data_extractor->extractLHNMBlock();
    
    Teuchos::ArrayView<const double>::iterator start = 
      std::find_if( raw_heating_cross_section.begin(),
		    raw_heating_cross_section.end(),
		    notEqualZero );

    Teuchos::ArrayRCP<double> heating_cross_section;
    heating_cross_section.assign( start, raw_heating_cross_section.end() );

    // Process the heating cross section
    for( unsigned i = 0; i < heating_cross_section.size(); ++i )
      heating_cross_section[i] = log( heating_cross_section[i] );
    
    unsigned heating_threshold_index = 
      energy_grid.size() - heating_cross_section.size();
    
    // Create the heating reaction
    ace_absorption_reaction.reset(
	       new MonteCarlo::AbsorptionPhotoatomicReaction<Utility::LogLog>(
				  energy_grid,
				  heating_cross_section,
				  heating_threshold_index,
				  MonteCarlo::HEATING_PHOTOATOMIC_REACTION ) );
  }

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
// end tstAbsorptionPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
