//---------------------------------------------------------------------------//
//!
//! \file   tstDetailedSubshellRelaxationModel.cpp
//! \author Alex Robinson
//! \brief  Detailed subshell relaxation model unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DetailedSubshellRelaxationModel.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::SubshellRelaxationModel>
detailed_subshell_relaxation_model;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a subshell can be relaxed
TEUCHOS_UNIT_TEST( DetailedSubshellRelaxationModel, relaxSubshell )
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

  TEST_EQUALITY_CONST(detailed_subshell_relaxation_model->getVacancySubshell(),
		      Data::K_SUBSHELL );
  TEST_EQUALITY_CONST( primary_vacancy, Data::P3_SUBSHELL );
  TEST_EQUALITY_CONST( secondary_vacancy, Data::INVALID_SUBSHELL );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 8.828470000000E-02 );
  TEST_EQUALITY_CONST( bank.top().getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( bank.top().getGenerationNumber(), 1 );

  Utility::RandomNumberGenerator::unsetFakeStream();
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

  // Create a subshell transition model for the K subshell
  Teuchos::ArrayView<const double> subshell_transitions =
    xss_data_extractor->extractSubshellVacancyTransitionPaths();

  unsigned k_shell_transitions = (unsigned)subshell_transitions[0];

  Teuchos::ArrayView<const double> relo_block =
    xss_data_extractor->extractRELOBlock();

  unsigned k_shell_start = (unsigned)relo_block[0];

  Teuchos::ArrayView<const double> xprob_block =
    xss_data_extractor->extractXPROBBlock();

  Teuchos::Array<Data::SubshellType>
    primary_transition_shells( k_shell_transitions );
  Teuchos::Array<Data::SubshellType>
    secondary_transition_shells( k_shell_transitions );
  Teuchos::Array<double>
    outgoing_particle_energies( k_shell_transitions );
  Teuchos::Array<double> transition_cdf( k_shell_transitions );

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
// end tstDetailedSubshellRelaxationModel.cpp
//---------------------------------------------------------------------------//
