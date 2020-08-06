//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager_def.hpp
//! \author Alex Robinson
//! \brief  Particle simulation manager template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_DEF_HPP
#define MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_DEF_HPP

// Std Lib Includes
#include <functional>
#include <type_traits>

//! Log lost particle details
#define LOG_LOST_PARTICLE_DETAILS( particle )   \
  FRENSIE_LOG_TAGGED_WARNING(                   \
       "Lost Particle",                         \
       "history " << particle.getHistoryNumber() <<        \
       ", generation " << particle.getGenerationNumber() << \
       ", collision number " << particle.getCollisionNumber() );        \
                                                                        \
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Lost Particle State Dump", \
                                   "\n" << particle )

//! Macro for catching a lost particle and breaking a loop
#define CATCH_LOST_PARTICLE_AND_BREAK( particle )       \
  catch( const std::runtime_error& exception )                \
  {                                                   \
    particle.setAsLost();                               \
                                                        \
    LOG_LOST_PARTICLE_DETAILS( particle );              \
                                                        \
    FRENSIE_LOG_NESTED_ERROR( exception.what() );       \
                                                        \
    break;                                              \
  }

//! Macro for catching a lost particle
#define CATCH_LOST_PARTICLE( particle, ... )                  \
  catch( const std::runtime_error& exception )                \
  {                                                   \
    particle.setAsLost();                               \
                                                        \
    LOG_LOST_PARTICLE_DETAILS( particle );              \
                                                        \
    FRENSIE_LOG_NESTED_ERROR( exception.what() );       \
                                                        \
    __VA_ARGS__;                                        \
  }

//! Macro for catching a lost particle
#define CATCH_LOST_PARTICLE_AND_CONTINUE( particle, ... )     \
  catch( const std::runtime_error& exception )                \
  {                                                   \
    particle.setAsLost();                               \
                                                        \
    LOG_LOST_PARTICLE_DETAILS( particle );              \
                                                        \
    FRENSIE_LOG_NESTED_ERROR( exception.what() );       \
                                                        \
    __VA_ARGS__;                                        \
                                                        \
    continue;                                           \
  }

namespace MonteCarlo{

namespace Details{

//! \brief The Ray Safety Helper class
template<typename State, typename Enabled=void>
struct RaySafetyHelper
{
  //! Return the distance to the next surface hit in the particle's direction
  static inline double getDistanceToSurfaceHit(
                                State& particle,
                                Geometry::Model::EntityId& surface_hit,
                                const double )
  {
    return particle.navigator().fireRay( surface_hit ).value();
  }

  //! Update the ray safety distance
  static inline void updateRaySafetyDistance(
                                 State&,
                                 const double )
  { /* ... */ }
};

//! \brief The Ray Safety Helper class
template<typename State>
struct RaySafetyHelper<State,typename std::enable_if<std::is_base_of<MonteCarlo::ChargedParticleState,State>::value>::type>
{
  // Return the distance to the next surface hit in the particle's direction
  static inline double getDistanceToSurfaceHit(
                                        State& particle,
                                        Geometry::Model::EntityId& surface_hit,
                                        const double remaining_track )
  {
    if ( particle.getRaySafetyDistance() < remaining_track )
      return particle.navigator().fireRay( surface_hit ).value();
    else
      return std::numeric_limits<double>::infinity();
  }

  //! Update the ray safety distance
  static inline void updateRaySafetyDistance(
                                MonteCarlo::ChargedParticleState& particle,
                                const double distance_to_collision_site )
  {
    double new_ray_safety_distance =
      particle.getRaySafetyDistance() - distance_to_collision_site;

    // Set the particle's new ray safety distance
    if( new_ray_safety_distance > 0.0 )
      particle.setRaySafetyDistance( new_ray_safety_distance );

    // Set ray safety distance to closest boundary in all directions
    else
    {
      particle.setRaySafetyDistance( particle.navigator().getDistanceToClosestBoundary().value() );
    }

  }
};

} // end Details namespace

// Simulate a resolved particle
template<typename State>
void ParticleSimulationManager::simulateParticle(
                                            ParticleState& unresolved_particle,
                                            ParticleBank& bank,
                                            const bool source_particle )
{
  // Make sure that the particle is embedded in the model
  testPrecondition( unresolved_particle.isEmbeddedInModel( *d_model ) );

  this->simulateParticleImpl<State>( unresolved_particle,
                                     bank,
                                     source_particle,
                                     std::bind<void>( &ParticleSimulationManager::simulateParticleTrack<State>,
                                                      std::ref( *this ),
                                                      std::placeholders::_1,
                                                      std::placeholders::_2,
                                                      std::placeholders::_3,
                                                      std::placeholders::_4 ) );
}

// Simulate a resolved particle using the "alternative" tracking method
template<typename State>
void ParticleSimulationManager::simulateParticleAlternative(
                                            ParticleState& unresolved_particle,
                                            ParticleBank& bank,
                                            const bool source_particle )
{
  // Make sure that the particle is embedded in the model
  testPrecondition( unresolved_particle.isEmbeddedInModel( *d_model ) );

  this->simulateParticleImpl<State>( unresolved_particle,
                                     bank,
                                     source_particle,
                                     std::bind<void>( &ParticleSimulationManager::simulateParticleTrackAlternative<State>,
                                                      std::ref( *this ),
                                                      std::placeholders::_1,
                                                      std::placeholders::_2,
                                                      std::placeholders::_3,
                                                      std::placeholders::_4 ) );
}

// Simulate a resolved particle implementation
template<typename State, typename SimulateParticleTrackMethod>
void ParticleSimulationManager::simulateParticleImpl(
                   ParticleState& unresolved_particle,
                   ParticleBank& bank,
                   const bool source_particle,
                   const SimulateParticleTrackMethod& simulate_particle_track )
{
  // Make sure that the particle is embedded in the model
  testPrecondition( unresolved_particle.isEmbeddedInModel( *d_model ) );

  // Resolve the particle state
  State& particle = dynamic_cast<State&>( unresolved_particle );

  // Simulate a particle subtrack of random optical path length starting from a
  // source point
  if( source_particle )
  {
    // Check if the particle energy is below the cutoff
    if( particle.getEnergy() < d_properties->getMinParticleEnergy<State>() )
    {
      FRENSIE_LOG_WARNING( particle.getParticleType() <<
                           " born below global cutoff energy. Check source "
                           "definition!\n" << particle );

      particle.setAsGone();
    }
    // Check if the particle energy is above the max energy
    if( particle.getEnergy() > d_properties->getMaxParticleEnergy<State>() )
    {
      FRENSIE_LOG_WARNING( particle.getParticleType() <<
                           " born above global max energy. Check source "
                           "definition!\n" << particle );

      particle.setAsGone();
    }
    else
    {
      // Inject first check here
      d_population_controller->checkParticleWithPopulationController( particle, bank );
      simulate_particle_track( particle,
                               bank,
                               d_transport_kernel->sampleOpticalPathLengthToNextCollisionSite(),
                               true );
    }
  }

  // Simulate a particle subtrack of random optical path length until the
  // particle is gone
  while( particle )
  {
    // Check if the particle energy is below the cutoff
    if( particle.getEnergy() < d_properties->getMinParticleEnergy<State>() )
    {
      particle.setAsGone();
      break;
    }
    // Check if the particle energy is above the max energy
    if( particle.getEnergy() > d_properties->getMaxParticleEnergy<State>() )
    {
      particle.setAsGone();
      break;
    }

    // Roulette the particle if it is below the threshold weight
    d_weight_roulette->rouletteParticleWeight( particle );

    if( particle )
    {
      simulate_particle_track( particle,
                               bank,
                               d_transport_kernel->sampleOpticalPathLengthToNextCollisionSite(),
                               false );
    }
  }
}

// Simulate an unresolved particle track
template<typename State>
void ParticleSimulationManager::simulateUnresolvedParticleTrack(
                                            ParticleState& unresolved_particle,
                                            ParticleBank& bank,
                                            const double optical_path,
                                            const bool starting_from_source )
{
  this->simulateParticleTrack( dynamic_cast<State&>( unresolved_particle ),
                               bank,
                               optical_path,
                               starting_from_source );
}

// Simulate a resolved particle track
// Note: Forced collisions cannot be done with this tracking method. Use the
//       "alternative" tracking method when forced collisions are requested.
template<typename State>
void ParticleSimulationManager::simulateParticleTrack(
                                              State& particle,
                                              ParticleBank& bank,
                                              const double optical_path,
                                              const bool starting_from_source )
{
  // Particle tracking information (op = optical_path)
  double remaining_track_op = optical_path;
  double op_to_surface_hit;
  double distance_to_surface_hit;

  double track_start_point[3] = {particle.getXPosition(),
                                 particle.getYPosition(),
                                 particle.getZPosition()};

  bool subtrack_starting_from_source_point = starting_from_source;
  bool subtrack_starting_from_cell_boundary = false;

  // Surface information
  Geometry::Model::EntityId surface_hit;

  // Cell information
  double cell_total_macro_cross_section;

  // Records if global subtrack ending event has been dispatched
  bool global_subtrack_ending_event_dispatched = false;

  // If the particle started from a source point, update the relevant
  // particle entering cell event observers
  if( starting_from_source )
  {
    d_event_handler->updateObserversFromParticleEnteringCellEvent(
                                                particle, particle.getCell() );
  }

  // Ray trace until the necessary number of optical paths have been traveled
  while( true )
  {
    // Get the total cross section for the cell
    if( !d_model->isCellVoid<State>( particle.getCell() ) )
    {
      cell_total_macro_cross_section =
        d_model->getMacroscopicTotalForwardCrossSectionQuick( particle );
    }
    else
      cell_total_macro_cross_section = 0.0;

    double cell_distance_to_collision = remaining_track_op/cell_total_macro_cross_section;

    // Fire a ray through the cell currently containing the particle
    try{
      distance_to_surface_hit =
        Details::RaySafetyHelper<State>::getDistanceToSurfaceHit( particle, surface_hit, cell_distance_to_collision );
    }
    CATCH_LOST_PARTICLE_AND_BREAK( particle );

    // Convert the distance to the surface to optical path
    op_to_surface_hit = distance_to_surface_hit*cell_total_macro_cross_section;

    // The particle passes through this cell to the next
    if( op_to_surface_hit < remaining_track_op )
    {
      try{
        this->advanceParticleToCellBoundary( particle,
                                             surface_hit,
                                             distance_to_surface_hit );
      }
      CATCH_LOST_PARTICLE_AND_BREAK( particle );

      // The particle has exited the geometry
      if( d_model->isTerminationCell( particle.getCell() ) )
      {
        particle.setAsGone();

        break;
      }

      // Update the remaining subtrack mfp
      remaining_track_op -= op_to_surface_hit;

      // Set the ray safety distance to zero
      particle.setRaySafetyDistance( 0.0 );

      // After the first subtrack the particle can no longer be starting from
      // a source point
      subtrack_starting_from_source_point = false;
      subtrack_starting_from_cell_boundary = true;
    }

    // A collision occurs in this cell
    else
    {
      this->advanceParticleToCollisionSite( particle,
                                            remaining_track_op,
                                            cell_distance_to_collision,
                                            track_start_point,
                                            global_subtrack_ending_event_dispatched );

      // Update the particle's ray safety distance
      Details::RaySafetyHelper<State>::updateRaySafetyDistance(
                                                  particle,
                                                  cell_distance_to_collision );

      this->collideWithCellMaterial( particle, bank );

      // This track is finished
      break;
    }
  }

  if( !global_subtrack_ending_event_dispatched )
  {
    d_event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                                      particle,
                                                      track_start_point,
                                                      particle.getPosition() );
  }

  if( !particle )
    d_event_handler->updateObserversFromParticleGoneGlobalEvent( particle );
}

// Simulate an unresolved particle track using the "alternative" method
template<typename State>
void ParticleSimulationManager::simulateUnresolvedParticleTrackAlternative(
                                            ParticleState& unresolved_particle,
                                            ParticleBank& bank,
                                            const double optical_path,
                                            const bool starting_from_source )
{
  this->simulateParticleTrackAlternative(
                                   dynamic_cast<State&>( unresolved_particle ),
                                   bank,
                                   optical_path,
                                   starting_from_source );
}

// Simulate a resolved particle track using the "alternative" method
// Note: This method must be used if forced collisions are used.
template<typename State>
void ParticleSimulationManager::simulateParticleTrackAlternative(
                                             State& particle,
                                             ParticleBank& bank,
                                             const double initial_optical_path,
                                             const bool starting_from_source )
{
  // Particle tracking information (op = optical_path)
  double cell_op_to_collision = initial_optical_path;
  double cell_distance_to_collision;
  double distance_to_surface_hit;

  double track_start_point[3] = {particle.getXPosition(),
                                 particle.getYPosition(),
                                 particle.getZPosition()};

  bool subtrack_starting_from_source_point = starting_from_source;

  // This will only be set to true once the first surface has been crossed -
  // it will not be set to true initially even if the particle lies on a
  // surface
  bool subtrack_starting_from_cell_boundary = false;

  // Surface information
  Geometry::Model::EntityId surface_hit;

  // Cell information
  double cell_total_macro_cross_section;

  // Records if global subtrack ending event has been dispatched
  bool global_subtrack_ending_event_dispatched = false;

  // If the particle started from a source point, update the relevant
  // particle entering cell event observers
  if( starting_from_source )
  {
    d_event_handler->updateObserversFromParticleEnteringCellEvent(
                                                particle, particle.getCell() );
  }

  // Ray trace until a collision occurs
  while( true )
  {
    // Fire a ray through the cell currently containing the particle
    try{
      distance_to_surface_hit = particle.navigator().fireRay( surface_hit ).value();
    }
    CATCH_LOST_PARTICLE_AND_BREAK( particle );

    // Get the total cross section for the cell and the distance to collision
    if( !d_model->isCellVoid<State>( particle.getCell() ) )
    {
      cell_total_macro_cross_section =
        d_model->getMacroscopicTotalForwardCrossSectionQuick( particle );

      // Only consider a forced collision cell if the subtrack is starting from
      // the source or from a cell boundary
      if( (subtrack_starting_from_source_point ||
           subtrack_starting_from_cell_boundary) &&
          d_collision_forcer->isForcedCollisionCell<State>(particle.getCell()))
      {
        // This event must be dispatched before the particle weight changes
        d_event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                                      particle,
                                                      track_start_point,
                                                      particle.getPosition() );

        track_start_point[0] = particle.getXPosition();
        track_start_point[1] = particle.getYPosition();
        track_start_point[2] = particle.getZPosition();

        d_collision_forcer->forceCollision(
                        particle.getCell(),
                        cell_total_macro_cross_section*distance_to_surface_hit,
                        std::bind<void>( &ParticleSimulationManager::simulateUnresolvedParticleTrackAlternative<State>,
                                         std::ref( *this ),
                                         std::placeholders::_1,
                                         std::placeholders::_2,
                                         std::placeholders::_3,
                                         false ),
                        particle,
                        bank );

        // The current particle becomes the uncollided branch of the track and
        // must therefore pass through the current cell
        cell_distance_to_collision =
          std::numeric_limits<double>::infinity();
      }

      // Normal cell
      else
      {
        cell_distance_to_collision =
          cell_op_to_collision/cell_total_macro_cross_section;
      }
    }

    // Void cell
    else
    {
      cell_total_macro_cross_section = 0.0;

      cell_distance_to_collision = std::numeric_limits<double>::infinity();
    }

    // The particle passes through this cell to the next
    if( distance_to_surface_hit < cell_distance_to_collision )
    {
      try{
        this->advanceParticleToCellBoundary( particle,
                                             surface_hit,
                                             distance_to_surface_hit );
      }
      CATCH_LOST_PARTICLE_AND_BREAK( particle );

      // The particle has exited the geometry
      if( d_model->isTerminationCell( particle.getCell() ) )
      {
        particle.setAsGone();

        break;
      }

      // Set the ray safety distance to zero
      particle.setRaySafetyDistance( 0.0 );

      // After the first subtrack the particle can no longer be starting from
      // a source point, but it will be starting from a cell boundary
      subtrack_starting_from_source_point = false;
      subtrack_starting_from_cell_boundary = true;

      // Sample the optical path to collision in the new cell
      cell_op_to_collision =
        d_transport_kernel->sampleOpticalPathLengthToNextCollisionSite();
    }

    // A collision occurs in this cell
    else
    {
      this->advanceParticleToCollisionSite( particle,
                                            cell_op_to_collision,
                                            cell_distance_to_collision,
                                            track_start_point,
                                            global_subtrack_ending_event_dispatched );

      this->collideWithCellMaterial( particle, bank );

      // This track is finished
      break;
    }
  }

  if( !global_subtrack_ending_event_dispatched )
  {
    d_event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                                      particle,
                                                      track_start_point,
                                                      particle.getPosition() );
  }

  if( !particle )
    d_event_handler->updateObserversFromParticleGoneGlobalEvent( particle );
}

// Advance a particle to the cell boundary
template<typename State>
void ParticleSimulationManager::advanceParticleToCellBoundary(
                              State& particle,
                              const Geometry::Model::EntityId surface_to_cross,
                              const double distance_to_surface )
{
  // Advance the particle to the cell boundary
  // Note: this will change the particle's cell
  Geometry::Model::EntityId start_cell = particle.getCell();

  double surface_normal[3];
  bool reflected = particle.navigator().advanceToCellBoundary( surface_normal );

  // Update the observers: particle subtrack ending in cell event
  d_event_handler->updateObserversFromParticleSubtrackEndingInCellEvent(
                                                         particle,
                                                         start_cell,
                                                         distance_to_surface );

  // Update the observers: particle leaving cell event
  d_event_handler->updateObserversFromParticleLeavingCellEvent( particle, start_cell );

  // Update the observers: particle crossing surface event
  d_event_handler->updateObserversFromParticleCrossingSurfaceEvent(
                                                              particle,
                                                              surface_to_cross,
                                                              surface_normal );

  if( reflected )
  {
    d_event_handler->updateObserversFromParticleCrossingSurfaceEvent(
                                                              particle,
                                                              surface_to_cross,
                                                              surface_normal );

  }

  // Update the observers: particle entering cell event
  d_event_handler->updateObserversFromParticleEnteringCellEvent( particle, particle.getCell() );
}

// Advance a particle to a collision site
template<typename State>
void ParticleSimulationManager::advanceParticleToCollisionSite(
                                   State& particle,
                                   const double op_to_collision_site,
                                   const double distance_to_collision,
                                   const double track_start_position[3],
                                   bool& global_subtrack_ending_event_dispatched )
{
  // Advance the particle
  particle.navigator().advanceBySubstep( *Utility::reinterpretAsQuantity<Geometry::Navigator::Length>( &distance_to_collision ) );

  // Update the observers: particle subtrack ending in cell event
  d_event_handler->updateObserversFromParticleSubtrackEndingInCellEvent(
                                                       particle,
                                                       particle.getCell(),
                                                       distance_to_collision );

  // Update the observers: particle subtrack ending global event
  d_event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                                      particle,
                                                      track_start_position,
                                                      particle.getPosition() );

  global_subtrack_ending_event_dispatched = true;
}

// Collide with the cell material
template<typename State>
void ParticleSimulationManager::collideWithCellMaterial( State& particle,
                                                         ParticleBank& bank )
{
  ParticleBank local_bank;

  // Undergo a collision with the material in the cell
  try{
    d_collision_kernel->collideWithCellMaterial( particle, local_bank );
  }
  CATCH_LOST_PARTICLE( particle );

  // Apply the population managers to the original particle and to each of its
  // progeny. Multiple particle mode will result in all different particle types using the same
  // population manager for now. Needs to be fixed later if desired.
  if( particle )
  {
    d_population_controller->checkParticleWithPopulationController( particle, bank );
  }

  while( !local_bank.isEmpty() )
  {
    ParticleBank split_particle_bank;

    if( local_bank.top() )
    {
      d_population_controller->checkParticleWithPopulationController( local_bank.top(),
                                                                      split_particle_bank );
    }

    std::shared_ptr<ParticleState> local_particle;

    local_bank.pop( local_particle );

    // If the particle wasn't terminated, add it to the bank
    if( local_particle )
    {
      bank.push( local_particle );
      bank.splice( split_particle_bank );
    }
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//
