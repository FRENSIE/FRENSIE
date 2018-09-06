//---------------------------------------------------------------------------//
//!
//! \file   tstElectronMaterial.cpp
//! \author Luke Kersting
//! \brief  Electron material class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_ElectronMaterial.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectronMaterial> material;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
FRENSIE_UNIT_TEST( ElectronMaterial, getId )
{
  FRENSIE_CHECK_EQUAL( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
FRENSIE_UNIT_TEST( ElectronMaterial, getNumberDensity )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( material->getNumberDensity(),
                          2.9064395906311e-3,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( ElectronMaterial, getMacroscopicTotalCrossSection )
{
  double energy = 1.0e-5;
  double cross_section =
    material->getMacroscopicTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.641204418336E+06, 1e-12 );

  energy = 1.0e5;
  cross_section = material->getMacroscopicTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.269992326372E+03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic absorption cross section can be returned
FRENSIE_UNIT_TEST( ElectronMaterial, getMacroscopicAbsorptionCrossSection )
{
  double cross_section = material->getMacroscopicAbsorptionCrossSection( 1.0e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( ElectronMaterial, getSurvivalProbability )
{
  double survival_prob = material->getSurvivalProbability( 1.0e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );

  survival_prob = material->getSurvivalProbability( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic cross section for a specific reaction can be ret
FRENSIE_UNIT_TEST( ElectronMaterial, getMacroscopicReactionCrossSection )
{
  // Test that the atomic excitation cross section can be returned
  double cross_section = material->getMacroscopicReactionCrossSection(
        1.0e-5,
        MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.545329003693E+04, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e5,
        MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.588134602166E+03, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e-5,
        MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.415377951846E+01, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e5,
        MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.679677054824E+00, 1e-12 );



  // Test that the total electroionization cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e-5,
        MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.8091128793704789e+05, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        8.97540E-02,
        MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0455904319300407e+04, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e5,
        MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.6761777904979213e+03, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e-5,
        MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e5,
        MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e-5,
        MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e5,
        MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the cutoff elastic cross section can be returned
  double energy = 1.0e-5;
  cross_section = material->getMacroscopicReactionCrossSection(
        energy,
        MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.234825686582E+06, 1e-12 );

  energy = 1.0e5;
  cross_section = material->getMacroscopicReactionCrossSection(
        energy,
        MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.566534386946E-04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( ElectronMaterial, getAbsorptionReactionTypes )
{
  MonteCarlo::ElectronMaterial::ReactionEnumTypeSet reaction_types;

  material->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( ElectronMaterial, getScatteringReactionTypes )
{
  MonteCarlo::ElectronMaterial::ReactionEnumTypeSet reaction_types;

  material->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 4 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the misc reaction types can be returned
FRENSIE_UNIT_TEST( ElectronMaterial, getMiscReactionTypes )
{
  MonteCarlo::ElectronMaterial::ReactionEnumTypeSet reaction_types;

  material->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( ElectronMaterial, getReactionTypes )
{
  MonteCarlo::ElectronMaterial::ReactionEnumTypeSet reaction_types;

  material->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 5 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that a electron can collide with the material
//! \details This unit test is dependent on the version of boost being used.
FRENSIE_UNIT_TEST( ElectronMaterial, collideAnalogue )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 1.0-1e-15; // select the elastic reaction
  fake_stream[2] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideAnalogue( electron, bank );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 0.9874366113907, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a electron can collide with the material and survival bias
//! \details This unit test is dependent on the version of boost being used.
FRENSIE_UNIT_TEST( ElectronMaterial, collideSurvivalBias )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 1.0-1e-15; // select the elastic reaction
  fake_stream[2] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideSurvivalBias( electron, bank );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 0.9874366113907, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getWeight(), 1.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
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

    const Data::AtomProperties& pb_properties =
      database.getAtomProperties( Data::Pb_ATOM );

    // Set the scattering center definitions
    MonteCarlo::ScatteringCenterDefinitionDatabase electroatom_definitions;

    MonteCarlo::ScatteringCenterDefinition& pb_definition =
      electroatom_definitions.createDefinition( "Pb", Data::Pb_ATOM );

    pb_definition.setElectroatomicDataProperties(
           pb_properties.getSharedElectroatomicDataProperties(
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               12 ) );

    MonteCarlo::ElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
    electroatom_aliases.insert( "Pb" );

    // Create the factories
    std::shared_ptr<MonteCarlo::AtomicRelaxationModelFactory>
      atomic_relaxation_model_factory(
                new MonteCarlo::AtomicRelaxationModelFactory );

    MonteCarlo::SimulationProperties properties;
    properties.setNumberOfElectronHashGridBins( 100 );
    properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::TWOBS_DISTRIBUTION );
    properties.setElasticCutoffAngleCosine( 1.0 );
    properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );

    MonteCarlo::ElectroatomFactory factory( data_directory,
                                            electroatom_aliases,
                                            electroatom_definitions,
                                            atomic_relaxation_model_factory,
                                            properties,
                                            true );

    MonteCarlo::ElectroatomFactory::ElectroatomNameMap atom_map;

    factory.createElectroatomMap( atom_map );

    // Assign the atom fractions and names
    std::vector<double> atom_fractions( 1 );
    std::vector<std::string> atom_names( 1 );

    atom_fractions[0] = -1.0; // weight fraction
    atom_names[0] = "Pb";

    // Create the test material
    material.reset( new MonteCarlo::ElectronMaterial( 0,
                                                      -1.0,
                                                      atom_map,
                                                      atom_fractions,
                                                      atom_names ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectronMaterial.cpp
//---------------------------------------------------------------------------//
