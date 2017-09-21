//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  electroionization subshell scattering distribution ACE factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
  ace_electroionization_distribution, epr14_electroionization_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   getBindingEnergy )
{
  // Get binding energy
  double binding_energy = ace_electroionization_distribution->getBindingEnergy();
  TEST_EQUALITY_CONST( binding_energy, 8.829E-02 );

  // Get binding energy
  binding_energy = epr14_electroionization_distribution->getBindingEnergy();
  TEST_EQUALITY_CONST( binding_energy, 8.829E-02 );
}

//---------------------------------------------------------------------------//
// Check that the min secondary (knock-on) electron energy can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   getMinSecondaryEnergyAtIncomingEnergy )
{
  // Get min energy
  double min_energy =
    ace_electroionization_distribution->getMinSecondaryEnergyAtIncomingEnergy( 8.829E-02 );
  TEST_EQUALITY_CONST( min_energy, 0.0 );

  // Get min energy
  min_energy =
    ace_electroionization_distribution->getMinSecondaryEnergyAtIncomingEnergy( 1e5 );
  UTILITY_TEST_FLOATING_EQUALITY( min_energy, 1e-7, 1e-12 );

  // Get min energy
  min_energy =
    ace_electroionization_distribution->getMinSecondaryEnergyAtIncomingEnergy( 2.0 );
  UTILITY_TEST_FLOATING_EQUALITY( min_energy, 1e-7, 1e-12 );


  // Use eprdata14 file
  min_energy =
    epr14_electroionization_distribution->getMinSecondaryEnergyAtIncomingEnergy( 8.829E-02 );
  TEST_EQUALITY_CONST( min_energy, 0.0 );

  // Get min energy
  min_energy =
    epr14_electroionization_distribution->getMinSecondaryEnergyAtIncomingEnergy( 1e5 );
  UTILITY_TEST_FLOATING_EQUALITY( min_energy, 1e-7, 1e-12 );

  // Get min energy
  min_energy =
    epr14_electroionization_distribution->getMinSecondaryEnergyAtIncomingEnergy( 2.0 );
  UTILITY_TEST_FLOATING_EQUALITY( min_energy, 1e-7, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the max secondary (knock-on) electron energy can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   getMaxSecondaryEnergyAtIncomingEnergy )
{
  // Get max energy
  double max_energy =
    ace_electroionization_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 8.829E-02 );
  TEST_EQUALITY_CONST( max_energy, 0.0 );

  // Get max energy
  max_energy =
    ace_electroionization_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 1e5 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy, 4.9999955855E+04, 1e-12 );

  // Get max energy
  max_energy =
    ace_electroionization_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 2.0 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy, 9.55855E-01, 1e-12 );

  // Use eprdata14 file
  max_energy =
    epr14_electroionization_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 8.829E-02 );
  TEST_EQUALITY_CONST( max_energy, 0.0 );

  // Get max energy
  max_energy =
    epr14_electroionization_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 1e5 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy, 4.9999955855E+04, 1e-12 );

  // Get max energy
  max_energy =
    epr14_electroionization_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 2.0 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy, 9.55855E-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   evaluateCDF )
{
  double cdf;
  cdf = ace_electroionization_distribution->evaluateCDF( 8.829e-2 + 1e-8, 1e-8 );
  TEST_EQUALITY_CONST( cdf, 0.0 );

  cdf = ace_electroionization_distribution->evaluateCDF( 8.829e-2 + 3e-8, 1.0001e-8 );
  TEST_FLOATING_EQUALITY( cdf, 6.9444444444523190e-07, 1e-12 );

  cdf = ace_electroionization_distribution->evaluateCDF( 9.12175e-2, 4.275e-4 );
  TEST_FLOATING_EQUALITY( cdf, 2.9200970177296481e-01, 1e-12 );

  cdf = ace_electroionization_distribution->evaluateCDF( 1e-1, 1e-2 );
  TEST_FLOATING_EQUALITY( cdf, 6.7056932843167538e-01, 1e-12 );

  cdf = ace_electroionization_distribution->evaluateCDF( 1.0, 1.33136131511529e-1 );
  TEST_FLOATING_EQUALITY( cdf, 7.9924064234926140e-01, 1e-12 );

  cdf = ace_electroionization_distribution->evaluateCDF( 1.0, 9.7163E-02 );
  TEST_FLOATING_EQUALITY( cdf, 7.2991814550720002e-01, 1e-12 );

  cdf = ace_electroionization_distribution->evaluateCDF( 1e5, 1.752970e2 );
  TEST_FLOATING_EQUALITY( cdf, 9.9991238642799996e-01, 1e-12 );

  // Use eprdata14 file
  cdf = epr14_electroionization_distribution->evaluateCDF( 8.829e-2 + 1e-8, 1e-8 );
  TEST_EQUALITY_CONST( cdf, 0.0 );

  cdf = epr14_electroionization_distribution->evaluateCDF( 8.829e-2 + 3e-8, 1.0001e-8 );
  TEST_FLOATING_EQUALITY( cdf, 8.3333333333244009e-06, 1e-12 );

  cdf = epr14_electroionization_distribution->evaluateCDF( 9.12175e-2, 4.275e-4 );
  TEST_FLOATING_EQUALITY( cdf, 2.9200970177296481e-01, 1e-12 );

  //! \todo Figure out why this test cannot be evaluated to the tolerance (1e-6)
  // cdf = epr14_electroionization_distribution->evaluateCDF( 1e-1, 1e-2 );
  // TEST_FLOATING_EQUALITY( cdf, 6.7056932843167538e-01, 1e-12 );

  cdf = epr14_electroionization_distribution->evaluateCDF( 1.0, 1.33136131511529e-1 );
  TEST_FLOATING_EQUALITY( cdf, 7.9997181385885974e-01, 1e-12 );

  cdf = epr14_electroionization_distribution->evaluateCDF( 1.0, 9.7163E-02 );
  TEST_FLOATING_EQUALITY( cdf, 7.2991814550720002e-01, 1e-12 );

  cdf = epr14_electroionization_distribution->evaluateCDF( 1e5, 1.752970e2 );
  TEST_FLOATING_EQUALITY( cdf, 9.9991238642799996e-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
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
  ace_electroionization_distribution->sample( incoming_energy,
                                              knock_on_energy,
                                              knock_on_angle_cosine );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.279436961765390, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 4.105262105768E-02, 1e-12 );


  // sample the electron using eprdata14 file
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  epr14_electroionization_distribution->sample( incoming_energy,
                                                knock_on_energy,
                                                knock_on_angle_cosine );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 2.6192810212740608e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 3.5894248945649160e-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   samplePrimaryAndSecondary )
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
  ace_electroionization_distribution->samplePrimaryAndSecondary(
        incoming_energy,
        outgoing_energy,
        knock_on_energy,
        scattering_angle_cosine,
        knock_on_angle_cosine );

  // Test original electron
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.964446703542646, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 8.706573789423E-01, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.279436961765390, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 4.105262105768E-02, 1e-12 );


  // sample the electron using the eprdata14 file
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  epr14_electroionization_distribution->samplePrimaryAndSecondary(
        incoming_energy,
        outgoing_energy,
        knock_on_energy,
        scattering_angle_cosine,
        knock_on_angle_cosine );

  // Test original electron
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.6598402273415784e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 8.7581575105435083e-01, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 2.6192810212740608e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 3.5894248945649160e-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0.0;
  double incoming_energy = 1.0;
  double knock_on_energy, scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  ace_electroionization_distribution->sampleAndRecordTrials(
                                                        incoming_energy,
                                                        knock_on_energy,
                                                        knock_on_angle_cosine,
                                                        trials );

  // Test trials
  TEST_EQUALITY_CONST( trials, 1.0 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.279436961765390, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 4.105262105768E-02, 1e-12 );


  // sample the electron using the eprdata14 file
  epr14_electroionization_distribution->sampleAndRecordTrials(
                                                        incoming_energy,
                                                        knock_on_energy,
                                                        knock_on_angle_cosine,
                                                        trials );

  // Test trials
  TEST_EQUALITY_CONST( trials, 2.0 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 2.6192810212740608e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 3.5894248945649160e-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionACEFactory,
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
  ace_electroionization_distribution->scatterElectron( electron,
                                                       bank,
                                                       shell_of_interaction );

  // Test original electron
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.8142335272952452e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.3707352378289799, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 2.5457978376168189e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 4.0974762171020106e-02, 1e-12 );

  bank.pop();

  // Scatter electron using the eprdata14 file
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  electron.setEnergy( 1.5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Sscatter electron
  epr14_electroionization_distribution->scatterElectron( electron,
                                                         bank,
                                                         shell_of_interaction );

  // Test original electron
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.8227274979569801e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.3763055557910753e+00, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 2.3726599328510786e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 3.5404444208924822e-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace12_file_name, test_ace12_table_name,
            test_ace14_file_name, test_ace14_table_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace12_file",
                   &test_ace12_file_name,
                   "Test ACE file name" );
  clp().setOption( "test_ace12_table",
                   &test_ace12_table_name,
                   "Test ACE12 table name" );

  clp().setOption( "test_ace14_file",
                   &test_ace14_file_name,
                   "Test ACE14 file name" );
  clp().setOption( "test_ace14_table",
                   &test_ace14_table_name,
                   "Test ACE14 table name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create eprdata12 distribution
  {
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace12_file_name,
                                  test_ace12_table_name,
                                  1u ) );
  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  // Extract the cross sections energy grid
  Teuchos::ArrayView<const double> energy_grid =
    xss_data_extractor->extractElectronEnergyGrid() ;

  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators =
    xss_data_extractor->extractSubshellENDFDesignators();

  // Extract the subshell binding energies
  Teuchos::ArrayView<const double> binding_energies =
    xss_data_extractor->extractSubshellBindingEnergies();

  // Extract the electroionization data block (EION)
  Teuchos::ArrayView<const double> eion_block(
    xss_data_extractor->extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = xss_data_extractor->returnEIONLoc();

  // Extract the number of subshells (N_s)
  int num_shells = subshell_endf_designators.size();

  // Extract the number of knock-on tables by subshell (N_i)
  Teuchos::Array<double> num_tables(eion_block(0,num_shells));

  // Extract the location of info about knock-on tables by subshell
  Teuchos::Array<double> table_info(eion_block(num_shells,num_shells));

  // Extract the location of knock-on tables by subshell
  Teuchos::Array<double> table_loc(eion_block(2*num_shells,num_shells));

  // Subshell index
  unsigned shell_index = 0;

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[shell_index]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[shell_index]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  Teuchos::Array<double> table_energy_grid(eion_block( subshell_info,
                                                       num_tables[shell_index] ) );

  // Extract the length of the knock-on sampling tables
  Teuchos::Array<double> table_length(eion_block(
                               subshell_info + num_tables[shell_index],
                               num_tables[shell_index] ) );

  // Extract the offset of the knock-on sampling tables
  Teuchos::Array<double> table_offset(eion_block(
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
    ace_electroionization_distribution,
    1e-6 );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();
  }


  // Create eprdata14 distribution
  {
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace14_file_name,
                                  test_ace14_table_name,
                                  1u ) );
  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  // Extract the cross sections energy grid
  Teuchos::ArrayView<const double> energy_grid =
    xss_data_extractor->extractElectronEnergyGrid() ;

  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators =
    xss_data_extractor->extractSubshellENDFDesignators();

  // Extract the subshell binding energies
  Teuchos::ArrayView<const double> binding_energies =
    xss_data_extractor->extractSubshellBindingEnergies();

  // Extract the electroionization data block (EION)
  Teuchos::ArrayView<const double> eion_block(
    xss_data_extractor->extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = xss_data_extractor->returnEIONLoc();

  // Extract the number of subshells (N_s)
  int num_shells = subshell_endf_designators.size();

  // Extract the number of knock-on tables by subshell (N_i)
  Teuchos::Array<double> num_tables(eion_block(0,num_shells));

  // Extract the location of info about knock-on tables by subshell
  Teuchos::Array<double> table_info(eion_block(num_shells,num_shells));

  // Extract the location of knock-on tables by subshell
  Teuchos::Array<double> table_loc(eion_block(2*num_shells,num_shells));

  // Subshell index
  unsigned shell_index = 0;

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[shell_index]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[shell_index]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  Teuchos::Array<double> table_energy_grid(eion_block( subshell_info,
                                                       num_tables[shell_index] ) );

  // Extract the length of the knock-on sampling tables
  Teuchos::Array<double> table_length(eion_block(
                               subshell_info + num_tables[shell_index],
                               num_tables[shell_index] ) );

  // Extract the offset of the knock-on sampling tables
  Teuchos::Array<double> table_offset(eion_block(
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
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
