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
#include "MonteCarlo_SimulationAdjointPhotonPropertiesFactory.hpp"
#include "MonteCarlo_SimulationElectronPropertiesFactory.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
std::shared_ptr<const SimulationProperties>
SimulationPropertiesFactory::createProperties(
                                      const Teuchos::ParameterList& properties,
                                      std::ostream* os_warn )
{
  // Create the new simulation properties object
  std::shared_ptr<SimulationProperties> simulation_properties(
                                                    new SimulationProperties );
  
  // Set the property list names
  std::string general_props_name = "General Properties";
  std::string neutron_props_name = "Neutron Properties";
  std::string photon_props_name = "Photon Properties";
  std::string adjoint_photon_props_name = "Adjoint Photon Properties";
  std::string electron_props_name = "Electron Properties";

  // Get the general properties - required
  TEST_FOR_EXCEPTION( !properties.isParameter( general_props_name ),
                      std::runtime_error,
                      "Error: the general properties must be specified!" );
  {
    Teuchos::ParameterList general_properties =
      properties.get<Teuchos::ParameterList>( general_props_name );

    SimulationGeneralPropertiesFactory::initializeProperties(
                                                        general_properties,
                                                        *simulation_properties,
                                                        os_warn );
  }

  // Get the neutron properties - optional
  if( properties.isParameter( neutron_props_name ) )
  {
    if( simulation_properties->getParticleMode() != NEUTRON_MODE &&
        simulation_properties->getParticleMode() != NEUTRON_PHOTON_MODE &&
        simulation_properties->getParticleMode() != NEUTRON_PHOTON_ELECTRON_MODE )
    {
      *os_warn << "Warning: the neutron simulation properties specified are "
               << "not required since neutrons will not be simulated!"
               << std::endl;
    }

    Teuchos::ParameterList neutron_properties =
      properties.get<Teuchos::ParameterList>( neutron_props_name );
    
    SimulationNeutronPropertiesFactory::initializeProperties(
                                                        neutron_properties,
                                                        *simulation_properties,
                                                        os_warn );
  }

  // Get the photon properties - optional
  if( properties.isParameter( photon_props_name ) )
  {
    if( simulation_properties->getParticleMode() != PHOTON_MODE &&
        simulation_properties->getParticleMode() != NEUTRON_PHOTON_MODE &&
        simulation_properties->getParticleMode() != PHOTON_ELECTRON_MODE &&
        simulation_properties->getParticleMode() != NEUTRON_PHOTON_ELECTRON_MODE )
    {
      *os_warn << "Warning: the photon simulation properties specified are "
               << "note required since photons will not be simulated!"
               << std::endl;
    }

    Teuchos::ParameterList photon_properties =
      properties.get<Teuchos::ParameterList>( photon_props_name );

    SimulationPhotonPropertiesFactory::initializeProperties(
                                                        photon_properties,
                                                        *simulation_properties,
                                                        os_warn );
  }

  // Get the electron properties - optional
  if( properties.isParameter( electron_props_name ) )
  {
    if( simulation_properties->getParticleMode() != ELECTRON_MODE &&
        simulation_properties->getParticleMode() != PHOTON_ELECTRON_MODE &&
        simulation_properties->getParticleMode() != NEUTRON_PHOTON_ELECTRON_MODE )
    {
      *os_warn << "Warning: the electron simulation properties specified are "
               << "not required since electrons will not be simulated!"
               << std::endl;
    }

    Teuchos::ParameterList electron_properties =
      properties.get<Teuchos::ParameterList>( electron_props_name );

    SimulationElectronPropertiesFactory::initializeProperties(
                                                        electron_properties,
                                                        *simulation_properties,
                                                        os_warn );
  }

  // Get the adjoint photon properties - optional
  if( properties.isParameter( adjoint_photon_props_name ) )
  {
    if( simulation_properties->getParticleMode() != ADJOINT_PHOTON_MODE )
    {
      *os_warn << "Warning: the adjoint photon simulation properties "
               << "specified are not required since adjoint photons will not "
               << "be simulated!"
               << std::endl;
    }

    Teuchos::ParameterList adjoint_photon_properties =
      properties.get<Teuchos::ParameterList>( adjoint_photon_props_name );

    SimulationAdjointPhotonPropertiesFactory::initializeProperties(
                                                     adjoint_photon_properties,
                                                     *simulation_properties,
                                                     os_warn );
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
        param_name != adjoint_photon_props_name &&
        param_name != electron_props_name )
    {
      *os_warn << "Warning: parameter list " << param_name
               << " is unused!" << std::endl;
    }

    ++parameter;
  }

  return simulation_properties;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPropertiesFactory.cpp
//---------------------------------------------------------------------------//
