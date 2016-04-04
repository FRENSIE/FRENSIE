//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManagerFactory.hpp
//! \author Alex Robinson
//! \brief  Particle simulation manager factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FRENSIE_PARTICLE_SIMULATION_MANAGER_FACTORY_HPP
#define FRENSIE_PARTICLE_SIMULATION_MANAGER_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <memory>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Comm.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationManager.hpp"

namespace MonteCarlo{

//! The particle simulation manager factory class
class ParticleSimulationManagerFactory
{

public:

  //! Create the requested manager
  static std::shared_ptr<SimulationManager> createManager( 
	  const Teuchos::ParameterList& simulation_info,
	  const Teuchos::ParameterList& geom_def,
	  const Teuchos::ParameterList& source_def,
	  const Teuchos::ParameterList& response_def,
	  const Teuchos::ParameterList& observer_def,
	  const Teuchos::ParameterList& material_def,
	  const Teuchos::ParameterList& cross_sections_table_info,
	  const std::string& cross_sections_xml_directory,
	  const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm );

private:

  // Constructor
  ParticleSimulationManagerFactory();

  // create the handler using DagMC
  static std::shared_ptr<SimulationManager> createManagerWithDagMC( 
            const Teuchos::ParameterList& geom_def,
            const Teuchos::ParameterList& source_def,
            const Teuchos::ParameterList& response_def,
            const Teuchos::ParameterList& observer_def,
            const Teuchos::ParameterList& material_def,
            const Teuchos::ParameterList& cross_sections_table_info,
            const std::string& cross_sections_xml_directory,
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            std::ostream* os_warn );

  // Initialize the modules with Root
  static std::shared_ptr<SimulationManager> createManagerWithRoot(
            const Teuchos::ParameterList& geom_def,
            const Teuchos::ParameterList& source_def,
            const Teuchos::ParameterList& response_def,
            const Teuchos::ParameterList& observer_def,
            const Teuchos::ParameterList& material_def,
            const Teuchos::ParameterList& cross_sections_table_info,
            const std::string& cross_sections_xml_directory,
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            std::ostream* os_warn );

  // Initialize the non-geometry modules
  template<typename GeometryHandler>
  static void initializeNonGeometryModules( 
                       const Teuchos::ParameterList& source_def,
                       const Teuchos::ParameterList& response_def,
                       const Teuchos::ParameterList& observer_def,
                       const Teuchos::ParameterList& material_def,
	               const Teuchos::ParameterList& cross_sections_table_info,
                       const std::string& cross_sections_xml_directory,
                       std::ostream* os_warn );

  // Create the manager
  template<typename GeometryHandler,
           typename SourceHandler,
           typename EventHandler,
           typename CollisionHandler>
  static std::shared_ptr<SimulationManager> createManager(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );
};

//! The invalid simulation info error
class InvalidSimulationInfo : public std::runtime_error
{

public:

  InvalidSimulationInfo( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleSimulationManagerFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FRENSIE_PARTICLE_SIMULATION_MANAGER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManagerFactory.hpp
//---------------------------------------------------------------------------//
