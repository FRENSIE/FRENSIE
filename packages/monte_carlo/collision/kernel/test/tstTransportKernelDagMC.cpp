//---------------------------------------------------------------------------//
//!
//! \file   tstTransportKernel.cpp
//! \author Alex Robinson
//! \brief  Transport kernel class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_TransportKernel.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Geometry_DagMCModel.hpp"
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

std::shared_ptr<const Geometry::Model> unfilled_model;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the simple distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleSimpleDistanceToNextCollisionSite_forward )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
    material_definition_database( new MonteCarlo::MaterialDefinitionDatabase );

  material_definition_database->addDefinition( "Hydrogen @ 293.6K", 1,
                                               {"H1 @ 293.6K"}, {1.0} );

  material_definition_database->addDefinition( "Water @ 293.6K", 2,
                                               {"H1 @ 293.6K", "O16 @ 293.6K"},
                                               {2.0,           1.0} );
  
  material_definition_database->addDefinition( "Oxygen @ 293.6K", 3,
                                               {"O16 @ 293.6K"}, {1.0} );
  
  material_definition_database->addDefinition( "Hydrogen Peroxide @ 293.6K", 4,
                                               {"H1 @ 293.6K", "O16 @ 293.6K"},
                                               {2.0,           1.0} );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  filled_model.reset( new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );


  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.setPosition( 0.0, 0.0, 0.0 );
    neutron.setDirection( 0.0, 0.0, 1.0 );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );
    
    Utility::RandomNumberGenerator::setFakeStream( {0.9797580885541957, 0.9990881180344455} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( neutron ),
                                     1.024728776794096019e+00,
                                     1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( neutron ),
                                     1.839256778861209307e+00,
                                     1e-12 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.setPosition( 0.0, 0.0, 0.0 );
    photon.setDirection( 0.0, 0.0, 1.0 );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );
    
    Utility::RandomNumberGenerator::setFakeStream( {0.20546639749666595, 0.3934693402873666} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( photon ),
                                     1.215755409727326652e+00,
                                     1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( photon ),
                                     2.642946542885493244e+00,
                                     1e-12 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.setPosition( 0.0, 0.0, 0.0 );
    electron.setDirection( 0.0, 0.0, 1.0 );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );
    
    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.75} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( electron ),
                                     3.941252557287573e-06,
                                     1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( electron ),
                                     7.882505114575146e-06,
                                     1e-12 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel, sampleDistanceToNextCollisionSite_forward )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
    material_definition_database( new MonteCarlo::MaterialDefinitionDatabase );

  material_definition_database->addDefinition( "Hydrogen @ 293.6K", 1,
                                               {"H1 @ 293.6K"}, {1.0} );

  material_definition_database->addDefinition( "Water @ 293.6K", 2,
                                               {"H1 @ 293.6K", "O16 @ 293.6K"},
                                               {2.0,           1.0} );
  
  material_definition_database->addDefinition( "Oxygen @ 293.6K", 3,
                                               {"O16 @ 293.6K"}, {1.0} );
  
  material_definition_database->addDefinition( "Hydrogen Peroxide @ 293.6K", 4,
                                               {"H1 @ 293.6K", "O16 @ 293.6K"},
                                               {2.0,           1.0} );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  filled_model.reset( new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );


  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.setPosition( 0.0, 0.0, 0.0 );
    neutron.setDirection( 0.0, 0.0, 1.0 );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );
    
    Utility::RandomNumberGenerator::setFakeStream( {0.9797580885541957, 0.9990881180344455} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( neutron ),
                                     1.169099703417278,
                                     1e-12 );
    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( neutron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.setPosition( 0.0, 0.0, 0.0 );
    photon.setDirection( 0.0, 0.0, 1.0 );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );
    
    Utility::RandomNumberGenerator::setFakeStream( {0.20546639749666595, 0.3934693402873666} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( photon ),
                                     1.5778606640918729,
                                     1e-12 );
    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.setPosition( 0.0, 0.0, 0.0 );
    electron.setDirection( 0.0, 0.0, 1.0 );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );
    
    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.75} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( electron ),
                                     3.941252557287573e-06,
                                     1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( electron ),
                                     7.882505114575146e-06,
                                     1e-12 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the simple distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleSimpleDistanceToNextCollisionSite_adjoint )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

  std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
    material_definition_database( new MonteCarlo::MaterialDefinitionDatabase );

  material_definition_database->addDefinition( 1, {"H1 @ 293.6K"}, {1.0} );

  material_definition_database->addDefinition( 2, {"H1 @ 293.6K"}, {1.0} );
  
  material_definition_database->addDefinition( 3, {"H1 @ 293.6K"}, {1.0} );
  
  material_definition_database->addDefinition( 4, {"H1 @ 293.6K"}, {1.0} );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  filled_model.reset( new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );


  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.setPosition( 0.0, 0.0, 0.0 );
    adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );
    
    Utility::RandomNumberGenerator::setFakeStream( {0.2591817793182821, 0.5506710358827784} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_photon ),
                                     1.584711548994382824e+00,
                                     1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_photon ),
                                     4.225897463985021751e+00,
                                     1e-12 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel, sampleDistanceToNextCollisionSite_adjoint )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

  std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
    material_definition_database( new MonteCarlo::MaterialDefinitionDatabase );

  material_definition_database->addDefinition( 1, {"H1 @ 293.6K"}, {1.0} );

  material_definition_database->addDefinition( 2, {"H1 @ 293.6K"}, {1.0} );
  
  material_definition_database->addDefinition( 3, {"H1 @ 293.6K"}, {1.0} );
  
  material_definition_database->addDefinition( 4, {"H1 @ 293.6K"}, {1.0} );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  filled_model.reset( new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) );


  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.setPosition( 0.0, 0.0, 0.0 );
    adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );
    
    Utility::RandomNumberGenerator::setFakeStream( {0.2591817793182821, 0.5506710358827784} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_photon ),
                                     1.8770673234915742,
                                     1e-12 );
    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_database",
                                        test_scattering_center_database_name, "",
                                        "Test scattering center database name "
                                        "with path" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_cad_file",
                                        test_dagmc_geom_file_name, "",
                                        "Test CAD file name" );
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
  }

  {
    Geometry::DagMCModelProperties
      local_properties( test_dagmc_geom_file_name );

    unfilled_model.reset( new Geometry::DagMCModel( local_properties ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstTransportKernelDagMC.cpp
//---------------------------------------------------------------------------//
