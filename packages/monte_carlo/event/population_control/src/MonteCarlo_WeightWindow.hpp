//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindow.hpp
//! \author Alex Robinson
//! \brief  Weight window class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WEIGHT_WINDOW_HPP
#define MONTE_CARLO_WEIGHT_WINDOW_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PopulationControl.hpp"


namespace MonteCarlo{

//! The weight window base class
class WeightWindow: public PopulationControl
{

public:

  //! Constructor
  WeightWindow()
  { /* ... */ }

  //! Destructor
  ~WeightWindow()
  { /* ... */ }

  void checkParticleWithPopulationController( ParticleState& particle, ParticleBank& bank) const;

};
  

} // end MonteCarlo namespace


#endif // end MONTE_CARLO_WEIGHT_WINDOW_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindow.hpp
//---------------------------------------------------------------------------//
