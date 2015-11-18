//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledYieldBasedPhotonProductionReaction.cpp
//! \author Eli  Moll
//! \brief  Yield Based Decoupled photon production reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledYieldBasedPhotonProductionReaction.hpp"
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronAbsorptionReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_basic_ace_file_name;
std::string test_basic_ace_table_name;
Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;

Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;

Teuchos::RCP<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::PhotonState> > 
  photon_production_distribution;
    
unsigned reaction_type;

Teuchos::RCP<MonteCarlo::DecoupledYieldBasedPhotonProductionReaction> nuclear_reaction;

Teuchos::RCP<MonteCarlo::NuclearReaction> base_reaction;

Teuchos::RCP<MonteCarlo::NuclearReaction> total_reaction;

Teuchos::Array<std::shared_ptr<Utility::OneDDistribution> > d_total_mt_yield_array;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeDecoupledYieldBasedPhotonProductionReaction(Teuchos::RCP<MonteCarlo::DecoupledYieldBasedPhotonProductionReaction>& reaction)
{
  // Reaction type
  reaction_type = 102001u;
  
  // Create the ace file handler
  ace_file_handler.reset(new Data::ACEFileHandler( test_basic_ace_file_name,
						     test_basic_ace_table_name,
						     1u ) );
						     
	// Create the XSS data extractor
  xss_data_extractor.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				        ace_file_handler->getTableJXSArray(),
				        ace_file_handler->getTableXSSArray()));
 
  // Create the photon production nuclear scattering distribution ACE factory
  MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory 
    photon_production_dist_factory( test_basic_ace_file_name,
			                              ace_file_handler->getTableAtomicWeightRatio(),
			                              *xss_data_extractor );
 
  // Create the photon production nuclear scattering distribution
  photon_production_dist_factory.createScatteringDistribution(
					     reaction_type,
					     photon_production_distribution );;

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  Teuchos::ArrayRCP<double> total_cross_section;
  total_cross_section.deepCopy( xss_data_extractor->extractTotalCrossSection() );

  // Create the total reaction
  total_reaction.reset( new MonteCarlo::NeutronAbsorptionReaction( 
               MonteCarlo::N__TOTAL_REACTION,
			         ace_file_handler->getTableTemperature(),
				       0.0,
				       0u,
				       energy_grid,
				       total_cross_section ) );

  // Create the base reaction with fictitious cross section data (total)
  base_reaction.reset( new MonteCarlo::NeutronAbsorptionReaction( 
               MonteCarlo::N__GAMMA_REACTION,
			         ace_file_handler->getTableTemperature(),
				       0.0,
				       0u,
				       energy_grid,
				       total_cross_section ) );

  // Construct the yield energy grid and yield data
  std::vector<double> yield_energy_grid = { 1.00000000000E-11, 
                                            2.00000000000E+01 };
  std::vector<double> yield_energy_values = { 2.00000000000E+00,
                                              2.00000000000E+00 };
                                              
  Teuchos::ArrayView<double> yield_energy_grid_av( yield_energy_grid );
  Teuchos::ArrayView<double> yield_energy_values_av( yield_energy_values );
  
  std::shared_ptr<Utility::OneDDistribution> d_mtp_yield( 
        new Utility::TabularDistribution<Utility::LinLin>( 
                              yield_energy_grid,
                              yield_energy_values ) );
                              
  d_total_mt_yield_array.push_back( d_mtp_yield );

  // Create the nuclear reaction
  nuclear_reaction.reset( new MonteCarlo::DecoupledYieldBasedPhotonProductionReaction( 
			         MonteCarlo::N__GAMMA_REACTION,
			         reaction_type,
				       ace_file_handler->getTableTemperature(),
				       d_total_mt_yield_array,
				       d_mtp_yield,
				       base_reaction,
				       photon_production_distribution,
				       total_reaction ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the base photon production ID can be returned
TEUCHOS_UNIT_TEST( DecoupledYieldBasedPhotonProductionReaction, getThresholdEnergy )
{
  initializeDecoupledYieldBasedPhotonProductionReaction( nuclear_reaction );

  TEST_EQUALITY_CONST( nuclear_reaction->getThresholdEnergy(), 
		       1.00000000000E-11 );
}

//---------------------------------------------------------------------------//
// Check that the base reaction type can be returned
TEUCHOS_UNIT_TEST( DecoupledYieldBasedPhotonProductionReaction, getCrossSection )
{
  double cross_section = 
    nuclear_reaction->getCrossSection( 1.00000000000e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 2.0*1.17724711000E+03 );

  cross_section = nuclear_reaction->getCrossSection( 1.03125000000E-11 );
  
  TEST_EQUALITY_CONST( cross_section, 2.0*1.15927812000E+03 );
  
  cross_section = nuclear_reaction->getCrossSection( 1.95e1 );
  
  TEST_EQUALITY_CONST( cross_section, 2.0*4.95490443000E-01 );

  cross_section = nuclear_reaction->getCrossSection( 2.0e1 );
  
  TEST_EQUALITY_CONST( cross_section, 2.0*4.82773424000E-01 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_basic_ace_file",
		 &test_basic_ace_file_name,
		 "Test basic ACE file name" );
  clp.setOption( "test_basic_ace_table",
		 &test_basic_ace_table_name,
		 "Test basic ACE table name in basic ACE file" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstDecoupledYieldBasedPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
