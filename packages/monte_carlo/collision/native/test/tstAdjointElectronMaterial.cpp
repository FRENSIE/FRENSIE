//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronMaterial.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron material class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomFactory.hpp"
#include "MonteCarlo_AdjointElectronMaterial.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::AdjointElectronMaterial> material;

double num_density;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
TEUCHOS_UNIT_TEST( AdjointElectronMaterial, getId )
{
  TEST_EQUALITY_CONST( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
TEUCHOS_UNIT_TEST( AdjointElectronMaterial, getNumberDensity )
{
  TEST_FLOATING_EQUALITY( material->getNumberDensity(),
                          num_density,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
TEUCHOS_UNIT_TEST( AdjointElectronMaterial, getMacroscopicTotalCrossSection )
{
  double cross_section = material->getMacroscopicTotalCrossSection( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.1121357857282637e+11*num_density, 1e-12 );

  cross_section = material->getMacroscopicTotalCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 8.4996373619527727e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicTotalCrossSection( 20.0 );
  TEST_FLOATING_EQUALITY( cross_section, 1.9755225380801866e+05*num_density, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic absorption cross section can be returned
TEUCHOS_UNIT_TEST( AdjointElectronMaterial, getMacroscopicAbsorptionCrossSection )
{
  double cross_section = material->getMacroscopicAbsorptionCrossSection( 1e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 1e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 20.0 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( AdjointElectronMaterial, getSurvivalProbability )
{
  double survival_prob = material->getSurvivalProbability( 1e-5 );
  TEST_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );

  survival_prob = material->getSurvivalProbability( 20.0 );
  TEST_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic cross section for a specific reaction can be ret
TEUCHOS_UNIT_TEST( AdjointElectronMaterial, getMacroscopicReactionCrossSection )
{
  // Test that the atomic excitation cross section can be returned
  double cross_section = material->getMacroscopicReactionCrossSection(
        1e-5,
        MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.1222996978575356e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1e-3,
        MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.0537482649407225e+07*num_density, 1e-12 );


  cross_section = material->getMacroscopicReactionCrossSection(
        20.0,
        MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 8.1829299853764838e+04*num_density, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
        1e-5,
        MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.4004979588000410e+01*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1e-3,
        MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.4938553344074585e+01*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        20.0,
        MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.4390795879250147*num_density, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
        1e-5,
        MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.1087745951184282e+11*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1e-3,
        MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 7.1653961216128990e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        20.0,
        MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.0269939235967887e+05*num_density, 1e-12 );


  // Test that there is L1 subshell electroionization cross section
  cross_section = material->getMacroscopicReactionCrossSection(
        1e-5,
        MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection(
        20.0,
        MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the analog elastic cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
        1e-5,
        MonteCarlo::ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        1e-3,
        MonteCarlo::ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.80490481543817E+06*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
        20.0,
        MonteCarlo::ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.3022122514987E+04*num_density, 1e-12 );


  // Test that there is no hybrid elastic cross section
  cross_section = material->getMacroscopicReactionCrossSection(
        1e-5,
        MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection(
        20.0,
        MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  cross_section = material->getMacroscopicReactionCrossSection(
        1e-5,
         MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection(
        20.0,
        MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no screened Rutherford reaction
  cross_section = material->getMacroscopicReactionCrossSection(
        1e-5,
        MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection(
        20.0,
        MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no moment preserving elastic cross section
  cross_section = material->getMacroscopicReactionCrossSection(
        1e-5,
        MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection(
        20.0,
        MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a adjoint electron can collide with the material
TEUCHOS_UNIT_TEST( AdjointElectronMaterial, collideAnalogue )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setCell( 4 );

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.5; // select the H atom
  fake_stream[1] = 3.30002880828054e-02; // select the elastic reaction
  fake_stream[2] = 1.08953394168687E-01; // sample mu = 0.90000623580299476956

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideAnalogue( electron, bank );

  TEST_EQUALITY_CONST( electron.getEnergy(), 1e-3 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.90000623580401506452, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a adjoint electron can collide with the material and survival bias
TEUCHOS_UNIT_TEST( AdjointElectronMaterial, collideSurvivalBias )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setCell( 4 );

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.5; // select the H atom
  fake_stream[1] = 3.30002880828054e-02; // select the elastic reaction
  fake_stream[2] = 1.08953394168687E-01; // sample mu = 0.90000623580299476956

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideSurvivalBias( electron, bank );

  TEST_EQUALITY_CONST( electron.getEnergy(), 1e-3 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.90000623580401506452, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getWeight(), 1.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_cross_sections_xml_directory;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &test_cross_sections_xml_directory,
                   "Directory where test cross_sections.xml file is located." );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  {
    // Assign the name of the cross_sections.xml file with path
    std::string cross_section_xml_file = test_cross_sections_xml_directory;
    cross_section_xml_file += "/cross_sections.xml";

    // Read in the xml file storing the cross section table info
    Teuchos::ParameterList cross_section_table_info;

    Teuchos::updateParametersFromXmlFile(
                 cross_section_xml_file,
                 Teuchos::inoutArg(cross_section_table_info) );

    std::unordered_set<std::string> atom_aliases;
    atom_aliases.insert( "H-Native" );

    double upper_cutoff_angle_cosine = 1.0;
    unsigned hash_grid_bins = 100;

    MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setAdjointElasticCutoffAngleCosine( 1.0 );
  properties.setNumberOfAdjointElectronHashGridBins( 100 );
  properties.setAdjointElectronEvaluationTolerance( 1e-7 );

    // Create the factories
    MonteCarlo::AdjointElectroatomFactory factory(
        test_cross_sections_xml_directory,
        cross_section_table_info,
        atom_aliases,
        properties );

    std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::AdjointElectroatom> >
      atom_map;

    factory.createAdjointElectroatomMap( atom_map );

    // Assign the atom fractions and names
    Teuchos::Array<double> atom_fractions( 1 );
    Teuchos::Array<std::string> atom_names( 1 );

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

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectronMaterial.cpp
//---------------------------------------------------------------------------//
