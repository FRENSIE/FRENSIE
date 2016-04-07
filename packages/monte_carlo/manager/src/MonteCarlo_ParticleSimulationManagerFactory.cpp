//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManagerFactory.cpp
//! \author Alex Robinson
//! \brief  Particle simulation manager factory class definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "MonteCarlo_SimulationPropertiesFactory.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Geometry_Config.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

#ifdef HAVE_FRENSIE_ROOT
#include "Geometry_RootInstanceFactory.hpp"
#endif

#ifdef HAVE_FRENSIE_DAGMC
#include "Geometry_DagMCInstanceFactory.hpp"
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
  
  // Initialize the simulation properties
  SimulationPropertiesFactory::initializeSimulationProperties( simulation_info,
							       out.get() );

  // Determine which geometry handler has been requested
  TEST_FOR_EXCEPTION( !geom_def.isParameter( "Handler" ),
                      std::runtime_error,
                      "Error: The geometry handler type must be specified in "
                      "the geometry xml file!" );
  
  std::string geom_handler_name = geom_def.get<std::string>( "Handler" );
    
  if( geom_handler_name == "DagMC" )
  {
    return ParticleSimulationManagerFactory::createManagerWithDagMC( 
                                                  geom_def,
                                                  source_def,
                                                  response_def,
                                                  observer_def,
                                                  material_def,
                                                  cross_sections_table_info,
                                                  cross_sections_xml_directory,
                                                  comm,
                                                  out.get() );
    
  }
  else if( geom_handler_name == "ROOT" )
  {
    return ParticleSimulationManagerFactory::createManagerWithRoot( 
                                                  geom_def,
                                                  source_def,
                                                  response_def,
                                                  observer_def,
                                                  material_def,
                                                  cross_sections_table_info,
                                                  cross_sections_xml_directory,
                                                  comm,
                                                  out.get() );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: The geometry handler type "
                     << geom_handler_name << " is not supported!" );
  }
}

// Initialize the modules using DagMC
std::shared_ptr<SimulationManager> 
ParticleSimulationManagerFactory::createManagerWithDagMC( 
            const Teuchos::ParameterList& geom_def,
            const Teuchos::ParameterList& source_def,
            const Teuchos::ParameterList& response_def,
            const Teuchos::ParameterList& observer_def,
            const Teuchos::ParameterList& material_def,
            const Teuchos::ParameterList& cross_sections_table_info,
            const std::string& cross_sections_xml_directory,
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            std::ostream* os_warn )
{
#ifdef HAVE_FRENSIE_DAGMC   
  // Initialize DagMC 
  Geometry::DagMCInstanceFactory::initializeDagMC( geom_def, *os_warn );

  // Initialize the geometry handler
  Geometry::ModuleInterface<Geometry::DagMC>::initialize();

  // Initialize the other handlers
  ParticleSimulationManagerFactory::initializeNonGeometryModules<Geometry::DagMC>(
                                                  source_def,
                                                  response_def,
                                                  observer_def,
                                                  material_def,
                                                  cross_sections_table_info,
                                                  cross_sections_xml_directory,
                                                  os_warn );
  // Create the manager
  return ParticleSimulationManagerFactory::createManager<Geometry::DagMC,ParticleSource,EventHandler,CollisionHandler>( comm, 0 );
  
#else
  THROW_EXCEPTION( InvalidSimulationInfo,
                   "Error: a DagMC geometry handler was requested without "
                   "having DagMC enabled! The particle simulation manager "
                   "cannot be created." );
#endif // end HAVE_FRENSIE_DAGMC   
}

// Initialize the modules with Root
std::shared_ptr<SimulationManager> 
ParticleSimulationManagerFactory::createManagerWithRoot(
            const Teuchos::ParameterList& geom_def,
            const Teuchos::ParameterList& source_def,
            const Teuchos::ParameterList& response_def,
            const Teuchos::ParameterList& observer_def,
            const Teuchos::ParameterList& material_def,
            const Teuchos::ParameterList& cross_sections_table_info,
            const std::string& cross_sections_xml_directory,
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            std::ostream* os_warn )
{
#ifdef HAVE_FRENSIE_ROOT 
  // Initialize Root 
  Geometry::RootInstanceFactory::initializeRoot( geom_def, *os_warn );

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
                                                  os_warn );
  // Create the manager
  return ParticleSimulationManagerFactory::createManager<Geometry::Root,ParticleSource,EventHandler,CollisionHandler>( comm, 0 );
  
#else
  THROW_EXCEPTION( InvalidSimulationInfo,
                   "Error: a Root geometry handler was requested without "
                   "having Root enabled! The particle simulation manager "
                   "cannot be created." );
#endif // end HAVE_FRENSIE_ROOT
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManagerFactory.cpp
//---------------------------------------------------------------------------//
