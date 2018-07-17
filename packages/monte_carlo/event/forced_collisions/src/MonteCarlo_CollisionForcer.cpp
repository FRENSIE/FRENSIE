//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionForcer.cpp
//! \author Alex Robinson
//! \brief  Collision forcer class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_CollisionForcer.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
CollisionForcer::CollisionForcer()
  : d_id( std::numeric_limits<size_t>::max() )
{ /* ... */ }

// Constructor (vector)
CollisionForcer::CollisionForcer(
                const size_t id,
                const MonteCarlo::FilledGeometryModel& model,
                const std::set<ParticleType>& particle_types,
                const std::vector<Geometry::Model::EntityId>& cells,
                const double generation_probability )
  : CollisionForcer( id,
                     model,
                     particle_types,
                     std::set<Geometry::Model::EntityId>( cells.begin(), cells.end() ),
                     generation_probability )
{ /* ... */ }
  
// Constructor (set)
CollisionForcer::CollisionForcer(
                   const size_t id,
                   const MonteCarlo::FilledGeometryModel& model,
                   const std::set<ParticleType>& particle_types,
                   const std::set<Geometry::Model::EntityId>& cells,
                   const double generation_probability )
  : d_id( id ),
    d_particle_types( particle_types ),
    d_cells( cells ),
    d_generation_probability( generation_probability )
{
  // Make sure that the requested cells are not void
  for( auto particle_type : particle_types )
  {
    for( auto cell : cells )
    {
       TEST_FOR_EXCEPTION( model.isCellVoid( cell, particle_type ),
                           std::runtime_error,
                           "A forced collision cell cannot be void (cell "
                           << cell << " is void w.r.t. a "
                           << particle_type << "!" );
    }
  }
  
  // Make sure that the generation probability is valid
  TEST_FOR_EXCEPTION( generation_probability <= 0.0,
                      std::runtime_error,
                      "The generation probability must be between 0.0 and "
                      "1.0!" );

  TEST_FOR_EXCEPTION( generation_probability > 1.0,
                      std::runtime_error,
                      "The generation probability must be between 0.0 and "
                      "1.0!" );
}

// Return the cells where collisions will be forced
const std::set<Geometry::Model::EntityId>& CollisionForcer::getCells() const
{
  return d_cells;
}

// Return the particle types that will have forced collisions
const std::set<ParticleType>& CollisionForcer::getParticleTypes() const
{
  return d_particle_types;
}

// Return the generation probability
double CollisionForcer::getGenerationProbability() const
{
  return d_generation_probability;
}

// Update the particle state and bank
void CollisionForcer::updateFromParticleEnteringCellEvent(
          const Geometry::Model::EntityId cell_entering,
          const double optical_path_to_next_cell,
          const SimulateParticleForOpticalPath& simulate_particle_track_method,
          ParticleState& particle,
          ParticleBank& bank ) const
{
  // Make sure that the particle type is supported
  testPrecondition( d_particle_types.find( particle.getParticleType() ) !=
                    d_particle_types.end() );
  // Make sure that the cell is valid
  testPrecondition( d_cells.find( particle.getCell() ) != d_cells.end() );
  // Make sure that the optical path to the next cell is valid
  testPrecondition( optical_path_to_next_cell > 0.0 );

  // Clone the particle before updating its weight
  std::shared_ptr<ParticleState> collided_particle;

  if( Utility::RandomNumberGenerator::getRandomNumber<double>() <=
      d_generation_probability )
    collided_particle.reset( particle.clone() );

  // Calculate the probability that a collision does not occur in the current
  // cell
  const double pass_through_probability = std::exp(-optical_path_to_next_cell);
  
  // Update the particle weight by the probability that the particle does
  // not collide
  particle.multiplyWeight( pass_through_probability );

  if( collided_particle )
  {
    // Update the collided particle weight by the probability that the particle
    // does collide
    collided_particle->multiplyWeight( (1.0 - pass_through_probability)/d_generation_probability );

    // Sample the optical path to the collision within the current cell
    const double optical_path_to_forced_collision =
      -std::log( 1.0 - Utility::RandomNumberGenerator::getRandomNumber<double>()*(1.0 - pass_through_probability) );

    ParticleBank local_bank;

    // Simulate the collided particle track to the sampled collision sight and
    // then undergo a collision
    simulate_particle_track_method( *collided_particle,
                                    local_bank,
                                    optical_path_to_forced_collision );

    // Add the collided particle to the bank
    bank.push( collided_particle );

    // Add the local bank to the bank (doing this last ensures that the
    // collided particle will be simulated before its progeny, assuming that
    // no bank sorting occurs)
    bank.splice( local_bank );
  }
}
  
} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::CollisionForcer );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::CollisionForcer );

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionForcer.cpp
//---------------------------------------------------------------------------//
