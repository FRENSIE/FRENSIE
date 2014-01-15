//---------------------------------------------------------------------------//
//!
//! \file   SimulationManager.hpp
//! \author Alex Robinson
//! \brief  Simulation base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef SIMULATION_MANAGER_HPP
#define SIMULATION_MANAGER_HPP

// Std Lib Includes
#include <iostream>

namespace FACEMC{

//! The simulation manager base class
class SimulationManager
{
  
public:

  //! Typedef for SimulationManager pointer
  typedef Teuchos::RCP<SimulationManager> Pointer;
  
  //! Default constructor.
  SimulationManager()
  { /* ... */ }

  //! Destructor
  virtual ~SimulationManger()
  { /* ... */ }

  //-------------------------------------------------------------------------//
  // Interface for Running a Simulation
  //-------------------------------------------------------------------------//

  //! Run the simulation set up by the user
  virtual void run() = 0;

  //! Print the info tables to std::cout
  virtual void printTables() const = 0;

  //! Print the info tables to the desired stream
  virtual void printTables( std::ostream &os ) const = 0;

  //! Print the data in all estimators to std::cout
  virtual void printEstimators() const = 0;

  //! Print the data in all estimators to the desired stream
  virtual void printEstimators( std::ostream &os ) const = 0;
}; 

} // end FACEMC namespace

#endif // end SIMULATION_MANAGER_HPP

//--------------------------------------------------------------------------//
// end SimulationManager.hpp
//--------------------------------------------------------------------------//
