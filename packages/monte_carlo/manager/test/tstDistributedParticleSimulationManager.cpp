//---------------------------------------------------------------------------//
//!
//! \file   tstDistributedParticleSimulationManager.cpp
//! \author Alex Robinson
//! \brief  The distributed particle simulation manager unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_StandardParticleSourceComponent.hpp"
#include "MonteCarlo_StandardAdjointParticleSourceComponent.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"
#include "FRENSIE_config.hpp"


// test
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

int threads;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that history details can be returned
FRENSIE_UNIT_TEST( ParticleSimulationManager, get_history_details )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );
    properties->setNumberOfHistories( (Utility::GlobalMPISession::size()-1)*5 );

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  FRENSIE_CHECK_EQUAL( manager->getNextHistory(), 0 );
  FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), 0 );
  FRENSIE_CHECK_EQUAL( manager->getRendezvousBatchSize(),
                       (Utility::GlobalMPISession::size()-1)*5 );
  FRENSIE_CHECK_EQUAL( manager->getBatchSize(), 5 );

  manager.reset();

  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );
    properties->setNumberOfHistories( (Utility::GlobalMPISession::size()-1)*10 );
    properties->setMinNumberOfRendezvous( 2 );

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  FRENSIE_CHECK_EQUAL( manager->getNextHistory(), 0 );
  FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), 0 );
  FRENSIE_CHECK_EQUAL( manager->getRendezvousBatchSize(),
                       (Utility::GlobalMPISession::size()-1)*5 );
  FRENSIE_CHECK_EQUAL( manager->getBatchSize(), 5 );

  manager.reset();

  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );
    properties->setNumberOfHistories( (Utility::GlobalMPISession::size()-1)*100 );
    properties->setMinNumberOfRendezvous( 2 );
    properties->setMaxRendezvousBatchSize( (Utility::GlobalMPISession::size()-1)*10 );

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  FRENSIE_CHECK_EQUAL( manager->getNextHistory(), 0 );
  FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), 0 );
  FRENSIE_CHECK_EQUAL( manager->getRendezvousBatchSize(),
                       (Utility::GlobalMPISession::size()-1)*10 );
  FRENSIE_CHECK_EQUAL( manager->getBatchSize(), 10 );

  manager.reset();

  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );
    properties->setNumberOfHistories( (Utility::GlobalMPISession::size()-1)*100 );
    properties->setMinNumberOfRendezvous( 2 );
    properties->setMaxRendezvousBatchSize( (Utility::GlobalMPISession::size()-1)*10 );
    properties->setNumberOfBatchesPerProcessor( 2 );

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  FRENSIE_CHECK_EQUAL( manager->getNextHistory(), 0 );
  FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), 0 );
  FRENSIE_CHECK_EQUAL( manager->getRendezvousBatchSize(),
                       (Utility::GlobalMPISession::size()-1)*10 );
  FRENSIE_CHECK_EQUAL( manager->getBatchSize(), 5 );

  manager.reset();
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager can rename the simulation
FRENSIE_UNIT_TEST( ParticleSimulationManager, setSimulationName )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
    manager->useMultipleRendezvousFiles();
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim" );

  manager->setSimulationName( "test_sim_2" );

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim_2" );
  FRENSIE_CHECK( boost::filesystem::exists( "test_sim_2_rendezvous_0.xml" ) );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager can change the archive
// type
FRENSIE_UNIT_TEST( ParticleSimulationManager, setSimulationArchiveType )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
    manager->useMultipleRendezvousFiles();
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );

  manager->setSimulationArchiveType( "txt" );

  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "txt" );
  FRENSIE_CHECK( boost::filesystem::exists( "test_sim_rendezvous_0.txt" ) );
}

//---------------------------------------------------------------------------//
// Check that the simulation name and archive can be changed simultaneously
FRENSIE_UNIT_TEST( ParticleSimulationManager, setSimulationNameAndArchiveType )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
    manager->useMultipleRendezvousFiles();
  }

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "xml" );

  manager->setSimulationNameAndArchiveType( "test_sim_2", "txt" );

  FRENSIE_CHECK_EQUAL( manager->getSimulationName(), "test_sim_2" );
  FRENSIE_CHECK_EQUAL( manager->getSimulationArchiveType(), "txt" );
  FRENSIE_CHECK( boost::filesystem::exists( "test_sim_2_rendezvous_0.txt" ) );
}

//---------------------------------------------------------------------------//
// Check that the geometry model can be returned
FRENSIE_UNIT_TEST( ParticleSimulationManager, getModel )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model;

  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );
    properties->setNumberOfHistories( 5 );

    model.reset( new MonteCarlo::FilledGeometryModel(
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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  FRENSIE_CHECK( &manager->getModel() == model.get() );
}

//---------------------------------------------------------------------------//
// Check that the source can be returned
FRENSIE_UNIT_TEST( ParticleSimulationManager, getSource )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

  std::shared_ptr<MonteCarlo::ParticleSource> source;

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  FRENSIE_CHECK( &manager->getSource() == source.get() );
}

//---------------------------------------------------------------------------//
// Check that the event handler can be returned
FRENSIE_UNIT_TEST( ParticleSimulationManager, getEventHandler )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

  std::shared_ptr<MonteCarlo::EventHandler> event_handler;

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
  
    event_handler.reset( new MonteCarlo::EventHandler( *properties ) );

    std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory;

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  FRENSIE_CHECK( &manager->getEventHandler() == event_handler.get() );
}

//---------------------------------------------------------------------------//
// Check that a simulation can be run
FRENSIE_UNIT_TEST( ParticleSimulationManager, runSimulation_history_wall )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_MODE );
    properties->setNumberOfHistories( 10 );

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), 10 );
    FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), 2 );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), 0 );
    FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a simulation can be run
FRENSIE_UNIT_TEST( ParticleSimulationManager, runSimulation_wall_time )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_MODE );
    properties->setSimulationWallTime( 0.5 );
    properties->setMaxRendezvousBatchSize( 10 );

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    FRENSIE_CHECK( manager->getNextHistory() > 0 );
    FRENSIE_CHECK( manager->getNumberOfRendezvous() > 0 );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), 0 );
    FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a particle simulation summary can be printed
FRENSIE_UNIT_TEST( ParticleSimulationManager, printSimulationSummary )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_MODE );
    properties->setNumberOfHistories( 10 );

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  manager->runSimulation();

  FRENSIE_REQUIRE_NO_THROW( manager->printSimulationSummary( std::cout ) );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation summary can be logged
FRENSIE_UNIT_TEST( ParticleSimulationManager, logSimulationSummary )
{
  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager;

  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_MODE );
    properties->setNumberOfHistories( 10 );

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

    factory.reset(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              "xml",
                                                              threads ) );
  
    manager = factory->getManager();
  }

  manager->runSimulation();

  FRENSIE_REQUIRE_NO_THROW( manager->logSimulationSummary() );
}

//---------------------------------------------------------------------------//
// Check that a particle simulation can be restarted
FRENSIE_DATA_UNIT_TEST_DECL( ParticleSimulationManager, restart_basic )
{
  FETCH_FROM_TABLE( std::string, archive_type );
  FETCH_FROM_TABLE( uint32_t, source_id );
  
  uint64_t next_history;
  uint64_t rendezvous_number;
  
  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_MODE );
    properties->setSimulationWallTime( 0.25 );
    properties->setMaxRendezvousBatchSize( 10 );

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
                                                     source_id,
                                                     1.0,
                                                     unfilled_model,
                                                     particle_distribution ) );

      source.reset( new MonteCarlo::StandardParticleSource( {source_component} ) );
    }
  
    std::shared_ptr<MonteCarlo::EventHandler> event_handler(
                                 new MonteCarlo::EventHandler( *properties ) );

    std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              archive_type,
                                                              threads ) );
  
    std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager =
      factory->getManager();
    manager->useMultipleRendezvousFiles();

    FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

    next_history = manager->getNextHistory();
    rendezvous_number = manager->getNumberOfRendezvous();
  }

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  Utility::broadcast( *comm, rendezvous_number, 0 );
  Utility::broadcast( *comm, next_history, 0 );

  std::string archive_name( "test_sim_rendezvous_" );
  archive_name += Utility::toString( rendezvous_number - 1 );
  archive_name += ".";
  archive_name += archive_type;

  std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory;

  FRENSIE_REQUIRE_NO_THROW( factory.reset( new MonteCarlo::ParticleSimulationManagerFactory( archive_name, (unsigned)threads ) ) );

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager =
    factory->getManager();

  manager->initialize();
  
  FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    FRENSIE_CHECK( manager->getNextHistory() > next_history );
    FRENSIE_CHECK( manager->getNumberOfRendezvous() > rendezvous_number );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), next_history );
    FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), rendezvous_number );
  }
}

FRENSIE_DATA_UNIT_TEST_INST( ParticleSimulationManager, restart_basic )
{
  COLUMNS()         << "archive_type" << "source_id" ;
  NEW_ROW( "xml" )  <<    "xml"       <<    0;
  NEW_ROW( "txt" )  <<    "txt"       <<    1;
  NEW_ROW( "bin" )  <<    "bin"       <<    2;
#ifdef HAVE_FRENSIE_HDF5
  NEW_ROW( "h5fa" ) <<    "h5fa"      <<    3;
#endif
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager can be restarted
FRENSIE_DATA_UNIT_TEST_DECL( ParticleSimulationManager, restart_add_histories )
{
  FETCH_FROM_TABLE( std::string, archive_type );
  FETCH_FROM_TABLE( uint32_t, source_id );
  
  uint64_t next_history;
  uint64_t rendezvous_number;
  
  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_MODE );
    properties->setSimulationWallTime( 0.25 );
    properties->setMaxRendezvousBatchSize( 10 );

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
                                                     source_id,
                                                     1.0,
                                                     unfilled_model,
                                                     particle_distribution ) );

      source.reset( new MonteCarlo::StandardParticleSource( {source_component} ) );
    }
  
    std::shared_ptr<MonteCarlo::EventHandler> event_handler(
                                 new MonteCarlo::EventHandler( *properties ) );

    std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              archive_type,
                                                              threads ) );
  
    std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager =
      factory->getManager();
    manager->useSingleRendezvousFile();

    FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

    next_history = manager->getNextHistory();
    rendezvous_number = manager->getNumberOfRendezvous();
  }

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  Utility::broadcast( *comm, rendezvous_number, 0 );
  Utility::broadcast( *comm, next_history, 0 );

  std::string archive_name( "test_sim_rendezvous." );
  archive_name += archive_type;

  std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory;

  FRENSIE_REQUIRE_NO_THROW( factory.reset( new MonteCarlo::ParticleSimulationManagerFactory( archive_name, (uint64_t)10, (unsigned)threads ) ) );

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager =
    factory->getManager();

  FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), next_history+10 );
    FRENSIE_CHECK( manager->getNumberOfRendezvous() > rendezvous_number );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), next_history );
    FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), rendezvous_number );
  }
}

FRENSIE_DATA_UNIT_TEST_INST( ParticleSimulationManager, restart_add_histories )
{
  COLUMNS()         << "archive_type" << "source_id" ;
  NEW_ROW( "xml" )  <<    "xml"       <<    0;
  NEW_ROW( "txt" )  <<    "txt"       <<    1;
  NEW_ROW( "bin" )  <<    "bin"       <<    2;
#ifdef HAVE_FRENSIE_HDF5
  NEW_ROW( "h5fa" ) <<    "h5fa"      <<    3;
#endif
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager can be restarted
FRENSIE_DATA_UNIT_TEST_DECL( ParticleSimulationManager, restart_new_wall_time )
{
  FETCH_FROM_TABLE( std::string, archive_type );
  FETCH_FROM_TABLE( uint32_t, source_id );
  
  uint64_t next_history;
  uint64_t rendezvous_number;
  
  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_MODE );
    properties->setSimulationWallTime( 0.25 );
    properties->setMaxRendezvousBatchSize( 10 );

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
                                                     source_id,
                                                     1.0,
                                                     unfilled_model,
                                                     particle_distribution ) );

      source.reset( new MonteCarlo::StandardParticleSource( {source_component} ) );
    }
  
    std::shared_ptr<MonteCarlo::EventHandler> event_handler(
                                 new MonteCarlo::EventHandler( *properties ) );

    std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              archive_type,
                                                              threads ) );
  
    std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager =
      factory->getManager();
    manager->useMultipleRendezvousFiles();

    FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

    next_history = manager->getNextHistory();
    rendezvous_number = manager->getNumberOfRendezvous();
  }

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  Utility::broadcast( *comm, rendezvous_number, 0 );
  Utility::broadcast( *comm, next_history, 0 );

  std::string archive_name( "test_sim_rendezvous_" );
  archive_name += Utility::toString( rendezvous_number - 1 );
  archive_name += ".";
  archive_name += archive_type;

  std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory;

  FRENSIE_REQUIRE_NO_THROW( factory.reset( new MonteCarlo::ParticleSimulationManagerFactory( archive_name, 0.1, (unsigned)threads ) ) );

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager =
    factory->getManager();

  FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

  if( Utility::GlobalMPISession::rank() == 0 )
  { 
    FRENSIE_CHECK( manager->getNextHistory() > next_history );
    FRENSIE_CHECK( manager->getNumberOfRendezvous() > rendezvous_number );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), next_history );
    FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), rendezvous_number );
  }
}

FRENSIE_DATA_UNIT_TEST_INST( ParticleSimulationManager, restart_new_wall_time )
{
  COLUMNS()         << "archive_type" << "source_id" ;
  NEW_ROW( "xml" )  <<    "xml"       <<    0;
  NEW_ROW( "txt" )  <<    "txt"       <<    1;
  NEW_ROW( "bin" )  <<    "bin"       <<    2;
#ifdef HAVE_FRENSIE_HDF5
  NEW_ROW( "h5fa" ) <<    "h5fa"      <<    3;
#endif
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager can be restarted
FRENSIE_DATA_UNIT_TEST_DECL( ParticleSimulationManager,
                             restart_add_histories_new_wall_time )
{
  FETCH_FROM_TABLE( std::string, archive_type );
  FETCH_FROM_TABLE( uint32_t, source_id );
  
  uint64_t next_history;
  uint64_t rendezvous_number;
  
  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_MODE );
    properties->setSimulationWallTime( 0.25 );
    properties->setMaxRendezvousBatchSize( 10 );

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
                                                     source_id,
                                                     1.0,
                                                     unfilled_model,
                                                     particle_distribution ) );

      source.reset( new MonteCarlo::StandardParticleSource( {source_component} ) );
    }
  
    std::shared_ptr<MonteCarlo::EventHandler> event_handler(
                                 new MonteCarlo::EventHandler( *properties ) );

    std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              archive_type,
                                                              threads ) );
  
    std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager =
      factory->getManager();
    manager->useMultipleRendezvousFiles();

    FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

    next_history = manager->getNextHistory();
    rendezvous_number = manager->getNumberOfRendezvous();
  }

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  Utility::broadcast( *comm, rendezvous_number, 0 );
  Utility::broadcast( *comm, next_history, 0 );

  std::string archive_name( "test_sim_rendezvous_" );
  archive_name += Utility::toString( rendezvous_number - 1 );
  archive_name += ".";
  archive_name += archive_type;

  std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory;

  FRENSIE_REQUIRE_NO_THROW( factory.reset( new MonteCarlo::ParticleSimulationManagerFactory( archive_name, (uint64_t)10, 1.0, (unsigned)threads ) ) );

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager =
    factory->getManager();

  FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), next_history+10 );
    FRENSIE_CHECK( manager->getNumberOfRendezvous() > rendezvous_number );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), next_history );
    FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), rendezvous_number );
  }
}

FRENSIE_DATA_UNIT_TEST_INST( ParticleSimulationManager,
                             restart_add_histories_new_wall_time )
{
  COLUMNS()         << "archive_type" << "source_id" ;
  NEW_ROW( "xml" )  <<    "xml"       <<    0;
  NEW_ROW( "txt" )  <<    "txt"       <<    1;
  NEW_ROW( "bin" )  <<    "bin"       <<    2;
#ifdef HAVE_FRENSIE_HDF5
  NEW_ROW( "h5fa" ) <<    "h5fa"      <<    3;
#endif
}

//---------------------------------------------------------------------------//
// Check that a particle simulation manager can be restarted
FRENSIE_DATA_UNIT_TEST_DECL( ParticleSimulationManager,
                             restart_updated_props )
{
  FETCH_FROM_TABLE( std::string, archive_type );
  FETCH_FROM_TABLE( uint32_t, source_id );
  
  uint64_t next_history;
  uint64_t rendezvous_number;
  
  {
    std::shared_ptr<MonteCarlo::SimulationProperties> properties(
                                        new MonteCarlo::SimulationProperties );
    properties->setParticleMode( MonteCarlo::PHOTON_MODE );
    properties->setSimulationWallTime( 0.25 );
    properties->setMaxRendezvousBatchSize( 10 );
    properties->setNumberOfSnapshotsPerBatch( 3 );

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
                                                     source_id,
                                                     1.0,
                                                     unfilled_model,
                                                     particle_distribution ) );

      source.reset( new MonteCarlo::StandardParticleSource( {source_component} ) );
    }
  
    std::shared_ptr<MonteCarlo::EventHandler> event_handler(
                                 new MonteCarlo::EventHandler( *properties ) );

    std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory(
            new MonteCarlo::ParticleSimulationManagerFactory( model,
                                                              source,
                                                              event_handler,
                                                              properties,
                                                              "test_sim",
                                                              archive_type,
                                                              threads ) );
  
    std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager =
      factory->getManager();
    manager->useMultipleRendezvousFiles();

    FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

    next_history = manager->getNextHistory();
    rendezvous_number = manager->getNumberOfRendezvous();
  }

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  Utility::broadcast( *comm, rendezvous_number, 0 );
  Utility::broadcast( *comm, next_history, 0 );

  std::string archive_name( "test_sim_rendezvous_" );
  archive_name += Utility::toString( rendezvous_number - 1 );
  archive_name += ".";
  archive_name += archive_type;

  MonteCarlo::SimulationGeneralProperties updated_properties;
  updated_properties.setNumberOfHistories( 16 );
  updated_properties.setMinNumberOfRendezvous( 2 );
  updated_properties.setMaxRendezvousBatchSize( 100 );
  updated_properties.setNumberOfBatchesPerProcessor( 2 );
  updated_properties.setSimulationWallTime( 1.0 );

  std::unique_ptr<MonteCarlo::ParticleSimulationManagerFactory> factory;

  FRENSIE_REQUIRE_NO_THROW( factory.reset( new MonteCarlo::ParticleSimulationManagerFactory( archive_name, updated_properties, (unsigned)threads ) ) );

  std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager =
    factory->getManager();

  FRENSIE_REQUIRE_NO_THROW( manager->runSimulation() );

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), next_history+16 );
    FRENSIE_CHECK( manager->getNumberOfRendezvous() > rendezvous_number );
    FRENSIE_CHECK_EQUAL( manager->getRendezvousBatchSize(), 8 );
    FRENSIE_CHECK_EQUAL( manager->getBatchSize(),
                         8/(2*(Utility::GlobalMPISession::size()-1)) );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( manager->getNextHistory(), next_history );
    FRENSIE_CHECK_EQUAL( manager->getNumberOfRendezvous(), rendezvous_number );
    FRENSIE_CHECK_EQUAL( manager->getRendezvousBatchSize(), 8 );
    FRENSIE_CHECK_EQUAL( manager->getBatchSize(),
                         8/(2*(Utility::GlobalMPISession::size()-1)) );
  }
}

FRENSIE_DATA_UNIT_TEST_INST( ParticleSimulationManager, restart_updated_props )
{
  COLUMNS()         << "archive_type" << "source_id" ;
  NEW_ROW( "xml" )  <<    "xml"       <<    0;
  NEW_ROW( "txt" )  <<    "txt"       <<    1;
  NEW_ROW( "bin" )  <<    "bin"       <<    2;
#ifdef HAVE_FRENSIE_HDF5
  NEW_ROW( "h5fa" ) <<    "h5fa"      <<    3;
#endif
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
    
    particle_distribution = tmp_particle_distribution;
  }                              
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDistributedParticleSimulationManager.cpp
//---------------------------------------------------------------------------//
