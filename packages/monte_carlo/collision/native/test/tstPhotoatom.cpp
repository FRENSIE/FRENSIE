//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatom.cpp
//! \author Alex Robinson
//! \brief  Photoatom unit tests
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
#include "MonteCarlo_Photoatom.hpp"
#include "MonteCarlo_PairProductionPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::Photoatom> ace_photoatom;

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
// Check that the absorption reaction types can be returned
TEUCHOS_UNIT_TEST( Photoatom, getAbsorptionReactionTypes )
{
  const boost::unordered_set<MonteCarlo::PhotoatomicReactionType>&
    absorption_types = MonteCarlo::Photoatom::getAbsorptionReactionTypes();

  TEST_ASSERT( absorption_types.count( 
		      MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		 MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	        MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
		MonteCarlo::P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	       MonteCarlo::P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	       MonteCarlo::P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	       MonteCarlo::Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	       MonteCarlo::Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( absorption_types.count(
	       MonteCarlo::Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );

  TEST_ASSERT( !absorption_types.count(
	       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( !absorption_types.count(
	       MonteCarlo::COHERENT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( !absorption_types.count(
	       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( !absorption_types.count(
	       MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the photoatom atom name can be returned
TEUCHOS_UNIT_TEST( Photoatom, getAtomName_ace )
{
  TEST_EQUALITY_CONST( ace_photoatom->getAtomName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the photoatom nuclide name can be returned
TEUCHOS_UNIT_TEST( Photoatom, getNuclideName_ace )
{
  TEST_EQUALITY_CONST( ace_photoatom->getNuclideName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the photoatom atomic number can be returned
TEUCHOS_UNIT_TEST( Photoatom, getAtomicNumber_ace )
{
  TEST_EQUALITY_CONST( ace_photoatom->getAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the photoatom atomic mass number can be returned
TEUCHOS_UNIT_TEST( Photoatom, getAtomicMassNumber_ace )
{
  TEST_EQUALITY_CONST( ace_photoatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the photoatom isomer number can be returned
TEUCHOS_UNIT_TEST( Photoatom, getIsomerNumber_ace )
{
  TEST_EQUALITY_CONST( ace_photoatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the photoatom atomic weight can be returned
TEUCHOS_UNIT_TEST( Photoatom, getAtomicWeight_ace )
{
  TEST_FLOATING_EQUALITY( ace_photoatom->getAtomicWeight(), 
			  207.1999470456033,
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the photoatom temperature can be returned
TEUCHOS_UNIT_TEST( Photoatom, getTemperature_ace )
{
  TEST_EQUALITY_CONST( ace_photoatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
TEUCHOS_UNIT_TEST( Photoatom, getTotalCrossSection_ace )
{
  double cross_section = 
    ace_photoatom->getTotalCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getTotalCrossSection( exp( -1.214720768866E+01 ) );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getTotalCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY(cross_section,
			 exp( -1.115947249407E+01 ) + exp( 3.718032834377E+00),
			 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the total atomic cross section can be returned
TEUCHOS_UNIT_TEST( Photoatom, getAtomicTotalCrossSection_ace )
{
  double cross_section = 
    ace_photoatom->getAtomicTotalCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getAtomicTotalCrossSection( exp( -1.214720768866E+01 ) );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getAtomicTotalCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY(cross_section,
			 exp( -1.115947249407E+01 ) + exp( 3.718032834377E+00),
			 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the total nuclear cross section can be returned
TEUCHOS_UNIT_TEST( Photoatom, getNuclearTotalCrossSection_ace )
{
  double cross_section = 
    ace_photoatom->getNuclearTotalCrossSection( 1e-3 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
  
  cross_section = ace_photoatom->getNuclearTotalCrossSection( 20.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 ); 
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
TEUCHOS_UNIT_TEST( Photoatom, getAbsorptionCrossSection_ace )
{
  double cross_section = 
    ace_photoatom->getAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section =
    ace_photoatom->getAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getAbsorptionCrossSection( exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic absorption cross section can be returned
TEUCHOS_UNIT_TEST( Photoatom, getAtomicAbsorptionCrossSection_ace )
{
  double cross_section = 
    ace_photoatom->getAtomicAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section =
    ace_photoatom->getAtomicAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getAtomicAbsorptionCrossSection( exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getAtomicAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear absorption cross section can be returned
TEUCHOS_UNIT_TEST( Photoatom, getNuclearAbsorptionCrossSection_ace )
{
  double cross_section = 
    ace_photoatom->getNuclearAbsorptionCrossSection( 1e-3 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_photoatom->getNuclearAbsorptionCrossSection( 20.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( Photoatom, getSurvivalProbability_ace )
{
  double survival_prob = 
    ace_photoatom->getSurvivalProbability( exp( -1.214969212306E+01 ) );
  
  TEST_FLOATING_EQUALITY( survival_prob, 0.0, 1e-12 );

  survival_prob = 
    ace_photoatom->getSurvivalProbability( exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( survival_prob, 0.0, 1e-12 );

  survival_prob = 
    ace_photoatom->getSurvivalProbability( exp( 1.151292546497E+01 ) );

  double expected_survival_prob = exp( 3.718032834377E+00 )/
    (exp( 3.718032834377E+00 ) + exp( -1.115947249407E+01 ));
  
  TEST_FLOATING_EQUALITY( survival_prob, expected_survival_prob, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic survival probability can be returned
TEUCHOS_UNIT_TEST( Photoatom, getAtomicSurvivalProbability_ace )
{
  double survival_prob = 
    ace_photoatom->getAtomicSurvivalProbability( exp( -1.214969212306E+01 ) );
  
  TEST_FLOATING_EQUALITY( survival_prob, 0.0, 1e-12 );

  survival_prob = 
    ace_photoatom->getAtomicSurvivalProbability( exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( survival_prob, 0.0, 1e-12 );

  survival_prob = 
    ace_photoatom->getAtomicSurvivalProbability( exp( 1.151292546497E+01 ) );

  double expected_survival_prob = exp( 3.718032834377E+00 )/
    (exp( 3.718032834377E+00 ) + exp( -1.115947249407E+01 ));
  
  TEST_FLOATING_EQUALITY( survival_prob, expected_survival_prob, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear survival probability can be returned
TEUCHOS_UNIT_TEST( Photoatom, getNuclearSurvivalProbability_ace )
{
  double survival_prob = 
    ace_photoatom->getNuclearSurvivalProbability( 1e-3 );
  
  TEST_EQUALITY_CONST( survival_prob,1.0 );

  survival_prob = ace_photoatom->getNuclearSurvivalProbability( 20.0 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
TEUCHOS_UNIT_TEST( Photoatom, getReactionCrossSection )
{
  // Photoelectric effect
  double cross_section = ace_photoatom->getReactionCrossSection( 
			exp( -1.381551055796E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section = ace_photoatom->getReactionCrossSection( 
		        exp( -1.214969212306E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getReactionCrossSection( 
		        exp( -1.214720768866E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = 
    ace_photoatom->getReactionCrossSection( 
		        exp( 1.151292546497E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );

  // Pair production
  cross_section = ace_photoatom->getReactionCrossSection(
			exp( -1.381551055796E+01 ),
			MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
  
  cross_section = ace_photoatom->getReactionCrossSection(
			    exp( 2.480967890857E-02 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection(
			    exp( 1.151292546497E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );

  // Incoherent
  cross_section = ace_photoatom->getReactionCrossSection(
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_photoatom->getReactionCrossSection(
			   exp( 2.480967890857E-02 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );
  
  cross_section = ace_photoatom->getReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Coherent
  cross_section = ace_photoatom->getReactionCrossSection(
				 exp( -1.381551055796E+01 ),
				 MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_photoatom->getReactionCrossSection(
				 exp( 2.480967890857E-02 ),
				 MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );
  
  cross_section = ace_photoatom->getReactionCrossSection(
				 exp( 1.151292546497E+01 ),
				 MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Total
  cross_section = ace_photoatom->getReactionCrossSection( 
				      exp( -1.214969212306E+01 ),
				      MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection( 
				      exp( -1.214720768866E+01 ),
				      MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection( 
				      exp( 1.151292546497E+01 ),
				      MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY(cross_section,
			 exp( -1.115947249407E+01 ) + exp( 3.718032834377E+00),
			 1e-12 );

  // Absorption
  cross_section = ace_photoatom->getReactionCrossSection( 
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section =ace_photoatom->getReactionCrossSection( 
			   exp( -1.214969212306E+01 ),
			   MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection( 
			   exp( -1.214720768866E+01 ),
			   MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection( 
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );

  // Photonuclear total cross section
  cross_section = ace_photoatom->getReactionCrossSection(
					   1e-3,
					   MonteCarlo::GAMMA__TOTAL_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_photoatom->getReactionCrossSection(
					   20.0,
					   MonteCarlo::GAMMA__TOTAL_REACTION );
}

//---------------------------------------------------------------------------//
// Check that an analogue collision with the atom can be modeled
TEUCHOS_UNIT_TEST( Photoatom, collideAnalogue )
{
  Teuchos::RCP<MonteCarlo::PhotonState> photon( 
					    new MonteCarlo::PhotonState( 0 ) );
  photon->setEnergy( exp( -1.214969212306E+01 ) );
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;
  
  ace_photoatom->collideAnalogue( *photon, bank );

  TEST_ASSERT( photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  photon->setEnergy( exp( 1.151292546497E+01 ) );

  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 3.0e-7; // choose absorption rxn

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_photoatom->collideAnalogue( *photon, bank );

  TEST_ASSERT( photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  // reset the particle
  photon.reset( new MonteCarlo::PhotonState( 0 ) );
  photon->setEnergy( exp( 1.151292546497E+01 ) );
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setWeight( 1.0 );

  fake_stream[0] = 0.5; // choose scattering rxn

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_photoatom->collideAnalogue( *photon, bank );
  
  TEST_ASSERT( !photon->isGone() );
  TEST_EQUALITY_CONST( photon->getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 2 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a survival biased collision with the atom can be modeled
TEUCHOS_UNIT_TEST( Photoatom, collideSurvivalBias )
{  
  Teuchos::RCP<MonteCarlo::PhotonState> photon( 
					    new MonteCarlo::PhotonState( 0 ) );
  photon->setEnergy( exp( -1.214969212306E+01 ) );
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setWeight( 1.0 );
  
  MonteCarlo::ParticleBank bank;

  ace_photoatom->collideSurvivalBias( *photon, bank );
  
  TEST_ASSERT( photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 0 );
  
  // reset the particle
  photon.reset( new MonteCarlo::PhotonState( 0 ) );
  photon->setEnergy( exp( 1.151292546497E+01 ) );
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setWeight( 1.0 );

  ace_photoatom->collideSurvivalBias( *photon, bank );

  TEST_ASSERT( !photon->isGone() );
  TEST_FLOATING_EQUALITY( photon->getWeight(), 0.9999996542347203, 1e-15 );
  TEST_EQUALITY_CONST( bank.size(), 2 );
  TEST_FLOATING_EQUALITY( bank.top()->getWeight(), 0.9999996542347203, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a photoatom can be constructed from a core
TEUCHOS_UNIT_TEST( Photoatom, core_constructor )
{
  MonteCarlo::Photoatom photoatom_copy( ace_photoatom->getAtomName(),
  					ace_photoatom->getAtomicNumber(),
  					ace_photoatom->getAtomicWeight(),
  					ace_photoatom->getCore() );

  TEST_EQUALITY( photoatom_copy.getAtomName(), 
		 ace_photoatom->getAtomName() );
  TEST_EQUALITY( photoatom_copy.getNuclideName(),
		 ace_photoatom->getNuclideName() );
  TEST_EQUALITY( photoatom_copy.getAtomicNumber(), 
		 ace_photoatom->getAtomicNumber() );
  TEST_EQUALITY( photoatom_copy.getAtomicMassNumber(),
		 ace_photoatom->getAtomicMassNumber() );
  TEST_EQUALITY( photoatom_copy.getIsomerNumber(), 
		 ace_photoatom->getIsomerNumber() );
  TEST_EQUALITY( photoatom_copy.getAtomicWeight(), 
		 ace_photoatom->getAtomicWeight() );
  TEST_EQUALITY( photoatom_copy.getTemperature(),
		 ace_photoatom->getTemperature() );

  TEST_EQUALITY( photoatom_copy.getTotalCrossSection( 1e-3 ),
		 ace_photoatom->getTotalCrossSection( 1e-3 ) );
  TEST_EQUALITY( photoatom_copy.getTotalCrossSection( 20.0 ),
		 ace_photoatom->getTotalCrossSection( 20.0 ) );
  TEST_EQUALITY( photoatom_copy.getAtomicTotalCrossSection( 1e-3 ),
		 ace_photoatom->getAtomicTotalCrossSection( 1e-3 ) );
  TEST_EQUALITY( photoatom_copy.getAtomicTotalCrossSection( 20.0 ),
		 ace_photoatom->getAtomicTotalCrossSection( 20.0 ) );
  TEST_EQUALITY( photoatom_copy.getNuclearTotalCrossSection( 1e-3 ),
		 ace_photoatom->getNuclearTotalCrossSection( 1e-3 ) );
  TEST_EQUALITY( photoatom_copy.getNuclearTotalCrossSection( 20.0 ),
		 ace_photoatom->getNuclearTotalCrossSection( 20.0 ) );
  TEST_EQUALITY( photoatom_copy.getAbsorptionCrossSection( 1e-3 ),
		 ace_photoatom->getAbsorptionCrossSection( 1e-3 ) );
  TEST_EQUALITY( photoatom_copy.getAbsorptionCrossSection( 20.0 ),
		 ace_photoatom->getAbsorptionCrossSection( 20.0 ) );
  TEST_EQUALITY( photoatom_copy.getAtomicAbsorptionCrossSection( 1e-3 ),
		 ace_photoatom->getAtomicAbsorptionCrossSection( 1e-3 ) );
  TEST_EQUALITY( photoatom_copy.getAtomicAbsorptionCrossSection( 20.0 ),
		 ace_photoatom->getAtomicAbsorptionCrossSection( 20.0 ) );
  TEST_EQUALITY( photoatom_copy.getNuclearAbsorptionCrossSection( 1e-3 ),
		 ace_photoatom->getNuclearAbsorptionCrossSection( 1e-3 ) );
  TEST_EQUALITY( photoatom_copy.getNuclearAbsorptionCrossSection( 20.0 ),
		 ace_photoatom->getNuclearAbsorptionCrossSection( 20.0 ) );
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
    energy_grid.deepCopy( xss_data_extractor->extractPhotonEnergyGrid() );
        
    Teuchos::ArrayView<const double> raw_pe_cross_section = 
      xss_data_extractor->extractPhotoelectricCrossSection();
    
    Teuchos::ArrayView<const double>::iterator start = 
      std::find_if( raw_pe_cross_section.begin(),
		    raw_pe_cross_section.end(),
		    notEqualZero );

    Teuchos::ArrayRCP<double> pe_cross_section;
    pe_cross_section.assign( start, raw_pe_cross_section.end() );

    unsigned pe_threshold_index = 
      energy_grid.size() - pe_cross_section.size();

    Teuchos::RCP<MonteCarlo::PhotoatomicReaction> pe_reaction(
	    new MonteCarlo::PhotoelectricPhotoatomicReaction<Utility::LogLog>(
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
    
    Teuchos::RCP<MonteCarlo::PhotoatomicReaction> pp_reaction(
	    new MonteCarlo::PairProductionPhotoatomicReaction<Utility::LogLog>(
							energy_grid,
							pp_cross_section,
							pp_threshold_index ) );

    // Create the reaction maps
    MonteCarlo::Photoatom::ReactionMap scattering_reactions, 
      absorption_reactions;
    
    scattering_reactions[pp_reaction->getReactionType()] = pp_reaction;
    
    absorption_reactions[pe_reaction->getReactionType()] = pe_reaction;
    
    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
				   new MonteCarlo::VoidAtomicRelaxationModel );

    // Extract the atomic weight
    double atomic_weight = ace_file_handler->getTableAtomicWeightRatio()*
      Utility::PhysicalConstants::neutron_rest_mass_amu;

    // Create a test photoatom
    ace_photoatom.reset(
	       new MonteCarlo::Photoatom( 
				    ace_file_handler->getTableName(),
				    xss_data_extractor->extractAtomicNumber(),
				    atomic_weight,
				    energy_grid,
				    scattering_reactions,
				    absorption_reactions,
				    relaxation_model,
				    true,
				    Utility::LogLog() ) );
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
// end tstPhotoatom.cpp
//---------------------------------------------------------------------------//

