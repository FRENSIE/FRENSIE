//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationElectronPropertiesFactory.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation electron properties factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_FACTORY_HPP
#define MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <iostream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationElectronProperties.hpp"

namespace MonteCarlo{

//! The simulation electron properties factory
class SimulationElectronPropertiesFactory
{

public:

  //! Initialize the simulation electron properties
  static void initializeProperties(
                             const Teuchos::ParameterList& properties,
                             SimulationElectronProperties& electron_properties,
                             std::ostream* os_warn = &std::cerr );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationElectronPropertiesFactory.hpp
//---------------------------------------------------------------------------//
