//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonuclearReaction.cpp
//! \author Ryan Pease
//! \brief  Photonuclear reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReaction.hpp"
//#include "MonteCarlo_PhotonuclearReaction_def.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string h2_ace_file_name;
std::string c12_ace_file_name;
std::string h2_ace_table_name;
std::string c12_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> h2_ace_file_handler;
Teuchos::RCP<Data::XSSPhotonuclearDataExtractor> h2_xss_data_extractor;
Teuchos::RCP<MonteCarlo::PhotonuclearReaction<MonteCarlo::PhotonState> > h2_photonuclear_reaction;

Teuchos::RCP<Data::ACEFileHandler> c12_ace_file_handler;
Teuchos::RCP<Data::XSSPhotonuclearDataExtractor> c12_xss_data_extractor;
Teuchos::RCP<MonteCarlo::PhotonuclearReaction<MonteCarlo::NeutronState> > c12_photonuclear_reaction;

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename OutgoingParticleType>
class TestPhotonuclearReaction : public MonteCarlo::PhotonuclearReaction<OutgoingParticleType>
{
public:
  TestPhotonuclearReaction( 
		   const MonteCarlo::PhotonuclearReactionType reaction_type,
		   const double q_value,
		   const unsigned threshold_energy_index,
	           const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::RCP<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::PhotonState,OutgoingParticleType> >& 
		   outgoing_particle_distribution)
    : MonteCarlo::PhotonuclearReaction<OutgoingParticleType>(
			       reaction_type,
      			       q_value,
			       threshold_energy_index,
			       incoming_energy_grid,
			       cross_section,
			       outgoing_particle_distribution)
  { /* ... */ }

  ~TestPhotonuclearReaction()
  { /* ... */ }
  
  unsigned getNumberOfEmittedParticles( const double energy ) const
  { return 0u; }

  void react( MonteCarlo::PhotonState& photon, MonteCarlo::ParticleBank& bank ) const
  { /* ... */ }
};

template<typename OutgoingParticleType>
class TestScatteringDistribution : public MonteCarlo::NuclearScatteringDistribution<MonteCarlo::PhotonState,OutgoingParticleType>
{
public:
  TestScatteringDistribution( const double atomic_weight_ratio )
  : MonteCarlo::NuclearScatteringDistribution<MonteCarlo::PhotonState,OutgoingParticleType>( atomic_weight_ratio )
  { /* ... */ }

  ~TestScatteringDistribution()
  { /* ... */ }

  void scatterParticle( const MonteCarlo::PhotonState& incoming_neutron,
			OutgoingParticleType& outgoing_neutron,
			const double temperature ) const
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeOutGammaReaction()
{
  h2_ace_file_handler.reset(new Data::ACEFileHandler(h2_ace_file_name,
						     h2_ace_table_name,
						     1u ) );
  h2_xss_data_extractor.reset(
   new Data::XSSPhotonuclearDataExtractor( h2_ace_file_handler->getTableNXSArray(),
				      h2_ace_file_handler->getTableJXSArray(),
				      h2_ace_file_handler->getTableXSSArray()));
  Teuchos::RCP<MonteCarlo::NuclearScatteringDistribution
	     <MonteCarlo::PhotonState, MonteCarlo::PhotonState> > 
    h2_scattering_distribution( new TestScatteringDistribution<MonteCarlo::PhotonState>( h2_ace_file_handler->getTableAtomicWeightRatio() ) );
   
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( h2_xss_data_extractor->extractESZBlock() );

  Teuchos::ArrayRCP<double> cross_section;
  cross_section.deepCopy( h2_xss_data_extractor->extractTOTBlock() );

  h2_photonuclear_reaction.reset( new TestPhotonuclearReaction<MonteCarlo::PhotonState>( 
			               MonteCarlo::GAMMA__ANYTHING_REACTION,
				       0,
				       0u,
				       energy_grid,
				       cross_section,
				       h2_scattering_distribution ) );
}

void initializeOutNeutronReaction()
{
   c12_ace_file_handler.reset(new Data::ACEFileHandler( c12_ace_file_name,
							c12_ace_table_name,
  							1u ) );
   c12_xss_data_extractor.reset(
   new Data::XSSPhotonuclearDataExtractor( c12_ace_file_handler->getTableNXSArray(),
  				      c12_ace_file_handler->getTableJXSArray(),
  				      c12_ace_file_handler->getTableXSSArray()));
   
   Teuchos::RCP<MonteCarlo::NuclearScatteringDistribution
	     <MonteCarlo::PhotonState, MonteCarlo::NeutronState> > 
    c12_scattering_distribution( new TestScatteringDistribution<MonteCarlo::NeutronState>( c12_ace_file_handler->getTableAtomicWeightRatio() ) );
   
  Teuchos::ArrayRCP<double> energy_grid;
   energy_grid.deepCopy( c12_xss_data_extractor->extractESZBlock() );
 
  Teuchos::ArrayRCP<double> cross_section;
  cross_section.deepCopy( c12_xss_data_extractor->extractTOTBlock() );

  c12_photonuclear_reaction.reset( new TestPhotonuclearReaction<MonteCarlo::NeutronState>( 
  			       MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION,
  				       0,
  				       0u,
  				       energy_grid,
			               cross_section,
			               c12_scattering_distribution ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the reaction type of an elastic reaction can be returned
TEUCHOS_UNIT_TEST( PhotonuclearReaction_total, getReactionType )
{
    TEST_EQUALITY_CONST( h2_photonuclear_reaction->getReactionType(), 
  		       MonteCarlo::GAMMA__ANYTHING_REACTION );
    TEST_EQUALITY_CONST( c12_photonuclear_reaction->getReactionType(), 
		       MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the Q value can be returned
TEUCHOS_UNIT_TEST( PhotonuclearReaction_total, getQValue )
{
 
  // TEST_EQUALITY_CONST( h2_photonuclear_reaction->getQValue(), 0 );

  //  TEST_EQUALITY_CONST( c12_photonuclear_reaction->getQValue(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( PhotonuclearReaction_total, getThresholdEnergy )
{
  //TEST_EQUALITY_CONST( h2_photonuclear_reaction->getThresholdEnergy(), 
  //		       2.2246 );

// TEST_EQUALITY_CONST( c12_photonuclear_reaction->getThresholdEnergy(),
  //                   7.366593 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( PhotonuclearReaction_total, getCrossSection )
{

  // H-2 CrossSection Test
  double h2_cross_section =
    h2_photonuclear_reaction->getCrossSection( 2.2246 );

  // TEST_EQUALITY_CONST( h2_cross_section , 0 );

  // h2_cross_section = h2_photonuclear_reaction->getCrossSection( 2.4);

  // TEST_EQUALITY_CONST( h2_cross_section , 8.9519e-4 );

  // h2_cross_section = h2_photonuclear_reaction->getCrossSection( 2.6);

  //TEST_EQUALITY_CONST( h2_cross_section , 1.1567e-3 );

  // h2_cross_section = h2_photonuclear_reaction->getCrossSection( 20 );

  //TEST_EQUALITY_CONST( h2_cross_section , 5.9811e-4);

  // h2_cross_section = h2_photonuclear_reaction->getCrossSection( 25 );

  // TEST_EQUALITY_CONST( h2_cross_section , 4.3855e-4 );

  //h2_cross_section = h2_photonuclear_reaction->getCrossSection( 30 );

  // TEST_EQUALITY_CONST( h2_cross_section , 3.549e-4 );


  // C-12 CrossSection Test
  double c12_cross_section = 
    c12_photonuclear_reaction->getCrossSection( 7.336593);

  // TEST_EQUALITY_CONST( c12_cross_section , 0 );

  // c12_cross_section = c12_photonuclear_reaction->getCrossSection( 7.3666 );

  //TEST_EQUALITY_CONST( c12_cross_section , 0 );

  //c12_cross_section = c12_photonuclear_reaction->getCrossSection( 7.5 );

  //TEST_EQUALITY_CONST( c12_cross_section , 1.3019e-6 );

  //c12_cross_section = c12_photonuclear_reaction->getCrossSection( 145 );

  //TEST_EQUALITY_CONST( c12_cross_section , 7.47069582e-4 );

  //c12_cross_section = c12_photonuclear_reaction->getCrossSection( 147.5 );

  //TEST_EQUALITY_CONST( c12_cross_section , 8.7044537e-4 );

  //c12_cross_section = c12_photonuclear_reaction->getCrossSection( 150 );

  //TEST_EQUALITY_CONST( c12_cross_section , 1.0447981e-3 );

}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "h2_ace_file",
  		 &h2_ace_file_name,
  		 "Test basic H2 ACE file name" );

  clp.setOption( "h2_ace_table",
  		 &h2_ace_table_name,
  		 "Test basic H2 ACE table name in basic ACE file" );

  clp.setOption( "c12_ace_file",
  		 &c12_ace_file_name,
  		 "Test basic C12 ACE file name" );

  clp.setOption( "c12_ace_table",
  		 &c12_ace_table_name,
  		 "Test basic ACE table name in basic ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  initializeOutGammaReaction();
  initializeOutNeutronReaction();
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
// end tstPhotonuclearReaction.cpp
//---------------------------------------------------------------------------//
