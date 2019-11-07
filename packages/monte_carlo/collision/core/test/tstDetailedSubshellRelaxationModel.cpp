//---------------------------------------------------------------------------//
//!
//! \file   tstDetailedSubshellRelaxationModel.cpp
//! \author Alex Robinson
//! \brief  Detailed subshell relaxation model unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_DetailedSubshellRelaxationModel.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::unique_ptr<const MonteCarlo::SubshellRelaxationModel>
detailed_subshell_relaxation_model;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a subshell can be relaxed
FRENSIE_UNIT_TEST( DetailedSubshellRelaxationModel, relaxSubshell )
{
  MonteCarlo::PhotonState photon( 1 );
  photon.setEnergy( 1.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setPosition( 1.0, 1.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType primary_vacancy, secondary_vacancy;

  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.96121; // select radiative transition to P3 subshell

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  detailed_subshell_relaxation_model->relaxSubshell( photon,
                                                     1e-3,
                                                     1e-5,
						     bank,
						     primary_vacancy,
						     secondary_vacancy );

  FRENSIE_CHECK_EQUAL(detailed_subshell_relaxation_model->getVacancySubshell(),
		      Data::K_SUBSHELL );
  FRENSIE_CHECK_EQUAL( primary_vacancy, Data::P3_SUBSHELL );
  FRENSIE_CHECK_EQUAL( secondary_vacancy, Data::INVALID_SUBSHELL );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 8.828470000000E-02 );
  FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getZPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getGenerationNumber(), 1 );

  Utility::RandomNumberGenerator::unsetFakeStream();
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
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.12p",
						  test_ace_file_start_line ) );
  
  std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                        new Data::XSSEPRDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  
  // Create a subshell transition model for the K subshell
  Utility::ArrayView<const double> subshell_transitions =
    xss_data_extractor->extractSubshellVacancyTransitionPaths();

  unsigned k_shell_transitions = (unsigned)subshell_transitions[0];

  Utility::ArrayView<const double> relo_block =
    xss_data_extractor->extractRELOBlock();

  unsigned k_shell_start = (unsigned)relo_block[0];

  Utility::ArrayView<const double> xprob_block =
    xss_data_extractor->extractXPROBBlock();

  std::vector<Data::SubshellType>
    primary_transition_shells( k_shell_transitions );
  std::vector<Data::SubshellType>
    secondary_transition_shells( k_shell_transitions );
  std::vector<double>
    outgoing_particle_energies( k_shell_transitions );
  std::vector<double> transition_cdf( k_shell_transitions );

  for( unsigned i = 0; i < k_shell_transitions; ++i )
  {
    primary_transition_shells[i] =
      Data::convertENDFDesignatorToSubshellEnum(
					      xprob_block[k_shell_start+i*4] );

    secondary_transition_shells[i] =
      Data::convertENDFDesignatorToSubshellEnum(
					    xprob_block[k_shell_start+i*4+1] );

    outgoing_particle_energies[i] = xprob_block[k_shell_start+i*4+2];
    transition_cdf[i] = xprob_block[k_shell_start+i*4+3];
  }

  detailed_subshell_relaxation_model.reset(
			       new MonteCarlo::DetailedSubshellRelaxationModel(
						   Data::K_SUBSHELL,
						   primary_transition_shells,
						   secondary_transition_shells,
						   outgoing_particle_energies,
						   transition_cdf ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDetailedSubshellRelaxationModel.cpp
//---------------------------------------------------------------------------//
