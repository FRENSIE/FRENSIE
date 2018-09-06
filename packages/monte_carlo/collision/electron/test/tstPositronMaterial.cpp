//---------------------------------------------------------------------------//
//!
//! \file   tstPositronMaterial.cpp
//! \author Luke Kersting
//! \brief  Positron material class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PositronatomFactory.hpp"
#include "MonteCarlo_PositronMaterial.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PositronMaterial> material;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
FRENSIE_UNIT_TEST( PositronMaterial, getId )
{
  FRENSIE_CHECK_EQUAL( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
FRENSIE_UNIT_TEST( PositronMaterial, getNumberDensity )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( material->getNumberDensity(),
                          2.9064395906311e-3,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( PositronMaterial, getMacroscopicTotalCrossSection )
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
FRENSIE_UNIT_TEST( PositronMaterial, getMacroscopicAbsorptionCrossSection )
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
FRENSIE_UNIT_TEST( PositronMaterial, getSurvivalProbability )
{
  double survival_prob = material->getSurvivalProbability( 1.0e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );

  survival_prob = material->getSurvivalProbability( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic cross section for a specific reaction can be ret
FRENSIE_UNIT_TEST( PositronMaterial, getMacroscopicReactionCrossSection )
{
  // Test that the atomic excitation cross section can be returned
  double cross_section = material->getMacroscopicReactionCrossSection(
        1.0e-5,
        MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.545329003693E+04, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e5,
        MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.588134602166E+03, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e-5,
        MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.415377951846E+01, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e5,
        MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.679677054824E+00, 1e-12 );


  // Test that the K subshell positron-ionization cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e-5,
        MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        8.97540E-02,
        MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.6350071826026E-04, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e5,
        MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.060615028974E-01, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e-5,
        MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.096230095899E+05, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1.0e5,
        MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.296521123591E+02, 1e-12 );


  // Test that the cutoff elastic cross section can be returned
  double energy = 1.0e-5;
  cross_section = material->getMacroscopicReactionCrossSection(
        energy,
        MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.234825686582E+06, 1e-12 );

  energy = 1.0e5;
  cross_section = material->getMacroscopicReactionCrossSection(
        energy,
        MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.566534386946E-04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( PositronMaterial, getAbsorptionReactionTypes )
{
  MonteCarlo::PositronMaterial::ReactionEnumTypeSet reaction_types;

  material->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( PositronMaterial, getScatteringReactionTypes )
{
  MonteCarlo::PositronMaterial::ReactionEnumTypeSet reaction_types;

  material->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 27 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the misc reaction types can be returned
FRENSIE_UNIT_TEST( PositronMaterial, getMiscReactionTypes )
{
  MonteCarlo::PositronMaterial::ReactionEnumTypeSet reaction_types;

  material->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( PositronMaterial, getReactionTypes )
{
  MonteCarlo::PositronMaterial::ReactionEnumTypeSet reaction_types;

  material->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 28 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that a positron can collide with the material
//! \details This unit test is dependent on the version of boost being used.
FRENSIE_UNIT_TEST( PositronMaterial, collideAnalogue )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1e-3 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.5; // select the pb atom
  if( BOOST_VERSION < 106000 )
    fake_stream[1] = 0.36; // select the elastic reaction (for boost below version 1.60)
  else
    fake_stream[1] = 0.61; // select the elastic reaction (for boost above version 1.60)
  fake_stream[2] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideAnalogue( positron, bank );

  FRENSIE_CHECK_EQUAL( positron.getEnergy(), 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 0.9874366113907, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a positron can collide with the material and survival bias
//! \details This unit test is dependent on the version of boost being used.
FRENSIE_UNIT_TEST( PositronMaterial, collideSurvivalBias )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1e-3 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.5; // select the pb atom
  if( BOOST_VERSION < 106000 )
    fake_stream[1] = 0.36; // select the elastic reaction (for boost below version 1.60)
  else
    fake_stream[1] = 0.61; // select the elastic reaction (for boost above version 1.60)
  fake_stream[2] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideSurvivalBias( positron, bank );

  FRENSIE_CHECK_EQUAL( positron.getEnergy(), 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 0.9874366113907, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getWeight(), 1.0, 1e-12 );

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
    MonteCarlo::ScatteringCenterDefinitionDatabase positronatom_definitions;

    MonteCarlo::ScatteringCenterDefinition& pb_definition =
      positronatom_definitions.createDefinition( "Pb", Data::Pb_ATOM );

    pb_definition.setElectroatomicDataProperties(
           pb_properties.getSharedElectroatomicDataProperties(
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               12 ) );

    MonteCarlo::PositronatomFactory::ScatteringCenterNameSet positronatom_aliases;
    positronatom_aliases.insert( "Pb" );

    // Create the factories
    std::shared_ptr<MonteCarlo::AtomicRelaxationModelFactory>
      atomic_relaxation_model_factory(
                new MonteCarlo::AtomicRelaxationModelFactory );


    MonteCarlo::SimulationProperties properties;
    properties.setNumberOfElectronHashGridBins( 100 );
    properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::TWOBS_DISTRIBUTION );
    properties.setElasticCutoffAngleCosine( 1.0 );
    properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );

    MonteCarlo::PositronatomFactory factory( data_directory,
                                             positronatom_aliases,
                                             positronatom_definitions,
                                             atomic_relaxation_model_factory,
                                             properties,
                                             true );

    MonteCarlo::PositronatomFactory::PositronatomNameMap atom_map;

    factory.createPositronatomMap( atom_map );

    // Assign the atom fractions and names
    std::vector<double> atom_fractions( 1 );
    std::vector<std::string> atom_names( 1 );

    atom_fractions[0] = -1.0; // weight fraction
    atom_names[0] = "Pb";

    // Create the test material
    material.reset( new MonteCarlo::PositronMaterial( 0,
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
// end tstPositronMaterial.cpp
//---------------------------------------------------------------------------//
