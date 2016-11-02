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

std::shared_ptr<MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  ace_dipole_brem_dist;

std::shared_ptr<MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  tabular_brem_dist;

std::shared_ptr<MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  native_twobs_brem_dist;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the min incoming electron energy
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   getMinEnergy )
{
  TEST_EQUALITY_CONST( native_twobs_brem_dist->getMinEnergy(), 1E-5 );
}

//---------------------------------------------------------------------------//
// Check that the max incoming electron energy
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   getMaxEnergy )
{
  TEST_EQUALITY_CONST( native_twobs_brem_dist->getMaxEnergy(), 1e5 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		               evaluate )
{
  // LinLinLog interpoation used.
  double pdf = native_twobs_brem_dist->evaluate( 1.0e-5, 1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.819250066065520E+05, 1e-12 );

  pdf = native_twobs_brem_dist->evaluate( 9.0e-4, 9.0e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf, 264.26069810584175457, 1e-12 );
  // (LinLinLin) UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.54862854225938E+02, 1e-12 );

  pdf = native_twobs_brem_dist->evaluate( 1.0e5, 2.0e4 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf,
				  1.363940131180460E-06,
				  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   evaluatePDF )
{
  // LinLinLog interpoation used.
  double pdf = native_twobs_brem_dist->evaluatePDF( 1.0e-5, 1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.819250066065520E+05, 1e-12 );

  pdf = native_twobs_brem_dist->evaluatePDF( 9.0e-4, 9.0e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf, 264.26069810584175457, 1e-12 );
  // (LinLinLin) UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.54862854225938E+02, 1e-12 );

  pdf = native_twobs_brem_dist->evaluatePDF( 1.0e5, 2.0e4 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.363940131180460E-06, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   evaluateCDF )
{
  // LinLinLog interpoation used.
  double cdf = native_twobs_brem_dist->evaluateCDF( 1.0e-5, 1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( cdf, 4.974034148027E-01, 1e-12 );

  cdf = native_twobs_brem_dist->evaluateCDF( 9.0e-4, 9.0e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( cdf, 1.0, 1e-12 );

  cdf = native_twobs_brem_dist->evaluateCDF( 1.0e5, 2.0e4 );

  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.575978856479E-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a bremsstrahlung photon can be sampled from a dipole distribution
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
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

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.51612969835718E-05 , 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );
}

//---------------------------------------------------------------------------//
/* Check that a bremsstrahlung photon can be sampled and the trial number
 * recordedfrom a dipole distribution
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   sampleAndRecordTrials_DipoleBremsstrahlung )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0.0;

  double incoming_energy = 0.0009;

  double photon_energy, photon_angle_cosine;

  ace_dipole_brem_dist->sampleAndRecordTrials( incoming_energy,
                                               photon_energy,
                                               photon_angle_cosine,
                                               trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.51612969835718E-05 , 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );
  TEST_EQUALITY_CONST( trials, 1.0 );
}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a simple
 * (dipole distribution) photon is generated
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   DipoleBremsstrahlung )
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

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 8.84838703016428E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 1.51612969835718E-05 , 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0592724905908 , 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a bremsstrahlung photon can be sampled using detailed 2BS
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
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

  native_twobs_brem_dist->sample( incoming_energy,
                                  photon_energy,
                                  photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.65383677217787E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
}

//---------------------------------------------------------------------------//
/* Check that a bremsstrahlung photon can be sampled and the trial number
 * recorded using detailed 2BS
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
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

  unsigned trials = 0.0;

  double incoming_energy = 1.0;

  double photon_energy, photon_angle_cosine;

  native_twobs_brem_dist->sampleAndRecordTrials( incoming_energy,
                                                 photon_energy,
                                                 photon_angle_cosine,
                                                 trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.65383677217787E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
  TEST_EQUALITY_CONST( trials, 1.0 );
}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed 2BS
 * photon is generated
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   2BS_bremsstrahlung )
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

  native_twobs_brem_dist->scatterElectron( electron,
                                           bank,
                                           shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 9.99834616322782E-01 , 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 1.65383677217787E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.612270260118, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1 );

}

//---------------------------------------------------------------------------//
/* Check that the bremsstrahlung photon angle and energy can be sampled using
 * the lower energy function of a detailed tabular function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   sample_tabular_bremsstrahlung_lower_energy )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 0.0009;

  double photon_energy, photon_angle_cosine;

  tabular_brem_dist->sample( incoming_energy,
                             photon_energy,
                             photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.51612969835718E-05 , 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );
}

//---------------------------------------------------------------------------//
/* Check that the bremsstrahlung photon angle and energy can be sampled using
 * the middle energy function of a detailed tabular function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   sample_tabular_bremsstrahlung_middle_energy )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 9.912140279513E-03

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;

  double photon_energy, photon_angle_cosine;

  tabular_brem_dist->sample( incoming_energy,
                             photon_energy,
                             photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.65383677217787E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 1.479601055066E-02, 1e-12 );
}

//---------------------------------------------------------------------------//
/* Check that the bremsstrahlung photon angle and energy can be sampled using
 * the upper energy function of a detailed tabular function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   sample_tabular_bremsstrahlung_upper_energy )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1.22474E01 MeV and 1.0E5 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.9999999986945 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1E04;

  double photon_energy, photon_angle_cosine;

  tabular_brem_dist->sample( incoming_energy,
                             photon_energy,
                             photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 7.79788089586180000E-03, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.9999999986945, 1e-12 );
}

//---------------------------------------------------------------------------//
/* Check that the bremsstrahlung photon angle and energy can be sampled and the
 * trial number returned using the lower energy function of a detailed tabular function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   sampleAndRecordTrials_tabular_bremsstrahlung_lower_energy )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0.0;

  double incoming_energy = 0.0009;

  double photon_energy, photon_angle_cosine;

  tabular_brem_dist->sampleAndRecordTrials( incoming_energy,
                                            photon_energy,
                                            photon_angle_cosine,
                                            trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.51612969835718E-05 , 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );
  TEST_EQUALITY_CONST( trials, 1.0 );
}

//---------------------------------------------------------------------------//
/* Check that the bremsstrahlung photon angle and energy can be sampled and the
 * trial number returned using the middle energy function of a detailed tabular function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   sampleAndRecordTrials_tabular_bremsstrahlung_middle_energy )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 9.912140279513E-03

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0.0;

  double incoming_energy = 1.0;

  double photon_energy, photon_angle_cosine;

  tabular_brem_dist->sampleAndRecordTrials( incoming_energy,
                                            photon_energy,
                                            photon_angle_cosine,
                                            trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.65383677217787E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 1.479601055066E-02, 1e-12 );
  TEST_EQUALITY_CONST( trials, 1.0 );
}

//---------------------------------------------------------------------------//
/* Check that the bremsstrahlung photon angle and energy can be sampled and the
 * trial number returned using the upper energy function of a detailed tabular function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   sampleAndRecordTrials_tabular_bremsstrahlung_upper_energy )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1.22474E01 MeV and 1.0E5 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.9999999986945 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0.0;

  double incoming_energy = 1E04;

  double photon_energy, photon_angle_cosine;

  tabular_brem_dist->sampleAndRecordTrials( incoming_energy,
                                            photon_energy,
                                            photon_angle_cosine,
                                            trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 7.79788089586180000E-03, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.9999999986945, 1e-12 );
  TEST_EQUALITY_CONST( trials, 1.0 );
}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed tabular
 * photon is generated using the lower energy function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   tabular_bremsstrahlung_lower_energy )
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

  tabular_brem_dist->scatterElectron( electron, bank, shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 8.84838703016428E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 1.51612969835718E-05 , 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0592724905908 , 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1 );

}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed tabular
 * photon is generated using the middle energy function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   tabular_bremsstrahlung_middle_energy )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 9.912140279513E-03

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  tabular_brem_dist->scatterElectron( electron, bank, shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 9.99834616322782E-01 , 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 1.65383677217787E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 1.479601055066E-02, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1 );

}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed tabular
 * photon is generated using the upper energy function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   tabular_bremsstrahlung_upper_energy )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 1E04 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1.22474E01 MeV and 1.0E5 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.9999999986945 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  tabular_brem_dist->scatterElectron( electron, bank, shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 9.9999922021191E+03, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 7.79788089586180000E-03, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.9999999986945, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1 );
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
  energy_bins[0] = 1e-6;
  energy_bins[1] = 1e-2;
  energy_bins[2] = 1e5;

  //! \todo Find real bremsstrahlung photon angular distribution
  Teuchos::Array<double> angular_distribution_values( 3 );
  angular_distribution_values[0] =  0.0;
  angular_distribution_values[1] =  0.9;
  angular_distribution_values[2] =  1.0;

  std::shared_ptr<Utility::OneDDistribution> angular_distribution(
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

  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType function_data( N );

  for( unsigned n = 0; n < N; ++n )
  {
    function_data[n].first = energy_grid[n];

    Teuchos::Array<double> photon_energy( breme_block( offset[n], table_length[n]) );

    function_data[n].second.reset(
	  new Utility::HistogramDistribution(
		 photon_energy,
		 breme_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );
  }

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_distribution(
        new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            function_data ) );

  // Create the scattering distributions
  ace_dipole_brem_dist.reset(
    new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
      scattering_distribution ) );


  double upper_cutoff_energy = 1000;
  double lower_cutoff_energy = 0.001;

  tabular_brem_dist.reset(
    new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
      scattering_distribution,
      angular_distribution,
      lower_cutoff_energy,
      upper_cutoff_energy ) );

  native_twobs_brem_dist.reset(
    new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
      scattering_distribution,
      xss_data_extractor->extractAtomicNumber() ) );

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
