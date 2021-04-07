//---------------------------------------------------------------------------//
//!
//! \file   tstHybridElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Moment Preserving elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_HybridElasticDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//

class TestHybridElasticElectronScatteringDistribution : public MonteCarlo::HybridElasticElectronScatteringDistribution
{
public:

  typedef MonteCarlo::HybridElasticElectronScatteringDistribution::BasicBivariateDist
            BasicBivariateDist;

  TestHybridElasticElectronScatteringDistribution(
    const std::shared_ptr<BasicBivariateDist>& hybrid_distribution,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
    : MonteCarlo::HybridElasticElectronScatteringDistribution(
                            hybrid_distribution,
                            cutoff_angle_cosine,
                            evaluation_tol )
  { /* ... */ }

  ~TestHybridElasticElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the HybridElasticElectronScatteringDistribution protected member functions
  using MonteCarlo::HybridElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
typedef Utility::FullyTabularBasicBivariateDistribution TwoDDist;

std::shared_ptr<MonteCarlo::HybridElasticElectronScatteringDistribution>
    hybrid_distribution, lin_hybrid_distribution, linlog_hybrid_distribution;
std::shared_ptr<TestHybridElasticElectronScatteringDistribution>
    test_hybrid_distribution, test_lin_hybrid_distribution, test_linlog_hybrid_distribution;

double angle_cosine_cutoff = 0.9;

//---------------------------------------------------------------------------//
// LogLogLog Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluate_logloglog )
{
  FRENSIE_CHECK_THROW( hybrid_distribution->evaluate( 1e-3, -1.0 ),
              std::runtime_error );

  FRENSIE_CHECK_THROW( hybrid_distribution->evaluate( 1e-4, angle_cosine_cutoff ),
              std::runtime_error );

  // double energy, scattering_angle_cosine, pdf_value;

  // // Test: below lowest bin
  // energy = 1e-6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: between bins
  // energy = 1e-4;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 3.0535587703057387e-01, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: On bin
  // energy = 1e-3;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.9520884073343972e-01, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test on highest bin
  // energy = 1e5;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 2.8685662935501774e-08, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: above highest bin
  // energy = 1e6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluatePDF_logloglog )
{
  FRENSIE_CHECK_THROW( hybrid_distribution->evaluatePDF( 1e-3, -1.0 ),
              std::runtime_error );

  FRENSIE_CHECK_THROW( hybrid_distribution->evaluatePDF( 1e-4, angle_cosine_cutoff ),
              std::runtime_error );

  // double energy, scattering_angle_cosine, pdf_value;

  // // Test: below lowest bin
  // energy = 1e-6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: in between bins
  // energy = 1e-4;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 8.0877272007709344e-01, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: On bin
  // energy = 1e-3;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.3009586997586640, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test on highest bin
  // energy = 1e5;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 3.3022053062175981e-03, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: above highest bin
  // energy = 1e6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluateCDF_logloglog )
{
  double energy, scattering_angle_cosine, cdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test: between bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 7.2973329008396992e-01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 7.2973329063571502e-01, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: right below cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff-1e-10;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.4463192139860923e-01, 1e-12 );

  // Test 2: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.4463192152870505e-01, 1e-12 );

  // Test 3: right above the cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.4463192152870505e-01, 1e-12 );

  // Test 4: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: right below cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff-1e-10;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.8288974926903438e-04, 1e-12 );

  // Test 2: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.8288974959925499e-04, 1e-12 );

  // Test 3: at 1st discrete angle
  scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.8288974959925499e-04, 1e-12 );

  // Test 4: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_logloglog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 5.2409574919482921e-02; // sample mu = 0.1 (cutoff)
  fake_stream[1] = 2.4463192152870505e-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 3.5160367533473e-01; // sample mu = 9.237831271699E-01 (discrete)
  fake_stream[3] = 3.5160367533474e-01; // sample mu = 9.817731638374E-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 1
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 12 );

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 3
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.2378312716992173e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 4
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.8177316383744406e-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 14 );


//  // Sample between 1e-5 and 1e-3 distribution bin
//  double energy = 1e-4;

//  fake_stream.resize( 8 );
//  // Sample mu = 0.1 (cutoff)
//  fake_stream[0] = 1.8585023785995389e-01;
//  // Sample at sampling ratio (mu = 0.9)
//  fake_stream[1] = 5.6660557766840980e-01;
//  // Sample right above sampling ratio (mu = 9.197507828539278618e-01)
//  fake_stream[2] = 5.6660557766840e-01;
//  // Sample right below discrete weight (mu = 9.196348006616309467e-01)
//  fake_stream[3] = 6.2798090284813e-01;
//  // Sample right above discrete weight (mu = 9.480603045455671118e-01)
//  fake_stream[4] = 6.2798090284814e-01;
//  // Sample right below discrete weight (mu = 9.480603045455671118e-01)
//  fake_stream[5] = 7.5012793908394e-01;
//  // Sample right above discrete weight (mu = 9.730956823071271744e-01)
//  fake_stream[6] = 7.5012793908395e-01;
//  // Sample at max (mu = 9.730956823071271744e-01)
//  fake_stream[7] = 1.0-1e-12;


//  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//  electron.setEnergy( energy );
//  electron.setDirection( 0.0, 0.0, 1.0 );

//  trials = 10;

//  // Test
//  test_hybrid_distribution->sampleAndRecordTrialsImpl(
//                                                electron.getEnergy(),
//                                                scattering_angle_cosine,
//                                                trials );
//  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
//  FRENSIE_CHECK_EQUAL( trials, 11 );

//  // Test
//  test_hybrid_distribution->sampleAndRecordTrialsImpl(
//                                                electron.getEnergy(),
//                                                scattering_angle_cosine,
//                                                trials );
//  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
//  FRENSIE_CHECK_EQUAL( trials, 12 );

//  // Test
//  test_hybrid_distribution->sampleAndRecordTrialsImpl(
//                                                electron.getEnergy(),
//                                                scattering_angle_cosine,
//                                                trials );
//  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.197507828539278618e-01, 1e-12 );
//  FRENSIE_CHECK_EQUAL( trials, 13 );

//  // Test
//  test_hybrid_distribution->sampleAndRecordTrialsImpl(
//                                                electron.getEnergy(),
//                                                scattering_angle_cosine,
//                                                trials );
//  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.197507828539278618e-01, 1e-12 );
//  FRENSIE_CHECK_EQUAL( trials, 14 );

//  // Test
//  test_hybrid_distribution->sampleAndRecordTrialsImpl(
//                                                electron.getEnergy(),
//                                                scattering_angle_cosine,
//                                                trials );
//  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.607562151148618668e-01, 1e-12 );
//  FRENSIE_CHECK_EQUAL( trials, 15 );

//  // Test
//  test_hybrid_distribution->sampleAndRecordTrialsImpl(
//                                                electron.getEnergy(),
//                                                scattering_angle_cosine,
//                                                trials );
//  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.607562151148618668e-01, 1e-12 );
//  FRENSIE_CHECK_EQUAL( trials, 16 );

//  // Test
//  test_hybrid_distribution->sampleAndRecordTrialsImpl(
//                                                electron.getEnergy(),
//                                                scattering_angle_cosine,
//                                                trials );
//  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.745609416833512784e-01, 1e-12 );
//  FRENSIE_CHECK_EQUAL( trials, 17 );

//  // Test
//  test_hybrid_distribution->sampleAndRecordTrialsImpl(
//                                                electron.getEnergy(),
//                                                scattering_angle_cosine,
//                                                trials );
//  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.745609416833512784e-01, 1e-12 );
//  FRENSIE_CHECK_EQUAL( trials, 18 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sample_logloglog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sample from distribution
  hybrid_distribution->sample( electron.getEnergy(),
                                       outgoing_energy,
                                       scattering_angle_cosine );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_logloglog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrials from distribution
  hybrid_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                                      outgoing_energy,
                                                      scattering_angle_cosine,
                                                      trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterElectron_logloglog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  hybrid_distribution->scatterElectron( electron,
                                                bank,
                                                shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterPositron_logloglog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1.0e-3 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  hybrid_distribution->scatterPositron( positron,
                                                bank,
                                                shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 1.0e-3, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle cosine can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_logloglog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.0e-3 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  hybrid_distribution->scatterAdjointElectron( adjoint_electron,
                                                       bank,
                                                       shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getZDirection(), 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0e-3, 1e-12 );

}


//---------------------------------------------------------------------------//
// LinLinLin Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluate_linlinlin )
{
  FRENSIE_CHECK_THROW( lin_hybrid_distribution->evaluate( 1e-3, -1.0 ),
              std::runtime_error );

  FRENSIE_CHECK_THROW( lin_hybrid_distribution->evaluate( 1e-4, angle_cosine_cutoff ),
              std::runtime_error );


  // double energy, scattering_angle_cosine, pdf_value;

  // // Test: below lowest bin
  // energy = 1e-6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: in between bins
  // energy = 1e-4;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 4.5197683215255630e-01, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: On bin
  // energy = 1e-3;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.9520884073343972e-01, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test on highest bin
  // energy = 1e5;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 2.8685662935501784e-08, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: above highest bin
  // energy = 1e6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluatePDF_linlinlin )
{
  FRENSIE_CHECK_THROW( lin_hybrid_distribution->evaluatePDF( 1e-3, -1.0 ),
              std::runtime_error );

  FRENSIE_CHECK_THROW( lin_hybrid_distribution->evaluatePDF( 1e-4, angle_cosine_cutoff ),
              std::runtime_error );

  // double energy, scattering_angle_cosine, pdf_value;

  // // Test: below lowest bin
  // energy = 1e-6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: in between bins
  // energy = 1e-4;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 5.7535378734118769e-01, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: On bin
  // energy = 1e-3;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.3009586997586640, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test on highest bin
  // energy = 1e5;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 3.3022053062175981e-03, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: above highest bin
  // energy = 1e6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluateCDF_linlinlin )
{
  double energy, scattering_angle_cosine, cdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test: in between bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 9.5119576273110340e-01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 9.5119576278641726e-01, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: right below cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff-1e-10;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.4463192139860923e-01, 1e-12 );

  // Test 2: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.4463192152870505e-01, 1e-12 );

  // Test 3: right above the cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.4463192152870505e-01, 1e-12 );

  // Test 4: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.8288974959925499e-04, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.8288974959925499e-04, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_linlinlin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 5.2409574919482921e-02; // sample mu = 0.1 (cutoff)
  fake_stream[1] = 2.4463192152870505e-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 3.5160367533473e-01; // sample mu = 9.237831271699E-01 (discrete)
  fake_stream[3] = 3.5160367533474e-01; // sample mu = 9.817731638374E-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_lin_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 1
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_lin_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 12 );

  // sampleAndRecordTrialsImpl from distribution
  test_lin_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 3
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.237831271699E-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_lin_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 4
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.817731638374E-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 14 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sample_linlinlin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sample from distribution
  lin_hybrid_distribution->sample( electron.getEnergy(),
                                   outgoing_energy,
                                   scattering_angle_cosine );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_linlinlin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrials from distribution
  lin_hybrid_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                                  outgoing_energy,
                                                  scattering_angle_cosine,
                                                  trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterElectron_linlinlin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  lin_hybrid_distribution->scatterElectron( electron,
                                            bank,
                                            shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterPositron_linlinlin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1.0e-3 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  lin_hybrid_distribution->scatterPositron( positron,
                                            bank,
                                            shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle cosine can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_linlinlin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.0e-3 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  lin_hybrid_distribution->scatterAdjointElectron( adjoint_electron,
                                                   bank,
                                                   shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getZDirection(), 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0e-3, 1e-12 );
}


//---------------------------------------------------------------------------//
// LinLinLin Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluate_linlinlog )
{
  FRENSIE_CHECK_THROW( linlog_hybrid_distribution->evaluate( 1e-3, -1.0 ),
              std::runtime_error );

  FRENSIE_CHECK_THROW( linlog_hybrid_distribution->evaluate( 1e-4, angle_cosine_cutoff ),
              std::runtime_error );


  // double energy, scattering_angle_cosine, pdf_value;

  // // Test: below lowest bin
  // energy = 1e-6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: in between bins
  // energy = 1e-4;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 3.3643123601395386e-01, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: On bin
  // energy = 1e-3;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.9520884073343972e-01, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test on highest bin
  // energy = 1e5;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 2.8685662935501774e-08, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: above highest bin
  // energy = 1e6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluatePDF_linlinlog )
{
  FRENSIE_CHECK_THROW( linlog_hybrid_distribution->evaluatePDF( 1e-3, -1.0 ),
              std::runtime_error );

  FRENSIE_CHECK_THROW( linlog_hybrid_distribution->evaluatePDF( 1e-4, angle_cosine_cutoff ),
              std::runtime_error );

  // double energy, scattering_angle_cosine, pdf_value;

  // // Test: below lowest bin
  // energy = 1e-6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: in between bins
  // energy = 1e-4;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 9.0187599792905204e-01, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: On bin
  // energy = 1e-3;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.3009586997586640, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test on highest bin
  // energy = 1e5;

  // // Test 1: at cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 3.3022053062175981e-03, 1e-12 );

  // // Test 2: right above the cutoff angle
  // scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 3: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test: above highest bin
  // energy = 1e6;

  // // Test 1: at the min angle
  // scattering_angle_cosine = -1.0;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // // Test 2: at the max angle
  // scattering_angle_cosine = 1.0;
  // pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluateCDF_linlinlog )
{
  double energy, scattering_angle_cosine, cdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test: in between bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 9.1419226401063258e-01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 9.1419226411118126e-01, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: right below cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff-1e-10;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.4463192139860923e-01, 1e-12 );

  // Test 2: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.4463192152870505e-01, 1e-12 );

  // Test 3: right above the cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.4463192152870505e-01, 1e-12 );

  // Test 4: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.8288974959925494e-04, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff+1e-10;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 2.8288974959925494e-04, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 5.2409574919482921e-02; // sample mu = 0.1 (cutoff)
  fake_stream[1] = 2.4463192152870505e-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 3.5160367533473e-01; // sample mu = 9.237831271699E-01 (discrete)
  fake_stream[3] = 3.5160367533474e-01; // sample mu = 9.817731638374E-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_linlog_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 1
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlog_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 12 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlog_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 3
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.237831271699E-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlog_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 4
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.817731638374E-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 14 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sample_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sample from distribution
  linlog_hybrid_distribution->sample( electron.getEnergy(),
                                   outgoing_energy,
                                   scattering_angle_cosine );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrials from distribution
  linlog_hybrid_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                                  outgoing_energy,
                                                  scattering_angle_cosine,
                                                  trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterElectron_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  linlog_hybrid_distribution->scatterElectron( electron,
                                            bank,
                                            shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterPositron_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1.0e-3 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  linlog_hybrid_distribution->scatterPositron( positron,
                                            bank,
                                            shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle cosine can be evaluated
FRENSIE_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.0e-3 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  linlog_hybrid_distribution->scatterAdjointElectron( adjoint_electron,
                                                   bank,
                                                   shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getZDirection(), 0.9, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0e-3, 1e-12 );
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
  // Get native data container
  Data::ElectronPhotonRelaxationDataContainer data_container =
    Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

  std::shared_ptr<const std::vector<double> > raw_energy_grid(
           new std::vector<double>( data_container.getElectronEnergyGrid() ) );

  // Construct the grid searcher
  Utility::StandardHashBasedGridSearcher<std::vector<double>,false>
    grid_searcher( raw_energy_grid,
                   raw_energy_grid->front(),
                   raw_energy_grid->back(),
                   raw_energy_grid->size()/10+1 );

  std::shared_ptr<const std::vector<double> > cutoff_cross_section(
    new std::vector<double>( data_container.getCutoffElasticCrossSection() ) );

  double evaluation_tol = 1e-14;

  // Moment preserving elastic cross section
  std::vector<double> moment_preserving_cross_sections;
  size_t mp_threshold_energy_index;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSections<Utility::LogNudgedLogCosLog ,Utility::Correlated>(
                               moment_preserving_cross_sections,
                               mp_threshold_energy_index,
                               data_container,
                               raw_energy_grid,
                               evaluation_tol );

  std::shared_ptr<const std::vector<double> > mp_cross_section(
                 new std::vector<double>( moment_preserving_cross_sections ) );

  // Get the angular energy grid
  std::vector<double> angular_energy_grid =
                            data_container.getElasticAngularEnergyGrid();

  // Get the energy grid
  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();

  double cutoff_angle_cosine = 0.9;

    // LogLogLog
    {
    // Create the full continuous scattering function
    std::shared_ptr<TwoDDist> full_continuous_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LogNudgedLogCosLog ,Utility::Correlated>(
        data_container.getCutoffElasticAngles(),
        data_container.getCutoffElasticPDF(),
        angular_energy_grid,
        full_continuous_function,
        1.0,
        evaluation_tol,
        false );

    // Create the cross section ratios
    std::vector<double> cross_section_ratio( energy_grid.size() );
    for( unsigned n = 0; n < energy_grid.size(); ++n )
    {
    // Get the energy
      energy_grid[n] = (*raw_energy_grid)[n];

    // Get the cutoff cdf value at the angle cosine cutoff
    double cutoff_cdf =
            full_continuous_function->evaluateSecondaryConditionalCDF(
                                                        energy_grid[n],
                                                        cutoff_angle_cosine );

    // Get the reduced cutoff cross section
    double reduced_cross_section = (*cutoff_cross_section)[n]*cutoff_cdf;

    // Get the ratio of the cutoff to the moment preserving cross section
      cross_section_ratio[n] =
        reduced_cross_section/(reduced_cross_section + (*mp_cross_section)[n] );
    }

    // Create cross section ratios
    std::shared_ptr<const Utility::UnivariateDistribution> cross_section_ratios(
      new const Utility::TabularDistribution<Utility::LinLin>(
                                    energy_grid, cross_section_ratio ) );

  // Create the hybrid scattering function
  std::shared_ptr<TwoDDist> hybrid_function;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction<Utility::LogNudgedLogCosLog ,Utility::Correlated>(
            cross_section_ratios,
            data_container.getCutoffElasticAngles(),
            data_container.getCutoffElasticPDF(),
            data_container.getMomentPreservingElasticDiscreteAngles(),
            data_container.getMomentPreservingElasticWeights(),
            angular_energy_grid,
            hybrid_function,
            cutoff_angle_cosine,
            evaluation_tol );


    hybrid_distribution.reset(
        new MonteCarlo::HybridElasticElectronScatteringDistribution(
            hybrid_function,
            angle_cosine_cutoff,
            evaluation_tol ) );

    test_hybrid_distribution.reset(
        new TestHybridElasticElectronScatteringDistribution(
            hybrid_function,
            angle_cosine_cutoff,
            evaluation_tol ) );
    }

    // LinLinLin
    {
    // Create the full continuous scattering function
    std::shared_ptr<TwoDDist> full_continuous_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLin,Utility::Correlated>(
        data_container.getCutoffElasticAngles(),
        data_container.getCutoffElasticPDF(),
        angular_energy_grid,
        full_continuous_function,
        1.0,
        evaluation_tol,
        false );

    // Create the cross section ratios
    std::vector<double> cross_section_ratio( energy_grid.size() );
    for( unsigned n = 0; n < energy_grid.size(); ++n )
    {
    // Get the energy
    energy_grid[n] = (*raw_energy_grid)[n];

    // Get the cutoff cdf value at the angle cosine cutoff
    double cutoff_cdf =
            full_continuous_function->evaluateSecondaryConditionalCDF(
                                                        energy_grid[n],
                                                        cutoff_angle_cosine );

    // Get the reduced cutoff cross section
    double reduced_cross_section = (*cutoff_cross_section)[n]*cutoff_cdf;

    // Get the ratio of the cutoff to the moment preserving cross section
      cross_section_ratio[n] =
        reduced_cross_section/(reduced_cross_section + (*mp_cross_section)[n] );
    }

    // Create cross section ratios
    std::shared_ptr<const Utility::UnivariateDistribution> cross_section_ratios(
      new const Utility::TabularDistribution<Utility::LinLin>(
                                    energy_grid, cross_section_ratio ) );

  // Create the hybrid scattering function
  std::shared_ptr<TwoDDist> hybrid_function;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction<Utility::LinLinLin,Utility::Correlated>(
            cross_section_ratios,
            data_container.getCutoffElasticAngles(),
            data_container.getCutoffElasticPDF(),
            data_container.getMomentPreservingElasticDiscreteAngles(),
            data_container.getMomentPreservingElasticWeights(),
            angular_energy_grid,
            hybrid_function,
            cutoff_angle_cosine,
            evaluation_tol );


    lin_hybrid_distribution.reset(
        new MonteCarlo::HybridElasticElectronScatteringDistribution(
            hybrid_function,
            angle_cosine_cutoff,
            evaluation_tol ) );

    test_lin_hybrid_distribution.reset(
        new TestHybridElasticElectronScatteringDistribution(
            hybrid_function,
            angle_cosine_cutoff,
            evaluation_tol ) );
    }

    // LinLinLog
    {
    // Create the full continuous scattering function
    std::shared_ptr<TwoDDist> full_continuous_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLog,Utility::Correlated>(
        data_container.getCutoffElasticAngles(),
        data_container.getCutoffElasticPDF(),
        angular_energy_grid,
        full_continuous_function,
        1.0,
        evaluation_tol,
        false );

    // Create the cross section ratios
    std::vector<double> cross_section_ratio( energy_grid.size() );
    for( unsigned n = 0; n < energy_grid.size(); ++n )
    {
    // Get the energy
    energy_grid[n] = (*raw_energy_grid)[n];

    // Get the cutoff cdf value at the angle cosine cutoff
    double cutoff_cdf =
            full_continuous_function->evaluateSecondaryConditionalCDF(
                                                        energy_grid[n],
                                                        cutoff_angle_cosine );

    // Get the reduced cutoff cross section
    double reduced_cross_section = (*cutoff_cross_section)[n]*cutoff_cdf;

    // Get the ratio of the cutoff to the moment preserving cross section
      cross_section_ratio[n] =
        reduced_cross_section/(reduced_cross_section + (*mp_cross_section)[n] );
    }

    // Create cross section ratios
    std::shared_ptr<const Utility::UnivariateDistribution> cross_section_ratios(
      new const Utility::TabularDistribution<Utility::LinLin>(
                                    energy_grid, cross_section_ratio ) );


  // Create the hybrid scattering function
  std::shared_ptr<TwoDDist> hybrid_function;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction<Utility::LinLinLog,Utility::Correlated>(
            cross_section_ratios,
            data_container.getCutoffElasticAngles(),
            data_container.getCutoffElasticPDF(),
            data_container.getMomentPreservingElasticDiscreteAngles(),
            data_container.getMomentPreservingElasticWeights(),
            angular_energy_grid,
            hybrid_function,
            cutoff_angle_cosine,
            evaluation_tol );


    linlog_hybrid_distribution.reset(
        new MonteCarlo::HybridElasticElectronScatteringDistribution(
            hybrid_function,
            angle_cosine_cutoff,
            evaluation_tol ) );

    test_linlog_hybrid_distribution.reset(
        new TestHybridElasticElectronScatteringDistribution(
            hybrid_function,
            angle_cosine_cutoff,
            evaluation_tol ) );
    }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHybridElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
