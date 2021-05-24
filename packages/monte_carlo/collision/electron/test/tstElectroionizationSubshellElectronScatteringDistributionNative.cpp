//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectronScatteringDistributionNative.cpp
//! \author Luke Kersting
//! \brief  Electroionization electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
  unit_base_ionization_dist, unit_correlated_ionization_dist,
  correlated_ionization_dist;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluate_unit_base_correlated )
{
  double pdf = unit_correlated_ionization_dist->evaluate( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.686600043417490087e+05, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.678581995788152526e+01, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.961132179316875043e-02, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.181582842929495631e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.463670078767589726e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.449719318262361153e-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluate_unit_base )
{
  double pdf = unit_base_ionization_dist->evaluate( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.705827064187504875e+05, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.214612295192431368e+01, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.724216068618125014e-02, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.041383244795287069e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.978639971990510892e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.449719318262361153e-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluatePDF_unit_base_correlated )
{
  double pdf = unit_correlated_ionization_dist->evaluatePDF( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.686599932174469868e+05, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.679406300200287205e+01, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.961131728313253442e-02, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.181582420161823117e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.463669219409544931e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.449717756676985891e-11, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1e5, 5e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.248089584586491624e-15, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluatePDF_unit_base )
{
  double pdf = unit_base_ionization_dist->evaluatePDF( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.705826874347286066e+05, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.214612154683611500e+01, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.724215848015932251e-02, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.041382902741912105e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.978639322085223699e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.449717756676985891e-11, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1e5, 5e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.248089584586491624e-15, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluateCDF_unit_base_correlated )
{
  double cdf = unit_correlated_ionization_dist->evaluateCDF( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9364828663505689e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9984273751835129e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9998825717709872e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9998150891124138e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9999998501226084e-01, 1e-10 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1e5, 5e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 1.0, 1e-10 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluateCDF_unit_base )
{
  double cdf = unit_base_ionization_dist->evaluateCDF( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );

  cdf = unit_base_ionization_dist->evaluateCDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9030213872906114e-01, 1e-4 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9964169418960402e-01, 1e-7 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9997873853576236e-01, 1e-10 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9996847362592778e-01, 1e-9 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9999998501226084e-01, 1e-10 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1e5, 5e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 1.0, 1e-10 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
/* Note: This tests a bug that caused electroionization to return non-realistic
 * knock-on energies. A unit based sampling routine was used to fix the problem.
 */
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sample_knock_on_native )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;         // Sample Bin
  fake_stream[1] = 0.0;         // Sample Electron
  fake_stream[2] = 0.0;         // Sample Bin
  fake_stream[3] = 1.0-1e-15;   // Sample Electron
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 6.041e-05;
  double knock_on_energy, knock_on_angle_cosine;

  // sample the electron at the min random number
  unit_base_ionization_dist->sample( incoming_energy,
                                     knock_on_energy,
                                     knock_on_angle_cosine );

  // Test knock-on electron at the min random number
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 4.0687255489257182e-02, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 1.0E-07, 1e-12 );

  // sample the electron at the max random number
  unit_base_ionization_dist->sample( incoming_energy,
                                     knock_on_energy,
                                     knock_on_angle_cosine );

  // Test knock-on electron at the max random number
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 6.7795576315906780e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 2.7765e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
/* Note: This tests a bug that caused electroionization to return non-realistic
 * knock-on energies with a correlated sampling routine.
 * The non-realistic sampled values can be rejected.
 */
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sample_knock_on_native_correlated )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 6.041e-05;
  double knock_on_energy, knock_on_angle_cosine;

  // sample the electron at the min random number
  correlated_ionization_dist->sample( incoming_energy,
                                      knock_on_energy,
                                      knock_on_angle_cosine );

  // Test knock-on electron at the min random number
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 0.0406872554892572, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 1.0E-07, 1e-12 );

  // sample the electron at the max random number
  correlated_ionization_dist->sample( incoming_energy,
                                      knock_on_energy,
                                      knock_on_angle_cosine );

  // Test knock-on electron at the max random number
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 6.680945582865936982e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 2.696314156988312136e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container
  std::unique_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container(
    new Data::ElectronPhotonRelaxationDataContainer( test_native_file_name ) );

  std::set<unsigned> subshells = data_container->getSubshells();

  unsigned subshell = *subshells.find(6);
  double binding_energy =
    data_container->getSubshellBindingEnergy( subshell );

  // Get the energies for which knock-on sampling tables are given
  std::vector<double> energy_grid =
    data_container->getElectroionizationEnergyGrid( subshell );

  // Create the scattering function
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    std::vector<double> recoil_energy(
        data_container->getElectroionizationRecoilEnergy(
            subshell,
            energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    std::vector<double> pdf(
        data_container->getElectroionizationRecoilPDF(
            subshell,
            energy_grid[n] ) );

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LogLog>( recoil_energy,
                                                               pdf ) );
  }

  {
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogLog> >(
                                                              primary_grid,
                                                              secondary_dists,
                                                              1e-6,
                                                              1e-12 ) );

  // Create the distributions
  unit_base_ionization_dist.reset(
        new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            MonteCarlo::KNOCK_ON_SAMPLING,
                            binding_energy ) );
  }
  {
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                                                              primary_grid,
                                                              secondary_dists,
                                                              1e-6,
                                                              1e-12 ) );

  // Create the distributions
  unit_correlated_ionization_dist.reset(
        new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            MonteCarlo::KNOCK_ON_SAMPLING,
                            binding_energy ) );
  }

  {
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Correlated<Utility::LogLogLog> >(
                                                             primary_grid,
                                                             secondary_dists,
                                                             1e-6,
                                                             1e-12 ) );

  // Create the distributions
  correlated_ionization_dist.reset(
        new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            MonteCarlo::KNOCK_ON_SAMPLING,
                            binding_energy ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellElectronScatteringDistributionNative.cpp
//---------------------------------------------------------------------------//
