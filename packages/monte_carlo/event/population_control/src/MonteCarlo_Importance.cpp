//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Importance.cpp
//! \author Philip Britt
//! \brief  Importance mesh class definition
//!
//---------------------------------------------------------------------------//

// std includes
#include <cmath>
#include <functional>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_Importance.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Update the particle state and bank
void Importance::checkParticleWithPopulationController( ParticleState& particle,
                                                              ParticleBank& bank ) const
{

  //! Make sure the particle is inside the importance discretization.
  if(this->isParticleInImportanceDiscretization( particle ))
  {
    // Importances are only applied after first collision
    if(particle.getCollisionNumber() >= 1)
    {
      // Particle has already had both importance members initialized, update to new importances
      if(particle.getCollisionNumber() > 1)
      {
        particle.updateImportance(this->getImportance(particle));
      }
      // Particle has undergone its first collision, update second importance member only
      else
      {
        particle.setNewImportance(this->getImportance(particle));
      }

      // Apply importances from here
      double importance_fraction = particle.getImportancePair().second/particle.getImportancePair().first;

      if(importance_fraction > 1)
      {
        std::function<double(double)> particle_number_operator;
        // Split particle into lower possible number of emergent particles
        if( Utility::RandomNumberGenerator::getRandomNumber<double>() < 1-std::fmod(importance_fraction, 1))
        {
          particle_number_operator = static_cast<double(*)(double)>(&std::floor);
        }
        // Split particle into greater possible number of emergent particles
        else
        {
          particle_number_operator = static_cast<double(*)(double)>(&std::ceil);
        }
        this->splitParticle(particle,
                            bank,
                            static_cast<unsigned>(particle_number_operator(importance_fraction)),
                            1/importance_fraction);

      }
      else
      {
        // Stochastically terminate particle
        this->terminateParticle(particle, 1-importance_fraction);        
      }
    }
    // If particle has not collided yet, initialize the first importance.
    else
    {
      // Only initialize importance from source emission
      particle.setInitialImportance(this->getImportance(particle));
    }
  }
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::Importance );

//---------------------------------------------------------------------------//
// end MonteCarlo_Importance.cpp
//---------------------------------------------------------------------------//