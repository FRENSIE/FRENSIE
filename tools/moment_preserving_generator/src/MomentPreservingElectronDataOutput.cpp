//---------------------------------------------------------------------------//
//!
//! \file   MomentPreservingElectronDataOutput.cpp
//! \author Luke Kersting
//! \brief  moment preserving elastic electron data output
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "MonteCarlo_AnalogElasticElectroatomicReaction.hpp"
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "DataGen_StandardMomentPreservingElectronDataGenerator.hpp"

/*! \details This exec outputs a test file to see the moment preserving data for
 *  Al. It was designed to match that of ITS. To run go to bin and run:
 * ./moment_preserving_test_output --test_native_file="NATIVE_TEST_DATA_SOURCE_DIR/test_epr_13_native.xml"
 * It should output a file called moment_preserving_elastic_data.txt
 */
//---------------------------------------------------------------------------//
// Structs.
//---------------------------------------------------------------------------//
class TestElasticElectronMomentsEvaluator : public DataGen::ElasticElectronMomentsEvaluator
{
public:
  TestElasticElectronMomentsEvaluator(
        const Data::ElectronPhotonRelaxationDataContainer& data_container )
    : ElasticElectronMomentsEvaluator( data_container, 0.999999 )
  { /* ... */ }

  ~TestElasticElectronMomentsEvaluator()
  { /* ... */ }

  // Allow public access to the ElasticElectronMomentsEvaluator protected member functions
  using DataGen::ElasticElectronMomentsEvaluator::evaluateCutoffPDFMoment;
  using DataGen::ElasticElectronMomentsEvaluator::evaluateScreenedRutherfordPDFMoment;
  using DataGen::ElasticElectronMomentsEvaluator::evaluateScreenedRutherfordPDFMomentByRecursion;
  using DataGen::ElasticElectronMomentsEvaluator::evaluateScreenedRutherfordPDFMomentByNumericalIntegration;
};

//---------------------------------------------------------------------------//
// Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> data;
Teuchos::RCP<DataGen::ElasticElectronMomentsEvaluator> evaluator;
Teuchos::RCP<TestElasticElectronMomentsEvaluator> test_evaluator;
Teuchos::RCP<const DataGen::StandardMomentPreservingElectronDataGenerator> data_generator;
Teuchos::RCP<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
    rutherford_distribution;
Teuchos::RCP<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_distribution;

//---------------------------------------------------------------------------//
// main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor mp_data_clp;

  std::string test_native_al_file_name;


  mp_data_clp.setDocString( "Moment Preserving AL Test Data Generator\n" );
  mp_data_clp.setOption( "test_native_al_file",
		                 &test_native_al_file_name,
		                 "Test Native Al file name",
                         true );

  mp_data_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = mp_data_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    mp_data_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  {
  // Create the native data file container
  data.reset( new Data::ElectronPhotonRelaxationDataContainer(
						     test_native_al_file_name ) );


  // Create the hard elastic distributions ( both Cutoff and Screened Rutherford )
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHardElasticDistributions(
    cutoff_distribution,
    rutherford_distribution,
    *data,
    0.999999 );

  // Create the moment evaluator
  evaluator.reset( new DataGen::ElasticElectronMomentsEvaluator(
                                    *data ) );

  // Create the test moment evaluator
  test_evaluator.reset( new TestElasticElectronMomentsEvaluator(
                                    *data ) );

  data_generator.reset(
		   new DataGen::StandardMomentPreservingElectronDataGenerator(
				     data->getAtomicNumber(),
				     data,
				     0.00001,
				     20.0,
				     0.999999 ) );
  }

  std::vector<double> angular_energy_grid =
    data->getElasticAngularEnergyGrid();

  std::vector<double> eta(angular_energy_grid.size());
  eta[0] = 1.189646992674E+01L;
  eta[1] = 3.629783667879E-02L;
  eta[2] = 1.679268560571E-02L;
  eta[3] = 7.908970260881E-03L;
  eta[4] = 3.774166375312E-03L;
  eta[5] = 1.815305453727E-03L;
  eta[6] = 8.743857991990E-04L;
  eta[7] = 4.179170609007E-04L;
  eta[8] = 1.953805580523E-04L;
  eta[9] = 8.739160865170E-05L;
  eta[10] = 2.589467963149E-07L;
  eta[11] = 6.032430519875E-08L;
  eta[12] = 2.620863475107E-08L;
  eta[13] = 1.457796275283E-08L;
  eta[14] = 6.407445779740E-09L;
  eta[15] = 2.855935652488E-15L;

  std::vector<Utility::long_float> moments(3);
  moments[0] = Utility::long_float(1);

  std::ofstream myfile;
  myfile.open ("moment_preserving_elastic_data.txt");
  myfile << "Screened Rutherford moments calculated using the recursion relationship and ITS eta.\n";
  myfile << "Element Z = \t"<< data->getAtomicNumber() << "\n";
  myfile << "\tEnergy" << std::setw(20)
         << "\t\tEta" << std::setw(20)
         << "\t\tMoment 1" << std::setw(20)
         << "\t\tMoment 2" << std::setw(20)
         << "\t\tMu\n";

  for ( unsigned i = 0; i < angular_energy_grid.size(); i++ )
  {
  // Evaluate the 1st and 2nd moment
  test_evaluator->evaluateScreenedRutherfordPDFMomentByRecursion(
        moments[1],
        eta[i]*Utility::long_float(2),
        1 );

  test_evaluator->evaluateScreenedRutherfordPDFMomentByRecursion(
        moments[2],
        eta[i]*Utility::long_float(2),
        2 );

  // Use radau quadrature to find the discrete angles and weights from the moments
  Teuchos::RCP<Utility::SloanRadauQuadrature> radau_quadrature(
      new Utility::SloanRadauQuadrature( moments ) );

  std::vector<double> discrete_angles, weights;
  radau_quadrature->getRadauNodesAndWeights( discrete_angles,
                                             weights,
                                             2 );

    myfile << std::setprecision(15) << std::scientific
           << angular_energy_grid[i] << "\t"
           << eta[i] << "\t"
           << moments[1] << "\t"
           << moments[2] << "\t"
           << discrete_angles[0] << "\n";
  }

  myfile << "\n\nScreened Rutherford moments calculated using numerical integration and ITS eta.\n";
  myfile << "Element Z = \t"<< data->getAtomicNumber() << "\n";
  myfile << "\tEnergy" << std::setw(20)
         << "\t\tEta" << std::setw(20)
         << "\t\tMoment 1" << std::setw(20)
         << "\t\tMoment 2" << std::setw(20)
         << "\t\tMu\n";

  for ( unsigned i = 0; i < angular_energy_grid.size(); i++ )
  {
  // Evaluate the 1st and 2nd moment
  test_evaluator->evaluateScreenedRutherfordPDFMomentByNumericalIntegration(
        moments[1],
        eta[i]*Utility::long_float(2),
        angular_energy_grid[i],
        1 );

  test_evaluator->evaluateScreenedRutherfordPDFMomentByNumericalIntegration(
        moments[2],
        eta[i]*Utility::long_float(2),
        angular_energy_grid[i],
        2 );

  // Use radau quadrature to find the discrete angles and weights from the moments
  Teuchos::RCP<Utility::SloanRadauQuadrature> radau_quadrature(
      new Utility::SloanRadauQuadrature( moments ) );

  std::vector<double> discrete_angles, weights;
  radau_quadrature->getRadauNodesAndWeights( discrete_angles,
                                             weights,
                                             2 );

    myfile << std::setprecision(15) << std::scientific
           << angular_energy_grid[i] << "\t"
           << eta[i] << "\t"
           << moments[1] << "\t"
           << moments[2] << "\t"
           << discrete_angles[0] << "\n";
  }

  myfile << "\n\nScreened Rutherford moments calculated using the recursion relationship and FRENSIE eta.\n";
  myfile << "Element Z = \t"<< data->getAtomicNumber() << "\n";
  myfile << "\tEnergy" << std::setw(20)
         << "\t\tEta" << std::setw(20)
         << "\t\tMoment 1" << std::setw(20)
         << "\t\tMoment 2" << std::setw(20)
         << "\t\tMu\n";

  for ( unsigned i = 0; i < angular_energy_grid.size(); i++ )
  {

  // Calcuate Moliere's modified screening constant (eta)
  eta[i] =
    rutherford_distribution->evaluateMoliereScreeningConstant( angular_energy_grid[i] );

  // Evaluate the 1st and 2nd moment
  test_evaluator->evaluateScreenedRutherfordPDFMomentByRecursion(
        moments[1],
        eta[i],
        1 );

  test_evaluator->evaluateScreenedRutherfordPDFMomentByRecursion(
        moments[2],
        eta[i],
        2 );

  // Use radau quadrature to find the discrete angles and weights from the moments
  Teuchos::RCP<Utility::SloanRadauQuadrature> radau_quadrature(
      new Utility::SloanRadauQuadrature( moments ) );

  std::vector<double> discrete_angles, weights;
  radau_quadrature->getRadauNodesAndWeights( discrete_angles,
                                             weights,
                                             2 );

    myfile << std::setprecision(15) << std::scientific
           << angular_energy_grid[i] << "\t"
           << eta[i]/Utility::long_float(2) << "\t"
           << moments[1] << "\t"
           << moments[2] << "\t"
           << discrete_angles[0] << "\n";
  }

  myfile << "\n\nScreened Rutherford moments calculated using numerical integration and FRENSIE eta.\n";
  myfile << "Element Z = \t"<< data->getAtomicNumber() << "\n";
  myfile << "\tEnergy" << std::setw(20)
         << "\t\tEta" << std::setw(20)
         << "\t\tMoment 1" << std::setw(20)
         << "\t\tMoment 2" << std::setw(20)
         << "\t\tMu\n";

  for ( unsigned i = 0; i < angular_energy_grid.size(); i++ )
  {

  // Evaluate the 1st and 2nd moment
  test_evaluator->evaluateScreenedRutherfordPDFMomentByNumericalIntegration(
        moments[1],
        eta[i],
        angular_energy_grid[i],
        1 );

  test_evaluator->evaluateScreenedRutherfordPDFMomentByNumericalIntegration(
        moments[2],
        eta[i],
        angular_energy_grid[i],
        2 );

  // Use radau quadrature to find the discrete angles and weights from the moments
  Teuchos::RCP<Utility::SloanRadauQuadrature> radau_quadrature(
      new Utility::SloanRadauQuadrature( moments ) );

  std::vector<double> discrete_angles, weights;
  radau_quadrature->getRadauNodesAndWeights( discrete_angles,
                                             weights,
                                             2 );

    myfile << std::setprecision(15) << std::scientific
           << angular_energy_grid[i] << "\t"
           << eta[i]/Utility::long_float(2) << "\t"
           << moments[1] << "\t"
           << moments[2] << "\t"
           << discrete_angles[0] << "\n";
  }
  myfile.close();


  return 0;
}

//---------------------------------------------------------------------------//
// end tstElasticElectronMomentsEvaluator.cpp
//---------------------------------------------------------------------------//
