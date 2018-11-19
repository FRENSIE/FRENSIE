//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCollisionForcer.cpp
//! \author Alex Robinson
//! \brief  Standard collision forcer class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_StandardCollisionForcer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
StandardCollisionForcer::StandardCollisionForcer()
  : d_forced_collision_cells()
{ /* ... */ }

// Set the cells where collision will be forced for the specified particle type
void StandardCollisionForcer::setForcedCollisionCells(
                           const MonteCarlo::FilledGeometryModel& model,
                           const ParticleType particle_type,
                           const std::vector<CellIdType>& cells,
                           const double generation_probability )
{
  this->setForcedCollisionCells( model,
                                 particle_type,
                                 std::set<CellIdType>( cells.begin(), cells.end() ),
                                 generation_probability );
}

// Set the cells where collision will be forced for the specified particle type
void StandardCollisionForcer::setForcedCollisionCells(
                           const MonteCarlo::FilledGeometryModel& model,
                           const ParticleType particle_type,
                           const std::set<CellIdType>& cells,
                           const double generation_probability )
{
  ForcedCollisionCellData& particle_forced_collision_cell_data =
    d_forced_collision_cells[particle_type];
  
  // Make sure that the requested cells are not void
  for( auto cell : cells )
  {
    TEST_FOR_EXCEPTION( model.isCellVoid( cell, particle_type ),
                        std::runtime_error,
                        "A forced collision cell cannot be void (cell "
                        << cell << " is void w.r.t. a "
                        << particle_type << "!" );

    Utility::get<0>( particle_forced_collision_cell_data ).insert( cell );
  }

  TEST_FOR_EXCEPTION( generation_probability <= 0.0,
                      std::runtime_error,
                      "The generation probability must be in (0.0,1.0]!" );

  TEST_FOR_EXCEPTION( generation_probability > 1.0,
                      std::runtime_error,
                      "The generation probability must be in (0.0,1.0]!" );

  Utility::get<1>( particle_forced_collision_cell_data ) =
    generation_probability;
}

// Check if forced collision cells have been specified for the particle type
bool StandardCollisionForcer::hasForcedCollisionCells(
                                       const ParticleType particle_type ) const
{
  return d_forced_collision_cells.find( particle_type ) !=
    d_forced_collision_cells.end();
}

// Check if a cell is a forced collision cell
bool StandardCollisionForcer::isForcedCollisionCell(
                                              const ParticleType particle_type,
                                              const CellIdType cell_id ) const
{
  ParticleTypeForcedCollisionCellMap::const_iterator particle_type_data_it =
    d_forced_collision_cells.find( particle_type );

  if( particle_type_data_it != d_forced_collision_cells.end() )
  {
    return particle_type_data_it->second.first.find( cell_id ) !=
      particle_type_data_it->second.first.end();
  }
  else
    return false;
}
  
// Return the cells where collisions will be forced
void StandardCollisionForcer::getCells(
                             const ParticleType particle_type,
                             std::set<CellIdType>& cells ) const
{
  ParticleTypeForcedCollisionCellMap::const_iterator particle_type_data_it =
    d_forced_collision_cells.find( particle_type );

  if( particle_type_data_it != d_forced_collision_cells.end() )
  {
    cells.insert( Utility::get<0>( particle_type_data_it->second ).begin(),
                  Utility::get<0>( particle_type_data_it->second ).end() );
  }
}

// Return the particle types that will have forced collisions
void StandardCollisionForcer::getParticleTypes(
                                 std::set<ParticleType>& particle_types ) const
{
  ParticleTypeForcedCollisionCellMap::const_iterator particle_type_data_it =
    d_forced_collision_cells.begin();

  while( particle_type_data_it != d_forced_collision_cells.end() )
  {
    particle_types.insert( particle_type_data_it->first );

    ++particle_type_data_it;
  }
}

// Return the generation probability
double StandardCollisionForcer::getGenerationProbability(
                                       const ParticleType particle_type ) const
{
  ParticleTypeForcedCollisionCellMap::const_iterator particle_type_data_it =
    d_forced_collision_cells.find( particle_type );

  if( particle_type_data_it != d_forced_collision_cells.end() )
    return Utility::get<1>( particle_type_data_it->second );
  else
    return 0.0;
}

// Update the particle state and bank
/*! \details The particle state that is passed in will become the uncollided 
 * branch of this track. It must be tracked through the current cell before 
 * a new collision distance is sampled. If a particle for the collided branch 
 * is created (determined by the generation probability specified for this 
 * cell) that particle history will be simulated to the forced collision site
 * and the subsequent collision will be simulated before it and any of its
 * progeny are banked.
 */
void StandardCollisionForcer::forceCollision(
          const CellIdType cell_entering,
          const double optical_path_to_next_cell,
          const SimulateParticleForOpticalPath& simulate_particle_track_method,
          ParticleState& particle,
          ParticleBank& bank ) const
{
  // Make sure that this is a forced collision cell
  testPrecondition( this->isForcedCollisionCell( particle.getParticleType(),
                                                 cell_entering ) );
  // Make sure that the optical path to the next cell is valid
  testPrecondition( optical_path_to_next_cell > 0.0 );

  const ForcedCollisionCellData& particle_forced_collision_cell_data =
    d_forced_collision_cells.find( particle.getParticleType() )->second;

  // Clone the particle before updating its weight
  std::shared_ptr<ParticleState> collided_particle;

  if( Utility::RandomNumberGenerator::getRandomNumber<double>() <=
      Utility::get<1>( particle_forced_collision_cell_data ) )
    collided_particle.reset( particle.clone() );

  // Calculate the probability that a collision does not occur in the
  // current cell
  const double pass_through_probability =
    std::exp(-optical_path_to_next_cell);
  
  // Update the particle weight by the probability that the particle does
  // not collide
  particle.multiplyWeight( pass_through_probability );

  if( collided_particle )
  {
    // Update the collided particle weight by the probability that the
    // particle does collide
    collided_particle->multiplyWeight( (1.0 - pass_through_probability)/Utility::get<1>( particle_forced_collision_cell_data ) );
    
    // Sample the optical path to the collision within the current cell
    const double optical_path_to_forced_collision =
      -std::log( 1.0 - Utility::RandomNumberGenerator::getRandomNumber<double>()*(1.0 - pass_through_probability) );

    ParticleBank local_bank;

    // Simulate the collided particle track to the sampled collision sight
    // and then undergo a collision
    simulate_particle_track_method( *collided_particle,
                                    local_bank,
                                    optical_path_to_forced_collision );

    // Add the collided particle to the bank
    bank.push( collided_particle );

    // Add the local bank to the bank (doing this last ensures that the
    // collided particle will be simulated before its progeny, assuming
    // that no bank sorting occurs)
    bank.splice( local_bank );
  }
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( StandardCollisionForcer, MonteCarlo );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardCollisionForcer );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCollisionForcer.cpp
//---------------------------------------------------------------------------//
