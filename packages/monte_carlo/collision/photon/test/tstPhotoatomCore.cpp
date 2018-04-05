//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomCore.cpp
//! \author Alex Robinson
//! \brief  PhotoatomCore unit tests
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
#include "MonteCarlo_PhotoatomCore.hpp"
#include "MonteCarlo_PairProductionPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotoatomCore> ace_photoatom_core;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( const double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Check that the total reaction can be returned
TEUCHOS_UNIT_TEST( PhotoatomCore, getTotalReaction )
{
  const MonteCarlo::PhotoatomicReaction& total_reaction =
    ace_photoatom_core->getTotalReaction();

  double cross_section =
    total_reaction.getCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    total_reaction.getCrossSection( exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section =
    total_reaction.getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY(cross_section,
			 exp( -1.115947249407E+01 ) + exp( 3.718032834377E+00),
			 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be returned
TEUCHOS_UNIT_TEST( PhotoatomCore, getTotalAbsorptionReaction )
{
  const MonteCarlo::PhotoatomicReaction& absorption_reaction =
    ace_photoatom_core->getTotalAbsorptionReaction();

  double cross_section = absorption_reaction.getCrossSection(
						  exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = absorption_reaction.getCrossSection(
						  exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = absorption_reaction.getCrossSection(
						  exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = absorption_reaction.getCrossSection(
						   exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
TEUCHOS_UNIT_TEST( PhotoatomCore, getScatteringReactions )
{
  const MonteCarlo::PhotoatomCore::ConstReactionMap& scattering_reactions =
    ace_photoatom_core->getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 1 );

  const MonteCarlo::PhotoatomicReaction& pp_reaction =
    *(scattering_reactions.find(MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION)->second);

  double cross_section =
    pp_reaction.getCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = pp_reaction.getCrossSection( exp( 2.480967890857E-02 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = pp_reaction.getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
TEUCHOS_UNIT_TEST( PhotoatomCore, getAbsorptionReactions )
{
  const MonteCarlo::PhotoatomCore::ConstReactionMap& absorption_reactions =
    ace_photoatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 1 );

  const MonteCarlo::PhotoatomicReaction& pe_reaction =
    *(absorption_reactions.find(MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION)->second);

  double cross_section =
    pe_reaction.getCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = pe_reaction.getCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = pe_reaction.getCrossSection( exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = pe_reaction.getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that miscellaneous reactions can be returned
TEUCHOS_UNIT_TEST( PhotoatomCore, getMiscReactions )
{
  const MonteCarlo::PhotoatomCore::ConstReactionMap& misc_reactions =
    ace_photoatom_core->getMiscReactions();

  TEST_EQUALITY_CONST( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic relaxation model can be returned
TEUCHOS_UNIT_TEST( PhotoatomCore, getAtomicRelaxationModel )
{
  Data::SubshellType vacancy = Data::K_SUBSHELL;

  MonteCarlo::PhotonState photon( 0u );
  photon.setEnergy( 1.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setPosition( 0.0, 0.0, 0.0 );

  MonteCarlo::ParticleBank bank;

  const MonteCarlo::AtomicRelaxationModel& relaxation_model =
    ace_photoatom_core->getAtomicRelaxationModel();

  relaxation_model.relaxAtom( vacancy, photon, bank );

  TEST_EQUALITY_CONST( bank.size(), 0u );
}

//---------------------------------------------------------------------------//
// Check that the hash-based grid searcher can be returned
TEUCHOS_UNIT_TEST( PhotoatomCore, getGridSearcher )
{
  const Utility::HashBasedGridSearcher& grid_searcher =
    ace_photoatom_core->getGridSearcher();

  unsigned grid_index = grid_searcher.findLowerBinIndex( 1e-3 );

  TEST_EQUALITY_CONST( grid_index, 1912 );
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

    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,true>(
					     energy_grid,
					     energy_grid[0],
					     energy_grid[energy_grid.size()-1],
					     100 ) );

    Teuchos::ArrayView<const double> raw_pe_cross_section =
      xss_data_extractor->extractPhotoelectricCrossSection();

    Teuchos::ArrayView<const double>::iterator start =
      std::find_if( raw_pe_cross_section.begin(),
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
						    pe_threshold_index,
						    grid_searcher ) );

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
							pp_threshold_index,
							grid_searcher ) );

    // Create the reaction maps
    MonteCarlo::PhotoatomCore::ReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[pp_reaction->getReactionType()] = pp_reaction;

    absorption_reactions[pe_reaction->getReactionType()] = pe_reaction;

    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
				   new MonteCarlo::VoidAtomicRelaxationModel );

    // Create a test photoatom core
    ace_photoatom_core.reset(
			  new MonteCarlo::PhotoatomCore( energy_grid,
							 grid_searcher,
							 scattering_reactions,
							 absorption_reactions,
							 relaxation_model,
							 true,
							 Utility::LogLog() ) );

    // Run the unit tests
    Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  }

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}


//---------------------------------------------------------------------------//
// end tstPhotoatomCore.cpp
//---------------------------------------------------------------------------//
