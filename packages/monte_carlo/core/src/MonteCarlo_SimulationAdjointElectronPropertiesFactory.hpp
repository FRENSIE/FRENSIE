//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointElectronPropertiesFactory.hpp
//! \author Luke Kersting
//! \brief  Simulation adjoint electron properties factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ADJOINT_ELECTRON_PROPERTIES_FACTORY_HPP
#define MONTE_CARLO_SIMULATION_ADJOINT_ELECTRON_PROPERTIES_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <iostream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"

namespace MonteCarlo{

//! The simulation adjoint electron properties factory
class SimulationAdjointElectronPropertiesFactory
{

public:

  //! Initialize the simulation adjoint electron properties
  static void initializeProperties(
                  const Teuchos::ParameterList& properties,
                  SimulationAdjointElectronProperties& adjoint_electron_properties,
                  std::ostream* os_warn = &std::cerr );
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_ADJOINT_ELECTRON_PROPERTIES_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointElectronPropertiesFactory.hpp
//---------------------------------------------------------------------------//
