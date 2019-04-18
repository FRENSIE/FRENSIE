//---------------------------------------------------------------------------//
//!
//! \file   tstMaterialParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Material particle response function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <fstream>

// FRENSIE Includes
#include "MonteCarlo_MaterialParticleResponseFunction.hpp"
#include "MonteCarlo_PhotonMaterialParticleResponseFunction.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_PhotonState.hpp"
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

std::shared_ptr<const MonteCarlo::FilledGeometryModel> neutron_material_filled_model;
std::shared_ptr<const MonteCarlo::FilledGeometryModel> photon_material_filled_model;
std::shared_ptr<const MonteCarlo::FilledGeometryModel> electron_material_filled_model;
std::shared_ptr<const MonteCarlo::FilledGeometryModel> positron_material_filled_model;
std::shared_ptr<const MonteCarlo::FilledGeometryModel> adjoint_photon_material_filled_model;
std::shared_ptr<const MonteCarlo::FilledGeometryModel> adjoint_electron_material_filled_model;

//---------------------------------------------------------------------------//
// Check if the response function is spatially uniform
FRENSIE_UNIT_TEST( MaterialParticleResponseFunction, isSpatiallyUniform )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    response_function( new MonteCarlo::NeutronMaterialParticleResponseFunction(
                                             neutron_material_filled_model,
                                             1,
                                             MonteCarlo::N__GAMMA_REACTION ) );

  FRENSIE_CHECK( response_function->isSpatiallyUniform() );

  response_function.reset(
            new MonteCarlo::PhotonMaterialParticleResponseFunction(
                          photon_material_filled_model,
                          1,
                          MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );

  FRENSIE_CHECK( response_function->isSpatiallyUniform() );

  response_function.reset(
            new MonteCarlo::ElectronMaterialParticleResponseFunction(
                         electron_material_filled_model,
                         1,
                         MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) );

  FRENSIE_CHECK( response_function->isSpatiallyUniform() );

  response_function.reset(
            new MonteCarlo::PositronMaterialParticleResponseFunction(
                        positron_material_filled_model,
                        1,
                        MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );

  FRENSIE_CHECK( response_function->isSpatiallyUniform() );

  response_function.reset(
            new MonteCarlo::AdjointPhotonMaterialParticleResponseFunction(
                         adjoint_photon_material_filled_model,
                         1,
                         MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  FRENSIE_CHECK( response_function->isSpatiallyUniform() );

  response_function.reset(
       new MonteCarlo::AdjointElectronMaterialParticleResponseFunction(
                 adjoint_electron_material_filled_model,
                 1,
                 MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );

  FRENSIE_CHECK( response_function->isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check that the response function description can be returned
FRENSIE_UNIT_TEST( MaterialParticleResponseFunction, description )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    response_function( new MonteCarlo::NeutronMaterialParticleResponseFunction(
                                             neutron_material_filled_model,
                                             1,
                                             MonteCarlo::N__GAMMA_REACTION ) );

  FRENSIE_CHECK_LESS( response_function->description().find( "cell_1_mat" ),
                      response_function->description().size() );
  FRENSIE_CHECK_LESS( response_function->description().find( Utility::toString( MonteCarlo::N__GAMMA_REACTION ) ),
                      response_function->description().size() );

  response_function.reset(
            new MonteCarlo::PhotonMaterialParticleResponseFunction(
                          photon_material_filled_model,
                          1,
                          MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );

  FRENSIE_CHECK_LESS( response_function->description().find( "cell_1_mat" ),
                      response_function->description().size() );
  FRENSIE_CHECK_LESS( response_function->description().find( Utility::toString( MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) ),
                      response_function->description().size() );

  response_function.reset(
            new MonteCarlo::ElectronMaterialParticleResponseFunction(
                         electron_material_filled_model,
                         1,
                         MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) );

  FRENSIE_CHECK_LESS( response_function->description().find( "cell_1_mat" ),
                      response_function->description().size() );
  FRENSIE_CHECK_LESS( response_function->description().find( Utility::toString( MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) ),
                      response_function->description().size() );

  response_function.reset(
            new MonteCarlo::PositronMaterialParticleResponseFunction(
                        positron_material_filled_model,
                        1,
                        MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );

  FRENSIE_CHECK_LESS( response_function->description().find( "cell_1_mat" ),
                      response_function->description().size() );
  FRENSIE_CHECK_LESS( response_function->description().find( Utility::toString( MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) ),
                      response_function->description().size() );

  response_function.reset(
            new MonteCarlo::AdjointPhotonMaterialParticleResponseFunction(
                         adjoint_photon_material_filled_model,
                         1,
                         MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  FRENSIE_CHECK_LESS( response_function->description().find( "cell_1_mat" ),
                      response_function->description().size() );
  FRENSIE_CHECK_LESS( response_function->description().find( Utility::toString( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) ),
                      response_function->description().size() );

  response_function.reset(
       new MonteCarlo::AdjointElectronMaterialParticleResponseFunction(
                 adjoint_electron_material_filled_model,
                 1,
                 MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );

  FRENSIE_CHECK_LESS( response_function->description().find( "cell_1_mat" ),
                      response_function->description().size() );
  FRENSIE_CHECK_LESS( response_function->description().find( Utility::toString( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) ),
                      response_function->description().size() );
}

//---------------------------------------------------------------------------//
// Check that the response function can be evaluated
FRENSIE_UNIT_TEST( MaterialParticleResponseFunction, evaluate )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    response_function( new MonteCarlo::NeutronMaterialParticleResponseFunction(
                                             neutron_material_filled_model,
                                             1,
                                             MonteCarlo::N__GAMMA_REACTION ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( response_function->evaluate( neutron ),
                                     2.254581767386568063e-06,
                                     1e-15 );
  }

  response_function.reset(
            new MonteCarlo::PhotonMaterialParticleResponseFunction(
                          photon_material_filled_model,
                          1,
                          MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.setEnergy( 4.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( response_function->evaluate( photon ),
                                     1.855849991744731604e-03,
                                     1e-15 );
  }

  FRENSIE_CHECK_THROW( response_function.reset(
                        new MonteCarlo::PhotonMaterialParticleResponseFunction(
                          photon_material_filled_model,
                          1,
                          MonteCarlo::GAMMA__N_REACTION ) ),
                       std::runtime_error );

  response_function.reset(
            new MonteCarlo::ElectronMaterialParticleResponseFunction(
                         electron_material_filled_model,
                         1,
                         MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) );

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( response_function->evaluate( electron ),
                                     5.673817218470100787e-01,
                                     1e-15 );
  }

  response_function.reset(
            new MonteCarlo::PositronMaterialParticleResponseFunction(
                        positron_material_filled_model,
                        1,
                        MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( response_function->evaluate( positron ),
                                     5.673817218470100787e-01,
                                     1e-15 );
  }

  response_function.reset(
            new MonteCarlo::AdjointPhotonMaterialParticleResponseFunction(
                         adjoint_photon_material_filled_model,
                         1,
                         MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( response_function->evaluate( adjoint_photon ),
                                     4.629028371467505184e-06,
                                     1e-15 );
  }

  response_function.reset(
       new MonteCarlo::AdjointElectronMaterialParticleResponseFunction(
                 adjoint_electron_material_filled_model,
                 1,
                 MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( response_function->evaluate( adjoint_electron ),
                                     5.357349256383157066e-01,
                                     1e-15 );
  }
}

//---------------------------------------------------------------------------//
// Check that the response function can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MaterialParticleResponseFunction,
                                   archive_forward,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_forward_material_particle_response_function" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      neutron_response_function( new MonteCarlo::NeutronMaterialParticleResponseFunction(
                                             neutron_material_filled_model,
                                             1,
                                             MonteCarlo::N__GAMMA_REACTION ) );


    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      photon_response_function(
            new MonteCarlo::PhotonMaterialParticleResponseFunction(
                          photon_material_filled_model,
                          1,
                          MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION ) );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      electron_response_function(
            new MonteCarlo::ElectronMaterialParticleResponseFunction(
                         electron_material_filled_model,
                         1,
                         MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      positron_response_function(
            new MonteCarlo::PositronMaterialParticleResponseFunction(
                        positron_material_filled_model,
                        1,
                        MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( neutron_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( photon_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( electron_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( positron_response_function ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    neutron_response_function,
    photon_response_function,
    electron_response_function,
    positron_response_function;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( neutron_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( photon_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( electron_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( positron_response_function ) );

  iarchive.reset();

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( neutron_response_function->evaluate( neutron ),
                                     2.254581767386568063e-06,
                                     1e-15 );
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.setEnergy( 4.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( photon_response_function->evaluate( photon ),
                                     1.855849991744731604e-03,
                                     1e-15 );
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( electron_response_function->evaluate( electron ),
                                     5.673817218470100787e-01,
                                     1e-15 );
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.setEnergy( 1.0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( positron_response_function->evaluate( positron ),
                                     5.673817218470100787e-01,
                                     1e-15 );
  }
}

//---------------------------------------------------------------------------//
// Check that the response function can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MaterialParticleResponseFunction,
                                   archive_adjoint_photon,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_adjoint_photon_material_particle_response_function" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      adjoint_photon_response_function(
            new MonteCarlo::AdjointPhotonMaterialParticleResponseFunction(
                         adjoint_photon_material_filled_model,
                         1,
                         MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( adjoint_photon_response_function ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    adjoint_photon_response_function;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( adjoint_photon_response_function ) );

  iarchive.reset();

  MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
  adjoint_photon.setEnergy( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon_response_function->evaluate( adjoint_photon ),
                                   4.629028371467505184e-06,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the response function can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MaterialParticleResponseFunction,
                                   archive_adjoint_electron,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_adjoint_electron_material_particle_response_function" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      adjoint_electron_response_function(
       new MonteCarlo::AdjointElectronMaterialParticleResponseFunction(
                 adjoint_electron_material_filled_model,
                 1,
                 MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( adjoint_electron_response_function ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    adjoint_electron_response_function;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( adjoint_electron_response_function ) );

  iarchive.reset();

  MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
  adjoint_electron.setEnergy( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron_response_function->evaluate( adjoint_electron ),
                                   5.357349256383157066e-01,
                                   1e-15 );
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
    std::shared_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase>
      scattering_center_definition_database(
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

    // Set the material definitions
    std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
      material_definition_database( new MonteCarlo::MaterialDefinitionDatabase );

    material_definition_database->addDefinition(
                                               "Water @ 293.6K", 1,
                                               {"H1 @ 293.6K", "O16 @ 293.6K"},
                                               {2.0,           1.0});

    material_definition_database->addDefinition( "H1 @ 293.6K", 2,
                                                 {"H1 @ 293.6K"}, {1.0} );

    // Create the neutron material, photon material, electron material and
    // positron material filled model
    std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

    std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

    std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model(
                          new MonteCarlo::FilledGeometryModel(
                                        database_path,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );

    neutron_material_filled_model = filled_model;
    photon_material_filled_model = filled_model;
    electron_material_filled_model = filled_model;
    positron_material_filled_model = filled_model;

    // Create the adjoint photon material filled model
    unfilled_model.reset( new Geometry::InfiniteMediumModel( 1, 2, 1e24/cubic_centimeter ) );

    properties.reset( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

    adjoint_photon_material_filled_model.reset(
                           new MonteCarlo::FilledGeometryModel(
                                        database_path,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );

    // Create the adjoint electron material filled model
    properties.reset( new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );

    adjoint_electron_material_filled_model.reset(
                           new MonteCarlo::FilledGeometryModel(
                                        database_path,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstMaterialParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
