//---------------------------------------------------------------------------//
//!
//! \file   tstCutoffElasticElectronScatteringDistributionACE.cpp
//! \author Luke Kersting
//! \brief  Cutoff elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticBasicBivariateDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestCutoffElasticElectronScatteringDistribution : public MonteCarlo::CutoffElasticElectronScatteringDistribution
{
public:
  TestCutoffElasticElectronScatteringDistribution(
        const std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
        full_cutoff_elastic_distribution,
        const std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
        partial_cutoff_elastic_distribution,
        const double cutoff_angle_cosine )
    : MonteCarlo::CutoffElasticElectronScatteringDistribution(
        full_cutoff_elastic_distribution,
        partial_cutoff_elastic_distribution,
        cutoff_angle_cosine )
  { /* ... */ }

  TestCutoffElasticElectronScatteringDistribution(
        const std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
        full_cutoff_elastic_distribution )
    : MonteCarlo::CutoffElasticElectronScatteringDistribution(
        full_cutoff_elastic_distribution )
  { /* ... */ }

  ~TestCutoffElasticElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the CutoffElasticElectronScatteringDistribution protected member functions
  using MonteCarlo::CutoffElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::CutoffElasticElectronScatteringDistribution>
  ace_elastic_distribution;
std::shared_ptr<TestCutoffElasticElectronScatteringDistribution>
  test_ace_elastic_distribution;

std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>
  ace_scattering_distribution;

double angle_cosine_cutoff = 1.0;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   evaluate_ace )
{
  // Set energy in MeV and angle cosine
  double energy = 1.0e-3;
  double scattering_angle_cosine = 0.0;

  // Calculate the pdf
  double pdf_value =
    ace_elastic_distribution->evaluate( energy,
                                        scattering_angle_cosine );
  // test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 4.821797947867E-02, 1e-12 );

  scattering_angle_cosine = 0.98;
  pdf_value =
    ace_elastic_distribution->evaluate( energy,
                                        scattering_angle_cosine );
  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 8.772194880275E+00, 1e-12 );

  // test with a different energy
  energy = 1e5;

  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value =
    ace_elastic_distribution->evaluate( energy,
                                        scattering_angle_cosine );
  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 4.48786781766095E+05, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   evaluatePDF_ace )
{
  // Set energy in MeV and angle cosine
  double energy = 1.0e-3;
  double scattering_angle_cosine = 0.0;

  // Calculate the pdf
  double pdf_value =
    ace_elastic_distribution->evaluatePDF( energy,
                                           scattering_angle_cosine );

  // test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 4.821797947867E-02, 1e-12 );


  scattering_angle_cosine = 0.98;
  pdf_value =
    ace_elastic_distribution->evaluatePDF( energy,
                                           scattering_angle_cosine );

  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 8.772194880275E+00, 1e-12 );

  // test with a different energy
  energy = 1.00E+05;

  scattering_angle_cosine = angle_cosine_cutoff;
  pdf_value =
    ace_elastic_distribution->evaluatePDF( energy,
                                           scattering_angle_cosine );

  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 4.48786781766095E+05, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   evaluateCDF_ace )
{
  // Set energy in MeV and angle cosine
  double energy = 1.0e-3;
  double scattering_angle_cosine = 0.0;

  // Calculate the cdf
  double cdf_value =
    ace_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 9.663705658970E-02, 1e-12 );

  scattering_angle_cosine = 9.8E-01;
  cdf_value =
    ace_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );

  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 4.211953219580E-01, 1e-12 );

  // test with a different energy
  energy = 1.00E+05;

  scattering_angle_cosine = 0.999999;
  cdf_value =
    ace_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );

  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 5.512132182210E-01, 1e-15 );

  scattering_angle_cosine = 1.0;
  cdf_value =
    ace_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );

  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  MonteCarlo::CutoffElasticElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_ace_elastic_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9874366113907, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   sample_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl from distribution
  ace_elastic_distribution->sample( electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9874366113907, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  MonteCarlo::CutoffElasticElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  ace_elastic_distribution->sampleAndRecordTrials(
                                          electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.9874366113907, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   ScatterElectron_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  ace_elastic_distribution->scatterElectron( electron,
                                             bank,
                                             shell_of_interaction );

  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 0.9874366113907, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   ScatterPositron_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1.0e-3 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  ace_elastic_distribution->scatterPositron( positron,
                                             bank,
                                             shell_of_interaction );

  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 0.9874366113907, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle cosine can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.0e-3 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  ace_elastic_distribution->scatterAdjointElectron( adjoint_electron,
                                                    bank,
                                                    shell_of_interaction );

  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          0.9874366113907,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create ACE distribution
  {
    // Create a file handler and data extractor
    std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace_file_name,
                                  "82000.12p",
                                  test_ace_file_start_line ) );
    
    std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

    // Extract the elastic scattering information data block (ELASI)
    Utility::ArrayView<const double> elasi_block(
          xss_data_extractor->extractELASIBlock() );

    // Extract the number of tabulated distributions
    int size = elasi_block.size()/3;

    // Extract the energy grid for elastic scattering angular distributions
    std::vector<double> energy_grid(elasi_block(0,size));

    // Extract the table lengths for elastic scattering angular distributions
    std::vector<double> table_length(elasi_block(size,size));

    // Extract the offsets for elastic scattering angular distributions
    std::vector<double> offset(elasi_block(2*size,size));

    // Extract the elastic scattering angular distributions block (elas)
    Utility::ArrayView<const double> elas_block =
    xss_data_extractor->extractELASBlock();

    // Create the elastic scattering distributions
    std::vector<double> ace_primary_grid( size );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      ace_secondary_dists( size );

    for( unsigned n = 0; n < size; ++n )
    {
      ace_primary_grid[n] = energy_grid[n];

      ace_secondary_dists[n].reset(
       new Utility::HistogramDistribution(
         elas_block( offset[n], table_length[n] ),
         elas_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
            true ) );
    }

    // Get the atomic number
    const int atomic_number = xss_data_extractor->extractAtomicNumber();

    // Create the scattering distribution
    ace_scattering_distribution.reset(
      new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLin> >(
                                                       ace_primary_grid,
                                                       ace_secondary_dists ) );

    // Create the distributions
    ace_elastic_distribution.reset(
        new MonteCarlo::CutoffElasticElectronScatteringDistribution(
                ace_scattering_distribution ) );

    test_ace_elastic_distribution.reset(
        new TestCutoffElasticElectronScatteringDistribution(
                ace_scattering_distribution ) );

    // Clear setup data
    ace_file_handler.reset();
    xss_data_extractor.reset();
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCutoffElasticElectronScatteringDistributionACE.cpp
//---------------------------------------------------------------------------//
