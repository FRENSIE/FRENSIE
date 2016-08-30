//---------------------------------------------------------------------------//
//!
//! \file   tstStandardElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Standard electroatomic reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_InterpolationPolicy.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroatomicReaction> ace_ae_reaction;
std::shared_ptr<MonteCarlo::ElectroatomicReaction> ace_b_reaction;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename InterpPolicy, bool processed_cross_section>
class TestElectroatomicReaction : public MonteCarlo::StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{
public:
  TestElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const double threshold_energy )
    : MonteCarlo::StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
        incoming_energy_grid, cross_section, threshold_energy )
  { /* ... */ }

  ~TestElectroatomicReaction()
  { /* ... */ }

  unsigned getNumberOfEmittedPhotons( const double energy ) const
  { return 0u; }

  unsigned getNumberOfEmittedElectrons( const double energy ) const
  { return 0u; }

  MonteCarlo::ElectroatomicReactionType getReactionType() const
  { return MonteCarlo::TOTAL_ELECTROATOMIC_REACTION; }

  void react( MonteCarlo::ElectronState& electron,
	      MonteCarlo::ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( StandardElectroatomicReaction, getThresholdEnergy_ace_ae )
{
  TEST_EQUALITY_CONST( ace_ae_reaction->getThresholdEnergy(), 1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( StandardElectroatomicReaction, getThresholdEnergy_ace_b )
{
  TEST_EQUALITY_CONST( ace_b_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( StandardElectroatomicReaction, getCrossSection_ace_ae )
{
  double cross_section =
    ace_ae_reaction->getCrossSection( ace_ae_reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, 8.757550E+06, 1e-12 );

  cross_section = ace_ae_reaction->getCrossSection( 1.300E-04 );

  TEST_FLOATING_EQUALITY( cross_section, 1.086520219780220E+09, 1e-12 );

  cross_section = ace_ae_reaction->getCrossSection( 1.00E+05 );

  TEST_FLOATING_EQUALITY( cross_section, 1.578610E+06, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
// \todo Complete tests using the raw EPDL cross section data
TEUCHOS_UNIT_TEST( StandardElectroatomicReaction, getCrossSection_ace_pe )
{
  double cross_section =
    ace_b_reaction->getCrossSection( ace_b_reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, 4.869800E+03, 1e-12 );

  cross_section = ace_b_reaction->getCrossSection( 6.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.303404261883680E+03, 1e-12 );

  cross_section = ace_b_reaction->getCrossSection( 1.0E+05 );

  TEST_FLOATING_EQUALITY( cross_section, 1.954170E+03, 1e-12 );
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

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

  Teuchos::ArrayView<const double> raw_ae_cross_section =
    xss_data_extractor->extractExcitationCrossSection();

  Teuchos::ArrayView<const double>::iterator start =
    std::find_if( raw_ae_cross_section.begin(),
		  raw_ae_cross_section.end(),
		  notEqualZero );

  Teuchos::ArrayRCP<double> ae_cross_section;
  ae_cross_section.assign( start, raw_ae_cross_section.end() );

  unsigned ae_threshold_index =
    energy_grid.size() - ae_cross_section.size();

  Teuchos::ArrayRCP<double> b_cross_section;
  b_cross_section.deepCopy( xss_data_extractor->extractBremsstrahlungCrossSection() );

  unsigned b_threshold_index =
    energy_grid.size() - b_cross_section.size();

  ace_ae_reaction.reset(
    new TestElectroatomicReaction<Utility::LinLin,false>( energy_grid,
        ae_cross_section,
        ae_threshold_index ) );

  ace_b_reaction.reset(
	new TestElectroatomicReaction<Utility::LinLin,false>( energy_grid,
        b_cross_section,
        b_threshold_index ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

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
// end tstStandardElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
