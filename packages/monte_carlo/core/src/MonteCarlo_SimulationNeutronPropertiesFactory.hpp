//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationNeutronPropertiesFactory.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation neutron properties factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_NEUTRON_PROPERTIES_FACTORY_HPP
#define MONTE_CARLO_SIMULATION_NEUTRON_PROPERTIES_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

namespace MonteCarlo{

//! The simulation neutron properties factory
class SimulationNeutronPropertiesFactory
{
  
public:
  
  //! Initialize the simulation neutron properties
  static void initializeSimulationNeutronProperties( 
				    const Teuchos::ParameterList& properties );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_NEUTRON_PROPERTIES_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationNeutronPropertiesFactory.hpp
//---------------------------------------------------------------------------//
