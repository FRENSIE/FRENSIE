//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PopulationControl.hpp
//! \author Philip Britt
//! \brief  Population Control class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POPULATION_CONTROL_HPP
#define MONTE_CARLO_POPULATION_CONTROL_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"

namespace MonteCarlo{

//! The population control base class
class PopulationControl
{

public:

  //! Constructor
  PopulationControl()
  { /* ... */ }

  //! Destructor
  virtual ~PopulationControl()
  { /* ... */ }

protected: 

  //! Split particle (purely based on number of splits)
  void splitParticle( ParticleState& particle,
                      ParticleBank& bank,
                      unsigned number_of_particles ) const;

  //! Split particle based on expectation weight
  void splitParticle( ParticleState& particle,
                      ParticleBank& bank,
                      unsigned number_of_particles,
                      double expectation_weight) const;

  //! Terminate particle
  void terminateParticle( ParticleState& particle,
                         ParticleBank& bank,
                         double termination_probability) const; 

};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POPULATION_CONTROL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PopulationControl.hpp
//---------------------------------------------------------------------------//
