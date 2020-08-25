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
void WeightWindowBase::checkParticleWithPopulationController( ParticleState& particle,
                                                              ParticleBank& bank ) const
{

  //! Make sure there is a weight window where this particle is.
  if(this->isParticleInImportanceDiscretization( particle ))
  {
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

      if(importance_fraction < 1)
      {

      }else
      {
        // Terminate
      }
      

    }else
    {
      // Only initialize importance from source emission
      particle.setInitialImportance(this->getImportance(particle));
    }
  }
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::WeightWindowBase );

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.cpp
//---------------------------------------------------------------------------//