//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManagerFactory.cpp
//! \author Alex Robinson
//! \brief  Particle simulation manager factory class definition
//!
//---------------------------------------------------------------------------//

// Moab Includes
#include "DagMC.hpp"

// Trilinos Includes
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "FRENSIE_dagmc_config.hpp"
#include "FRENSIE_root_config.hpp"
#include "FRENSIE_mpi_config.hpp"
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "MonteCarlo_SimulationPropertiesFactory.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

#ifdef HAVE_FRENSIE_ROOT
#include "Geometry_RootInstanceFactory.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#endif
namespace MonteCarlo{

// Create the requested manager
std::shared_ptr<SimulationManager> 
ParticleSimulationManagerFactory::createManager(
	   const Teuchos::ParameterList& simulation_info,
	   const Teuchos::ParameterList& geom_def,
	   const Teuchos::ParameterList& source_def,
	   const Teuchos::ParameterList& response_def,
	   const Teuchos::ParameterList& observer_def,
	   const Teuchos::ParameterList& material_def,
	   const Teuchos::ParameterList& cross_sections_table_info,
	   const std::string& cross_sections_xml_directory,
	   const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm )
{
  // Make sure the comm object is valid
  testPrecondition( !comm.is_null() );

  // Create the output stream
  Teuchos::RCP<std::ostream> out;
  
  if( Teuchos::GlobalMPISession::mpiIsInitialized() &&
	Teuchos::GlobalMPISession::getNProc() > 1 )
  {
    Teuchos::RCP<Teuchos::FancyOStream> fancy_out =
      Teuchos::VerboseObjectBase::getDefaultOStream();
    fancy_out->setProcRankAndSize( comm->getRank(), comm->getSize() );
    fancy_out->setOutputToRootOnly( 0 );

    out = fancy_out;
  }
  else
    out.reset( &std::cerr, false );
  
  TEST_FOR_EXCEPTION( !simulation_info.isParameter( "General Properties" ),
		      InvalidSimulationInfo,
		      "Error: the general properties must be specified!" );
  
  // Initialize the simulation properties
  SimulationPropertiesFactory::initializeSimulationProperties( simulation_info,
							       out.get() );

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
    Geometry::DagMCInstanceFactory::initializeDagMC( geom_def, *out );

    // Initialize the geometry handler
    Geometry::ModuleInterface<moab::DagMC>::initialize();

    // Initialize the other handlers
    ParticleSimulationManagerFactory::initializeNonGeometryModules<moab::DagMC>(
                                                  source_def,
                                                  response_def,
                                                  observer_def,
                                                  material_def,
                                                  cross_sections_table_info,
                                                  cross_sections_xml_directory,
                                                  out.get() );
                                                                   
    // Create the manager
    return ParticleSimulationManagerFactory::createManager<moab::DagMC,ParticleSource,EventHandler,CollisionHandler>( comm, 0 );    
    
    #else
    THROW_EXCEPTION( InvalidSimulationInfo,
                     "Error: a DagMC geometry handler was requested without "
                     "having DagMC enabled!" );
    #endif // end HAVE_FRENSIE_DAGMC
  }
  else if( geom_handler_name == "ROOT" )
  {
    #ifdef HAVE_FRENSIE_ROOT 

    // Initialize Root 
    Geometry::RootInstanceFactory::initializeRoot( geom_def, *out );

    // Initialize the geometry handler
    Geometry::ModuleInterface<Geometry::Root>::initialize();

    // Initialize the other handlers
    ParticleSimulationManagerFactory::initializeNonGeometryModules<Geometry::Root>(
                                                  source_def,
                                                  response_def,
                                                  observer_def,
                                                  material_def,
                                                  cross_sections_table_info,
                                                  cross_sections_xml_directory,
                                                  out.get() );
                                                                   
    // Create the manager
    return ParticleSimulationManagerFactory::createManager<Geometry::Root,ParticleSource,EventHandler,CollisionHandler>( comm, 0 );    

    #else
      THROW_EXCEPTION( InvalidSimulationInfo,
                       "Error: a Root geometry handler was requested without "
                       "having Root enabled!" );
    #endif // end HAVE_FRENSIE_ROOT
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManagerFactory.cpp
//---------------------------------------------------------------------------//
