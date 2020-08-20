//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindowMesh.cpp
//! \author Philip Britt
//! \brief  Weight window mesh class definition
//!
//---------------------------------------------------------------------------//

// std includes
#include <math.h>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_WeightWindow.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Update the particle state and bank
void WeightWindowBase::checkParticleWithPopulationController( ParticleState& particle,
                                                              ParticleBank& bank ) const
{

  //! Make sure there is a weight window where this particle is.
  if(this->isParticleInWeightWindowDiscretization( particle ))
  {

    std::shared_ptr<WeightWindow> window = this->getWeightWindow(particle);

    double weight = particle.getWeight();

    if(weight > window->upper_weight)
    {
      // return number after decimal
      double weight_fraction = fmod(weight/window->upper_weight,1);

      unsigned number_of_particles;

      if(Utility::RandomNumberGenerator::getRandomNumber<double>() < weight_fraction)
      {
        number_of_particles = static_cast<unsigned>(floor(weight_fraction));
      }else
      {
        number_of_particles = static_cast<unsigned>(ceil(weight_fraction));
      }

      this->splitParticle(particle, bank, number_of_particles);

    }else if(weight < window->lower_weight)
    {
      this->terminateParticle(particle, 
                              1 - (weight/window->survival_weight));
    }

  }
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::WeightWindow );

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.cpp
//---------------------------------------------------------------------------//