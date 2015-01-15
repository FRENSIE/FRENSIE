//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomCore.cpp
//! \author Luke Kersting
//! \brief  ElectroatomCore unit tests
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
#include "MonteCarlo_ElectroatomCore.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectroatomCore> ace_electroatom_core;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( const double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Check that the total reaction can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getTotalReaction )
{
  const MonteCarlo::ElectroatomicReaction& total_reaction =
    ace_electroatom_core->getTotalReaction();

  double cross_section = 
    total_reaction.getCrossSection( 1.214969212306E+01 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.719257539043E+01, 1e-12 );

  cross_section = 
    total_reaction.getCrossSection( 1.214720768866E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.718780625507E+01, 1e-12 );

  cross_section = 
    total_reaction.getCrossSection( 1.151292546497E+01 );

  TEST_FLOATING_EQUALITY(cross_section,
                         1.115947249407E+01 + 3.718032834377E+00,
                         1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getTotalAbsorptionReaction )
{
  const MonteCarlo::ElectroatomicReaction& absorption_reaction = 
    ace_electroatom_core->getTotalAbsorptionReaction();

  double cross_section = absorption_reaction.getCrossSection(  
                                             1.381551055796E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section = absorption_reaction.getCrossSection( 1.214969212306E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.719257539043E+01, 1e-12 );

  cross_section = absorption_reaction.getCrossSection( 1.214720768866E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.718780625507E+01, 1e-12 );

  cross_section = absorption_reaction.getCrossSection( 1.151292546497E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.115947249407E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getScatteringReactions )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& scattering_reactions = 
    ace_electroatom_core->getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );

  const MonteCarlo::ElectroatomicReaction& ae_reaction = 
    *(scattering_reactions.find(MonteCarlo::ATOMIC_EXCITAION_ELECTROATOMIC_REACTION)->second);

  const MonteCarlo::ElectroatomicReaction& b_reaction = 
    *(scattering_reactions.find(MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION)->second);

  double cross_section = 
    ae_reaction.getCrossSection( 1.381551055796E+01 ) +
     b_reaction.getCrossSection( 1.381551055796E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
  
  cross_section = ae_reaction.getCrossSection( 2.480967890857E-02 ) +
                   b_reaction.getCrossSection( 2.480967890857E-02 );

  TEST_FLOATING_EQUALITY( cross_section, 1.431923975437E+01, 1e-12 );

  cross_section = ae_reaction.getCrossSection( 1.151292546497E+01 ) +
                   b_reaction.getCrossSection( 1.151292546497E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 3.718032834377E+00 , 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getAbsorptionReactions )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& absorption_reactions =
    ace_electroatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 1 );

  const MonteCarlo::ElectroatomicReaction& va_reaction = 
    *(absorption_reactions.find(MonteCarlo::VOID_ABSORPTION_ELECTROATOMIC_REACTION)->second);

  double cross_section = 
    va_reaction.getCrossSection( 1.381551055796E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section = va_reaction.getCrossSection( 1.214969212306E+01 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.719257539043E+01, 1e-12 );

  cross_section = va_reaction.getCrossSection( 1.214720768866E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.718780625507E+01, 1e-12 );

  cross_section = va_reaction.getCrossSection( 1.151292546497E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.115947249407E+01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that miscellaneous reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getMiscReactions )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& misc_reactions = 
    ace_electroatom_core->getMiscReactions();

  TEST_EQUALITY_CONST( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic relaxation model can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getAtomicRelaxationModel )
{
  MonteCarlo::SubshellType vacancy = MonteCarlo::K_SUBSHELL;

  MonteCarlo::ElectronState electron( 0u );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setPosition( 0.0, 0.0, 0.0 );

  MonteCarlo::ParticleBank bank;

  const MonteCarlo::AtomicRelaxationModel& relaxation_model = 
    ace_electroatom_core->getAtomicRelaxationModel();

  relaxation_model.relaxAtom( vacancy, electron, bank );

  TEST_EQUALITY_CONST( bank.size(), 0u );  
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
  
  {
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

    // Create the pair production and photoelectric effect cross sections
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );
        
    Teuchos::ArrayView<const double> raw_pe_cross_section = 
      xss_data_extractor->extractElectroelectricCrossSection();
    
    Teuchos::ArrayView<const double>::iterator start = 
      std::find_if( raw_pe_cross_section.begin(),
		    raw_pe_cross_section.end(),
		    notEqualZero );

    Teuchos::ArrayRCP<double> pe_cross_section;
    pe_cross_section.assign( start, raw_pe_cross_section.end() );

    unsigned pe_threshold_index = 
      energy_grid.size() - pe_cross_section.size();

    Teuchos::RCP<MonteCarlo::ElectroatomicReaction> pe_reaction(
	    new MonteCarlo::ElectroelectricElectroatomicReaction<Utility::LogLog>(
						    energy_grid,
						    pe_cross_section,
						    pe_threshold_index ) );
    
    Teuchos::ArrayView<const double> raw_pp_cross_section = 
      xss_data_extractor->extractPairProductionCrossSection();
    
    start = std::find_if( raw_pp_cross_section.begin(),
		    raw_pp_cross_section.end(),
		    notEqualZero );
  
    Teuchos::ArrayRCP<double> pp_cross_section;
    pp_cross_section.assign( start, raw_pp_cross_section.end() );
    
    unsigned pp_threshold_index = 
      energy_grid.size() - pp_cross_section.size();
    
    Teuchos::RCP<MonteCarlo::ElectroatomicReaction> pp_reaction(
	    new MonteCarlo::PairProductionElectroatomicReaction<Utility::LogLog>(
							energy_grid,
							pp_cross_section,
							pp_threshold_index ) );

    // Create the reaction maps
    MonteCarlo::ElectroatomCore::ReactionMap scattering_reactions, 
      absorption_reactions;
    
    scattering_reactions[pp_reaction->getReactionType()] = pp_reaction;
    
    absorption_reactions[pe_reaction->getReactionType()] = pe_reaction;
    
    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
				   new MonteCarlo::VoidAtomicRelaxationModel );

    // Create a test electroatom core
    ace_electroatom_core.reset(
			  new MonteCarlo::ElectroatomCore( energy_grid,
							 scattering_reactions,
							 absorption_reactions,
							 relaxation_model,
							 true,
							 Utility::LogLog() ) );

    // Run the unit tests
    Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  }

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}
							   

//---------------------------------------------------------------------------//
// end tstElectroatomCore.cpp
//---------------------------------------------------------------------------//
