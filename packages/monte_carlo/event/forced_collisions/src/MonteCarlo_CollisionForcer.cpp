//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionForcer.cpp
//! \author Alex Robinson
//! \brief  Collision forcer class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CollisionForcer.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Constructor (set)
CollisionForcer::CollisionForcer(
                   const size_t id,
                   const MonteCarlo::FilledGeometryModel& model,
                   const std::set<ParticleType>& particle_types,
                   const std::set<Geometry::Model::InternalCellHandle>& cells )
{

}

// Constructor (vector)
CollisionForcer::CollisionForcer(
                const size_t id,
                const MonteCarlo::FilledGeometryModel& model,
                const std::set<ParticleType>& particle_types,
                const std::vector<Geometry::Model::InternalCellHandle>& cells )
{

}

// Update the particle state and bank
void CollisionForcer::updateFromParticleEnteringCellEvent(
                       const Geometry::Model::InternalCellHandle cell_entering,
                       const double optical_path_to_next_cell,
                       const Callback& callback,
                       ParticleState& particle,
                       ParticleBank& bank ) const
{
  // Clone the particle before updating its weight
  std::shared_ptr<ParticleState>& collided_particle( particle->clone() );

  // Calculate the probability that a collision does not occur in the current
  // cell
  const double pass_through_probability = std::exp(-optical_path_to_next_cell);
  
  // Update the particle weight by the probability that the particle does
  // not collide
  particle->multiplyWeight( pass_through_probability );

  // Update the collided particle weight by the probability that the particle
  // does collide
  collided_particle->multiplyWeight( 1.0 - pass_through_probability );

  // Sample the optical path to the collision within the current cell
  const double optical_path_to_forced_collision =
    -std::log( 1.0 - Utility::RandomNumberGenerator::getRandomNumber<double>()*(1.0 - pass_through_probability) );

  // Execute the callback using the sampled optical path
  callback( particle, bank, optical_path_to_forced_collision );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionForcer.cpp
//---------------------------------------------------------------------------//
