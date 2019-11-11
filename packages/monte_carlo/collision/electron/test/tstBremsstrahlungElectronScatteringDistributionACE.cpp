//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungElectronScatteringDistributionACE.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  ace_dipole_brem_dist, twobs_brem_dist;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the min incoming electron energy
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution, getMinEnergy )
{
  FRENSIE_CHECK_EQUAL( twobs_brem_dist->getMinEnergy(), 1E-5 );
}

//---------------------------------------------------------------------------//
// Check that the max incoming electron energy
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution, getMaxEnergy )
{
  FRENSIE_CHECK_EQUAL( twobs_brem_dist->getMaxEnergy(), 1e5 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution, evaluate_ace )
{
  // LinLinLin interpolation used.
  double pdf = twobs_brem_dist->evaluate( 1.0e-5, 1.0e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.819250066065521386e5, 1e-12 );

  pdf = twobs_brem_dist->evaluate( 9.0e-4, 9.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.0746668573912197e+02, 1e-12 );

  pdf = twobs_brem_dist->evaluate( 1.0e5, 2.0e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.36394013118046E-06, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution, evaluatePDF_ace )
{
  // LinLinLin interpolation used.
  double pdf = twobs_brem_dist->evaluatePDF( 1.0e-5, 1.0e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.819250066065521386e5, 1e-12 );

  pdf = twobs_brem_dist->evaluatePDF( 9.0e-4, 9.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.0746668573912197e+02, 1e-12 );

  pdf = twobs_brem_dist->evaluatePDF( 1.0e5, 2.0e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.36394013118046E-06, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   evaluateCDF_ace )
{
  // LinLinLin interpolation used.
  double cdf = twobs_brem_dist->evaluateCDF( 1.0e-5, 1.0e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 4.974034148027E-01, 1e-12 );

  cdf = twobs_brem_dist->evaluateCDF( 9.0e-4, 9.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 1.0, 1e-12 );

  cdf = twobs_brem_dist->evaluateCDF( 1.0e5, 2.0e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.575978856479E-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a bremsstrahlung photon can be sampled from a dipole distribution
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   sample_DipoleBremsstrahlung )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  ace_dipole_brem_dist->sample( incoming_energy,
                                photon_energy,
                                photon_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.51612969835718E-05 , 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
/* Check that a bremsstrahlung photon can be sampled and the trial number
 * recordedfrom a dipole distribution
 */
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   sampleAndRecordTrials_DipoleBremsstrahlung )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronScatteringDistribution::Counter trials = 0.0;

  double incoming_energy = 0.0009;

  double photon_energy, photon_angle_cosine;

  ace_dipole_brem_dist->sampleAndRecordTrials( incoming_energy,
                                               photon_energy,
                                               photon_angle_cosine,
                                               trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.51612969835718E-05 , 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a simple
 * (dipole distribution) photon is generated
 */
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   scatterElectron_DipoleBremsstrahlung )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 0.0009 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_dipole_brem_dist->scatterElectron( electron, bank, shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 8.84838703016428E-04, 1e-12 );
  FRENSIE_CHECK_SMALL( electron.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( electron.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 1.51612969835718E-05 , 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0592724905908 , 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a bremsstrahlung photon can be sampled using detailed 2BS
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   sample_2BS_bremsstrahlung )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[4] = 0.48; // Accept the angle


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;

  double photon_energy, photon_angle_cosine;

  twobs_brem_dist->sample( incoming_energy,
                                  photon_energy,
                                  photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.65383677217787E-04, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
}

//---------------------------------------------------------------------------//
/* Check that a bremsstrahlung photon can be sampled and the trial number
 * recorded using detailed 2BS
 */
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   sampleAndRecordTrials_2BS_bremsstrahlung )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[4] = 0.48; // Accept the angle

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronScatteringDistribution::Counter trials = 0.0;

  double incoming_energy = 1.0;

  double photon_energy, photon_angle_cosine;

  twobs_brem_dist->sampleAndRecordTrials( incoming_energy,
                                          photon_energy,
                                          photon_angle_cosine,
                                          trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.65383677217787E-04, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 1.0 );
}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed 2BS
 * photon is generated
 */
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   scatterElectron_2BS_bremsstrahlung )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[4] = 0.48; // Accept the angle


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  twobs_brem_dist->scatterElectron( electron,
                                    bank,
                                    shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 9.99834616322782E-01 , 1e-12 );
  FRENSIE_CHECK_SMALL( electron.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( electron.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 1.65383677217787E-04, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 0.612270260118, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 1 );

}

//---------------------------------------------------------------------------//
/* Check that an positron can be bremsstrahlung scattered and a simple
 * (dipole distribution) photon is generated
 */
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   scatterPositron_DipoleBremsstrahlung )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PositronState positron( 1 );
  positron.setEnergy( 0.0009 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_dipole_brem_dist->scatterPositron( positron, bank, shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 8.84838703016428E-04, 1e-12 );
  FRENSIE_CHECK_SMALL( positron.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( positron.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 1.0, 1e-12 );

  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 1.51612969835718E-05 , 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0592724905908 , 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 1 );
}

//---------------------------------------------------------------------------//
/* Check that an positron can be bremsstrahlung scattered and a detailed 2BS
 * photon is generated
 */
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   scatterPositron_2BS_bremsstrahlung )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PositronState positron( 1 );
  positron.setEnergy( 1.0 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[4] = 0.48; // Accept the angle


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  twobs_brem_dist->scatterPositron( positron,
                                    bank,
                                    shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 9.99834616322782E-01 , 1e-12 );
  FRENSIE_CHECK_SMALL( positron.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( positron.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 1.0, 1e-12 );

  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 1.65383677217787E-04, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 0.612270260118, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 1 );

}

//---------------------------------------------------------------------------//
// Custom setup
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

  // Extract the elastic scattering information data block (BREMI)
  Utility::ArrayView<const double> bremi_block(
                                        xss_data_extractor->extractBREMIBlock() );

  // Extract the number of tabulated distributions
  int N = bremi_block.size()/3;
  
  // Extract the electron energy grid for bremsstrahlung energy distributions
  std::vector<double> energy_grid(bremi_block(0,N));
  
  // Extract the table lengths for bremsstrahlung energy distributions
  std::vector<double> table_length(bremi_block(N,N));
  
  // Extract the offsets for bremsstrahlung energy distributions
  std::vector<double> offset(bremi_block(2*N,N));
  
  // Extract the bremsstrahlung photon energy distributions block (BREME)
  Utility::ArrayView<const double> breme_block =
    xss_data_extractor->extractBREMEBlock();
  
  // Create the scattering function
  std::vector<double> primary_grid( N );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( N );

  for( unsigned n = 0; n < N; ++n )
  {
    primary_grid[n] = energy_grid[n];
    
    std::vector<double> photon_energy( breme_block( offset[n], table_length[n]) );
    
    secondary_dists[n].reset(
          new Utility::HistogramDistribution(
                photon_energy,
                breme_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
                true ) );
  }

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> scattering_distribution(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLin> >(
                                                           primary_grid,
                                                           secondary_dists ) );
  
  // Create the scattering distributions
  ace_dipole_brem_dist.reset(
      new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
          scattering_distribution ) );

  twobs_brem_dist.reset(
      new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
          xss_data_extractor->extractAtomicNumber(),
          scattering_distribution ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungElectronScatteringDistributionACE.cpp
//---------------------------------------------------------------------------//
