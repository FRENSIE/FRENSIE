//---------------------------------------------------------------------------//
//!
//! \file   tstCoupledCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  Coupled complete DB photon energy distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfilePolicy.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_InverseAtomicMomentumUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>
  half_distribution;

std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>
  full_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( CoupledCompleteDopplerBroadenedPhotonEnergyDistribution,
		   sample_half )
{
  double incoming_energy = 20.0, scattering_angle_cosine = 0.0;
  double outgoing_energy;
  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.005; // select first shell for collision
  fake_stream[1] = 6.427713151861e-01; // select pz = 0.291894102792
  fake_stream[2] = 0.25; // select energy loss
  fake_stream[3] = 0.5; // select pz = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  half_distribution->sample( incoming_energy,
			     scattering_angle_cosine,
			     outgoing_energy,
			     shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.352804013048420073, 1e-12 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( CoupledCompleteDopplerBroadenedPhotonEnergyDistribution,
		   sample_full )
{
  double incoming_energy = 20.0, scattering_angle_cosine = 0.0;
  double outgoing_energy;
  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.005; // select first shell for collision
  fake_stream[1] = 0.5; // select pz = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  full_distribution->sample( incoming_energy,
			scattering_angle_cosine,
			outgoing_energy,
			shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.4982681851517501, 1e-12 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );
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

  // Create the subshell order array
  Utility::ArrayView<const double> subshell_endf_des =
    xss_data_extractor->extractSubshellENDFDesignators();

  std::vector<Data::SubshellType> subshell_order(
						    subshell_endf_des.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
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
    half_compton_profiles( lswd_block.size() ),
    full_compton_profiles( lswd_block.size() );

  for( unsigned shell = 0; shell < lswd_block.size(); ++shell )
  {
    unsigned shell_index = lswd_block[shell]; // ignore interp parameter

    unsigned num_mom_vals = swd_block[shell_index];

    Utility::ArrayView<const double> raw_half_momentum_grid =
      swd_block( shell_index + 1, num_mom_vals );
    
    std::vector<double> half_momentum_grid( raw_half_momentum_grid.begin(),
                                            raw_half_momentum_grid.end() );
                                           
    Utility::ArrayView<const double> raw_half_profile =
      swd_block( shell_index + 1 + num_mom_vals, num_mom_vals );
    
    std::vector<double> half_profile( raw_half_profile.begin(),
                                      raw_half_profile.end() );
                                     
    std::vector<double> full_momentum_grid, full_profile;

    MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						  half_momentum_grid.end(),
						  half_profile.begin(),
						  half_profile.end(),
						  full_momentum_grid,
						  full_profile,
                                                  true );

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> > raw_compton_profile(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>(
                                                       half_momentum_grid,
                                                       half_profile ) );
    half_compton_profiles[shell].reset(
       new MonteCarlo::StandardComptonProfile<Utility::Units::AtomicMomentum>(
                                                       raw_compton_profile ) );

    raw_compton_profile.reset(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>(
                                                       full_momentum_grid,
                                                       full_profile ) );

    full_compton_profiles[shell].reset(
       new MonteCarlo::StandardComptonProfile<Utility::Units::AtomicMomentum>(
                                                       raw_compton_profile ) );
  }

  std::vector<double> subshell_binding_energies(
                  xss_data_extractor->extractSubshellBindingEnergies().begin(),
                  xss_data_extractor->extractSubshellBindingEnergies().end() );

  std::vector<double> subshell_occupancies(
                      xss_data_extractor->extractSubshellOccupancies().begin(),
                      xss_data_extractor->extractSubshellOccupancies().end() );

  half_distribution.reset(
     new MonteCarlo::CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::DoubledHalfComptonProfilePolicy>(
                                                subshell_binding_energies,
                                                subshell_occupancies,
                                                subshell_order,
                                                converter,
                                                half_compton_profiles ) );

  full_distribution.reset(
     new MonteCarlo::CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::FullComptonProfilePolicy>(
                                                 subshell_binding_energies,
                                                 subshell_occupancies,
                                                 subshell_order,
                                                 converter,
                                                 full_compton_profiles ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCoupledCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
