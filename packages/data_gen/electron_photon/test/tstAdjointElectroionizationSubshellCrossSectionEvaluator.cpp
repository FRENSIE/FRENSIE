//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectroionizationSubshellCrossSection.cpp
//! \author Luke Kersting
//! \brief  Adjoint electroionization subshell cross section evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::AdjointElectroionizationSubshellCrossSectionEvaluator>
  adjoint_h_cs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint differential cross section can be evaluated for the first subshell
TEUCHOS_UNIT_TEST( AdjointElectroionizationSubshellCrossSectionEvaluator,
		   evaluateDifferentialCrossSection )
{
  
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
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated for the first subshell
TEUCHOS_UNIT_TEST( AdjointElectroionizationSubshellCrossSectionEvaluator,
		   evaluateCrossSection )
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
// Check that the max outgoing adjoint energy can be returned for a given energy
TEUCHOS_UNIT_TEST( AdjointElectroionizationSubshellCrossSectionEvaluator,
		   getMaxEnergyAtEnergy_h )
{
  double max_outgoing_energy = adjoint_h_cs->getMaxOutgoingEnergyAtEnergy( 1.0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( max_outgoing_energy,
				  1e5,
  				  1e-15 );

  max_outgoing_energy = adjoint_h_cs->getMaxOutgoingEnergyAtEnergy( 1e-8 );
  
  UTILITY_TEST_FLOATING_EQUALITY( max_outgoing_energy,
				  1.416970000000E-05		,
  				  1e-15 );

  max_outgoing_energy = adjoint_h_cs->getMaxOutgoingEnergyAtEnergy( 0.00000000279860 );
  
  UTILITY_TEST_FLOATING_EQUALITY( max_outgoing_energy,
				  0.0,
  				  1e-15 );
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

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators = 
    xss_data_extractor->extractSubshellENDFDesignators();
    
  // Extract the subshell binding energies
  Teuchos::ArrayView<const double> binding_energies =
    xss_data_extractor->extractSubshellBindingEnergies();

  Teuchos::Array<MonteCarlo::SubshellType> subshell_order(
					    subshell_endf_designators.size() );

    for( unsigned i = 0; i < subshell_order.size(); ++i )
    {
      subshell_order[i] = MonteCarlo::convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
    }

  // Extract the number of subshells (N_s)
  unsigned num_subshells = subshell_order.size();
  
  // Extract the number of points in the energy grid
  unsigned num_energy_points = energy_grid.size();

  // Extract the subshell cross sections
  Teuchos::ArrayView<const double> raw_subshell_cross_sections =
    xss_data_extractor->extractElectroionizationSubshellCrossSections();


  // Extract the electroionization data block (EION)
  Teuchos::ArrayView<const double> eion_block(
				      xss_data_extractor->extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = xss_data_extractor->returnEIONLoc();

  // Extract the number of knock-on tables by subshell (N_i)
  Teuchos::Array<double> num_tables(eion_block(0,num_subshells));

  // Extract the location of info about knock-on tables by subshell
  Teuchos::Array<double> table_info(eion_block(num_subshells,num_subshells));

  // Extract the location of knock-on tables by subshell
  Teuchos::Array<double> table_loc(eion_block(2*num_subshells,num_subshells));

 Teuchos::RCP<MonteCarlo::ElectroatomicReaction> electroionization_subshell_reaction;

  unsigned first_subshell = 0;

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[first_subshell]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[first_subshell]- eion_loc - 1;


  // Subshell cross section without zeros removed  
  Teuchos::ArrayView<const double> raw_subshell_cross_section =
  raw_subshell_cross_sections( first_subshell*num_energy_points,num_energy_points );

  // Electroionization cross section with zeros removed
  Teuchos::ArrayRCP<double> subshell_cross_section;
  
  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index;

  // Remove all cross sections equal to zero
  MonteCarlo::ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                           energy_grid,
                           raw_subshell_cross_section,
                           subshell_cross_section,
                           threshold_energy_index );
/*
  // Subshell distribution 
  DataGen::AdjointElectroionizationSubshellCrossSectionEvaluator::ElectroionizationSubshellDistribution
             subshell_distribution( num_tables[first_subshell] );

  // Create the subshell distribution
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionACEFactory::createSubshellDistribution( 
        subshell_info,
        subshell_loc,
        num_tables[first_subshell],
	eion_block,
	subshell_distribution );
 
  // The electroionization subshell distribution
  Teuchos::RCP<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
    electroionization_subshell_distribution;
    
  electroionization_subshell_distribution.reset( 
    new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution( 
                                subshell_distribution, 
                                binding_energies[first_subshell] ) );
*/                                                    
    // Create the electroionization subshell distribution
   
  // The electroionization subshell distribution
  Teuchos::RCP<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
    electroionization_subshell_distribution;
 MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
        subshell_info,
        subshell_loc,
        num_tables[first_subshell],
        binding_energies[first_subshell],
	eion_block,
	electroionization_subshell_distribution );


    // Create the subshell electroelectric reaction
    electroionization_subshell_reaction.reset(
      new MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
              energy_grid,
              subshell_cross_section,
              threshold_energy_index,
              subshell_order[first_subshell],
              electroionization_subshell_distribution ) );


  // Initialize the hydrogen adjoint cross section evaluator
  adjoint_h_cs.reset( new DataGen::AdjointElectroionizationSubshellCrossSectionEvaluator(
                                    binding_energies[first_subshell],
                                    electroionization_subshell_reaction,
                                    electroionization_subshell_distribution ) );

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
// end tstAdjointElectroionizationSubshellCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
