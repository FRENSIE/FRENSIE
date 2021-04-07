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
#include "MonteCarlo_StandardParticleSimulationManager.hpp"
#include "MonteCarlo_BatchedDistributedStandardParticleSimulationManager.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_StandardParticleSourceComponent.hpp"
#include "MonteCarlo_StandardAdjointParticleSourceComponent.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_GlobalMPISession.hpp"
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

std::shared_ptr<const Geometry::Model> unfilled_model;

std::shared_ptr<const MonteCarlo::ParticleDistribution> particle_distribution;

std::shared_ptr<MonteCarlo::PopulationControl> population_controller;
std::shared_ptr<const MonteCarlo::CollisionForcer> collision_forcer;

int threads;

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
                                        test_scattering_center_database_name,
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

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );

  FRENSIE_REQUIRE_NO_THROW( factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "h5fa",
                                                              threads ) ) );

  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "h5fa" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), threads );

  Utility::OpenMPProperties::setNumberOfThreads( 1 );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory, constructor_photon_mode )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        false ) );
  
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  {
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      source_component( new MonteCarlo::StandardPhotonSourceComponent(
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

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );

  FRENSIE_REQUIRE_NO_THROW( factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "h5fa",
                                                              threads ) ) );

  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "h5fa" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), threads );

  Utility::OpenMPProperties::setNumberOfThreads( 1 );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory, constructor_electron_mode )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ELECTRON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        false ) );
  
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  {
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      source_component( new MonteCarlo::StandardElectronSourceComponent(
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

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );

  FRENSIE_REQUIRE_NO_THROW( factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "h5fa",
                                                              threads ) ) );

  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "h5fa" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), threads );

  Utility::OpenMPProperties::setNumberOfThreads( 1 );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_neutron_photon_mode )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
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

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );

  FRENSIE_REQUIRE_NO_THROW( factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "h5fa",
                                                              threads ) ) );

  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "h5fa" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), threads );

  Utility::OpenMPProperties::setNumberOfThreads( 1 );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_photon_electron_mode )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_ELECTRON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        false ) );
  
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  {
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      source_component( new MonteCarlo::StandardPhotonSourceComponent(
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

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::PHOTON_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::PHOTON_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::PHOTON_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::PHOTON_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );

  FRENSIE_REQUIRE_NO_THROW( factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "h5fa",
                                                              threads ) ) );

  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::PHOTON_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::PHOTON_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::PHOTON_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::PHOTON_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "h5fa" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), threads );

  Utility::OpenMPProperties::setNumberOfThreads( 1 );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_neutron_photon_electron_mode )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
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

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );

  FRENSIE_REQUIRE_NO_THROW( factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "h5fa",
                                                              threads ) ) );

  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "h5fa" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), threads );

  Utility::OpenMPProperties::setNumberOfThreads( 1 );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_adjoint_photon_mode )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        false ) );
  
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  {
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      source_component( new MonteCarlo::StandardAdjointPhotonSourceComponent(
                                                     0,
                                                     1.0,
                                                     model,
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

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ADJOINT_PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ADJOINT_PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ADJOINT_PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ADJOINT_PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );

  FRENSIE_REQUIRE_NO_THROW( factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "h5fa",
                                                              threads ) ) );

  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ADJOINT_PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ADJOINT_PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ADJOINT_PHOTON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ADJOINT_PHOTON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "h5fa" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), threads );

  Utility::OpenMPProperties::setNumberOfThreads( 1 );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_adjoint_electron_mode )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        false ) );
  
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  {
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      source_component( new MonteCarlo::StandardAdjointElectronSourceComponent(
                                                     0,
                                                     1.0,
                                                     model,
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

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ADJOINT_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ADJOINT_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ADJOINT_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ADJOINT_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );

  FRENSIE_REQUIRE_NO_THROW( factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "h5fa",
                                                              threads ) ) );

  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ADJOINT_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::ADJOINT_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ADJOINT_ELECTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::ADJOINT_ELECTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "h5fa" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), threads );

  Utility::OpenMPProperties::setNumberOfThreads( 1 );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed and
// weight windows can be set
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_set_population_controller )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
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

  factory->setPopulationControl( population_controller );

  FRENSIE_CHECK_EQUAL( population_controller.use_count(), 2 );

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );
  FRENSIE_CHECK_EQUAL( population_controller.use_count(), 3 );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed and
// a collision forcer can be set
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_set_collision_forcer )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
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

  factory->setCollisionForcer( collision_forcer );

  FRENSIE_CHECK_EQUAL( collision_forcer.use_count(), 2 );

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );
  FRENSIE_CHECK_EQUAL( collision_forcer.use_count(), 3 );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager factory can be constructed and
// both weight windows and a collision forcer can be set
FRENSIE_UNIT_TEST( ParticleSimulationManagerFactory,
                   constructor_set_population_controller_collision_forcer )
{
  std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_MODE );
  properties->setNumberOfHistories( 5 );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model(
                               new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
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

  factory->setPopulationControl( population_controller );
  factory->setCollisionForcer( collision_forcer );

  FRENSIE_CHECK_EQUAL( population_controller.use_count(), 2 );
  FRENSIE_CHECK_EQUAL( collision_forcer.use_count(), 2 );

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;
  
  FRENSIE_REQUIRE_NO_THROW( manager = factory->getManager() );

  if( Utility::GlobalMPISession::size() == 1 )
  {
    std::shared_ptr<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }
  else
  {
    std::shared_ptr<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::BatchedDistributedStandardParticleSimulationManager<MonteCarlo::NEUTRON_MODE> >( manager );
    
    FRENSIE_CHECK( true_manager.get() != NULL );
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "simulation" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );
  FRENSIE_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );
  FRENSIE_CHECK_EQUAL( population_controller.use_count(), 3 );
  FRENSIE_CHECK_EQUAL( collision_forcer.use_count(), 3 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

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
    
    // Load the database
    const Data::ScatteringCenterPropertiesDatabase database( database_path );

    const Data::AtomProperties& h_properties =
      database.getAtomProperties( 1001 );

    const Data::NuclideProperties& h1_properties =
      database.getNuclideProperties( 1001 );

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

    material_definition_database.reset(
                                  new MonteCarlo::MaterialDefinitionDatabase );

    material_definition_database->addDefinition( "H1 @ 293.6K", 1,
                                                 {"H1 @ 293.6K"}, {1.0} );
  }

  unfilled_model.reset(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  {
    std::shared_ptr<MonteCarlo::StandardParticleDistribution>
      tmp_particle_distribution( new MonteCarlo::StandardParticleDistribution( "test dist" ) );
    tmp_particle_distribution->constructDimensionDistributionDependencyTree();
    
    particle_distribution = tmp_particle_distribution;
  }                              

  population_controller = MonteCarlo::PopulationControl::getDefault();
 
  collision_forcer = MonteCarlo::CollisionForcer::getDefault();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstParticleSimulationManagerFactory.cpp
//---------------------------------------------------------------------------//

