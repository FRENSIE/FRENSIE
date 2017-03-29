//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointPhotonPropertiesFactory.hpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_FACTORY_HPP
#define MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <iostream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"

namespace MonteCarlo{

//! The simulation adjoint photon properties factory
class SimulationAdjointPhotonPropertiesFactory
{

public:

  //! Initialize the simulation adjoint photon properties
  static void initializeProperties(
                  const Teuchos::ParameterList& properties,
                  SimulationAdjointPhotonProperties& adjoint_photon_properties,
                  std::ostream* os_warn = &std::cerr );
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointPhotonPropertiesFactory.hpp
//---------------------------------------------------------------------------//
