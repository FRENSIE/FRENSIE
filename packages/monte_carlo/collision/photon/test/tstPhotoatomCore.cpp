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
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotoatomCore> ace_photoatom_core;

//---------------------------------------------------------------------------//
// Check that the total reaction can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getTotalReaction )
{
  const MonteCarlo::PhotoatomicReaction& total_reaction =
    ace_photoatom_core->getTotalReaction();

  double cross_section =
    total_reaction.getCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    total_reaction.getCrossSection( exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section =
    total_reaction.getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY(cross_section,
			 exp( -1.115947249407E+01 ) + exp( 3.718032834377E+00),
			 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getTotalAbsorptionReaction )
{
  const MonteCarlo::PhotoatomicReaction& absorption_reaction =
    ace_photoatom_core->getTotalAbsorptionReaction();

  double cross_section = absorption_reaction.getCrossSection(
						  exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = absorption_reaction.getCrossSection(
						  exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = absorption_reaction.getCrossSection(
						  exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = absorption_reaction.getCrossSection(
						   exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getScatteringReactions )
{
  const MonteCarlo::PhotoatomCore::ConstReactionMap& scattering_reactions =
    ace_photoatom_core->getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 1 );

  const MonteCarlo::PhotoatomicReaction& pp_reaction =
    *(scattering_reactions.find(MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION)->second);

  double cross_section =
    pp_reaction.getCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = pp_reaction.getCrossSection( exp( 2.480967890857E-02 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = pp_reaction.getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getScatteringReactionTypes )
{
  MonteCarlo::PhotoatomCore::ReactionEnumTypeSet reaction_types;
  
  ace_photoatom_core->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 1 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getAbsorptionReactions )
{
  const MonteCarlo::PhotoatomCore::ConstReactionMap& absorption_reactions =
    ace_photoatom_core->getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 1 );

  const MonteCarlo::PhotoatomicReaction& pe_reaction =
    *(absorption_reactions.find(MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION)->second);

  double cross_section =
    pe_reaction.getCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = pe_reaction.getCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = pe_reaction.getCrossSection( exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = pe_reaction.getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getAbsorptionReactionTypes )
{
  MonteCarlo::PhotoatomCore::ReactionEnumTypeSet reaction_types;
  
  ace_photoatom_core->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 1 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that miscellaneous reactions can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getMiscReactions )
{
  const MonteCarlo::PhotoatomCore::ConstReactionMap& misc_reactions =
    ace_photoatom_core->getMiscReactions();

  FRENSIE_CHECK_EQUAL( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the misc reaction types can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getMiscReactionTypes )
{
  MonteCarlo::PhotoatomCore::ReactionEnumTypeSet reaction_types;
  
  ace_photoatom_core->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getReactionTypes )
{
  MonteCarlo::PhotoatomCore::ReactionEnumTypeSet reaction_types;
  
  ace_photoatom_core->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 4 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the atomic relaxation model can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getAtomicRelaxationModel )
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

  FRENSIE_CHECK_EQUAL( bank.size(), 0u );
}

//---------------------------------------------------------------------------//
// Check that the hash-based grid searcher can be returned
FRENSIE_UNIT_TEST( PhotoatomCore, getGridSearcher )
{
  const Utility::HashBasedGridSearcher<double>& grid_searcher =
    ace_photoatom_core->getGridSearcher();

  size_t grid_index = grid_searcher.findLowerBinIndex( 1e-3 );

  FRENSIE_CHECK_EQUAL( grid_index, 1912 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Create a file handler and data extractor
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.12p",
						  test_ace_file_start_line ) );
    
    std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    // Create the pair production and photoelectric effect cross sections
    std::shared_ptr<std::vector<double> > energy_grid(
       new std::vector<double>( xss_data_extractor->extractPhotonEnergyGrid() ) );

    std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
          new Utility::StandardHashBasedGridSearcher<std::vector<double>,true>(
					     energy_grid,
					     energy_grid->front(),
					     energy_grid->back(),
					     100 ) );

    Utility::ArrayView<const double> raw_pe_cross_section =
      xss_data_extractor->extractPhotoelectricCrossSection();

    Utility::ArrayView<const double>::iterator start =
      std::find_if( raw_pe_cross_section.begin(),
		    raw_pe_cross_section.end(),
		    [](double cs){ return cs != 0.0; } );

    std::shared_ptr<std::vector<double> > pe_cross_section(
                new std::vector<double>( start, raw_pe_cross_section.end() ) );

    size_t pe_threshold_index =
      energy_grid->size() - pe_cross_section->size();

    std::shared_ptr<MonteCarlo::PhotoatomicReaction> pe_reaction(
	    new MonteCarlo::PhotoelectricPhotoatomicReaction<Utility::LogLog>(
						    energy_grid,
						    pe_cross_section,
						    pe_threshold_index,
						    grid_searcher ) );

    Utility::ArrayView<const double> raw_pp_cross_section =
      xss_data_extractor->extractPairProductionCrossSection();

    start = std::find_if( raw_pp_cross_section.begin(),
                          raw_pp_cross_section.end(),
                          [](double cs){ return cs != 0.0; } );

    std::shared_ptr<std::vector<double> > pp_cross_section(
                new std::vector<double>( start, raw_pp_cross_section.end() ) );

    size_t pp_threshold_index =
      energy_grid->size() - pp_cross_section->size();

    std::shared_ptr<MonteCarlo::PhotoatomicReaction> pp_reaction(
	    new MonteCarlo::PairProductionPhotoatomicReaction<Utility::LogLog>(
							energy_grid,
							pp_cross_section,
							pp_threshold_index,
							grid_searcher ) );

    // Create the reaction maps
    MonteCarlo::PhotoatomCore::ConstReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[pp_reaction->getReactionType()] = pp_reaction;

    absorption_reactions[pe_reaction->getReactionType()] = pe_reaction;

    // Create a void atomic relaxation model
    std::shared_ptr<MonteCarlo::AtomicRelaxationModel> relaxation_model(
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
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotoatomCore.cpp
//---------------------------------------------------------------------------//
