//---------------------------------------------------------------------------//
//!
//! \file   tstCoupledElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Coupled elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronTraits.hpp"
#include "MonteCarlo_CoupledElasticDistribution.hpp"
#include "MonteCarlo_ElasticBasicBivariateDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestCoupledElasticElectronScatteringDistribution : public MonteCarlo::CoupledElasticElectronScatteringDistribution
{
public:
  TestCoupledElasticElectronScatteringDistribution(
    const std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
        elastic_cutoff_distribution,
    const std::shared_ptr<const Utility::UnivariateDistribution>& cutoff_cross_section_ratios,
    const std::shared_ptr<const MonteCarlo::ElasticElectronTraits>& elastic_traits,
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
  using MonteCarlo::CoupledElasticElectronScatteringDistribution::sampleModifiedTwoDUnion;
  using MonteCarlo::CoupledElasticElectronScatteringDistribution::sampleTwoDUnion;
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
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluate_linlinlog )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.8836447748920078e-16, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0198661034411070e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9686225038692240e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0003853171793733e+06, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0952349918582737e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2871040449210824e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2254602823514824e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9698246187472879e+05, 1e-12 );
  }
  {
  // Test between the two energies
  energy = 200.0;

  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 7.7370863381120232e-10, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 7.9706781241222326e-10, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.8873796832346860e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.9280874953955145e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 5 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 7.7776801327554984e+06, 1e-12 );
  }
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.8836447290971699e-16, 1e-12 );

  scattering_angle_cosine = .71;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0198660938776344e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9686224103916112e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9043300839413338e+14, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0952344626057818e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2871029397194368e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2254592069380697e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.4115862396475458e+08, 1e-12 );
  }
  {
  // Test between the two energies
  energy = 2.00E+02;

  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 7.7370825993175027e-10, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 7.9706742724484971e-10, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.8873792076425484e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.9280867171545342e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.0979308448352657e+10, 1e-12 );
  }
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford pdf can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.5, tol );

  // Test
  scattering_angle_cosine = 0.9999995;
  pdf_value = test_linlinlog_distribution->evaluateScreenedRutherfordPDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.5000005, tol );

  // Test
  scattering_angle_cosine = 1.0;
  pdf_value = test_linlinlog_distribution->evaluateScreenedRutherfordPDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.500001, tol );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateCDF_linlinlog )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  // Test 1 energy 1
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.5194151539596018523e-16, 1e-12 );

  // Test 2 energy 1
  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.0228604997734523684e-15, 1e-12 );

  // Test 3 energy 1
  scattering_angle_cosine = 0.999995;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.0215493910276143181e-10, 1e-12 );

  // Test 4 energy 1
  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0100484326755010891e-09, 1e-12 );

  // Test 5 energy 1
  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  // Test 1 energy 2
  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.4077730521222221e-10, 1e-12 );

  // Test 2 energy 2
  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.5364424726616341e-09, 1e-12 );

  // Test 3 energy 2
  scattering_angle_cosine = 0.999995;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.5313099196981932e-04, 1e-12 );

  // Test 4 energy 2
  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2599172405176550e-03, 1e-12 );

  // Test 5 energy 2
  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test between the two energies
  energy = 2.00E+02;

  // Test 1 energy 3
  scattering_angle_cosine = -1.0;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 0.0, 1e-12 );

  // Test 1 energy 3
  scattering_angle_cosine = -0.01;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.8581420097532581e-10, 1e-12 );

  // Test 1 energy 3
  scattering_angle_cosine = 0.0;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.9366807942591920e-10, 1e-12 );

  // Test 2 energy 3
  scattering_angle_cosine = 0.71;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.5337390232707917e-09, 1e-12 );

  // Test 3 energy 3
  scattering_angle_cosine = 0.999995;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.8476149581342586e-04, 1e-12 );

  // Test 4 energy 3
  scattering_angle_cosine = 0.999999;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.5106038136353922e-04, 1e-12 );

  // Test 5 energy 3
  scattering_angle_cosine = 1.0;
  value = linlinlog_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford cdf can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.5, tol );

  // Test
  scattering_angle_cosine = 0.9999995;
  cdf_value = test_linlinlog_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.749999875000063, tol );

  // Test with a different energy
  scattering_angle_cosine = 1.0;
  cdf_value = test_linlinlog_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
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
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_linlinlog_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlinlog_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 12 );
  // sampleAndRecordTrialsImpl from distribution
  test_linlinlog_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlinlog_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 14 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlinlog_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 15 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692943e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886739e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy in between energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 1.0e-3; // sample mu = -8.5537934174508756e-01
  fake_stream[1] = 0.5; // sample mu = 4.9274826288429413e-01
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 9.9999799195028571e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -8.5537934174508756e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 4.9274826288429413e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.9913094173895369288e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999799195028571e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy in between energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9998073891771788e-01
  fake_stream[2] = 2.510603e-04; // sample just below cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample at the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9998073891771788e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999233828751999e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999233828998058e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleModifiedTwoDUnion_linlinlog )
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

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy in between energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 1.0e-3; // sample mu = -8.5537934174508756e-01
  fake_stream[1] = 0.5; // sample mu = 4.9274826288429413e-01
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369e-01
  fake_stream[3] = 0.999999; // sample mu = 9.9999799195028571e-01
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -8.5537934174508756e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 4.9274826288429413e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.9913094173895369e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999799195028571e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy in between energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1
  fake_stream[1] = 1.0e-4; // sample mu = 9.9998740058910129e-01
  fake_stream[2] = 2.510603e-04; // sample just below the cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample at the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9998740058910129e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999899999753938e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy in between energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 1.0e-3; // sample mu = -0.85537934174508756247
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -0.85537934174508756247, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 4.9274826288429413035e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.9913094173895369288e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999799195028571397, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy in between energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9998073891771788e-01
  fake_stream[2] = 2.510603e-04; // sample just below the cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9998073891771788e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999233828751999e-01, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_linlinlog_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );


  // Test energy in between energy bins
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -0.85537934174508756247, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 4.9274826288429413035e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.9913094173895369288e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999799195028571397, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  // Test energy in between energy bins
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9980743513319303e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9998073891771788e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999233828751999e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  linlinlog_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
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
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  linlinlog_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterPositron_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 6.625E+01 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  linlinlog_distribution->scatterPositron( positron,
                                 bank,
                                 shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          9.9999999774886750e-01,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// LogLogLog Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluate_logloglog )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.8836447748920078e-16, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0198661034411070e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9686225038692240e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0003853171793733e+06, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0952349918582737e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2871040449210824e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2254602823514824e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9698246187472879e+05, 1e-12 );
  }
  {
  // Test between the two energies
  energy = 200.0;

  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.7994721919646270e-13, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.0410083116607051e-13, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 5.7108399377568105e-10, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 5.1628128366552642e+02, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 5 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.0826184975880277e+06, 1e-12 );
  }
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluatePDF_logloglog )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value =
    log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.8836447290971699e-16, 1e-12 );

  scattering_angle_cosine = .71;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0198660938776344e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9686224103916112e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9043300839413338e+14, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0952344626057818e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2871029397194368e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2254592069380697e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.4115862396475458e+08, 1e-12 );
  }
  {
  // Test between the two energies
  energy = 2.00E+02;

  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.7994721335569622e-13, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.0410082468163887e-13, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 5.7108387748106213e-10, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 5.1831872731713042e+02, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 8.3280256978338032e+09, 1e-12 );
  }
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford pdf can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordPDF_logloglog )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.5, tol );

  // Test
  scattering_angle_cosine = 0.9999995;
  pdf_value = test_log_distribution->evaluateScreenedRutherfordPDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.5000005, tol );

  // Test
  scattering_angle_cosine = 1.0;
  pdf_value = test_log_distribution->evaluateScreenedRutherfordPDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.500001, tol );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateCDF_logloglog )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  // Test 1 energy 1
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.5194151539596023e-16, 1e-12 );

  // Test 2 energy 1
  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.0228604997734524e-15, 1e-12 );

  // Test 3 energy 1
  scattering_angle_cosine = 0.999995;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.0215493910276146e-10, 1e-12 );

  // Test 4 energy 1
  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0100484326755011e-09, 1e-12 );

  // Test 5 energy 1
  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  // Test 1 energy 2
  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.4077730521222221e-10, 1e-12 );

  // Test 2 energy 2
  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.5364424726616341e-09, 1e-12 );

  // Test 3 energy 2
  scattering_angle_cosine = 0.999995;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.5313099196981932e-04, 1e-12 );

  // Test 4 energy 2
  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2599172405176550e-03, 1e-12 );

  // Test 5 energy 2
  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test between the two energies
  energy = 2.00E+02;

  // Test 1 energy 3
  scattering_angle_cosine = -1.0;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 0.0, 1e-12 );

  // Test 2 energy 3
  scattering_angle_cosine = -0.01;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.1911228527689988e-14, 1e-12 );

  // Test 3 energy 3
  scattering_angle_cosine = 0.0;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.4836258908904261e-14, 1e-12 );

  // Test 4 energy 3
  scattering_angle_cosine = 0.71;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.2244915239096932e-11, 1e-12 );

  // Test 5 energy 3
  scattering_angle_cosine = 0.999995;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 6.7887648778744983e-05, 1e-12 );

  // Test 6 energy 3
  scattering_angle_cosine = 0.999999;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.5106038136353922e-04, 1e-12 );

  // Test 7 energy 3
  scattering_angle_cosine = 1.0;
  value = log_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford cdf can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordCDF_logloglog )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.5, tol );

  // Test
  scattering_angle_cosine = 0.9999995;
  cdf_value = test_log_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.749999875000063, tol );

  // Test with a different energy
  scattering_angle_cosine = 1.0;
  cdf_value = test_log_distribution->evaluateScreenedRutherfordCDF(
                        scattering_angle_cosine,
                        eta,
                        cutoff_pdf*cutoff_cdf );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_logloglog )
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
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_log_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_log_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 12 );
  // sampleAndRecordTrialsImpl from distribution
  test_log_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_log_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 14 );

  // sampleAndRecordTrialsImpl from distribution
  test_log_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 15 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleOneDUnion_logloglog )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy in between energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.7957167459329355e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.8136012649293924e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999825404676779e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy in between energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9999750799434528e-01
  fake_stream[2] = 2.510603e-04; // sample just below cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample at the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999642274005895e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999837849488138e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999837849532358e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleOneDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleModifiedTwoDUnion_logloglog )
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

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy in between energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.7957167459329355e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.8136012649293924e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999825404676779e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy in between energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1
  fake_stream[1] = 1.0e-4; // sample mu = 9.9999749944145055e-01
  fake_stream[2] = 2.510603e-04; // sample just below the cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample at the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999704424412761e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999899999955777e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleModifiedTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleTwoDUnion_logloglog )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );


  // Test energy in between energy bins
  energy = 1e-4;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 0.5; // sample mu = 0.49274826288429413035
  fake_stream[2] = 0.9; // sample mu = 8.9913094173895369288e-01
  fake_stream[3] = 0.999999; // sample mu = 0.999999
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.7957167459329355e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.8136012649293924e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999825404676779e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  // Test energy in between energy bins
  energy = 2e2;

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9999999774886750e-01
  fake_stream[2] = 2.510603e-04; // sample just below the cutoff cross section ratio
  fake_stream[3] = 2.5106038136353922e-04; // sample the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999642274005895e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999837849488138e-01, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  scattering_angle_cosine = test_log_distribution->sampleTwoDUnion( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sample_logloglog )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999900003692932e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );


  // Test energy in between energy bins
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.7957167459329355e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.8136012649293924e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999825404676779e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  // Test energy in between energy bins
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999704424412761e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999899999955777e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );

  log_distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, electron.getEnergy(), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_logloglog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  log_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterElectron_logloglog )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterPositron_logloglog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 6.625E+01 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  log_distribution->scatterPositron( positron,
                                     bank,
                                     shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_logloglog )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          9.9999999774886750e-01,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// LinLinLin Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluate_linlinlin )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.8836447748920078e-16, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0198661034411070e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9686225038692240e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0003853171793733e+06, 1e-12 );

  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0952349918582737e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2871040449210824e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2254602823514824e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9698246187472879e+05, 1e-12 );

  }
  {
  // Test between the two energies
  energy = 200.0;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0931496873762000e-09, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.1328228698954650e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2850014916055102e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2232697075812862e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 8.9684107571399193e+06, 1e-12 );

  }
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluatePDF_linlinlin )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;

  double value =
    lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.8836447290971699e-16, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0198660938776344e-14, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9686224103916112e-04, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 9.9043300839413338e+14, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0952344626057818e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2871029397194368e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2254592069380697e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.4115862396475458e+08, 1e-12 );

  // Test between the two energies
  energy = 2.00E+02;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0931491591314005e-09, 1e-12 );

  scattering_angle_cosine = 0.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.1328223224793178e-09, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2850003908721748e-08, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2232686345372099e+03, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 3
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.5722109477794708e+10, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   evaluateCDF_linlinlin )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  // Test 1 energy 1
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.51941515395960185227e-16, 1e-12 );

  // Test 2 energy 1
  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.02286049977345236836e-15, 1e-12 );

  // Test 3 energy 1
  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.01004843267550108913e-09, 1e-12 );

  // Test 4 energy 1
  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  // Test 1 energy 2
  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.4077730521222221e-10, 1e-12 );

  // Test 2 energy 2
  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.5364424726616341e-09, 1e-12 );

  // Test 3 energy 2
  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.2599172405176550e-03, 1e-12 );

  // Test 4 energy 2
  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test between the two energies
  energy = 2.00E+02;

  // Test 1 energy 3
  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.3929722123280143e-10, 1e-12 );

  // Test 2 energy 3
  scattering_angle_cosine = 0.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 3.5041802971888968e-10, 1e-12 );

  // Test 3 energy 3
  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 4.5275636298840866e-09, 1e-12 );

  // Test 4 energy 3
  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 2.5106038136353922e-04, 1e-12 );

  // Test 5 energy 3
  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( value, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_linlinlin )
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
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from lin_distribution
  test_lin_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999773362030264e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

  // sampleAndRecordTrialsImpl from lin_distribution
  test_lin_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999997748864499769e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 12 );

  // sampleAndRecordTrialsImpl from lin_distribution
  test_lin_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 13 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sample_linlinlin )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999997748864499769e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );

  // Test energy in between energy bins
  electron.setEnergy( 1e-4 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // sampleAndRecordTrialsImpl from lin_distribution
  lin_distribution->sample( electron.getEnergy(),
                            outgoing_energy,
                            scattering_angle_cosine );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.95901841607806975754e-02, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_linlinlin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  lin_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                           outgoing_energy,
                                           scattering_angle_cosine,
                                           trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterElectron_linlinlin )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterPositron_linlinlin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999774886750e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 6.625E+01 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  lin_distribution->scatterPositron( positron, bank, shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 9.9999999774886750e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CoupledElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_linlinlin )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          9.9999999774886750e-01,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 6.625E+01, 1e-12 );
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
  // create Native H distribution
  {
  // Get native data container
  Data::ElectronPhotonRelaxationDataContainer data_container =
    Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

  // Get the Elastic electron traits
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
  std::shared_ptr<const Utility::UnivariateDistribution> cross_section_ratios(
      new const Utility::TabularDistribution<Utility::LogLog>( energy_grid, cross_section_ratio ) );

  // Get the energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  std::vector<double> primary_grid( size );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( size );

  for( unsigned n = 0; n < size; ++n )
  {
    // Set the energy
    primary_grid[n] = angular_energy_grid[n];

    // Get the value of moliere's eta
    double eta = traits->evaluateMoliereScreeningConstant( angular_energy_grid[n] );

    // Get the ratio of the cutoff to total elastic cross section
    double cutoff_ratio = cross_section_ratios->evaluate( angular_energy_grid[n] );

    // Get the cutoff elastic scattering angles at the energy
    std::vector<double> angles(
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scattering pdf at the energy
    std::vector<double> pdf(
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

  // Create coupled elastic distribution
  secondary_dists[n].reset(
    new const MonteCarlo::CoupledElasticDistribution<Utility::LinLin>( angles, pdf, eta, cutoff_ratio ) );
  }

  MonteCarlo::CoupledElasticSamplingMethod sampling_method =
    MonteCarlo::TWO_D_UNION;
  double evaluation_tol = 1e-15;

    // Create the distributions using LogLogLog interpolation
    {
    // Create the scattering distribution
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> scattering_function(
       new MonteCarlo::ElasticBasicBivariateDistribution<Utility::Correlated<Utility::LogNudgedLogCosLog > >(
                                                       primary_grid,
                                                       secondary_dists,
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
                MonteCarlo::MODIFIED_TWO_D_UNION ) );

    // Create the test distribution
    test_log_distribution.reset(
        new TestCoupledElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                traits,
                MonteCarlo::MODIFIED_TWO_D_UNION ) );
    }

    // Create the distributions using LinLinLog interpolation
    {
    // Create the scattering distribution
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> scattering_function(
        new MonteCarlo::ElasticBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLog>>(
                                                    primary_grid,
                                                    secondary_dists,
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
    // Create the distributions using LinLinLin interpolation
    {
    // Create the scattering distribution
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> scattering_function(
       new MonteCarlo::ElasticBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLin>>(
                                                        primary_grid,
                                                        secondary_dists,
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

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCoupledElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
