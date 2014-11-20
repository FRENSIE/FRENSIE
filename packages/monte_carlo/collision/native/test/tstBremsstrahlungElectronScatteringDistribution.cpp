//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungElectronScatteringScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
  
// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectronScatteringDistribution>
  basic_bremsstrahlung_distribution;

Teuchos::RCP<MonteCarlo::ElectronScatteringDistribution>
  detailed_bremsstrahlung_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an electron can be bremsstrahlung scattered and a simple photon is generated
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   simpleBremsstrahlung )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 0.0009 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  
  unsigned shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 9.465e-03; // Sample the 7.9496800E-04 MeV distribution
  fake_stream[1] = 0.5; // Sample a photon energy of 1.49055124391153000E-05 MeV
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function 
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_bremsstrahlung_distribution->scatterElectron( electron,
						bank,
						shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 8.850944875608850E-04, 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-15 );
/*
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 1.49055124391153000e-05 , 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0557151835328 , 1e-15 );
  TEST_EQUALITY_CONST( photon.getHistoryNumber(), 1 );
*/
}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed photon
 * is generated using the lower energy function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   detailedBremsstrahlung_lower_energy )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 0.0009 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  
  unsigned shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 9.465e-03; // Sample the 7.9496800E-04 MeV distribution
  fake_stream[1] = 0.5; // Sample a photon energy of 1.49055124391153000E-05 MeV
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function  
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_bremsstrahlung_distribution->scatterElectron( electron,
						bank,
						shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 8.850944875608850E-04, 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-15 );
/*
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 1.49055124391153000e-05 , 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0557151835328 , 1e-15 );
  TEST_EQUALITY_CONST( photon.getHistoryNumber(), 1 );
*/
}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed photon 
 * is generated using the middle energy function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   detailedBremsstrahlung_middle_energy )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  
  unsigned shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 4.061e-01; // Sample the 7.9496800E-04 MeV distribution
  fake_stream[1] = 0.5; // Sample a photon energy of 1.11123878505389000E-04 MeV
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_bremsstrahlung_distribution->scatterElectron( electron,
						bank,
						shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 9.99888876121495000E-01 , 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-15 );
/*
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 1.11123878505389000E-04, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 4.999444880552E-01, 1e-15 );
  TEST_EQUALITY_CONST( photon.getHistoryNumber(), 1 );
*/
}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed photon 
 * is generated using the upper energy function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   detailedBremsstrahlung_upper_energy )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 10000 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  
  unsigned shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 9.980E-02; // Sample the upper energy distribution
  fake_stream[1] = 0.5; // Sample a photon energy of 7.19800305553610000E-02 MeV
  fake_stream[1] = 0.5; // Sample angle 0.9999999999869 from analytical function  
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_bremsstrahlung_distribution->scatterElectron( electron,
						bank,
						shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 9.99992801996944000E+03 , 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-15 );
/*
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 7.19800305553610000e-02 , 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.9999999999869 , 1e-15 );
  TEST_EQUALITY_CONST( photon.getHistoryNumber(), 1 );
*/
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

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
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
  
  // Create the tabular angular distribution
  Teuchos::Array<double> energy_bins( 3 ); // (MeV)
  energy_bins[0] = 1e-7;
  energy_bins[1] = 1.0;
  energy_bins[2] = 1e5;
  
  Teuchos::Array<double> angular_distribution_values( 3 );
  angular_distribution_values[0] =  0.0;
  angular_distribution_values[1] =  0.5;
  angular_distribution_values[2] =  1.0;

  Teuchos::RCP<Utility::OneDDistribution> angular_distribution(
			    new Utility::TabularDistribution<Utility::LinLin>( 
						energy_bins,
						angular_distribution_values ) );

  // Extract the elastic scattering information data block (BREMI)
  Teuchos::ArrayView<const double> bremi_block(
				      xss_data_extractor->extractBREMIBlock() );

  // Extract the number of tabulated distributions
  int N = bremi_block.size()/3;

  // Extract the electron energy grid for bremsstrahlung energy distributions
  Teuchos::Array<double> energy_grid(bremi_block(0,N));

  // Extract the table lengths for bremsstrahlung energy distributions
  Teuchos::Array<double> table_length(bremi_block(N,N));

  // Extract the offsets for bremsstrahlung energy distributions
  Teuchos::Array<double> offset(bremi_block(2*N,N));

  // Extract the bremsstrahlung photon energy distributions block (BREME)
  Teuchos::ArrayView<const double> breme_block = 
    xss_data_extractor->extractBREMEBlock();

  // Create the elastic scattering distributions
  Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >
    energy_loss_distribution( N );
  
  for( unsigned n = 0; n < N; ++n )
  {
    energy_loss_distribution[n].first = energy_grid[n];

    energy_loss_distribution[n].second.reset( 
	  new Utility::HistogramDistribution(
		 breme_block( offset[n], table_length[n] ),
		 breme_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );

/*	  new Utility::TabularDistribution<Utility::LinLin>(
		 breme_block( offset[n], table_length[n] ),
		 breme_block( offset[n] + table_length[n], table_length[n] ),
         true ) );     */
  }

  // Create the scattering distributions
  basic_bremsstrahlung_distribution.reset( 
		   new MonteCarlo::BremsstrahlungElectronScatteringDistribution( 
						       energy_loss_distribution ) );


  double upper_cutoff_energy = 1000;
  double lower_cutoff_energy = 0.001;

  detailed_bremsstrahlung_distribution.reset( 
		      new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
							energy_loss_distribution,
							angular_distribution,
                            lower_cutoff_energy, 
                            upper_cutoff_energy ) );

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
// end tstIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
