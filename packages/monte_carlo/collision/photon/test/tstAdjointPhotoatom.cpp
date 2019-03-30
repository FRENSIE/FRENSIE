//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotoatom.cpp
//! \author Alex Robinson
//! \brief  Adjoint photoatom unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatom.hpp"
#include "MonteCarlo_AdjointPhotoatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::AdjointPhotoatom> adjoint_photoatom;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atom name can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAtomName )
{
  FRENSIE_CHECK( adjoint_photoatom->getAtomName().find( "14" ) <
               adjoint_photoatom->getAtomName().size() );
}

//---------------------------------------------------------------------------//
// Check that the nuclide name can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getNuclideName )
{
  FRENSIE_CHECK( adjoint_photoatom->getAtomName().find( "14" ) <
               adjoint_photoatom->getAtomName().size() );
}

//---------------------------------------------------------------------------//
// Check that the atomic number can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAtomicNumber )
{
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicNumber(), 14 );
}

//---------------------------------------------------------------------------//
// Check that the atomic mass number can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAtomicMassNumber )
{
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear isomer number can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getIsomerNumber )
{
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAtomicWeight )
{
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicWeight(), 14.0 );
}

//---------------------------------------------------------------------------//
// Check that the temperature of the atom can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getTemperature )
{
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getTemperature(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the core can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getCore )
{
  const MonteCarlo::AdjointPhotoatomCore& core =
    adjoint_photoatom->getCore();

  FRENSIE_CHECK_EQUAL( core.getScatteringReactions().size(), 2 );
  FRENSIE_CHECK_EQUAL( core.getLineEnergyReactions().size(), 1 );

  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies().size(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getCriticalLineEnergies )
{
  const std::vector<double>& critical_line_energies =
    adjoint_photoatom->getCriticalLineEnergies();

  FRENSIE_REQUIRE_EQUAL( critical_line_energies.size(), 2 );
  FRENSIE_CHECK_EQUAL( critical_line_energies[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( critical_line_energies[1], 20.0 );
}

//---------------------------------------------------------------------------//
// Check if the energy corresponds to a line energy reaction
FRENSIE_UNIT_TEST( AdjointPhotoatom, doesEnergyHaveLineEnergyReaction )
{
  FRENSIE_CHECK( !adjoint_photoatom->doesEnergyHaveLineEnergyReaction( 0.51 ) );
  FRENSIE_CHECK( adjoint_photoatom->doesEnergyHaveLineEnergyReaction( Utility::PhysicalConstants::electron_rest_mass_energy ) );
  FRENSIE_CHECK( !adjoint_photoatom->doesEnergyHaveLineEnergyReaction( 0.52 ) );
}

//---------------------------------------------------------------------------//
// Check that the total cross section at the desired energy can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getTotalCrossSection )
{
  double cross_section = adjoint_photoatom->getTotalCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 100.584831294850716, 1e-12 );

  cross_section = adjoint_photoatom->getTotalCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.51199615670455145, 1e-12 );

  cross_section = adjoint_photoatom->getTotalCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the total atomic cross section at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAtomicTotalCrossSection )
{
  double cross_section = adjoint_photoatom->getAtomicTotalCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 100.584831294850716, 1e-12 );

  cross_section = adjoint_photoatom->getAtomicTotalCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.51199615670455145, 1e-12 );

  cross_section = adjoint_photoatom->getAtomicTotalCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the total nuclear cross section at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getNuclearTotalCrossSection )
{
  double cross_section =
    adjoint_photoatom->getNuclearTotalCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearTotalCrossSection( 1.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearTotalCrossSection( 20.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the total line energy cross section at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getTotalLineEnergyCrossSection )
{
  double cross_section =
    adjoint_photoatom->getTotalLineEnergyCrossSection( 0.51 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getTotalLineEnergyCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 15.3615415024052222, 1e-12 );

  cross_section = adjoint_photoatom->getTotalLineEnergyCrossSection( 0.52 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the total forward cross section at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getTotalForwardCrossSection )
{
  double cross_section =
    adjoint_photoatom->getTotalForwardCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 73136.5325778411352, 1e-12 );

  cross_section = adjoint_photoatom->getTotalForwardCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.96240900282447228, 1e-12 );

  cross_section = adjoint_photoatom->getTotalForwardCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.08806003440055754, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the total atomic forward cross section at the desired energy
// can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAtomicTotalForwardCrossSection )
{
  double cross_section =
    adjoint_photoatom->getAtomicTotalForwardCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 73136.5325778411352, 1e-12 );

  cross_section = adjoint_photoatom->getAtomicTotalForwardCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.96240900282447228, 1e-12 );

  cross_section = adjoint_photoatom->getAtomicTotalForwardCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.08806003440055754, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear total forward cross section at the desired energy
// can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getNuclearTotalForwardCrossSection )
{
  double cross_section =
    adjoint_photoatom->getNuclearTotalForwardCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearTotalForwardCrossSection( 1.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearTotalForwardCrossSection( 20.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint weight factor at the desired energy can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAdjointWeightFactor )
{
  double weight_factor = adjoint_photoatom->getAdjointWeightFactor( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 0.00137530216089743699, 1e-12 );

  weight_factor = adjoint_photoatom->getAdjointWeightFactor( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 1.86064657224887142, 1e-12 );

  weight_factor = adjoint_photoatom->getAdjointWeightFactor( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 1.8036124537152385e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic adjoint weight factor at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAtomicAdjointWeightFactor )
{
  double weight_factor =
    adjoint_photoatom->getAtomicAdjointWeightFactor( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 0.00137530216089743699, 1e-12 );

  weight_factor = adjoint_photoatom->getAtomicAdjointWeightFactor( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 1.86064657224887142, 1e-12 );

  weight_factor = adjoint_photoatom->getAtomicAdjointWeightFactor( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 1.8036124537152385e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear adjoint weight factor at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getNuclearAdjointWeightFactor )
{
  double weight_factor =
    adjoint_photoatom->getNuclearAdjointWeightFactor( 1e-3 );

  FRENSIE_CHECK_EQUAL( weight_factor, 1.0 );

  weight_factor = adjoint_photoatom->getNuclearAdjointWeightFactor( 1.0 );

  FRENSIE_CHECK_EQUAL( weight_factor, 1.0 );

  weight_factor = adjoint_photoatom->getNuclearAdjointWeightFactor( 20.0 );

  FRENSIE_CHECK_EQUAL( weight_factor, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint line energy weight factor at the desired energy can
// be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAdjointLineEnergyWeightFactor )
{
  double weight_factor =
    adjoint_photoatom->getAdjointLineEnergyWeightFactor( 0.51 );

  FRENSIE_CHECK_EQUAL( weight_factor, 0.0 );

  weight_factor = adjoint_photoatom->getAdjointLineEnergyWeightFactor( Utility::PhysicalConstants::electron_rest_mass_energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 3.80493907935216980e+00, 1e-12 );

  weight_factor = adjoint_photoatom->getAdjointLineEnergyWeightFactor( 0.52 );

  FRENSIE_CHECK_EQUAL( weight_factor, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAbsorptionCrossSection )
{
  double cross_section =
    adjoint_photoatom->getAbsorptionCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getAbsorptionCrossSection( 1.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getAbsorptionCrossSection( 20.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic absorption cross section at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAtomicAbsorptionCrossSection )
{
  double cross_section =
    adjoint_photoatom->getAtomicAbsorptionCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getAtomicAbsorptionCrossSection( 1.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getAtomicAbsorptionCrossSection( 20.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear absorption cross section at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getNuclearAbsorptionCrossSection )
{
  double cross_section =
    adjoint_photoatom->getNuclearAbsorptionCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearAbsorptionCrossSection( 1.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearAbsorptionCrossSection( 20.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability at the desired energy can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getSurvivalProbability )
{
  double survival_prob = adjoint_photoatom->getSurvivalProbability( 1e-3 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getSurvivalProbability( 1.0 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getSurvivalProbability( 1.0 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic survival probability at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAtomicSurvivalProbability )
{
  double survival_prob =
    adjoint_photoatom->getAtomicSurvivalProbability( 1e-3 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getAtomicSurvivalProbability( 1.0 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getAtomicSurvivalProbability( 1.0 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear survival probability at the desired energy can be
// returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getNuclearSurvivalProbability )
{
  double survival_prob =
    adjoint_photoatom->getNuclearSurvivalProbability( 1e-3 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getNuclearSurvivalProbability( 1.0 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getNuclearSurvivalProbability( 1.0 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the cross section for a specific adjoint photoatomic reaction
// can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getReactionCrossSection )
{
  // Check the atomic total cross section
  double cross_section = adjoint_photoatom->getReactionCrossSection( 1e-3, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 100.584831294850716, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 1.0, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.51199615670455145, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 20.0, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );

  // Check the total incoherent cross section
  cross_section = adjoint_photoatom->getReactionCrossSection( 1e-3, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.620920802623559753, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 1.0, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.50415974966055277, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 20.0, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  // Check the coherent cross section
  cross_section = adjoint_photoatom->getReactionCrossSection( 1e-3, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 99.9639104922271571, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 1.0, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.00783640704399895215, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 20.0, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getAbsorptionReactionTypes )
{
  MonteCarlo::AdjointPhotoatom::ReactionEnumTypeSet reaction_types;

  adjoint_photoatom->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getScatteringReactionTypes )
{
  MonteCarlo::AdjointPhotoatom::ReactionEnumTypeSet reaction_types;

  adjoint_photoatom->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 2 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the miscellaneous reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getMiscReactionTypes )
{
  MonteCarlo::AdjointPhotoatom::ReactionEnumTypeSet reaction_types;

  adjoint_photoatom->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatom, getReactionTypes )
{
  MonteCarlo::AdjointPhotoatom::ReactionEnumTypeSet reaction_types;

  adjoint_photoatom->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 3 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that an analogue collision can be modeled
FRENSIE_UNIT_TEST( AdjointPhotoatom, collideAnalogue )
{
  // Sample the incoherent reaction
  std::vector<double> fake_stream( 10 );
  fake_stream[0] = 0.78; // choose incoherent scattering
  fake_stream[1] = 0.15; // branch 1
  fake_stream[2] = 0.4721647344828152; // select x = 0.9
  fake_stream[3] = 0.49; // accept
  fake_stream[4] = 0.91; // reject based on scattering function
  fake_stream[5] = 0.15; // branch 1
  fake_stream[6] = 0.4721647344828152; // select x = 0.9
  fake_stream[7] = 0.49; // accept
  fake_stream[8] = 0.909; // accept based on scattering function
  fake_stream[9] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  adjoint_photoatom->collideAnalogue( adjoint_photon, bank );

  FRENSIE_CHECK( !adjoint_photon.isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  // Sample the coherent reaction
  fake_stream.resize( 6 );
  fake_stream[0] = 0.79;
  fake_stream[1] = 1.00475965594E-03; // sample form factor function squared (y = 1E6 cm)
  fake_stream[2] = 9.98800000000E-01; // reject the cosine scattering angle form function rejection loop
  fake_stream[3] = 6.50327467413E-01; // sample form factor function squared (y = 3E7 cm)
  fake_stream[4] = 5.07800000000E-01; // accept the cosine scattering angle form function rejection loop
  fake_stream[5] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_photon.setEnergy( 4.95936772145E-03 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  adjoint_photoatom->collideAnalogue( adjoint_photon, bank );

  FRENSIE_CHECK( !adjoint_photon.isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  4.95936772145E-03,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a survival biased collision can be modeled
FRENSIE_UNIT_TEST( AdjointPhotoatom, collideSurvivalBias )
{
  // Sample the incoherent reaction
  std::vector<double> fake_stream( 10 );
  fake_stream[0] = 0.78; // choose incoherent scattering
  fake_stream[1] = 0.15; // branch 1
  fake_stream[2] = 0.4721647344828152; // select x = 0.9
  fake_stream[3] = 0.49; // accept
  fake_stream[4] = 0.91; // reject based on scattering function
  fake_stream[5] = 0.15; // branch 1
  fake_stream[6] = 0.4721647344828152; // select x = 0.9
  fake_stream[7] = 0.49; // accept
  fake_stream[8] = 0.909; // accept based on scattering function
  fake_stream[9] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  adjoint_photoatom->collideSurvivalBias( adjoint_photon, bank );

  FRENSIE_CHECK( !adjoint_photon.isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  // Sample the coherent reaction
  fake_stream.resize( 6 );
  fake_stream[0] = 0.79;
  fake_stream[1] = 1.00475965594E-03; // sample form factor function squared (y = 1E6 cm)
  fake_stream[2] = 9.98800000000E-01; // reject the cosine scattering angle form function rejection loop
  fake_stream[3] = 6.50327467413E-01; // sample form factor function squared (y = 3E7 cm)
  fake_stream[4] = 5.07800000000E-01; // accept the cosine scattering angle form function rejection loop
  fake_stream[5] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_photon.setEnergy( 4.95936772145E-03 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  adjoint_photoatom->collideSurvivalBias( adjoint_photon, bank );

  FRENSIE_CHECK( !adjoint_photon.isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  4.95936772145E-03,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a line energy collision can be modeled
FRENSIE_UNIT_TEST( AdjointPhotoatom, collideAtLineEnergy )
{
  // Sample the pair production reaction
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.05; // select pair production
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  std::unique_ptr<MonteCarlo::AdjointPhotonProbeState>
    adjoint_photon( new MonteCarlo::AdjointPhotonProbeState( 0 ) );
  adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  adjoint_photoatom->collideAtLineEnergy( *adjoint_photon, bank );

  FRENSIE_CHECK( adjoint_photon->isGone() );
  FRENSIE_CHECK_EQUAL( bank.size(), 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
                                   2*Utility::PhysicalConstants::electron_rest_mass_energy,
                                   1e-15 );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 20.0 );
  FRENSIE_CHECK( bank.top().getWeight() != 1.0 );

  bank.pop();

  // Sample the triplet production reaction
  fake_stream[0] = 0.04; // select triplet production
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_photon.reset( new MonteCarlo::AdjointPhotonProbeState( 0 ) );
  adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );

  adjoint_photoatom->collideAtLineEnergy( *adjoint_photon, bank );

  FRENSIE_CHECK( adjoint_photon->isGone() );
  FRENSIE_CHECK_EQUAL( bank.size(), 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
                                   4*Utility::PhysicalConstants::electron_rest_mass_energy,
                                   1e-15 );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 20.0 );
  FRENSIE_CHECK( bank.top().getWeight() != 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the atom can be relaxed
FRENSIE_UNIT_TEST( AdjointPhotoatom, relaxAtom )
{
  std::shared_ptr<MonteCarlo::AdjointPhotonState> adjoint_photon(
                                    new MonteCarlo::AdjointPhotonState( 0 ) );
  adjoint_photon->setEnergy( exp( -1.214969212306E+01 ) );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );

  Data::SubshellType vacancy = Data::K_SUBSHELL;
  MonteCarlo::ParticleBank bank;

  adjoint_photoatom->relaxAtom( vacancy, *adjoint_photon, bank );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container
  Data::AdjointElectronPhotonRelaxationDataContainer
    data_container( test_native_file_name );

  // Create the union energy grid
  std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                                data_container,
                                                                *energy_grid,
                                                                20.0 );

  // Create the hash based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double> > grid_searcher(
         new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                                                                  *energy_grid,
                                                                  100 ) );

  // Create the total forward reaction
  std::shared_ptr<const MonteCarlo::PhotoatomicReaction> total_forward_reaction;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createTotalForwardReaction(
                                       data_container,
                                       energy_grid,
                                       grid_searcher,
                                       MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                                       total_forward_reaction );

  // Create the scattering reactions
  MonteCarlo::AdjointPhotoatom::ConstReactionMap scattering_reactions;

  std::shared_ptr<std::vector<double> >
    critical_line_energies( new std::vector<double>(2) );
  (*critical_line_energies)[0] =
    Utility::PhysicalConstants::electron_rest_mass_energy;
  (*critical_line_energies)[1] = 20.0;

  {
    std::vector<std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> >
      incoherent_reactions;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createIncoherentReactions(
                    data_container,
                    energy_grid,
                    grid_searcher,
                    incoherent_reactions,
                    MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                    MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                    critical_line_energies );

    scattering_reactions[incoherent_reactions[0]->getReactionType()] =
      incoherent_reactions[0];
  }

  {
    std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> coherent_reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createCoherentReaction(
                                                           data_container,
                                                           energy_grid,
                                                           grid_searcher,
                                                           coherent_reaction );

    scattering_reactions[coherent_reaction->getReactionType()] =
      coherent_reaction;
  }

  // Create the line energy reactions
  MonteCarlo::AdjointPhotoatom::ConstLineEnergyReactionMap
    line_energy_reactions;

  {
    MonteCarlo::AdjointPhotoatom::ConstReactionMap& me_line_energy_reactions =
      line_energy_reactions[Utility::PhysicalConstants::electron_rest_mass_energy];

    std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction> reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createPairProductionReaction(
                                                                data_container,
                                                                energy_grid,
                                                                grid_searcher,
                                                                reaction,
                                                                critical_line_energies );

    me_line_energy_reactions[reaction->getReactionType()] = reaction;


    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createTripletProductionReaction(
                                                                data_container,
                                                                energy_grid,
                                                                grid_searcher,
                                                                reaction,
                                                                critical_line_energies );

    me_line_energy_reactions[reaction->getReactionType()] = reaction;
  }

  // Construct the adjoint photoatom
  adjoint_photoatom.reset(
            new MonteCarlo::AdjointPhotoatom(
                              test_native_file_name,
                              data_container.getAtomicNumber(),
                              data_container.getAtomicNumber(),
                              energy_grid,
                              grid_searcher,
                              critical_line_energies,
                              total_forward_reaction,
                              scattering_reactions,
                              MonteCarlo::AdjointPhotoatom::ConstReactionMap(),
                              line_energy_reactions ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotoatom.cpp
//---------------------------------------------------------------------------//
