//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Electroionization electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution> 
  ace_electroionization_distribution;

double binding_energy;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution, 
                   scatterElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;
  
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  ace_electroionization_distribution->scatterElectron( electron, 
                                                       bank, 
                                                       shell_of_interaction );

  // Test original electron
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.964446703542646, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 8.706573789423E-01, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.279436961765390, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 4.105262105768E-02, 1e-12 );

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

  // Extract the cross sections energy grid
  Teuchos::ArrayView<const double> energy_grid =
    xss_data_extractor->extractElectronEnergyGrid() ;

  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators = 
    xss_data_extractor->extractSubshellENDFDesignators();

  // Extract the subshell binding energies
  Teuchos::ArrayView<const double> binding_energies =
    xss_data_extractor->extractSubshellBindingEnergies();

  // Extract the electroionization data block (EION)
  Teuchos::ArrayView<const double> eion_block(
    xss_data_extractor->extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = xss_data_extractor->returnEIONLoc();

  // Extract the number of subshells (N_s)
  int num_shells = subshell_endf_designators.size();

  // Extract the number of knock-on tables by subshell (N_i)
  Teuchos::Array<double> num_tables(eion_block(0,num_shells));

  // Extract the location of info about knock-on tables by subshell
  Teuchos::Array<double> table_info(eion_block(num_shells,num_shells));

  // Extract the location of knock-on tables by subshell
  Teuchos::Array<double> table_loc(eion_block(2*num_shells,num_shells));

  // Subshell
  unsigned subshell = 0;

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[subshell]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[subshell]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  Teuchos::Array<double> table_energy_grid(eion_block( subshell_info,
                                                       num_tables[subshell] ) );

  // Extract the length of the knock-on sampling tables
  Teuchos::Array<double> table_length(eion_block( 
                               subshell_info + num_tables[subshell],
                               num_tables[subshell] ) );

  // Extract the offset of the knock-on sampling tables
  Teuchos::Array<double> table_offset(eion_block( 
                             subshell_info + 2*num_tables[subshell],
                             num_tables[subshell] ) );

   // Create the electroionization sampling table for the subshell
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution
      subshell_distribution( num_tables[subshell] );


  for( unsigned n = 0; n < num_tables[subshell]; ++n )
  {
    subshell_distribution[n].first = table_energy_grid[n];

    subshell_distribution[n].second.reset( 
     new Utility::HistogramDistribution(
	  eion_block( subshell_loc + table_offset[n], table_length[n] ),
      eion_block( subshell_loc + table_offset[n] + table_length[n] + 1, 
                  table_length[n] - 1),
      true ) );
  }


  // Create the distributions
  ace_electroionization_distribution.reset(
		new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            binding_energies[subshell] ) );

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
// end tstElectroionizationSubshellElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
