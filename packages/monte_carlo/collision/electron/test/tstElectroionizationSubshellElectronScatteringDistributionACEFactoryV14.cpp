//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectronScatteringDistributionACEFactoryV14.cpp
//! \author Luke Kersting
//! \brief  electroionization subshell scattering distribution ACE factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
  epr14_electroionization_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   getBindingEnergy )
{
  // Get binding energy
  double binding_energy = epr14_electroionization_distribution->getBindingEnergy();
  FRENSIE_CHECK_EQUAL( binding_energy, 8.829E-02 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   evaluateCDF )
{
  double cdf = epr14_electroionization_distribution->evaluateCDF( 8.829e-2 + 1e-8, 1e-8 );
  FRENSIE_CHECK_EQUAL( cdf, 0.0 );

  cdf = epr14_electroionization_distribution->evaluateCDF( 8.829e-2 + 3e-8, 1.0001e-8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 8.3333333333244009e-06, 1e-12 );

  cdf = epr14_electroionization_distribution->evaluateCDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 2.9200970177296481e-01, 1e-12 );

  //! \todo Figure out why this test cannot be evaluated to the tolerance (1e-6)
  // cdf = epr14_electroionization_distribution->evaluateCDF( 1e-1, 1e-2 );
  // FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 6.7056932843167538e-01, 1e-12 );

  cdf = epr14_electroionization_distribution->evaluateCDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 7.9997181385885974e-01, 1e-12 );

  cdf = epr14_electroionization_distribution->evaluateCDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 7.2991814550720002e-01, 1e-12 );

  cdf = epr14_electroionization_distribution->evaluateCDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9991238642799996e-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   sample_knock_on )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double knock_on_energy, knock_on_angle_cosine;
  double incoming_energy = 1.0;

  // sample the electron
  epr14_electroionization_distribution->sample( incoming_energy,
                                                knock_on_energy,
                                                knock_on_angle_cosine );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 2.7854463307465377e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.0780406968911040e-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   sample_PrimaryAndSecondary )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;

  double outgoing_energy, knock_on_energy,
         scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  epr14_electroionization_distribution->sample(
        incoming_energy,
        outgoing_energy,
        knock_on_energy,
        scattering_angle_cosine,
        knock_on_angle_cosine );

  // Test original electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.6452810069913897e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 8.7092959303108897e-01, 1e-12 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 2.7854463307465377e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.0780406968911040e-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronScatteringDistribution::Counter trials = 0;
  double incoming_energy = 1.0;
  double knock_on_energy, scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  epr14_electroionization_distribution->sampleAndRecordTrials(
                                                        incoming_energy,
                                                        knock_on_energy,
                                                        knock_on_angle_cosine,
                                                        trials );

  // Test trials
  FRENSIE_CHECK_EQUAL( trials, 1 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 2.7854463307465377e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.0780406968911040e-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   scatterElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Scatter electron
  epr14_electroionization_distribution->scatterElectron( electron,
                                                         bank,
                                                         shell_of_interaction );

  // Test original electron
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 9.8154265018847409e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.3715157338528261, 1e-12 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 2.5223610130300528e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 4.0194266147173835e-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   scatterPositron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.25;
  fake_stream[1] = 0.25;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1.5 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Scatter positron
  epr14_electroionization_distribution->scatterPositron( positron,
                                                         bank,
                                                         shell_of_interaction );

  // Test original positron
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 9.8154265018847409e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 1.3715157338528261, 1e-12 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 2.5223610130255830e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 4.0194266147025766e-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace14_file_name;
unsigned test_ace14_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace14_file",
                                        test_ace14_file_name, "",
                                        "Test ACE14 file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace14_file_start_line",
                                        test_ace14_file_start_line, 1,
                                        "Test ACE14 file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create a file handler and data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace14_file_name,
                                  "82000.14p",
                                  test_ace14_file_start_line ) );
  
  std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  // Extract the cross sections energy grid
  Utility::ArrayView<const double> energy_grid =
    xss_data_extractor->extractElectronEnergyGrid() ;

  // Extract the subshell information
  Utility::ArrayView<const double> subshell_endf_designators =
    xss_data_extractor->extractSubshellENDFDesignators();

  // Extract the subshell binding energies
  Utility::ArrayView<const double> binding_energies =
    xss_data_extractor->extractSubshellBindingEnergies();

  // Extract the electroionization data block (EION)
  Utility::ArrayView<const double> eion_block(
    xss_data_extractor->extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = xss_data_extractor->returnEIONLoc();

  // Extract the number of subshells (N_s)
  int num_shells = subshell_endf_designators.size();

  // Extract the number of knock-on tables by subshell (N_i)
  std::vector<double> num_tables(eion_block(0,num_shells));

  // Extract the location of info about knock-on tables by subshell
  std::vector<double> table_info(eion_block(num_shells,num_shells));

  // Extract the location of knock-on tables by subshell
  std::vector<double> table_loc(eion_block(2*num_shells,num_shells));

  // Subshell index
  unsigned shell_index = 0;

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[shell_index]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[shell_index]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  std::vector<double> table_energy_grid(eion_block( subshell_info,
                                                       num_tables[shell_index] ) );

  // Extract the length of the knock-on sampling tables
  std::vector<double> table_length(eion_block(
                               subshell_info + num_tables[shell_index],
                               num_tables[shell_index] ) );

  // Extract the offset of the knock-on sampling tables
  std::vector<double> table_offset(eion_block(
                             subshell_info + 2*num_tables[shell_index],
                             num_tables[shell_index] ) );

  // Create the electroionization subshell distribution
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
    subshell_info,
    subshell_loc,
    num_tables[shell_index],
    binding_energies[shell_index],
    xss_data_extractor->isEPRVersion14(),
    eion_block,
    epr14_electroionization_distribution,
    1e-6 );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellElectronScatteringDistributionACEFactoryV14.cpp
//---------------------------------------------------------------------------//
