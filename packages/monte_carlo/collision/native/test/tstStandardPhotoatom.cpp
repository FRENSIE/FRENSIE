//---------------------------------------------------------------------------//
//!
//! \file   tstStandardPhotoatom.cpp
//! \author Alex Robinson
//! \brief  Standard photoatom unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardPhotoatom.hpp"
#include "MonteCarlo_PairProductionPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::Photoatom> ace_photoatom;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be set
TEUCHOS_UNIT_TEST( Photoatom, setAbsorptionReactionTypes )
{
  const boost::unordered_set<MonteCarlo::PhotoatomicReactionType>&
    absorption_types = MonteCarlo::Photoatom::getAbsorptionReactionTypes();

  TEST_ASSERT( absorption_types.count( 
		      MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
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

    // Create the pair production and photoelectric effect cross sections
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( xss_data_extractor->extractPhotonEnergyGrid() );
    
    Teuchos::ArrayView<const double> raw_pp_cross_section = 
      xss_data_extractor->extractPairProductionCrossSection();
    
    Teuchos::ArrayView<const double>::iterator start = 
      std::find_if( raw_pp_cross_section.begin(),
		    raw_pp_cross_section.end(),
		    notEqualZero );
  
    Teuchos::ArrayRCP<double> pp_cross_section;
    pp_cross_section.assign( start, raw_pp_cross_section.end() );
    
    unsigned pp_threshold_index = 
      energy_grid.size() - pp_cross_section.size();
    
    Teuchos::RCP<MonteCarlo::PhotoatomicReaction> pp_reaction(
	    new MonteCarlo::PairProductionPhotoatomicReaction<Utility::LogLog>(
							energy_grid,
							pp_cross_section,
							pp_threshold_index ) );
  
    Teuchos::ArrayView<const double> raw_pe_cross_section = 
      xss_data_extractor->extractPhotoelectricCrossSection();

    start = std::find_if( raw_pe_cross_section.begin(),
			  raw_pe_cross_section.end(),
			  notEqualZero );

    Teuchos::ArrayRCP<double> pe_cross_section;
    pe_cross_section.assign( start, raw_pe_cross_section.end() );
    
    unsigned pe_threshold_index = 
      energy_grid.size() - pe_cross_section.size();
    
    Teuchos::RCP<MonteCarlo::PhotoatomicReaction> pe_reaction(
	    new MonteCarlo::PhotoelectricPhotoatomicReaction<Utility::LogLog>(
						    energy_grid,
						    pe_cross_section,
						    pe_threshold_index ) );

    // Create the reaction maps
    MonteCarlo::Photoatom::ReactionMap scattering_reactions, 
      absorption_reactions;
    
    scattering_reactions[pp_reaction->getReactionType()] = pp_reaction;
    
    absorption_reactions[pe_reaction->getReactionType()] = pe_reaction;
    
    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
				   new MonteCarlo::VoidAtomicRelaxationModel );

    // Create a test photoatom
    ace_photoatom.reset(
	       new MonteCarlo::StandardPhotoatom<Utility::LogLog>( 
				    ace_file_handler->getTableName(),
				    xss_data_extractor->extractAtomicNumber(),
				    energy_grid,
				    scattering_reactions,
				    absorption_reactions,
				    relaxation_model ) );
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
// end tstStandardPhotoatom.cpp
//---------------------------------------------------------------------------//

