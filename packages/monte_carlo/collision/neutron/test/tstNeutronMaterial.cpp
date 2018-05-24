//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronMaterial.cpp
//! \author Alex Robinson
//! \brief  Neutron material class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_NeutronMaterial.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using Utility::Units::MeV;
using boost::units::si::kelvin;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::NeutronMaterial> material;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen, getId )
{
  FRENSIE_CHECK_EQUAL( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen, getNumberDensity )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(material->getNumberDensity(), 0.5975385703365, 1e-13);
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen, getMacroscopicTotalCrossSection )
{
  double cross_section = material->getMacroscopicTotalCrossSection( 1.0e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  cross_section = material->getMacroscopicTotalCrossSection( 2.0e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic absorption cross section can be returned
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen,
		   getMacroscopicAbsorptionCrossSection )
{
  double cross_section =
    material->getMacroscopicAbsorptionCrossSection( 1.0e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 2.0e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen, getSurvivalProbability )
{
  double survival_prob = material->getSurvivalProbability( 1.0e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 0.98581342025975, 1e-13 );

  survival_prob = material->getSurvivalProbability( 2.0e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 0.99994361011057, 1e-13 );
}

//---------------------------------------------------------------------------//
// Check that a reaction cross section can be returned
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen,
		   getMacroscopicReationCrossSection )
{
  double cross_section =
    material->getMacroscopicReactionCrossSection( 1.0e-11,
						  MonteCarlo::N__TOTAL_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection(
						   2.0e1,
						   MonteCarlo::N__TOTAL_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  cross_section = material->getMacroscopicReactionCrossSection(
					       1.0e-11,
					       MonteCarlo::N__N_ELASTIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 693.47099764974, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection(
					       2.0e1,
					       MonteCarlo::N__N_ELASTIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.28845947418338, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection(
					           1.0e-11,
					           MonteCarlo::N__GAMMA_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection(
					           2.0e1,
					           MonteCarlo::N__GAMMA_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection(
					       1.0e-11,
					       MonteCarlo::N__TOTAL_D_PRODUCTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection(
					       2.0e1,
					       MonteCarlo::N__TOTAL_D_PRODUCTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection(
					                      1.0e-11,
					                      MonteCarlo::N__DAMAGE );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );

  cross_section = material->getMacroscopicReactionCrossSection(
					                      2.0e1,
					                      MonteCarlo::N__DAMAGE );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.833066682067e-4, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection(
					         1.0e-11,
					         MonteCarlo::N__FISSION_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen, getAbsorptionReactionTypes )
{
  MonteCarlo::NeutronMaterial::ReactionEnumTypeSet reaction_types;

  material->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 1 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N__GAMMA_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen, getScatteringReactionTypes )
{
  MonteCarlo::NeutronMaterial::ReactionEnumTypeSet reaction_types;

  material->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 1 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N__N_ELASTIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the misc reaction types can be returned
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen, getMiscReactionTypes )
{
  MonteCarlo::NeutronMaterial::ReactionEnumTypeSet reaction_types;

  material->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 2 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N__TOTAL_D_PRODUCTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N__DAMAGE ) );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen, getReactionTypes )
{
  MonteCarlo::NeutronMaterial::ReactionEnumTypeSet reaction_types;

  material->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 6 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N__TOTAL_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N__TOTAL_ABSORPTION_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N__GAMMA_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N__N_ELASTIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N__TOTAL_D_PRODUCTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::N__DAMAGE ) );
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with a material
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen, collideAnalogue )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  material->collideAnalogue( neutron, bank );

  FRENSIE_CHECK_EQUAL( neutron.getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with a material
FRENSIE_UNIT_TEST( NeutronMaterial_hydrogen, collideSurvivalBias )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.03125e-11 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  material->collideSurvivalBias( neutron, bank );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getWeight(), 0.98581348192787, 1e-14 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
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
  MonteCarlo::NuclideFactory::NuclideNameMap nuclide_map;

  {
    // Determine the database directory
    boost::filesystem::path database_path =
      test_scattering_center_database_name;
    
    boost::filesystem::path data_directory = database_path.parent_path();

    // Load the database
    const Data::ScatteringCenterPropertiesDatabase database( database_path );
    
    const Data::NuclideProperties& h1_properties =
      database.getNuclideProperties( 1001 );

    // Initialize the nuclide definitions
    MonteCarlo::ScatteringCenterDefinitionDatabase nuclide_definitions;

    MonteCarlo::ScatteringCenterDefinition& h1_293K_definition =
      nuclide_definitions.createDefinition( "H-1_293.6K", 1001 );

    h1_293K_definition.setNuclearDataProperties(
                                 h1_properties.getSharedNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         2.53010E-08*MeV,
                                         true ) );
  
    MonteCarlo::NuclideFactory::ScatteringCenterNameSet nuclides_to_create;
    nuclides_to_create.insert( "H-1_293.6K" );

    MonteCarlo::SimulationProperties properties;
    properties.setNumberOfNeutronHashGridBins( 100 );
    properties.setUnresolvedResonanceProbabilityTableModeOn();
    properties.setParticleMode( MonteCarlo::NEUTRON_MODE );

    MonteCarlo::NuclideFactory nuclide_factory( data_directory,
                                                nuclides_to_create,
                                                nuclide_definitions,
                                                properties,
                                                true );

  

    nuclide_factory.createNuclideMap( nuclide_map );
  }

  std::vector<double> nuclide_fractions( {-1.0} ); // weight fraction
  std::vector<std::string> nuclide_names( {"H-1_293.6K"} );

  material.reset( new MonteCarlo::NeutronMaterial( 0,
                                                   -1.0, // mass density (g/cm^3)
                                                   nuclide_map,
                                                   nuclide_fractions,
                                                   nuclide_names ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNeutronMaterial.cpp
//---------------------------------------------------------------------------//
