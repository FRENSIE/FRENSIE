//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation Properties factory class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "MonteCarlo_SimulationPropertiesFactory.hpp"
#include "MonteCarlo_SimulationGeneralPropertiesFactory.hpp"
#include "MonteCarlo_SimulationNeutronPropertiesFactory.hpp"
#include "MonteCarlo_SimulationPhotonPropertiesFactory.hpp"
#include "MonteCarlo_SimulationElectronPropertiesFactory.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
void SimulationPropertiesFactory::initializeSimulationProperties( 
				      const Teuchos::ParameterList& properties,
				      std::ostream* os_warn )
{  
  // Set the property list names
  std::string general_props_name = "General Properties";
  std::string neutron_props_name = "Neutron Properties";
  std::string photon_props_name = "Photon Properties";
  std::string electron_props_name = "Electron Properties";
  
  // Get the general properties - required
  TEST_FOR_EXCEPTION( !properties.isParameter( general_props_name ),
		      std::runtime_error,
		      "Error: the general properties must be specified!" );
  {
    Teuchos::ParameterList general_properties = 
      properties.get<Teuchos::ParameterList>( general_props_name );

    SimulationGeneralPropertiesFactory::initializeSimulationGeneralProperties( 
							    general_properties,
							    os_warn );
  }
  
  // Get the neutron properties - optional
  if( properties.isParameter( neutron_props_name ) )
  {
    if( SimulationGeneralProperties::getParticleMode() == NEUTRON_MODE ||
	SimulationGeneralProperties::getParticleMode() == NEUTRON_PHOTON_MODE )
    {
      Teuchos::ParameterList neutron_properties = 
	properties.get<Teuchos::ParameterList>( neutron_props_name );
      
      SimulationNeutronPropertiesFactory::initializeSimulationNeutronProperties( neutron_properties, os_warn );
    }
    else
    {
      *os_warn << "Warning: the neutron simulation properties will be ignored "
	       << "since neutrons are not being simulated! " << std::endl;
    }
  }
  
  // Get the photon properties - optional
  if( properties.isParameter( photon_props_name ) )
  {
    if( SimulationGeneralProperties::getParticleMode() == PHOTON_MODE ||
	SimulationGeneralProperties::getParticleMode() == NEUTRON_PHOTON_MODE )
    {
      Teuchos::ParameterList photon_properties = 
	properties.get<Teuchos::ParameterList>( photon_props_name );
      
      SimulationPhotonPropertiesFactory::initializeSimulationPhotonProperties( photon_properties, os_warn );
    }
    else
    {
      *os_warn << "Warning: the photon simulation properties will be ignored "
	       << "since photons are not being simulated! " << std::endl;
    }
  }
  
  // Get the electron properties - optional
  if( properties.isParameter( electron_props_name ) )
  {
    if( SimulationGeneralProperties::getParticleMode() == ELECTRON_MODE )
    {
      Teuchos::ParameterList electron_properties = 
	properties.get<Teuchos::ParameterList>( electron_props_name );

      SimulationElectronPropertiesFactory::initializeSimulationElectronProperties( electron_properties, os_warn );
    }
    else
    {
      *os_warn << "Warning: the electron simulation properties will be "
	       << "ignored since electrons are not being simulated! " 
	       << std::endl;
    }
  }

  properties.unused( *os_warn );

  // For some reason, unused parameter lists do not get printed by the
  // unused member function - we need to do this manually for now
  Teuchos::ParameterList::ConstIterator parameter = properties.begin();

  while( parameter != properties.end() )
  {
    const std::string& param_name = properties.name( parameter );
    
    if( param_name != general_props_name &&
	param_name != neutron_props_name &&
	param_name != photon_props_name &&
	param_name != electron_props_name )
    {
      *os_warn << "Warning: parameter list " << param_name
	       << " is unused!" << std::endl;      
    }

    ++parameter;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPropertiesFactory.cpp
//---------------------------------------------------------------------------//
