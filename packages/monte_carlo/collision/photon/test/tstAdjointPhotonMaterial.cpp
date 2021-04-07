//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotonMaterial.cpp
//! \author Alex Robinson
//! \brief  The adjoint photon material unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomFactory.hpp"
#include "MonteCarlo_AdjointPhotonMaterial.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotonMaterial> material;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getId )
{
  FRENSIE_CHECK_EQUAL( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getNumberDensity )
{
  FRENSIE_CHECK_EQUAL( material->getNumberDensity(), 2.144255400640911191e-02 );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getCriticalLineEnergies )
{
  const std::vector<double>& critical_line_energies =
    material->getCriticalLineEnergies();

  FRENSIE_REQUIRE_EQUAL( critical_line_energies.size(), 1 );
  FRENSIE_REQUIRE_EQUAL( critical_line_energies[0],
                         Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check if the energy corresponds to a line energy reaction
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, doesEnergyHaveLineEnergyReaction )
{
  FRENSIE_CHECK( !material->doesEnergyHaveLineEnergyReaction( 0.51 ) );
  FRENSIE_CHECK( material->doesEnergyHaveLineEnergyReaction( Utility::PhysicalConstants::electron_rest_mass_energy ) );
  FRENSIE_CHECK( !material->doesEnergyHaveLineEnergyReaction( 0.52 ) );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getMacroscopicTotalCrossSection )
{
  double cross_section = material->getMacroscopicTotalCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.156795677265385791e+00, 1e-12 );

  cross_section = material->getMacroscopicTotalCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.181912752732568045e-01, 1e-12 );

  cross_section = material->getMacroscopicTotalCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.207969627447397433e-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total line energy cross section can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial,
                   getMacroscopicTotalLineEnergyCrossSection )
{
  double cross_section =
    material->getMacroscopicTotalLineEnergyCrossSection( 0.51 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicTotalLineEnergyCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.293906832870189261e-01, 1e-12 );

  cross_section = material->getMacroscopicTotalLineEnergyCrossSection( 0.52 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total forward cross section can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial,
                   getMacroscopicTotalForwardCrossSection )
{
  double cross_section =
    material->getMacroscopicTotalForwardCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.568234049641858064e+03, 1e-12 );

  cross_section = material->getMacroscopicTotalForwardCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.352161503213631100e-02, 1e-12 );

  cross_section = material->getMacroscopicTotalForwardCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.333078604984931137e-02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic absorption cross section can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial,
                   getMacroscopicAbsorptionCrossSection )
{
  double cross_section =
    material->getMacroscopicAbsorptionCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 1.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 20.0 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint weight factor can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getAdjointWeightFactor )
{
  double weight_factor = material->getAdjointWeightFactor( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 0.00137530216089743699, 1e-12 );

  weight_factor = material->getAdjointWeightFactor( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 1.86064657224887142, 1e-12 );

  weight_factor = material->getAdjointWeightFactor( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 1.8036124537152385e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint line energy weight factor can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getAdjointLineEnergyWeightFactor )
{
  double weight_factor =
    material->getAdjointLineEnergyWeightFactor( 0.51 );

  FRENSIE_CHECK_EQUAL( weight_factor, 0.0 );

  weight_factor = material->getAdjointLineEnergyWeightFactor( Utility::PhysicalConstants::electron_rest_mass_energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( weight_factor, 3.80493907935216980e+00, 1e-12 );

  weight_factor = material->getAdjointLineEnergyWeightFactor( 0.52 );

  FRENSIE_CHECK_EQUAL( weight_factor, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getSurvivalProbability )
{
  double survival_prob = material->getSurvivalProbability( 1e-3 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob = material->getSurvivalProbability( 1.0 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob = material->getSurvivalProbability( 1.0 );

  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic cross section for a specific reaction can
// be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getMacroscopicReactionCrossSection )
{
  // Check the atomic total cross section
  double cross_section = material->getMacroscopicReactionCrossSection( 1e-3, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.156795677265385791e+00, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1.0, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.181912752732568045e-01, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.207969627447397433e-07, 1e-12 );

  // Check the total incoherent cross section
  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.331412784395857342e-02, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1.0, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.180232426919996663e-01, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Check the coherent cross section
  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.143481549421427435e+00, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1.0, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.680325812571523071e-04, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.207969627447397433e-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getAbsorptionReactionTypes )
{
  MonteCarlo::AdjointPhotonMaterial::ReactionEnumTypeSet reaction_types;

  material->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getScatteringReactionTypes )
{
  MonteCarlo::AdjointPhotonMaterial::ReactionEnumTypeSet reaction_types;

  material->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 2 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the miscellaneous reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getMiscReactionTypes )
{
  MonteCarlo::AdjointPhotonMaterial::ReactionEnumTypeSet reaction_types;

  material->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, getReactionTypes )
{
  MonteCarlo::AdjointPhotonMaterial::ReactionEnumTypeSet reaction_types;

  material->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 3 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can collide with the material
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, collideAnalogue )
{
  // Sample the incoherent reaction
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.99; // choose the only photoatom
  fake_stream[1] = 0.78; // choose incoherent scattering
  fake_stream[2] = 0.15; // branch 1
  fake_stream[3] = 0.4721647344828152; // select x = 0.9
  fake_stream[4] = 0.49; // accept
  fake_stream[5] = 0.91; // reject based on scattering function
  fake_stream[6] = 0.15; // branch 1
  fake_stream[7] = 0.4721647344828152; // select x = 0.9
  fake_stream[8] = 0.49; // accept
  fake_stream[9] = 0.909; // accept based on scattering function
  fake_stream[10] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  material->collideAnalogue( adjoint_photon, bank );

  FRENSIE_CHECK( !adjoint_photon.isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  // Sample the coherent reaction
  fake_stream.resize( 7 );
  fake_stream[0] = 0.99; // choose the only photoatom
  fake_stream[1] = 0.79; // choose coherent scattering
  fake_stream[2] = 1.00475965594E-03; // sample form factor function squared (y = 1E6 cm)
  fake_stream[3] = 9.98800000000E-01; // reject the cosine scattering angle form function rejection loop
  fake_stream[4] = 6.50327467413E-01; // sample form factor function squared (y = 3E7 cm)
  fake_stream[5] = 5.07800000000E-01; // accept the cosine scattering angle form function rejection loop
  fake_stream[6] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_photon.setEnergy( 4.95936772145E-03 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  material->collideAnalogue( adjoint_photon, bank );

  FRENSIE_CHECK( !adjoint_photon.isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  4.95936772145E-03,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can collide with the material and survival
// bias
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, collideSurvivalBias )
{
  // Sample the incoherent reaction
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.99; // choose the only photoatom
  fake_stream[1] = 0.78; // choose incoherent scattering
  fake_stream[2] = 0.15; // branch 1
  fake_stream[3] = 0.4721647344828152; // select x = 0.9
  fake_stream[4] = 0.49; // accept
  fake_stream[5] = 0.91; // reject based on scattering function
  fake_stream[6] = 0.15; // branch 1
  fake_stream[7] = 0.4721647344828152; // select x = 0.9
  fake_stream[8] = 0.49; // accept
  fake_stream[9] = 0.909; // accept based on scattering function
  fake_stream[10] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  material->collideSurvivalBias( adjoint_photon, bank );

  FRENSIE_CHECK( !adjoint_photon.isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  // Sample the coherent reaction
  fake_stream.resize( 7 );
  fake_stream[0] = 0.99; // choose the only photoatom
  fake_stream[1] = 0.79; // choose coherent scattering
  fake_stream[2] = 1.00475965594E-03; // sample form factor function squared (y = 1E6 cm)
  fake_stream[3] = 9.98800000000E-01; // reject the cosine scattering angle form function rejection loop
  fake_stream[4] = 6.50327467413E-01; // sample form factor function squared (y = 3E7 cm)
  fake_stream[5] = 5.07800000000E-01; // accept the cosine scattering angle form function rejection loop
  fake_stream[6] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_photon.setEnergy( 4.95936772145E-03 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  material->collideSurvivalBias( adjoint_photon, bank );

  FRENSIE_CHECK( !adjoint_photon.isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  4.95936772145E-03,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon at a line energy can collide with the material
FRENSIE_UNIT_TEST( AdjointPhotonMaterial, collideAtLineEnergy )
{
  // Sample the pair production reaction
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.99; // select the only photoatom
  fake_stream[1] = 0.05;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  std::unique_ptr<MonteCarlo::AdjointPhotonProbeState>
    adjoint_photon( new MonteCarlo::AdjointPhotonProbeState( 0 ) );
  adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  material->collideAtLineEnergy( *adjoint_photon, bank );

  FRENSIE_CHECK( adjoint_photon->isGone() );
  FRENSIE_CHECK_EQUAL( adjoint_photon->getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
                                   2*Utility::PhysicalConstants::electron_rest_mass_energy,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  bank.pop();

  // Sample the triplet production reaction
  fake_stream[0] = 0.99; // select the only photoatom
  fake_stream[1] = 0.04;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_photon.reset( new MonteCarlo::AdjointPhotonProbeState( 0 ) );
  adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );

  material->collideAtLineEnergy( *adjoint_photon, bank );

  FRENSIE_CHECK( adjoint_photon->isGone() );
  FRENSIE_CHECK_EQUAL( adjoint_photon->getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
                                   4*Utility::PhysicalConstants::electron_rest_mass_energy,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_scattering_center_database_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_database",
                                        test_scattering_center_database_name, "",
                                        "Test scattering center database name "
                                        "with path" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Determine the database directory
    boost::filesystem::path database_path =
      test_scattering_center_database_name;

    boost::filesystem::path data_directory = database_path.parent_path();

    // Load the database
    const Data::ScatteringCenterPropertiesDatabase database( database_path );

    const Data::AtomProperties& si_properties =
      database.getAtomProperties( Data::Si_ATOM );

    // Set the scattering center definitions
    MonteCarlo::ScatteringCenterDefinitionDatabase adjoint_photoatom_definitions;

    MonteCarlo::ScatteringCenterDefinition& si_definition =
    adjoint_photoatom_definitions.createDefinition( "Si-Native", Data::Si_ATOM );

    si_definition.setPhotoatomicDataProperties(
          si_properties.getSharedPhotoatomicDataProperties(
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              0 ) );

    si_definition.setAdjointPhotoatomicDataProperties(
          si_properties.getSharedAdjointPhotoatomicDataProperties(
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       0 ) );

    MonteCarlo::AdjointPhotoatomFactory::ScatteringCenterNameSet adjoint_photoatom_aliases;
    adjoint_photoatom_aliases.insert( "Si-Native" );

    // Set the simulation properties
    MonteCarlo::SimulationProperties properties;
    properties.setMaxAdjointPhotonEnergy( 20.0 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
    properties.setAdjointKleinNishinaSamplingType( MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING );

    // Create the factories
    MonteCarlo::AdjointPhotoatomFactory factory( data_directory,
                                                 adjoint_photoatom_aliases,
                                                 adjoint_photoatom_definitions,
                                                 properties,
                                                 true );

    MonteCarlo::AdjointPhotoatomFactory::AdjointPhotoatomNameMap
      adjoint_photoatom_map;

    factory.createAdjointPhotoatomMap( adjoint_photoatom_map );

    // Assign the atom fractions and names
    std::vector<double> atom_fractions( 1 );
    std::vector<std::string> atom_names( 1 );

    atom_fractions[0] = -1.0; // weight fraction
    atom_names[0] = "Si-Native";

    // Create the test material
    material.reset( new MonteCarlo::AdjointPhotonMaterial( 0,
                                                           -1.0,
                                                           adjoint_photoatom_map,
                                                           atom_fractions,
                                                           atom_names ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotonMaterial.cpp
//---------------------------------------------------------------------------//
