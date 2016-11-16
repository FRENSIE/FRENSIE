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

typedef MonteCarlo::HybridElasticElectronScatteringDistribution HD;

class TestHD : public HD
{
public:
  TestHD( const std::shared_ptr<HD::HybridDistribution>& hybrid_distribution,
          const double cutoff_angle_cosine )
    : HD( hybrid_distribution,
          cutoff_angle_cosine )
  { /* ... */ }

  ~TestHD()
  { /* ... */ }

  // Allow public access to the HybridElasticElectronScatteringDistribution protected member functions
  using HD::sampleAndRecordTrialsImpl;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<HD> hybrid_elastic_distribution;
std::shared_ptr<TestHD> test_hybrid_elastic_distribution;

double angle_cosine_cutoff = 0.9;

//---------------------------------------------------------------------------//
// Tests
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
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 6.48984808511E-01, 1e-12 );

  // Test 2: inbetween cutoff and discrete
  scattering_angle_cosine = 0.91;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at 1st discrete angle
  scattering_angle_cosine = 9.15505102565478457e-01;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 2.11726722771624E-01, 1e-12 );

  // Test 4: at 2nd discrete angle
  scattering_angle_cosine = 9.81773163837444063e-01;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 4.29192299188420E-01 , 1e-12 );

  // Test 5: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.797969617021276445, 1e-12 );

  // Test 2: inbetween cutoff and discrete
  scattering_angle_cosine = 0.91;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at 1st discrete angle
  scattering_angle_cosine = 9.23783127169921725e-01;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.41615401623161025e-01, 1e-12 );

  // Test 4: at 2nd discrete angle
  scattering_angle_cosine = 9.81773163837444063e-01;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 8.58384598376839003e-01, 1e-12 );

  // Test 5: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.0140227058823529248e-04, 1e-12 );

  // Test 2: at 1st discrete angle
  scattering_angle_cosine = 9.33076191050687509e-01;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 5.49699922275026379e-04, 1e-12 );

  // Test 3: inbetween 1st and 2nd discrete angles
  scattering_angle_cosine = 0.95;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 4: at 2nd discrete angle
  scattering_angle_cosine = 9.99076800496474626e-01;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 9.99450300077724951e-01, 1e-12 );

  // Test 5: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_elastic_distribution->evaluate( energy, scattering_angle_cosine );
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
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 6.4898488176239E-01, 1e-12 );

  // Test 2: inbetween cutoff and discrete
  scattering_angle_cosine = 0.91;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at 1st discrete angle
  scattering_angle_cosine = 9.15505102565478457e-01;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 2.11726722771624E-01, 1e-12 );

  // Test 4: at 2nd discrete angle
  scattering_angle_cosine = 9.81773163837444063e-01;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 4.29192299188420E-01 , 1e-12 );

  // Test 5: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.79796951352463207918, 1e-12 );

  // Test 2: inbetween cutoff and discrete
  scattering_angle_cosine = 0.91;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 3: at 1st discrete angle
  scattering_angle_cosine = 9.23783127169921725e-01;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.41615401623161025e-01, 1e-12 );

  // Test 4: at 2nd discrete angle
  scattering_angle_cosine = 9.81773163837444063e-01;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 8.58384598376839003e-01, 1e-12 );

  // Test 5: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 1.014022390233077273e-04, 1e-12 );

  // Test 2: at 1st discrete angle
  scattering_angle_cosine = 9.33076191050687509e-01;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 5.49699922275026379e-04, 1e-12 );

  // Test 3: inbetween 1st and 2nd discrete angles
  scattering_angle_cosine = 0.95;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 4: at 2nd discrete angle
  scattering_angle_cosine = 9.99076800496474626e-01;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 9.99450300077724951e-01, 1e-12 );

  // Test 5: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  pdf_value = hybrid_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
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
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test: Inbetween bins
  energy = 1e-4;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 5.50025223094E-01, 1e-12 );

  // Test 2: inbetween cutoff and discrete
  scattering_angle_cosine = 0.91;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 3: at 1st discrete angle
  scattering_angle_cosine = 9.15505102565478457e-01;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 2.11726722771624E-01, 1e-12 );

  // Test 4: at 2nd discrete angle
  scattering_angle_cosine = 9.81773163837444063e-01;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0 , 1e-12 );

  // Test 5: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: On bin
  energy = 1e-3;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.15004997118745524998, 1e-12 );

  // Test 2: inbetween cutoff and discrete
  scattering_angle_cosine = 0.91;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 3: at 1st discrete angle
  scattering_angle_cosine = 9.23783127169921725e-01;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.41615401623161025e-01, 1e-12 );

  // Test 4: at 2nd discrete angle
  scattering_angle_cosine = 9.81773163837444063e-01;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 5: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test on highest bin
  energy = 1e5;

  // Test 1: at cutoff angle
  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 8.6868172466733645936e-06, 1e-12 );

  // Test 2: at 1st discrete angle
  scattering_angle_cosine = 9.33076191050687509e-01;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 5.49699922275026379e-04, 1e-12 );

  // Test 3: inbetween 1st and 2nd discrete angles
  scattering_angle_cosine = 0.95;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 5.49699922275026379e-04, 1e-12 );

  // Test 4: at 2nd discrete angle
  scattering_angle_cosine = 9.99076800496474626e-01;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test 5: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test: above highest bin
  energy = 1e6;

  // Test 1: at the min angle
  scattering_angle_cosine = -1.0;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );

  // Test 2: at the max angle
  scattering_angle_cosine = 1.0;
  cdf_value = hybrid_elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
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
  test_hybrid_elastic_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 1
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.7, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_elastic_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 2
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_elastic_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test 3
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.237831271699E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // sampleAndRecordTrialsImpl from distribution
  test_hybrid_elastic_distribution->sampleAndRecordTrialsImpl(
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
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 2.44631921528705E-01; // sample mu = 0.9

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sample from distribution
  hybrid_elastic_distribution->sample( electron.getEnergy(),
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
  hybrid_elastic_distribution->sampleAndRecordTrials( electron.getEnergy(),
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
  hybrid_elastic_distribution->scatterElectron( electron,
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
  hybrid_elastic_distribution->scatterAdjointElectron( adjoint_electron,
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

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    data_container.getElectronEnergyGrid().begin(),
    data_container.getElectronEnergyGrid().end() );

  // Construct the grid searcher
  Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false> 
    grid_searcher(
	   energy_grid,
	   energy_grid[0],
	   energy_grid[energy_grid.size()-1],
	   energy_grid.size()/10+1 );

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

  // Create the scattering function
  HD::HybridDistribution hybrid_scattering_function( size );

  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    // Create the cutoff elastic scattering function
    hybrid_scattering_function[n].first = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    Teuchos::Array<double> angles(
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    Teuchos::Array<double> pdf(
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

    hybrid_scattering_function[n].second.reset(
      new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );


    // Get the moment preserving elastic scattering angle cosines at the energy
    std::vector<double> discrete_angles(
        data_container.getMomentPreservingElasticDiscreteAngles(
            angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    std::vector<double> weights(
        data_container.getMomentPreservingElasticWeights(
            angular_energy_grid[n] ) );

    hybrid_scattering_function[n].third.reset(
	  new const Utility::DiscreteDistribution( discrete_angles, weights ) );

    unsigned energy_index =
        grid_searcher.findLowerBinIndex( angular_energy_grid[n] );

    // Get the moment preserving cross section at the given energy
    double mp_cross_section_i =
        Utility::LinLin::interpolate(
            energy_grid[energy_index],
            energy_grid[energy_index+1],
            angular_energy_grid[n],
            mp_cross_section[energy_index],
            mp_cross_section[energy_index+1] );

    // Get the cutoff cross section at the given energy
    double cutoff_cross_section_i =
        Utility::LinLin::interpolate(
            energy_grid[energy_index],
            energy_grid[energy_index+1],
            angular_energy_grid[n],
            cutoff_cross_section[energy_index],
            cutoff_cross_section[energy_index+1] );

    // Get the cutoff cdf value at the angle cosine cutoff
    double cutoff_cdf =
      hybrid_scattering_function[n].second->evaluateCDF( angle_cosine_cutoff );

    // Get the ratio of the cutoff cross section to the moment preserving cross section
    hybrid_scattering_function[n].fourth =
      cutoff_cross_section_i*cutoff_cdf/mp_cross_section_i;
  }

    std::shared_ptr<HD::HybridDistribution> hybrid_distribution(
        new HD::HybridDistribution( hybrid_scattering_function ) );

    hybrid_elastic_distribution.reset(
        new HD( hybrid_distribution,
                angle_cosine_cutoff ) );

    test_hybrid_elastic_distribution.reset(
        new TestHD( hybrid_distribution,
                    angle_cosine_cutoff ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHybridElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
