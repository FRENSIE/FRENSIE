//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManagerFactory.cpp
//! \author Alex Robinson
//! \brief  Particle simulation manager factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_dagmc_config.hpp"
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "MonteCarlo_StandardParticleSourceFactory.hpp"
#include "MonteCarlo_SourceModuleInterface.hpp"
#include "MonteCarlo_EstimatorHandlerFactory.hpp"
#include "MonteCarlo_CollisionHandlerFactory.hpp"

#ifdef HAVE_FRENSIE_DAGMC
#include "Geometry_DagMCInstanceFactory.hpp"
#endif

#include "Utility_ExceptionTestMacros.hpp"

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
  #ifdef HAVE_FRENSIE_DAGMC
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
  #else
  return Teuchos::RCP<SimulationManager>();
  #endif // end HAVE_FRENSIE_DAGMC
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManagerFactory.cpp
//---------------------------------------------------------------------------//
