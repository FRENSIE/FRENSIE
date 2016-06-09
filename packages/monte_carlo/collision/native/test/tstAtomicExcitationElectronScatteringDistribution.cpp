//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::AtomicExcitationElectronScatteringDistribution>
  ace_atomic_excitation_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
TEUCHOS_UNIT_TEST( AtomicExcitationElectronScatteringDistribution,
                   sample )
{

  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.000000000000e-03 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  double final_energy = (electron.getEnergy() - 9.32298000000E-06);

  // sample distribution
  ace_atomic_excitation_distribution->sample( electron.getEnergy(),
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( outgoing_energy,final_energy, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
TEUCHOS_UNIT_TEST( AtomicExcitationElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.000000000000e-03 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  double final_energy = (electron.getEnergy() - 9.32298000000E-06);
  unsigned trials = 10;

  // sample distribution
  ace_atomic_excitation_distribution->sampleAndRecordTrials(
                                           electron.getEnergy(),
                                           outgoing_energy,
                                           scattering_angle_cosine,
                                           trials );

  // Test
  TEST_FLOATING_EQUALITY( outgoing_energy,final_energy, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );
  TEST_EQUALITY_CONST( trials, 11 );

}
//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( AtomicExcitationElectronScatteringDistribution,
                   scatterElectron )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.000000000000e-03 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;
  double final_energy = (electron.getEnergy() - 9.32298000000E-06);

  // Scatter the electron
  ace_atomic_excitation_distribution->scatterElectron( electron,
	                                               bank,
                                                       shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( electron.getEnergy(), final_energy, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

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

  // Extract the atomic excitation information data block (EXCIT)
  Teuchos::ArrayView<const double> excit_block(
				      xss_data_extractor->extractEXCITBlock() );

  // Extract the number of tabulated energies
  int size = excit_block.size()/2;

  // Extract the energy grid for atomic excitation energy loss
  Teuchos::Array<double> energy_grid(excit_block(0,size));

  // Extract the energy loss for atomic excitation
  Teuchos::Array<double> energy_loss(excit_block(size,size));

  // Create the energy loss distributions
  Teuchos::RCP<Utility::OneDDistribution> energy_loss_function;

  energy_loss_function.reset(
    new Utility::TabularDistribution<Utility::LinLin>( energy_grid,
	                                               energy_loss ) );

  // Create the distribution
  ace_atomic_excitation_distribution.reset(
    new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
						       energy_loss_function ) );

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
// end tstAtomicExcitationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
