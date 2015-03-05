//---------------------------------------------------------------------------//
//!
//! \file   tstOccupationNumberEvaluator.cpp
//! \author Alex Robinson
//! \brief  Occupation number evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_OccupationNumberEvaluator.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::OccupationNumberEvaluator> 
  occupation_number_h_k;

Teuchos::RCP<DataGen::OccupationNumberEvaluator>
  occupation_number_pb_k;

Teuchos::RCP<DataGen::OccupationNumberEvaluator>
  occupation_number_pb_p3;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Compton profile can be evaluated
TEUCHOS_UNIT_TEST( OccupationNumberEvaluator, evaluateComptonProfile_h )
{
  double norm_constant = 
    occupation_number_h_k->getComptonProfileNormConstant();
  
  double compton_profile_value = 
    occupation_number_h_k->evaluateComptonProfile( -1.1 );

  TEST_EQUALITY_CONST( compton_profile_value, 0.0 );

  compton_profile_value = 
    occupation_number_h_k->evaluateComptonProfile( -1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value, 
				  2.22639294755139392e-09/norm_constant, 
				  1e-15 );

  compton_profile_value = 
    occupation_number_h_k->evaluateComptonProfile( -0.5837882030079395 );

  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value,
				  4.561986437562962e-09/norm_constant,
				  1e-15 );

  compton_profile_value =
    occupation_number_h_k->evaluateComptonProfile( 0.0 );

  TEST_FLOATING_EQUALITY( compton_profile_value, 
			  115.83526012799598/norm_constant, 1e-15 );

  compton_profile_value = 
    occupation_number_h_k->evaluateComptonProfile( 0.5837882030079395 );

  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value,
				  4.561986437562962e-09/norm_constant,
				  1e-15 );
  
  compton_profile_value = 
    occupation_number_h_k->evaluateComptonProfile( 1.0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value, 
				  2.22639294755139392e-09/norm_constant, 
				  1e-15 );

  compton_profile_value =
    occupation_number_h_k->evaluateComptonProfile( 1.1 );

  TEST_EQUALITY_CONST( compton_profile_value, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be evaluated
TEUCHOS_UNIT_TEST( OccupationNumberEvaluator, evaluateComptonProfile_pb )
{
  double norm_constant = 
    occupation_number_pb_k->getComptonProfileNormConstant();
  
  // K-shell
  double compton_profile_value = 
    occupation_number_pb_k->evaluateComptonProfile( -1.1 );

  TEST_EQUALITY_CONST( compton_profile_value, 0.0 );

  compton_profile_value = 
    occupation_number_pb_k->evaluateComptonProfile( -1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value, 
				  5.20373615890446367e-02/norm_constant, 
				  1e-15 );

  compton_profile_value = 
    occupation_number_pb_k->evaluateComptonProfile( -0.5837882030079395 );

  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value,
				  0.26118480303735186/norm_constant,
				  1e-15 );

  compton_profile_value =
    occupation_number_pb_k->evaluateComptonProfile( 0.0 );

  TEST_FLOATING_EQUALITY( compton_profile_value, 
			  1.3083852583290587/norm_constant, 
			  1e-15 );

  compton_profile_value = 
    occupation_number_pb_k->evaluateComptonProfile( 0.5837882030079395 );

  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value,
				  0.26118480303735186/norm_constant,
				  1e-15 );
  
  compton_profile_value = 
    occupation_number_pb_k->evaluateComptonProfile( 1.0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value, 
				  5.20373615890446367e-02/norm_constant, 
				  1e-15 );

  compton_profile_value =
    occupation_number_pb_k->evaluateComptonProfile( 1.1 );

  TEST_EQUALITY_CONST( compton_profile_value, 0.0 );

  // P3-shell
  norm_constant = occupation_number_pb_p3->getComptonProfileNormConstant();
  
  compton_profile_value = 
    occupation_number_pb_p3->evaluateComptonProfile( -1.1 );

  TEST_EQUALITY_CONST( compton_profile_value, 0.0 );

  compton_profile_value = 
    occupation_number_pb_p3->evaluateComptonProfile( -1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value, 
				  1.55571233220910706e-06/norm_constant, 
				  1e-15 );

  compton_profile_value = 
    occupation_number_pb_p3->evaluateComptonProfile( -0.5837882030079395 );

  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value,
				  4.269136342282414e-05/norm_constant,
				  1e-15 );

  compton_profile_value =
    occupation_number_pb_p3->evaluateComptonProfile( 0.0 );

  TEST_FLOATING_EQUALITY( compton_profile_value, 
			  110.18902693969845/norm_constant, 
			  1e-15 );

  compton_profile_value = 
    occupation_number_pb_p3->evaluateComptonProfile( 0.5837882030079395 );

  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value,
				  4.269136342282414e-05/norm_constant,
				  1e-15 );
  
  compton_profile_value = 
    occupation_number_pb_p3->evaluateComptonProfile( 1.0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( compton_profile_value, 
				  1.55571233220910706e-06/norm_constant, 
				  1e-15 );

  compton_profile_value =
    occupation_number_pb_p3->evaluateComptonProfile( 1.1 );

  TEST_EQUALITY_CONST( compton_profile_value, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the occupation number can be evaluated
TEUCHOS_UNIT_TEST( OccupationNumberEvaluator, evaluateOccupationNumber_h )
{
  double occupation_number = 
    occupation_number_h_k->evaluateOccupationNumber( -1.1 );

  TEST_EQUALITY_CONST( occupation_number, 0.0 );

  occupation_number = 
    occupation_number_h_k->evaluateOccupationNumber( -1.0 );
  
  TEST_EQUALITY_CONST( occupation_number, 0.0 );

  occupation_number = 
    occupation_number_h_k->evaluateOccupationNumber( 0.0, 1e-5 );

  TEST_FLOATING_EQUALITY( occupation_number, 0.5, 1e-6 );

  occupation_number = 
    occupation_number_h_k->evaluateOccupationNumber( 1.0, 1e-4 );

  TEST_FLOATING_EQUALITY( occupation_number, 1.0, 1e-15 );

  occupation_number = 
    occupation_number_h_k->evaluateOccupationNumber( 1.1, 1e-4 );

  TEST_FLOATING_EQUALITY( occupation_number, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the occupation number can be evaluated
TEUCHOS_UNIT_TEST( OccupationNumberEvaluator, evaluateOccupationNumber_pb )
{
  // K-shell
  double occupation_number = 
    occupation_number_pb_k->evaluateOccupationNumber( -1.1 );

  TEST_EQUALITY_CONST( occupation_number, 0.0 );

  occupation_number = 
    occupation_number_pb_k->evaluateOccupationNumber( -1.0 );
  
  TEST_EQUALITY_CONST( occupation_number, 0.0 );

  occupation_number = 
    occupation_number_pb_k->evaluateOccupationNumber( 0.0, 1e-5 );
  
  TEST_FLOATING_EQUALITY( occupation_number, 0.5, 1e-5 );

  occupation_number = 
    occupation_number_pb_k->evaluateOccupationNumber( 1.0, 1e-4 );
  
  TEST_FLOATING_EQUALITY( occupation_number, 1.0, 1e-15 );

  occupation_number = 
    occupation_number_pb_k->evaluateOccupationNumber( 1.1, 1e-4 );

  TEST_FLOATING_EQUALITY( occupation_number, 1.0, 1e-15 );

  // P3-shell
  occupation_number = 
    occupation_number_pb_p3->evaluateOccupationNumber( -1.1 );

  TEST_EQUALITY_CONST( occupation_number, 0.0 );

  occupation_number = 
    occupation_number_pb_p3->evaluateOccupationNumber( -1.0 );
  
  TEST_EQUALITY_CONST( occupation_number, 0.0 );

  occupation_number = 
    occupation_number_pb_p3->evaluateOccupationNumber( 0.0, 1e-5 );
  
  TEST_FLOATING_EQUALITY( occupation_number, 0.5, 1e-6 );

  occupation_number = 
    occupation_number_pb_p3->evaluateOccupationNumber( 1.0, 1e-4 );

  TEST_FLOATING_EQUALITY( occupation_number, 1.0, 1e-15 );

  occupation_number = 
    occupation_number_pb_p3->evaluateOccupationNumber( 1.1, 1e-4 );

  TEST_FLOATING_EQUALITY( occupation_number, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_h_ace_file_name, test_h_ace_table_name;
  std::string test_pb_ace_file_name, test_pb_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_ace_file",
		 &test_h_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_h_ace_table",
		 &test_h_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_pb_ace_file",
		 &test_pb_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_pb_ace_table",
		 &test_pb_ace_table_name,
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
    // Create the file handler and data extractor for hydrogen
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_h_ace_file_name,
							 test_h_ace_table_name,
							 1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
    
    // Create the Compton profile subshell converter
    Teuchos::RCP<MonteCarlo::ComptonProfileSubshellConverter> converter;
    
    MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
				   converter,
			           xss_data_extractor->extractAtomicNumber() );

    unsigned k_shell_index = converter->convertSubshellToIndex(
						      MonteCarlo::K_SUBSHELL );

    // Pull out the k-shell compton profile for hydrogen
    Teuchos::ArrayView<const double> lswd_block = 
      xss_data_extractor->extractLSWDBlock();
    
    Teuchos::ArrayView<const double> swd_block = 
      xss_data_extractor->extractSWDBlock();

    unsigned profile_index = lswd_block[k_shell_index]; // ignore interp param
    
    unsigned num_mom_vals = swd_block[profile_index];

    Teuchos::Array<double> compton_profile = 
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    // Divide profile values by 2 since they are multiplied by 2 in epr tables
    for( unsigned i = 0u; i < compton_profile.size(); ++i )
      compton_profile[i] /= 2.0;

    occupation_number_h_k.reset( new DataGen::OccupationNumberEvaluator(
	       swd_block( profile_index + 1, num_mom_vals ),
	       compton_profile ) );
  }

  {
    // Create the file handler and data extractor for lead
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			      new Data::ACEFileHandler( test_pb_ace_file_name,
							test_pb_ace_table_name,
							1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
    
    // Create the Compton profile subshell converter
    Teuchos::RCP<MonteCarlo::ComptonProfileSubshellConverter> converter;
    
    MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
				   converter,
			           xss_data_extractor->extractAtomicNumber() );

    unsigned k_shell_index = converter->convertSubshellToIndex(
						      MonteCarlo::K_SUBSHELL );

    unsigned p3_shell_index = converter->convertSubshellToIndex(
						     MonteCarlo::P3_SUBSHELL );

    // Pull out the k-shell and p3-shell compton profiles for lead
    Teuchos::ArrayView<const double> lswd_block = 
      xss_data_extractor->extractLSWDBlock();
    
    Teuchos::ArrayView<const double> swd_block = 
      xss_data_extractor->extractSWDBlock();

    unsigned profile_index = lswd_block[k_shell_index]; // ignore interp param
    
    unsigned num_mom_vals = swd_block[profile_index];

    Teuchos::Array<double> compton_profile = 
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    // Divide profile values by 2 since they are multiplied by 2 in epr tables
    for( unsigned i = 0u; i < compton_profile.size(); ++i )
      compton_profile[i] /= 2.0;

    occupation_number_pb_k.reset( new DataGen::OccupationNumberEvaluator(
				  swd_block( profile_index + 1, num_mom_vals ),
				  compton_profile ) );

    profile_index = lswd_block[p3_shell_index];

    num_mom_vals = swd_block[profile_index];

    compton_profile = 
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    // Divide profile values by 2 since they are multiplied by 2 in epr tables
    for( unsigned i = 0u; i < compton_profile.size(); ++i )
      compton_profile[i] /= 2.0;

    occupation_number_pb_p3.reset( new DataGen::OccupationNumberEvaluator(
				  swd_block( profile_index + 1, num_mom_vals ),
				  compton_profile ) );
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
// end tstOccupationNumberEvaluator.cpp
//---------------------------------------------------------------------------//
