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
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::si::kelvin;
using boost::units::cgs::cubic_centimeter;
using Utility::Units::MeV;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_scattering_center_database_name;

std::shared_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase>
scattering_center_definition_database;

std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
material_definition_database;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_neutron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_MODE );

  std::unique_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  FRENSIE_CHECK( &filled_model->getUnfilledModel() == unfilled_model.get() );
  FRENSIE_CHECK( &(const Geometry::Model&)(*filled_model) ==
                 unfilled_model.get() );
  FRENSIE_CHECK( (std::shared_ptr<const Geometry::Model>)(*filled_model) ==
                 unfilled_model );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_MODE );

  std::unique_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  FRENSIE_CHECK( &filled_model->getUnfilledModel() == unfilled_model.get() );
  FRENSIE_CHECK( &(const Geometry::Model&)(*filled_model) ==
                 unfilled_model.get() );
  FRENSIE_CHECK( (std::shared_ptr<const Geometry::Model>)(*filled_model) ==
                 unfilled_model );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ELECTRON_MODE );

  std::unique_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                  new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  FRENSIE_CHECK( &filled_model->getUnfilledModel() == unfilled_model.get() );
  FRENSIE_CHECK( &(const Geometry::Model&)(*filled_model) ==
                 unfilled_model.get() );
  FRENSIE_CHECK( (std::shared_ptr<const Geometry::Model>)(*filled_model) ==
                 unfilled_model );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_neutron_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );

  std::unique_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                 new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  FRENSIE_CHECK( &filled_model->getUnfilledModel() == unfilled_model.get() );
  FRENSIE_CHECK( &(const Geometry::Model&)(*filled_model) ==
                 unfilled_model.get() );
  FRENSIE_CHECK( (std::shared_ptr<const Geometry::Model>)(*filled_model) ==
                 unfilled_model );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_photon_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_ELECTRON_MODE );

  std::unique_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  FRENSIE_CHECK( &filled_model->getUnfilledModel() == unfilled_model.get() );
  FRENSIE_CHECK( &(const Geometry::Model&)(*filled_model) ==
                 unfilled_model.get() );
  FRENSIE_CHECK( (std::shared_ptr<const Geometry::Model>)(*filled_model) ==
                 unfilled_model );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_neutron_photon_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  std::unique_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                              new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  FRENSIE_CHECK( &filled_model->getUnfilledModel() == unfilled_model.get() );
  FRENSIE_CHECK( &(const Geometry::Model&)(*filled_model) ==
                 unfilled_model.get() );
  FRENSIE_CHECK( (std::shared_ptr<const Geometry::Model>)(*filled_model) ==
                 unfilled_model );
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

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

  std::unique_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  FRENSIE_CHECK( &filled_model->getUnfilledModel() == unfilled_model.get() );
  FRENSIE_CHECK( &(const Geometry::Model&)(*filled_model) ==
                 unfilled_model.get() );
  FRENSIE_CHECK( (std::shared_ptr<const Geometry::Model>)(*filled_model) ==
                 unfilled_model );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be constructed
FRENSIE_UNIT_TEST( FilledGeometryModel, constructor_adjoint_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
             new Geometry::InfiniteMediumModel( 1, 2, 1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );

  std::unique_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                 new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  FRENSIE_CHECK( &filled_model->getUnfilledModel() == unfilled_model.get() );
  FRENSIE_CHECK( &(const Geometry::Model&)(*filled_model) ==
                 unfilled_model.get() );
  FRENSIE_CHECK( (std::shared_ptr<const Geometry::Model>)(*filled_model) ==
                 unfilled_model );
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_neutron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( !filled_model.isTerminationCell( 1 ) );

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

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( !filled_model.isTerminationCell( 1 ) );

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

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ELECTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( !filled_model.isTerminationCell( 1 ) );

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
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( !filled_model.isTerminationCell( 1 ) );

  FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::NeutronState>( 1 ) );

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
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_photon_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_ELECTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( !filled_model.isTerminationCell( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::PhotonState>( 1 ) );

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
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_neutron_photon_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( !filled_model.isTerminationCell( 1 ) );

  FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::PhotonState>( 1 ) );

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
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_adjoint_neutron_mode )
{

}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_adjoint_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 2, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( !filled_model.isTerminationCell( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );
}

//---------------------------------------------------------------------------//
// Check if a cell is void
FRENSIE_UNIT_TEST( FilledGeometryModel, isCellVoid_adjoint_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 2, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  FRENSIE_CHECK( !filled_model.isTerminationCell( 1 ) );

  FRENSIE_CHECK( filled_model.isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( filled_model.isCellVoid<MonteCarlo::NeutronState>( 1 ) );

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

  FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( !filled_model.isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( !filled_model.isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( FilledGeometryModel, get_cross_section_neutron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  // Check the neutron cross sections
  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( filled_model );
    neutron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( neutron ),
                       5.565644507161069399e-01,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( neutron ),
                  5.565644507161069399e-01,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       5.565644507161069399e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       5.565644507161069399e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                5.565644507161069399e-01,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( neutron ),
           5.565644507161069399e-01,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      5.565644507161069399e-01,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      5.565644507161069399e-01,
      1e-15 );

    neutron.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( neutron ),
                       1.064473352626745806e-01,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( neutron ),
                  1.064473352626745806e-01,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       1.064473352626745806e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       1.064473352626745806e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                1.064473352626745806e-01,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( neutron ),
           1.064473352626745806e-01,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      1.064473352626745806e-01,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      1.064473352626745806e-01,
      1e-15 );
  }

  // Check the photon cross sections
  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( filled_model );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );

    photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
  }

  // Check the electron cross sections
  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( filled_model );
    electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );

    electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
  }

  // Check the positron cross sections
  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( filled_model );
    positron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );

    positron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint photon cross sections
  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( filled_model );
    adjoint_photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );

    adjoint_photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint electron cross sections
  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( filled_model );
    adjoint_electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );

    adjoint_electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( FilledGeometryModel, get_cross_section_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  // Check the neutron cross sections
  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( filled_model );
    neutron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );

    neutron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
  }

  // Check the photon cross sections
  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( filled_model );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( photon ),
                       7.063503858378371303e-02,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( photon ),
                  7.063503858378371303e-02,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       7.063503858378371303e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       7.063503858378371303e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                7.063503858378371303e-02,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( photon ),
           7.063503858378371303e-02,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      7.063503858378371303e-02,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      7.063503858378371303e-02,
      1e-15 );

    photon.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( photon ),
                       2.213467312742279508e-02,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( photon ),
                  2.213467312742279508e-02,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       2.213467312742279508e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       2.213467312742279508e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                2.213467312742279508e-02,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( photon ),
           2.213467312742279508e-02,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      2.213467312742279508e-02,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      2.213467312742279508e-02,
      1e-15 );
  }

  // Check the electron cross sections
  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( filled_model );
    electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );

    electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
  }

  // Check the positron cross sections
  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( filled_model );
    positron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );

    positron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint photon cross sections
  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( filled_model );
    adjoint_photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );

    adjoint_photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint electron cross sections
  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( filled_model );
    adjoint_electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );

    adjoint_electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( FilledGeometryModel, get_cross_section_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ELECTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  // Check the neutron cross sections
  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( filled_model );
    neutron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );

    neutron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
  }

  // Check the photon cross sections
  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( filled_model );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );

    photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
  }

  // Check the electron cross sections
  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( filled_model );
    electron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( electron ),
                      4.065685841790169070e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( electron ),
                 4.065685841790169070e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       4.065685841790169070e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       4.065685841790169070e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( electron ),
               4.065685841790169070e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( electron ),
          4.065685841790169070e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      4.065685841790169070e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      4.065685841790169070e+04,
      1e-15 );

    electron.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( electron ),
                      2.997884161999163916e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( electron ),
                 2.997884161999163916e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       2.997884161999163916e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       2.997884161999163916e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( electron ),
               2.997884161999163916e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( electron ),
          2.997884161999163916e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      2.997884161999163916e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      2.997884161999163916e+04,
      1e-15 );
  }

  // Check the positron cross sections
  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( filled_model );
    positron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( positron ),
                      4.065685841790115228e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( positron ),
                 4.065685841790115228e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       4.065685841790115228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       4.065685841790115228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( positron ),
               4.065685841790115228e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( positron ),
          4.065685841790115228e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      4.065685841790115228e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      4.065685841790115228e+04,
      1e-15 );

    positron.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( positron ),
                      2.997884161999251228e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( positron ),
                 2.997884161999251228e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       2.997884161999251228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       2.997884161999251228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( positron ),
               2.997884161999251228e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( positron ),
          2.997884161999251228e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      2.997884161999251228e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      2.997884161999251228e+04,
      1e-15 );
  }

  // Check the adjoint photon cross sections
  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( filled_model );
    adjoint_photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );

    adjoint_photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint electron cross sections
  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( filled_model );
    adjoint_electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );

    adjoint_electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( FilledGeometryModel, get_cross_section_neutron_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  // Check the neutron cross sections
  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( filled_model );
    neutron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( neutron ),
                       5.565644507161069399e-01,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( neutron ),
                  5.565644507161069399e-01,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       5.565644507161069399e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       5.565644507161069399e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                5.565644507161069399e-01,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( neutron ),
           5.565644507161069399e-01,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      5.565644507161069399e-01,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      5.565644507161069399e-01,
      1e-15 );

    neutron.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( neutron ),
                       1.064473352626745806e-01,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( neutron ),
                  1.064473352626745806e-01,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       1.064473352626745806e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       1.064473352626745806e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                1.064473352626745806e-01,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( neutron ),
           1.064473352626745806e-01,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      1.064473352626745806e-01,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      1.064473352626745806e-01,
      1e-15 );
  }

  // Check the photon cross sections
  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( filled_model );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( photon ),
                       7.063503858378371303e-02,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( photon ),
                  7.063503858378371303e-02,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       7.063503858378371303e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       7.063503858378371303e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                7.063503858378371303e-02,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( photon ),
           7.063503858378371303e-02,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      7.063503858378371303e-02,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      7.063503858378371303e-02,
      1e-15 );

    photon.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( photon ),
                       2.213467312742279508e-02,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( photon ),
                  2.213467312742279508e-02,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       2.213467312742279508e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       2.213467312742279508e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                2.213467312742279508e-02,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( photon ),
           2.213467312742279508e-02,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      2.213467312742279508e-02,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      2.213467312742279508e-02,
      1e-15 );
  }

  // Check the electron cross sections
  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( filled_model );
    electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );

    electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
  }

  // Check the positron cross sections
  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( filled_model );
    positron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );

    positron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint photon cross sections
  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( filled_model );
    adjoint_photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );

    adjoint_photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint electron cross sections
  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( filled_model );
    adjoint_electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );

    adjoint_electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( FilledGeometryModel, get_cross_section_photon_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_ELECTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  // Check the neutron cross sections
  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( filled_model );
    neutron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );

    neutron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
  }

  // Check the photon cross sections
  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( filled_model );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( photon ),
                       7.063503858378371303e-02,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( photon ),
                  7.063503858378371303e-02,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       7.063503858378371303e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       7.063503858378371303e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                7.063503858378371303e-02,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( photon ),
           7.063503858378371303e-02,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      7.063503858378371303e-02,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      7.063503858378371303e-02,
      1e-15 );

    photon.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( photon ),
                       2.213467312742279508e-02,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( photon ),
                  2.213467312742279508e-02,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       2.213467312742279508e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       2.213467312742279508e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                2.213467312742279508e-02,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( photon ),
           2.213467312742279508e-02,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      2.213467312742279508e-02,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      2.213467312742279508e-02,
      1e-15 );
  }

  // Check the electron cross sections
  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( filled_model );
    electron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( electron ),
                      4.065685841790169070e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( electron ),
                 4.065685841790169070e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       4.065685841790169070e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       4.065685841790169070e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( electron ),
               4.065685841790169070e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( electron ),
          4.065685841790169070e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      4.065685841790169070e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      4.065685841790169070e+04,
      1e-15 );

    electron.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( electron ),
                      2.997884161999163916e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( electron ),
                 2.997884161999163916e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       2.997884161999163916e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       2.997884161999163916e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( electron ),
               2.997884161999163916e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( electron ),
          2.997884161999163916e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      2.997884161999163916e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      2.997884161999163916e+04,
      1e-15 );
  }

  // Check the positron cross sections
  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( filled_model );
    positron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( positron ),
                      4.065685841790115228e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( positron ),
                 4.065685841790115228e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       4.065685841790115228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       4.065685841790115228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( positron ),
               4.065685841790115228e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( positron ),
          4.065685841790115228e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      4.065685841790115228e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      4.065685841790115228e+04,
      1e-15 );

    positron.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( positron ),
                      2.997884161999251228e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( positron ),
                 2.997884161999251228e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       2.997884161999251228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       2.997884161999251228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( positron ),
               2.997884161999251228e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( positron ),
          2.997884161999251228e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      2.997884161999251228e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      2.997884161999251228e+04,
      1e-15 );
  }

  // Check the adjoint photon cross sections
  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( filled_model );
    adjoint_photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );

    adjoint_photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint electron cross sections
  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( filled_model );
    adjoint_electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );

    adjoint_electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( FilledGeometryModel, get_cross_section_neutron_photon_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  // Check the neutron cross sections
  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( filled_model );
    neutron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( neutron ),
                       5.565644507161069399e-01,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( neutron ),
                  5.565644507161069399e-01,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       5.565644507161069399e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       5.565644507161069399e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                5.565644507161069399e-01,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( neutron ),
           5.565644507161069399e-01,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      5.565644507161069399e-01,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      5.565644507161069399e-01,
      1e-15 );

    neutron.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( neutron ),
                       1.064473352626745806e-01,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( neutron ),
                  1.064473352626745806e-01,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       1.064473352626745806e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
       1.064473352626745806e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                1.064473352626745806e-01,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( neutron ),
           1.064473352626745806e-01,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      1.064473352626745806e-01,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::NeutronState>(
                                      neutron.getCell(), neutron.getEnergy() ),
      1.064473352626745806e-01,
      1e-15 );
  }

  // Check the photon cross sections
  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( filled_model );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( photon ),
                       7.063503858378371303e-02,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( photon ),
                  7.063503858378371303e-02,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       7.063503858378371303e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       7.063503858378371303e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                7.063503858378371303e-02,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( photon ),
           7.063503858378371303e-02,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      7.063503858378371303e-02,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      7.063503858378371303e-02,
      1e-15 );

    photon.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getMacroscopicTotalCrossSection( photon ),
                       2.213467312742279508e-02,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getMacroscopicTotalCrossSectionQuick( photon ),
                  2.213467312742279508e-02,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       2.213467312742279508e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
       2.213467312742279508e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                2.213467312742279508e-02,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalForwardCrossSectionQuick( photon ),
           2.213467312742279508e-02,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      2.213467312742279508e-02,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PhotonState>(
                                      photon.getCell(), photon.getEnergy() ),
      2.213467312742279508e-02,
      1e-15 );
  }

  // Check the electron cross sections
  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( filled_model );
    electron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( electron ),
                      4.065685841790169070e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( electron ),
                 4.065685841790169070e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       4.065685841790169070e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       4.065685841790169070e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( electron ),
               4.065685841790169070e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( electron ),
          4.065685841790169070e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      4.065685841790169070e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      4.065685841790169070e+04,
      1e-15 );

    electron.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( electron ),
                      2.997884161999163916e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( electron ),
                 2.997884161999163916e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       2.997884161999163916e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
       2.997884161999163916e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( electron ),
               2.997884161999163916e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( electron ),
          2.997884161999163916e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      2.997884161999163916e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::ElectronState>(
                                    electron.getCell(), electron.getEnergy() ),
      2.997884161999163916e+04,
      1e-15 );
  }

  // Check the positron cross sections
  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( filled_model );
    positron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( positron ),
                      4.065685841790115228e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( positron ),
                 4.065685841790115228e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       4.065685841790115228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       4.065685841790115228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( positron ),
               4.065685841790115228e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( positron ),
          4.065685841790115228e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      4.065685841790115228e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      4.065685841790115228e+04,
      1e-15 );

    positron.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                      filled_model.getMacroscopicTotalCrossSection( positron ),
                      2.997884161999251228e+04,
                      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                 filled_model.getMacroscopicTotalCrossSectionQuick( positron ),
                 2.997884161999251228e+04,
                 1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       2.997884161999251228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
       2.997884161999251228e+04,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
               filled_model.getMacroscopicTotalForwardCrossSection( positron ),
               2.997884161999251228e+04,
               1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getMacroscopicTotalForwardCrossSectionQuick( positron ),
          2.997884161999251228e+04,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      2.997884161999251228e+04,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::PositronState>(
                                    positron.getCell(), positron.getEnergy() ),
      2.997884161999251228e+04,
      1e-15 );
  }

  // Check the adjoint photon cross sections
  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( filled_model );
    adjoint_photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );

    adjoint_photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint electron cross sections
  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( filled_model );
    adjoint_electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );

    adjoint_electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( FilledGeometryModel, get_cross_section_adjoint_neutron_mode )
{

}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( FilledGeometryModel, get_cross_section_adjoint_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 2, 1e24/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );
  properties->setMaxAdjointPhotonEnergy( 20.0 );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  // Check the neutron cross sections
  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( filled_model );
    neutron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );

    neutron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
  }

  // Check the photon cross sections
  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( filled_model );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );

    photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
  }

  // Check the electron cross sections
  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( filled_model );
    electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );

    electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
  }

  // Check the positron cross sections
  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( filled_model );
    positron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );

    positron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint photon cross sections
  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( filled_model );
    adjoint_photon.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
           3.898546934741942138e-01,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalCrossSectionQuick( adjoint_photon ),
           3.898546934741942138e-01,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
       3.898546934741942138e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
       3.898546934741942138e-01,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
         filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
         2.112255390180249326e-01,
         1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
         filled_model.getMacroscopicTotalForwardCrossSectionQuick( adjoint_photon ),
         2.112255390180249326e-01,
         1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
      2.112255390180249326e-01,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
      2.112255390180249326e-01,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                         filled_model.getAdjointWeightFactor( adjoint_photon ),
                         1.845679718875878672e+00,
                         1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                    filled_model.getAdjointWeightFactorQuick( adjoint_photon ),
                    1.845679718875878672e+00,
                    1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getAdjointWeightFactor<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
          1.845679718875878672e+00,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getAdjointWeightFactorQuick<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
      1.845679718875878672e+00,
      1e-15 );

    adjoint_photon.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                1.332400408475752779e-02,
                1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalCrossSectionQuick( adjoint_photon ),
           1.332400408475752779e-02,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
       1.332400408475752779e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
       1.332400408475752779e-02,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
         filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
         5.430040110435463419e-02,
         1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
         filled_model.getMacroscopicTotalForwardCrossSectionQuick( adjoint_photon ),
         5.430040110435463419e-02,
         1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
      5.430040110435463419e-02,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
      5.430040110435463419e-02,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                         filled_model.getAdjointWeightFactor( adjoint_photon ),
                         2.453757949071393996e-01,
                         1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                    filled_model.getAdjointWeightFactorQuick( adjoint_photon ),
                    2.453757949071393996e-01,
                    1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
          filled_model.getAdjointWeightFactor<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
          2.453757949071393996e-01,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getAdjointWeightFactorQuick<MonteCarlo::AdjointPhotonState>(
                        adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
      2.453757949071393996e-01,
      1e-15 );

    const std::vector<double>& critical_line_energies =
      filled_model.getCriticalLineEnergies<MonteCarlo::AdjointPhotonState>();

    FRENSIE_REQUIRE_EQUAL( critical_line_energies.size(), 1 );
    FRENSIE_CHECK_EQUAL( critical_line_energies[0],
                         Utility::PhysicalConstants::electron_rest_mass_energy );
  }

  // Check the adjoint electron cross sections
  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( filled_model );
    adjoint_electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getAdjointWeightFactor( adjoint_electron ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getAdjointWeightFactor<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         1.0 );

    adjoint_electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getAdjointWeightFactor( adjoint_electron ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getAdjointWeightFactor<MonteCarlo::AdjointElectronState>( adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
                         1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
FRENSIE_UNIT_TEST( FilledGeometryModel, get_cross_section_adjoint_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
           new Geometry::InfiniteMediumModel( 1, 2, 1.e24/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );

  MonteCarlo::FilledGeometryModel filled_model( test_scattering_center_database_name,
                                                scattering_center_definition_database,
                                                material_definition_database,
                                                properties,
                                                unfilled_model,
                                                true );

  // Check the neutron cross sections
  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( filled_model );
    neutron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );

    neutron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( neutron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::NeutronState>( neutron.getCell(), neutron.getEnergy() ),
                         0.0 );
  }

  // Check the photon cross sections
  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( filled_model );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );

    photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PhotonState>( photon.getCell(), photon.getEnergy() ),
                         0.0 );
  }

  // Check the electron cross sections
  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( filled_model );
    electron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );

    electron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( electron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::ElectronState>( electron.getCell(), electron.getEnergy() ),
                         0.0 );
  }

  // Check the positron cross sections
  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( filled_model );
    positron.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );

    positron.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( positron ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::PositronState>( positron.getCell(), positron.getEnergy() ),
                         0.0 );
  }

  // Check the adjoint photon cross sections
  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( filled_model );
    adjoint_photon.setEnergy( 1.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getAdjointWeightFactor( adjoint_photon ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getAdjointWeightFactor<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         1.0 );

    adjoint_photon.setEnergy( 10.0 );

    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection( adjoint_photon ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         0.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getAdjointWeightFactor( adjoint_photon ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( filled_model.getAdjointWeightFactor<MonteCarlo::AdjointPhotonState>( adjoint_photon.getCell(), adjoint_photon.getEnergy() ),
                         1.0 );
  }

  // Check the adjoint electron cross sections
  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( filled_model );
    adjoint_electron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
           filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
           1.962547578714210249e+05,
           1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
         filled_model.getMacroscopicTotalCrossSectionQuick( adjoint_electron ),
         1.962547578714210249e+05,
         1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>(
                    adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
       1.962547578714210249e+05,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::AdjointElectronState>(
                    adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
       1.962547578714210249e+05,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
       1.962264560274902324e+05,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalForwardCrossSectionQuick( adjoint_electron ),
       1.962264560274902324e+05,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>(
                    adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
      1.962264560274902324e+05,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::AdjointElectronState>(
                    adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
      1.962264560274902324e+05,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getAdjointWeightFactor( adjoint_electron ),
      1.000144230520714439,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getAdjointWeightFactorQuick( adjoint_electron ),
      1.000144230520714439,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getAdjointWeightFactor<MonteCarlo::AdjointElectronState>(
                adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
      1.000144230520714439,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getAdjointWeightFactorQuick<MonteCarlo::AdjointElectronState>(
                    adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
      1.000144230520714439,
      1e-15 );

    adjoint_electron.setEnergy( 10.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalCrossSection( adjoint_electron ),
      1.782038552051321312e+05,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalCrossSectionQuick( adjoint_electron ),
      1.782038552051321312e+05,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalCrossSection<MonteCarlo::AdjointElectronState>(
                  adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
      1.782038552051321312e+05,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalCrossSectionQuick<MonteCarlo::AdjointElectronState>(
                  adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
      1.782038552051321312e+05,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalForwardCrossSection( adjoint_electron ),
       1.781250859381078626e+05,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
       filled_model.getMacroscopicTotalForwardCrossSectionQuick( adjoint_electron ),
       1.781250859381078626e+05,
       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSection<MonteCarlo::AdjointElectronState>(
                    adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
      1.781250859381078626e+05,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getMacroscopicTotalForwardCrossSectionQuick<MonteCarlo::AdjointElectronState>(
                    adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
      1.781250859381078626e+05,
      1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                       filled_model.getAdjointWeightFactor( adjoint_electron ),
                       1.000442213215558152,
                       1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
                  filled_model.getAdjointWeightFactorQuick( adjoint_electron ),
                  1.000442213215558152,
                  1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
         filled_model.getAdjointWeightFactor<MonteCarlo::AdjointElectronState>(
                    adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
         1.000442213215558152,
          1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY(
      filled_model.getAdjointWeightFactorQuick<MonteCarlo::AdjointElectronState>(
                    adjoint_electron.getCell(), adjoint_electron.getEnergy() ),
      1.000442213215558152,
      1e-15 );

    const std::vector<double>& critical_line_energies =
      filled_model.getCriticalLineEnergies<MonteCarlo::AdjointElectronState>();

    FRENSIE_REQUIRE_EQUAL( critical_line_energies.size(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( FilledGeometryModel,
                                   archive_neutron_mode,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_filled_geometry_model_neutron_mode" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

    std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::NEUTRON_MODE );

    std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model(
                                 new MonteCarlo::FilledGeometryModel(
                                         test_scattering_center_database_name,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );

    //FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model ) );
    (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  Utility::JustInTimeInitializer::getInstance().activate();

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( filled_model ) );

  iarchive.reset();

  FRENSIE_REQUIRE( !filled_model->isInitialized() );

  FRENSIE_REQUIRE_EQUAL( Utility::JustInTimeInitializer::getInstance().getNumberOfObjects(), 1 );

  FRENSIE_REQUIRE_NO_THROW( Utility::JustInTimeInitializer::getInstance().initializeObjectsAndClear() );

  FRENSIE_REQUIRE( filled_model->isInitialized() );

  FRENSIE_CHECK( !filled_model->isTerminationCell( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );

  Utility::JustInTimeInitializer::getInstance().deactivate();
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( FilledGeometryModel,
                                   archive_photon_mode,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_filled_geometry_model_photon_mode" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

    std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_MODE );

    std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model(
                                 new MonteCarlo::FilledGeometryModel(
                                         test_scattering_center_database_name,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );

    //FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model ) );
    (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( filled_model ) );

  iarchive.reset();

  FRENSIE_REQUIRE( filled_model->isInitialized() );

  FRENSIE_CHECK( !filled_model->isTerminationCell( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( FilledGeometryModel,
                                   archive_electron_mode,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_filled_geometry_model_electron_mode" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

    std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::ELECTRON_MODE );

    std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model(
                                 new MonteCarlo::FilledGeometryModel(
                                         test_scattering_center_database_name,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );

    //FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model ) );
    (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  Utility::JustInTimeInitializer::getInstance().activate();

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( filled_model ) );

  iarchive.reset();

  FRENSIE_REQUIRE( !filled_model->isInitialized() );

  FRENSIE_REQUIRE_EQUAL( Utility::JustInTimeInitializer::getInstance().getNumberOfObjects(), 1 );

  FRENSIE_REQUIRE_NO_THROW( Utility::JustInTimeInitializer::getInstance().initializeObjectsAndClear() );

  FRENSIE_REQUIRE( filled_model->isInitialized() );

  FRENSIE_CHECK( !filled_model->isTerminationCell( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );

  Utility::JustInTimeInitializer::getInstance().deactivate();
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( FilledGeometryModel,
                                   archive_neutron_photon_mode,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_filled_geometry_model_neutron_photon_mode" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

    std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );

    std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model(
                                 new MonteCarlo::FilledGeometryModel(
                                         test_scattering_center_database_name,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );

    //FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model ) );
    (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  Utility::JustInTimeInitializer::getInstance().activate();

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( filled_model ) );

  iarchive.reset();

  FRENSIE_REQUIRE( !filled_model->isInitialized() );

  FRENSIE_REQUIRE_EQUAL( Utility::JustInTimeInitializer::getInstance().getNumberOfObjects(), 1 );

  FRENSIE_REQUIRE_NO_THROW( Utility::JustInTimeInitializer::getInstance().initializeObjectsAndClear() );

  FRENSIE_REQUIRE( filled_model->isInitialized() );

  FRENSIE_CHECK( !filled_model->isTerminationCell( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );

  Utility::JustInTimeInitializer::getInstance().deactivate();
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( FilledGeometryModel,
                                   archive_photon_electron_mode,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_filled_geometry_model_photon_electron_mode" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

    std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_ELECTRON_MODE );

    std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model(
                                 new MonteCarlo::FilledGeometryModel(
                                         test_scattering_center_database_name,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );

    //FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model ) );
    (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  Utility::JustInTimeInitializer::getInstance().activate();

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( filled_model ) );

  iarchive.reset();

  FRENSIE_REQUIRE( !filled_model->isInitialized() );

  FRENSIE_REQUIRE_EQUAL( Utility::JustInTimeInitializer::getInstance().getNumberOfObjects(), 1 );

  FRENSIE_REQUIRE_NO_THROW( Utility::JustInTimeInitializer::getInstance().initializeObjectsAndClear() );

  FRENSIE_REQUIRE( filled_model->isInitialized() );

  FRENSIE_CHECK( !filled_model->isTerminationCell( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );

  Utility::JustInTimeInitializer::getInstance().deactivate();
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( FilledGeometryModel,
                                   archive_neutron_photon_electron_mode,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_filled_geometry_model_neutron_photon_electron_mode" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

    std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

    std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model(
                                 new MonteCarlo::FilledGeometryModel(
                                         test_scattering_center_database_name,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );

    //FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model ) );
    (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  Utility::JustInTimeInitializer::getInstance().activate();

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( filled_model ) );

  iarchive.reset();

  FRENSIE_REQUIRE( !filled_model->isInitialized() );

  FRENSIE_REQUIRE_EQUAL( Utility::JustInTimeInitializer::getInstance().getNumberOfObjects(), 1 );

  FRENSIE_REQUIRE_NO_THROW( Utility::JustInTimeInitializer::getInstance().initializeObjectsAndClear() );

  FRENSIE_REQUIRE( filled_model->isInitialized() );

  FRENSIE_CHECK( !filled_model->isTerminationCell( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );

  Utility::JustInTimeInitializer::getInstance().deactivate();
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( FilledGeometryModel,
                                   archive_adjoint_neutron_mode,
                                   TestArchives )
{

}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( FilledGeometryModel,
                                   archive_adjoint_photon_mode,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_filled_geometry_adjoint_photon_mode" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 2, -1.0/cubic_centimeter ) );

    std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

    std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model(
                                 new MonteCarlo::FilledGeometryModel(
                                         test_scattering_center_database_name,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );

    //FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model ) );
    (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  Utility::JustInTimeInitializer::getInstance().activate();

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( filled_model ) );

  iarchive.reset();

  FRENSIE_REQUIRE( !filled_model->isInitialized() );

  FRENSIE_REQUIRE_EQUAL( Utility::JustInTimeInitializer::getInstance().getNumberOfObjects(), 1 );

  FRENSIE_REQUIRE_NO_THROW( Utility::JustInTimeInitializer::getInstance().initializeObjectsAndClear() );

  FRENSIE_REQUIRE( filled_model->isInitialized() );

  FRENSIE_CHECK( !filled_model->isTerminationCell( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );

  Utility::JustInTimeInitializer::getInstance().deactivate();
}

//---------------------------------------------------------------------------//
// Check that a filled geometry model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( FilledGeometryModel,
                                   archive_adjoint_electron_mode,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_filled_geometry_adjoint_electron_mode" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 2, -1.0/cubic_centimeter ) );

    std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );

    std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model(
                                 new MonteCarlo::FilledGeometryModel(
                                         test_scattering_center_database_name,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );

    //FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model ) );
    (*oarchive) << BOOST_SERIALIZATION_NVP( filled_model );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  Utility::JustInTimeInitializer::getInstance().activate();

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( filled_model ) );

  iarchive.reset();

  FRENSIE_REQUIRE( !filled_model->isInitialized() );

  FRENSIE_REQUIRE_EQUAL( Utility::JustInTimeInitializer::getInstance().getNumberOfObjects(), 1 );

  FRENSIE_REQUIRE_NO_THROW( Utility::JustInTimeInitializer::getInstance().initializeObjectsAndClear() );

  FRENSIE_REQUIRE( filled_model->isInitialized() );

  FRENSIE_CHECK( !filled_model->isTerminationCell( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::NeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::PhotonState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::ElectronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::PositronState>( 1 ) );

  // FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_NEUTRON ) );
  // FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointNeutronState>( 1 ) );

  FRENSIE_CHECK( filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( filled_model->isCellVoid<MonteCarlo::AdjointPhotonState>( 1 ) );

  FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_ELECTRON ) );
  FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::AdjointElectronState>( 1 ) );

  // FRENSIE_CHECK( !filled_model->isCellVoid( 1, MonteCarlo::ADJOINT_POSITRON ) );
  // FRENSIE_CHECK( !filled_model->isCellVoid<MonteCarlo::AdjointPositronState>( 1 ) );

  Utility::JustInTimeInitializer::getInstance().deactivate();
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

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
