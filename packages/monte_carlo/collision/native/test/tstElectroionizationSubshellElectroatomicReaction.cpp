//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Electroionization Subshell electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectroatomicReaction> ace_first_subshell_reaction;

Teuchos::RCP<MonteCarlo::ElectroatomicReaction> ace_last_subshell_reaction;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_first_subshell_reaction->getReactionType(),
		       MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( ace_last_subshell_reaction->getReactionType(),
		       MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_first_subshell_reaction->getThresholdEnergy(),
                       8.975400000000E-02 );

  TEST_EQUALITY_CONST( ace_last_subshell_reaction->getThresholdEnergy(),
                       1.000000000000E-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getNumberOfEmittedElectrons_ace )
{
  TEST_EQUALITY_CONST( ace_first_subshell_reaction->getNumberOfEmittedElectrons(1e-3),
		       0u );

  TEST_EQUALITY_CONST( ace_first_subshell_reaction->getNumberOfEmittedElectrons(20.0),
		       1u );

  TEST_EQUALITY_CONST( ace_last_subshell_reaction->getNumberOfEmittedElectrons(1e-3),
		       1u );

  TEST_EQUALITY_CONST( ace_last_subshell_reaction->getNumberOfEmittedElectrons(20.0),
		       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST( ace_first_subshell_reaction->getNumberOfEmittedPhotons(1e-3),
		       0u );

  TEST_EQUALITY_CONST( ace_first_subshell_reaction->getNumberOfEmittedPhotons(20.0),
		       0u );

  TEST_EQUALITY_CONST( ace_last_subshell_reaction->getNumberOfEmittedPhotons(1e-3),
		       0u );

  TEST_EQUALITY_CONST( ace_last_subshell_reaction->getNumberOfEmittedPhotons(20.0),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getCrossSection_ace )
{
  // First Subshell
  double cross_section =
    ace_first_subshell_reaction->getCrossSection( 2.000000000000E-01 );

  TEST_FLOATING_EQUALITY( cross_section, 4.991897715052E+00, 1e-12 );

  cross_section =
    ace_first_subshell_reaction->getCrossSection( 1.500000000000E+00 );

  TEST_FLOATING_EQUALITY( cross_section, 1.174906212079E+01, 1e-12 );

  cross_section =
    ace_first_subshell_reaction->getCrossSection( 6.000000000000E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 2.443293975497E+01, 1e-12 );

  // Last Subshell
  cross_section =
    ace_last_subshell_reaction->getCrossSection( 2.000000000000E-01 );

  TEST_FLOATING_EQUALITY( cross_section, 3.567266284782E+05, 1e-12 );

  cross_section =
    ace_last_subshell_reaction->getCrossSection( 1.500000000000E+00 );

  TEST_FLOATING_EQUALITY( cross_section, 1.949916537107E+05, 1e-12 );

  cross_section =
    ace_last_subshell_reaction->getCrossSection( 6.000000000000E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.870602125397E+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the first_subshell reaction can be simulated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, react_ace )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_first_subshell_reaction->react( electron, bank, shell_of_interaction );

  TEST_ASSERT( electron.getEnergy() < 20.0 );
  TEST_ASSERT( electron.getZDirection() < 1.0 );
  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint differential cross section can be evaluated for the first subshell
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction,
		   evaluateAdjointDifferentialCrossSection )
{
 /*
  double diff_cross_section =
    adjoint_h_cs->evaluateDifferentialCrossSection( 1.000000000000E-04,
						    1.584900000000E-05 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  6.582854525864990E+11,
				  1e-12 );

  diff_cross_section =
    adjoint_h_cs->evaluateDifferentialCrossSection( 1.000000000000E-04,
						    7.054100000000E-05 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  6.582854525864990E+11,
				  1e-12 );

  diff_cross_section =
    adjoint_h_cs->evaluateDifferentialCrossSection( 6.309570000000E-02,
						    1.009140000000E-03 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  9.362881076230510E+05,
				  1e-12 );

  diff_cross_section =
    adjoint_h_cs->evaluateDifferentialCrossSection( 6.309570000000E-02,
						    3.154110000000E-02 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  2.802751399940720E+03,
				  1e-12 );

  diff_cross_section =
    adjoint_h_cs->evaluateDifferentialCrossSection( 1.000000000000E+05,
						    1.042750000000E+01 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  1.959197477405080E-03,
				  1e-12 );

  diff_cross_section =
    adjoint_h_cs->evaluateDifferentialCrossSection( 1.000000000000E+05,
						    9.999999510161E+04 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  9.534573269680380E+03,
				  1e-12 );
*/
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated for the first subshell
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction,
		   evaluateAdjointCrossSection )
{/*
  double cross_section = adjoint_h_cs->evaluateCrossSection( 0.001, 0.001 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 0.001, 1e-4);



  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
				  2.050,
  				  1e-15 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 0.001,
  						      0.0010039292814978508 );


  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
				  8.523,
  				  1e-15 );
  				  */
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  // Extract the energy grid and cross section
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

  Teuchos::ArrayView<const double> raw_subshell_cross_sections =
    xss_data_extractor->extractElectroionizationSubshellCrossSections();

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

//---------------------------------------------------------------------------//
  // Use the first subshell for test
  unsigned first_subshell = 0;

  // Assign raw cross sections for first subshell
  Teuchos::ArrayView<const double> raw_first_subshell_cross_section(
                                          raw_subshell_cross_sections(
                                              first_subshell*energy_grid.size(),
                                              energy_grid.size()) );

  // Eliminate any cross sections entries equal to zero
  Teuchos::ArrayView<const double>::iterator first_start =
    std::find_if( raw_first_subshell_cross_section.begin(),
                  raw_first_subshell_cross_section.end(),
                  notEqualZero );

  // Assign cross sections for first subshell
  Teuchos::ArrayRCP<double> first_subshell_cross_section;
  first_subshell_cross_section.assign( first_start,
                                       raw_first_subshell_cross_section.end() );

  // Calculate threshold energy index
  unsigned first_subshell_threshold_index =
    energy_grid.size() - first_subshell_cross_section.size();

  // Assign subshell type for the first subshell
  Data::SubshellType interaction_first_subshell;
  interaction_first_subshell = Data::convertENDFDesignatorToSubshellEnum(
                                    subshell_endf_designators[first_subshell] );

  // Subshell table info realtive to the EION Block
  unsigned first_subshell_info = table_info[first_subshell]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned first_subshell_loc = table_loc[first_subshell]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  Teuchos::Array<double> first_energy_grid(
                                     eion_block( first_subshell_info,
                                                 num_tables[first_subshell] ) );

  // Extract the length of the knock-on sampling tables
  Teuchos::Array<double> first_table_length(eion_block(
                               first_subshell_info + num_tables[first_subshell],
                               num_tables[first_subshell] ) );

  // Extract the offset of the knock-on sampling tables
  Teuchos::Array<double> first_table_offset(eion_block(
                             first_subshell_info + 2*num_tables[first_subshell],
                             num_tables[first_subshell] ) );

   // Create the electroionization sampling table for the first subshell
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution
      first_subshell_function( num_tables[first_subshell] );


  for( unsigned n = 0; n < num_tables[first_subshell]; ++n )
  {
    first_subshell_function[n].first = first_energy_grid[n];

    first_subshell_function[n].second.reset(
     new Utility::HistogramDistribution(
       eion_block( first_subshell_loc + first_table_offset[n],
                   first_table_length[n] ),
       eion_block( first_subshell_loc + first_table_offset[n] + first_table_length[n] + 1,
                   first_table_length[n] - 1),
       true ) );
  }

  // Create the subshell distribution from the function
  Teuchos::RCP<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
    first_subshell_distribution;

    first_subshell_distribution.reset(
      new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                                           first_subshell_function,
                                           binding_energies[first_subshell] ) );

  // Create the reaction
  ace_first_subshell_reaction.reset(
    new MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
                      energy_grid,
                      first_subshell_cross_section,
                      first_subshell_threshold_index,
                      interaction_first_subshell,
                      first_subshell_distribution ) );

//---------------------------------------------------------------------------//
  // Use the last subshell for test
  unsigned last_subshell = subshell_endf_designators.size() -1;

  // Assign raw cross sections for last subshell
  Teuchos::ArrayView<const double> raw_last_subshell_cross_section(
                           raw_subshell_cross_sections(
                               last_subshell*energy_grid.size(),
                               energy_grid.size()) );

  // Eliminate any cross sections entries equal to zero
  Teuchos::ArrayView<const double>::iterator last_start =
    std::find_if( raw_last_subshell_cross_section.begin(),
                  raw_last_subshell_cross_section.end(),
                  notEqualZero );

  // Assign cross sections for last subshell
  Teuchos::ArrayRCP<double> last_subshell_cross_section;
  last_subshell_cross_section.assign( last_start,
                                      raw_last_subshell_cross_section.end() );

  // Calculate threshold energy index
  unsigned last_subshell_threshold_index =
    energy_grid.size() - last_subshell_cross_section.size();

  // Assign subshell type for the last subshell
  Data::SubshellType interaction_last_subshell;
  interaction_last_subshell = Data::convertENDFDesignatorToSubshellEnum(
                                     subshell_endf_designators[last_subshell] );

  // Subshell table info realtive to the EION Block
  unsigned last_subshell_info = table_info[last_subshell]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned last_subshell_loc = table_loc[last_subshell]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  Teuchos::Array<double> last_energy_grid(
                                      eion_block( last_subshell_info,
                                                  num_tables[last_subshell] ) );

  // Extract the length of the knock-on sampling tables
  Teuchos::Array<double> last_table_length(eion_block(
                               last_subshell_info + num_tables[last_subshell],
                               num_tables[last_subshell] ) );

  // Extract the offset of the knock-on sampling tables
  Teuchos::Array<double> last_table_offset(eion_block(
                             last_subshell_info + 2*num_tables[last_subshell],
                             num_tables[last_subshell] ) );

   // Create the electroionization sampling table for the last_subshell
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution
      last_subshell_function( num_tables[last_subshell] );


  for( unsigned n = 0; n < num_tables[last_subshell]; ++n )
  {
    last_subshell_function[n].first = last_energy_grid[n];

    last_subshell_function[n].second.reset(
     new Utility::HistogramDistribution(
       eion_block( last_subshell_loc + last_table_offset[n],
                   last_table_length[n] ),
       eion_block( last_subshell_loc + last_table_offset[n] + last_table_length[n] + 1,
                   last_table_length[n] - 1),
       true ) );
  }

  // Create the subshell distribution from the function
  Teuchos::RCP<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
    last_subshell_distribution;

  last_subshell_distribution.reset(
    new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                                           last_subshell_function,
                                           binding_energies[last_subshell] ) );

  // Create the reaction
  ace_last_subshell_reaction.reset(
    new MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
                      energy_grid,
                      last_subshell_cross_section,
                      last_subshell_threshold_index,
                      interaction_last_subshell,
                      last_subshell_distribution ) );


  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

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
// end tstElectroionizationSubshellElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
