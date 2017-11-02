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
  TEST_FLOATING_EQUALITY( cross_section, 4.6912017327045776e+10*num_density, 1e-12 );

  cross_section = material->getMacroscopicTotalCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 2.9901614824232530e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicTotalCrossSection( 20.0 );
  TEST_FLOATING_EQUALITY( cross_section, 1.5704893915974183e+05*num_density, 1e-12 );
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
  double cross_section;
  MonteCarlo::AdjointElectroatomicReactionType reaction;


  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.1243057898416743e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.0551636170350602e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 8.1829299836129925e+04*num_density, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.6329278793906738e+01*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.6620526718982738e+01*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.7114113565473230e-01*num_density, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.74896e+08*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.8205052827449557e+06*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.3022122514987041e+04*num_density, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no hybrid elastic cross section
  reaction = MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.6575878222818077e+10*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.6529456750610253e+07*num_density, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.2196745667489216e+04*num_density, 1e-12 );


  // Test that the L1 subshell electroionization cross section can be returned
  reaction = MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = material->getMacroscopicReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a adjoint electron can collide with the material
//! \details This unit test is dependent on the version of boost being used.
TEUCHOS_UNIT_TEST( AdjointElectronMaterial, collideAnalogue )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setCell( 4 );

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5; // select the H atom
  if( BOOST_VERSION < 106000 )
    fake_stream[1] = 0.6; // select elastic (for boost below version 1.60)
  else
    fake_stream[1] = 9.065e-01; // select elastic (for boost above version 1.60)
  fake_stream[2] = 0.0; // sample cutoff distribution
  fake_stream[3] = 0.0; // sample mu = -1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideAnalogue( electron, bank );

  TEST_EQUALITY_CONST( electron.getEnergy(), 1e-3 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), -1.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a adjoint electron can collide with the material and survival bias
//! \details This unit test is dependent on the version of boost being used.
TEUCHOS_UNIT_TEST( AdjointElectronMaterial, collideSurvivalBias )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setCell( 4 );

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5; // select the H atom
  if( BOOST_VERSION < 106000 )
    fake_stream[1] = 0.6; // select pair production (for boost below version 1.60)
  else
    fake_stream[1] = 9.065e-01; // select pair production (for boost above version 1.60)
  fake_stream[2] = 1.0-1e-15; // sample cutoff distribution
  fake_stream[3] = 1.0-1e-15; // sample mu = 0.999999

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideSurvivalBias( electron, bank );

  TEST_EQUALITY_CONST( electron.getEnergy(), 1e-3 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.999999, 1e-12 );
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
