//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellPhotoelectricPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Subshell photoelectric photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_SubshellPhotoelectricPhotoatomicReaction.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotoatomicReaction> ace_k_photoelectric_reaction;
Teuchos::RCP<MonteCarlo::PhotoatomicReaction> ace_l1_photoelectric_reaction;

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
// Check that the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction, getSubshell_ace )
{
  Teuchos::RCP<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> > true_reaction = 
    Teuchos::rcp_dynamic_cast<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> >( ace_k_photoelectric_reaction );

  TEST_EQUALITY_CONST( true_reaction->getSubshell(), Data::K_SUBSHELL );

  true_reaction =  
    Teuchos::rcp_dynamic_cast<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> >( ace_l1_photoelectric_reaction );

  TEST_EQUALITY_CONST( true_reaction->getSubshell(), Data::L1_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energy can be returned
TEUCHOS_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getSubshellBindingEnergy )
{
  Teuchos::RCP<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> > true_reaction = 
    Teuchos::rcp_dynamic_cast<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> >( ace_k_photoelectric_reaction );

  TEST_EQUALITY_CONST( true_reaction->getSubshellBindingEnergy(), 
		       8.829000000000E-02 );

  true_reaction =  
    Teuchos::rcp_dynamic_cast<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> >( ace_l1_photoelectric_reaction );

  TEST_EQUALITY_CONST( true_reaction->getSubshellBindingEnergy(), 
		       1.584700000000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getReactionType_ace )
{
  TEST_EQUALITY_CONST( 
		   ace_k_photoelectric_reaction->getReactionType(),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST(
		  ace_l1_photoelectric_reaction->getReactionType(),
		  MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_k_photoelectric_reaction->getThresholdEnergy(),
		       exp( -2.427128314806E+00 ) );

  TEST_EQUALITY_CONST( ace_l1_photoelectric_reaction->getThresholdEnergy(),
		       exp( -4.144774439987E+00 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST(
	       ace_k_photoelectric_reaction->getNumberOfEmittedPhotons( 1e-3 ),
	       0u );

  TEST_EQUALITY_CONST(
	       ace_k_photoelectric_reaction->getNumberOfEmittedPhotons( 20.0 ),
	       0u );

  TEST_EQUALITY_CONST( 
	      ace_l1_photoelectric_reaction->getNumberOfEmittedPhotons( 1e-3 ),
	      0u );

  TEST_EQUALITY_CONST( 
	      ace_l1_photoelectric_reaction->getNumberOfEmittedPhotons( 20.0 ),
	      0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getCrossSection_ace )
{
  // K subshell
  double cross_section = 
    ace_k_photoelectric_reaction->getCrossSection( exp(-1.381551055796E+01) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = 
    ace_k_photoelectric_reaction->getCrossSection( exp( -2.427128314806E+00 ));

  TEST_FLOATING_EQUALITY( cross_section, exp( 7.578565567350E+00 ), 1e-12 );

  cross_section = 
    ace_k_photoelectric_reaction->getCrossSection( exp(-2.414302996307E+00) );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( 7.547192730643E+00 ), 1e-12 );

  cross_section = 
    ace_k_photoelectric_reaction->getCrossSection( exp(1.151292546497E+01) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.135387253512E+01 ), 1e-12 );

  // L1 subshell
  cross_section = 
    ace_l1_photoelectric_reaction->getCrossSection( exp(-1.381551055796E+01) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = 
    ace_l1_photoelectric_reaction->getCrossSection( exp(-4.144774439987E+00) );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( 8.861685600842E+00 ), 1e-12 );

  cross_section = 
    ace_l1_photoelectric_reaction->getCrossSection( exp(-4.136738416467E+00) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 8.847146529853E+00 ), 1e-12 );

  cross_section = 
    ace_l1_photoelectric_reaction->getCrossSection( exp(1.151292546497E+01) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.347975286228E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the reaction can be modeled
TEUCHOS_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction, react_ace )
{
  Teuchos::RCP<MonteCarlo::PhotonState> photon(new MonteCarlo::PhotonState(0));
 
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setEnergy( 2.0 );

  MonteCarlo::ParticleBank bank;
  
  Data::SubshellType subshell;

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[0] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_k_photoelectric_reaction->react( *photon, bank, subshell );

  TEST_ASSERT( photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
			  2.0 - 8.829000000000E-02,
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getYDirection(), -1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-15 );

  bank.pop();

  Utility::RandomNumberGenerator::unsetFakeStream();

  photon.reset( new MonteCarlo::PhotonState(0) );
 
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setEnergy( 2.0 );

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_l1_photoelectric_reaction->react( *photon, bank, subshell );

  TEST_ASSERT( photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
			  2.0 - 1.584700000000E-02,
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getYDirection(), -1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-15 );

  bank.pop();

  Utility::RandomNumberGenerator::unsetFakeStream();
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
   
  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_order = 
    xss_data_extractor->extractSubshellENDFDesignators();

  Teuchos::ArrayView<const double> binding_energies = 
    xss_data_extractor->extractSubshellBindingEnergies();

  // Extract the energy grid and cross sections
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractPhotonEnergyGrid() );
  
  unsigned energy_grid_points = energy_grid.size();

  Teuchos::ArrayView<const double> subshell_cross_sections = 
    xss_data_extractor->extractSPHELBlock();

  Teuchos::ArrayView<const double> raw_k_cross_section = 
    subshell_cross_sections( 0, energy_grid_points );

  Teuchos::ArrayView<const double>::iterator start = 
    std::find_if( raw_k_cross_section.begin(),
		  raw_k_cross_section.end(),
		  notEqualZero );

  Teuchos::ArrayRCP<double> k_cross_section;
  k_cross_section.assign( start, raw_k_cross_section.end() );

  unsigned k_threshold_index = 
    energy_grid.size() - k_cross_section.size();
 
  Teuchos::ArrayView<const double> raw_l1_cross_section = 
    subshell_cross_sections( energy_grid_points, energy_grid_points );

  start = std::find_if( raw_l1_cross_section.begin(),
			raw_l1_cross_section.end(),
			notEqualZero );

  Teuchos::ArrayRCP<double> l1_cross_section;
  l1_cross_section.assign( start, raw_l1_cross_section.end() );

  unsigned l1_threshold_index =
    energy_grid.size() - l1_cross_section.size();

  // Create the reactions
  ace_k_photoelectric_reaction.reset(
    new MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog>(
	  energy_grid,
	  k_cross_section,
	  k_threshold_index,
	  Data::convertENDFDesignatorToSubshellEnum( subshell_order[0] ),
	  binding_energies[0] ) );

  ace_l1_photoelectric_reaction.reset(
    new MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog>(
	  energy_grid,
	  l1_cross_section,
	  l1_threshold_index,
	  Data::convertENDFDesignatorToSubshellEnum( subshell_order[1] ),
	  binding_energies[1] ) );

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
// end tstSubshellPhotoelectricPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
