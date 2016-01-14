//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationGeneralPropertiesFactory.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_FACTORY_HPP
#define MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <iostream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

namespace MonteCarlo{

//! The simulation general properties factory
class SimulationGeneralPropertiesFactory
{
  
public:
  
  //! Initialize the simulation general properties
  static void initializeSimulationGeneralProperties( 
				      const Teuchos::ParameterList& properties,
				      std::ostream* os_warn = &std::cerr );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationGeneralPropertiesFactory.hpp
//---------------------------------------------------------------------------//
