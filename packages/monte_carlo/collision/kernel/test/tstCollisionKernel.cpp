//---------------------------------------------------------------------------//
//!
//! \file   tstCollisionKernel.cpp
//! \author Alex Robinson
//! \brief  Collision kernel class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_CollisionKernel.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
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

std::string test_scattering_center_database_name;

std::shared_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase>
scattering_center_definition_database;

std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
material_definition_database;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a particle can collide with the cell material
FRENSIE_UNIT_TEST( CollisionKernel, collideWithCellMaterial_neutron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  filled_model.reset( new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );

  // Check analogue mode
  {
    properties->setAnalogueCaptureModeOn();

    MonteCarlo::CollisionKernel collision_kernel( filled_model, *properties );

    FRENSIE_REQUIRE( collision_kernel.isDefinedOnModel( *filled_model ) );

    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );
    neutron.setWeight( 1.0 );

    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( neutron, bank ) );
    FRENSIE_CHECK_LESS_OR_EQUAL( neutron.getEnergy(), 1.0 );
    FRENSIE_CHECK_EQUAL( neutron.getWeight(), 1.0 );
  }

  // Check survival bias mode
  {
    properties->setImplicitCaptureModeOn();

    MonteCarlo::CollisionKernel collision_kernel( filled_model, *properties );

    FRENSIE_REQUIRE( collision_kernel.isDefinedOnModel( *filled_model ) );

    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );
    neutron.setWeight( 1.0 );

    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( neutron, bank ) );
    FRENSIE_CHECK_LESS_OR_EQUAL( neutron.getEnergy(), 1.0 );
    FRENSIE_CHECK_LESS( neutron.getWeight(), 1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a particle can collide with the cell material
FRENSIE_UNIT_TEST( CollisionKernel, collideWithCellMaterial_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  filled_model.reset( new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );

  // Check analogue mode
  {
    properties->setAnalogueCaptureModeOn();

    MonteCarlo::CollisionKernel collision_kernel( filled_model, *properties );

    FRENSIE_REQUIRE( collision_kernel.isDefinedOnModel( *filled_model ) );

    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );
    photon.setWeight( 1.0 );

    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( photon, bank ) );
    FRENSIE_CHECK_LESS_OR_EQUAL( photon.getEnergy(), 1.0 );
    FRENSIE_CHECK_EQUAL( photon.getWeight(), 1.0 );

  }

  // Check survival bias mode
  {
    properties->setImplicitCaptureModeOn();

    MonteCarlo::CollisionKernel collision_kernel( filled_model, *properties );

    FRENSIE_REQUIRE( collision_kernel.isDefinedOnModel( *filled_model ) );

    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );
    photon.setWeight( 1.0 );

    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( photon, bank ) );
    FRENSIE_CHECK_LESS_OR_EQUAL( photon.getEnergy(), 1.0 );
    FRENSIE_CHECK_LESS( photon.getWeight(), 1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a particle can collide with the cell material
FRENSIE_UNIT_TEST( CollisionKernel, collideWithCellMaterial_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ELECTRON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  filled_model.reset( new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );

  // Check analogue mode
  {
    properties->setAnalogueCaptureModeOn();

    MonteCarlo::CollisionKernel collision_kernel( filled_model, *properties );

    FRENSIE_REQUIRE( collision_kernel.isDefinedOnModel( *filled_model ) );

    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );
    electron.setWeight( 1.0 );

    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( electron, bank ) );
    FRENSIE_CHECK_LESS_OR_EQUAL( electron.getEnergy(), 1.0 );
    FRENSIE_CHECK_EQUAL( electron.getWeight(), 1.0 );
  }

  // Check survival bias mode - should be the same as analogue since electrons
  // do not have any absorption reactions
  {
    properties->setImplicitCaptureModeOn();

    MonteCarlo::CollisionKernel collision_kernel( filled_model, *properties );

    FRENSIE_REQUIRE( collision_kernel.isDefinedOnModel( *filled_model ) );

    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );
    electron.setWeight( 1.0 );

    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( electron, bank ) );
    FRENSIE_CHECK_LESS_OR_EQUAL( electron.getEnergy(), 1.0 );
    FRENSIE_CHECK_EQUAL( electron.getWeight(), 1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a particle can collide with the cell material
FRENSIE_UNIT_TEST( CollisionKernel, collideWithCellMaterial_adjoint_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 3, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );
  properties->setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
  properties->setMaxAdjointPhotonEnergy( 20.0 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  filled_model.reset( new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );

  // Check analogue mode
  {
    properties->setAnalogueCaptureModeOn();

    MonteCarlo::CollisionKernel collision_kernel( filled_model, *properties );

    FRENSIE_REQUIRE( collision_kernel.isDefinedOnModel( *filled_model ) );

    std::unique_ptr<MonteCarlo::AdjointPhotonState>
      adjoint_photon( new MonteCarlo::AdjointPhotonState( 1ull ) );

    adjoint_photon->embedInModel( *filled_model );
    adjoint_photon->setEnergy( 1.0 );
    adjoint_photon->setWeight( 1.0 );

    std::unique_ptr<MonteCarlo::ParticleBank>
      bank( new MonteCarlo::ParticleBank );

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( *adjoint_photon, *bank ) );
    FRENSIE_CHECK_GREATER_OR_EQUAL( adjoint_photon->getEnergy(), 1.0 );

    // The adjoint photon's weight will be multiplied by the adjoint weight
    // factor before the collision occurs.
    FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon->getWeight(),
                                     1.8606465722488712,
                                     1e-15 );

    // Sample the pair production reaction
    std::vector<double> fake_stream( 5 );
    fake_stream[0] = 0.99; // select the only photoatom
    fake_stream[1] = 0.05; // select pair production
    fake_stream[2] = 0.0;
    fake_stream[3] = 0.5;
    fake_stream[4] = 0.0;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    adjoint_photon.reset( new MonteCarlo::AdjointPhotonProbeState( 1ull ) );
    adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
    adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
    adjoint_photon->setWeight( 1.0 );
    adjoint_photon->embedInModel( *filled_model );

    bank.reset( new MonteCarlo::ParticleBank );

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( *adjoint_photon, *bank ) );

    FRENSIE_CHECK( adjoint_photon->isGone() );
    FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon->getWeight(),
                                     3.804939079352169351,
                                     1e-15 );
    FRENSIE_REQUIRE_EQUAL( bank->size(), 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank->top().getEnergy(),
                                     2*Utility::PhysicalConstants::electron_rest_mass_energy,
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank->top().getWeight(),
                                     3.804939079352169351,
                                     1e-15 );

    bank->pop();

    // Sample the triplet production reaction
    fake_stream[0] = 0.99; // select the only photoatom
    fake_stream[1] = 0.04;
    fake_stream[2] = 0.0;
    fake_stream[3] = 0.5;
    fake_stream[4] = 0.0;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    adjoint_photon.reset( new MonteCarlo::AdjointPhotonProbeState( 1ull ) );
    adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
    adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
    adjoint_photon->setWeight( 1.0 );
    adjoint_photon->embedInModel( *filled_model );

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( *adjoint_photon, *bank ) );

    FRENSIE_CHECK( adjoint_photon->isGone() );
    FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon->getWeight(),
                                     3.804939079352169351,
                                     1e-15 );
    FRENSIE_REQUIRE_EQUAL( bank->size(), 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank->top().getEnergy(),
                                     4*Utility::PhysicalConstants::electron_rest_mass_energy,
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank->top().getWeight(),
                                     3.804939079352169351,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  // Check survival bias mode - should be the same as analogue mode since
  // adjoint photons have no absorption reactions
  {
    properties->setImplicitCaptureModeOn();

    MonteCarlo::CollisionKernel collision_kernel( filled_model, *properties );

    FRENSIE_REQUIRE( collision_kernel.isDefinedOnModel( *filled_model ) );

    std::unique_ptr<MonteCarlo::AdjointPhotonState>
      adjoint_photon( new MonteCarlo::AdjointPhotonState( 1ull ) );

    adjoint_photon->embedInModel( *filled_model );
    adjoint_photon->setEnergy( 1.0 );
    adjoint_photon->setWeight( 1.0 );

    std::unique_ptr<MonteCarlo::ParticleBank>
      bank( new MonteCarlo::ParticleBank );

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( *adjoint_photon, *bank ) );
    FRENSIE_CHECK_GREATER_OR_EQUAL( adjoint_photon->getEnergy(), 1.0 );

    // The adjoint photon's weight will be multiplied by the adjoint weight
    // factor before the collision occurs.
    FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon->getWeight(),
                                     1.8606465722488712,
                                     1e-15 );

    // Sample the pair production reaction
    std::vector<double> fake_stream( 5 );
    fake_stream[0] = 0.99; // select the only photoatom
    fake_stream[1] = 0.05; // select pair production
    fake_stream[2] = 0.0;
    fake_stream[3] = 0.5;
    fake_stream[4] = 0.0;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    adjoint_photon.reset( new MonteCarlo::AdjointPhotonProbeState( 1ull ) );
    adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
    adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
    adjoint_photon->setWeight( 1.0 );
    adjoint_photon->embedInModel( *filled_model );

    bank.reset( new MonteCarlo::ParticleBank );

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( *adjoint_photon, *bank ) );

    FRENSIE_CHECK( adjoint_photon->isGone() );
    FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon->getWeight(),
                                     3.804939079352169351,
                                     1e-15 );
    FRENSIE_REQUIRE_EQUAL( bank->size(), 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank->top().getEnergy(),
                                     2*Utility::PhysicalConstants::electron_rest_mass_energy,
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank->top().getWeight(),
                                     3.804939079352169351,
                                     1e-15 );

    bank->pop();

    // Sample the triplet production reaction
    fake_stream[0] = 0.99; // select the only photoatom
    fake_stream[1] = 0.04;
    fake_stream[2] = 0.0;
    fake_stream[3] = 0.5;
    fake_stream[4] = 0.0;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    adjoint_photon.reset( new MonteCarlo::AdjointPhotonProbeState( 1ull ) );
    adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
    adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
    adjoint_photon->setWeight( 1.0 );
    adjoint_photon->embedInModel( *filled_model );

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( *adjoint_photon, *bank ) );

    FRENSIE_CHECK( adjoint_photon->isGone() );
    FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon->getWeight(),
                                     3.804939079352169351,
                                     1e-15 );
    FRENSIE_REQUIRE_EQUAL( bank->size(), 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank->top().getEnergy(),
                                     4*Utility::PhysicalConstants::electron_rest_mass_energy,
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank->top().getWeight(),
                                     3.804939079352169351,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that a particle can collide with the cell material
FRENSIE_UNIT_TEST( CollisionKernel, collideWithCellMaterial_adjoint_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 3, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );
  properties->setMaxAdjointElectronEnergy( 20.0 );
  properties->setAdjointElasticModeOff();

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  filled_model.reset( new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );

  // Check analogue mode
  {
    properties->setAnalogueCaptureModeOn();

    MonteCarlo::CollisionKernel collision_kernel( filled_model, *properties );

    FRENSIE_REQUIRE( collision_kernel.isDefinedOnModel( *filled_model ) );

    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );

    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );
    adjoint_electron.setWeight( 1.0 );

    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( adjoint_electron, bank ) );
    FRENSIE_CHECK_GREATER_OR_EQUAL( adjoint_electron.getEnergy(), 1.0 );

    // The adjoint electron's weight will be multiplied by the adjoint weight
    // factor before the collision occurs.
    FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getWeight(),
                                     1.000590048664524723,
                                     1e-15 );

    // Test a collision at max energy
    adjoint_electron.setEnergy( 20.0 );
    adjoint_electron.setWeight( 1.0 );

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( adjoint_electron, bank ) );
    FRENSIE_CHECK_GREATER_OR_EQUAL( adjoint_electron.getEnergy(), 20.0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron.getWeight(), 9.910537998525245085e-01 );
    FRENSIE_CHECK( !adjoint_electron.isGone() );
  }

  // Check survival bias mode
  {
    properties->setImplicitCaptureModeOn();

    MonteCarlo::CollisionKernel collision_kernel( filled_model, *properties );

    FRENSIE_REQUIRE( collision_kernel.isDefinedOnModel( *filled_model ) );

    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );

    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );
    adjoint_electron.setWeight( 1.0 );

    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_kernel.collideWithCellMaterial( adjoint_electron, bank ) );
    FRENSIE_CHECK_GREATER_OR_EQUAL( adjoint_electron.getEnergy(), 1.0 );

    // The adjoint electron's weight will be multiplied by the adjoint weight
    // factor before the collision occurs.
    FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getWeight(),
                                     1.000590048664524723,
                                     1e-15 );
  }
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

    const Data::AtomProperties& si_properties =
      database.getAtomProperties( Data::Si_ATOM );

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

    MonteCarlo::ScatteringCenterDefinition& si_definition =
      scattering_center_definition_database->createDefinition( "Si", Data::Si_ATOM );

    si_definition.setPhotoatomicDataProperties(
          si_properties.getSharedPhotoatomicDataProperties(
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              0 ) );

    si_definition.setAdjointPhotoatomicDataProperties(
          si_properties.getSharedAdjointPhotoatomicDataProperties(
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       0 ) );

    si_definition.setElectroatomicDataProperties(
          si_properties.getSharedElectroatomicDataProperties(
                           Data::ElectroatomicDataProperties::Native_EPR_FILE,
                           0 ) );

    si_definition.setAdjointElectroatomicDataProperties(
          si_properties.getSharedAdjointElectroatomicDataProperties(
                    Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                    0 ) );

    material_definition_database.reset(
                                  new MonteCarlo::MaterialDefinitionDatabase );

    // Set the material definitions
    material_definition_database->addDefinition(
                                               "Water @ 293.6K", 1,
                                               {"H1 @ 293.6K", "O16 @ 293.6K"},
                                               {2.0,           1.0});

    material_definition_database->addDefinition( "H1 @ 293.6K", 2,
                                                 {"H1 @ 293.6K"}, {1.0} );

    material_definition_database->addDefinition( "Si", 3, {"Si"}, {1.0} );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCollisionKernel.cpp
//---------------------------------------------------------------------------//
