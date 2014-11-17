//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicRelaxationModelACEFactory.cpp
//! \author Alex Robinson
//! \brief  Atomic relaxation model factory using ACE data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModelACEFactory.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a void relaxation model can be created
TEUCHOS_UNIT_TEST( AtomicRelaxationModelACEFactory,
		   createAtomicRelaxationModel_void )
{
  MonteCarlo::AtomicRelaxationModelACEFactory::createAtomicRelaxationModel( 
							   *xss_data_extractor,
							   relaxation_model,
							   false );
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::SubshellType vacancy = MonteCarlo::K_SUBSHELL;

  relaxation_model->relaxAtom( vacancy, photon, bank );

  TEST_EQUALITY_CONST( bank.size(), 0 );

  // Clear the relaxation model
  relaxation_model.reset();
}

//---------------------------------------------------------------------------//
// Check that a detaild relaxation model can be created
TEUCHOS_UNIT_TEST( AtomicRelaxationModelACEFactory,
		   createAtomicRelaxationModel_detailed )
{
  MonteCarlo::AtomicRelaxationModelACEFactory::createAtomicRelaxationModel( 
							   *xss_data_extractor,
							   relaxation_model,
							   true );

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0 );
  photon.setPosition( 1.0, 1.0, 1.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::SubshellType vacancy = MonteCarlo::K_SUBSHELL;

  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.966; // Choose the non-radiative L1-L2 transition
  fake_stream[1] = 0.09809; // Chose the radiative P3 transition
  fake_stream[2] = 0.5; // direction
  fake_stream[3] = 0.5; // direction
  fake_stream[4] = 0.40361; // Chose the radiative P1 transition
  fake_stream[5] = 0.5; // direction
  fake_stream[6] = 0.5; // direction

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  relaxation_model->relaxAtom( vacancy, photon, bank );

  // L1 and L2 radiative transitions
  TEST_EQUALITY_CONST( bank.size(), 2 );

  // L1 radiative transition
  TEST_EQUALITY_CONST( bank.top()->getEnergy(), 1.584170000000E-02 );
  
  bank.pop();
  
  // L2 radiative transition
  TEST_EQUALITY_CONST( bank.top()->getEnergy(), 1.523590000000E-02 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  // Clear the relaxation model
  relaxation_model.reset();
}

//---------------------------------------------------------------------------//
// Check that a relaxation model gets cached
TEUCHOS_UNIT_TEST( AtomicRelaxationModelACEFactory, cache_models )
{
  MonteCarlo::AtomicRelaxationModelACEFactory factory;

  factory.createAndCacheAtomicRelaxationModel( *xss_data_extractor,
					       relaxation_model,
					       true );

  Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> copy_relaxation_model;
  
  factory.createAndCacheAtomicRelaxationModel( *xss_data_extractor,
					       copy_relaxation_model,
					       true );

  TEST_EQUALITY( relaxation_model, copy_relaxation_model );
}

//---------------------------------------------------------------------------//
// Custom main function
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
    xss_data_extractor.reset( new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  }

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
// end tstAtomicRelaxationModelACEFactory.cpp
//---------------------------------------------------------------------------//
