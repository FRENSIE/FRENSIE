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
  using MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction;
  using MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer>
    adjoint_data_container;
std::shared_ptr< const MonteCarlo::CutoffElasticElectronScatteringDistribution>
  native_cutoff_elastic_distribution;
std::shared_ptr< const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
  native_sr_elastic_distribution;
std::shared_ptr< const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution>
  native_mp_elastic_distribution;
std::shared_ptr< const MonteCarlo::AnalogElasticElectronScatteringDistribution>
  native_analog_elastic_distribution;
std::shared_ptr< const MonteCarlo::HybridElasticElectronScatteringDistribution>
  native_hybrid_elastic_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the angular grid can be returned
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   getAngularGrid )
{

  double cutoff_angle_cosine = -1.0;
  double energy = 1.0e-5;
  std::vector<double> angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
                    data_container->getCutoffElasticAngles(),
                    energy,
                    cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

  energy = 1.001e-5;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
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
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
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
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
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
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
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
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
                                                raw_grid,
                                                cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

  angular_grid.clear();

  cutoff_angle_cosine = 0.9;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
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
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
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
                   getAngularGridAndPDF_LinLinLog )
{
  std::vector<double> angular_grid, evaluated_pdf;

  // Test lowerest energy bin
  double energy = 1.0e-5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLog>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy );

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
    energy );

  TEST_EQUALITY_CONST( angular_grid.size(), 79 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 79 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 5.19221275245657547e-08 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 5.06129104868643801e+05 );


  // Test highest energy bin
  energy = 1.0e+5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLog>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy );

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

  // Test lowerest energy bin
  double energy = 1.0e-5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLin>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy );

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
    energy );

  TEST_EQUALITY_CONST( angular_grid.size(), 79 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 79 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 6.14602802628500258e-08 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 4.33429072791244427e+05 );


  // Test highest energy bin
  energy = 1.0e5;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLin>(
    angular_grid,
    evaluated_pdf,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    energy );

  TEST_EQUALITY_CONST( angular_grid.size(), 90 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );
  TEST_EQUALITY_CONST( evaluated_pdf.size(), 90 );
  TEST_EQUALITY_CONST( evaluated_pdf.front(), 1.76576e-8 );
  TEST_EQUALITY_CONST( evaluated_pdf.back(), 9.86374e5 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCutoffElasticDistribution_LinLinLog )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLog>(
        native_cutoff_elastic_distribution,
        *data_container,
        1.0 );

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
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLin>(
        native_cutoff_elastic_distribution,
        *data_container,
        1.0 );

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
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLog>(
        native_cutoff_elastic_distribution,
        *adjoint_data_container,
        1.0 );

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
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLin>(
        native_cutoff_elastic_distribution,
        *adjoint_data_container,
        1.0 );

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
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
        native_cutoff_elastic_distribution,
        *data_container,
        1.0 );

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
        native_sr_elastic_distribution,
        native_cutoff_elastic_distribution,
        data_container->getAtomicNumber() );

  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  // Screened Rutherford
  fake_stream[0] = 0.0; // sample angle cosine = 1.0
  fake_stream[1] = 0.5; // sample angle cosine = 0.9999995
  fake_stream[2] = 1.0 - 1.0e-15; // sample angle cosine = 0.999999

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0-1.0e-6, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createScreenedRutherfordElasticDistribution_adjoint )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
        native_cutoff_elastic_distribution,
        *adjoint_data_container,
        1.0 );

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
        native_sr_elastic_distribution,
        native_cutoff_elastic_distribution,
        data_container->getAtomicNumber() );

  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  // Screened Rutherford
  fake_stream[0] = 0.0; // sample angle cosine = 1.0
  fake_stream[1] = 0.5; // sample angle cosine = 0.9999995
  fake_stream[2] = 1.0 - 1.0e-15; // sample angle cosine = 0.999999

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0-1.0e-6, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createMomentPreservingElasticDistribution_LinLinLog )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLog>(
        native_mp_elastic_distribution,
        *data_container,
        0.9 );

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
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLin>(
        native_mp_elastic_distribution,
        *data_container,
        0.9 );

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
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLog>(
        native_mp_elastic_distribution,
        *adjoint_data_container,
        0.9 );

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
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLin>(
        native_mp_elastic_distribution,
        *adjoint_data_container,
        0.9 );

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
// Check that the analog distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createAnalogElasticDistribution_LinLinLog )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<Utility::LinLinLog>(
        native_analog_elastic_distribution,
        data_container->getCutoffElasticAngles(),
        data_container->getCutoffElasticPDF(),
        data_container->getElasticAngularEnergyGrid(),
        data_container->getAtomicNumber(),
        1e-7,
        true );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 0.98751141888536664304
  fake_stream[2] = 0.9; // sample angle cosine = 0.99879780594178391162
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 2
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98751141888536664304, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 3
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99879780594178391162, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 4
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Set fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.49375570944268343, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.8993989029708922, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the analog distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createAnalogElasticDistribution_LinLinLin )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<Utility::LinLinLin>(
        native_analog_elastic_distribution,
        data_container->getCutoffElasticAngles(),
        data_container->getCutoffElasticPDF(),
        data_container->getElasticAngularEnergyGrid(),
        data_container->getAtomicNumber(),
        1e-7,
        true );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 0.98751141888536664304
  fake_stream[2] = 0.9; // sample angle cosine = 0.99879780594178391162
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 2
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98751141888536664304, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 3
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99879780594178391162, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 4
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Set fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.08977376535321535, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.8180725278128899, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the analog distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createAnalogElasticDistribution_LinLinLog_adjoint )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<Utility::LinLinLog>(
        native_analog_elastic_distribution,
        adjoint_data_container->getAdjointCutoffElasticAngles(),
        adjoint_data_container->getAdjointCutoffElasticPDF(),
        adjoint_data_container->getAdjointElasticAngularEnergyGrid(),
        adjoint_data_container->getAtomicNumber(),
        1e-7,
        true );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 0.98751141888536664304
  fake_stream[2] = 0.9; // sample angle cosine = 0.99879780594178391162
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 2
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98549871388816456808, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 3
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99826383658664175069, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 4
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  // Reset fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          -1.0,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.4927493569443319, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.8991319182937703, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the analog distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createAnalogElasticDistribution_LinLinLin_adjoint )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<Utility::LinLinLin>(
        native_analog_elastic_distribution,
        adjoint_data_container->getAdjointCutoffElasticAngles(),
        adjoint_data_container->getAdjointCutoffElasticPDF(),
        adjoint_data_container->getAdjointElasticAngularEnergyGrid(),
        adjoint_data_container->getAtomicNumber(),
        1e-7,
        true );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 0.98751141888536664304
  fake_stream[2] = 0.9; // sample angle cosine = 0.99879780594178391162
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 1.0
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 2
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98549871388816456808, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 3
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99826383658664175069, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 4
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  // Reset fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          -1.0,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.0895907921721053, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.8180239851450574, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hybrid distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createHybridElasticDistribution_LinLinLog )
{
  double cutoff_angle_cosine = 0.9;

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    data_container->getElectronEnergyGrid().begin(),
    data_container->getElectronEnergyGrid().end() );

  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(   
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
         energy_grid,
         energy_grid[0],
         energy_grid[energy_grid.size()-1],
         100 ) );

  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container->getCutoffElasticCrossSection().begin(),
    data_container->getCutoffElasticCrossSection().end() );

  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    data_container->getMomentPreservingCrossSection().begin(),
    data_container->getMomentPreservingCrossSection().end() );

  
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
        native_hybrid_elastic_distribution,
        grid_searcher,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        *data_container,
        cutoff_angle_cosine,
        true,
        true );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 2.23821564049245E-01; // sample mu = 0.57 (cutoff)
  fake_stream[1] = 3.60131793351356E-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 0.4; // sample mu = 9.239785050451E-01 (discrete)
  fake_stream[3] = 0.453; // sample mu = 9.817110812843E-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.57, 1e-12 );
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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.8171108128432372e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Reset fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 7.5781109112208478e-03, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 3.0813106115890876e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 3.5976703029236534e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 4.4133887396648674e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hybrid distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createHybridElasticDistribution_LinLinLin )
{
  double cutoff_angle_cosine = 0.9;

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    data_container->getElectronEnergyGrid().begin(),
    data_container->getElectronEnergyGrid().end() );

  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(   
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
         energy_grid,
         energy_grid[0],
         energy_grid[energy_grid.size()-1],
         100 ) );

  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container->getCutoffElasticCrossSection().begin(),
    data_container->getCutoffElasticCrossSection().end() );

  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    data_container->getMomentPreservingCrossSection().begin(),
    data_container->getMomentPreservingCrossSection().end() );

  
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
        native_hybrid_elastic_distribution,
        grid_searcher,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        *data_container,
        cutoff_angle_cosine,
        false,
        true );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 2.23821564049245E-01; // sample mu = 0.57 (cutoff)
  fake_stream[1] = 3.60131793351356E-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 0.4; // sample mu = 9.239785050451E-01 (discrete)
  fake_stream[3] = 0.453; // sample mu = 9.817110812843E-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.57, 1e-12 );
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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.8171108128432372e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Reset fake random number stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test with an energy inbetween bins
  incoming_energy = 1.0e-4;

  // Test 1
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -4.5258525288874457e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 2
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.7612534334743835e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 3
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -1.0186053995985905e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );

  // Test 4
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -7.8384111174351068e-04, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, incoming_energy, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hybrid distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createHybridElasticDistribution_LinLinLog_adjoint )
{
  double cutoff_angle_cosine = 0.9;

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    adjoint_data_container->getAdjointElectronEnergyGrid().begin(),
    adjoint_data_container->getAdjointElectronEnergyGrid().end() );

  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(   
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
         energy_grid,
         energy_grid[0],
         energy_grid[energy_grid.size()-1],
         100 ) );

  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    adjoint_data_container->getAdjointCutoffElasticCrossSection().begin(),
    adjoint_data_container->getAdjointCutoffElasticCrossSection().end() );

  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    adjoint_data_container->getAdjointMomentPreservingCrossSection().begin(),
    adjoint_data_container->getAdjointMomentPreservingCrossSection().end() );

  
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
        native_hybrid_elastic_distribution,
        grid_searcher,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        *adjoint_data_container,
        cutoff_angle_cosine );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 2.83326426433763E-02; // sample mu = 0.54 (cutoff)
  fake_stream[1] = 1.54748775311950E-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 1.55E-01; // sample mu = 9.23986089002024E-01 (discrete)
  fake_stream[3] = 2.921E-01; // sample mu = 9.78892622475528E-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // Test 1
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.54, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 2
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

 // Test 3
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.23986089002024E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Test 4
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.78892622475528E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createScatteringFunction_LinLinLog )
{
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function;

  TestElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLog>(
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    data_container->getElasticAngularEnergyGrid(),
    scattering_function,
    1e-7,
    true );

  TEST_FLOATING_EQUALITY( scattering_function->getLowerBoundOfPrimaryIndepVar(), 1e-5, 1e-12 );
  TEST_FLOATING_EQUALITY( scattering_function->getUpperBoundOfPrimaryIndepVar(), 1e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createScatteringFunction_LinLinLin )
{
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function;

  TestElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLin>(
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    data_container->getElasticAngularEnergyGrid(),
    scattering_function,
    1e-7,
    true );

  TEST_FLOATING_EQUALITY( scattering_function->getLowerBoundOfPrimaryIndepVar(), 1e-5, 1e-12 );
  TEST_FLOATING_EQUALITY( scattering_function->getUpperBoundOfPrimaryIndepVar(), 1e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hybrid distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createHybridScatteringFunction )
{
  double cutoff_angle_cosine = 0.9;

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    data_container->getElectronEnergyGrid().begin(),
    data_container->getElectronEnergyGrid().end() );

  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(   
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                 energy_grid,
                 energy_grid[0],
                 energy_grid[energy_grid.size()-1],
                 100 ) );

  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container->getCutoffElasticCrossSection().begin(),
    data_container->getCutoffElasticCrossSection().end() );

  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    data_container->getMomentPreservingCrossSection().begin(),
    data_container->getMomentPreservingCrossSection().end() );

  std::shared_ptr<MonteCarlo::HybridElasticElectronScatteringDistribution::HybridDistribution>
    hybrid_function;

  TestElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction(
    grid_searcher,
    energy_grid,
    cutoff_cross_section,
    data_container->getCutoffElasticAngles(),
    data_container->getCutoffElasticPDF(),
    mp_cross_section,
    data_container->getMomentPreservingElasticDiscreteAngles(),
    data_container->getMomentPreservingElasticWeights(),
    data_container->getElasticAngularEnergyGrid(),
    cutoff_angle_cosine,
    hybrid_function );

  TEST_EQUALITY_CONST( hybrid_function->size(), 14 );
  TEST_FLOATING_EQUALITY( hybrid_function->front().first, 1e-5, 1e-12 );
  TEST_FLOATING_EQUALITY( hybrid_function->back().first, 1e5, 1e-12 );
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

  // Create the native adjoint data file container
  adjoint_data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                                test_adjoint_file_name ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
