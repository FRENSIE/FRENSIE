//---------------------------------------------------------------------------//
//!
//! \file   tstDetailedAtomicRelaxationModel.cpp
//! \author Alex Robinson
//! \brief  Detailed atomic relaxation model unit tests
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
#include "MonteCarlo_DetailedAtomicRelaxationModel.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::AtomicRelaxationModel>
detailed_atomic_relaxation_model;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the atom can be relaxed
TEUCHOS_UNIT_TEST( DetailedAtomicRelaxationModel, relaxAtom )
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

  TEST_EQUALITY_CONST( bank.size(), 3 );

  // K non-radiative transition
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 5.71919999999999998e-02 );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY_CONST( bank.top().getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( bank.top().getGenerationNumber(), 1 );

  bank.pop();

  // L1 radiative transition
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 1.584170000000E-02 );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( bank.top().getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( bank.top().getGenerationNumber(), 1 );

  bank.pop();

  // L2 radiative transition
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 1.523590000000E-02 );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
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

  // Create a subshell transition model for each subshell
  Teuchos::ArrayView<const double> raw_subshell_endf_designators =
    xss_data_extractor->extractSubshellENDFDesignators();

  Teuchos::Array<Data::SubshellType>
    subshells( raw_subshell_endf_designators.size() );

  for( unsigned i = 0; i < subshells.size(); ++i )
  {
    subshells[i] = Data::convertENDFDesignatorToSubshellEnum(
					    raw_subshell_endf_designators[i] );
  }

  Teuchos::ArrayView<const double> subshell_transitions =
    xss_data_extractor->extractSubshellVacancyTransitionPaths();

  Teuchos::ArrayView<const double> relo_block =
    xss_data_extractor->extractRELOBlock();

  Teuchos::ArrayView<const double> xprob_block =
    xss_data_extractor->extractXPROBBlock();

  Teuchos::Array<Teuchos::RCP<const MonteCarlo::SubshellRelaxationModel> >
    subshell_relaxation_models;

  for( unsigned i = 0; i < subshell_transitions.size(); ++i )
  {
    unsigned shell_transitions = (unsigned)subshell_transitions[i];

    unsigned shell_start = (unsigned)relo_block[i];

    Teuchos::Array<Data::SubshellType>
      primary_transition_shells( shell_transitions );
    Teuchos::Array<Data::SubshellType>
      secondary_transition_shells( shell_transitions );
    Teuchos::Array<double>
      outgoing_particle_energies( shell_transitions );
    Teuchos::Array<double> transition_cdf( shell_transitions );

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

      Teuchos::RCP<const MonteCarlo::SubshellRelaxationModel> shell_model(
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
// end tstDetailedAtomicRelaxationModel.cpp
//---------------------------------------------------------------------------//
