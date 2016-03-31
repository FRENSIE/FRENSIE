//---------------------------------------------------------------------------//
//!
//! \file   SimulationManager.hpp
//! \author Alex Robinson
//! \brief  Simulation base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FRENSIE_SIMULATION_MANAGER_HPP
#define FRENSIE_SIMULATION_MANAGER_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

namespace MonteCarlo{

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
  virtual void printSimulationSummary( std::ostream& os ) const = 0;

  //! Export the simulation data
  virtual void exportSimulationData( const std::string& data_file_name,
                                     std::ostream& os) const = 0;

  //! Return a signal handler function
  virtual void signalHandler(int signal) = 0;
}; 

} // end MonteCarlo namespace

#endif // end FRENSIE_SIMULATION_MANAGER_HPP

//--------------------------------------------------------------------------//
// end SimulationManager.hpp
//--------------------------------------------------------------------------//
