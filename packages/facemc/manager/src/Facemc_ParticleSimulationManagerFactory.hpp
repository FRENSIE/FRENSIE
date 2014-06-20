//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSimulationManagerFactory.hpp
//! \author Alex Robinson
//! \brief  Particle simulation manager factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SIMULATION_MANAGER_FACTORY_HPP
#define FACEMC_PARTICLE_SIMULATION_MANAGER_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Facemc_SimulationManager.hpp"

namespace Facemc{

//! The particle simulation manager factory class
class ParticleSimulationManagerFactory
{

public:

  //! Create the requested manager
  Teuchos::RCP<SimulationManager> createManager( 
		       const Teuchos::ParameterList& simulation_info,
		       const Teuchos::ParameterList& geom_def,
		       const Teuchos::ParameterList& source_def,
		       const Teuchos::ParameterList& response_def,
		       const Teuchos::ParameterList& estimator_def,
		       const Teuchos::ParameterList& material_def,
		       const Teuchos::ParameterList& cross_sections_table_info,
		       const std::string& cross_sections_xml_directory );

private:

  // Constructor
  ParticleSimulationManagerFactory();
};

//! The invalid simulation info error
class InvalidSimulationInfo : public std::logic_error
{

public:

  InvalidSimulationInfo( const std::string& what_arg )
    : std::logic_error( what_arg )
  { /* ... */ }
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_SIMULATION_MANAGER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleSimulationManagerFactory.hpp
//---------------------------------------------------------------------------//
