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
TEUCHOS_UNIT_TEST( Photoatom, getAbsorptionReactionTypes_default )
{
  const boost::unordered_set<MonteCarlo::PhotoatomicReactionType>&
    absorption_types = MonteCarlo::Photoatom::getAbsorptionReactionTypes();

  TEST_ASSERT( absorption_types.count( 
		      MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		 MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	       MonteCarlo::P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	       MonteCarlo::P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	       MonteCarlo::Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	       MonteCarlo::Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	       MonteCarlo::Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );

  TEST_ASSERT( !absorption_types.count(
	       MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( !absorption_types.count(
	       MonteCarlo::COHERENT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( !absorption_types.count(
	       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( !absorption_types.count(
	       MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the absorption types can be set
TEUCHOS_UNIT_TEST( Photoatom, setAbsorptionTypes )
{
  Teuchos::Array<MonteCarlo::PhotoatomicReactionType> absorption_reactions( 1 );

  absorption_reactions[0] = 
    MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  MonteCarlo::Photoatom::setAbsorptionReactionTypes( absorption_reactions );

  TEST_EQUALITY_CONST( 
		    MonteCarlo::Photoatom::getAbsorptionReactionTypes().size(),
		    1 );

  TEST_ASSERT( MonteCarlo::Photoatom::getAbsorptionReactionTypes().count(
	       MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that an absorption type can be added
TEUCHOS_UNIT_TEST( Photoatom, addAbsorptionReactionType )
{
  Teuchos::Array<MonteCarlo::PhotoatomicReactionType> absorption_reactions( 1 );

  absorption_reactions[0] = 
    MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  MonteCarlo::Photoatom::setAbsorptionReactionTypes( absorption_reactions );
  MonteCarlo::Photoatom::addAbsorptionReactionType(
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( 
		    MonteCarlo::Photoatom::getAbsorptionReactionTypes().size(),
		    2 );

  TEST_ASSERT( MonteCarlo::Photoatom::getAbsorptionReactionTypes().count(
	       MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( MonteCarlo::Photoatom::getAbsorptionReactionTypes().count(
	       MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the photoatom name can be returned
TEUCHOS_UNIT_TEST( Photoatom, getName_ace )
{
  TEST_EQUALITY_CONST( ace_photoatom->getName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the photoatom atomic number can be returned
TEUCHOS_UNIT_TEST( Photoatom, getAtomicNumber_ace )
{
  TEST_EQUALITY_CONST( ace_photoatom->getAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
TEUCHOS_UNIT_TEST( StandardPhotoatom, getTotalCrossSection_ace )
{
  double cross_section = 
    ace_photoatom->getTotalCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getTotalCrossSection( exp( -1.214720768866E+01 ) );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getTotalCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY(cross_section,
			 exp( -1.115947249407E+01 ) + exp( 3.71803283438E+00 ),
			 1e-11 );

}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
TEUCHOS_UNIT_TEST( StandardPhotoatom, getAbsorptionCrossSection_ace )
{
  double cross_section = 
    ace_photoatom->getAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section =
    ace_photoatom->getAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getAbsorptionCrossSection( exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( Photoatom, getSurvivalProbability )
{
  double survival_prob = 
    ace_photoatom->getSurvivalProbability( exp( -1.214969212306E+01 ) );
  
  TEST_FLOATING_EQUALITY( survival_prob, 0.0, 1e-12 );

  survival_prob = 
    ace_photoatom->getSurvivalProbability( exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( survival_prob, 0.0, 1e-12 );

  survival_prob = 
    ace_photoatom->getAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  double expected_survival_prob = exp( 3.71803283438E+00 )/
    (exp( 3.71803283438E+00 ) + exp( -1.115947249407E+01 ));
  
  TEST_FLOATING_EQUALITY( survival_prob, expected_survival_prob, 1e-12 );
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
    Teuchos::ArrayView<const double> raw_energy_grid = 
      xss_data_extractor->extractPhotonEnergyGrid();
    
    Teuchos::ArrayView<const double> raw_pe_cross_section = 
      xss_data_extractor->extractPhotoelectricCrossSection();
    
    Teuchos::ArrayView<const double>::iterator start = 
      std::find_if( raw_pe_cross_section.begin(),
		    raw_pe_cross_section.end(),
		    notEqualZero );

    Teuchos::ArrayRCP<double> pe_cross_section;
    pe_cross_section.assign( start, raw_pe_cross_section.end() );

    unsigned start_energy_bin = std::distance( raw_pe_cross_section.begin(),
					       start );

    start = raw_energy_grid.begin();
    std::advance( start, start_energy_bin );

    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.assign( start, raw_energy_grid.end() );
    std::cout << energy_grid.size() << " " << pe_cross_section.size() 
	      << std::endl;
    Teuchos::RCP<MonteCarlo::PhotoatomicReaction> pe_reaction(
	    new MonteCarlo::PhotoelectricPhotoatomicReaction<Utility::LogLog>(
						    energy_grid,
						    pe_cross_section,
						    0u ) );
    
    Teuchos::ArrayView<const double> raw_pp_cross_section = 
      xss_data_extractor->extractPairProductionCrossSection();
    
    start = std::find_if( raw_pp_cross_section.begin(),
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

