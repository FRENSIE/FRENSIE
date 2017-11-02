//---------------------------------------------------------------------------//
//!
//! \file   tstCoupledElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Coupled elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"
#include "Utility_ElasticElectronTraits.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_CoupledElasticDistribution.hpp"
#include "Utility_ElasticTwoDDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestCoupledElasticElectronScatteringDistribution : public MonteCarlo::CoupledElasticElectronScatteringDistribution
{
public:
  TestCoupledElasticElectronScatteringDistribution(
    const std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
        elastic_cutoff_distribution,
    const std::shared_ptr<const Utility::OneDDistribution>& cutoff_cross_section_ratios,
    const std::shared_ptr<const Utility::ElasticElectronTraits>& elastic_traits,
    const MonteCarlo::CoupledElasticSamplingMethod& sampling_method )
    : MonteCarlo::CoupledElasticElectronScatteringDistribution(
        elastic_cutoff_distribution,
        cutoff_cross_section_ratios,
        elastic_traits,
        sampling_method )
  { /* ... */ }

  ~TestCoupledElasticElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the CoupledElasticElectronScatteringDistribution protected member functions
  using MonteCarlo::CoupledElasticElectronScatteringDistribution::sampleOneDUnion;
  using MonteCarlo::CoupledElasticElectronScatteringDistribution::sampleTwoDUnion;
  using MonteCarlo::CoupledElasticElectronScatteringDistribution::sampleSimplifiedUnion;
  using MonteCarlo::CoupledElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl;
  using MonteCarlo::CoupledElasticElectronScatteringDistribution::evaluateScreenedRutherfordPDF;
  using MonteCarlo::CoupledElasticElectronScatteringDistribution::evaluateScreenedRutherfordCDF;

};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::CoupledElasticElectronScatteringDistribution>
  linlinlog_distribution, lin_distribution, log_distribution;

std::shared_ptr<TestCoupledElasticElectronScatteringDistribution>
  test_linlinlog_distribution, test_lin_distribution, test_log_distribution;

//---------------------------------------------------------------------------//
// LinLinLog Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluate_linlinlog )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.8836447748920078e-16, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.0198661034411070e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.9686225038692240e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 1.0003853171793733e+06, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 1.0952349918582737e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2871040449210824e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2254602823514824e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 9.9698246187472879e+05, 1e-12 );
  }
  {
  // Test inbetween the two energies
  energy = 200.0;

  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 5.1902291189033630e-06, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 5.6042928493529642e-06, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 1.8597615040167894e-03, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 3
  TEST_FLOATING_EQUALITY( value, 5.5194289292652345e+08, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 5 energy 3
  TEST_FLOATING_EQUALITY( value, 2.2264732710429272e+12, 1e-12 );
  }
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluatePDF_linlinlog )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value =
    linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.8836447290971699e-16, 1e-12 );

  scattering_angle_cosine = .71;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.0198660938776344e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.9686224103916112e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 9.9043300839413338e+14, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 1.0952344626057818e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2871029397194368e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2254592069380697e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 4.4115862396475458e+08, 1e-12 );
  }
  {
  // Test inbetween the two energies
  energy = 2.00E+02;

  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 5.1902290699693328e-06, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 5.6042927965282025e-06, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 1.8412462418416247e+06, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 5.4645052649586253e+17, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 3
  TEST_FLOATING_EQUALITY( value, 8.7800301000275057e+24, 1e-12 );
  }
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford pdf can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordPDF_linlinlog )
{
  double tol = 1.0e-12;
  double eta = 1.0;
  double cutoff_pdf = 0.5;

  // Test
  double scattering_angle_cosine = 0.999999;
  double pdf_value = test_linlinlog_distribution->evaluateScreenedRutherfordPDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf );
  TEST_FLOATING_EQUALITY( pdf_value, 0.5, tol );

  // Test
  scattering_angle_cosine = 0.9999995;
  pdf_value = test_linlinlog_distribution->evaluateScreenedRutherfordPDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf );
  TEST_FLOATING_EQUALITY( pdf_value, 0.5000005, tol );

  // Test
  scattering_angle_cosine = 1.0;
  pdf_value = test_linlinlog_distribution->evaluateScreenedRutherfordPDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf );
  TEST_FLOATING_EQUALITY( pdf_value, 0.500001, tol );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateCDF_linlinlog )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  // Test 1 energy 1
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.5194151539596018523e-16, 1e-12 );

  // Test 2 energy 1
  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.0228604997734523684e-15, 1e-12 );

  // Test 3 energy 1
  scattering_angle_cosine = 0.999995;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.0215493910276143181e-10, 1e-12 );

  // Test 4 energy 1
  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0100484326755010891e-09, 1e-12 );

  // Test 5 energy 1
  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  // Test 1 energy 2
  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.4077730521222221e-10, 1e-12 );

  // Test 2 energy 2
  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.5364424726616341e-09, 1e-12 );

  // Test 3 energy 2
  scattering_angle_cosine = 0.999995;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.5313099196981932e-04, 1e-12 );

  // Test 4 energy 2
  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.2599172405176550e-03, 1e-12 );

  // Test 5 energy 2
  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test inbetween the two energies
  energy = 2.00E+02;

  // Test 1 energy 3
  scattering_angle_cosine = -1.0;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value,  0.0, 1e-12 );

  // Test 1 energy 3
  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.8581420097549228e-10, 1e-12 );

  // Test 1 energy 3
  scattering_angle_cosine = 0.0;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.9366807942573329e-10, 1e-12 );

  // Test 2 energy 3
  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.5337390233739692e-09, 1e-12 );

  // Test 3 energy 3
  scattering_angle_cosine = 0.999995;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.8476062182844816e-04, 1e-12 );

  // Test 4 energy 3
  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.5106038136353922e-04, 1e-12 );

  // Test 5 energy 3
  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford cdf can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordCDF_linlinlog )
{
  double tol = 1e-10;
  double eta = 1.0;
  double cutoff_pdf = 1.0;
  double cutoff_cdf = 0.5;

  // Test
  double scattering_angle_cosine = 0.999999;
  double cdf_value = test_linlinlog_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  TEST_FLOATING_EQUALITY( cdf_value, 0.5, tol );

  // Test
  scattering_angle_cosine = 0.9999995;
  cdf_value = test_linlinlog_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  TEST_FLOATING_EQUALITY( cdf_value, 0.749999875000063, tol );

  // Test with a different energy
  scattering_angle_cosine = 1.0;
  cdf_value = test_linlinlog_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999900003692932e-01
  fake_stream[2] = 2.2599172405176550e-03; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774886750e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_linlinlog_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlinlog_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );
  // sampleAndRecordTrialsImpl from distribution
  test_linlinlog_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlinlog_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 14 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlinlog_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( trials, 15 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleOneDUnion_linlinlog )
{
  double scattering_angle_cosine, energy;
  energy = 6.625e1;

  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999900003692943e-01
  fake_stream[2] = 2.2599172405176550e-03; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774886739e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692943e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886739e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy inbetween energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 1.0e-3; // sample mu = -8.5537934174508756e-01
  fake_stream[1] = 0.5; // sample mu = 4.9274826288429413e-01
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 9.9999799195028571e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -8.5537934174508756e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 4.9274826288429413e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.9913094173895369288e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999799195028571e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy inbetween energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9998073891771788e-01
  fake_stream[2] = 2.510603e-04; // sample just below cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample at the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9998073891771788e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999233828751999e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999233828998058e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleTwoDUnion_linlinlog )
{
  double scattering_angle_cosine, energy;
  energy = 6.625e1;

  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999900003692932e-01
  fake_stream[2] = 2.2599172405176550e-03; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774886750e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy inbetween energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 1.0e-3; // sample mu = -8.5537934174508756e-01
  fake_stream[1] = 0.5; // sample mu = 4.9274826288429413e-01
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369e-01
  fake_stream[3] = 0.999999; // sample mu = 9.9999799195028571e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -8.5537934174508756e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 4.9274826288429413e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.9913094173895369e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999799195028571e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy inbetween energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1
  fake_stream[1] = 1.0e-4; // sample mu = 9.9998740058910129e-01
  fake_stream[2] = 2.510603e-04; // sample just below the cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample at the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9998740058910129e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999899999753938e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleSimplifiedUnion_linlinlog )
{
  double scattering_angle_cosine, energy;
  energy = 6.625e1;

  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999900003692932e-01
  fake_stream[2] = 2.2599172405176550e-03; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774886750e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy inbetween energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 1.0e-3; // sample mu = -0.85537934174508756247
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.85537934174508756247, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 4.9274826288429413035e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.9913094173895369288e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999799195028571397, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy inbetween energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9998073891771788e-01
  fake_stream[2] = 2.510603e-04; // sample just below the cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9998073891771788e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999233828751999e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sample_linlinlog )
{
  // Set up the electron
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999900003692932e-01
  fake_stream[2] = 2.2599172405176550e-03; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774886750e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );


  // Test energy inbetween energy bins
  electron.setEnergy( 1e-4 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Set fake random number stream
  fake_stream[0] = 1.0e-3; // sample mu = -0.85537934174508756247
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.85537934174508756247, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 4.9274826288429413035e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.9913094173895369288e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999799195028571397, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  // Test energy inbetween energy bins
  electron.setEnergy( 2e2 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Set fake random number stream
  fake_stream[0] = 1.0e-5; // sample mu = 9.9980743513319303e-01
  fake_stream[1] = 1.0e-4; // sample mu = 9.9998073891771788e-01
  fake_stream[2] = 2.510603e-04; // sample just below mu = 0.999999
  fake_stream[3] = 2.5106038136353922e-04; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9980743513319303e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9998073891771788e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999233828751999e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  linlinlog_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterElectron_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  linlinlog_distribution->scatterElectron( electron,
                                 bank,
                                 shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.9999999774886750e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 6.625E+01 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  linlinlog_distribution->scatterAdjointElectron(
        adjoint_electron,
        bank,
        shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          9.9999999774886750e-01,
                          1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// LogLogLog Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluate_log )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.8836447748920078e-16, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.0198661034411070e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.9686225038692240e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 1.0003853171793733e+06, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 1.0952349918582737e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2871040449210824e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2254602823514824e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 9.9698246187472879e+05, 1e-12 );
  }
  {
  // Test inbetween the two energies
  energy = 200.0;

  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 4.3250307706222139e-12, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 4.5449923867001888e-12, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 8.6256518252190875e-10, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 3
  TEST_FLOATING_EQUALITY( value, 2.5065672544519705e+02, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 5 energy 3
  TEST_FLOATING_EQUALITY( value, 1.0111200027448682e+06, 1e-12 );
  }
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluatePDF_log )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value =
    log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.8836447290971699e-16, 1e-12 );

  scattering_angle_cosine = .71;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.0198660938776344e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.9686224103916112e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 9.9043300839413338e+14, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 1.0952344626057818e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2871029397194368e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2254592069380697e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 4.4115862396475458e+08, 1e-12 );
  }
  {
  // Test inbetween the two energies
  energy = 2.00E+02;

  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 4.3250289899930614e-12, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 4.5449905155121276e-12, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 8.6256482740103416e-10, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 5.7145196857642550e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 3
  TEST_FLOATING_EQUALITY( value, 9.1817378546509247e+10, 1e-12 );
  }
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford pdf can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordPDF_log )
{
  double tol = 1.0e-12;
  double eta = 1.0;
  double cutoff_pdf = 0.5;

  // Test
  double scattering_angle_cosine = 0.999999;
  double pdf_value = test_log_distribution->evaluateScreenedRutherfordPDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf );
  TEST_FLOATING_EQUALITY( pdf_value, 0.5, tol );

  // Test
  scattering_angle_cosine = 0.9999995;
  pdf_value = test_log_distribution->evaluateScreenedRutherfordPDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf );
  TEST_FLOATING_EQUALITY( pdf_value, 0.5000005, tol );

  // Test
  scattering_angle_cosine = 1.0;
  pdf_value = test_log_distribution->evaluateScreenedRutherfordPDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf );
  TEST_FLOATING_EQUALITY( pdf_value, 0.500001, tol );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateCDF_log )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  // Test 1 energy 1
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.5194151539596023e-16, 1e-12 );

  // Test 2 energy 1
  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.0228604997734524e-15, 1e-12 );

  // Test 3 energy 1
  scattering_angle_cosine = 0.999995;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.0215493910276146e-10, 1e-12 );

  // Test 4 energy 1
  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0100484326755011e-09, 1e-12 );

  // Test 5 energy 1
  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  // Test 1 energy 2
  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.4077730521222221e-10, 1e-12 );

  // Test 2 energy 2
  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.5364424726616341e-09, 1e-12 );

  // Test 3 energy 2
  scattering_angle_cosine = 0.999995;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.5313099196981932e-04, 1e-12 );

  // Test 4 energy 2
  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.2599172405176550e-03, 1e-12 );

  // Test 5 energy 2
  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test inbetween the two energies
  energy = 2.00E+02;

  // Test 1 energy 3
  scattering_angle_cosine = -1.0;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 0.0, 1e-12 );

  // Test 2 energy 3
  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.1911228355588287e-14, 1e-12 );

  // Test 3 energy 3
  scattering_angle_cosine = 0.0;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.4836258710726529e-14, 1e-12 );

  // Test 4 energy 3
  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.2244810859730156e-11, 1e-12 );

  // Test 5 energy 3
  scattering_angle_cosine = 0.999995;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.9813917317399604e-05, 1e-12 );

  // Test 6 energy 3
  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.5106038136353922e-04, 1e-12 );

  // Test 7 energy 3
  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford cdf can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordCDF_log )
{
  double tol = 1e-10;
  double eta = 1.0;
  double cutoff_pdf = 1.0;
  double cutoff_cdf = 0.5;

  // Test
  double scattering_angle_cosine = 0.999999;
  double cdf_value = test_log_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  TEST_FLOATING_EQUALITY( cdf_value, 0.5, tol );

  // Test
  scattering_angle_cosine = 0.9999995;
  cdf_value = test_log_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  TEST_FLOATING_EQUALITY( cdf_value, 0.749999875000063, tol );

  // Test with a different energy
  scattering_angle_cosine = 1.0;
  cdf_value = test_log_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_log )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999900003692932e-01
  fake_stream[2] = 2.2599172405176550e-03; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774886750e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_log_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_log_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );
  // sampleAndRecordTrialsImpl from distribution
  test_log_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_log_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 14 );

  // sampleAndRecordTrialsImpl from distribution
  test_log_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( trials, 15 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleOneDUnion_log )
{
  double scattering_angle_cosine, energy;
  energy = 6.625e1;

  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999900003692932e-01
  fake_stream[2] = 2.2599172405176550e-03; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774886750e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy inbetween energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.87957167491449994579, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98136012693408603003, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999825406177955678, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy inbetween energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9999750799434528e-01
  fake_stream[2] = 2.510603e-04; // sample just below cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample at the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999750799434528e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900855263080e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900855290114e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleTwoDUnion_log )
{
  double scattering_angle_cosine, energy;
  energy = 6.625e1;

  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999900003692932e-01
  fake_stream[2] = 2.2599172405176550e-03; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774886750e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy inbetween energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.87957167491449994579, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98136012693408603003, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999825406177955678, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy inbetween energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1
  fake_stream[1] = 1.0e-4; // sample mu = 9.9999749944145055e-01
  fake_stream[2] = 2.510603e-04; // sample just below the cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample at the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999749944145055e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleSimplifiedUnion_log )
{
  double scattering_angle_cosine, energy;
  energy = 6.625e1;

  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999900003692932e-01
  fake_stream[2] = 2.2599172405176550e-03; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774886750e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy inbetween energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.87957167491449994579, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98136012693408603003, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999825406177955678, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy inbetween energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9999999774886750e-01
  fake_stream[2] = 2.510603e-04; // sample just below the cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999750799434528e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900855263080e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleSimplifiedUnion( energy );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sample_log )
{
  // Set up the electron
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // Set fake random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 2.26e-3; // sample mu = 9.9999900003692932e-01
  fake_stream[2] = 2.2599172405176550e-03; // sample mu = 0.999999
  fake_stream[3] = 0.5; // sample mu = 9.9999999774886750e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );


  // Test energy inbetween energy bins
  electron.setEnergy( 1e-4 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -0.85537934174508756247
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.87957167491449994579, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98136012693408603003, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999825406177955678, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  // Test energy inbetween energy bins
  electron.setEnergy( 2e2 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = 9.9980743513319303e-01
  fake_stream[1] = 1.0e-4; // sample mu = 9.9999999774886750e-01
  fake_stream[2] = 2.510603e-04; // sample just below mu = 0.999999
  fake_stream[3] = 2.5106038136353922e-04; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999750799434528e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900855263080e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_log )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  log_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterElectron_log )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  log_distribution->scatterElectron( electron,
                                 bank,
                                 shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.9999999774886750e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_log )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 6.625E+01 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  log_distribution->scatterAdjointElectron(
        adjoint_electron,
        bank,
        shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          9.9999999774886750e-01,
                          1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// LinLinLin Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluate_lin )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.8836447748920078e-16, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.0198661034411070e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.9686225038692240e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 1.0003853171793733e+06, 1e-12 );

  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 1.0952349918582737e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2871040449210824e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2254602823514824e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 9.9698246187472879e+05, 1e-12 );

  }
  {
  // Test inbetween the two energies
  energy = 200.0;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 1.5200850246037449e-07, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 1.6440774637821668e-07, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 2.7114022228624985e-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 6.7570908519540690e+06, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 3
  TEST_FLOATING_EQUALITY( value, 2.7257316589611729e+10, 1e-12 );

  }
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluatePDF_lin )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;

  double value =
    lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.8836447290971699e-16, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.0198660938776344e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.9686224103916112e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 9.9043300839413338e+14, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 1.0952344626057818e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2871029397194368e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 2.2254592069380697e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 4.4115862396475458e+08, 1e-12 );

  // Test inbetween the two energies
  energy = 2.00E+02;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 1.5200850051835421e-07, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 1.6440774430117738e-07, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 2.6821716866860537e+04, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 6.6876728358653890e+15, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 3
  TEST_FLOATING_EQUALITY( value, 1.0745340328348830e+23, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateCDF_lin )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  // Test 1 energy 1
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.51941515395960185227e-16, 1e-12 );

  // Test 2 energy 1
  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.02286049977345236836e-15, 1e-12 );

  // Test 3 energy 1
  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.01004843267550108913e-09, 1e-12 );

  // Test 4 energy 1
  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  // Test 1 energy 2
  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.4077730521222221e-10, 1e-12 );

  // Test 2 energy 2
  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.5364424726616341e-09, 1e-12 );

  // Test 3 energy 2
  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.2599172405176550e-03, 1e-12 );

  // Test 4 energy 2
  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test inbetween the two energies
  energy = 2.00E+02;

  // Test 1 energy 3
  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.3929722123280406e-10, 1e-12 );

  // Test 2 energy 3
  scattering_angle_cosine = 0.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.5041802971889387e-10, 1e-12 );

  // Test 3 energy 3
  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.5275636298857005e-09, 1e-12 );

  // Test 4 energy 3
  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.5106038136353922e-04, 1e-12 );

  // Test 5 energy 3
  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 1.0e-3; // sample mu = 9.9999773362030264e-01
  fake_stream[1] = 0.5; // sample mu = 9.99999997748864499769e-01
  fake_stream[2] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from lin_distribution
  test_lin_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from lin_distribution
  test_lin_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999997748864499769e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // sampleAndRecordTrialsImpl from lin_distribution
  test_lin_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sample_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample mu = 9.99999997748864499769e-01
  fake_stream[1] = 0.5; // sample mu = 8.95901841607806975754e-02

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl from lin_distribution
  lin_distribution->sample( electron.getEnergy(),
                            outgoing_energy,
                            scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999997748864499769e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );

  // Test energy inbetween energy bins
  electron.setEnergy( 1e-4 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // sampleAndRecordTrialsImpl from lin_distribution
  lin_distribution->sample( electron.getEnergy(),
                            outgoing_energy,
                            scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.95901841607806975754e-02, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  lin_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                           outgoing_energy,
                                           scattering_angle_cosine,
                                           trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterElectron_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  lin_distribution->scatterElectron( electron, bank, shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.9999999774886750e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 6.625E+01 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  lin_distribution->scatterAdjointElectron(
        adjoint_electron,
        bank,
        shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          9.9999999774886750e-01,
                          1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 6.625E+01, 1e-12 );
}

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

  // Get the Elastic electron traits
  std::shared_ptr<Utility::ElasticElectronTraits> traits(
    new Utility::ElasticElectronTraits( data_container.getAtomicNumber() ) );

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
      new const Utility::TabularDistribution<Utility::LogLog>( energy_grid, cross_section_ratio ) );

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

  // Create coupled elastic distribution
  function_data[n].second.reset(
    new const Utility::CoupledElasticDistribution<Utility::LinLin>( angles, pdf, eta, cutoff_ratio ) );
  }

  MonteCarlo::CoupledElasticSamplingMethod sampling_method =
    MonteCarlo::SIMPLIFIED_UNION;
  double evaluation_tol = 1e-15;

    // Create the distributions unsing LogLogLog interpolation
    {
    // Create the scattering distribution
    std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function(
        new Utility::ElasticTwoDDistribution<Utility::LogLogCosLog,Utility::Exact>(
            function_data,
            1.0,
            1e-6,
            evaluation_tol,
            1e-12 ) );

    // Create the distribution
    log_distribution.reset(
        new MonteCarlo::CoupledElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                sampling_method ) );

    // Create the test distribution
    test_log_distribution.reset(
        new TestCoupledElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                sampling_method ) );
    }

    // Create the distributions unsing LinLinLog interpolation
    {
    // Create the scattering distribution
    std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function(
        new Utility::ElasticTwoDDistribution<Utility::LinLinLog,Utility::Exact>(
            function_data,
            1.0,
            1e-6,
            evaluation_tol,
            1e-12 ) );

    // Create the distribution
    linlinlog_distribution.reset(
        new MonteCarlo::CoupledElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                sampling_method ) );

    // Create the test distribution
    test_linlinlog_distribution.reset(
        new TestCoupledElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                sampling_method ) );
    }
    // Create the distributions unsing LinLinLin interpolation
    {
    // Create the scattering distribution
    std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function(
        new Utility::ElasticTwoDDistribution<Utility::LinLinLin,Utility::Exact>(
            function_data,
            1.0,
            1e-6,
            evaluation_tol,
            1e-12 ) );

    // Create the distribution
    lin_distribution.reset(
        new MonteCarlo::CoupledElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                sampling_method ) );

    // Create the test distribution
    test_lin_distribution.reset(
        new TestCoupledElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                sampling_method ) );
    }
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END(); 

//---------------------------------------------------------------------------//
// end tstCoupledElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
