//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSimulationManagerFactory.cpp
//! \author Alex Robinson
//! \brief  Particle simulation manager factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleSimulationManagerFactory.hpp"
#include "Facemc_ParticleSimulationManager.hpp"
#include "Facemc_StandardParticleSourceFactory.hpp"
#include "Facemc_SourceModuleInterface.hpp"
#include "Facemc_EstimatorHandlerFactory.hpp"
#include "Facemc_CollisionHandlerFactory.hpp"
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Facemc{

// Create the requested manager
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
  
  // Initialize DagMC
  Geometry::DagMCInstanceFactory::initializeDagMC( geom_def );

  // Initialize the source handler
  Teuchos::RCP<ParticleSourceFactory> source_factory =
    StandardParticleSourceFactory<moab::DagMC>::getInstance();
  
  Teuchos::RCP<ParticleSource> source = 
    source_factory->createSource( source_def );

  setSourceHandlerInstance( source );

  // Initialize the estimator handler
  EstimatorHandlerFactory::initializeHandlerUsingDagMC( response_def,
							estimator_def );

  // Initialize the collision handler
  CollisionHandlerFactory::initializeHandlerUsingDagMC( 
						material_def,
						cross_sections_table_info,
						cross_sections_xml_directory );

  return Teuchos::rcp( 
         new ParticleSimulationManager<moab::DagMC,
		                       ParticleSource,
	                               EstimatorHandler,
		                       CollisionHandler>(
			  simulation_info.get<unsigned int>( "Histories" ) ) );
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleSimulationManagerFactory.cpp
//---------------------------------------------------------------------------//
