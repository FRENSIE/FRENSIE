//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPropertiesFactory.hpp
//! \author Alex Robinson
//! \brief  Simulation properties factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_PROPERTIES_FACTORY_HPP
#define MONTE_CARLO_SIMULATION_PROPERTIES_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <iostream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

namespace MonteCarlo{

//! The simulation properties factory
class SimulationPropertiesFactory
{
  
public:

  //! Initialize the simulation properties
  static void initializeSimulationProperties( 
				      const Teuchos::ParameterList& properties,
				      std::ostream* os_warn = &std::cerr );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_PROPERTIES_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPropertiesFactory.hpp
//---------------------------------------------------------------------------//
