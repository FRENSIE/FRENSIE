//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PopulationControl.cpp
//! \author Philip Britt
//! \brief  Population Control class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE includes
#include "MonteCarlo_PopulationControl.hpp"

namespace MonteCarlo{

// Method that splits particle into equal number of weights based on number of particles split into
void PopulationControl::splitParticle( ParticleState& particle,
                      ParticleBank& bank,
                      unsigned number_of_particles ) const
{
  
}

// Method that splits particles with weights based on the expectation weight of particles
void PopulationControl::splitParticle( ParticleState& particle,
                    ParticleBank& bank,
                    unsigned number_of_particles,
                    double expectation_weight) const
{

}

// Method that terminates particle 
void PopulationControl::terminateParticle( ParticleState& particle,
                        ParticleBank& bank,
                        double termination_probability) const
{

}

}// end MonteCarlo namespace