//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellIncoherentPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Subshell incoherent photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotoatomicReaction> 
  basic_subshell_incoherent_reaction;

Teuchos::RCP<MonteCarlo::PhotoatomicReaction>
  detailed_subshell_incoherent_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, 
		   getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST(
     basic_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 1e-3 ),
     0u );

  TEST_EQUALITY_CONST(
      basic_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 8.82e-2 ),
      0u );

  TEST_EQUALITY_CONST(
      basic_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 8.83e-2 ),
      1u );

  TEST_EQUALITY_CONST(
	 basic_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 20.0 ),
	 1u );

  TEST_EQUALITY_CONST(
  detailed_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 1e-3 ),
  0u );

  TEST_EQUALITY_CONST(
   detailed_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 8.82e-2 ),
   0u );

  TEST_EQUALITY_CONST(
   detailed_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 8.83e-2 ),
   1u );

  TEST_EQUALITY_CONST(
      detailed_subshell_incoherent_reaction->getNumberOfEmittedPhotons( 20.0 ),
      1u );
}

//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( basic_subshell_incoherent_reaction->getReactionType(),
		       MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION);
  
  TEST_EQUALITY_CONST(detailed_subshell_incoherent_reaction->getReactionType(),
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION);
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, getThresholdEnergy )
{
  TEST_FLOATING_EQUALITY(
		      basic_subshell_incoherent_reaction->getThresholdEnergy(),
		      8.82900086220703151e-02,
		      1e-15 );
  
  TEST_FLOATING_EQUALITY(
		   detailed_subshell_incoherent_reaction->getThresholdEnergy(),
		   8.82900086220703151e-02,
		   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, getCrossSection )
{
  double cross_section = 
    basic_subshell_incoherent_reaction->getCrossSection( 1e-3 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = 
    basic_subshell_incoherent_reaction->getCrossSection( 8.82e-2 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = 
    basic_subshell_incoherent_reaction->getCrossSection( 8.82899999999999935e-02 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = 
    basic_subshell_incoherent_reaction->getCrossSection( 8.82900086220703151e-02 );

  TEST_FLOATING_EQUALITY( cross_section, 5.25553220583787745e-09, 1e-15 );

  cross_section = 
    basic_subshell_incoherent_reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 6.03100615156834802e-02, 1e-15 );

  cross_section = 
    detailed_subshell_incoherent_reaction->getCrossSection( 1e-3 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = 
    detailed_subshell_incoherent_reaction->getCrossSection( 8.82e-2 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = 
    detailed_subshell_incoherent_reaction->getCrossSection( 8.82899999999999935e-02 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = 
    detailed_subshell_incoherent_reaction->getCrossSection( 8.82900086220703151e-02 );

  TEST_FLOATING_EQUALITY( cross_section, 5.25553220583787745e-09, 1e-15 );

  cross_section = 
    detailed_subshell_incoherent_reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 6.03100615156834802e-02, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the interaction subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, getSubshell )
{
  typedef MonteCarlo::SubshellIncoherentPhotoatomicReaction<Utility::LinLin,false> Reaction;
  
  Teuchos::RCP<Reaction> derived_basic_reaction = 
    Teuchos::rcp_dynamic_cast<Reaction>( basic_subshell_incoherent_reaction );

  TEST_EQUALITY_CONST( derived_basic_reaction->getSubshell(),
		       MonteCarlo::K_SUBSHELL );

  Teuchos::RCP<Reaction> derived_detailed_reaction = 
    Teuchos::rcp_dynamic_cast<Reaction>(detailed_subshell_incoherent_reaction);

  TEST_EQUALITY_CONST( derived_basic_reaction->getSubshell(),
		       MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, 
		   getSubshellBindingEnergy )
{
  typedef MonteCarlo::SubshellIncoherentPhotoatomicReaction<Utility::LinLin,false> Reaction;
  
  Teuchos::RCP<Reaction> derived_basic_reaction = 
    Teuchos::rcp_dynamic_cast<Reaction>( basic_subshell_incoherent_reaction );

  TEST_EQUALITY_CONST( derived_basic_reaction->getSubshellBindingEnergy(),
		       8.82899999999999935e-02 );

  Teuchos::RCP<Reaction> derived_detailed_reaction = 
    Teuchos::rcp_dynamic_cast<Reaction>(detailed_subshell_incoherent_reaction);

  TEST_EQUALITY_CONST( derived_basic_reaction->getSubshellBindingEnergy(),
		       8.82899999999999935e-02 );
}

//---------------------------------------------------------------------------//
// Check that the basic incoherent reaction can be simulated
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, react_basic )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_subshell_incoherent_reaction->react( photon,
					     bank,
					     shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
			  19.50173181484825,
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 
			  0.9996898054103247, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 
			  -0.024905681252821114, 
			  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the detailed incoherent reaction can be simulated
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotoatomicReaction, react_detailed )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // select pz = 0.0
  fake_stream[4] = 0.0; // azimuthal_angle = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  detailed_subshell_incoherent_reaction->react( photon,
						bank,
						shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
			  19.50173181484825,
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 
			  0.9996898054103247, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 
			  0.024905681252821114, 
			  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer 
      data_container( test_native_file_name );

    // Extract the photon energy grid
    Teuchos::ArrayRCP<double> photon_energy_grid;
    photon_energy_grid.assign( data_container.getPhotonEnergyGrid().begin(),
			       data_container.getPhotonEnergyGrid().end() );

    // Extract the subshell impulse approx incoherent cross section
    Teuchos::ArrayRCP<double> subshell_incoherent_cs;
    subshell_incoherent_cs.assign( 
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).begin(),
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).end() );

    unsigned threshold_index = 
      data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1);
    
    // Extract the Compton profile and occupation number for the first subshell
    const std::vector<double>& compton_profile_grid_s1 = 
      data_container.getComptonProfileMomentumGrid( 1 );
    
    const std::vector<double>& compton_profile_s1 = 
      data_container.getComptonProfile( 1 );
    
    const std::vector<double>& occupation_number_grid_s1 = 
      data_container.getOccupationNumberMomentumGrid( 1 );
    
    const std::vector<double>& occupation_number_s1 = 
      data_container.getOccupationNumber( 1 );
    
    // Create the Compton profile and occupation number distributions
    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum> > raw_compton_profile(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
                                                       compton_profile_grid_s1,
						       compton_profile_s1 ) );

    std::shared_ptr<MonteCarlo::ComptonProfile> compton_profile_s1_dist( 
           new MonteCarlo::StandardComptonProfile<Utility::Units::MeCMomentum>(
                                                       raw_compton_profile ) );

    Teuchos::RCP<const Utility::OneDDistribution> occupation_number_s1_dist(
			    new Utility::TabularDistribution<Utility::LinLin>(
						    occupation_number_grid_s1,
						    occupation_number_s1 ) );

    // Create the subshell incoherent distributions
    Teuchos::RCP<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
      basic_distribution( new MonteCarlo::SubshellIncoherentPhotonScatteringDistribution( 
			  MonteCarlo::convertENDFDesignatorToSubshellEnum( 1 ),
			  data_container.getSubshellOccupancy( 1 ),
			  data_container.getSubshellBindingEnergy( 1 ),
			  occupation_number_s1_dist,
			  3.0 ) );

    std::shared_ptr<const MonteCarlo::SubshellDopplerBroadenedPhotonEnergyDistribution>
      doppler_dist( new MonteCarlo::StandardSubshellDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::FullComptonProfilePolicy>(
		    MonteCarlo::convertENDFDesignatorToSubshellEnum( 1 ),
		    data_container.getSubshellOccupancy( 1 ),
		    data_container.getSubshellBindingEnergy( 1 ),
		    compton_profile_s1_dist ) );

    Teuchos::RCP<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
      detailed_distribution( new MonteCarlo::DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution(
						     doppler_dist,
						     occupation_number_s1_dist,
						     3.0 ) );

    // Create the subshell incoherent reaction
    basic_subshell_incoherent_reaction.reset(
         new MonteCarlo::SubshellIncoherentPhotoatomicReaction<Utility::LinLin,false>(
			                                photon_energy_grid,
			                                subshell_incoherent_cs,
							threshold_index,
							basic_distribution ) );

    detailed_subshell_incoherent_reaction.reset(
	 new MonteCarlo::SubshellIncoherentPhotoatomicReaction<Utility::LinLin,false>(
			  photon_energy_grid,
			  subshell_incoherent_cs,
			  threshold_index,
			  detailed_distribution ) );
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
// end tstSubshellIncoherentPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
