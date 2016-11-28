//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Electroionization electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
  ace_electroionization_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   getBindingEnergy )
{
  // Get binding energy
  double binding_energy =
    ace_electroionization_distribution->getBindingEnergy();

  // Test original electron
  TEST_EQUALITY_CONST( binding_energy, 8.829000000000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the max secondary (knock-on) electron energy can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   getMaxSecondaryEnergyAtIncomingEnergy )
{
  // Get max energy
  double max_energy =
    ace_electroionization_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 8.829E-02 );

  // Test original electron
  TEST_EQUALITY_CONST( max_energy, 0.0 );

  // Get max energy
  max_energy =
    ace_electroionization_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 1e5 );

  // Test original electron
  UTILITY_TEST_FLOATING_EQUALITY( max_energy, 4.9999955855E+04, 1e-12 );

  // Get max energy
  max_energy =
    ace_electroionization_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 2.0 );

  // Test original electron
  UTILITY_TEST_FLOATING_EQUALITY( max_energy, 9.55855E-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluate )
{
  double pdf = ace_electroionization_distribution->evaluate( 8.829e-2, 5e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );

  pdf = ace_electroionization_distribution->evaluate( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 683.2234482287432229, 1e-12 );

  pdf = ace_electroionization_distribution->evaluate( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 676.63484458985044512, 1e-12 );

  pdf = ace_electroionization_distribution->evaluate( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.4576996990397919074, 1e-12 );

  pdf = ace_electroionization_distribution->evaluate( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.045394577710E+00, 1e-12 );

  pdf = ace_electroionization_distribution->evaluate( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 4.399431656723E-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluatePDF )
{
  double pdf = ace_electroionization_distribution->evaluatePDF( 8.829e-2, 5e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );

  pdf = ace_electroionization_distribution->evaluatePDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 683.2234482287432229, 1e-12 );

  pdf = ace_electroionization_distribution->evaluatePDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 676.63484458985044512, 1e-12 );

  pdf = ace_electroionization_distribution->evaluatePDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.4576996990397919074, 1e-12 );

  pdf = ace_electroionization_distribution->evaluatePDF( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.045394577710E+00, 1e-12 );

  pdf = ace_electroionization_distribution->evaluatePDF( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 4.399431656723E-07, 1e-12 );

  pdf = ace_electroionization_distribution->evaluatePDF( 1e5, 5e4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.337458903100E-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluateCDF )
{
  double cdf = ace_electroionization_distribution->evaluateCDF( 8.829e-2, 5e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 0.0, 1e-12 );

  cdf = ace_electroionization_distribution->evaluateCDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 2.92009701772965E-01, 1e-12 );

  cdf = ace_electroionization_distribution->evaluateCDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 2.96911596049771E-01, 1e-12 );

  cdf = ace_electroionization_distribution->evaluateCDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 7.99240642349262E-01, 1e-12 );

  cdf = ace_electroionization_distribution->evaluateCDF( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 7.299181455072E-01, 1e-12 );

  cdf = ace_electroionization_distribution->evaluateCDF( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.999123864280E-01, 1e-10 );

  cdf = ace_electroionization_distribution->evaluateCDF( 1e5, 5e4 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sample_knock_on )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;

  double knock_on_energy, knock_on_angle_cosine;

  // sample the electron
  ace_electroionization_distribution->sample( incoming_energy,
                                              knock_on_energy,
                                              knock_on_angle_cosine );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.279436961765390, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 4.105262105768E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  double incoming_energy = 1.0;

  double outgoing_energy, knock_on_energy,
         scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  ace_electroionization_distribution->sample( incoming_energy,
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

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

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

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
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
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  ace_electroionization_distribution->scatterElectron( electron,
                                                       bank,
                                                       shell_of_interaction );

  // Test original electron
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.964446703542646, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 8.706573789423E-01, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.279436961765390, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 4.105262105768E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace_file",
                   &test_ace_file_name,
                   "Test ACE file name" );
  clp().setOption( "test_ace_table",
                   &test_ace_table_name,
                   "Test ACE table name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
     new Data::ACEFileHandler( test_ace_file_name,
                               test_ace_table_name,
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

  // Subshell
  unsigned subshell = 0;

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[subshell]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[subshell]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  Teuchos::Array<double> table_energy_grid(eion_block( subshell_info,
                                                       num_tables[subshell] ) );

  // Extract the length of the knock-on sampling tables
  Teuchos::Array<double> table_length(eion_block(
                               subshell_info + num_tables[subshell],
                               num_tables[subshell] ) );

  // Extract the offset of the knock-on sampling tables
  Teuchos::Array<double> table_offset(eion_block(
                             subshell_info + 2*num_tables[subshell],
                             num_tables[subshell] ) );

  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType
     function_data( num_tables[subshell] );

  for( unsigned n = 0; n < num_tables[subshell]; ++n )
  {
    function_data[n].first = table_energy_grid[n];

    function_data[n].second.reset(
     new Utility::HistogramDistribution(
      eion_block( subshell_loc + table_offset[n], table_length[n] ),
      eion_block( subshell_loc + table_offset[n] + table_length[n] + 1,
                  table_length[n] - 1),
      true ) );
  }

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> subshell_distribution(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            function_data ) );

  // Create the distributions
  ace_electroionization_distribution.reset(
        new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            binding_energies[subshell] ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
