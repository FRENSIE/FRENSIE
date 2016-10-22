//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationNeutronPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation neutron properties factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationNeutronPropertiesFactory.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
void SimulationNeutronPropertiesFactory::initializeProperties(
			       const Teuchos::ParameterList& properties,
                               SimulationNeutronProperties& neutron_properties,
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

    neutron_properties.setFreeGasThreshold( threshold );
  }

  // Get the minimum neutron energy - optional
  if( properties.isParameter( "Min Neutron Energy" ) )
  {
    double min_energy = properties.get<double>( "Min Neutron Energy" );

    if( min_energy >= neutron_properties.getAbsoluteMinNeutronEnergy() )
      neutron_properties.setMinNeutronEnergy( min_energy );
    else
    {
      neutron_properties.setMinNeutronEnergy(
                            neutron_properties.getAbsoluteMinNeutronEnergy() );

      *os_warn << "Warning: the lowest supported neutron energy is "
		<< neutron_properties.getAbsoluteMinNeutronEnergy()
		<< ". This value will be used instead of "
		<< min_energy << "." << std::endl;
    }
  }

  // Get the maximum neutron energy - optional
  if( properties.isParameter( "Max Neutron Energy" ) )
  {
    double max_energy = properties.get<double>( "Max Neutron Energy" );

    if( max_energy <= neutron_properties.getAbsoluteMaxNeutronEnergy() )
      neutron_properties.setMaxNeutronEnergy( max_energy );
    else
    {
      neutron_properties.setMaxNeutronEnergy(
			    neutron_properties.getAbsoluteMaxNeutronEnergy() );

      *os_warn << "Warning: the highest supported neutron energy is "
		<< neutron_properties.getAbsoluteMaxNeutronEnergy()
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
