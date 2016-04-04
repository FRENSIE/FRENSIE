//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManagerFactory.hpp
//! \author Alex Robinson
//! \brief  Particle simulation manager factory class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTIClE_SIMULATION_MANAGER_FACTORY_DEF_HPP
#define MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_FACTORY_DEF_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "MonteCarlo_BatchedDistributedParticleSimulationManager.hpp"
#include "MonteCarlo_StandardParticleSourceFactory.hpp"
#include "MonteCarlo_EventHandlerFactory.hpp"
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_DagMC.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_Root.hpp"
#include "MonteCarlo_ResponseFunctionFactory.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the non-geometry modules
template<typename GeometryHandler>
void ParticleSimulationManagerFactory::initializeNonGeometryModules( 
                       const Teuchos::ParameterList& source_def,
                       const Teuchos::ParameterList& response_def,
                       const Teuchos::ParameterList& observer_def,
                       const Teuchos::ParameterList& material_def,
	               const Teuchos::ParameterList& cross_sections_table_info,
                       const std::string& cross_sections_xml_directory,
                       std::ostream* os_warn)
{
  // Make sure the warning output stream is valid
  testPrecondition( os_warn );
  
  // Initialize the source handler and interface
  {
    std::shared_ptr<ParticleSourceFactory> source_factory = 
      StandardParticleSourceFactory<Geometry::ModuleInterface<GeometryHandler> >::getInstance();

    std::shared_ptr<ParticleSource> source = source_factory->createSource( 
                              source_def, 
                              SimulationGeneralProperties::getParticleMode(),
                              *os_warn );

    setSourceHandlerInstance( source );
  }
  
  // Initialize the collision handler and interface
  {
    std::shared_ptr<CollisionHandlerFactory> collision_handler_factory = 
      getCollisionHandlerFactoryInstance<GeometryHandler>( os_warn );

    collision_handler_factory->initializeHandler( 
                                                material_def,
                                                cross_sections_table_info,
                                                cross_sections_xml_directory );
  }

  // Initialize the event handler and interface
  {
    // Create the response functions
    boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >
      response_function_id_map;

    ResponseFunctionFactory::createResponseFunctions( 
                                                    response_def,
                                                    response_function_id_map );
    
    std::shared_ptr<EventHandler> event_handler = 
      EventHandlerFactory<GeometryHandler>::createHandler( 
                                                      observer_def,
                                                      response_function_id_map,
                                                      os_warn );

    setEventHandlerInstance( event_handler );
  }
}

// Create the manager
template<typename GeometryHandler,
         typename SourceHandler,
         typename EventHandler,
         typename CollisionHandler>
std::shared_ptr<SimulationManager> 
ParticleSimulationManagerFactory::createManager(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  // Create a distributed simulation manager
  if( comm->getSize() > 1 )
  {
    return std::shared_ptr<SimulationManager>(
             new BatchedDistributedParticleSimulationManager<GeometryHandler,ParticleSource,EventHandler,CollisionHandler>(
	     comm,
             0,
             SimulationGeneralProperties::getNumberOfHistories(),
             SimulationGeneralProperties::getNumberOfBatchesPerProcessor() ) );
  }
  // Create a local simulation manager
  else
  {   
    return std::shared_ptr<SimulationManager>( 
            new ParticleSimulationManager<GeometryHandler,ParticleSource,EventHandler,CollisionHandler>(
                       SimulationGeneralProperties::getNumberOfHistories() ) );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTIClE_SIMULATION_MANAGER_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManagerFactory_def.hpp
//---------------------------------------------------------------------------//
