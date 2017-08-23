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
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
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
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
    : MonteCarlo::HybridElasticElectronScatteringDistribution(
                            continuous_distribution,
                            discrete_distribution,
                            cross_section_ratios,
                            cutoff_angle_cosine,
                            correlated_sampling_mode_on,
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
    hybrid_distribution, lin_hybrid_distribution, linlog_hybrid_distribution;
std::shared_ptr<TestHybridElasticElectronScatteringDistribution>
    test_hybrid_distribution, test_lin_hybrid_distribution, test_linlog_hybrid_distribution;

double angle_cosine_cutoff = 0.9;
bool correlated_sampling_mode_on = true;

//---------------------------------------------------------------------------//
// LogLogLog Tests
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
  TEST_FLOATING_EQUALITY( pdf_value, 4.1322732652776589e-01, 1e-12 );

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
  TEST_FLOATING_EQUALITY( pdf_value, 2.3657400354083533e-01, 1e-12 );

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
  TEST_FLOATING_EQUALITY( pdf_value, 4.9492006233424737e-08, 1e-12 );

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
  TEST_FLOATING_EQUALITY( pdf_value, 1.0628794758553139, 1e-12 );

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
  TEST_FLOATING_EQUALITY( pdf_value, 1.5612401544380923, 1e-12 );

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
  TEST_FLOATING_EQUALITY( pdf_value, 5.5792715520311190e-03, 1e-12 );

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
  TEST_FLOATING_EQUALITY( cdf_value, 5.6660567494182890e-01, 1e-12 );

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
  TEST_FLOATING_EQUALITY( cdf_value, 2.4463192152870505e-01, 1e-12 );

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
  TEST_FLOATING_EQUALITY( cdf_value, 2.8288974959925494e-04, 1e-12 );

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
  fake_stream[0] = 5.1897842425367033e-02; // sample mu = 0.1 (cutoff)
  fake_stream[1] = 2.4463192152870505e-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 3.5160367533473e-01; // sample mu = 9.237831271699E-01 (discrete)
  fake_stream[3] = 3.5160367533474e-01; // sample mu = 9.817731638374E-01 (discrete)

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.2378312716992173e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 4
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.8177316383744406e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 14 );


  // Sample between 1e-5 and 1e-3 distribution bin
  double energy = 1e-4;

  fake_stream.resize( 8 );
  // Sample mu = 0.1 (cutoff)
  fake_stream[0] = 1.8290157505997623e-01;
  // Sample at sampling ratio (mu = 0.9)
  fake_stream[1] = 5.6660567494182890e-01;
  // Sample right above sampling ratio (mu = 9.197507828539278618e-01)
  fake_stream[2] = 5.6660567494183e-01;
  // Sample right below discrete weight (mu = 9.196348006616309467e-01)
  fake_stream[3] = 6.2798098634613e-01;
  // Sample right above discrete weight (mu = 9.480603045455671118e-01)
  fake_stream[4] = 6.2798098634615e-01;
  // Sample right below discrete weight (mu = 9.480603045455671118e-01)
  fake_stream[5] = 7.501279951666e-01;
  // Sample right above discrete weight (mu = 9.730956823071271744e-01)
  fake_stream[6] = 7.5012799516661e-01;
  // Sample at max (mu = 9.730956823071271744e-01)
  fake_stream[7] = 1.0-1e-12;


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  electron.setEnergy( energy );
  electron.setDirection( 0.0, 0.0, 1.0 );

  trials = 10;

  // Test
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // Test
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // Test
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.197507828539278618e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // Test
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.197507828539278618e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 14 );

  // Test
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.607562151148618668e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 15 );

  // Test
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.607562151148618668e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 16 );

  // Test
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.745609416833512784e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 17 );

  // Test
  test_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.745609416833512784e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 18 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sample )
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
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

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
  TEST_FLOATING_EQUALITY( pdf_value, 4.2429073574554144e-01, 1e-12 );

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
  TEST_FLOATING_EQUALITY( pdf_value, 2.3657400354083533e-01, 1e-12 );

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
  TEST_FLOATING_EQUALITY( pdf_value, 4.9492006233424737e-08, 1e-12 );

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
  TEST_FLOATING_EQUALITY( pdf_value, 7.8045844433362543e-01, 1e-12 );

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
  TEST_FLOATING_EQUALITY( pdf_value, 1.5612401544380923, 1e-12 );

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
  TEST_FLOATING_EQUALITY( pdf_value, 5.5792715520311190e-03, 1e-12 );

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
  TEST_FLOATING_EQUALITY( cdf_value, 7.2168815213236748e-01, 1e-12 );

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
  TEST_FLOATING_EQUALITY( cdf_value, 2.8288974959925494e-04, 1e-12 );

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
  fake_stream[0] = 5.1897842425367033e-02; // sample mu = 0.1 (cutoff)
  fake_stream[1] = 2.4463192152870505e-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 3.5160367533473e-01; // sample mu = 9.237831271699E-01 (discrete)
  fake_stream[3] = 3.5160367533474e-01; // sample mu = 9.817731638374E-01 (discrete)

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
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
  fake_stream[0] = 2.4463192152870505e-01; // sample mu = 0.9

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
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(), 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0e-3, 1e-12 );
}


//---------------------------------------------------------------------------//
// LinLinLin Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluate_linlinlog )
{
  double energy, scattering_angle_cosine, pdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 5.3997704242990696e-01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 2.3657400354083533e-01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 4.9492006233424737e-08, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = linlog_hybrid_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluatePDF_linlinlog )
{
  double energy, scattering_angle_cosine, pdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 2.4678403539087039, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.5612401544380923, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 5.5792715520311190e-03, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = linlog_hybrid_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   evaluateCDF_linlinlog )
{
  double energy, scattering_angle_cosine, cdf_value;

  // Test: below lowest bin
  energy = 1e-6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 7.1187273796892825e-01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 2.4463192152870505e-01, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 2.8288974959925494e-04, 1e-12 );

  // Test 2: right above the cutoff angle
  scattering_angle_cosine = 0.9001;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 3: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = linlog_hybrid_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_linlinlog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 5.1897842425367033e-02; // sample mu = 0.1 (cutoff)
  fake_stream[1] = 2.4463192152870505e-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 3.5160367533473e-01; // sample mu = 9.237831271699E-01 (discrete)
  fake_stream[3] = 3.5160367533474e-01; // sample mu = 9.817731638374E-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_linlog_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 1
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlog_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 2
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlog_hybrid_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 3
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.237831271699E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_linlog_hybrid_distribution->sampleAndRecordTrialsImpl(
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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
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
  unsigned trials = 10;

  // sampleAndRecordTrials from distribution
  linlog_hybrid_distribution->sampleAndRecordTrials( electron.getEnergy(),
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
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle cosine can be evaluated
TEUCHOS_UNIT_TEST( HybridElasticElectronScatteringDistribution,
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

  // Get the energy grid
  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();

  double evaluation_tol = 1e-7;
  double cutoff_angle_cosine = 0.9;

    // LogLogLog
    {
    // Set the full continuous scattering function
    std::shared_ptr<TwoDDist> full_continuous_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LogLogLog>(
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    angular_energy_grid,
    full_continuous_function,
    1.0,
    evaluation_tol,
    false );


    // Set the continuous scattering function
    std::shared_ptr<TwoDDist> continuous_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LogLogLog>(
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    angular_energy_grid,
    continuous_function,
    cutoff_angle_cosine,
    evaluation_tol,
    false );


    // Set the discrete scattering function
    std::shared_ptr<TwoDDist> discrete_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LogLogLog>(
    data_container.getMomentPreservingElasticDiscreteAngles(),
    data_container.getMomentPreservingElasticWeights(),
    angular_energy_grid,
    discrete_function,
    1.0,
    evaluation_tol,
    true );

    std::vector<double> cross_section_ratio( energy_grid.size() );
    for( unsigned n = 0; n < energy_grid.size(); ++n )
    {
    // Get the energy
    energy_grid[n] = raw_energy_grid[n];

    // Get the cutoff cdf value at the angle cosine cutoff
    double cutoff_cdf =
            full_continuous_function->evaluateSecondaryConditionalCDFExact(
                                                        energy_grid[n],
                                                        cutoff_angle_cosine );

    // Get the ratio of the cutoff to the moment preserving cross section
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
            correlated_sampling_mode_on,
            evaluation_tol ) );

    test_hybrid_distribution.reset(
        new TestHybridElasticElectronScatteringDistribution(
            continuous_function,
            discrete_function,
            cross_section_ratios,
            angle_cosine_cutoff,
            correlated_sampling_mode_on,
            evaluation_tol ) );
    }

    // LinLinLin
    {
    // Set the full continuous scattering function
    std::shared_ptr<TwoDDist> full_continuous_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLin>(
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    angular_energy_grid,
    full_continuous_function,
    1.0,
    evaluation_tol,
    false );


    // Set the continuous scattering function
    std::shared_ptr<TwoDDist> continuous_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLin>(
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    angular_energy_grid,
    continuous_function,
    cutoff_angle_cosine,
    evaluation_tol,
    false );


    // Set the discrete scattering function
    std::shared_ptr<TwoDDist> discrete_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLin>(
    data_container.getMomentPreservingElasticDiscreteAngles(),
    data_container.getMomentPreservingElasticWeights(),
    angular_energy_grid,
    discrete_function,
    1.0,
    evaluation_tol,
    true );

    std::vector<double> cross_section_ratio( energy_grid.size() );
    for( unsigned n = 0; n < energy_grid.size(); ++n )
    {
    // Get the energy
    energy_grid[n] = raw_energy_grid[n];

    // Get the cutoff cdf value at the angle cosine cutoff
    double cutoff_cdf =
            full_continuous_function->evaluateSecondaryConditionalCDFExact(
                                                        energy_grid[n],
                                                        cutoff_angle_cosine );

    // Get the ratio of the cutoff to the moment preserving cross section
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
            correlated_sampling_mode_on,
            evaluation_tol ) );

    test_lin_hybrid_distribution.reset(
        new TestHybridElasticElectronScatteringDistribution(
            continuous_function,
            discrete_function,
            cross_section_ratios,
            angle_cosine_cutoff,
            correlated_sampling_mode_on,
            evaluation_tol ) );
    }

    // LinLinLog
    {
    // Set the full continuous scattering function
    std::shared_ptr<TwoDDist> full_continuous_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLog>(
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    angular_energy_grid,
    full_continuous_function,
    1.0,
    evaluation_tol,
    false );


    // Set the continuous scattering function
    std::shared_ptr<TwoDDist> continuous_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLog>(
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    angular_energy_grid,
    continuous_function,
    cutoff_angle_cosine,
    evaluation_tol,
    false );


    // Set the discrete scattering function
    std::shared_ptr<TwoDDist> discrete_function;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLog>(
    data_container.getMomentPreservingElasticDiscreteAngles(),
    data_container.getMomentPreservingElasticWeights(),
    angular_energy_grid,
    discrete_function,
    1.0,
    evaluation_tol,
    true );

    std::vector<double> cross_section_ratio( energy_grid.size() );
    for( unsigned n = 0; n < energy_grid.size(); ++n )
    {
    // Get the energy
    energy_grid[n] = raw_energy_grid[n];

    // Get the cutoff cdf value at the angle cosine cutoff
    double cutoff_cdf =
            full_continuous_function->evaluateSecondaryConditionalCDFExact(
                                                        energy_grid[n],
                                                        cutoff_angle_cosine );

    // Get the ratio of the cutoff to the moment preserving cross section
      cross_section_ratio[n] =
        cutoff_cross_section[n]*cutoff_cdf/mp_cross_section[n];
    }

    // Create cross section ratios
    std::shared_ptr<const Utility::OneDDistribution> cross_section_ratios(
      new const Utility::TabularDistribution<Utility::LinLin>(
                                    energy_grid, cross_section_ratio ) );

    linlog_hybrid_distribution.reset(
        new MonteCarlo::HybridElasticElectronScatteringDistribution(
            continuous_function,
            discrete_function,
            cross_section_ratios,
            angle_cosine_cutoff,
            correlated_sampling_mode_on,
            evaluation_tol ) );

    test_linlog_hybrid_distribution.reset(
        new TestHybridElasticElectronScatteringDistribution(
            continuous_function,
            discrete_function,
            cross_section_ratios,
            angle_cosine_cutoff,
            correlated_sampling_mode_on,
            evaluation_tol ) );
    }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHybridElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
