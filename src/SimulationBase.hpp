//---------------------------------------------------------------------------//
//!
//! \file SimulationBase.hpp
//! \author Alex Robinson
//! \brief Simulation Base Class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef SIMULATION_BASE_HPP
#define SIMULATION_BASE_HPP

namespace FACEMC{

class SimulationBase
{
  
  //! Default Constructor.
  SimulationBase()
  { /* ... */ }

  //! Destructor
  virtual ~SimulationBase()
  { /* ... */ }

  //-------------------------------------------------------------------------//
  // Interface for Running a Simulation
  //-------------------------------------------------------------------------//

  //! Run the number of histories requested by the user
  virtual void runHistories() = 0;

  //! Print the info tables requested by the user
  virtual void printTables() = 0;

  //! Print the data in all tallies
  virtual void printTallies() = 0;

}; // end class SimulationBase

} // end namespace FAPMC

#endif // end SIMULATION_BASE_HPP

//--------------------------------------------------------------------------//
// end SimulationBase.hpp
//--------------------------------------------------------------------------//
