//---------------------------------------------------------------------------//
//!
//! \file   tstAnalogElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Analog elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronTraits.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_AnalogElasticDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestAnalogElasticElectronScatteringDistribution : public MonteCarlo::AnalogElasticElectronScatteringDistribution
{
public:
  TestAnalogElasticElectronScatteringDistribution(
    const std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
        elastic_cutoff_distribution,
    const std::shared_ptr<const Utility::OneDDistribution>& cutoff_cross_section_ratios,
    const std::shared_ptr<const MonteCarlo::ElasticElectronTraits>& screened_rutherford_traits,
    const bool correlated_sampling_mode_on )
    : MonteCarlo::AnalogElasticElectronScatteringDistribution(
        elastic_cutoff_distribution,
        cutoff_cross_section_ratios,
        screened_rutherford_traits,
        correlated_sampling_mode_on )
  { /* ... */ }

  ~TestAnalogElasticElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the AnalogElasticElectronScatteringDistribution protected member functions
  using MonteCarlo::AnalogElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl;
  using MonteCarlo::AnalogElasticElectronScatteringDistribution::evaluateScreenedRutherfordPDF;
  using MonteCarlo::AnalogElasticElectronScatteringDistribution::evaluateScreenedRutherfordCDF;

};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AnalogElasticElectronScatteringDistribution>
  distribution, lin_distribution;

std::shared_ptr<TestAnalogElasticElectronScatteringDistribution>
  test_distribution, test_lin_distribution;

////---------------------------------------------------------------------------//
//// LinLinLog Tests
////---------------------------------------------------------------------------//
//// Check that the distribution can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   evaluate )
//{
//  // Set energy in MeV
//  double energy = 1.0e+5;
//  double scattering_angle_cosine = -0.01;
//  double value;

//  {
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 1 energy 1
//  TEST_FLOATING_EQUALITY( value, 4.9148915165877459e-16, 1e-12 );

//  scattering_angle_cosine = 0.71;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 2 energy 1
//  TEST_FLOATING_EQUALITY( value, 1.0263914537004669e-14, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 3 energy 1
//  TEST_FLOATING_EQUALITY( value, 1.0032404164247587e-03, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 4 energy 1
//  TEST_FLOATING_EQUALITY( value, 9.9677004793195188e+14, 1e-12 );
//  }
//  {
//  // Test with a different energy
//  energy = 6.625E+01;

//  scattering_angle_cosine = -0.01;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 1 energy 2
//  TEST_FLOATING_EQUALITY( value, 1.1028348687574122e-09, 1e-12 );

//  scattering_angle_cosine = 0.71;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 2 energy 2
//  TEST_FLOATING_EQUALITY( value, 2.3029743461131859e-08, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 3 energy 2
//  TEST_FLOATING_EQUALITY( value, 2.2409028351511301e+03, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 4 energy 2
//  TEST_FLOATING_EQUALITY( value, 4.4422005494954091e+08, 1e-12 );
//  }
//  {
//  // Test inbetween the two energies
//  energy = 200.0;

//  scattering_angle_cosine = -0.01;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 1 energy 3
//  TEST_FLOATING_EQUALITY( value, 1.2267740656596080e-10, 1e-12 );

//  scattering_angle_cosine = 0.0;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 2 energy 3
//  TEST_FLOATING_EQUALITY( value, 1.2732591553615765e-10, 1e-12 );

//  scattering_angle_cosine = 0.71;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 3 energy 3
//  TEST_FLOATING_EQUALITY( value, 2.5620450599249141e-09, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 4 energy 3
//  TEST_FLOATING_EQUALITY( value, 2.4941206012684930e+02, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 5 energy 3
//  TEST_FLOATING_EQUALITY( value, 4.0073991862833123e+09, 1e-12 );
//  }
//}

////---------------------------------------------------------------------------//
//// Check that the pdf can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   evaluatePDF )
//{
//  // Set energy in MeV
//  double energy = 1.0e+5;
//  double scattering_angle_cosine = -0.01;
//  double value;

//  {
//  value =
//    distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 1 energy 1
//  TEST_FLOATING_EQUALITY( value, 4.9148915165877469e-16, 1e-12 );

//  scattering_angle_cosine = .71;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 2 energy 1
//  TEST_FLOATING_EQUALITY( value, 1.0263914537004671e-14, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 3 energy 1
//  TEST_FLOATING_EQUALITY( value, 1.0032404164247587e-03, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 4 energy 1
//  TEST_FLOATING_EQUALITY( value, 9.9677004793195188e+14, 1e-12 );
//  }
//  {
//  // Test with a different energy
//  energy = 6.625E+01;

//  scattering_angle_cosine = -0.01;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 1 energy 2
//  TEST_FLOATING_EQUALITY( value, 1.1028348675446878e-09, 1e-12 );

//  scattering_angle_cosine = 0.71;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 2 energy 2
//  TEST_FLOATING_EQUALITY( value, 2.3029743435807368e-08, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 3 energy 2
//  TEST_FLOATING_EQUALITY( value, 2.2409028326869375e+03, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 4 energy 2
//  TEST_FLOATING_EQUALITY( value, 4.4422005446105748e+08, 1e-12 );
//  }
//  {
//  // Test inbetween the two energies
//  energy = 2.00E+02;

//  scattering_angle_cosine = -0.01;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 1 energy 3
//  TEST_FLOATING_EQUALITY( value, 1.2267740653920285e-10, 1e-12 );

//  scattering_angle_cosine = 0.0;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 1 energy 3
//  TEST_FLOATING_EQUALITY( value, 1.2732591550869694e-10, 1e-12 );

//  scattering_angle_cosine = 0.71;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 2 energy 3
//  TEST_FLOATING_EQUALITY( value, 2.5620450596029448e-09, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 3 energy 3
//  TEST_FLOATING_EQUALITY( value, 2.4941206010085943e+02, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 4 energy 3
//  TEST_FLOATING_EQUALITY( value, 4.0073991858657231e+09, 1e-12 );
//  }
//}

////---------------------------------------------------------------------------//
//// Check that the screened Rutherford pdf can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   evaluateScreenedRutherfordPDF )
//{
//  double tol = 1.0e-12;
//  double eta = 1.0;
//  double cutoff_pdf = 1.0;
//  double cutoff_cdf = 0.5;

//  // Test
//  double scattering_angle_cosine = 0.999999;
//  double pdf_value = test_distribution->evaluateScreenedRutherfordPDF(
//                        scattering_angle_cosine,
//                        eta,
//                        cutoff_pdf,
//                        cutoff_cdf );
//  TEST_FLOATING_EQUALITY( pdf_value, 0.5, tol );

//  // Test
//  scattering_angle_cosine = 0.9999995;
//  pdf_value = test_distribution->evaluateScreenedRutherfordPDF(
//                        scattering_angle_cosine,
//                        eta,
//                        cutoff_pdf,
//                        cutoff_cdf );
//  TEST_FLOATING_EQUALITY( pdf_value, 0.5000005, tol );

//  // Test
//  scattering_angle_cosine = 1.0;
//  pdf_value = test_distribution->evaluateScreenedRutherfordPDF(
//                        scattering_angle_cosine,
//                        eta,
//                        cutoff_pdf,
//                        cutoff_cdf );
//  TEST_FLOATING_EQUALITY( pdf_value, 0.500001, tol );
//}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateCDF )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  // Test 1 energy 1
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.5194151539596018523e-16, 1e-12 );

  // Test 2 energy 1
  scattering_angle_cosine = 0.71;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.0228604997734523684e-15, 1e-12 );

  // Test 3 energy 1
  scattering_angle_cosine = 0.999995;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.0215493910276143181e-10, 1e-12 );

  // Test 4 energy 1
  scattering_angle_cosine = 0.999999;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0100484326755010891e-09, 1e-12 );

  // Test 5 energy 1
  scattering_angle_cosine = 1.0;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  // Test 1 energy 2
  scattering_angle_cosine = -0.01;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.4087717596560064879e-10, 1e-12 );

  // Test 2 energy 2
  scattering_angle_cosine = 0.71;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.5377719565224249441e-09, 1e-12 );

  // Test 3 energy 2
  scattering_angle_cosine = 0.999995;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.532637899374508195e-04, 1e-12 );

  // Test 4 energy 2
  scattering_angle_cosine = 0.999999;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.2605795488167450616e-03, 1e-12 );
std::cout << std::setprecision(20) << "cdf (" << scattering_angle_cosine << ") = " << value << std::endl;
  // Test 5 energy 2
  scattering_angle_cosine = 1.0;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test inbetween the two energies
  energy = 2.00E+02;
std::cout << std::setprecision(20) << "\ncdf at cutoff = " << distribution->evaluateCDFAtCutoff( energy ) << std::endl;
  // Test 1 energy 3
  scattering_angle_cosine = -0.01;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value,  1.8586865689420059512e-10, 1e-12 );
std::cout << std::setprecision(20) << "cdf (" << scattering_angle_cosine << ") = " << value << std::endl;
  // Test 1 energy 3
  scattering_angle_cosine = 0.0;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.9372483706177144234e-10, 1e-12 );
std::cout << std::setprecision(20) << "cdf (" << scattering_angle_cosine << ") = " << value << std::endl;
  // Test 2 energy 3
  scattering_angle_cosine = 0.71;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.5347746472730750536e-09, 1e-12 );
std::cout << std::setprecision(20) << "cdf (" << scattering_angle_cosine << ") = " << value << std::endl;
  // Test 3 energy 3
  scattering_angle_cosine = 0.999995;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.8487615166561635121e-04, 1e-12 );
std::cout << std::setprecision(20) << "cdf (" << scattering_angle_cosine << ") = " << value << std::endl;
  // Test 4 energy 3
  scattering_angle_cosine = 0.999999;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.5106038136353921652e-04, 1e-12 );
std::cout << std::setprecision(20) << "cdf (" << scattering_angle_cosine << ") = " << value << std::endl;
  // Test 5 energy 3
  scattering_angle_cosine = 1.0;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford cdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordCDF )
{
  double tol = 1e-10;
  double eta = 1.0;
  double cutoff_pdf = 1.0;
  double cutoff_cdf = 0.5;

  // Test
  double scattering_angle_cosine = 0.999999;
  double cdf_value = test_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  TEST_FLOATING_EQUALITY( cdf_value, 0.5, tol );

  // Test
  scattering_angle_cosine = 0.9999995;
  cdf_value = test_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  TEST_FLOATING_EQUALITY( cdf_value, 0.749999875000063, tol );

  // Test with a different energy
  scattering_angle_cosine = 1.0;
  cdf_value = test_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773296016569724e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999899973959993638e-01
  fake_stream[2] = 2.2605795488167450616e-3; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774879678e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773296016569724e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999899973959993638e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );
  // sampleAndRecordTrialsImpl from distribution
  test_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774879678e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 14 );

  // sampleAndRecordTrialsImpl from distribution
  test_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( trials, 15 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   sample )
{
  // Set up the electron
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773296016569724e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999899973959993638e-01
  fake_stream[2] = 2.2605795488167450616e-3; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774879678e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773296016569724e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999899973959993638e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774879678e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );


  // Test energy inbetween energy bins
  electron.setEnergy( 1e-4 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Set fake random number stream
  fake_stream[0] = 1.0e-3; // sample mu = -0.85537934174508756247
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 0.999999
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.85537934174508756247, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 4.9274826288429413035e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.9913094173895369288e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );

  // Test energy inbetween energy bins
  electron.setEnergy( 2e2 );
  electron.setDirection( 0.0, 0.0, 1.0 );
std::cout << std::setprecision(20) << "\ncdf at cutoff = " << distribution->evaluateCDFAtCutoff( 2e2 ) << std::endl;
  // Set fake random number stream
  fake_stream[0] = 1.0e-5; // sample mu = 0.99980737913598205502
  fake_stream[1] = 1.0e-4; // sample mu = 0.99998073331622627791
  fake_stream[2] = 2.5106038136353917e-04; // sample mu = 0.999999
  fake_stream[3] = 2.5106038136353921652e-04; // sample mu = 0.999999
  fake_stream[4] = 2.5106038136353916e-04; //1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99980737913598205502, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );
std::cout << std::setprecision(20) << "angle = " << scattering_angle_cosine << std::endl;
  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99998073331622627791, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );
std::cout << std::setprecision(20) << "angle = " << scattering_angle_cosine << std::endl;
  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );
std::cout << std::setprecision(20) << "angle = " << scattering_angle_cosine << std::endl;
  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );
std::cout << std::setprecision(20) << "angle = " << scattering_angle_cosine << std::endl;
  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );
std::cout << std::setprecision(20) << "angle = " << scattering_angle_cosine << std::endl;
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774879678e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  distribution->sampleAndRecordTrials( electron.getEnergy(),
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774879678e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   ScatterElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774879678e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  distribution->scatterElectron( electron,
                                 bank,
                                 shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.9999999774879678e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 6.625E+01, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   ScatterAdjointElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774879678e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 6.625E+01 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  distribution->scatterAdjointElectron(
        adjoint_electron,
        bank,
        shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          9.9999999774879678e-01,
                          1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 6.625E+01, 1e-12 );
}

////---------------------------------------------------------------------------//
//// LinLinLin Tests
////---------------------------------------------------------------------------//
//// Check that the distribution can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   evaluate_lin )
//{
//  // Set energy in MeV
//  double energy = 1.0e+5;
//  double scattering_angle_cosine = -0.01;
//  double value;

//  {
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 1 energy 1
//  TEST_FLOATING_EQUALITY( value, 4.9148915165877459e-16, 1e-12 );

//  scattering_angle_cosine = 0.71;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 2 energy 1
//  TEST_FLOATING_EQUALITY( value, 1.0263914537004669e-14, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 3 energy 1
//  TEST_FLOATING_EQUALITY( value, 1.0032404164247587e-03, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 4 energy 1
//  TEST_FLOATING_EQUALITY( value, 9.9677004793195188e+14, 1e-12 );
//  }
//  {
//  // Test with a different energy
//  energy = 6.625E+01;

//  scattering_angle_cosine = -0.01;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 1 energy 2
//  TEST_FLOATING_EQUALITY( value, 1.1028348687574122e-09, 1e-12 );

//  scattering_angle_cosine = 0.71;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 2 energy 2
//  TEST_FLOATING_EQUALITY( value, 2.3029743461131859e-08, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 3 energy 2
//  TEST_FLOATING_EQUALITY( value, 2.2409028351511301e+03, 1e-12 );


//  scattering_angle_cosine = 1.0;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 4 energy 2
//  TEST_FLOATING_EQUALITY( value, 4.4422005494954091e+08, 1e-12 );
//  }
//  {
//  // Test inbetween the two energies
//  energy = 200.0;

//  scattering_angle_cosine = -0.01;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 1 energy 3
//  TEST_FLOATING_EQUALITY( value, 1.2274472463816009e-10, 1e-12 );

//  scattering_angle_cosine = 0.0;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 1 energy 3
//  TEST_FLOATING_EQUALITY( value, 1.2741278936395448e-10, 1e-12 );

//  scattering_angle_cosine = 0.71;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 2 energy 3
//  TEST_FLOATING_EQUALITY( value, 2.5631964706096331e-09, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 3 energy 3
//  TEST_FLOATING_EQUALITY( value, 2.4941203909677358e+02, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
//  // Test 4 energy 3
//  TEST_FLOATING_EQUALITY( value, 4.0073988483850236e+09, 1e-12 );
//  }
//}

////---------------------------------------------------------------------------//
//// Check that the pdf can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   evaluatePDF_lin )
//{
//  // Set energy in MeV
//  double energy = 1.0e+5;
//  double scattering_angle_cosine = -0.01;

//  double value =
//    lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 1 energy 1
//  TEST_FLOATING_EQUALITY( value, 4.9148915165877469e-16, 1e-12 );

//  scattering_angle_cosine = 0.71;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 2 energy 1
//  TEST_FLOATING_EQUALITY( value, 1.0263914537004671e-14, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 3 energy 1
//  TEST_FLOATING_EQUALITY( value, 1.0032404164247587e-03, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 4 energy 1
//  TEST_FLOATING_EQUALITY( value, 9.9677004793195188e+14, 1e-12 );

//  // Test with a different energy
//  energy = 6.625E+01;

//  scattering_angle_cosine = -0.01;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 1 energy 2
//  TEST_FLOATING_EQUALITY( value, 1.1028348675446878e-09, 1e-12 );

//  scattering_angle_cosine = 0.71;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 2 energy 2
//  TEST_FLOATING_EQUALITY( value, 2.3029743435807368e-08, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 3 energy 2
//  TEST_FLOATING_EQUALITY( value, 2.2409028326869375e+03, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 4 energy 2
//  TEST_FLOATING_EQUALITY( value, 4.4422005446105748e+08, 1e-12 );

//  // Test inbetween the two energies
//  energy = 2.00E+02;

//  scattering_angle_cosine = -0.01;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 1 energy 3
//  TEST_FLOATING_EQUALITY( value, 1.2274472462302344e-10, 1e-12 );

//  scattering_angle_cosine = 0.0;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 2 energy 3
//  TEST_FLOATING_EQUALITY( value, 1.2741278934823265e-10, 1e-12 );
//  scattering_angle_cosine = 0.71;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 2 energy 3
//  TEST_FLOATING_EQUALITY( value, 2.5631964702961900e-09, 1e-12 );

//  scattering_angle_cosine = 0.999999;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 3 energy 3
//  TEST_FLOATING_EQUALITY( value, 2.4941203906628823e+02, 1e-12 );

//  scattering_angle_cosine = 1.0;
//  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
//  // Test 4 energy 3
//  TEST_FLOATING_EQUALITY( value, 4.0073988478952036e+09, 1e-12 );
//}

////---------------------------------------------------------------------------//
//// Check that the cdf can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   evaluateCDF_lin )
//{
//  // Set energy in MeV
//  double energy = 1.0e+5;
//  double scattering_angle_cosine = -0.01;
//  double value;

//  // Test 1 energy 1
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 1.5291367543337785e-16, 1e-12 );

//  // Test 2 energy 1
//  scattering_angle_cosine = 0.71;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 2.0358032701152229e-15, 1e-12 );

//  // Test 3 energy 1
//  scattering_angle_cosine = 0.999999;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 1.0165109766322634e-09, 1e-12 );

//  // Test 4 energy 1
//  scattering_angle_cosine = 1.0;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

//  // Test with a different energy
//  energy = 6.625E+01;

//  // Test 1 energy 2
//  scattering_angle_cosine = -0.01;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 3.4314213722037488e-10, 1e-12 );

//  // Test 2 energy 2
//  scattering_angle_cosine = 0.71;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 4.5679232203476135e-09, 1e-12 );

//  // Test 3 energy 2
//  scattering_angle_cosine = 0.999999;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 2.2755999885892267e-03, 1e-12 );

//  // Test 4 energy 2
//  scattering_angle_cosine = 1.0;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

//  // Test inbetween the two energies
//  energy = 2.00E+02;

//  // Test 1 energy 3
//  scattering_angle_cosine = -0.01;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 3.8191414917559124e-11, 1e-12 );

//  // Test 2 energy 3
//  scattering_angle_cosine = 0.0;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 3.9442201622592641e-11, 1e-12 );

//  // Test 3 energy 3
//  scattering_angle_cosine = 0.71;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 5.0840586615198269e-10, 1e-12 );

//  // Test 4 energy 3
//  scattering_angle_cosine = 0.999999;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 2.5327307090551652e-04, 1e-12 );

//  // Test 5 energy 3
//  scattering_angle_cosine = 1.0;
//  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );
//}

////---------------------------------------------------------------------------//
//// Check that sampleAndRecordTrialsImpl can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   sampleAndRecordTrialsImpl_lin )
//{
//  // Set fake random number stream
//  std::vector<double> fake_stream( 3 );
//  fake_stream[0] = 1.0e-3; // sample mu =  9.9999771799523429e-01
//  fake_stream[1] = 0.5; // sample mu = 9.9999999774879678e-01
//  fake_stream[2] = 1.0 - 1e-15; // sample mu = 1.0

//  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//  MonteCarlo::ElectronState electron( 0 );
//  electron.setEnergy( 6.625e1 );
//  electron.setDirection( 0.0, 0.0, 1.0 );

//  double scattering_angle_cosine;
//  unsigned trials = 10;

//  // sampleAndRecordTrialsImpl from lin_distribution
//  test_lin_distribution->sampleAndRecordTrialsImpl(
//                                    electron.getEnergy(),
//                                    scattering_angle_cosine,
//                                    trials );
//  // Test
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999771799523429e-01, 1e-12 );
//  TEST_EQUALITY_CONST( trials, 11 );

//  // sampleAndRecordTrialsImpl from lin_distribution
//  test_lin_distribution->sampleAndRecordTrialsImpl(
//                                    electron.getEnergy(),
//                                    scattering_angle_cosine,
//                                    trials );
//  // Test
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774879678e-01, 1e-12 );
//  TEST_EQUALITY_CONST( trials, 12 );

//  // sampleAndRecordTrialsImpl from lin_distribution
//  test_lin_distribution->sampleAndRecordTrialsImpl(
//                                    electron.getEnergy(),
//                                    scattering_angle_cosine,
//                                    trials );
//  // Test
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
//  TEST_EQUALITY_CONST( trials, 13 );
//}

////---------------------------------------------------------------------------//
//// Check sample can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   sample_lin )
//{
//  // Set fake random number stream
//  std::vector<double> fake_stream( 2 );
//  fake_stream[0] = 0.5; // sample mu = 9.9999999774879678e-01
//  fake_stream[1] = 0.5; // sample mu = 8.9590792171902925e-02

//  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//  MonteCarlo::ElectronState electron( 0 );
//  electron.setEnergy( 6.625e1 );
//  electron.setDirection( 0.0, 0.0, 1.0 );

//  double scattering_angle_cosine, outgoing_energy;

//  // sampleAndRecordTrialsImpl from lin_distribution
//  lin_distribution->sample( electron.getEnergy(),
//                            outgoing_energy,
//                            scattering_angle_cosine );

//  // Test
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774879678e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );


//  // Test energy inbetween energy bins
//  electron.setEnergy( 1e-4 );
//  electron.setDirection( 0.0, 0.0, 1.0 );

//  // sampleAndRecordTrialsImpl from lin_distribution
//  lin_distribution->sample( electron.getEnergy(),
//                            outgoing_energy,
//                            scattering_angle_cosine );

//  // Test
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.9590792171902925e-02, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );
//}

////---------------------------------------------------------------------------//
//// Check sampleAndRecordTrials can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   sampleAndRecordTrials_lin )
//{
//  // Set fake random number stream
//  std::vector<double> fake_stream( 1 );
//  fake_stream[0] = 0.5; // sample mu = 9.9999999774879678e-01

//  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//  MonteCarlo::ElectronState electron( 0 );
//  electron.setEnergy( 6.625E+01 );
//  electron.setDirection( 0.0, 0.0, 1.0 );

//  double scattering_angle_cosine, outgoing_energy;
//  unsigned trials = 10;

//  // sampleAndRecordTrialsImpl from distribution
//  lin_distribution->sampleAndRecordTrials( electron.getEnergy(),
//                                           outgoing_energy,
//                                           scattering_angle_cosine,
//                                           trials );

//  // Test
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774879678e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
//}

////---------------------------------------------------------------------------//
//// Check that the angle can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   ScatterElectron_lin )
//{
//  // Set fake random number stream
//  std::vector<double> fake_stream( 1 );
//  fake_stream[0] = 0.5; // sample mu = 9.9999999774879678e-01

//  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//  MonteCarlo::ParticleBank bank;
//  Data::SubshellType shell_of_interaction;

//  MonteCarlo::ElectronState electron( 0 );
//  electron.setEnergy( 6.625E+01 );
//  electron.setDirection( 0.0, 0.0, 1.0 );

//  // Analytically scatter electron
//  lin_distribution->scatterElectron( electron, bank, shell_of_interaction );

//  // Test
//  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.9999999774879678e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( electron.getEnergy(), 6.625E+01, 1e-12 );

//}

////---------------------------------------------------------------------------//
//// Check that the angle can be evaluated
//TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
//                   ScatterAdjointElectron_lin )
//{
//  // Set fake random number stream
//  std::vector<double> fake_stream( 1 );
//  fake_stream[0] = 0.5; // sample mu = 9.9999999774879678e-01

//  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//  MonteCarlo::ParticleBank bank;
//  Data::SubshellType shell_of_interaction;

//  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
//  adjoint_electron.setEnergy( 6.625E+01 );
//  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

//  // Analytically scatter electron
//  lin_distribution->scatterAdjointElectron(
//        adjoint_electron,
//        bank,
//        shell_of_interaction );

//  // Test
//  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
//                          9.9999999774879678e-01,
//                          1e-12 );
//  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 6.625E+01, 1e-12 );
//}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // create Native H distribution
  {
  // Get native data container
  Data::ElectronPhotonRelaxationDataContainer data_container =
    Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

  // Get the screened Rutherford traits
  std::shared_ptr<MonteCarlo::ElasticElectronTraits> traits(
    new MonteCarlo::ElasticElectronTraits( data_container.getAtomicNumber() ) );

  // Electron energy grid
  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();

  // Cutoff elastic cross section
  std::vector<double> cutoff_cross_section =
    data_container.getCutoffElasticCrossSection();

  // Total elastic cross section
  std::vector<double> total_cross_section =
    data_container.getTotalElasticCrossSection();

  // Calculate the ratio of the cutoff to the total cross section
  std::vector<double> cross_section_ratio( energy_grid.size() );
  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    // Get the ratio of the cutoff to the total cross section
    cross_section_ratio[n] = cutoff_cross_section[n]/total_cross_section[n];
  }

  // Create cross section ratios
  std::shared_ptr<const Utility::OneDDistribution> cross_section_ratios(
      new const Utility::TabularDistribution<Utility::LinLin>( energy_grid, cross_section_ratio ) );

  // Get the energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType function_data( size );

  for( unsigned n = 0; n < size; ++n )
  {
    // Set the energy
    function_data[n].first = angular_energy_grid[n];

    // Get the value of moliere's eta
    double eta = traits->evaluateMoliereScreeningConstant( angular_energy_grid[n] );

    // Get the ratio of the cutoff to total elastic cross section
    double cutoff_ratio = cross_section_ratios->evaluate( angular_energy_grid[n] );

    // Get the cutoff elastic scattering angles at the energy
    Teuchos::Array<double> angles(
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    Teuchos::Array<double> pdf(
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

  // Create analog elastic distribution
  function_data[n].second.reset(
    new const Utility::AnalogElasticDistribution<Utility::LinLin>( angles, pdf, eta, cutoff_ratio ) );
  }


  double evaluation_tol = 1e-15;

    // Create the distributions unsing LinLinLog interpolation
    {
    // Create the scattering distribution
    std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function(
        new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLog>(
            function_data,
            1e-6,
            evaluation_tol ) );

    bool linlinlog_interpolation_mode_on = true;
    bool correlated_sampling_mode_on = true;

    // Create the distribution
    distribution.reset(
        new MonteCarlo::AnalogElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                correlated_sampling_mode_on ) );

    // Create the test distribution
    test_distribution.reset(
        new TestAnalogElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                correlated_sampling_mode_on ) );
    }
    // Create the distributions unsing LinLinLin interpolation
    {
    // Create the scattering distribution
    std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function(
        new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            function_data,
            1e-6,
            evaluation_tol ) );

    bool linlinlog_interpolation_mode_on = false;
    bool correlated_sampling_mode_on = true;

    // Create the distribution
    lin_distribution.reset(
        new MonteCarlo::AnalogElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                correlated_sampling_mode_on ) );

    // Create the test distribution
    test_lin_distribution.reset(
        new TestAnalogElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                correlated_sampling_mode_on ) );
    }
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END(); 

//---------------------------------------------------------------------------//
// end tstAnalogElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
