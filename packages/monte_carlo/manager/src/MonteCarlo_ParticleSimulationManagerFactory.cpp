//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManagerFactory.cpp
//! \author Alex Robinson
//! \brief  Particle simulation manager factory class definition
//!
//---------------------------------------------------------------------------//

// Moab Includes
#include "DagMC.hpp"

// FRENSIE Includes
#include "FRENSIE_dagmc_config.hpp"
#include "FRENSIE_root_config.hpp"
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "MonteCarlo_SimulationPropertiesFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_StandardParticleSourceFactory.hpp"
#include "MonteCarlo_SourceModuleInterface.hpp"
#include "MonteCarlo_EstimatorHandlerFactoryDecl.hpp"
#include "MonteCarlo_EstimatorHandlerFactory_DagMC.hpp"
#include "MonteCarlo_EstimatorHandlerFactory_Root.hpp"
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_DagMC.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_Root.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Utility_ExceptionTestMacros.hpp"

#ifdef HAVE_FRENSIE_ROOT
#include "Geometry_RootInstanceFactory.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#endif

namespace MonteCarlo{

// Create the requested manager
/*! \details If DagMC has not been enabled, this function will be empty
 */
Teuchos::RCP<SimulationManager> 
ParticleSimulationManagerFactory::createManager(
		       const Teuchos::ParameterList& simulation_info,
		       const Teuchos::ParameterList& geom_def,
		       const Teuchos::ParameterList& source_def,
		       const Teuchos::ParameterList& response_def,
		       const Teuchos::ParameterList& estimator_def,
		       const Teuchos::ParameterList& material_def,
		       const Teuchos::ParameterList& cross_sections_table_info,
		       const std::string& cross_sections_xml_directory )
{
  TEST_FOR_EXCEPTION( !simulation_info.isParameter( "Histories" ),
		      InvalidSimulationInfo,
		      "Error: the number of histories to run must be "
		      "specified!" );
  
  // Initialize the simulation properties
  SimulationPropertiesFactory::initializeSimulationProperties(simulation_info);

  // Determine which geometry handler has been requested
  std::string geom_handler_name;
  
  if( geom_def.isParameter( "Handler" ) )
    geom_handler_name = geom_def.get<std::string>( "Handler" );
  else
  {
    THROW_EXCEPTION( std::runtime_error,
		     "Error: The geometry handler type must be specified in "
		     "the geometry xml file!" );
  }
  
  if( geom_handler_name == "DagMC" )
  {
    #ifdef HAVE_FRENSIE_DAGMC   
    // Initialize DagMC 
    Geometry::DagMCInstanceFactory::initializeDagMC( geom_def );

    // Initialize the geometry handler
    Geometry::ModuleInterface<moab::DagMC>::initialize();

    // Initialize the source handler
    Teuchos::RCP<ParticleSourceFactory> source_factory =
      StandardParticleSourceFactory<moab::DagMC>::getInstance();
  
    Teuchos::RCP<ParticleSource> source = 
      source_factory->createSource( source_def );

    setSourceHandlerInstance( source );

    // Initialize the estimator handler
    EstimatorHandlerFactory<moab::DagMC>::initializeHandler( response_def,
							     estimator_def );
    
    // Initialize the collision handler
    getCollisionHandlerFactoryInstance<moab::DagMC>()->initializeHandler(
						material_def,
						cross_sections_table_info,
						cross_sections_xml_directory );
        
    return Teuchos::rcp( 
	 new ParticleSimulationManager<moab::DagMC,
                                       ParticleSource,
                                       EstimatorHandler,
                                       CollisionHandler>(
                               SimulationProperties::getNumberOfHistories() ) );
    #else
    return Teuchos::RCP<SimulationManager>();
    #endif // end HAVE_FRENSIE_DAGMC
  }
  else if( geom_handler_name == "ROOT" )
  {
    #ifdef HAVE_FRENSIE_ROOT 

    // Initialize Root 
    Geometry::RootInstanceFactory::initializeRoot( geom_def );

    // Initialize the geometry handler
    Geometry::ModuleInterface<Geometry::Root>::initialize();

    // Initialize the source handler
    Teuchos::RCP<ParticleSourceFactory> source_factory =
      StandardParticleSourceFactory<Geometry::Root>::getInstance();
  
    Teuchos::RCP<ParticleSource> source = 
      source_factory->createSource( source_def );

    setSourceHandlerInstance( source );

    // Initialize the estimator handler
    EstimatorHandlerFactory<Geometry::Root>::initializeHandler( response_def,
							     estimator_def );
    
    // Initialize the collision handler
    getCollisionHandlerFactoryInstance<Geometry::Root>()->initializeHandler(
						material_def,
						cross_sections_table_info,
						cross_sections_xml_directory );
        
    return Teuchos::rcp( 
	 new ParticleSimulationManager<Geometry::Root,
                                       ParticleSource,
                                       EstimatorHandler,
                                       CollisionHandler>(
                               SimulationProperties::getNumberOfHistories() ) );



    #else
    return Teuchos::RCP<SimulationManager>();
    #endif // end HAVE_FRENSIE_ROOT
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManagerFactory.cpp
//---------------------------------------------------------------------------//
