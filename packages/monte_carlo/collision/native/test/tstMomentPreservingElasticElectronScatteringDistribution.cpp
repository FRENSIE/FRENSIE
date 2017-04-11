//---------------------------------------------------------------------------//
//!
//! \file   tstMomentPreservingElasticElectronScatteringDistribution.cpp
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
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DiscreteDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//

typedef Utility::FullyTabularTwoDDistribution TwoDDist;

class TestMomentPreservingElasticElectronScatteringDistribution : public MonteCarlo::MomentPreservingElasticElectronScatteringDistribution
{
public:
  TestMomentPreservingElasticElectronScatteringDistribution(
        const std::shared_ptr<TwoDDist>& discrete_scattering_distribution,
        const double cutoff_angle_cosine,
        const bool correlated_sampling_mode_on )
    : MonteCarlo::MomentPreservingElasticElectronScatteringDistribution(
        discrete_scattering_distribution,
        cutoff_angle_cosine,
        correlated_sampling_mode_on )
  { /* ... */ }

  ~TestMomentPreservingElasticElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the MomentPreservingElasticElectronScatteringDistribution protected member functions
  using MonteCarlo::MomentPreservingElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::MomentPreservingElasticElectronScatteringDistribution>
  discrete_elastic_distribution;
std::shared_ptr<TestMomentPreservingElasticElectronScatteringDistribution>
  test_discrete_elastic_distribution;

double angle_cosine_cutoff = 0.9;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectronScatteringDistribution,
                   evaluate )
{
  // Set energy in MeV and angle cosine
  double energy = 1.0e-3;
  double scattering_angle_cosine = angle_cosine_cutoff;

  // Calculate the pdf
  double pdf_value =
    discrete_elastic_distribution->evaluate( energy,
                                             scattering_angle_cosine );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );


  scattering_angle_cosine = 9.23783127169921725e-01;
  pdf_value =
    discrete_elastic_distribution->evaluate( energy,
                                             scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 1.41615401623161025e-01, 1e-12 );

  scattering_angle_cosine = 9.81773163837444063e-01;
  pdf_value =
    discrete_elastic_distribution->evaluate( energy,
                                             scattering_angle_cosine );

  // Test 3
  TEST_FLOATING_EQUALITY( pdf_value, 8.58384598376839003e-01, 1e-12 );

  scattering_angle_cosine = 1.0;
  pdf_value =
    discrete_elastic_distribution->evaluate( energy,
                                             scattering_angle_cosine );

  // Test 4
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test with a different energy
  energy = 1.00E+05;

  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value =
    discrete_elastic_distribution->evaluate( energy,
                                             scattering_angle_cosine );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );


  scattering_angle_cosine = 9.33076191050687509e-01;
  pdf_value =
    discrete_elastic_distribution->evaluate( energy,
                                             scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 5.49699922275026379e-04, 1e-12 );


  scattering_angle_cosine = 9.99076800496474626e-01;
  pdf_value =
    discrete_elastic_distribution->evaluate( energy,
                                             scattering_angle_cosine );

  // Test 3
  TEST_FLOATING_EQUALITY( pdf_value, 9.99450300077724951e-01, 1e-12 );

  scattering_angle_cosine = 1.0;
  pdf_value =
    discrete_elastic_distribution->evaluate( energy,
                                             scattering_angle_cosine );

  // Test 4
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectronScatteringDistribution,
                   evaluatePDF )
{
  // Set energy in MeV and angle cosine
  double energy = 1.0e-3;
  double scattering_angle_cosine = angle_cosine_cutoff;

  // Calculate the pdf
  double pdf_value =
    discrete_elastic_distribution->evaluatePDF( energy,
                                                scattering_angle_cosine );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );


  scattering_angle_cosine = 9.23783127169921725e-01;
  pdf_value =
    discrete_elastic_distribution->evaluatePDF( energy,
                                                scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 1.41615401623161025e-01, 1e-12 );

  scattering_angle_cosine = 9.81773163837444063e-01;
  pdf_value =
    discrete_elastic_distribution->evaluatePDF( energy,
                                                scattering_angle_cosine );

  // Test 3
  TEST_FLOATING_EQUALITY( pdf_value, 8.58384598376839003e-01, 1e-12 );

  scattering_angle_cosine = 1.0;
  pdf_value =
    discrete_elastic_distribution->evaluatePDF( energy,
                                                scattering_angle_cosine );

  // Test 4
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // Test with a different energy
  energy = 1.00E+05;

  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value =
    discrete_elastic_distribution->evaluatePDF( energy,
                                                scattering_angle_cosine );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );


  scattering_angle_cosine = 9.33076191050687509e-01;
  pdf_value =
    discrete_elastic_distribution->evaluatePDF( energy,
                                                scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 5.49699922275026379e-04, 1e-12 );


  scattering_angle_cosine = 9.99076800496474626e-01;
  pdf_value =
    discrete_elastic_distribution->evaluatePDF( energy,
                                                scattering_angle_cosine );

  // Test 3
  TEST_FLOATING_EQUALITY( pdf_value, 9.99450300077724951e-01, 1e-12 );

  scattering_angle_cosine = 1.0;
  pdf_value =
    discrete_elastic_distribution->evaluatePDF( energy,
                                                scattering_angle_cosine );

  // Test 4
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectronScatteringDistribution,
                   evaluateCDF )
{
  // Set energy in MeV and angle cosine
  double energy = 1.0e-3;
  double scattering_angle_cosine = angle_cosine_cutoff;

  // Calculate the pdf
  double cdf_value =
    discrete_elastic_distribution->evaluateCDF( energy,
                                                scattering_angle_cosine );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );


  scattering_angle_cosine = 9.23783127169921725e-01;
  cdf_value =
    discrete_elastic_distribution->evaluateCDF( energy,
                                                scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( cdf_value, 1.41615401623161025e-01, 1e-12 );

  scattering_angle_cosine = 9.5e-01;
  cdf_value =
    discrete_elastic_distribution->evaluateCDF( energy,
                                                scattering_angle_cosine );

  // Test 3
  TEST_FLOATING_EQUALITY( cdf_value, 1.41615401623161025e-01, 1e-12 );

  scattering_angle_cosine = 9.81773163837444063e-01;
  cdf_value =
    discrete_elastic_distribution->evaluateCDF( energy,
                                                scattering_angle_cosine );

  // Test 4
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // Test with a different energy
  energy = 1.00E+05;

  scattering_angle_cosine = angle_cosine_cutoff;
  cdf_value =
    discrete_elastic_distribution->evaluateCDF( energy,
                                                scattering_angle_cosine );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );


  scattering_angle_cosine = 9.33076191050687509e-01;
  cdf_value =
    discrete_elastic_distribution->evaluateCDF( energy,
                                                scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( cdf_value, 5.49699922275026379e-04, 1e-12 );


  scattering_angle_cosine = 9.6e-01;
  cdf_value =
    discrete_elastic_distribution->evaluateCDF( energy,
                                                scattering_angle_cosine );

  // Test 3
  TEST_FLOATING_EQUALITY( cdf_value, 5.49699922275026379e-04, 1e-12 );

  scattering_angle_cosine = 9.99076800496474626e-01;
  cdf_value =
    discrete_elastic_distribution->evaluateCDF( energy,
                                                scattering_angle_cosine );

  // Test 4
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 1.4161540162316102e-01; // sample mu = 9.23783127169921725e-01
  fake_stream[1] = 1.42e-01; // sample mu = 9.81773163837444063e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_discrete_elastic_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.23783127169921725e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_discrete_elastic_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.81773163837444063e-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );
}


//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectronScatteringDistribution,
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 1.41615401623161025e-01; // sample mu = 9.23783127169921725e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sample from distribution
  discrete_elastic_distribution->sample( electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.23783127169921725e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 1.41615401623161025e-01; // sample mu = 9.23783127169921725e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrials from distribution
  discrete_elastic_distribution->sampleAndRecordTrials(
                                          electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.23783127169921725e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectronScatteringDistribution,
                   ScatterElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 1.41615401623161025e-01; // sample mu = 9.23783127169921725e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  discrete_elastic_distribution->scatterElectron( electron,
                                             bank,
                                             shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.23783127169921725e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle cosine can be evaluated
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectronScatteringDistribution,
                   ScatterAdjointElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 1.41615401623161025e-01; // sample mu = 9.23783127169921725e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.0e-3 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  discrete_elastic_distribution->scatterAdjointElectron( adjoint_electron,
                                                    bank,
                                                    shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          9.23783127169921725e-01,
                          1e-12 );
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

  // Get the angular energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  TwoDDist::DistributionType function_data( size );

  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    function_data[n].first = angular_energy_grid[n];

    // Get the moment preserving elastic scattering angle cosines at the energy
    std::vector<double> discrete_angles(
        data_container.getMomentPreservingElasticDiscreteAngles(
            angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    std::vector<double> weights(
        data_container.getMomentPreservingElasticWeights(
            angular_energy_grid[n] ) );

    function_data[n].second.reset(
      new const Utility::DiscreteDistribution(
        discrete_angles,
        weights,
        false,
        true ) );
  }

    std::shared_ptr<TwoDDist> scattering_function(
      new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLog>(
        function_data ) );

    bool correlated_sampling_mode_on = true;

    discrete_elastic_distribution.reset(
        new MonteCarlo::MomentPreservingElasticElectronScatteringDistribution(
                scattering_function,
                angle_cosine_cutoff,
                correlated_sampling_mode_on ) );

    test_discrete_elastic_distribution.reset(
        new TestMomentPreservingElasticElectronScatteringDistribution(
                scattering_function,
                angle_cosine_cutoff,
                correlated_sampling_mode_on ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstMomentPreservingElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
