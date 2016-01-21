//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Incoherent photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedHybridIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_InverseAtomicMomentumUnit.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
  
//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotoatomicReaction> ace_basic_incoherent_reaction;
Teuchos::RCP<MonteCarlo::PhotoatomicReaction> ace_detailed_incoherent_reaction;

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
TEUCHOS_UNIT_TEST( IncoherentPhotoatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_basic_incoherent_reaction->getReactionType(),
		       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( ace_detailed_incoherent_reaction->getReactionType(),
		       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( IncoherentPhotoatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_basic_incoherent_reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );
  
  TEST_EQUALITY_CONST( ace_detailed_incoherent_reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) ); 
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( IncoherentPhotoatomicReaction, 
		   getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST( 
	      ace_basic_incoherent_reaction->getNumberOfEmittedPhotons( 1e-3 ),
	      1u );

  TEST_EQUALITY_CONST( 
	      ace_basic_incoherent_reaction->getNumberOfEmittedPhotons( 20.0 ),
	      1u );
  
  TEST_EQUALITY_CONST( 
	   ace_detailed_incoherent_reaction->getNumberOfEmittedPhotons( 1e-3 ),
	   1u );
  
  TEST_EQUALITY_CONST( 
	   ace_detailed_incoherent_reaction->getNumberOfEmittedPhotons( 20.0 ),
	   1u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( IncoherentPhotoatomicReaction, getCrossSection_ace )
{
  // Basic reaction
  double cross_section = 
    ace_basic_incoherent_reaction->getCrossSection(exp( -1.381551055796E+01 ));
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = 
    ace_basic_incoherent_reaction->getCrossSection(exp( -1.364234411496E+01 ));

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = 
    ace_basic_incoherent_reaction->getCrossSection(exp( 1.151292546497E+01 ));

  TEST_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Detailed reaction
  cross_section = 
    ace_detailed_incoherent_reaction->getCrossSection(exp( -1.381551055796E+01 ));
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = ace_detailed_incoherent_reaction->getCrossSection(
						  exp( -1.364234411496E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = ace_detailed_incoherent_reaction->getCrossSection(
						   exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the basic incoherent reaction can be simulated
TEUCHOS_UNIT_TEST( IncoherentPhotoatomicReaction, react_ace_basic )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::SubshellType shell_of_interaction;

  ace_basic_incoherent_reaction->react( photon, 
					bank, 
					shell_of_interaction );

  double min_energy = 
    20.0/(1.0+2.0*20.0/Utility::PhysicalConstants::electron_rest_mass_energy );
  
  TEST_ASSERT( photon.getEnergy() >= min_energy );
  TEST_ASSERT( photon.getEnergy() <= 20.0 );
  TEST_EQUALITY_CONST( photon.getCollisionNumber(), 1 );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_ASSERT( shell_of_interaction != MonteCarlo::UNKNOWN_SUBSHELL );
  TEST_ASSERT( shell_of_interaction != MonteCarlo::INVALID_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the detailed incoherent reaction can be simulated
TEUCHOS_UNIT_TEST( IncoherentPhotoatomicReaction, react_ace_detailed )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::SubshellType shell_of_interaction;

  ace_detailed_incoherent_reaction->react( photon, 
					   bank, 
					   shell_of_interaction );
  
  TEST_ASSERT( photon.getEnergy() <= 20.0 );
  TEST_EQUALITY_CONST( photon.getCollisionNumber(), 1 );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_ASSERT( shell_of_interaction != MonteCarlo::UNKNOWN_SUBSHELL );
  TEST_ASSERT( shell_of_interaction != MonteCarlo::INVALID_SUBSHELL );
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
  energy_grid.deepCopy( xss_data_extractor->extractPhotonEnergyGrid() );
  
  Teuchos::ArrayView<const double> raw_incoherent_cross_section = 
    xss_data_extractor->extractIncoherentCrossSection();
  
  Teuchos::ArrayView<const double>::iterator start = 
    std::find_if( raw_incoherent_cross_section.begin(),
                  raw_incoherent_cross_section.end(),
                  notEqualZero );

  Teuchos::ArrayRCP<double> incoherent_cross_section;
  incoherent_cross_section.assign( start, raw_incoherent_cross_section.end() );

  unsigned incoherent_threshold_index = 
    energy_grid.size() - incoherent_cross_section.size();

  // Create the scattering function
  Teuchos::ArrayView<const double> jince_block =
    xss_data_extractor->extractJINCEBlock();

  unsigned scatt_func_size = jince_block.size()/2;

  Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ) );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<Utility::Units::InverseAngstrom,void> > raw_scattering_function(
     new Utility::UnitAwareTabularDistribution<Utility::LogLog,Utility::Units::InverseAngstrom,void>( 
			   recoil_momentum,
			   jince_block( scatt_func_size, scatt_func_size ) ) );

  std::shared_ptr<MonteCarlo::ScatteringFunction> scattering_function(
      new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseAngstrom>( raw_scattering_function ) );

  // Create the subshell order array
  Teuchos::ArrayView<const double> subshell_endf_des = 
    xss_data_extractor->extractSubshellENDFDesignators();

  Teuchos::Array<MonteCarlo::SubshellType> subshell_order( 
						    subshell_endf_des.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = MonteCarlo::convertENDFDesignatorToSubshellEnum( 
					      (unsigned)subshell_endf_des[i] );
  }

  // Create the Compton profile subshell converter
  std::shared_ptr<MonteCarlo::ComptonProfileSubshellConverter> converter;
  
  MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
				   converter,
			           xss_data_extractor->extractAtomicNumber() );
    
  // Create the compton profile distributions
  Teuchos::ArrayView<const double> lswd_block = 
    xss_data_extractor->extractLSWDBlock();

  Teuchos::ArrayView<const double> swd_block = 
    xss_data_extractor->extractSWDBlock();

  MonteCarlo::DopplerBroadenedPhotonEnergyDistribution::ElectronMomentumDistArray
    compton_profiles( lswd_block.size() );
  
  for( unsigned shell = 0; shell < lswd_block.size(); ++shell )
  {
    unsigned shell_index = lswd_block[shell]; // ignore interp parameter

    unsigned num_mom_vals = swd_block[shell_index];

    Teuchos::Array<double> half_momentum_grid( 
				  swd_block( shell_index + 1, num_mom_vals ) );

    Teuchos::Array<double> half_profile(
		   swd_block( shell_index + 1 + num_mom_vals, num_mom_vals ) );

    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> > raw_compton_profile(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>(
                                                       half_momentum_grid,
                                                       half_profile ) );

    compton_profiles[shell].reset( 
       new MonteCarlo::StandardComptonProfile<Utility::Units::AtomicMomentum>( 
                                                       raw_compton_profile ) );
  }

  // Create the incoherent scattering distributions
  Teuchos::RCP<const MonteCarlo::IncoherentPhotonScatteringDistribution>
    basic_distribution( new MonteCarlo::DetailedWHIncoherentPhotonScatteringDistribution(
			  scattering_function,
			  xss_data_extractor->extractSubshellOccupancies(),
			  subshell_order ) );

  std::shared_ptr<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution>
    doppler_dist( new MonteCarlo::DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::DoubledHalfComptonProfilePolicy>(
			  xss_data_extractor->extractSubshellOccupancies(),
			  subshell_order,
			  xss_data_extractor->extractLBEPSBlock(),
			  xss_data_extractor->extractLNEPSBlock(),
                          converter,
			  compton_profiles ) );

  Teuchos::RCP<const MonteCarlo::IncoherentPhotonScatteringDistribution>
    detailed_distribution( new MonteCarlo::DopplerBroadenedHybridIncoherentPhotonScatteringDistribution(
			  scattering_function,
			  doppler_dist,
			  3.0 ) );

  // Create the reactions
  ace_basic_incoherent_reaction.reset(
		new MonteCarlo::IncoherentPhotoatomicReaction<Utility::LogLog>(
						    energy_grid,
						    incoherent_cross_section,
						    incoherent_threshold_index,
						    basic_distribution ) );

  ace_detailed_incoherent_reaction.reset(
		new MonteCarlo::IncoherentPhotoatomicReaction<Utility::LogLog>(
			  energy_grid,
			  incoherent_cross_section,
			  incoherent_threshold_index,
			  detailed_distribution ) );

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
// end tstIncoherentPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
