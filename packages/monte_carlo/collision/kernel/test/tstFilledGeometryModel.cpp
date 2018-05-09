//---------------------------------------------------------------------------//
//!
//! \file   tstFilledGeometryModel.cpp
//! \author Alex Robinson
//! \brief  Filled geometry model class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::si::kelvin;
using boost::units::cgs::cubic_centimeter;
using Utility::Units::MeV;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

boost::filesystem::path data_directory;

std::unique_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase>
scattering_center_definition_database;

std::unique_ptr<MonteCarlo::MaterialDefinitionDatabase>
material_definition_database;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_neutron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::NEUTRON_MODE );

  FRENSIE_CHECK_NO_THROW( MonteCarlo::FilledGeometryModel(
                                        data_directory,
                                        *scattering_center_definition_database,
                                        *material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::PHOTON_MODE );

  FRENSIE_CHECK_NO_THROW( MonteCarlo::FilledGeometryModel(
                                        data_directory,
                                        *scattering_center_definition_database,
                                        *material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::ELECTRON_MODE );

  FRENSIE_CHECK_NO_THROW( MonteCarlo::FilledGeometryModel(
                                        data_directory,
                                        *scattering_center_definition_database,
                                        *material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_neutron_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );

  FRENSIE_CHECK_NO_THROW( MonteCarlo::FilledGeometryModel(
                                        data_directory,
                                        *scattering_center_definition_database,
                                        *material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_photon_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::PHOTON_ELECTRON_MODE );

  FRENSIE_CHECK_NO_THROW( MonteCarlo::FilledGeometryModel(
                                        data_directory,
                                        *scattering_center_definition_database,
                                        *material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_neutron_photon_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  FRENSIE_CHECK_NO_THROW( MonteCarlo::FilledGeometryModel(
                                        data_directory,
                                        *scattering_center_definition_database,
                                        *material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_adjoint_neutron_mode )
{

}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_adjoint_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
             new Geometry::InfiniteMediumModel( 1, 2, 1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

  FRENSIE_CHECK_NO_THROW( MonteCarlo::FilledGeometryModel(
                                        data_directory,
                                        *scattering_center_definition_database,
                                        *material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_adjoint_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
             new Geometry::InfiniteMediumModel( 1, 2, 1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );

  FRENSIE_CHECK_NO_THROW( MonteCarlo::FilledGeometryModel(
                                        data_directory,
                                        *scattering_center_definition_database,
                                        *material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_neutron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::NEUTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( data_directory,
                                                *scattering_center_definition_database,
                                                *material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::PHOTON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( data_directory,
                                                *scattering_center_definition_database,
                                                *material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::ELECTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( data_directory,
                                                *scattering_center_definition_database,
                                                *material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_neutron_photon_mode )
{
  
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_photon_electron_mode )
{
  
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_neutron_photon_electron_mode )
{
  
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_adjoint_neutron_mode )
{
  
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_adjoint_photon_mode )
{
  
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_adjoint_electron_mode )
{
  
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
    
    data_directory = database_path.parent_path();

    // Load the database
    const Data::ScatteringCenterPropertiesDatabase database( database_path );

    const Data::AtomProperties& h_properties =
      database.getAtomProperties( 1001 );

    const Data::NuclideProperties& h1_properties =
      database.getNuclideProperties( 1001 );

    const Data::AtomProperties& o_properties =
      database.getAtomProperties( 8016 );

    const Data::NuclideProperties& o16_properties =
      database.getNuclideProperties( 8016 );

    // Set the sattering center definitions
    scattering_center_definition_database.reset(
                          new MonteCarlo::ScatteringCenterDefinitionDatabase );

    MonteCarlo::ScatteringCenterDefinition& h_definition =
      scattering_center_definition_database->createDefinition( "H1 @ 293.6K", 1001 );

    h_definition.setPhotoatomicDataProperties(
          h_properties.getSharedPhotoatomicDataProperties(
                       Data::PhotoatomicDataProperties::Native_EPR_FILE, 0 ) );
    
    h_definition.setAdjointPhotoatomicDataProperties(
          h_properties.getSharedAdjointPhotoatomicDataProperties(
                Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 0 ) );
    
    h_definition.setElectroatomicDataProperties(
          h_properties.getSharedElectroatomicDataProperties(
                     Data::ElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

    h_definition.setAdjointElectroatomicDataProperties(
          h_properties.getSharedAdjointElectroatomicDataProperties(
              Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

    h_definition.setNuclearDataProperties(
          h1_properties.getSharedNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         2.53010E-08*MeV,
                                         true ) );

    MonteCarlo::ScatteringCenterDefinition& o_definition =
      scattering_center_definition_database->createDefinition( "O16 @ 293.6K", 8016 );

    o_definition.setPhotoatomicDataProperties(
          o_properties.getSharedPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::ACE_EPR_FILE, 12 ) );
    
    o_definition.setElectroatomicDataProperties(
          o_properties.getSharedElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::ACE_EPR_FILE, 12 ) );

    o_definition.setNuclearDataProperties(
          o16_properties.getSharedNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         2.53010E-08*MeV,
                                         true ) );

    material_definition_database.reset(
                                  new MonteCarlo::MaterialDefinitionDatabase );

    // Set the material definitions
    material_definition_database->addDefinition(
                                               "Water @ 293.6K", 1,
                                               {"H1 @ 293.6K", "O16 @ 293.6K"},
                                               {2.0,           1.0});
    
    material_definition_database->addDefinition( "H1 @ 293.6K", 2,
                                                 {"H1 @ 293.6K"}, {1.0} );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFilledGeometryModel.cpp
//---------------------------------------------------------------------------//
