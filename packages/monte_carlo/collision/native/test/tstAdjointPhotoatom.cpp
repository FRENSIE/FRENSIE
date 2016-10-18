//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotoatom.cpp
//! \author Alex Robinson
//! \brief  Adjoint photoatom unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatom.hpp"
#include "MonteCarlo_AdjointPhotoatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatom> adjoint_photoatom;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atom name can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAtomName )
{
  TEST_ASSERT( adjoint_photoatom->getAtomName().find( "14" ) <
               adjoint_photoatom->getAtomName().size() );
}

//---------------------------------------------------------------------------//
// Check that the nuclide name can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getNuclideName )
{
  TEST_ASSERT( adjoint_photoatom->getAtomName().find( "14" ) <
               adjoint_photoatom->getAtomName().size() );
}

//---------------------------------------------------------------------------//
// Check that the atomic number can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAtomicNumber )
{
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicNumber(), 14 );
}

//---------------------------------------------------------------------------//
// Check that the atomic mass number can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAtomicMassNumber )
{
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear isomer number can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getIsomerNumber )
{
  TEST_EQUALITY_CONST( adjoint_photoatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAtomicWeight )
{
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicWeight(), 14.0 );
}

//---------------------------------------------------------------------------//
// Check that the temperature of the atom can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getTemperature )
{
  TEST_EQUALITY_CONST( adjoint_photoatom->getTemperature(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the core can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getCore )
{
  const MonteCarlo::AdjointPhotoatomCore& core =
    adjoint_photoatom->getCore();

  TEST_EQUALITY_CONST( core.getScatteringReactions().size(), 2 );
  TEST_EQUALITY_CONST( core.getLineEnergyReactions().size(), 1 );

  TEST_EQUALITY_CONST( core.getCriticalLineEnergies().size(), 2 );
}

//---------------------------------------------------------------------------//
// Check if the energy corresponds to a line energy reaction
TEUCHOS_UNIT_TEST( AdjointPhotoatom, doesEnergyHaveLineEnergyReaction )
{
  TEST_ASSERT( !adjoint_photoatom->doesEnergyHaveLineEnergyReaction( 0.51 ) );
  TEST_ASSERT( adjoint_photoatom->doesEnergyHaveLineEnergyReaction( Utility::PhysicalConstants::electron_rest_mass_energy ) );
  TEST_ASSERT( !adjoint_photoatom->doesEnergyHaveLineEnergyReaction( 0.52 ) );
}

//---------------------------------------------------------------------------//
// Check that the total cross section at the desired energy can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getTotalCrossSection )
{
  double cross_section = adjoint_photoatom->getTotalCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 100.584831294850716, 1e-12 );

  cross_section = adjoint_photoatom->getTotalCrossSection( 1.0 );

  TEST_FLOATING_EQUALITY( cross_section, 5.51199615670455145, 1e-12 );

  cross_section = adjoint_photoatom->getTotalCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the total atomic cross section at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAtomicTotalCrossSection )
{
  double cross_section = adjoint_photoatom->getAtomicTotalCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 100.584831294850716, 1e-12 );

  cross_section = adjoint_photoatom->getAtomicTotalCrossSection( 1.0 );

  TEST_FLOATING_EQUALITY( cross_section, 5.51199615670455145, 1e-12 );

  cross_section = adjoint_photoatom->getAtomicTotalCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the total nuclear cross section at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getNuclearTotalCrossSection )
{
  double cross_section =
    adjoint_photoatom->getNuclearTotalCrossSection( 1e-3 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearTotalCrossSection( 1.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearTotalCrossSection( 20.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the total line energy cross section at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getTotalLineEnergyCrossSection )
{
  double cross_section =
    adjoint_photoatom->getTotalLineEnergyCrossSection( 0.51 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getTotalLineEnergyCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy );
  
  TEST_FLOATING_EQUALITY( cross_section, 15.3615415024052222, 1e-12 );

  cross_section = adjoint_photoatom->getTotalLineEnergyCrossSection( 0.52 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the total forward cross section at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getTotalForwardCrossSection )
{
  double cross_section =
    adjoint_photoatom->getTotalForwardCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 73136.5325778411352, 1e-12 );

  cross_section = adjoint_photoatom->getTotalForwardCrossSection( 1.0 );

  TEST_FLOATING_EQUALITY( cross_section, 2.96240900282447228, 1e-12 );

  cross_section = adjoint_photoatom->getTotalForwardCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.08806003440055754, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the total atomic forward cross section at the desired energy
// can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAtomicTotalForwardCrossSection )
{
  double cross_section =
    adjoint_photoatom->getAtomicTotalForwardCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 73136.5325778411352, 1e-12 );

  cross_section = adjoint_photoatom->getAtomicTotalForwardCrossSection( 1.0 );

  TEST_FLOATING_EQUALITY( cross_section, 2.96240900282447228, 1e-12 );

  cross_section = adjoint_photoatom->getAtomicTotalForwardCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.08806003440055754, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear total forward cross section at the desired energy
// can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getNuclearTotalForwardCrossSection )
{
  double cross_section =
    adjoint_photoatom->getNuclearTotalForwardCrossSection( 1e-3 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearTotalForwardCrossSection( 1.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearTotalForwardCrossSection( 20.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint weight factor at the desired energy can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAdjointWeightFactor )
{
  double weight_factor = adjoint_photoatom->getAdjointWeightFactor( 1e-3 );
  
  TEST_FLOATING_EQUALITY( weight_factor, 0.00137530216089743699, 1e-12 );

  weight_factor = adjoint_photoatom->getAdjointWeightFactor( 1.0 );

  TEST_FLOATING_EQUALITY( weight_factor, 1.86064657224887142, 1e-12 );

  weight_factor = adjoint_photoatom->getAdjointWeightFactor( 20.0 );

  TEST_FLOATING_EQUALITY( weight_factor, 1.8036124537152385e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic adjoint weight factor at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAtomicAdjointWeightFactor )
{
  double weight_factor =
    adjoint_photoatom->getAtomicAdjointWeightFactor( 1e-3 );
  
  TEST_FLOATING_EQUALITY( weight_factor, 0.00137530216089743699, 1e-12 );

  weight_factor = adjoint_photoatom->getAtomicAdjointWeightFactor( 1.0 );

  TEST_FLOATING_EQUALITY( weight_factor, 1.86064657224887142, 1e-12 );

  weight_factor = adjoint_photoatom->getAtomicAdjointWeightFactor( 20.0 );

  TEST_FLOATING_EQUALITY( weight_factor, 1.8036124537152385e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear adjoint weight factor at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getNuclearAdjointWeightFactor )
{
  double weight_factor =
    adjoint_photoatom->getNuclearAdjointWeightFactor( 1e-3 );
  
  TEST_EQUALITY_CONST( weight_factor, 1.0 );

  weight_factor = adjoint_photoatom->getNuclearAdjointWeightFactor( 1.0 );

  TEST_EQUALITY_CONST( weight_factor, 1.0 );

  weight_factor = adjoint_photoatom->getNuclearAdjointWeightFactor( 20.0 );

  TEST_EQUALITY_CONST( weight_factor, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint line energy weight factor at the desired energy can
// be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAdjointLineEnergyWeightFactor )
{
  double weight_factor =
    adjoint_photoatom->getAdjointLineEnergyWeightFactor( 0.51 );
  
  TEST_EQUALITY_CONST( weight_factor, 0.0 );

  weight_factor = adjoint_photoatom->getAdjointLineEnergyWeightFactor( Utility::PhysicalConstants::electron_rest_mass_energy );

  TEST_FLOATING_EQUALITY( weight_factor, 3.80493907935216980e+00, 1e-12 );

  weight_factor = adjoint_photoatom->getAdjointLineEnergyWeightFactor( 0.52 );

  TEST_EQUALITY_CONST( weight_factor, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAbsorptionCrossSection )
{
  double cross_section =
    adjoint_photoatom->getAbsorptionCrossSection( 1e-3 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getAbsorptionCrossSection( 1.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getAbsorptionCrossSection( 20.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic absorption cross section at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAtomicAbsorptionCrossSection )
{
  double cross_section =
    adjoint_photoatom->getAtomicAbsorptionCrossSection( 1e-3 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getAtomicAbsorptionCrossSection( 1.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getAtomicAbsorptionCrossSection( 20.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear absorption cross section at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getNuclearAbsorptionCrossSection )
{
  double cross_section =
    adjoint_photoatom->getNuclearAbsorptionCrossSection( 1e-3 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearAbsorptionCrossSection( 1.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_photoatom->getNuclearAbsorptionCrossSection( 20.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability at the desired energy can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getSurvivalProbability )
{
  double survival_prob = adjoint_photoatom->getSurvivalProbability( 1e-3 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getSurvivalProbability( 1.0 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getSurvivalProbability( 1.0 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic survival probability at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getAtomicSurvivalProbability )
{
  double survival_prob =
    adjoint_photoatom->getAtomicSurvivalProbability( 1e-3 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getAtomicSurvivalProbability( 1.0 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getAtomicSurvivalProbability( 1.0 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the nuclear survival probability at the desired energy can be
// returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getNuclearSurvivalProbability )
{
  double survival_prob =
    adjoint_photoatom->getNuclearSurvivalProbability( 1e-3 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getNuclearSurvivalProbability( 1.0 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob = adjoint_photoatom->getNuclearSurvivalProbability( 1.0 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the cross section for a specific adjoint photoatomic reaction
// can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatom, getReactionCrossSection )
{
  // Check the atomic total cross section
  double cross_section = adjoint_photoatom->getReactionCrossSection( 1e-3, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 100.584831294850716, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 1.0, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 5.51199615670455145, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 20.0, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );

  // Check the total incoherent cross section
  cross_section = adjoint_photoatom->getReactionCrossSection( 1e-3, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.620920802623559753, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 1.0, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 5.50415974966055277, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 20.0, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Check the coherent cross section
  cross_section = adjoint_photoatom->getReactionCrossSection( 1e-3, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 99.9639104922271571, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 1.0, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.00783640704399895215, 1e-12 );

  cross_section = adjoint_photoatom->getReactionCrossSection( 20.0, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that an analogue collision can be modeled
TEUCHOS_UNIT_TEST( AdjointPhotoatom, collideAnalogue )
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

  TEST_ASSERT( !adjoint_photon.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  TEST_EQUALITY_CONST( adjoint_photon.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

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

  TEST_ASSERT( !adjoint_photon.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  4.95936772145E-03,
			  1e-15 );
  TEST_EQUALITY_CONST( adjoint_photon.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a survival biased collision can be modeled
TEUCHOS_UNIT_TEST( AdjointPhotoatom, collideSurvivalBias )
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

  TEST_ASSERT( !adjoint_photon.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  TEST_EQUALITY_CONST( adjoint_photon.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

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

  TEST_ASSERT( !adjoint_photon.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  4.95936772145E-03,
			  1e-15 );
  TEST_EQUALITY_CONST( adjoint_photon.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a line energy collision can be modeled
TEUCHOS_UNIT_TEST( AdjointPhotoatom, collideAtLineEnergy )
{
  // Sample the pair production reaction
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.95; // select pair production
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

  TEST_ASSERT( adjoint_photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
                          2*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );

  bank.pop();

  // Sample the triplet production reaction
  fake_stream[0] = 0.96; // select triplet production
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  adjoint_photon.reset( new MonteCarlo::AdjointPhotonProbeState( 0 ) );
  adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );

  adjoint_photoatom->collideAtLineEnergy( *adjoint_photon, bank );

  TEST_ASSERT( adjoint_photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
                          4*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  Data::AdjointElectronPhotonRelaxationDataContainer
    data_container( test_native_file_name );

  // Create the union energy grid
  Teuchos::ArrayRCP<double> energy_grid;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                                data_container,
                                                                energy_grid,
                                                                20.0 );

  // Create the hash based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                                                                   energy_grid,
                                                                   100 ) );

  // Create the total forward reaction
  std::shared_ptr<MonteCarlo::PhotoatomicReaction> total_forward_reaction;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createTotalForwardReaction(
                                       data_container,
                                       energy_grid,
                                       grid_searcher,
                                       MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                                       total_forward_reaction );

  // Create the scattering reactions
  MonteCarlo::AdjointPhotoatom::ReactionMap scattering_reactions;

  Teuchos::ArrayRCP<double> critical_line_energies( 2 );
  critical_line_energies[0] =
    Utility::PhysicalConstants::electron_rest_mass_energy;
  critical_line_energies[1] = 20.0;
  
  {
    std::vector<std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> >
      incoherent_reactions;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createIncoherentReactions(
                                       data_container,
                                       energy_grid,
                                       grid_searcher,
                                       incoherent_reactions,
                                       MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                                       critical_line_energies );

    scattering_reactions[incoherent_reactions[0]->getReactionType()] =
      incoherent_reactions[0];
  }

  {
    std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> coherent_reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createCoherentReaction(
                                                           data_container,
                                                           energy_grid,
                                                           grid_searcher,
                                                           coherent_reaction );

    scattering_reactions[coherent_reaction->getReactionType()] =
      coherent_reaction;
  }

  // Create the line energy reactions
  MonteCarlo::AdjointPhotoatom::LineEnergyReactionMap
    line_energy_reactions;

  {
    MonteCarlo::AdjointPhotoatom::ReactionMap& me_line_energy_reactions =
      line_energy_reactions[Utility::PhysicalConstants::electron_rest_mass_energy];
    
    std::shared_ptr<MonteCarlo::LineEnergyAdjointPhotoatomicReaction> reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createPairProductionReaction(
                                                                data_container,
                                                                energy_grid,
                                                                grid_searcher,
                                                                reaction );

    me_line_energy_reactions[reaction->getReactionType()] = reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createTripletProductionReaction(
                                                                data_container,
                                                                energy_grid,
                                                                grid_searcher,
                                                                reaction );

    me_line_energy_reactions[reaction->getReactionType()] = reaction;
  }

  // Construct the adjoint photoatom
  adjoint_photoatom.reset(
            new MonteCarlo::AdjointPhotoatom(
                                   test_native_file_name,
                                   data_container.getAtomicNumber(),
                                   data_container.getAtomicNumber(),
                                   grid_searcher,
                                   critical_line_energies,
                                   total_forward_reaction,
                                   scattering_reactions,
                                   MonteCarlo::AdjointPhotoatom::ReactionMap(),
                                   line_energy_reactions ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotoatom.cpp
//---------------------------------------------------------------------------//
