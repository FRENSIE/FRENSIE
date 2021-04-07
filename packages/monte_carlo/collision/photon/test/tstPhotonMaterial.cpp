//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonMaterial.cpp
//! \author Alex Robinson
//! \brief  Photon material class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_PhotonMaterial.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotonMaterial> material;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getId )
{
  FRENSIE_CHECK_EQUAL( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getNumberDensity )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( material->getNumberDensity(),
                                   2.9064395906311e-3,
                                   1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering centers can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getScatteringCenter )
{
  std::shared_ptr<const MonteCarlo::Photoatom> photoatom =
    material->getScatteringCenter( "Pb" );

  FRENSIE_CHECK( photoatom.get() != NULL );

  FRENSIE_CHECK_THROW( material->getScatteringCenter( "pb" ),
                       std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that the scattering center number density can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getScatteringCenterNumberDensity )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( material->getScatteringCenterNumberDensity( "Pb" ),
                                   2.9064395906311e-3,
                                   1e-12 );

  FRENSIE_CHECK_THROW( material->getScatteringCenterNumberDensity( "pb" ),
                       std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getMacroscopicTotalCrossSection )
{
  double cross_section =
    material->getMacroscopicTotalCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  cross_section =
    material->getMacroscopicTotalCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic absorption cross section can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getMacroscopicAbsorptionCrossSection )
{
  double cross_section =
    material->getMacroscopicAbsorptionCrossSection(exp( -1.381551055796E+01 ));

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section =
    material->getMacroscopicAbsorptionCrossSection(exp( -1.214969212306E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 85114.18059425855, 1e-12 );

  cross_section =
    material->getMacroscopicAbsorptionCrossSection(exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.138700272111011e-08, 1e-11 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getSurvivalProbability )
{
  double survival_prob =
    material->getSurvivalProbability( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );

  survival_prob =
    material->getSurvivalProbability( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 0.9999996542464503, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic cross section for a specific reaction can be ret
FRENSIE_UNIT_TEST( PhotonMaterial, getMacroscopicReactionCrossSection )
{
  // Test that the incoherent cross section can be returned
  double cross_section = material->getMacroscopicReactionCrossSection(
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.460222195795113e-09, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.060877396028078e-06, 1e-12 );

  // Test that the coherent cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
				   exp(-1.381551055796E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.8233859760860873e-05, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
				   exp( 1.151292546497E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.712301051729535e-13, 1e-12 );

  // Test that the K subshell photoelectric cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
		   exp( -1.381551055796E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		   exp( -2.427128314806E+00 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.684476918092442, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		   exp( 1.151292546497E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.4075097760409515e-08, 1e-12 );

  // Test that the P3 subshell photoelectric cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
		  exp( -1.381551055796E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		  exp( -1.214969212306E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 85114.18059425855, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		  exp( 1.151292546497E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.5612230905027824e-13, 1e-12 );

  // Test that the pair production cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
			    exp( -1.381551055796E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
			    exp( 2.480967890857E-02 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.7562829707526906e-09, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
			    exp( 1.151292546497E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.11969677359280363, 1e-12 );

  // Test that there is not (gamma,total) reaction
  cross_section = material->getMacroscopicReactionCrossSection(
					    1e-3,
					    MonteCarlo::GAMMA__TOTAL_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection(
					   20.0,
					   MonteCarlo::GAMMA__TOTAL_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getAbsorptionReactionTypes )
{
  MonteCarlo::PhotonMaterial::ReactionEnumTypeSet reaction_types;

  material->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 24 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );

  MonteCarlo::PhotonMaterial::PhotonuclearReactionEnumTypeSet nuclear_reaction_types;

  material->getAbsorptionReactionTypes( nuclear_reaction_types );

  FRENSIE_CHECK_EQUAL( nuclear_reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getScatteringReactionTypes )
{
  MonteCarlo::PhotonMaterial::ReactionEnumTypeSet reaction_types;

  material->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 3 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::COHERENT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );

  MonteCarlo::PhotonMaterial::PhotonuclearReactionEnumTypeSet nuclear_reaction_types;

  material->getScatteringReactionTypes( nuclear_reaction_types );

  FRENSIE_CHECK_EQUAL( nuclear_reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the miscellaneous reaction types can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getMiscReactionTypes )
{
  MonteCarlo::PhotonMaterial::ReactionEnumTypeSet reaction_types;

  material->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 1 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::HEATING_PHOTOATOMIC_REACTION ) );

  MonteCarlo::PhotonMaterial::PhotonuclearReactionEnumTypeSet nuclear_reaction_types;

  material->getMiscReactionTypes( nuclear_reaction_types );

  FRENSIE_CHECK_EQUAL( nuclear_reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( PhotonMaterial, getReactionTypes )
{
  MonteCarlo::PhotonMaterial::ReactionEnumTypeSet reaction_types;

  material->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 30 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::HEATING_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::COHERENT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION ) );

  MonteCarlo::PhotonMaterial::PhotonuclearReactionEnumTypeSet nuclear_reaction_types;

  material->getReactionTypes( nuclear_reaction_types );

  FRENSIE_CHECK_EQUAL( nuclear_reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a photon can collide with the material
FRENSIE_UNIT_TEST( PhotonMaterial, collideAnalogue )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 0.1; // select the incoherent reaction
  fake_stream[2] = 0.001; // sample from first term of koblinger's method
  fake_stream[3] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[4] = 0.5; // accept x in scattering function rejection loop
  fake_stream[5] = 0.005; // select first shell for collision - old
  fake_stream[6] = 0.005; // select first shell for collision - endf
  fake_stream[7] = 6.427713151861e-01; // select pz = 40.0
  fake_stream[8] = 0.25; // select energy loss

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideAnalogue( photon, bank );
  std::cout.precision( 18 );
  std::cout << photon.getEnergy() << std::endl;
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a photon can collide with the material and survival bias
FRENSIE_UNIT_TEST( PhotonMaterial, collideSurvivalBias )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 0.1; // select the incoherent reaction
  fake_stream[2] = 0.001; // sample from first term of koblinger's method
  fake_stream[3] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[4] = 0.5; // accept x in scattering function rejection loop
  fake_stream[5] = 0.005; // select first shell for collision - old
  fake_stream[6] = 0.005; // select first shell for collision - endf
  fake_stream[7] = 6.427713151861e-01; // select pz = 40.0
  fake_stream[8] = 0.25; // select energy loss

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideSurvivalBias( photon, bank );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getWeight(), 0.99623491442141220986, 1e-12 );

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

    const Data::AtomProperties& pb_properties =
      database.getAtomProperties( Data::Pb_ATOM );

    // Set the scattering center definitions
    MonteCarlo::ScatteringCenterDefinitionDatabase photoatom_definitions;

    MonteCarlo::ScatteringCenterDefinition& pb_definition =
      photoatom_definitions.createDefinition( "Pb", Data::Pb_ATOM );

    pb_definition.setPhotoatomicDataProperties(
           pb_properties.getSharedPhotoatomicDataProperties(
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 12 ) );

    MonteCarlo::PhotoatomFactory::ScatteringCenterNameSet photoatom_aliases;
    photoatom_aliases.insert( "Pb" );

    // Set the simulation properties
    MonteCarlo::SimulationProperties properties;
    properties.setNumberOfPhotonHashGridBins( 1000 );
    properties.setIncoherentModelType( MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
    properties.setKahnSamplingCutoffEnergy( 3.0 );
    properties.setAtomicRelaxationModeOn( MonteCarlo::PHOTON );
    properties.setDetailedPairProductionModeOff();
    
    // Create the factories
    std::shared_ptr<MonteCarlo::AtomicRelaxationModelFactory>
      atomic_relaxation_model_factory(
				new MonteCarlo::AtomicRelaxationModelFactory );

    MonteCarlo::PhotoatomFactory factory( data_directory,
                                          photoatom_aliases,
                                          photoatom_definitions,
                                          atomic_relaxation_model_factory,
                                          properties,
                                          true );
    
    MonteCarlo::PhotoatomFactory::PhotoatomNameMap atom_map;

    factory.createPhotoatomMap( atom_map );
    
    // Assign the atom fractions and names
    std::vector<double> atom_fractions( 1 );
    std::vector<std::string> atom_names( 1 );
    
    atom_fractions[0] = -1.0; // weight fraction
    atom_names[0] = "Pb";
    
    // Create the test material
    material.reset( new MonteCarlo::PhotonMaterial( 0,
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
// end tstPhotonMaterial.cpp
//---------------------------------------------------------------------------//
