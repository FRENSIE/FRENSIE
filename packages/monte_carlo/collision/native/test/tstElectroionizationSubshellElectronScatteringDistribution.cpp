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
  MonteCarlo::SubshellType shell_of_interaction;
  
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  std::cout << " number of particles = " << bank.size() << std::endl;

  // Analytically scatter electron
  ace_electroionization_distribution->scatterElectron( electron, 
                                                   bank, 
                                                   shell_of_interaction );

  std::cout << " number of particles = " << bank.size() << std::endl;
  std::cout << " top of bank = " << bank.top()->getEnergy() << std::endl;

  // Test original electron
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 9.589473789423E-01, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( bank.top()->getZDirection(), 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top()->getEnergy(), 4.105262105768E-02, 1e-12 );

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

  // Extract the subshell cross sections
  Teuchos::ArrayView<const double> electroionization_subshell_cross_sections =
    xss_data_extractor->extractElectroionizationSubshellCrossSections();

  // Extract the cross sections energy grid
  Teuchos::ArrayView<const double> energy_grid =
    xss_data_extractor->extractElectronEnergyGrid() ;

  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators = 
    xss_data_extractor->extractSubshellENDFDesignators();

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
  unsigned shell = 0;

  // Shell table info realtive to the EION Block
  unsigned shell_info = table_info[shell]- eion_loc - 1;

  // Shell table loc realtive to the EION Block
  unsigned shell_loc = table_loc[shell]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  Teuchos::Array<double> table_energy_grid(eion_block( 
                                                    shell_info,
                                                    num_tables[shell] ) );

  // Extract the length of the knock-on sampling tables
  Teuchos::Array<double> table_length(eion_block( 
                               shell_info + num_tables[shell],
                               num_tables[shell] ) );

  // Extract the offset of the knock-on sampling tables
  Teuchos::Array<double> table_offset(eion_block( 
                             shell_info + 2*num_tables[shell],
                             num_tables[shell] ) );
   // Create the electroionization sampling table for the subshell
//  Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution
      subshell_distribution( num_tables[shell] );

std::cout << "# of tables = " << table_energy_grid.size() << std::endl;
std::cout << "shell_info = " << shell_info << std::endl;
std::cout << "shell_loc = " << shell_loc << std::endl;
std::cout << "eion_loc = " << eion_loc << std::endl;

  for( unsigned n = 0; n < num_tables[shell]; ++n )
  {

std::cout << "table_energy_grid[n] = " << table_energy_grid[n] << std::endl;
std::cout << "table_length[n] = " << table_length[n] << std::endl;
std::cout << "table_loc[shell] + table_offset[n] = " << table_loc[shell]+ table_offset[n] << std::endl;

    subshell_distribution[n].first = table_energy_grid[n];

    subshell_distribution[n].second.reset( 
     new Utility::HistogramDistribution(
	  eion_block( shell_loc + table_offset[n], table_length[n] ),
      eion_block( shell_loc + table_offset[n] + table_length[n] + 1, 
                  table_length[n] - 1),
      true ) );
  }


  // Create the distributions
  ace_electroionization_distribution.reset(
		new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution ) );

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
