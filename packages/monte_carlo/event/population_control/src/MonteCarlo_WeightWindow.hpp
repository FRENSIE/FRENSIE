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

//! An actual weight window object.
struct WeightWindow{
  double upper_weight;
  double survival_weight;
  double lower_weight;
};

//! The weight window base class
class WeightWindowBase: public PopulationControl
{

public:

  //! Constructor
  WeightWindowBase()
  { /* ... */ }

  //! Destructor
  ~WeightWindowBase()
  { /* ... */ }

  void checkParticleWithPopulationController( ParticleState& particle, 
                                              ParticleBank& bank) const;

  protected:

  virtual std::shared_ptr<WeightWindow> getWeightWindow( ParticleState& particle ) const = 0;

  virtual bool isParticleInWeightWindowDiscretization( ParticleState& particle ) const = 0;

};



} // end MonteCarlo namespace


#endif // end MONTE_CARLO_WEIGHT_WINDOW_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindow.hpp
//---------------------------------------------------------------------------//
