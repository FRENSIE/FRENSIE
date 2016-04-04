//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledCrossSectionBasedPhotonProductionReaction.cpp
//! \author Eli  Moll
//! \brief  Cross section based decoupled photon production reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.hpp"
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

Teuchos::RCP<MonteCarlo::DecoupledCrossSectionBasedPhotonProductionReaction> nuclear_reaction;

Teuchos::RCP<MonteCarlo::NuclearReaction> base_reaction;

Teuchos::RCP<MonteCarlo::NuclearReaction> total_reaction;

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestDecoupledCrossSectionBasedPhotonProductionReaction : public MonteCarlo::DecoupledCrossSectionBasedPhotonProductionReaction
{
public:
  TestDecoupledCrossSectionBasedPhotonProductionReaction(  
	  const MonteCarlo::NuclearReactionType base_reaction_type,
	  const unsigned photon_production_id,
	  const double temperature,
	  const unsigned threshold_energy_index,
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cross_section,
	  const Teuchos::RCP<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::PhotonState> >& 
	  photon_production_distribution,
	  const Teuchos::RCP<MonteCarlo::NuclearReaction>& total_reaction,
	  const Teuchos::Array<std::shared_ptr<Utility::OneDDistribution> >& total_mt_yield_array )
    : MonteCarlo::DecoupledCrossSectionBasedPhotonProductionReaction( base_reaction_type,
			       photon_production_id,
			       temperature,
			       threshold_energy_index,
			       incoming_energy_grid,
			       cross_section,
			       photon_production_distribution,
			       total_reaction,
			       total_mt_yield_array )
  { /* ... */ }

  ~TestDecoupledCrossSectionBasedPhotonProductionReaction()
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeDecoupledCrossSectionBasedPhotonProductionReaction(Teuchos::RCP<MonteCarlo::DecoupledCrossSectionBasedPhotonProductionReaction>& reaction)
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


  // Construct the photon production energy grid and yield data
  std::vector<double> xs_energy_grid = { 1.00000000000E+01, 
                                      2.00000000000E+01 };
  std::vector<double> xs_energy_values = { 1.00000000000E+00,
                                           2.00000000000E+00 };
                                              
  Teuchos::ArrayView<double> energy_grid_av( xs_energy_grid );
  Teuchos::ArrayView<double> xs_energy_values_av( xs_energy_values );
  
  Teuchos::ArrayRCP<double> energy_grid_rcp;
  energy_grid_rcp.deepCopy( energy_grid_av );
  Teuchos::ArrayRCP<double> xs_energy_values_rcp;
  xs_energy_values_rcp.deepCopy( xs_energy_values_av );

  // Create the nuclear reaction
  nuclear_reaction.reset( new TestDecoupledCrossSectionBasedPhotonProductionReaction( 
			         MonteCarlo::N__GAMMA_REACTION,
			         reaction_type,
				       ace_file_handler->getTableTemperature(),
				       0u,
				       energy_grid_rcp,
				       xs_energy_values_rcp,
				       photon_production_distribution,
				       total_reaction,
				       Teuchos::Array<std::shared_ptr<Utility::OneDDistribution> >() ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the base photon production ID can be returned
TEUCHOS_UNIT_TEST( DecoupledCrossSectionBasedPhotonProductionReaction, getThresholdEnergy )
{
  initializeDecoupledCrossSectionBasedPhotonProductionReaction( nuclear_reaction );

  TEST_EQUALITY_CONST( nuclear_reaction->getThresholdEnergy(), 
		       1.00000000000E+01 );
}

//---------------------------------------------------------------------------//
// Check that the base reaction type can be returned
TEUCHOS_UNIT_TEST( DecoupledCrossSectionBasedPhotonProductionReaction, getCrossSection )
{
  double cross_section = 
    nuclear_reaction->getCrossSection( 1.00000000000e+01 );
  
  TEST_EQUALITY_CONST( cross_section, 1.00000000000E+00 );

  cross_section = nuclear_reaction->getCrossSection( 1.50000000000e+01 );
  
  TEST_EQUALITY_CONST( cross_section, 1.50000000000E+00 );
  
  cross_section = nuclear_reaction->getCrossSection( 2.00000000000e+01 );
  
  TEST_EQUALITY_CONST( cross_section, 2.00000000000E+00 );
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
// end tstDecoupledCrossSectionBasedPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
