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
  static inline double getDistanceSurfaceHit(
                                State& particle,
                                Geometry::Model::EntityId& surface_hit,
                                const double remaining_track_op )
  {
    return particle.navigator().fireRay( surface_hit ).value();
  }

  //! Update the ray safety distance
  static inline void updateRaySafetyDistance(
                                State& particle,
                                const double op_to_collision_site )
  { /* ... */ }
};

//! \brief The Ray Safety Helper class
template<typename State>
struct RaySafetyHelper<State,typename std::enable_if<std::is_base_of<MonteCarlo::ChargedParticleState,State>::value>::type>
{
  // Return the distance to the next surface hit in the particle's direction
  static inline double getDistanceSurfaceHit(
                                MonteCarlo::ChargedParticleState& particle,
                                Geometry::Model::EntityId& surface_hit,
                                const double remaining_track_op )
  {
    if ( particle.getRaySafetyDistance() < remaining_track_op )
      return particle.navigator().fireRay( surface_hit ).value();
    else
      return std::numeric_limits<double>::infinity();
  }

  //! Update the ray safety distance
  static inline void updateRaySafetyDistance(
                                MonteCarlo::ChargedParticleState& particle,
                                const double op_to_collision_site )
  {
    double new_ray_safety_distance =
      particle.getRaySafetyDistance() - op_to_collision_site;

    // Set the particle's new ray safety distance
    if( new_ray_safety_distance > 0.0 )
      particle.setRaySafetyDistance( new_ray_safety_distance );

    // Set ray safety to distance to closest boundary in all directions
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
      this->simulateParticleTrack(
              particle,
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

    this->simulateParticleTrack(
              particle,
              bank,
              d_transport_kernel->sampleOpticalPathLengthToNextCollisionSite(),
              false );
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
template<typename State>
void ParticleSimulationManager::simulateParticleTrack(
                                              State& particle,
                                              ParticleBank& bank,
                                              const double optical_path,
                                              const bool starting_from_source )
{
  // Particle tracking information (op = optical_path)
  double distance_to_surface_hit;
  double op_to_surface_hit;
  double remaining_track_op = optical_path;
  double track_start_point[3] = {particle.getXPosition(),
                                 particle.getYPosition(),
                                 particle.getZPosition()};

  bool subtrack_starting_from_source_point = starting_from_source;
  bool subtrack_starting_from_cell_boundary = false;

  CollisionForcer::SimulateParticleForOpticalPath simulate_unresolved_particle_track =
    std::bind<void>( &ParticleSimulationManager::simulateUnresolvedParticleTrack<State>,
                     std::ref( *this ),
                     std::placeholders::_1,
                     std::placeholders::_2,
                     std::placeholders::_3,
                     std::ref( subtrack_starting_from_source_point ) );

  // Surface information
  Geometry::Model::EntityId surface_hit;

  // Cell information
  double cell_total_macro_cross_section;

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
    // Fire a ray through the cell currently containing the particle
    try{
      distance_to_surface_hit =
        Details::RaySafetyHelper<State>::getDistanceSurfaceHit( particle, surface_hit, remaining_track_op );
    }
    CATCH_LOST_PARTICLE_AND_BREAK( particle );

    // Get the total cross section for the cell
    if( !d_model->isCellVoid<State>( particle.getCell() ) )
    {
      cell_total_macro_cross_section =
        d_model->getMacroscopicTotalCrossSectionQuick( particle );
    }
    else
      cell_total_macro_cross_section = 0.0;

    // Convert the distance to the surface to optical path
    op_to_surface_hit = distance_to_surface_hit*cell_total_macro_cross_section;

    // The particle passes through this cell to the next
    if( op_to_surface_hit < remaining_track_op )
    {
      // Force a collision - if required
      if( subtrack_starting_from_source_point ||
          subtrack_starting_from_cell_boundary )
      {
        d_collision_forcer->forceCollision( particle.getCell(),
                                            op_to_surface_hit,
                                            simulate_unresolved_particle_track,
                                            particle,
                                            bank );
      }

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
                                            cell_total_macro_cross_section,
                                            track_start_point );

      // Update the particle state before the collision (e.g. roulette/split
      // using weight window mesh)
      ParticleBank local_bank;

      d_weight_windows->updateParticleState( particle, local_bank );

      // Undergo a collision with the material in the cell
      if( particle )
      {
        try{
          d_collision_kernel->collideWithCellMaterial( particle, bank );
        }
        CATCH_LOST_PARTICLE( particle );
      }

      // All split particles must also undergo a collision
      while( !local_bank.isEmpty() )
      {
        ParticleBank next_gen_local_bank;

        try{
          d_collision_kernel->collideWithCellMaterial(
                                      dynamic_cast<State&>( local_bank.top() ),
                                      next_gen_local_bank );
        }
        CATCH_LOST_PARTICLE_AND_CONTINUE( local_bank.top(), local_bank.pop() );

        std::shared_ptr<ParticleState> local_particle;

        local_bank.pop( local_particle );

        bank.push( local_particle );
        bank.splice( next_gen_local_bank );
      }

      // This track is finished
      break;
    }
  }

  if( !particle )
  {
    d_event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                                      particle,
                                                      track_start_point,
                                                      particle.getPosition() );

    d_event_handler->updateObserversFromParticleGoneGlobalEvent( particle );
  }
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
                                   const double cell_total_macro_cross_section,
                                   const double track_start_position[3] )
{
  // Calculate the distance to the collision site
  double distance_to_collision =
    op_to_collision_site/cell_total_macro_cross_section;

  // Advance the particle
  particle.navigator().advanceBySubstep( *Utility::reinterpretAsQuantity<Geometry::Navigator::Length>( &distance_to_collision ) );

  // Update the particle's ray safety distance
  Details::RaySafetyHelper<State>::updateRaySafetyDistance( particle, op_to_collision_site );

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
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//
