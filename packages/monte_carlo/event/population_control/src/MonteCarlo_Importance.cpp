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
#include "MonteCarlo_Importance.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Update the particle state and bank
void Importance::checkParticleWithPopulationController( ParticleState& particle,
                                                              ParticleBank& bank ) const
{

  //! Make sure there is a weight window where this particle is.
  if(this->isParticleInImportanceDiscretization( particle ))
  {
    // Apply importances
    if(particle.getCollisionNumber() >= 1)
    {
      if(particle.getCollisionNumber() > 1)
      {
        particle.updateImportance(this->getImportance(particle));
      }else if(particle.getCollisionNumber() == 1)
      {
        particle.setNewImportance(this->getImportance(particle));
      }

      double importance_fraction = particle.getImportancePair().second/particle.getImportancePair().first;

      if(importance_fraction > 1)
      {
        // Split particle
        if( Utility::RandomNumberGenerator::getRandomNumber<double>() < 1-std::fmod(importance_fraction, 1))
        {
          this->splitParticle(particle,
                              bank,
                              static_cast<unsigned>(floor(importance_fraction)),
                              1/importance_fraction);
        }else
        {
          this->splitParticle(particle,
                              bank,
                              static_cast<unsigned>(ceil(importance_fraction)),
                              1/importance_fraction);
        }
      }else
      {
        // Terminate particle
        this->terminateParticle(particle, 1-importance_fraction);        
      }
    }else
    {
      // Only initialize importance from source emission
      particle.setInitialImportance(this->getImportance(particle));
    }
  }
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::Importance );

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.cpp
//---------------------------------------------------------------------------//