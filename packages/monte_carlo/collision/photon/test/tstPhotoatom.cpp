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

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"
#include "MonteCarlo_PairProductionPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::Photoatom> ace_photoatom;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the photoatom atom name can be returned
FRENSIE_UNIT_TEST( Photoatom, getAtomName_ace )
{
  FRENSIE_CHECK_EQUAL( ace_photoatom->getAtomName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the photoatom nuclide name can be returned
FRENSIE_UNIT_TEST( Photoatom, getNuclideName_ace )
{
  FRENSIE_CHECK_EQUAL( ace_photoatom->getNuclideName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the photoatom atomic number can be returned
FRENSIE_UNIT_TEST( Photoatom, getAtomicNumber_ace )
{
  FRENSIE_CHECK_EQUAL( ace_photoatom->getAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the photoatom atomic mass number can be returned
FRENSIE_UNIT_TEST( Photoatom, getAtomicMassNumber_ace )
{
  FRENSIE_CHECK_EQUAL( ace_photoatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the photoatom isomer number can be returned
FRENSIE_UNIT_TEST( Photoatom, getIsomerNumber_ace )
{
  FRENSIE_CHECK_EQUAL( ace_photoatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the photoatom atomic weight can be returned
FRENSIE_UNIT_TEST( Photoatom, getAtomicWeight_ace )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( ace_photoatom->getAtomicWeight(),
			  207.1999470456033,
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the photoatom temperature can be returned
FRENSIE_UNIT_TEST( Photoatom, getTemperature_ace )
{
  FRENSIE_CHECK_EQUAL( ace_photoatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
FRENSIE_UNIT_TEST( Photoatom, getTotalCrossSection_ace )
{
  double cross_section =
    ace_photoatom->getTotalCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    ace_photoatom->getTotalCrossSection( exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section =
    ace_photoatom->getTotalCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY(cross_section,
			 exp( -1.115947249407E+01 ) + exp( 3.718032834377E+00),
			 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the total atomic cross section can be returned
FRENSIE_UNIT_TEST( Photoatom, getAtomicTotalCrossSection_ace )
{
  double cross_section =
    ace_photoatom->getAtomicTotalCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    ace_photoatom->getAtomicTotalCrossSection( exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section =
    ace_photoatom->getAtomicTotalCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY(cross_section,
			 exp( -1.115947249407E+01 ) + exp( 3.718032834377E+00),
			 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the total nuclear cross section can be returned
FRENSIE_UNIT_TEST( Photoatom, getNuclearTotalCrossSection_ace )
{
  double cross_section =
    ace_photoatom->getNuclearTotalCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_photoatom->getNuclearTotalCrossSection( 20.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
FRENSIE_UNIT_TEST( Photoatom, getAbsorptionCrossSection_ace )
{
  double cross_section =
    ace_photoatom->getAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section =
    ace_photoatom->getAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    ace_photoatom->getAbsorptionCrossSection( exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section =
    ace_photoatom->getAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic absorption cross section can be returned
FRENSIE_UNIT_TEST( Photoatom, getAtomicAbsorptionCrossSection_ace )
{
  double cross_section =
    ace_photoatom->getAtomicAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section =
    ace_photoatom->getAtomicAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    ace_photoatom->getAtomicAbsorptionCrossSection( exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section =
    ace_photoatom->getAtomicAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear absorption cross section can be returned
FRENSIE_UNIT_TEST( Photoatom, getNuclearAbsorptionCrossSection_ace )
{
  double cross_section =
    ace_photoatom->getNuclearAbsorptionCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_photoatom->getNuclearAbsorptionCrossSection( 20.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( Photoatom, getSurvivalProbability_ace )
{
  double survival_prob =
    ace_photoatom->getSurvivalProbability( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_SMALL( survival_prob, 1e-12 );

  survival_prob =
    ace_photoatom->getSurvivalProbability( exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_SMALL( survival_prob, 1e-12 );

  survival_prob =
    ace_photoatom->getSurvivalProbability( exp( 1.151292546497E+01 ) );

  double expected_survival_prob = exp( 3.718032834377E+00 )/
    (exp( 3.718032834377E+00 ) + exp( -1.115947249407E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, expected_survival_prob, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic survival probability can be returned
FRENSIE_UNIT_TEST( Photoatom, getAtomicSurvivalProbability_ace )
{
  double survival_prob =
    ace_photoatom->getAtomicSurvivalProbability( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_SMALL( survival_prob, 1e-12 );

  survival_prob =
    ace_photoatom->getAtomicSurvivalProbability( exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_SMALL( survival_prob, 1e-12 );

  survival_prob =
    ace_photoatom->getAtomicSurvivalProbability( exp( 1.151292546497E+01 ) );

  double expected_survival_prob = exp( 3.718032834377E+00 )/
    (exp( 3.718032834377E+00 ) + exp( -1.115947249407E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, expected_survival_prob, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear survival probability can be returned
FRENSIE_UNIT_TEST( Photoatom, getNuclearSurvivalProbability_ace )
{
  double survival_prob =
    ace_photoatom->getNuclearSurvivalProbability( 1e-3 );

  FRENSIE_CHECK_EQUAL( survival_prob,1.0 );

  survival_prob = ace_photoatom->getNuclearSurvivalProbability( 20.0 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
FRENSIE_UNIT_TEST( Photoatom, getReactionCrossSection )
{
  // Photoelectric effect
  double cross_section = ace_photoatom->getReactionCrossSection(
			exp( -1.381551055796E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection(
		        exp( -1.214969212306E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    ace_photoatom->getReactionCrossSection(
		        exp( -1.214720768866E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section =
    ace_photoatom->getReactionCrossSection(
		        exp( 1.151292546497E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );

  // Pair production
  cross_section = ace_photoatom->getReactionCrossSection(
			exp( -1.381551055796E+01 ),
			MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection(
			    exp( 2.480967890857E-02 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection(
			    exp( 1.151292546497E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );

  // Incoherent
  cross_section = ace_photoatom->getReactionCrossSection(
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_photoatom->getReactionCrossSection(
			   exp( 2.480967890857E-02 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_photoatom->getReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Coherent
  cross_section = ace_photoatom->getReactionCrossSection(
				 exp( -1.381551055796E+01 ),
				 MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_photoatom->getReactionCrossSection(
				 exp( 2.480967890857E-02 ),
				 MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_photoatom->getReactionCrossSection(
				 exp( 1.151292546497E+01 ),
				 MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Total
  cross_section = ace_photoatom->getReactionCrossSection(
				      exp( -1.214969212306E+01 ),
				      MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection(
				      exp( -1.214720768866E+01 ),
				      MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection(
				      exp( 1.151292546497E+01 ),
				      MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY(cross_section,
			 exp( -1.115947249407E+01 ) + exp( 3.718032834377E+00),
			 1e-12 );

  // Absorption
  cross_section = ace_photoatom->getReactionCrossSection(
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section =ace_photoatom->getReactionCrossSection(
			   exp( -1.214969212306E+01 ),
			   MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection(
			   exp( -1.214720768866E+01 ),
			   MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = ace_photoatom->getReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );

  // Photonuclear total cross section
  cross_section = ace_photoatom->getReactionCrossSection(
					   1e-3,
					   MonteCarlo::GAMMA__TOTAL_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_photoatom->getReactionCrossSection(
					   20.0,
					   MonteCarlo::GAMMA__TOTAL_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( Photoatom, getAbsorptionReactionTypes )
{
  MonteCarlo::Photoatom::ReactionEnumTypeSet reaction_types;

  ace_photoatom->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 1 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );

  MonteCarlo::Photoatom::PhotonuclearReactionEnumTypeSet nuclear_reaction_types;

  ace_photoatom->getAbsorptionReactionTypes( nuclear_reaction_types );

  FRENSIE_CHECK_EQUAL( nuclear_reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( Photoatom, getScatteringReactionTypes )
{
  MonteCarlo::Photoatom::ReactionEnumTypeSet reaction_types;

  ace_photoatom->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 1 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );

  MonteCarlo::Photoatom::PhotonuclearReactionEnumTypeSet nuclear_reaction_types;

  ace_photoatom->getScatteringReactionTypes( nuclear_reaction_types );

  FRENSIE_CHECK_EQUAL( nuclear_reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the miscellaneous reaction types can be returned
FRENSIE_UNIT_TEST( Photoatom, getMiscReactionTypes )
{
  MonteCarlo::Photoatom::ReactionEnumTypeSet reaction_types;

  ace_photoatom->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );

  MonteCarlo::Photoatom::PhotonuclearReactionEnumTypeSet nuclear_reaction_types;

  ace_photoatom->getMiscReactionTypes( nuclear_reaction_types );

  FRENSIE_CHECK_EQUAL( nuclear_reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( Photoatom, getReactionTypes )
{
  MonteCarlo::Photoatom::ReactionEnumTypeSet reaction_types;

  ace_photoatom->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 4 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );

  MonteCarlo::Photoatom::PhotonuclearReactionEnumTypeSet nuclear_reaction_types;

  ace_photoatom->getReactionTypes( nuclear_reaction_types );

  FRENSIE_CHECK_EQUAL( nuclear_reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an analogue collision with the atom can be modeled
FRENSIE_UNIT_TEST( Photoatom, collideAnalogue )
{
  std::shared_ptr<MonteCarlo::PhotonState> photon(
					    new MonteCarlo::PhotonState( 0 ) );
  photon->setEnergy( exp( -1.214969212306E+01 ) );
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  ace_photoatom->collideAnalogue( *photon, bank );

  FRENSIE_CHECK( photon->isGone() );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  photon->setEnergy( exp( 1.151292546497E+01 ) );

  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 3.0e-7; // choose absorption rxn

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_photoatom->collideAnalogue( *photon, bank );

  FRENSIE_CHECK( photon->isGone() );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  // reset the particle
  photon.reset( new MonteCarlo::PhotonState( 0 ) );
  photon->setEnergy( exp( 1.151292546497E+01 ) );
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setWeight( 1.0 );

  fake_stream[0] = 0.5; // choose scattering rxn

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_photoatom->collideAnalogue( *photon, bank );

  FRENSIE_CHECK( !photon->isGone() );
  FRENSIE_CHECK_EQUAL( photon->getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 2 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a survival biased collision with the atom can be modeled
FRENSIE_UNIT_TEST( Photoatom, collideSurvivalBias )
{
  std::shared_ptr<MonteCarlo::PhotonState> photon(
					    new MonteCarlo::PhotonState( 0 ) );
  photon->setEnergy( exp( -1.214969212306E+01 ) );
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  ace_photoatom->collideSurvivalBias( *photon, bank );

  FRENSIE_CHECK( photon->isGone() );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  // reset the particle
  photon.reset( new MonteCarlo::PhotonState( 0 ) );
  photon->setEnergy( exp( 1.151292546497E+01 ) );
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setWeight( 1.0 );

  ace_photoatom->collideSurvivalBias( *photon, bank );

  FRENSIE_CHECK( !photon->isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon->getWeight(), 0.9999996542347203, 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(), 0.9999996542347203, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the atom can be relaxed
FRENSIE_UNIT_TEST( Photoatom, relaxAtom )
{
  std::shared_ptr<MonteCarlo::PhotonState> photon(
                                            new MonteCarlo::PhotonState( 0 ) );
  photon->setEnergy( exp( -1.214969212306E+01 ) );
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setWeight( 1.0 );

  Data::SubshellType vacancy = Data::K_SUBSHELL;
  MonteCarlo::ParticleBank bank;

  ace_photoatom->relaxAtom( vacancy, *photon, bank );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a photoatom can be constructed from a core
FRENSIE_UNIT_TEST( Photoatom, core_constructor )
{
  MonteCarlo::Photoatom photoatom_copy( ace_photoatom->getAtomName(),
  					ace_photoatom->getAtomicNumber(),
  					ace_photoatom->getAtomicWeight(),
  					ace_photoatom->getCore() );

  FRENSIE_CHECK_EQUAL( photoatom_copy.getAtomName(),
		 ace_photoatom->getAtomName() );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getNuclideName(),
		 ace_photoatom->getNuclideName() );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getAtomicNumber(),
		 ace_photoatom->getAtomicNumber() );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getAtomicMassNumber(),
		 ace_photoatom->getAtomicMassNumber() );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getIsomerNumber(),
		 ace_photoatom->getIsomerNumber() );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getAtomicWeight(),
		 ace_photoatom->getAtomicWeight() );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getTemperature(),
		 ace_photoatom->getTemperature() );

  FRENSIE_CHECK_EQUAL( photoatom_copy.getTotalCrossSection( 1e-3 ),
		 ace_photoatom->getTotalCrossSection( 1e-3 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getTotalCrossSection( 20.0 ),
		 ace_photoatom->getTotalCrossSection( 20.0 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getAtomicTotalCrossSection( 1e-3 ),
		 ace_photoatom->getAtomicTotalCrossSection( 1e-3 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getAtomicTotalCrossSection( 20.0 ),
		 ace_photoatom->getAtomicTotalCrossSection( 20.0 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getNuclearTotalCrossSection( 1e-3 ),
		 ace_photoatom->getNuclearTotalCrossSection( 1e-3 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getNuclearTotalCrossSection( 20.0 ),
		 ace_photoatom->getNuclearTotalCrossSection( 20.0 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getAbsorptionCrossSection( 1e-3 ),
		 ace_photoatom->getAbsorptionCrossSection( 1e-3 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getAbsorptionCrossSection( 20.0 ),
		 ace_photoatom->getAbsorptionCrossSection( 20.0 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getAtomicAbsorptionCrossSection( 1e-3 ),
		 ace_photoatom->getAtomicAbsorptionCrossSection( 1e-3 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getAtomicAbsorptionCrossSection( 20.0 ),
		 ace_photoatom->getAtomicAbsorptionCrossSection( 20.0 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getNuclearAbsorptionCrossSection( 1e-3 ),
		 ace_photoatom->getNuclearAbsorptionCrossSection( 1e-3 ) );
  FRENSIE_CHECK_EQUAL( photoatom_copy.getNuclearAbsorptionCrossSection( 20.0 ),
		 ace_photoatom->getNuclearAbsorptionCrossSection( 20.0 ) );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Create a file handler and data extractor
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.12p",
						  test_ace_file_start_line ) );
    
    std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    // Create the pair production and photoelectric effect cross sections
    std::shared_ptr<std::vector<double> > energy_grid(
       new std::vector<double>( xss_data_extractor->extractPhotonEnergyGrid() ) );

    std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
          new Utility::StandardHashBasedGridSearcher<std::vector<double>,true>(
					     energy_grid,
					     energy_grid->front(),
					     energy_grid->back(),
					     1000 ) );

    Utility::ArrayView<const double> raw_pe_cross_section =
      xss_data_extractor->extractPhotoelectricCrossSection();

    Utility::ArrayView<const double>::iterator start =
      std::find_if( raw_pe_cross_section.begin(),
		    raw_pe_cross_section.end(),
		    [](double cs){ return cs != 0.0; } );

    std::shared_ptr<std::vector<double> > pe_cross_section(
                new std::vector<double>( start, raw_pe_cross_section.end() ) );

    size_t pe_threshold_index =
      energy_grid->size() - pe_cross_section->size();

    std::shared_ptr<MonteCarlo::PhotoatomicReaction> pe_reaction(
	    new MonteCarlo::PhotoelectricPhotoatomicReaction<Utility::LogLog>(
						    energy_grid,
						    pe_cross_section,
						    pe_threshold_index ) );

    Utility::ArrayView<const double> raw_pp_cross_section =
      xss_data_extractor->extractPairProductionCrossSection();

    start = std::find_if( raw_pp_cross_section.begin(),
                          raw_pp_cross_section.end(),
                          [](double cs){ return cs != 0.0; } );

    std::shared_ptr<std::vector<double> > pp_cross_section(
                new std::vector<double>( start, raw_pp_cross_section.end() ) );

    size_t pp_threshold_index =
      energy_grid->size() - pp_cross_section->size();

    std::shared_ptr<MonteCarlo::PhotoatomicReaction> pp_reaction(
	    new MonteCarlo::PairProductionPhotoatomicReaction<Utility::LogLog>(
							energy_grid,
							pp_cross_section,
							pp_threshold_index,
							false ) );

    // Create the reaction maps
    MonteCarlo::Photoatom::ConstReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[pp_reaction->getReactionType()] = pp_reaction;

    absorption_reactions[pe_reaction->getReactionType()] = pe_reaction;

    // Create a void atomic relaxation model
    std::shared_ptr<MonteCarlo::AtomicRelaxationModel> relaxation_model(
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
				    grid_searcher,
				    scattering_reactions,
				    absorption_reactions,
				    relaxation_model,
				    true,
				    Utility::LogLog() ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotoatom.cpp
//---------------------------------------------------------------------------//

