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
        const int atomic_number )
    : MonteCarlo::AnalogElasticElectronScatteringDistribution(
        elastic_cutoff_distribution,
        atomic_number )
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
  elastic_distribution;

std::shared_ptr<TestAnalogElasticElectronScatteringDistribution>
  test_elastic_distribution;

double mu_cutoff = 1.0;

//---------------------------------------------------------------------------//
// Tests
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
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.83505999999999E-07, 1e-12 );


  scattering_angle_cosine = 0.71;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.00972000000000E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.86945000000000E+05, 1e-12 );


  scattering_angle_cosine = 1.0;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 9.80579728298825E+23, 1e-12 );
  }
  {
  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 4.846349999999990E-07, 1e-12 );


  scattering_angle_cosine = 0.71;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 1.012030000000000E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 9.847530000000000E+05, 1e-12 );


  scattering_angle_cosine = 1.0;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 1.952101737343830E+11, 1e-12 );
  }
  {
  // Test inbetween the two energies
  energy = 2.00E+02;

  scattering_angle_cosine = -0.01;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 4.84464576696329E-07, 1e-12 );


  scattering_angle_cosine = 0.71;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 1.01168130395795E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 9.85083883863282E+05, 1e-9 );


  scattering_angle_cosine = 1.0;
  value =
    elastic_distribution->evaluate( energy,
                                    scattering_angle_cosine );
  // Test 4 energy 3
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
    test_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  double pdf_value = 
    test_elastic_distribution->evaluateScreenedRutherford(
                        energy,
                        scattering_angle_cosine,
                        eta );


  // Test energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 9.80579728298825E+23, tol );

  // Test with a different energy
  energy = 6.625E+01;
  eta = test_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_elastic_distribution->evaluateScreenedRutherford(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 1.952101737343830E+11, tol );


  // Test with a different energy
  energy = 2.00E+02;
  eta = test_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_elastic_distribution->evaluateScreenedRutherford(
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
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.83505995466074E-07, 1e-12 );


  scattering_angle_cosine = .71;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.00971999053167E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 9.86944990745234E+05, 1e-12 );


  scattering_angle_cosine = 1.0;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 4 energy 1
  TEST_FLOATING_EQUALITY( value, 9.80579719103748E+23, 1e-12 );



  // Test with a different energy
  energy = 6.625E+01;

  scattering_angle_cosine = -0.01;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 1 energy 2
  TEST_FLOATING_EQUALITY( value, 4.846347658089040E-07, 1e-12 );


  scattering_angle_cosine = 0.71;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 1.012029510954810E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 3 energy 2
  TEST_FLOATING_EQUALITY( value, 9.847525241359310E+05, 1e-12 );


  scattering_angle_cosine = 1.0;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 4 energy 2
  TEST_FLOATING_EQUALITY( value, 1.952100794025980E+11, 1e-12 );

  // Test inbetween the two energies
  energy = 2.00E+02;

  scattering_angle_cosine = -0.01;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 1 energy 3
  TEST_FLOATING_EQUALITY( value, 4.84464377172137E-07, 1e-12 );


  scattering_angle_cosine = 0.71;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 2 energy 3
  TEST_FLOATING_EQUALITY( value, 1.01168088730521E-05, 1e-12 );

  scattering_angle_cosine = 0.999999;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
  // Test 3 energy 3
  TEST_FLOATING_EQUALITY( value, 9.85083478434198E+05, 1e-9 );

  scattering_angle_cosine = 1.0;
  value =
    elastic_distribution->evaluatePDF( energy,
                                       scattering_angle_cosine );
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
    test_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  double pdf_value = test_elastic_distribution->evaluateScreenedRutherfordPDF(
                        energy,
                        scattering_angle_cosine,
                        eta );


  // Test energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 9.80579719103748E+23, tol );

  // Test with a different energy
  energy = 6.625E+01;
  eta = test_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_elastic_distribution->evaluateScreenedRutherfordPDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 1.952100794025980E+11, tol );


  // Test with a different energy
  energy = 2.00E+02;
  eta = test_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  pdf_value = test_elastic_distribution->evaluateScreenedRutherfordPDF(
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
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.50429930368274E-07, 1e-12 );

  // Test 2 energy 1
  scattering_angle_cosine = 0.71;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.00273614049885E-06, 1e-12 );

  // Test 3 energy 1
  scattering_angle_cosine = 0.999999;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test 4 energy 1
  scattering_angle_cosine = 1.0;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 9.83757207759616E+08, 1e-12 );



  // Test with a different energy
  energy = 6.625E+01;

  // Test 1 energy 2
  scattering_angle_cosine = -0.01;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.507919401217380E-07, 1e-12 );

  // Test 2 energy 2
  scattering_angle_cosine = 0.71;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.007348937973720E-06, 1e-12 );

  // Test 3 energy 2
  scattering_angle_cosine = 0.999999;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.000000000000000E+00, 1e-12 );

  // Test 4 energy 2
  scattering_angle_cosine = 1.0;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 4.39444544314946E+02, 1e-12 );


  // Test inbetween the two energies
  energy = 2.00E+02;

  // Test 1 energy 3
  scattering_angle_cosine = -0.01;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.50737294507791E-07, 1e-12 );

  // Test 2 energy 3
  scattering_angle_cosine = 0.71;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 2.00665263311559E-06, 1e-12 );

  // Test 3 energy 3
  scattering_angle_cosine = 0.999999;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( value, 1.0, 1e-12 );

  // Test 4 energy 3
  scattering_angle_cosine = 1.0;
  value = elastic_distribution->evaluateCDF( energy, scattering_angle_cosine );
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
    test_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  // Calculate the cdf
  double cdf_value = test_elastic_distribution->evaluateScreenedRutherfordCDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 9.83757207759616E+08, tol );


  // Test with a different energy
  energy = 6.625E+01;
  eta = test_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  cdf_value = test_elastic_distribution->evaluateScreenedRutherfordCDF(
                        energy,
                        scattering_angle_cosine,
                        eta );

  // Test energy 2
  TEST_FLOATING_EQUALITY( cdf_value, 4.39444544314946E+02, tol );


  // Test with a different energy
  energy = 2.00E+02;
  eta = test_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  cdf_value = test_elastic_distribution->evaluateScreenedRutherfordCDF(
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
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_elastic_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99999771799414149953, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from distribution
  test_elastic_distribution->sampleAndRecordTrialsImpl(
                                    electron.getEnergy(),
                                    scattering_angle_cosine,
                                    trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999775901926569E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // sampleAndRecordTrialsImpl from distribution
  test_elastic_distribution->sampleAndRecordTrialsImpl(
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
    test_elastic_distribution->evaluateMoliereScreeningConstant(
                                    electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 1.00112938850689E+00, 1e-12 );

 // Test 2
  electron.setEnergy( 1.0e-3 );
  screening_constant =
    test_elastic_distribution->evaluateMoliereScreeningConstant(
                                    electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 9.82490598654803E-03, 1e-12 );

 // Test 3
  electron.setEnergy( 1.0e+5 );
  screening_constant =
    test_elastic_distribution->evaluateMoliereScreeningConstant(
                                    electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 1.00324041845106E-15, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution,
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.9999999775901926569E-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 6.625E+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl from distribution
  elastic_distribution->sample( electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999999775901926569E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 6.625E+01, 1e-12 );
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
  elastic_distribution->sampleAndRecordTrials(
                                          electron.getEnergy(),
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
  elastic_distribution->scatterElectron( electron,
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
  elastic_distribution->scatterAdjointElectron(
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

  // Create the scattering distribution
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function(
        new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLog>(
            function_data,
            1e-6 ) );

  // Create the distribution
  elastic_distribution.reset(
        new MonteCarlo::AnalogElasticElectronScatteringDistribution(
                scattering_function,
                atomic_number  ) );

  // Create the test distribution
  test_elastic_distribution.reset(
        new TestAnalogElasticElectronScatteringDistribution(
                scattering_function,
                atomic_number  ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END(); 

//---------------------------------------------------------------------------//
// end tstAnalogElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
