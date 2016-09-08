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
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
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
// Check that the cutoff distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createCutoffElasticDistribution )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
        native_cutoff_elastic_distribution,
        *data_container,
        1.0 );

  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  // Cutoff
  fake_stream[0] = 0.5; // sample angle cosine = 1.249161208881750E-02

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
        *data_container );

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9999995000000930, 1e-12 );
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
                   createMomentPreservingElasticDistribution )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
        native_mp_elastic_distribution,
        *data_container,
        0.9 );

  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 1.44375258484736535e-01; // sample mu = 9.23978505045084053e-01

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
}

//---------------------------------------------------------------------------//
// Check that the analog distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createAnalogElasticDistribution )
{
  std::map<double,std::vector<double> >
    cutoff_elastic_angles( data_container->getCutoffElasticAngles() );
  std::map<double,std::vector<double> >
    cutoff_elastic_pdf( data_container->getCutoffElasticPDF() );
  std::vector<double>
    angular_energy_grid( data_container->getElasticAngularEnergyGrid() );
  unsigned atomic_number = data_container->getAtomicNumber();

  
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
        native_analog_elastic_distribution,
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        atomic_number );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0; // sample angle cosine = -1.0
  fake_stream[1] = 0.5; // sample angle cosine = 0.98751141888536664304
  fake_stream[2] = 0.9; // sample angle cosine = 0.99879780594178391162
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle cosine = 1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test 1
  TEST_FLOATING_EQUALITY( scattering_angle_cosine,
                          -1.0,
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.98751141888536664304, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test 3
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.99879780594178391162, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  native_analog_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test 4
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}


//---------------------------------------------------------------------------//
// Check that the hybrid distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory,
                   createHybridElasticDistribution )
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
        cutoff_angle_cosine );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 2.23821564049245E-01; // sample mu = 0.57 (cutoff)
  fake_stream[1] = 3.60131793351356E-01; // sample mu = 0.9 (cutoff)
  fake_stream[2] = 0.4; // sample mu = 9.239785050451E-01 (discrete)
  fake_stream[3] = 0.453; // sample mu = 9.817110812843E-01 (discrete)

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test 1
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.57, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // sample from distribution
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // sample from distribution
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test 3
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.239785050451E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // sample from distribution
  native_hybrid_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test 4
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.817110812843E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
						     test_native_file_name ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
