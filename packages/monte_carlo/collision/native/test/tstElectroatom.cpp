//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatom.cpp
//! \author Luke Kersting
//! \brief  Electroatom unit tests
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
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::Electroatom> ace_electroatom;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
TEUCHOS_UNIT_TEST( Electroatom, getScatteringReactionTypes )
{
  const boost::unordered_set<MonteCarlo::ElectroatomicReactionType>&
    scattering_types = MonteCarlo::Electroatom::getScatteringReactionTypes();

  TEST_ASSERT( scattering_types.count( 
		      MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		 MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	        MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	        MonteCarlo::M2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::M4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::M5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::N1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::N2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::N3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::N4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	        MonteCarlo::N5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::N6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::N7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	        MonteCarlo::O1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	        MonteCarlo::O2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	        MonteCarlo::O3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::O4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::O5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::O6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::O7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::O8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::O9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::P1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::P2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::P4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::P5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::P6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::P7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::P8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
		MonteCarlo::P9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	       MonteCarlo::P10_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	       MonteCarlo::P11_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	       MonteCarlo::Q1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	       MonteCarlo::Q2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	       MonteCarlo::Q3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );

  TEST_ASSERT( scattering_types.count(
	       MonteCarlo::ELASTIC_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	       MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
	       MonteCarlo::INELASTIC_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atom name can be returned
TEUCHOS_UNIT_TEST( Electroatom, getAtomName_ace )
{
  TEST_EQUALITY_CONST( ace_electroatom->getAtomName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom nuclide name can be returned
TEUCHOS_UNIT_TEST( Electroatom, getNuclideName_ace )
{
  TEST_EQUALITY_CONST( ace_electroatom->getNuclideName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic number can be returned
TEUCHOS_UNIT_TEST( Electroatom, getAtomicNumber_ace )
{
  TEST_EQUALITY_CONST( ace_electroatom->getAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic mass number can be returned
TEUCHOS_UNIT_TEST( Electroatom, getAtomicMassNumber_ace )
{
  TEST_EQUALITY_CONST( ace_electroatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom isomer number can be returned
TEUCHOS_UNIT_TEST( Electroatom, getIsomerNumber_ace )
{
  TEST_EQUALITY_CONST( ace_electroatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic weight can be returned
TEUCHOS_UNIT_TEST( Electroatom, getAtomicWeight_ace )
{
  TEST_FLOATING_EQUALITY( ace_electroatom->getAtomicWeight(), 
                          207.1999470456033,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom temperature can be returned
TEUCHOS_UNIT_TEST( Electroatom, getTemperature_ace )
{
  TEST_EQUALITY_CONST( ace_electroatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
TEUCHOS_UNIT_TEST( Electroatom, getTotalCrossSection_ace )
{
  double cross_section = 
    ace_electroatom->getTotalCrossSection( 2.000000000000E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 
                          9.258661418255E+03 + 1.965170000000E+08,
                          1e-12 );
  cross_section = 
    ace_electroatom->getTotalCrossSection( 4.000000000000E-04 );
  
  TEST_FLOATING_EQUALITY( cross_section, 
                          8.914234996439E+03 + 6.226820000000E+08,
                          1e-12 );
  cross_section = 
    ace_electroatom->getTotalCrossSection( 9.000000000000E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 
                          7.249970966838E+03 + 1.160420000000E+09,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
TEUCHOS_UNIT_TEST( Electroatom, getAbsorptionCrossSection_ace )
{
  double cross_section = 
    ace_electroatom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );
    
  cross_section =
    ace_electroatom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = 
    ace_electroatom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = 
    ace_electroatom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( Electroatom, getSurvivalProbability_ace )
{
  double survival_prob = 
    ace_electroatom->getSurvivalProbability( 2.000000000000E-03 );
  
   TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob = 
    ace_electroatom->getSurvivalProbability( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob = 
    ace_electroatom->getSurvivalProbability( 9.000000000000E-05 );
  
   TEST_EQUALITY_CONST( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
TEUCHOS_UNIT_TEST( Electroatom, getReactionCrossSection )
{
  // Total Electroionization
  double cross_section = ace_electroatom->getReactionCrossSection( 
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );
    
  cross_section = ace_electroatom->getReactionCrossSection( 
                   2.000000000000E-03,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection( 
                   4.000000000000E-04,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection( 
                   9.000000000000E-05,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Atomic Excitation
  cross_section = ace_electroatom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );
  
  cross_section = ace_electroatom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  // Bremsstrahlung
  cross_section = ace_electroatom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    4.000000000000E-04,
				 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );
  
  cross_section = ace_electroatom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  // Hard Elastic
  cross_section = ace_electroatom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ELASTIC_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );
  
  cross_section = ace_electroatom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Total
  cross_section = ace_electroatom->getReactionCrossSection( 
                    2.000000000000E-03,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 
                          9.258661418255E+03 + 1.965170000000E+08,
                          1e-12 );

  cross_section = ace_electroatom->getReactionCrossSection( 
                    4.000000000000E-04,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 
                          8.914234996439E+03 + 6.226820000000E+08,
                          1e-12 );

  cross_section = ace_electroatom->getReactionCrossSection( 
                    9.000000000000E-05,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 
                          7.249970966838E+03 + 1.160420000000E+09,
                          1e-12 );

  // Absorption
  cross_section = ace_electroatom->getReactionCrossSection( 
                    1.000000000000E-02,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
    
  cross_section =ace_electroatom->getReactionCrossSection( 
                    2.000000000000E-03,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection( 
                    4.000000000000E-04,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection( 
                    9.000000000000E-05,
			   MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that an analogue collision with the atom can be modeled
TEUCHOS_UNIT_TEST( Electroatom, collideAnalogue )
{
  Teuchos::RCP<MonteCarlo::ElectronState> electron( 
					    new MonteCarlo::ElectronState( 0 ) );
  electron->setEnergy( 20 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // choose scattering rxn

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_electroatom->collideAnalogue( *electron, bank );
  
  TEST_ASSERT( !electron->isGone() );
  TEST_EQUALITY_CONST( electron->getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a survival biased collision with the atom can be modeled
TEUCHOS_UNIT_TEST( Electroatom, collideSurvivalBias )
{  
  Teuchos::RCP<MonteCarlo::ElectronState> electron( 
					    new MonteCarlo::ElectronState( 0 ) );
  electron->setEnergy( 1 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );
  
  MonteCarlo::ParticleBank bank;

  ace_electroatom->collideSurvivalBias( *electron, bank );
  
  TEST_ASSERT( !electron->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 0 );
  
  // reset the particle
  electron.reset( new MonteCarlo::ElectronState( 0 ) );
  electron->setEnergy( 1 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  ace_electroatom->collideSurvivalBias( *electron, bank );

  TEST_ASSERT( !electron->isGone() );
  TEST_FLOATING_EQUALITY( electron->getWeight(), 1.0, 1e-15 );
  TEST_EQUALITY_CONST( bank.size(), 0 );
  TEST_FLOATING_EQUALITY( bank.top()->getWeight(), 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a electroatom can be constructed from a core
TEUCHOS_UNIT_TEST( Electroatom, core_constructor )
{
  MonteCarlo::Electroatom electroatom_copy( ace_electroatom->getAtomName(),
  					ace_electroatom->getAtomicNumber(),
  					ace_electroatom->getAtomicWeight(),
  					ace_electroatom->getCore() );

  TEST_EQUALITY( electroatom_copy.getAtomName(), 
		 ace_electroatom->getAtomName() );
  TEST_EQUALITY( electroatom_copy.getNuclideName(),
		 ace_electroatom->getNuclideName() );
  TEST_EQUALITY( electroatom_copy.getAtomicNumber(), 
		 ace_electroatom->getAtomicNumber() );
  TEST_EQUALITY( electroatom_copy.getAtomicMassNumber(),
		 ace_electroatom->getAtomicMassNumber() );
  TEST_EQUALITY( electroatom_copy.getIsomerNumber(), 
		 ace_electroatom->getIsomerNumber() );
  TEST_EQUALITY( electroatom_copy.getAtomicWeight(), 
		 ace_electroatom->getAtomicWeight() );
  TEST_EQUALITY( electroatom_copy.getTemperature(),
		 ace_electroatom->getTemperature() );

  TEST_EQUALITY( electroatom_copy.getTotalCrossSection( 1e-3 ),
		 ace_electroatom->getTotalCrossSection( 1e-3 ) );
  TEST_EQUALITY( electroatom_copy.getTotalCrossSection( 20.0 ),
		 ace_electroatom->getTotalCrossSection( 20.0 ) );
  TEST_EQUALITY( electroatom_copy.getAbsorptionCrossSection( 1e-3 ),
		 ace_electroatom->getAbsorptionCrossSection( 1e-3 ) );
  TEST_EQUALITY( electroatom_copy.getAbsorptionCrossSection( 20.0 ),
		 ace_electroatom->getAbsorptionCrossSection( 20.0 ) );
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

    // Create the atomic excitation, bremsstrahlung cross sections
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

    // Extract the atomic excitation information data block (EXCIT)
    Teuchos::ArrayView<const double> excit_block(
				      xss_data_extractor->extractEXCITBlock() );
  
    // Extract the number of tabulated energies
    int size = excit_block.size()/2;

    // Extract the energy grid for atomic excitation energy loss
    Teuchos::Array<double> ae_energy_grid(excit_block(0,size));

    // Extract the energy loss for atomic excitation
    Teuchos::Array<double> energy_loss(excit_block(size,size));

    // Create the energy loss distributions
    Teuchos::RCP<Utility::OneDDistribution> ae_energy_loss_distribution;
  
    ae_energy_loss_distribution.reset( 
      new Utility::TabularDistribution<Utility::LinLin>( ae_energy_grid,
		                                                 energy_loss ) );

    Teuchos::RCP<MonteCarlo::ElectroatomicReaction> ae_reaction(
	    new MonteCarlo::AtomicExcitationElectroatomicReaction<Utility::LinLin>(
						    energy_grid,
						    ae_cross_section,
						    ae_threshold_index,
                            ae_energy_loss_distribution ) );
    
    Teuchos::ArrayView<const double> raw_b_cross_section = 
      xss_data_extractor->extractBremsstrahlungCrossSection();
    
    start = std::find_if( raw_b_cross_section.begin(),
		    raw_b_cross_section.end(),
		    notEqualZero );
  
    Teuchos::ArrayRCP<double> b_cross_section;
    b_cross_section.assign( start, raw_b_cross_section.end() );
    
    unsigned b_threshold_index = 
      energy_grid.size() - b_cross_section.size();

    //! \todo Find real bremsstrahlung photon angular distribution
    // Create the tabular angular distribution
    Teuchos::Array<double> b_energy_bins( 3 ); // (MeV)
    b_energy_bins[0] = 1e-7;
    b_energy_bins[1] = 1.0;
    b_energy_bins[2] = 1e5;
 
    Teuchos::Array<double> b_angular_distribution_values( 3 );
    b_angular_distribution_values[0] =  0.0;
    b_angular_distribution_values[1] =  0.5;
    b_angular_distribution_values[2] =  1.0;

    Teuchos::RCP<Utility::OneDDistribution> b_angular_distribution(
	  		    new Utility::TabularDistribution<Utility::LinLin>( 
						b_energy_bins,
						b_angular_distribution_values ) );

    // Extract the elastic scattering information data block (BREMI)
    Teuchos::ArrayView<const double> bremi_block(
	  			      xss_data_extractor->extractBREMIBlock() );

    // Extract the number of tabulated distributions
    int N = bremi_block.size()/3;

    // Extract the electron energy grid for bremsstrahlung energy distributions
    Teuchos::Array<double> b_energy_grid(bremi_block(0,N));

    // Extract the table lengths for bremsstrahlung energy distributions
    Teuchos::Array<double> table_length(bremi_block(N,N));

    // Extract the offsets for bremsstrahlung energy distributions
    Teuchos::Array<double> offset(bremi_block(2*N,N));

    // Extract the bremsstrahlung photon energy distributions block (BREME)
    Teuchos::ArrayView<const double> breme_block = 
      xss_data_extractor->extractBREMEBlock();

    // Create the bremsstrahlung scattering distributions
    Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >
      b_scattering_distribution( N );
  
    for( unsigned n = 0; n < N; ++n )
    {
      b_scattering_distribution[n].first = b_energy_grid[n];

      b_scattering_distribution[n].second.reset( 
	    new Utility::HistogramDistribution(
		   breme_block( offset[n], table_length[n] ),
		   breme_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
           true ) );
    }

    // Set the upper and lower energy cutoff for the photon angular distribution
    double upper_cutoff_energy = 1000;
    double lower_cutoff_energy = 0.001;

    // Create the scattering distributions
    Teuchos::RCP<MonteCarlo::ElectroatomicReaction> b_reaction(
	    new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
							energy_grid,
							b_cross_section,
							b_threshold_index,
                            b_scattering_distribution,
                            b_angular_distribution,
                            lower_cutoff_energy,
                            upper_cutoff_energy ) );

    // Create void absorption reaction
    Teuchos::RCP<MonteCarlo::ElectroatomicReaction> va_reaction(
      new MonteCarlo::VoidAbsorptionElectroatomicReaction() );

    // Create the reaction maps
    MonteCarlo::ElectroatomCore::ReactionMap scattering_reactions, 
      absorption_reactions;
    
    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    absorption_reactions[va_reaction->getReactionType()] = va_reaction;
    
    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
				   new MonteCarlo::VoidAtomicRelaxationModel );

    // Extract the atomic weight
    double atomic_weight = ace_file_handler->getTableAtomicWeightRatio()*
      Utility::PhysicalConstants::neutron_rest_mass_amu;

    // Create a test electroatom
    ace_electroatom.reset(
	       new MonteCarlo::Electroatom( 
				    ace_file_handler->getTableName(),
				    xss_data_extractor->extractAtomicNumber(),
				    atomic_weight,
				    energy_grid,
				    scattering_reactions,
				    absorption_reactions,
				    relaxation_model,
				    false,
				    Utility::LinLin() ) );
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
// end tstElectroatom.cpp
//---------------------------------------------------------------------------//

