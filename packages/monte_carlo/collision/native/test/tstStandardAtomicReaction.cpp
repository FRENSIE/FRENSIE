//---------------------------------------------------------------------------//
//!
//! \file   tstStandardAtomicReaction.cpp
//! \author Alex Robinson
//! \brief  Standard photoatomic reaction unit tests.
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
#include "MonteCarlo_StandardAtomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotoatomicDataExtractor.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_InterpolationPolicy.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::AtomicReaction> ace_pp_reaction;
Teuchos::RCP<MonteCarlo::AtomicReaction> ace_pe_reaction;

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
class TestAtomicReaction : public MonteCarlo::StandardAtomicReaction<InterpPolicy,processed_cross_section>
{
public:
  TestAtomicReaction(
        const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
        const Teuchos::ArrayRCP<const double>& cross_section,
        const double threshold_energy )
    : MonteCarlo::StandardAtomicReaction<InterpPolicy,processed_cross_section>( incoming_energy_grid, cross_section, threshold_energy )
  { /* ... */ }

  ~TestAtomicReaction()
  { /* ... */ }

  unsigned getNumberOfEmittedPhotons( const double energy ) const
  { return 1u; }

  unsigned getNumberOfEmittedElectrons( const double energy ) const
  { return 0u; }
};

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( StandardAtomicReaction, getThresholdEnergy_ace_pp )
{
  TEST_EQUALITY_CONST( ace_pp_reaction->getThresholdEnergy(), 
		       exp( 2.17614917816E-02 ) );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( StandardAtomicReaction, getThresholdEnergy_ace_pe )
{
  TEST_EQUALITY_CONST( ace_pe_reaction->getThresholdEnergy(), 
		       exp( -6.90775527898E+00 ) );    
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
// \todo Complete tests using the raw EPDL cross section data
TEUCHOS_UNIT_TEST( StandardAtomicReaction, getCrossSection_ace_pp )
{
  double cross_section = 
    ace_pp_reaction->getCrossSection( ace_pp_reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, exp( -3.84621780013E+01 ), 1e-12 );

  cross_section = ace_pp_reaction->getCrossSection( exp( 5.98672834901E+00 ));

  TEST_FLOATING_EQUALITY( cross_section, exp( 3.62139611703E+00 ), 1e-12 );

  cross_section = ace_pp_reaction->getCrossSection( exp( 1.15129254650E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 3.71803283438E+00 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
// \todo Complete tests using the raw EPDL cross section data
TEUCHOS_UNIT_TEST( StandardAtomicReaction, getCrossSection_ace_pe )
{
  double cross_section = 
    ace_pe_reaction->getCrossSection( ace_pe_reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.43969286532E+01 ), 1e-12 );

  cross_section = ace_pe_reaction->getCrossSection( exp( 5.98672834901E+00 ));

  TEST_FLOATING_EQUALITY( cross_section, exp( -5.62662022605E+00 ), 1e-12 );

  cross_section = ace_pe_reaction->getCrossSection( exp( 1.15129254650E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.11594725061E+01 ), 1e-12 );
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
  
  Teuchos::ArrayRCP<double> pe_cross_section;
  pe_cross_section.deepCopy( xss_data_extractor->extractPhotoelectricCrossSection() );

  ace_pp_reaction.reset(
    new TestAtomicReaction<Utility::LogLog,true>( energy_grid,
						       pp_cross_section,
						       pp_threshold_index ) );

  ace_pe_reaction.reset(
	   new TestAtomicReaction<Utility::LogLog,true>( energy_grid,
							      pe_cross_section,
							      0u ) );

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
// end tstStandardAtomicReaction.cpp
//---------------------------------------------------------------------------//
