//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSimulationManagerFactory.cpp
//! \author Alex Robinson
//! \brief  The particle simulation manager factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_StandardParticleSourceComponent.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_GlobalMPISession.hpp"
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

boost::filesystem::path data_directory;

std::shared_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase>
scattering_center_definition_database;

std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
material_definition_database;

std::shared_ptr<const Geometry::Model> unfilled_model;

std::shared_ptr<const MonteCarlo::ParticleDistribution> particle_distribution;

std::shared_ptr<const MonteCarlo::WeightWindow> weight_windows;
std::shared_ptr<const MonteCarlo::CollisionForcer> collision_forcer;

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory, constructor_neutron_mode )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        data_directory,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        false ) );
  
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  {
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      source_component( new MonteCarlo::StandardNeutronSourceComponent(
                                                     0,
                                                     1.0,
                                                     unfilled_model,
                                                     particle_distribution ) );

    source.reset( new MonteCarlo::StandardParticleSource( {source_component} ) );
  }
  
  std::shared_ptr<MonteCarlo::EventHandler> event_handler(
                                 new MonteCarlo::EventHandler( *properties ) );

  std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory;

  FRENSIE_REQUIRE_NO_THROW( factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties ) ) );
  
  
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed and
// weight windows can be set
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_set_weight_windows )
{

}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed and
// a collision forcer can be set
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_set_collision_forcer )
{

}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed and
// both weight windows and a collision forcer can be set
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_set_weight_windows_collision_forcer )
{

}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be archived
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory, restart_basic )
{

}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be archived
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory, restart_add_histories )
{

}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be archived
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory, restart_new_wall_time )
{

}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be archived
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   restart_add_histories_new_wall_time )
{

}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can rename the simulation
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory, renameSimulation )
{

}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can change the archive
// type
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   changeSimulationArchiveType )
{

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_scattering_center_database_name;
int threads;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_database",
                                        test_scattering_center_database_name, "",
                                        "Test scattering center database name "
                                        "with path" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
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

    material_definition_database.reset(
                                  new MonteCarlo::MaterialDefinitionDatabase );

    material_definition_database->addDefinition( "H1 @ 293.6K", 1,
                                                 {"H1 @ 293.6K"}, {1.0} );
  }

  unfilled_model.reset(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  {
    std::shared_ptr<MonteCarlo::ParticleDistribution>
      tmp_particle_distribution( new MonteCarlo::StandardParticleDistribution() );
    tmp_particle_distribution->constructDimensionDistributionDependencyTree();
    
    particle_distribution = tmp_particle_distribution;
  }                              

  weight_windows = MonteCarlo::WeightWindow::getDefault();
 
  collision_forcer = MonteCarlo::CollisionForcer::getDefault();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstParticleSimulationManagerFactory.cpp
//---------------------------------------------------------------------------//

