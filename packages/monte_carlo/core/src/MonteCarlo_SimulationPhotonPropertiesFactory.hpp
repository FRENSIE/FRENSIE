//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPhotonPropertiesFactory.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_PHOTON_PROPERTIES_FACTORY_HPP
#define MONTE_CARLO_SIMULATION_PHOTON_PROPERTIES_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <iostream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

namespace MonteCarlo{

//! The simulation photon properties factory
class SimulationPhotonPropertiesFactory
{
  
public:
  
  //! Initialize the simulation photon properties
  static void initializeSimulationPhotonProperties( 
				      const Teuchos::ParameterList& properties,
				      std::ostream* os_warn = &std::cerr );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_PHOTON_PROPERTIES_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPhotonPropertiesFactory.hpp
//---------------------------------------------------------------------------//
