//---------------------------------------------------------------------------//
//!
//! \file   tstElasticElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestElasticElectronScatteringDistributionNativeFactory : public MonteCarlo::ElasticElectronScatteringDistributionNativeFactory
{
public:

  // Allow public access to the protected member functions
  using MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridCrossSectionRatios;
  using MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction;
  using MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunctionInSubrange;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
  typedef Utility::FullyTabularTwoDDistribution TwoDDist;

std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer>
    adjoint_data_container;
std::shared_ptr< const MonteCarlo::CutoffElasticElectronScatteringDistribution>
  native_cutoff_elastic_distribution;
std::shared_ptr< const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
  native_sr_elastic_distribution;
std::shared_ptr< const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution>
  native_mp_elastic_distribution;
std::shared_ptr< const MonteCarlo::CoupledElasticElectronScatteringDistribution>
  native_coupled_elastic_distribution;

Teuchos::ArrayRCP<double> energy_grid, cutoff_cross_section, total_cross_section,
  adjoint_energy_grid, adjoint_cutoff_cross_section, adjoint_total_cross_section;

bool correlated_sampling_mode_on = true;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the angular grid can be returned
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   getAngularGridAboveCutoff )
{

  double cutoff_angle_cosine = -1.0;
  double energy = 1.0e-5;
  std::vector<double> angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAboveCutoff(
                    data_container->getCutoffElasticAngles(),
                    energy,
                    cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

  energy = 1.001e-5;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAboveCutoff(
                    data_container->getCutoffElasticAngles(),
                    energy,
                    cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

  angular_grid.clear();

  cutoff_angle_cosine = 0.9;
  energy = 1.0e-5;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAboveCutoff(
                    data_container->getCutoffElasticAngles(),
                    energy,
                    cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), 0.9 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

  angular_grid.clear();

  cutoff_angle_cosine = -1.0;
  energy = 1.0e+5;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAboveCutoff(
                    data_container->getCutoffElasticAngles(),
                    energy,
                    cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 90 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

  cutoff_angle_cosine = -1.0;
  energy = 9.0e+4;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAboveCutoff(
                    data_container->getCutoffElasticAngles(),
                    energy,
                    cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 90 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );


  cutoff_angle_cosine = -1.0;
  energy = 1.0e-5;
  std::vector<double> raw_grid = 
    data_container->getCutoffElasticAngles( energy );
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAboveCutoff(
                                                raw_grid,
                                                cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

  angular_grid.clear();

  cutoff_angle_cosine = 0.9;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAboveCutoff(
                                                raw_grid,
                                                cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), 0.9 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

  angular_grid.clear();

  cutoff_angle_cosine = -1.0;
  energy = 1.0e+5;
  raw_grid = data_container->getCutoffElasticAngles( energy );
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAboveCutoff(
                                                raw_grid,
                                                cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 90 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );
}

//---------------------------------------------------------------------------//
// Check that the angular grid can be returned
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   getAngularGrid )
{
  std::vector<double> angular_grid;
  double cutoff_angle_cosine = 0.9;

  // Test lowerest energy bin
  double energy = 1.0e-5;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
        data_container->getCutoffElasticAngles(energy),
        cutoff_angle_cosine );

  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.9 );

  // Test highest energy bin
  energy = 1.0e+5;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
        data_container->getCutoffElasticAngles(energy),
        cutoff_angle_cosine );

  TEST_EQUALITY_CONST( angular_grid.size(), 21 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the angular grid can be returned
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   getAngularGridAndPDF )
{
  std::vector<double> angular_grid, evaluated_pdf;
  double cutoff_angle_cosine = 0.9;

  // Test lowest energy bin
  double energy = 1.0e-5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(energy),
    data_container->getCutoffElasticPDF(energy),
    cutoff_angle_cosine );

  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.9 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 2 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 0.5 );
  TEST_FLOATING_EQUALITY( evaluated_pdf.back(), 0.5, 1e-12 );


  // Test mid energy bin
  energy = 1.0e-3;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(energy),
    data_container->getCutoffElasticPDF(energy),
    cutoff_angle_cosine );

  TEST_EQUALITY_CONST( angular_grid.size(), 51 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.9 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 51 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 5.96843e-01 );
  TEST_FLOATING_EQUALITY( evaluated_pdf.back(), 7.2266e-01, 1e-12 );

  // Test highest energy bin
  energy = 1.0e+5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(energy),
    data_container->getCutoffElasticPDF(energy),
    cutoff_angle_cosine );

  TEST_EQUALITY_CONST( angular_grid.size(), 21 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.9 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 21 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 1.76576e-8 );
  TEST_FLOATING_EQUALITY( evaluated_pdf.back(), 1.2910653846153849e-04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angular grid can be returned
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   getAngularGridAndPDF_LinLinLog )
{
  std::vector<double> angular_grid, evaluated_pdf;
  double evaluation_tol = 1e-7;
  double cutoff_angle_cosine = 1.0;

  // Test lowerest energy bin
  double energy = 1.0e-5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLog>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 2 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 0.5 );

  // Test inbetween energy bins
  energy = 20.0;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLog>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_EQUALITY_CONST( angular_grid.size(), 79 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 79 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 5.19221420086210804e-08 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 5.06129128916336049e+05 );

  // Test highest energy bin
  energy = 1.0e+5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLog>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_EQUALITY_CONST( angular_grid.size(), 90 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 90 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 1.76576e-8 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 9.86374e5 );
}

//---------------------------------------------------------------------------//
// Check that the angular grid can be returned
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   getAngularGridAndPDF_LinLinLin )
{
  std::vector<double> angular_grid, evaluated_pdf;
  double evaluation_tol = 1e-7;
  double cutoff_angle_cosine = 1.0;

  // Test lowerest energy bin
  double energy = 1.0e-5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLin>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 2 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 0.5 );

  // Test inbetween energy bins
  energy = 20.0;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLin>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_EQUALITY_CONST( angular_grid.size(), 79 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 79 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 6.14603e-08 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 4.33429111111111124e+05 );


  // Test highest energy bin
  energy = 1.0e5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLin>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_EQUALITY_CONST( angular_grid.size(), 90 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 90 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 1.76576e-8 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 9.86374e5 );
}

//---------------------------------------------------------------------------//
// Check that the angular grid can be returned
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   getAngularGridAndPDF_LogLogLog )
{
  std::vector<double> angular_grid, evaluated_pdf;
  double evaluation_tol = 1e-7;
  double cutoff_angle_cosine = 0.9;

  // Test lowerest energy bin
  double energy = 1.0e-5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LogLogLog>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.9 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 2 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 0.5 );

  // Test inbetween energy bins
  energy = 20.0;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LogLogLog>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_EQUALITY_CONST( angular_grid.size(), 21 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.9 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 21 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 4.21284828599103030e-08 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 3.02987288635384749e-04 );


  // Test highest energy bin
  energy = 1.0e5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LogLogLog>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_EQUALITY_CONST( angular_grid.size(), 21 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.9 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 21 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 1.76576e-8 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 1.29106538461538494e-04 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCutoffElasticDistribution_LogLogLog )
{
  double cutoff_angle_cosine = 1.0;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LogLogLog>(
        native_cutoff_elastic_distribution,
        *data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  // Cutoff
  fake_stream[0] = 0.5; // sample angle cosine = 1-1.249161208881750E-02
  fake_stream[1] = 0.5; // sample angle cosine = 1-1.249161208881750E-02

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample cutoff
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          1.0 - 1.249161208881750E-02,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  incoming_energy = 1.0e-4;

  // sample cutoff
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          8.88234091357768651e-01,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCutoffElasticDistribution_LinLinLog )
{
  double cutoff_angle_cosine = 1.0;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLog>(
        native_cutoff_elastic_distribution,
        *data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  // Cutoff
  fake_stream[0] = 0.5; // sample angle cosine = 1.249161208881750E-02
  fake_stream[1] = 0.5; // sample angle cosine = 1.249161208881750E-02

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample cutoff
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          1.0 - 1.249161208881750E-02,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  incoming_energy = 1.0e-4;

  // sample cutoff
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          0.49375394395559125,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCutoffElasticDistribution_LinLinLin )
{
  double cutoff_angle_cosine = 1.0;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLin>(
        native_cutoff_elastic_distribution,
        *data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  // Cutoff
  fake_stream[0] = 0.5; // sample angle cosine = 1.249161208881750E-02
  fake_stream[1] = 0.5; // sample angle cosine = 1.249161208881750E-02

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample cutoff
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          1.0 - 1.249161208881750E-02,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  incoming_energy = 1.0e-4;

  // sample cutoff
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          0.0897730352646529,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCutoffElasticDistribution_LinLinLog_adjoint )
{
  double cutoff_angle_cosine = 1.0;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLog>(
        native_cutoff_elastic_distribution,
        *adjoint_data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9875083879111824503
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample from distribution
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98549702576858821956, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  incoming_energy = 1.0e-4;
  // sample from distribution
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          0.49274826288429413,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCutoffElasticDistribution_LinLinLin_adjoint )
{
  double cutoff_angle_cosine = 1.0;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLin>(
        native_cutoff_elastic_distribution,
        *adjoint_data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9875083879111824503
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample from distribution
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98549702576858821956, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  incoming_energy = 1.0e-4;
  // sample from distribution
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          0.0895901841607807,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createScreenedRutherfordElasticDistribution )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
        native_sr_elastic_distribution,
        data_container->getAtomicNumber() );

  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  // Screened Rutherford
  fake_stream[0] = 0.0; // sample angle cosine = 0.999999
  fake_stream[1] = 0.5; // sample angle cosine = 0.9999995
  fake_stream[2] = 1.0 - 1.0e-15; // sample angle cosine = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // sample screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9999995, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // sample screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createScreenedRutherfordElasticDistribution_adjoint )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
        native_sr_elastic_distribution,
        data_container->getAtomicNumber() );

  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  // Screened Rutherford
  fake_stream[0] = 0.0; // sample angle cosine = 0.999999
  fake_stream[1] = 0.5; // sample angle cosine = 0.9999995
  fake_stream[2] = 1.0 - 1.0e-15; // sample angle cosine = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // sample screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9999995, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // sample screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createMomentPreservingElasticDistribution_LinLinLog )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLog>(
        native_mp_elastic_distribution,
        *data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 1.44375258484736535e-01; // sample mu = 9.23978505045084053e-01
  fake_stream[1] = 0.02;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample moment preserving
  native_mp_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.23978505045084053e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  incoming_energy = 1.0e-4;

  // sample moment preserving
  native_mp_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9197418038052813, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createMomentPreservingElasticDistribution_LinLinLin )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLin>(
        native_mp_elastic_distribution,
        *data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 1.44375258484736535e-01; // sample mu = 9.23978505045084053e-01
  fake_stream[1] = 0.02;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample moment preserving
  native_mp_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.23978505045084053e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  incoming_energy = 1.0e-4;

  // sample moment preserving
  native_mp_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9162754118818063, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createMomentPreservingElasticDistribution_LinLinLog_adjoint )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLog>(
        native_mp_elastic_distribution,
        *adjoint_data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 1.44375258484736535e-01; // sample mu = 9.23978505045084053e-01
  fake_stream[1] = 0.02;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample moment preserving
  native_mp_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.92398608900202416905, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  incoming_energy = 1.0e-4;

  // sample moment preserving
  native_mp_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9197455957837513, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createMomentPreservingElasticDistribution_LinLinLin_adjoint )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLin>(
        native_mp_elastic_distribution,
        *adjoint_data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 1.44375258484736535e-01; // sample mu = 9.23978505045084053e-01
  fake_stream[1] = 0.02;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample moment preserving
  native_mp_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.92398608900202416905, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  incoming_energy = 1.0e-4;

  // sample moment preserving
  native_mp_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9162761013324372, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coupled distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCoupledElasticDistribution_LogLogLog )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method = MonteCarlo::SIMPLIFIED_UNION;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LogLogLog>(
        native_coupled_elastic_distribution,
        cutoff_cross_section,
        total_cross_section,
        energy_grid,
        data_container->getCutoffElasticAngles(),
        data_container->getCutoffElasticPDF(),
        data_container->getElasticAngularEnergyGrid(),
        data_container->getAtomicNumber(),
        sampling_method,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 9.87508387911182450e-01
  fake_stream[2] = 0.9; // sample angle cosine = 9.98796724798355462e-01
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 0.999999

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test at an energy bin
  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.87508387911182450e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.98796724798355462e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Set fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.88234091357768651e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.84486904780908834e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test energy inbetween energy bins
  incoming_energy = 2e2;
  fake_stream.resize( 5 );

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9989497571065022e-01
  fake_stream[2] = 1.0171e-02; // sample just below the cutoff cross section ratio
  fake_stream[3] = 1.0171287468598524e-02; // sample the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9989497571065022e-01, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999901223584842e-01, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coupled distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
  createCoupledElasticDistribution_LogLogLog_OneDUnion )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method = MonteCarlo::ONE_D_UNION;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LogLogLog>(
  native_coupled_elastic_distribution,
  cutoff_cross_section,
  total_cross_section,
  energy_grid,
  data_container->getCutoffElasticAngles(),
  data_container->getCutoffElasticPDF(),
  data_container->getElasticAngularEnergyGrid(),
  data_container->getAtomicNumber(),
  sampling_method,
  correlated_sampling_mode_on,
  evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 9.87508387911182450e-01
  fake_stream[2] = 0.9; // sample angle cosine = 9.98796724798355462e-01
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 0.999999

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test at an energy bin
  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                outgoing_energy,
                                scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                outgoing_energy,
                                scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.87508387911182450e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                outgoing_energy,
                                scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.98796724798355462e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                outgoing_energy,
                                scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Set fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                outgoing_energy,
                                scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.88234091357768651e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.84486904780908834e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test energy inbetween energy bins
  incoming_energy = 2e2;
  fake_stream.resize( 5 );

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9989497571065022e-01
  fake_stream[2] = 1.0171e-02; // sample just below the cutoff cross section ratio
  fake_stream[3] = 1.0171287468598524e-02; // sample the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9989497571065022e-01, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999901223584842e-01, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999901226382204e-01, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coupled distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
    createCoupledElasticDistribution_LogLogLog_TwoDUnion )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method = MonteCarlo::TWO_D_UNION;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LogLogLog>(
  native_coupled_elastic_distribution,
  cutoff_cross_section,
  total_cross_section,
  energy_grid,
  data_container->getCutoffElasticAngles(),
  data_container->getCutoffElasticPDF(),
  data_container->getElasticAngularEnergyGrid(),
  data_container->getAtomicNumber(),
  sampling_method,
  correlated_sampling_mode_on,
  evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 9.87508387911182450e-01
  fake_stream[2] = 0.9; // sample angle cosine = 9.98796724798355462e-01
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 0.999999

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test at an energy bin
  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                outgoing_energy,
                                scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                outgoing_energy,
                                scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.87508387911182450e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                outgoing_energy,
                                scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.98796724798355462e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                outgoing_energy,
                                scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Set fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                outgoing_energy,
                                scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.88234091357768651e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.84486904780908834e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test energy inbetween energy bins
  incoming_energy = 2e2;
  fake_stream.resize( 5 );

  // Set fake random number stream
  fake_stream[0] = 0.0; // sample mu = -1.0
  fake_stream[1] = 1.0e-4; // sample mu = 9.9989496344746609e-01
  fake_stream[2] = 1.0171e-02; // sample just below the cutoff cross section ratio
  fake_stream[3] = 1.0171287468598524e-02; // sample the cutoff cross section ratio
  fake_stream[4] = 1.0 - 1e-15; // sample mu = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9989496344746609e-01, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999899997202635e-01, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );

  native_coupled_elastic_distribution->sample( incoming_energy,
                                               outgoing_energy,
                                               scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coupled distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCoupledElasticDistribution_LinLinLog )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method = MonteCarlo::SIMPLIFIED_UNION;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLog>(
        native_coupled_elastic_distribution,
        cutoff_cross_section,
        total_cross_section,
        energy_grid,
        data_container->getCutoffElasticAngles(),
        data_container->getCutoffElasticPDF(),
        data_container->getElasticAngularEnergyGrid(),
        data_container->getAtomicNumber(),
        sampling_method,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 9.87508387911182450e-01
  fake_stream[2] = 0.9; // sample angle cosine = 9.98796724798355462e-01
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 0.999999

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.87508387911182450e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.98796724798355462e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Set fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 4.93753943955591245718e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.99397912399177767995e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coupled distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCoupledElasticDistribution_LinLinLin )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method = MonteCarlo::SIMPLIFIED_UNION;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLin>(
        native_coupled_elastic_distribution,
        cutoff_cross_section,
        total_cross_section,
        energy_grid,
        data_container->getCutoffElasticAngles(),
        data_container->getCutoffElasticPDF(),
        data_container->getElasticAngularEnergyGrid(),
        data_container->getAtomicNumber(),
        sampling_method,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 9.87508387911182450e-01
  fake_stream[2] = 0.9; // sample angle cosine = 9.98796724798355462e-01
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.87508387911182450e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.98796724798355462e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Set fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.97730352646528978466e-02, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.18071611345305038654e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coupled distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCoupledElasticDistribution_LinLinLog_adjoint )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method = MonteCarlo::SIMPLIFIED_UNION;
  double evaluation_tol = 1e-7;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLog>(
        native_coupled_elastic_distribution,
        adjoint_cutoff_cross_section,
        adjoint_total_cross_section,
        adjoint_energy_grid,
        adjoint_data_container->getAdjointCutoffElasticAngles(),
        adjoint_data_container->getAdjointCutoffElasticPDF(),
        adjoint_data_container->getAdjointElasticAngularEnergyGrid(),
        adjoint_data_container->getAtomicNumber(),
        sampling_method,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 9.85497025768588219563e-01
  fake_stream[2] = 0.9; // sample angle cosine = 9.98262783477907422736e-01
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.85497025768588219563e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.98262783477907422736e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  // Reset fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 4.92748262884294130348e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.99130941738953692877e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coupled distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCoupledElasticDistribution_LinLinLin_adjoint )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method = MonteCarlo::SIMPLIFIED_UNION;
  double evaluation_tol = 1e-14;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLin>(
        native_coupled_elastic_distribution,
        adjoint_cutoff_cross_section,
        adjoint_total_cross_section,
        adjoint_energy_grid,
        adjoint_data_container->getAdjointCutoffElasticAngles(),
        adjoint_data_container->getAdjointCutoffElasticPDF(),
        adjoint_data_container->getAdjointElasticAngularEnergyGrid(),
        adjoint_data_container->getAtomicNumber(),
        sampling_method,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 9.85497025768588219563e-01
  fake_stream[2] = 0.9; // sample angle cosine = 9.98262783477907422736e-01
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 0.999999
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.85497025768588219563e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.98262783477907422736e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  // Reset fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.95901841607806975754e-02, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.18023071225264297723e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_coupled_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hybrid distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createHybridElasticDistribution_LinLinLog )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-14;

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    data_container->getElectronEnergyGrid().begin(),
    data_container->getElectronEnergyGrid().end() );

  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container->getCutoffElasticCrossSection().begin(),
    data_container->getCutoffElasticCrossSection().end() );

  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    data_container->getMomentPreservingCrossSection().begin(),
    data_container->getMomentPreservingCrossSection().end() );

  std::shared_ptr< const MonteCarlo::HybridElasticElectronScatteringDistribution>
    native_hybrid_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<Utility::LinLinLog>(
        native_hybrid_elastic_distribution,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        *data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  double incoming_energy = 1.0e-3;

  // Set fake random number stream
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 1.5069669466805288e-01; // sample mu = 0.1 (cutoff)
  fake_stream[1] = 3.6013179335135637e-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 3.6013179335136e-01; // sample mu = 9.2397850504508405e-01 (discrete)
  fake_stream[3] = 4.5251293108241e-01; // sample mu = 9.2397850504508405e-01 (discrete)
  fake_stream[4] = 4.5251293108242e-01; // sample mu = 9.8171108128432372e-01 (discrete)
  fake_stream[5] = 1.0-1e-15; // sample mu = 9.8171108128432372e-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.2397850504508405e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.2397850504508405e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 5
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.8171108128432372e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 6
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.8171108128432372e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );


  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Set fake random number stream
  fake_stream.resize( 4 );
  fake_stream[0] = 0.5; // sample mu = 4.8807776285444099e-01
  fake_stream[1] = 0.9; // sample mu = 8.8585554062426430e-01
  fake_stream[2] = 0.95; // sample mu = 9.3557776284549221e-01
  fake_stream[3] = 1.0-1e-15; // sample mu = 9.7310298934180761e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test 1
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 4.8807776285444099e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.8585554062426430e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.3557776284549221e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.7310298934180761e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Set fake random number stream
//  fake_stream.resize( 8 );
//  fake_stream[0] = 2.4740532166124285e-01; // sample mu = 0.1 (cutoff)
//  fake_stream[1] = 8.5655308013118403e-01; // sample mu = 0.9 (cutoff)
//  fake_stream[2] = 9.5711173935107219e-01; // sample mu = 9.197418038052812550e-01 (discrete)
//  fake_stream[3] = 9.3610699179616e-01; // sample mu = 9.197418038052812550e-01 (discrete)
//  fake_stream[4] = 9.3610699179617e-01; // sample mu = 9.486080919249011423e-01 (discrete)
//  fake_stream[5] = 9.5694690447057e-01; // sample mu = 9.486080919249011423e-01 (discrete)
//  fake_stream[6] = 9.5694690447058e-01; // sample mu = 9.731029893418076115e-01 (discrete)
//  fake_stream[7] = 1.0-1e-15; // sample mu = 9.731029893418076115e-01 (discrete)

//  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//  // Test 1
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 2
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 3
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.197418038052812550e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 4
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.197418038052812550e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 5
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.486080919249011423e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 6
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.486080919249011423e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 7
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.731029893418076115e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 8
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.731029893418076115e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hybrid distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createHybridElasticDistribution_LinLinLin )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-7;

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    data_container->getElectronEnergyGrid().begin(),
    data_container->getElectronEnergyGrid().end() );

  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container->getCutoffElasticCrossSection().begin(),
    data_container->getCutoffElasticCrossSection().end() );

  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    data_container->getMomentPreservingCrossSection().begin(),
    data_container->getMomentPreservingCrossSection().end() );

  std::shared_ptr< const MonteCarlo::HybridElasticElectronScatteringDistribution>
    native_hybrid_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<Utility::LinLinLin>(
        native_hybrid_elastic_distribution,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        *data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  double incoming_energy = 1.0e-3;

  // Set fake random number stream
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 1.5069669466805288e-01; // sample mu = 0.1 (cutoff)
  fake_stream[1] = 3.6013179335135637e-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 3.6013179335136e-01; // sample mu = 9.2397850504508405e-01 (discrete)
  fake_stream[3] = 4.5251293108241e-01; // sample mu = 9.2397850504508405e-01 (discrete)
  fake_stream[4] = 4.5251293108242e-01; // sample mu = 9.8171108128432372e-01 (discrete)
  fake_stream[5] = 1.0-1e-15; // sample mu = 9.8171108128432372e-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.2397850504508405e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.2397850504508405e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 5
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.8171108128432372e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 6
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.8171108128432372e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );


  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Set fake random number stream
  fake_stream.resize( 4 );
  fake_stream[0] = 0.5; // sample mu = 8.4195956866355129e-02
  fake_stream[1] = 0.9; // sample mu = 8.0742828008421574e-01
  fake_stream[2] = 0.95; // sample mu = 8.9783232048644823e-01
  fake_stream[3] = 1.0-1e-15; // sample mu = 9.6606000502520351e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test 1
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.4195956866355129e-02, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.0742828008421574e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.9783232048644823e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.6606000502520351e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Set fake random number stream
//  fake_stream.resize( 8 );
//  fake_stream[0] = 5.1354078318308127e-01; // sample mu = 0.1 (cutoff)
//  fake_stream[1] = 9.2858622885104125e-01; // sample mu = 0.9 (cutoff)
//  fake_stream[2] = 9.2858622885105e-01; // sample mu = 9.162754118818062787e-01 (discrete)
//  fake_stream[3] = 9.3889661052004e-01; // sample mu = 9.162754118818062787e-01 (discrete)
//  fake_stream[4] = 9.3889661052005e-01; // sample mu = 9.215238279035552482e-01 (discrete)
//  fake_stream[5] = 9.5882663630330e-01; // sample mu = 9.215238279035552482e-01 (discrete)
//  fake_stream[6] = 9.5882663630331e-01; // sample mu = 9.660600050252035054e-01 (discrete)
//  fake_stream[7] = 1.0-1e-15; // sample mu = 9.660600050252035054e-01 (discrete)

//  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//  // Test 1
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 2
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 3
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.162754118818062787e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 4
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.162754118818062787e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 5
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.215238279035552482e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 6
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.215238279035552482e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 7
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.660600050252035054e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

//  // Test 8
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.660600050252035054e-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hybrid distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createHybridElasticDistribution_LinLinLog_adjoint )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-15;

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    adjoint_data_container->getAdjointElectronEnergyGrid().begin(),
    adjoint_data_container->getAdjointElectronEnergyGrid().end() );

  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    adjoint_data_container->getAdjointCutoffElasticCrossSection().begin(),
    adjoint_data_container->getAdjointCutoffElasticCrossSection().end() );

  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    adjoint_data_container->getAdjointMomentPreservingCrossSection().begin(),
    adjoint_data_container->getAdjointMomentPreservingCrossSection().end() );

  std::shared_ptr< const MonteCarlo::HybridElasticElectronScatteringDistribution>
    native_hybrid_elastic_distribution;

  
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<Utility::LinLinLog>(
        native_hybrid_elastic_distribution,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        *adjoint_data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.1; // sample mu = 8.4559530792436211e-01
  fake_stream[1] = 0.2; // sample mu = 9.2398608900202417e-01
  fake_stream[2] = 0.3; // sample mu = 9.7889262247552877e-01
  fake_stream[3] = 1.0-1e-15; // sample mu = 9.7889262247552877e-01


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 8.4575166562763160e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 2
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.2398608900202417e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

 // Test 3
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.7889262247552877e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

 // Test 4
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.7889262247552877e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


//  // Set fake random number stream
//  std::vector<double> fake_stream( 6 );
//  fake_stream[0] = 1.0239714515463915e-02; // sample mu = 0.1 (cutoff)
//  fake_stream[1] = 1.5586513237760702e-01; // sample mu = 0.9 (cutoff)
//  fake_stream[2] = 1.55865132377608e-01; // sample mu = 9.23986089002024E-01 (discrete)
//  fake_stream[3] = 2.92999320187278e-01; // sample mu = 9.23986089002024E-01 (discrete)
//  fake_stream[4] = 2.92999320187279e-01; // sample mu = 9.78892622475528E-01 (discrete)
//  fake_stream[5] = 1.0-1e-15; // sample mu = 9.78892622475528E-01 (discrete)


//  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//  double incoming_energy = 1.0e-3;
//  double scattering_angle_cosine, outgoing_energy;

//  // Test 1
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.1, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

//  // Test 2
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

// // Test 3
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.23986089002024E-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

// // Test 4
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.23986089002024E-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

//  // Test 5
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.78892622475528E-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

//  // Test 6
//  native_hybrid_elastic_distribution->sample( incoming_energy,
//                                              outgoing_energy,
//                                              scattering_angle_cosine );
//  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.78892622475528E-01, 1e-12 );
//  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createScatteringFunction_LinLinLog )
{
  double evaluation_tol = 1e-7;
  double cutoff_angle_cosine = 1.0;

  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function;

  TestElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLog>(
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    data_container->getElasticAngularEnergyGrid(),
    scattering_function,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_FLOATING_EQUALITY( scattering_function->getLowerBoundOfPrimaryIndepVar(), 1e-5, 1e-12 );
  TEST_FLOATING_EQUALITY( scattering_function->getUpperBoundOfPrimaryIndepVar(), 1e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createScatteringFunction_LinLinLin )
{
  double evaluation_tol = 1e-7;
  double cutoff_angle_cosine = 1.0;

  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function;

  TestElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLin>(
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    data_container->getElasticAngularEnergyGrid(),
    scattering_function,
    cutoff_angle_cosine,
    evaluation_tol );

  TEST_FLOATING_EQUALITY( scattering_function->getLowerBoundOfPrimaryIndepVar(), 1e-5, 1e-12 );
  TEST_FLOATING_EQUALITY( scattering_function->getUpperBoundOfPrimaryIndepVar(), 1e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createScatteringFunctionInSubrange )
{
  double cutoff_angle_cosine = 0.9;
  std::vector<double> energy_grid = data_container->getElasticAngularEnergyGrid();

  Utility::Pair<double, std::shared_ptr<const Utility::UnitAwareTabularOneDDistribution<void, void> > > scattering_function;

  TestElasticElectronScatteringDistributionNativeFactory::createScatteringFunctionInSubrange(
    data_container->getCutoffElasticAngles( energy_grid[0] ),
    data_container->getCutoffElasticPDF( energy_grid[0] ),
    energy_grid[0],
    cutoff_angle_cosine,
    scattering_function );

  TEST_FLOATING_EQUALITY( scattering_function.first, 1e-5, 1e-12 );
  TEST_FLOATING_EQUALITY( scattering_function.second->getLowerBoundOfIndepVar(),
                          -1.0,
                          1e-12 );
  TEST_FLOATING_EQUALITY( scattering_function.second->getUpperBoundOfIndepVar(),
                          0.9,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hybrid distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createHybridCrossSectionRatios )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-7;

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    data_container->getElectronEnergyGrid().begin(),
    data_container->getElectronEnergyGrid().end() );

  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container->getCutoffElasticCrossSection().begin(),
    data_container->getCutoffElasticCrossSection().end() );

  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    data_container->getMomentPreservingCrossSection().begin(),
    data_container->getMomentPreservingCrossSection().end() );

  std::shared_ptr<TwoDDist> cutoff_scattering_function;
  TestElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLin>(
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    data_container->getElasticAngularEnergyGrid(),
    cutoff_scattering_function,
    1.0,
    evaluation_tol );

  std::shared_ptr<const Utility::OneDDistribution> cross_section_ratios;
  TestElasticElectronScatteringDistributionNativeFactory::createHybridCrossSectionRatios<Utility::LinLinLog>(
    energy_grid,
    cutoff_cross_section,
    mp_cross_section,
    cutoff_scattering_function,
    cutoff_angle_cosine,
    cross_section_ratios );

  TEST_FLOATING_EQUALITY( cross_section_ratios->getLowerBoundOfIndepVar(),
                          1e-5,
                          1e-12 );
  TEST_FLOATING_EQUALITY( cross_section_ratios->getUpperBoundOfIndepVar(),
                          1e5,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name, test_adjoint_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
  clp().setOption( "test_adjoint_file",
                   &test_adjoint_file_name,
                   "Test Adjoint file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                        test_native_file_name ) );

  // Energy grid
  energy_grid.assign( data_container->getElectronEnergyGrid().begin(),
                      data_container->getElectronEnergyGrid().end() );

  // Cutoff elastic cross section
  cutoff_cross_section.assign(
    data_container->getCutoffElasticCrossSection().begin(),
    data_container->getCutoffElasticCrossSection().end() );

  // Total elastic cross section
  total_cross_section.assign(
    data_container->getTotalElasticCrossSection().begin(),
    data_container->getTotalElasticCrossSection().end() );

  // Create the native adjoint data file container
  adjoint_data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                                test_adjoint_file_name ) );


  // Energy grid
  adjoint_energy_grid.assign(
    adjoint_data_container->getAdjointElectronEnergyGrid().begin(),
    adjoint_data_container->getAdjointElectronEnergyGrid().end() );

  // Cutoff elastic cross section
  adjoint_cutoff_cross_section.assign(
    adjoint_data_container->getAdjointCutoffElasticCrossSection().begin(),
    adjoint_data_container->getAdjointCutoffElasticCrossSection().end() );

  // Total elastic cross section
  adjoint_total_cross_section.assign(
    adjoint_data_container->getAdjointTotalElasticCrossSection().begin(),
    adjoint_data_container->getAdjointTotalElasticCrossSection().end() );


  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
