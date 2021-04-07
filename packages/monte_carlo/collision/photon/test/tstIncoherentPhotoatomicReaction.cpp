//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Incoherent photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedHybridIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "Data_SubshellType.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_InverseAtomicMomentumUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotoatomicReaction> ace_basic_incoherent_reaction;
std::shared_ptr<MonteCarlo::PhotoatomicReaction> ace_detailed_incoherent_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( IncoherentPhotoatomicReaction, getReactionType_ace )
{
  FRENSIE_CHECK_EQUAL( ace_basic_incoherent_reaction->getReactionType(),
		       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( ace_detailed_incoherent_reaction->getReactionType(),
		       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( IncoherentPhotoatomicReaction, getThresholdEnergy_ace )
{
  FRENSIE_CHECK_EQUAL( ace_basic_incoherent_reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_EQUAL( ace_detailed_incoherent_reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( IncoherentPhotoatomicReaction,
		   getNumberOfEmittedPhotons_ace )
{
  FRENSIE_CHECK_EQUAL(
	      ace_basic_incoherent_reaction->getNumberOfEmittedPhotons( 1e-3 ),
	      1u );

  FRENSIE_CHECK_EQUAL(
	      ace_basic_incoherent_reaction->getNumberOfEmittedPhotons( 20.0 ),
	      1u );

  FRENSIE_CHECK_EQUAL(
	   ace_detailed_incoherent_reaction->getNumberOfEmittedPhotons( 1e-3 ),
	   1u );

  FRENSIE_CHECK_EQUAL(
	   ace_detailed_incoherent_reaction->getNumberOfEmittedPhotons( 20.0 ),
	   1u );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( IncoherentPhotoatomicReaction,
		   getNumberOfEmittedElectrons_ace )
{
  FRENSIE_CHECK_EQUAL(
	    ace_basic_incoherent_reaction->getNumberOfEmittedElectrons( 1e-3 ),
            1u );

  FRENSIE_CHECK_EQUAL(
	    ace_basic_incoherent_reaction->getNumberOfEmittedElectrons( 20.0 ),
            1u );

  FRENSIE_CHECK_EQUAL(
	 ace_detailed_incoherent_reaction->getNumberOfEmittedElectrons( 1e-3 ),
         1u );

  FRENSIE_CHECK_EQUAL(
	 ace_detailed_incoherent_reaction->getNumberOfEmittedElectrons( 20.0 ),
         1u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( IncoherentPhotoatomicReaction,
		   getNumberOfEmittedPositrons_ace )
{
  FRENSIE_CHECK_EQUAL(
	    ace_basic_incoherent_reaction->getNumberOfEmittedPositrons( 1e-3 ),
            0u );

  FRENSIE_CHECK_EQUAL(
	    ace_basic_incoherent_reaction->getNumberOfEmittedPositrons( 20.0 ),
            0u );

  FRENSIE_CHECK_EQUAL(
	 ace_detailed_incoherent_reaction->getNumberOfEmittedPositrons( 1e-3 ),
         0u );

  FRENSIE_CHECK_EQUAL(
	 ace_detailed_incoherent_reaction->getNumberOfEmittedPositrons( 20.0 ),
         0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( IncoherentPhotoatomicReaction, getCrossSection_ace )
{
  // Basic reaction
  double cross_section =
    ace_basic_incoherent_reaction->getCrossSection(exp( -1.381551055796E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section =
    ace_basic_incoherent_reaction->getCrossSection(exp( -1.364234411496E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section =
    ace_basic_incoherent_reaction->getCrossSection(exp( 1.151292546497E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Detailed reaction
  cross_section =
    ace_detailed_incoherent_reaction->getCrossSection(exp( -1.381551055796E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = ace_detailed_incoherent_reaction->getCrossSection(
						  exp( -1.364234411496E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = ace_detailed_incoherent_reaction->getCrossSection(
						   exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the basic incoherent reaction can be simulated
FRENSIE_UNIT_TEST( IncoherentPhotoatomicReaction, react_ace_basic )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_basic_incoherent_reaction->react( photon,
					bank,
					shell_of_interaction );

  double min_energy =
    20.0/(1.0+2.0*20.0/Utility::PhysicalConstants::electron_rest_mass_energy );

  FRENSIE_CHECK( photon.getEnergy() >= min_energy );
  FRENSIE_CHECK( photon.getEnergy() <= 20.0 );
  FRENSIE_CHECK_EQUAL( photon.getCollisionNumber(), 1 );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK( shell_of_interaction != Data::UNKNOWN_SUBSHELL );
  FRENSIE_CHECK( shell_of_interaction != Data::INVALID_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the detailed incoherent reaction can be simulated
FRENSIE_UNIT_TEST( IncoherentPhotoatomicReaction, react_ace_detailed )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_detailed_incoherent_reaction->react( photon,
					   bank,
					   shell_of_interaction );

  FRENSIE_CHECK( photon.getEnergy() <= 20.0 );
  FRENSIE_CHECK_EQUAL( photon.getCollisionNumber(), 1 );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK( shell_of_interaction != Data::UNKNOWN_SUBSHELL );
  FRENSIE_CHECK( shell_of_interaction != Data::INVALID_SUBSHELL );
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

  // Extract the energy grid and cross section
  std::shared_ptr<std::vector<double> > energy_grid(
    new std::vector<double>( xss_data_extractor->extractPhotonEnergyGrid() ) );

  Utility::ArrayView<const double> raw_incoherent_cross_section =
    xss_data_extractor->extractIncoherentCrossSection();

  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_incoherent_cross_section.begin(),
                  raw_incoherent_cross_section.end(),
                  [](double cs){ return cs != 0.0; } );

  std::shared_ptr<std::vector<double> > incoherent_cross_section(
        new std::vector<double>( start, raw_incoherent_cross_section.end() ) );

  size_t incoherent_threshold_index =
    energy_grid->size() - incoherent_cross_section->size();

  // Create the scattering function
  Utility::ArrayView<const double> jince_block =
    xss_data_extractor->extractJINCEBlock();

  size_t scatt_func_size = jince_block.size()/2;

  std::vector<double> recoil_momentum( jince_block( 0, scatt_func_size ) );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<Utility::Units::InverseAngstrom,void> > raw_scattering_function(
     new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseAngstrom,void>(
			   recoil_momentum,
			   jince_block( scatt_func_size, scatt_func_size ) ) );

  std::shared_ptr<MonteCarlo::ScatteringFunction> scattering_function(
      new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseAngstrom>( raw_scattering_function ) );

  // Create the subshell order array
  Utility::ArrayView<const double> subshell_endf_des =
    xss_data_extractor->extractSubshellENDFDesignators();

  std::vector<Data::SubshellType> subshell_order( subshell_endf_des.size() );

  for( size_t i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = Data::convertENDFDesignatorToSubshellEnum(
					      (unsigned)subshell_endf_des[i] );
  }

  // Create the Compton profile subshell converter
  std::shared_ptr<const MonteCarlo::ComptonProfileSubshellConverter> converter;

  MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
				   converter,
			           xss_data_extractor->extractAtomicNumber() );

  // Create the compton profile distributions
  Utility::ArrayView<const double> lswd_block =
    xss_data_extractor->extractLSWDBlock();

  Utility::ArrayView<const double> swd_block =
    xss_data_extractor->extractSWDBlock();

  MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution::ComptonProfileArray
    compton_profiles( lswd_block.size() );

  for( size_t shell = 0; shell < lswd_block.size(); ++shell )
  {
    size_t shell_index = lswd_block[shell]; // ignore interp parameter

    size_t num_mom_vals = swd_block[shell_index];

    std::vector<double> half_momentum_grid(
				  swd_block( shell_index + 1, num_mom_vals ) );

    std::vector<double> half_profile(
		   swd_block( shell_index + 1 + num_mom_vals, num_mom_vals ) );

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> > raw_compton_profile(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>(
                                                       half_momentum_grid,
                                                       half_profile ) );

    compton_profiles[shell].reset(
       new MonteCarlo::StandardComptonProfile<Utility::Units::AtomicMomentum>(
                                                       raw_compton_profile ) );
  }

  // Create the incoherent scattering distributions
  std::shared_ptr<const MonteCarlo::IncoherentPhotonScatteringDistribution>
    basic_distribution( new MonteCarlo::DetailedWHIncoherentPhotonScatteringDistribution(
			  scattering_function,
			  xss_data_extractor->extractSubshellOccupancies(),
			  subshell_order ) );

  std::shared_ptr<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution>
    doppler_dist( new MonteCarlo::DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::DoubledHalfComptonProfilePolicy>(
			  xss_data_extractor->extractSubshellOccupancies(),
			  subshell_order,
			  xss_data_extractor->extractLBEPSBlock(),
			  xss_data_extractor->extractLNEPSBlock(),
                          converter,
			  compton_profiles ) );

  std::shared_ptr<const MonteCarlo::IncoherentPhotonScatteringDistribution>
    detailed_distribution( new MonteCarlo::DopplerBroadenedHybridIncoherentPhotonScatteringDistribution(
			  scattering_function,
			  doppler_dist,
			  3.0 ) );

  // Create the reactions
  ace_basic_incoherent_reaction.reset(
		new MonteCarlo::IncoherentPhotoatomicReaction<Utility::LogLog>(
						    energy_grid,
						    incoherent_cross_section,
						    incoherent_threshold_index,
						    basic_distribution ) );

  ace_detailed_incoherent_reaction.reset(
		new MonteCarlo::IncoherentPhotoatomicReaction<Utility::LogLog>(
			  energy_grid,
			  incoherent_cross_section,
			  incoherent_threshold_index,
			  detailed_distribution ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstIncoherentPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
