//---------------------------------------------------------------------------//
//!
//! \file   tstPairProductionPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Pair production photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PairProductionPhotoatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotoatomicDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotoatomicReaction> ace_basic_pp_reaction;

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
TEUCHOS_UNIT_TEST( PairProductionPhotoatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_basic_pp_reaction->getReactionType(),
		       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( PairProductionPhotoatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_basic_pp_reaction->getThresholdEnergy(),
		       exp( 2.17614917816E-02 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( PairProductionPhotoatomicReaction,
		   getNumberOfEmittedPhotons_ace_basic )
{
  TEST_EQUALITY_CONST(ace_basic_pp_reaction->getNumberOfEmittedPhotons( 1e-4 ),
		      0u);

  TEST_EQUALITY_CONST( ace_basic_pp_reaction->getNumberOfEmittedPhotons(
                       ace_basic_pp_reaction->getThresholdEnergy() ),
		       2u );

  TEST_EQUALITY_CONST( ace_basic_pp_reaction->getNumberOfEmittedPhotons( 20.0 ), 2u);
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( PairProductionPhotoatomicReaction,
                   getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST(
              ace_basic_pp_reaction->getNumberOfEmittedElectrons( 1e-4 ), 0u );

  TEST_EQUALITY_CONST( ace_basic_pp_reaction->getNumberOfEmittedElectrons(
                         ace_basic_pp_reaction->getThresholdEnergy() ),
		       1u );

  TEST_EQUALITY_CONST(
              ace_basic_pp_reaction->getNumberOfEmittedElectrons( 20.0 ), 1u );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section can be returned
TEUCHOS_UNIT_TEST( PairProductionPhotoatomicReaction, getCrossSection_ace )
{
  double cross_section = ace_basic_pp_reaction->getCrossSection(
                                 ace_basic_pp_reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, exp( -3.84621780013E+01 ), 1e-12 );

  cross_section =
    ace_basic_pp_reaction->getCrossSection( exp( 5.98672834901E+00 ));

  TEST_FLOATING_EQUALITY( cross_section, exp( 3.62139611703E+00 ), 1e-12 );

  cross_section =
    ace_basic_pp_reaction->getCrossSection( exp( 1.15129254650E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 3.71803283438E+00 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pair production reaction can be simulated
TEUCHOS_UNIT_TEST( PairProductionPhotoatomicReaction, react_ace_basic )
{
  Teuchos::RCP<MonteCarlo::PhotonState> photon(new MonteCarlo::PhotonState(0));

  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setEnergy( 2.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType subshell;

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_basic_pp_reaction->react( *photon, bank, subshell );

  TEST_EQUALITY_CONST( photon->getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  UTILITY_TEST_FLOATING_EQUALITY( photon->getZDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon->getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon->getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( photon->getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( photon->getGenerationNumber(), 1 );
  TEST_EQUALITY_CONST( bank.size(), 2 );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY_CONST( bank.top().getZDirection(), 1.0 );
  TEST_EQUALITY_CONST(
	       bank.top().getEnergy(),
	       2.0 - 2*Utility::PhysicalConstants::electron_rest_mass_energy );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( bank.top().getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( bank.top().getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( bank.top().getGenerationNumber(), 1 );
  TEST_EQUALITY_CONST( subshell, Data::UNKNOWN_SUBSHELL );

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
  Teuchos::RCP<Data::XSSPhotoatomicDataExtractor> xss_data_extractor(
                            new Data::XSSPhotoatomicDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  Teuchos::ArrayView<const double> raw_pp_cross_section =
    xss_data_extractor->extractPairProductionCrossSection();

  Teuchos::ArrayView<const double>::iterator start =
    std::find_if( raw_pp_cross_section.begin(),
		  raw_pp_cross_section.end(),
		  notEqualZero );

  Teuchos::ArrayRCP<double> pp_cross_section;
  pp_cross_section.assign( start, raw_pp_cross_section.end() );

  unsigned pp_threshold_index =
    energy_grid.size() - pp_cross_section.size();

  ace_basic_pp_reaction.reset(
    new MonteCarlo::PairProductionPhotoatomicReaction<Utility::LogLog>(
                                                        energy_grid,
						        pp_cross_section,
						        pp_threshold_index,
							false ) );

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
// end tstPairProductionPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
