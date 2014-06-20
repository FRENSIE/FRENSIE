//---------------------------------------------------------------------------//
//!
//! \file   SimulationManager.hpp
//! \author Alex Robinson
//! \brief  Simulation base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_SIMULATION_MANAGER_HPP
#define FACEMC_SIMULATION_MANAGER_HPP

// Std Lib Includes
#include <iostream>

namespace Facemc{

//! The simulation manager base class
class SimulationManager
{
  
public:
  
  //! Default constructor.
  SimulationManager()
  { /* ... */ }

  //! Destructor
  virtual ~SimulationManager()
  { /* ... */ }

  //! Run the simulation set up by the user
  virtual void runSimulation() = 0;

  //! Print the data in all estimators to the desired stream
  virtual void printSimulationSummary( std::ostream &os ) const = 0;
}; 

} // end Facemc namespace

#endif // end FACEMC_SIMULATION_MANAGER_HPP

//--------------------------------------------------------------------------//
// end SimulationManager.hpp
//--------------------------------------------------------------------------//
