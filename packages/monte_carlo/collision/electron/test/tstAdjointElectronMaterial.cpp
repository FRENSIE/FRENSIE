//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronMaterial.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron material class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomFactory.hpp"
#include "MonteCarlo_AdjointElectronMaterial.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectronMaterial> material;
double num_density;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getId )
{
  FRENSIE_CHECK_EQUAL( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be returned
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getCriticalLineEnergies )
{
  const std::vector<double>& critical_line_energies =
    material->getCriticalLineEnergies();

  FRENSIE_REQUIRE_EQUAL( critical_line_energies.size(), 1 );
  FRENSIE_REQUIRE_EQUAL( critical_line_energies[0], 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getNumberDensity )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( material->getNumberDensity(),
                          num_density,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getMacroscopicTotalCrossSection )
{
  double cross_section = material->getMacroscopicTotalCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.280728254654968262e+10*num_density, 1e-12 );

  cross_section = material->getMacroscopicTotalCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.609051066694104671e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicTotalCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.798205883647680457e+04*num_density, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic absorption cross section can be returned
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getMacroscopicAbsorptionCrossSection )
{
  double cross_section = material->getMacroscopicAbsorptionCrossSection( 1e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 1e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 20.0 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getSurvivalProbability )
{
  double survival_prob = material->getSurvivalProbability( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );

  survival_prob = material->getSurvivalProbability( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic cross section for a specific reaction can be ret
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getMacroscopicReactionCrossSection )
{
  double cross_section;
  MonteCarlo::AdjointElectroatomicReactionType reaction;


  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.124055828282346576e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.050254326707092859e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.182929983612992510e+04*num_density, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.422553386152458188e+01*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.569786837648857869e+01*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.303534746154091928e-01*num_density, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.74896e+08*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.804290802376420237e+06*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.3022122514987041e+04*num_density, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no hybrid elastic cross section
  reaction = MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.247114594404132843e+10*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.278366089962531999e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.130506131885223567e+03*num_density, 1e-12 );


  // Test that the L1 subshell electroionization cross section can be returned
  reaction = MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getAbsorptionReactionTypes )
{
  MonteCarlo::AdjointElectronMaterial::ReactionEnumTypeSet reaction_types;

  material->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getScatteringReactionTypes )
{
  MonteCarlo::AdjointElectronMaterial::ReactionEnumTypeSet reaction_types;

  material->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 4 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the misc reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getMiscReactionTypes )
{
  MonteCarlo::AdjointElectronMaterial::ReactionEnumTypeSet reaction_types;

  material->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectronMaterial, getReactionTypes )
{
  MonteCarlo::AdjointElectronMaterial::ReactionEnumTypeSet reaction_types;

  material->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 5 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that a adjoint electron can collide with the material
//! \details This unit test is dependent on the version of boost being used.
FRENSIE_UNIT_TEST( AdjointElectronMaterial, collideAnalogue )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5; // select the H atom
  fake_stream[1] = 1.0-1e-15; // select elastic scattering
  fake_stream[2] = 0.0; // sample cutoff distribution
  fake_stream[3] = 0.0; // sample mu = -1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideAnalogue( electron, bank );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( electron.getWeight(), 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a adjoint electron can collide with the material and survival bias
//! \details This unit test is dependent on the version of boost being used.
FRENSIE_UNIT_TEST( AdjointElectronMaterial, collideSurvivalBias )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5; // select the H atom
  fake_stream[1] = 1.0-1e-15; // select elastic scattering
  fake_stream[2] = 1.0-1e-15; // sample cutoff distribution
  fake_stream[3] = 1.0-1e-15; // sample mu = 0.999999

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideSurvivalBias( electron, bank );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 0.999999, 1e-12 );
  FRENSIE_CHECK_EQUAL( electron.getWeight(), 1.0 );

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

    const Data::AtomProperties& h_properties =
      database.getAtomProperties( Data::H_ATOM );

    // Set the scattering center definitions
    MonteCarlo::ScatteringCenterDefinitionDatabase atom_definitions;

    MonteCarlo::ScatteringCenterDefinition& h_definition =
      atom_definitions.createDefinition( "H-Native", Data::H_ATOM );

    h_definition.setAdjointElectroatomicDataProperties(
           h_properties.getSharedAdjointElectroatomicDataProperties(
              Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 ) );


    MonteCarlo::AdjointElectroatomFactory::ScatteringCenterNameSet atom_aliases;
    atom_aliases.insert( "H-Native" );

    double upper_cutoff_angle_cosine = 1.0;
    unsigned hash_grid_bins = 100;

    MonteCarlo::SimulationProperties properties;

    std::vector<double> user_critical_line_energies( 1 );
    user_critical_line_energies[0] = 20.0;

    properties.setCriticalAdjointElectronLineEnergies( user_critical_line_energies );
    properties.setAdjointBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
    properties.setAdjointElasticCutoffAngleCosine( 1.0 );
    properties.setNumberOfAdjointElectronHashGridBins( 100 );
    properties.setAdjointElectronEvaluationTolerance( 1e-7 );

    // Create the factories
    MonteCarlo::AdjointElectroatomFactory factory( data_directory,
                                                   atom_aliases,
                                                   atom_definitions,
                                                   properties,
                                                   true );

    MonteCarlo::AdjointElectroatomFactory::AdjointElectroatomNameMap atom_map;

    factory.createAdjointElectroatomMap( atom_map );

    // Assign the atom fractions and names
    std::vector<double> atom_fractions( 1 );
    std::vector<std::string> atom_names( 1 );

    atom_fractions[0] = -1.0; // weight fraction
    atom_names[0] = "H-Native";

    num_density = 0.59749372094791031174;

    // Create the test material
    material.reset( new MonteCarlo::AdjointElectronMaterial( 0,
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
// end tstAdjointElectronMaterial.cpp
//---------------------------------------------------------------------------//
