//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledPhotonProductionReaction.cpp
//! \author Eli  Moll
//! \brief  Decoupled photon production reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
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

Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionReaction> nuclear_reaction;

Teuchos::RCP<MonteCarlo::NuclearReaction> total_reaction;

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestDecoupledPhotonProductionReaction : public MonteCarlo::DecoupledPhotonProductionReaction
{
public:
  TestDecoupledPhotonProductionReaction(  
      const MonteCarlo::NuclearReactionType base_reaction_type,
      const unsigned photon_production_id,
      const double temperature,
      const Teuchos::RCP<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::PhotonState> >&
        photon_production_distribution,
      const Teuchos::RCP<MonteCarlo::NuclearReaction>& total_reaction )
    : MonteCarlo::DecoupledPhotonProductionReaction( base_reaction_type,
			       photon_production_id,
			       temperature,
			       photon_production_distribution,
			       total_reaction )
  { /* ... */ }

  ~TestDecoupledPhotonProductionReaction()
  { /* ... */ }
  
  // Return the threshold energy
  double getThresholdEnergy() const
  { /* ... */ }

  // Return the cross section at a given energy
  double getCrossSection( const double energy ) const
  { /* ... */ }

  void react( MonteCarlo::NeutronState& neutron, MonteCarlo::ParticleBank& bank ) const
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeDecoupledPhotonProductionReaction(Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionReaction>& reaction)
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
					     photon_production_distribution );

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  Teuchos::ArrayRCP<double> cross_section;
  cross_section.deepCopy( xss_data_extractor->extractTotalCrossSection() );

  total_reaction.reset( new MonteCarlo::NeutronAbsorptionReaction( 
               MonteCarlo::N__TOTAL_REACTION,
			         ace_file_handler->getTableTemperature(),
				       0.0,
				       0u,
				       energy_grid,
				       cross_section ) );

  nuclear_reaction.reset( new TestDecoupledPhotonProductionReaction( 
			         MonteCarlo::N__GAMMA_REACTION,
			         reaction_type,
				       ace_file_handler->getTableTemperature(),
				       photon_production_distribution,
				       total_reaction ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the base photon production ID can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionReaction, getPhotonProductionId )
{
  initializeDecoupledPhotonProductionReaction( nuclear_reaction );

  TEST_EQUALITY_CONST( nuclear_reaction->getPhotonProductionId(), 
		       MonteCarlo::N__GAMMA_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the base reaction type can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionReaction, getBaseReactionType )
{
  initializeDecoupledPhotonProductionReaction( nuclear_reaction );

  TEST_EQUALITY_CONST( nuclear_reaction->getBaseReactionType(), 
		       MonteCarlo::N__GAMMA_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the photon production reaction ID can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionReaction, getPhotonProductionReactionId )
{
  TEST_EQUALITY_CONST( nuclear_reaction->getPhotonProductionReactionId(), 102001u );		       
}

//---------------------------------------------------------------------------//
// Check that the decoupled photon production reaction can take place
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionReaction, react )
{
  Teuchos::RCP<MonteCarlo::NeutronState> neutron( new MonteCarlo::NeutronState(0ull) );
  
  neutron->setDirection( 0.0, 0.0, 1.0 );
  neutron->setEnergy( 1.0 );

  MonteCarlo::ParticleBank bank;

  bank.push( neutron );
  
  nuclear_reaction->react( *neutron, bank );

  int bank_size = 1;
  if ( !neutron->isGone() )
  {
    ++bank_size;
  }

  // Photon produced (note that this is not linked to a neuton destruction)
  TEST_EQUALITY_CONST( bank.size(), bank_size );     
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

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

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
// end tstNuclearReaction.cpp
//---------------------------------------------------------------------------//
