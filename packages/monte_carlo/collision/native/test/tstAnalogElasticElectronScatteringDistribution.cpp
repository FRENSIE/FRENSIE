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
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestAnalogElasticElectronScatteringDistribution : public MonteCarlo::AnalogElasticElectronScatteringDistribution
{
public:
  TestAnalogElasticElectronScatteringDistribution(
        const std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
            elastic_cutoff_distribution,
        const int atomic_number,
        const bool linlinlog_interpolation_mode_on,
        const bool correlated_sampling_mode_on )
    : MonteCarlo::AnalogElasticElectronScatteringDistribution(
        elastic_cutoff_distribution,
        atomic_number,
        linlinlog_interpolation_mode_on,
        correlated_sampling_mode_on )
  { /* ... */ }

  ~TestAnalogElasticElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the AnalogElasticElectronScatteringDistribution protected member functions
  using MonteCarlo::AnalogElasticElectronScatteringDistribution::sampleBin;
  using MonteCarlo::AnalogElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl;
  using MonteCarlo::AnalogElasticElectronScatteringDistribution::evaluateMoliereScreeningConstant;
  using MonteCarlo::AnalogElasticElectronScatteringDistribution::evaluateScreenedRutherford;
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

double mu_cutoff = 1.0;

//---------------------------------------------------------------------------//
// LinLinLog Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluate )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.83505999999999E-07, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.00972000000000E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.86945000000000E+05, 1e-12 );


  scattering_angle_cosine = 1.0;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 9.80579728298825E+23, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 4.846349999999990E-07, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 1.012030000000000E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 9.847530000000000E+05, 1e-12 );


  scattering_angle_cosine = 1.0;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 1.952101737343830E+11, 1e-12 );
  }
  {
  // Test inbetween the two energies
  energy = 200.0;

  scattering_angle_cosine = -0.01;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 4.8452964167333881569e-07, 1e-6 );

  scattering_angle_cosine = 0.0;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 5.0288950473772263006e-07, 1e-6 );

  scattering_angle_cosine = 0.71;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 1.0119114917618560241e-05, 1e-6 );

  scattering_angle_cosine = 0.999999;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 3
  TEST_FLOATING_EQUALITY( value, 9.85083883863282E+05, 1e-9 );

  scattering_angle_cosine = 1.0;
  value = distribution->evaluate( energy, scattering_angle_cosine );
  // Test 5 energy 3
  TEST_FLOATING_EQUALITY( value, 1.582772041017910E+13, 1e-9 );
  }
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford pdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateScreenedRutherford )
{
  double tol = 1.0e-12;
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 1.0;
  double eta = 
    test_distribution->evaluateMoliereScreeningConstant( energy );

  double pdf_value = 
    test_distribution->evaluateScreenedRutherford(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 9.80579728298825E+23, tol );

  // Test with a different energy
  energy = 6.625E+01;
  eta = test_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_distribution->evaluateScreenedRutherford(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 1.952101737343830E+11, tol );


  // Test with a different energy
  energy = 2.00E+02;
  eta = test_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_distribution->evaluateScreenedRutherford(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 3
  TEST_FLOATING_EQUALITY( pdf_value, 1.582772041017910E+13, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluatePDF )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;

  double value =
    distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.83505995466074E-07, 1e-12 );

  scattering_angle_cosine = .71;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.00971999053167E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.86944990745234E+05, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 9.80579719103748E+23, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 4.846347658089040E-07, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 1.012029510954810E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 9.847525241359310E+05, 1e-12 );


  scattering_angle_cosine = 1.0;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 1.952100794025980E+11, 1e-12 );

  // Test inbetween the two energies
  energy = 2.00E+02;

  scattering_angle_cosine = -0.01;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 4.8452944220121082286e-07, 1e-6 );

  scattering_angle_cosine = 0.0;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 5.0288929770839855144e-07, 1e-6 );

  scattering_angle_cosine = 0.71;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 1.0119110752696660311e-05, 1e-6 );

  scattering_angle_cosine = 0.999999;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 9.85083478434198E+05, 1e-9 );

  scattering_angle_cosine = 1.0;
  value = distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 3
  TEST_FLOATING_EQUALITY( value, 1.582771389599460E+13, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford pdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordPDF )
{
  double tol = 1.0e-12;
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 1.0;
  double eta = 
    test_distribution->evaluateMoliereScreeningConstant( energy );

  double pdf_value = test_distribution->evaluateScreenedRutherfordPDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 9.80579719103748E+23, tol );

  // Test with a different energy
  energy = 6.625E+01;
  eta = test_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_distribution->evaluateScreenedRutherfordPDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 1.952100794025980E+11, tol );


  // Test with a different energy
  energy = 2.00E+02;
  eta = test_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_distribution->evaluateScreenedRutherfordPDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 3
  TEST_FLOATING_EQUALITY( pdf_value, 1.582771389599460E+13, 1e-9 );
}

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
  TEST_FLOATING_EQUALITY( value, 1.50429930368274E-07, 1e-12 );

  // Test 2 energy 1
  scattering_angle_cosine = 0.71;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.00273614049885E-06, 1e-12 );

  // Test 3 energy 1
  scattering_angle_cosine = 0.999999;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test 4 energy 1
  scattering_angle_cosine = 1.0;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 9.83757207759616E+08, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  // Test 1 energy 2
  scattering_angle_cosine = -0.01;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.507919401217380E-07, 1e-12 );

  // Test 2 energy 2
  scattering_angle_cosine = 0.71;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.007348937973720E-06, 1e-12 );

  // Test 3 energy 2
  scattering_angle_cosine = 0.999999;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.000000000000000E+00, 1e-12 );

  // Test 4 energy 2
  scattering_angle_cosine = 1.0;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.39444544314946E+02, 1e-12 );

  // Test inbetween the two energies
  energy = 2.00E+02;

  // Test 1 energy 3
  scattering_angle_cosine = -0.01;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.5073724854885435558e-07, 1e-6 );

  // Test 1 energy 3
  scattering_angle_cosine = 0.0;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.55674018468224071e-07, 1e-6 );

  // Test 2 energy 3
  scattering_angle_cosine = 0.71;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.0066525118587287668e-06, 1e-6 );

  // Test 3 energy 3
  scattering_angle_cosine = 0.999999;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test 4 energy 3
  scattering_angle_cosine = 1.0;
  value = distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.94962247641177E+03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford cdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordCDF )
{
  double tol = 1.0e-14;
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 1.0;

  double eta =
    test_distribution->evaluateMoliereScreeningConstant( energy );

  // Calculate the cdf
  double cdf_value = test_distribution->evaluateScreenedRutherfordCDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 9.83757207759616E+08, tol );

  // Test with a different energy
  energy = 6.625E+01;
  eta = test_distribution->evaluateMoliereScreeningConstant( energy );

  cdf_value = test_distribution->evaluateScreenedRutherfordCDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 2
  TEST_FLOATING_EQUALITY( cdf_value, 4.39444544314946E+02, tol );

  // Test with a different energy
  energy = 2.00E+02;
  eta = test_distribution->evaluateMoliereScreeningConstant( energy );

  cdf_value = test_distribution->evaluateScreenedRutherfordCDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 3
  TEST_FLOATING_EQUALITY( cdf_value, 3.94962247641177E+03, tol );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 1.0e-3; // sample mu =  0.99999771799414149953
  fake_stream[1] = 0.5; // sample mu = 0.99999999776919568095
  fake_stream[2] = 1.0 - 1e-15; // sample mu = 1.0

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999771799414149953, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999775901926569E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // sampleAndRecordTrialsImpl from distribution
  test_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateMoliereScreeningConstant )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double screening_constant;

 // Test 1
  screening_constant =
    test_distribution->evaluateMoliereScreeningConstant(
                                    electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 1.00112938850689E+00, 1e-12 );

 // Test 2
  electron.setEnergy( 1.0e-3 );
  screening_constant =
    test_distribution->evaluateMoliereScreeningConstant(
                                    electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 9.82490598654803E-03, 1e-12 );

 // Test 3
  electron.setEnergy( 1.0e+5 );
  screening_constant =
    test_distribution->evaluateMoliereScreeningConstant(
                                    electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 1.00324041845106E-15, 1e-12 );
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


  // Get the max CDF
  double max_cdf = distribution->evaluateCDF( electron.getEnergy(), 1.0 );

  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 1.0/max_cdf; // sample mu = 0.999999
  fake_stream[1] = 0.5; // sample mu = 9.9999999775901926569E-01
  fake_stream[2] = 1.0 - 1e-15; // sample mu = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );

  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );

  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999775901926569E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );

  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );


  // Test energy inbetween energy bins
  electron.setEnergy( 1e-4 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Get the max CDF
  max_cdf = distribution->evaluateCDF( electron.getEnergy(), 1.0 );

  // Set fake random number stream
  fake_stream[0] = 1.0/max_cdf; // sample mu = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );

  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );

  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 4.9274935694433192e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );

  distribution->sample( electron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );

  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999775901926569E-01

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999775901926569E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   ScatterElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999775901926569E-01

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
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.9999999775901926569E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 6.625E+01, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   ScatterAdjointElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999775901926569E-01

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
                          9.9999999775901926569E-01,
                          1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// LinLinLin Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluate_lin )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  {
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.83505999999999E-07, 1e-12 );


  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.00972000000000E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.86945000000000E+05, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 9.80579728298825E+23, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 4.846349999999990E-07, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 1.012030000000000E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 9.847530000000000E+05, 1e-12 );


  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 1.952101737343830E+11, 1e-12 );
  }
  {
  // Test inbetween the two energies
  energy = 200.0;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 4.8463416746395810876e-07, 1e-6 );

  scattering_angle_cosine = 0.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 5.0306513196139206712e-07, 1e-6 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 1.0120293081779165389e-05, 1e-6 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 9.8475593374360516e+05, 1e-9 );


  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluate( energy, scattering_angle_cosine );
  // Test 4 energy 3
  TEST_FLOATING_EQUALITY( value, 1.5822451109881053e+13, 1e-9 );
  }
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford pdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateScreenedRutherford_lin )
{
  double tol = 1.0e-12;
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 1.0;
  double eta = 
    test_lin_distribution->evaluateMoliereScreeningConstant( energy );

  double pdf_value = 
    test_lin_distribution->evaluateScreenedRutherford(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 9.80579728298825E+23, tol );

  // Test with a different energy
  energy = 6.625E+01;
  eta = test_lin_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_lin_distribution->evaluateScreenedRutherford(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 1.952101737343830E+11, tol );

  // Test with a different energy
  energy = 2.00E+02;
  eta = test_lin_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_lin_distribution->evaluateScreenedRutherford(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 3
  TEST_FLOATING_EQUALITY( pdf_value, 1.5822451109881053e+13, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluatePDF_lin )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;

  double value =
    lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.83505995466074E-07, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.00971999053167E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.86944990745234E+05, 1e-12 );


  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 9.80579719103748E+23, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 4.846347658089040E-07, 1e-12 );

  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 1.012029510954810E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 9.847525241359310E+05, 1e-12 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 1.952100794025980E+11, 1e-12 );

  // Test inbetween the two energies
  energy = 2.00E+02;

  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 4.8463393358077665588e-07, 1e-6 );

  scattering_angle_cosine = 0.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 5.0306488918343780226e-07, 1e-6 );
  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 1.0120288197762642812e-05, 1e-6 );

  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 9.8475545850404026e+05, 1e-9 );

  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluatePDF( energy, scattering_angle_cosine );
  // Test 4 energy 3
  TEST_FLOATING_EQUALITY( value, 1.5822443474024773e+13, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford pdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordPDF_lin )
{
  double tol = 1.0e-12;
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 1.0;
  double eta = 
    test_lin_distribution->evaluateMoliereScreeningConstant( energy );

  double pdf_value = test_lin_distribution->evaluateScreenedRutherfordPDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 9.80579719103748E+23, tol );

  // Test with a different energy
  energy = 6.625E+01;
  eta = test_lin_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_lin_distribution->evaluateScreenedRutherfordPDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 1.952100794025980E+11, tol );

  // Test with a different energy
  energy = 2.00E+02;
  eta = test_lin_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_lin_distribution->evaluateScreenedRutherfordPDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 3
  TEST_FLOATING_EQUALITY( pdf_value, 1.5822443474024773e+13, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateCDF_lin )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = -0.01;
  double value;

  // Test 1 energy 1
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.50429930368274E-07, 1e-12 );

  // Test 2 energy 1
  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.00273614049885E-06, 1e-12 );

  // Test 3 energy 1
  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test 4 energy 1
  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 9.83757207759616E+08, 1e-12 );

  // Test with a different energy
  energy = 6.625E+01;

  // Test 1 energy 2
  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.507919401217380E-07, 1e-12 );

  // Test 2 energy 2
  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.007348937973720E-06, 1e-12 );

  // Test 3 energy 2
  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.000000000000000E+00, 1e-12 );

  // Test 4 energy 2
  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.39444544314946E+02, 1e-12 );

  // Test inbetween the two energies
  energy = 2.00E+02;

  // Test 1 energy 3
  scattering_angle_cosine = -0.01;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.5079145517134912672e-07, 1e-6 );

  // Test 2 energy 3
  scattering_angle_cosine = 0.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.5572994587058386904e-07, 1e-6 );

  // Test 3 energy 3
  scattering_angle_cosine = 0.71;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.0073427638173389808e-06, 1e-6 );

  // Test 4 energy 3
  scattering_angle_cosine = 0.999999;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-4 );

  // Test 5 energy 3
  scattering_angle_cosine = 1.0;
  value = lin_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 3.9483076367080416e+03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford cdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateScreenedRutherfordCDF_lin )
{
  double tol = 1.0e-14;
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 1.0;

  double eta =
    test_lin_distribution->evaluateMoliereScreeningConstant( energy );

  // Calculate the cdf
  double cdf_value = test_lin_distribution->evaluateScreenedRutherfordCDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 9.83757207759616E+08, tol );


  // Test with a different energy
  energy = 6.625E+01;
  eta = test_lin_distribution->evaluateMoliereScreeningConstant( energy );

  cdf_value = test_lin_distribution->evaluateScreenedRutherfordCDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 2
  TEST_FLOATING_EQUALITY( cdf_value, 4.39444544314946E+02, tol );


  // Test with a different energy
  energy = 2.00E+02;
  eta = test_lin_distribution->evaluateMoliereScreeningConstant( energy );

  cdf_value = test_lin_distribution->evaluateScreenedRutherfordCDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 3
  TEST_FLOATING_EQUALITY( cdf_value, 3.9483076367080416e+03, tol );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 1.0e-3; // sample mu =  0.99999771799414149953
  fake_stream[1] = 0.5; // sample mu = 0.99999999776919568095
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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999771799414149953, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from lin_distribution
  test_lin_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999775901926569E-01, 1e-12 );
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
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   evaluateMoliereScreeningConstant_lin )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double screening_constant;

 // Test 1
  screening_constant =
    test_lin_distribution->evaluateMoliereScreeningConstant(
                                    electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 1.00112938850689E+00, 1e-12 );

 // Test 2
  electron.setEnergy( 1.0e-3 );
  screening_constant =
    test_lin_distribution->evaluateMoliereScreeningConstant(
                                    electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 9.82490598654803E-03, 1e-12 );

 // Test 3
  electron.setEnergy( 1.0e+5 );
  screening_constant =
    test_lin_distribution->evaluateMoliereScreeningConstant(
                                    electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 1.00324041845106E-15, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   sample_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999775901926569E-01
  fake_stream[1] = 0.5;

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999775901926569E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );


  // Test energy inbetween energy bins
  electron.setEnergy( 1e-4 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // sampleAndRecordTrialsImpl from lin_distribution
  lin_distribution->sample( electron.getEnergy(),
                            outgoing_energy,
                            scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.0895907921721053, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999775901926569E-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  lin_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                           outgoing_energy,        scattering_angle_cosine,
                                           trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999775901926569E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   ScatterElectron_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999775901926569E-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  lin_distribution->scatterElectron( electron, bank, shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.9999999775901926569E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 6.625E+01, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_lin )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999775901926569E-01

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
                          9.9999999775901926569E-01,
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

  // Get the energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType function_data( size );

  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    function_data[n].first = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    Teuchos::Array<double> angles(
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    Teuchos::Array<double> pdf(
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

    function_data[n].second.reset(
      new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );
  }

  double atomic_number = data_container.getAtomicNumber();
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
                atomic_number,
                linlinlog_interpolation_mode_on,
                correlated_sampling_mode_on ) );

    // Create the test distribution
    test_distribution.reset(
        new TestAnalogElasticElectronScatteringDistribution(
                scattering_function,
                atomic_number,
                linlinlog_interpolation_mode_on,
                correlated_sampling_mode_on ) );
    }
    // Create the distributions unsing LinLinLin interpolation
    {
    // Create the scattering distribution
    std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function(
        new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            function_data,
            1e-6,
            1e-7 ) );

    bool linlinlog_interpolation_mode_on = false;
    bool correlated_sampling_mode_on = true;

    // Create the distribution
    lin_distribution.reset(
        new MonteCarlo::AnalogElasticElectronScatteringDistribution(
                scattering_function,
                atomic_number,
                linlinlog_interpolation_mode_on,
                correlated_sampling_mode_on ) );

    // Create the test distribution
    test_lin_distribution.reset(
        new TestAnalogElasticElectronScatteringDistribution(
                scattering_function,
                atomic_number,
                linlinlog_interpolation_mode_on,
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
