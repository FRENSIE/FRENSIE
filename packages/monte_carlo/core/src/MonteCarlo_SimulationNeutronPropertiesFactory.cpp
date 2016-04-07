//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationNeutronPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation neutron properties factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationNeutronPropertiesFactory.hpp"
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
void SimulationNeutronPropertiesFactory::initializeSimulationNeutronProperties(
				      const Teuchos::ParameterList& properties,
				      std::ostream* os_warn )
{  
  // Get the free gas thermal treatment temperature threshold - optional
  if( properties.isParameter( "Free Gas Threshold" ) )
  {
    double threshold = properties.get<double>( "Free Gas Threshold" );

    TEST_FOR_EXCEPTION( threshold < 0.0,
			std::runtime_error,
			"Error: The free gas thermal treatment threshold must "
			"be a positive number!" );

    SimulationNeutronProperties::setFreeGasThreshold( threshold );
  }

  // Get the minimum neutron energy - optional
  if( properties.isParameter( "Min Neutron Energy" ) )
  {
    double min_energy = properties.get<double>( "Min Neutron Energy" );

    if( min_energy >= SimulationNeutronProperties::getAbsoluteMinNeutronEnergy() )
      SimulationNeutronProperties::setMinNeutronEnergy( min_energy );
    else
    {
      SimulationNeutronProperties::setMinNeutronEnergy( 
			 SimulationNeutronProperties::getAbsoluteMinNeutronEnergy() );
      
      *os_warn << "Warning: the lowest supported neutron energy is "
		<< SimulationNeutronProperties::getAbsoluteMinNeutronEnergy()
		<< ". This value will be used instead of "
		<< min_energy << "." << std::endl;
    }
  }

  // Get the maximum neutron energy - optional
  if( properties.isParameter( "Max Neutron Energy" ) )
  {
    double max_energy = properties.get<double>( "Max Neutron Energy" );

    if( max_energy <= SimulationNeutronProperties::getAbsoluteMaxNeutronEnergy() )
      SimulationNeutronProperties::setMaxNeutronEnergy( max_energy );
    else
    {
      SimulationNeutronProperties::setMaxNeutronEnergy(
			 SimulationNeutronProperties::getAbsoluteMaxNeutronEnergy() );
      
      *os_warn << "Warning: the highest supported neutron energy is "
		<< SimulationNeutronProperties::getAbsoluteMaxNeutronEnergy()
		<< ". This value will be used instead of "
		<< max_energy << "." << std::endl;
    }
  }

  properties.unused( *os_warn );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationNeutronPropertiesFactory.cpp
//---------------------------------------------------------------------------//
