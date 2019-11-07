//---------------------------------------------------------------------------//
//!
//! \file   tstDetailedAtomicRelaxationModel.cpp
//! \author Alex Robinson
//! \brief  Detailed atomic relaxation model unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_DetailedSubshellRelaxationModel.hpp"
#include "MonteCarlo_DetailedAtomicRelaxationModel.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::unique_ptr<const MonteCarlo::AtomicRelaxationModel>
detailed_atomic_relaxation_model;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the atom can be relaxed
FRENSIE_UNIT_TEST( DetailedAtomicRelaxationModel, relaxAtom )
{
  MonteCarlo::PhotonState photon( 1 );
  photon.setEnergy( 1.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setPosition( 1.0, 1.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType vacancy = Data::K_SUBSHELL;

  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.966; // Choose the non-radiative L1-L2 transition
  fake_stream[1] = 0.5; // direction
  fake_stream[2] = 0.5; // direction
  fake_stream[3] = 0.09809; // Chose the radiative P3 transition
  fake_stream[4] = 0.5; // direction
  fake_stream[5] = 0.5; // direction
  fake_stream[6] = 0.40361; // Chose the radiative P1 transition
  fake_stream[7] = 0.5; // direction
  fake_stream[8] = 0.5; // direction

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  detailed_atomic_relaxation_model->relaxAtom( vacancy, photon, bank );

  FRENSIE_CHECK_EQUAL( bank.size(), 3 );

  // K non-radiative transition
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.71919999999999998e-02 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getZPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getGenerationNumber(), 1 );

  bank.pop();

  // L1 radiative transition
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.584170000000E-02 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::PHOTON );
  FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getZPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getGenerationNumber(), 1 );

  bank.pop();

  // L2 radiative transition
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.523590000000E-02 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::PHOTON );
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

  // Create a subshell transition model for each subshell
  Utility::ArrayView<const double> raw_subshell_endf_designators =
    xss_data_extractor->extractSubshellENDFDesignators();

  std::vector<Data::SubshellType>
    subshells( raw_subshell_endf_designators.size() );

  for( unsigned i = 0; i < subshells.size(); ++i )
  {
    subshells[i] = Data::convertENDFDesignatorToSubshellEnum(
					    raw_subshell_endf_designators[i] );
  }

  Utility::ArrayView<const double> subshell_transitions =
    xss_data_extractor->extractSubshellVacancyTransitionPaths();

  Utility::ArrayView<const double> relo_block =
    xss_data_extractor->extractRELOBlock();

  Utility::ArrayView<const double> xprob_block =
    xss_data_extractor->extractXPROBBlock();

  std::vector<std::shared_ptr<const MonteCarlo::SubshellRelaxationModel> >
    subshell_relaxation_models;

  for( unsigned i = 0; i < subshell_transitions.size(); ++i )
  {
    unsigned shell_transitions = (unsigned)subshell_transitions[i];

    unsigned shell_start = (unsigned)relo_block[i];

    std::vector<Data::SubshellType>
      primary_transition_shells( shell_transitions );
    std::vector<Data::SubshellType>
      secondary_transition_shells( shell_transitions );
    std::vector<double>
      outgoing_particle_energies( shell_transitions );
    std::vector<double> transition_cdf( shell_transitions );

    if( shell_transitions > 0 )
    {
      for( unsigned j = 0; j < shell_transitions; ++j )
      {
	primary_transition_shells[j] =
	  Data::convertENDFDesignatorToSubshellEnum(
					        xprob_block[shell_start+j*4] );

	secondary_transition_shells[j] =
	  Data::convertENDFDesignatorToSubshellEnum(
					      xprob_block[shell_start+j*4+1] );

	outgoing_particle_energies[j] = xprob_block[shell_start+j*4+2];
	transition_cdf[j] = xprob_block[shell_start+j*4+3];
      }

      std::shared_ptr<const MonteCarlo::SubshellRelaxationModel> shell_model(
			       new MonteCarlo::DetailedSubshellRelaxationModel(
						   subshells[i],
						   primary_transition_shells,
						   secondary_transition_shells,
						   outgoing_particle_energies,
						   transition_cdf ) );

      subshell_relaxation_models.push_back( shell_model );
    }
  }

  detailed_atomic_relaxation_model.reset(
			      new MonteCarlo::DetailedAtomicRelaxationModel(
                                    subshell_relaxation_models, 1e-3, 1e-5 ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDetailedAtomicRelaxationModel.cpp
//---------------------------------------------------------------------------//
