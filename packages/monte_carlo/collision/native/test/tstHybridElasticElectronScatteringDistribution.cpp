//---------------------------------------------------------------------------//
//!
//! \file   tstHybridElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Moment Preserving elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//

class TestHybridElasticElectronScatteringDistribution : public MonteCarlo::HybridElasticElectronScatteringDistribution
{
public:

  typedef MonteCarlo::HybridElasticElectronScatteringDistribution::TwoDDist
            TwoDDist;

  TestHybridElasticElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& continuous_distribution,
    const std::shared_ptr<TwoDDist>& discrete_distribution,
    const std::shared_ptr<const Utility::OneDDistribution>& cross_section_ratios,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
    : MonteCarlo::HybridElasticElectronScatteringDistribution(
                            continuous_distribution,
                            discrete_distribution,
                            cross_section_ratios,
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
typedef Utility::FullyTabularTwoDDistribution TwoDDist;

std::shared_ptr<MonteCarlo::HybridElasticElectronScatteringDistribution>
    hybrid_distribution, lin_hybrid_distribution;
std::shared_ptr<TestHybridElasticElectronScatteringDistribution>
    test_hybrid_distribution, test_lin_hybrid_distribution;

double angle_cosine_cutoff = 0.9;

//---------------------------------------------------------------------------//
// LinLinLog Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluate )
{
  double energy, scattering_angle_cosine, pdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 5.602720631514607419e+01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.300958868493, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 3.30220600215765E-03, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluatePDF )
{
  double energy, scattering_angle_cosine, pdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 5.602719921040877438e+01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.30095869975870E+00, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 3.30220497423299E-03, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluateCDF )
{
  double energy, scattering_angle_cosine, cdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.92652534676358189181, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 2.44631921528705E-01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 2.82889721159159E-04, 1e-12 );

  // Test 2: at 1st discrete angle
  scattering_angle_cosine = 0.9001;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 1.30241599279513E-01; // sample mu = 0.7 (cutoff)
  fake_stream[1] = 2.44631921528705E-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 0.3; // sample mu = 9.237831271699E-01 (discrete)
  fake_stream[3] = 0.352; // sample mu = 9.817731638374E-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 1
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.7, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 2
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 3
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.237831271699E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 4
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.817731638374E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 14 );


  // Sample between 1e-5 and 1e-3 distribution bin
  double energy = 1e-4;

  // Discrete angles for energy bin 1e-5 and 1e-3
  double lower_angle_1 = 9.155051025654784569e-01;
  double lower_angle_2 = 9.644948973992915064e-01;
  double upper_angle_1 = 9.237831271699217250e-01;
  double upper_angle_2 = 9.817731638374440628e-01;

  // Interpolation fraction for incoming energy 1e-4
  double log_interpolation = std::log(energy/1e-5)/std::log(1e-3/1e-5);

  // Interpolated discrete angles for incoming energy 1e-4
  double interp_angle_1 =
            lower_angle_1 + ( upper_angle_1 - lower_angle_1 )*log_interpolation;
  double interp_angle_2 =
            lower_angle_1 + ( upper_angle_2 - lower_angle_1 )*log_interpolation;
  double interp_angle_3 =
            lower_angle_2 + ( upper_angle_2 - lower_angle_2 )*log_interpolation;

  // Weights of discrete angles for energy bin 1e-5 and 1e-3
  double lower_weight_1 = 4.234534455432483191e-01;
  double lower_weight_2 = 5.765465544567517364e-01;
  double upper_weight_1 = 1.416154016231610246e-01;
  double upper_weight_2 = 8.583845983768390031e-01;

  // Sampling values for energy 1e-4
  double sampling_ratio = 0.92652534676358189181;
  double cs_ratio = 12.610135685599178856;
  double cdf_lower_1 = ( lower_weight_1 + cs_ratio )/(1.0+cs_ratio);
  double cdf_lower_2 = ( lower_weight_2 + cs_ratio )/(1.0+cs_ratio);
  double cdf_upper_1 = ( upper_weight_1 + cs_ratio )/(1.0+cs_ratio);
  double cdf_upper_2 = ( upper_weight_2 + cs_ratio )/(1.0+cs_ratio);

  fake_stream.resize( 7 );
  // Sample at sampling ratio (mu = 0.9)
  fake_stream[0] = sampling_ratio;
  // Sample right above sampling ratio (mu = 9.196441148677001465e-01)
  fake_stream[1] = sampling_ratio + (cdf_upper_1 - sampling_ratio)/50.0;
  // Sample right below upper weight 1 (mu = 9.196441148677001465e-01)
  fake_stream[2] = cdf_upper_1 - (cdf_upper_1 - sampling_ratio)/50.0;
  // Sample at upper weight 1 (mu = 9.486391332014612043e-01)
  fake_stream[3] = cdf_upper_1;
  // Sample right below lower weight 1 (mu = 9.486391332014612043e-01)
  fake_stream[4] = cdf_lower_1 - (cdf_lower_1 - cdf_upper_1)/50.0;
  // Sample at lower weight 1 (mu = 9.731340306183677846e-01)
  fake_stream[5] = cdf_lower_1;
  // Sample at max (mu = 9.731340306183677846e-01)
  fake_stream[6] = 1.0-1e-12;


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  electron.setEnergy( 1.0e-4 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  scattering_angle_cosine;
  trials = 10;

  // Test 1
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // Test 2
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, interp_angle_1, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // Test 3
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, interp_angle_1, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // Test 4
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, interp_angle_2, 1e-12 );
  TEST_EQUALITY_CONST( trials, 14 );

  // Test 5
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, interp_angle_2, 1e-12 );
  TEST_EQUALITY_CONST( trials, 15 );

  // Test 6
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, interp_angle_3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 16 );

  // Test 7
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, interp_angle_3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 17 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.44631921528705E-01;

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.44631921528705E-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrials from distribution
  hybrid_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                                      outgoing_energy,
                                                      scattering_angle_cosine,
                                                      trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.44631921528705E-01; // sample mu = 0.9

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
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle cosine can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterAdjointElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.44631921528705E-01; // sample mu = 0.9

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
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(), 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0e-3, 1e-12 );

}


//---------------------------------------------------------------------------//
// LinLinLin Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluate_lin )
{
  double energy, scattering_angle_cosine, pdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.117726458931536371e+01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.3009588684930047, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 3.3022060021574385e-03, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = lin_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluatePDF_lin )
{
  double energy, scattering_angle_cosine, pdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.117726342122608862e+01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.3009586997586637e+00, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 3.3022049742327912e-03, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = lin_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluateCDF_lin )
{
  double energy, scattering_angle_cosine, cdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 9.297499658314400950e-01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 2.4463192152870505e-01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 2.82889721159159E-04, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = lin_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 1.30241599279513E-01; // sample mu = 0.7 (cutoff)
  fake_stream[1] = 2.44631921528705E-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 0.3; // sample mu = 9.237831271699E-01 (discrete)
  fake_stream[3] = 0.352; // sample mu = 9.817731638374E-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_lin_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 1
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.7, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_lin_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 2
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // sampleAndRecordTrialsImpl from distribution
  test_lin_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 3
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.237831271699E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_lin_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 4
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.817731638374E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 14 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sample_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.44631921528705E-01;

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.44631921528705E-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrials from distribution
  lin_hybrid_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                                  outgoing_energy,
                                                  scattering_angle_cosine,
                                                  trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterElectron_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.44631921528705E-01; // sample mu = 0.9

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
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle cosine can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.44631921528705E-01; // sample mu = 0.9

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
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(), 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0e-3, 1e-12 );

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
  // create Native distributions
  {
  // Get native data container
  Data::ElectronPhotonRelaxationDataContainer data_container =
    Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

  Teuchos::ArrayRCP<double> raw_energy_grid;
  raw_energy_grid.assign(
    data_container.getElectronEnergyGrid().begin(),
    data_container.getElectronEnergyGrid().end() );

  // Construct the grid searcher
  Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false> 
    grid_searcher(
       raw_energy_grid,
       raw_energy_grid[0],
       raw_energy_grid[raw_energy_grid.size()-1],
       raw_energy_grid.size()/10+1 );

  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container.getCutoffElasticCrossSection().begin(),
    data_container.getCutoffElasticCrossSection().end() );

  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    data_container.getMomentPreservingCrossSection().begin(),
    data_container.getMomentPreservingCrossSection().end() );

  // Get the angular energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Get the distribution data
  TwoDDist::DistributionType continuous_function_data( size );
  TwoDDist::DistributionType discrete_function_data( size );

  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    // Get the energy
    continuous_function_data[n].first = angular_energy_grid[n];
    discrete_function_data[n].first = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    Teuchos::Array<double> angles(
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    Teuchos::Array<double> pdf(
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

    continuous_function_data[n].second.reset(
      new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );


    // Get the moment preserving elastic scattering angle cosines at the energy
    std::vector<double> discrete_angles(
        data_container.getMomentPreservingElasticDiscreteAngles(
            angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    std::vector<double> weights(
        data_container.getMomentPreservingElasticWeights(
            angular_energy_grid[n] ) );

    discrete_function_data[n].second.reset(
      new const Utility::DiscreteDistribution( discrete_angles, weights, false, true ) );
  }

    double evaluation_tol = 1e-7;
    double cutoff_angle_cosine = 0.9;

    // LinLinLog
    {
    // Set the continuous scattering function
    std::shared_ptr<TwoDDist> continuous_function(
        new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLog>(
          continuous_function_data,
          1e-6,
          evaluation_tol ) );

    // Set the discrete scattering function
    std::shared_ptr<TwoDDist> discrete_function(
        new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLog>(
          discrete_function_data,
          1e-6,
          evaluation_tol ) );

    std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
    std::vector<double> cross_section_ratio( energy_grid.size() );
    for( unsigned n = 0; n < energy_grid.size(); ++n )
    {
      // Get the cutoff cdf value at the angle cosine cutoff
      double cutoff_cdf =
              continuous_function->evaluateSecondaryConditionalCDFExact(
                                                          energy_grid[n],
                                                          cutoff_angle_cosine );

      // Get the ratio of the cutoff cross section to the moment preserving cross section
      cross_section_ratio[n] =
        cutoff_cross_section[n]*cutoff_cdf/mp_cross_section[n];
    }

    // Create cross section ratios
    std::shared_ptr<const Utility::OneDDistribution> cross_section_ratios(
        new const Utility::TabularDistribution<Utility::LinLin>(
                                        energy_grid, cross_section_ratio ) );


    hybrid_distribution.reset(
        new MonteCarlo::HybridElasticElectronScatteringDistribution(
            continuous_function,
            discrete_function,
            cross_section_ratios,
            angle_cosine_cutoff,
            evaluation_tol ) );

    test_hybrid_distribution.reset(
        new TestHybridElasticElectronScatteringDistribution(
            continuous_function,
            discrete_function,
            cross_section_ratios,
            angle_cosine_cutoff,
            evaluation_tol ) );
    }

    // LinLinLin
    {
    // Set the continuous scattering function
    std::shared_ptr<TwoDDist> continuous_function(
        new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
          continuous_function_data,
          1e-6,
          evaluation_tol ) );

    // Set the discrete scattering function
    std::shared_ptr<TwoDDist> discrete_function(
        new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
          discrete_function_data,
          1e-6,
          evaluation_tol ) );

    std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
    std::vector<double> cross_section_ratio( energy_grid.size() );
    for( unsigned n = 0; n < energy_grid.size(); ++n )
    {
      // Get the cutoff cdf value at the angle cosine cutoff
      double cutoff_cdf =
              continuous_function->evaluateSecondaryConditionalCDFExact(
                                                          energy_grid[n],
                                                          cutoff_angle_cosine );

      // Get the ratio of the cutoff cross section to the moment preserving cross section
      cross_section_ratio[n] =
        cutoff_cross_section[n]*cutoff_cdf/mp_cross_section[n];
    }

    // Create cross section ratios
    std::shared_ptr<const Utility::OneDDistribution> cross_section_ratios(
        new const Utility::TabularDistribution<Utility::LinLin>(
                                        energy_grid, cross_section_ratio ) );

    lin_hybrid_distribution.reset(
        new MonteCarlo::HybridElasticElectronScatteringDistribution(
            continuous_function,
            discrete_function,
            cross_section_ratios,
            angle_cosine_cutoff,
            evaluation_tol ) );

    test_lin_hybrid_distribution.reset(
        new TestHybridElasticElectronScatteringDistribution(
            continuous_function,
            discrete_function,
            cross_section_ratios,
            angle_cosine_cutoff,
            evaluation_tol ) );
    }
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHybridElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
