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

//! Log lost particle details
#define LOG_LOST_PARTICLE_DETAILS( particle )   \
  FRENSIE_LOG_TAGGED_WARNING(                   \
       "Lost Particle",                         \
       "history " << particle.getHistoryNumber() <<        \
       ", generation " << particle.getGenerationNumber(); \
                                                          \
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Lost Particle State Dump", \
                                   particle )

//! Macro for catching a lost particle and breaking a loop
#define CATCH_LOST_PARTICLE_AND_BREAK( particle )       \
  catch( std::runtime_error& exception )                \
  {                                                   \
    particle.setAsLost();                               \
                                                        \
    FRENSIE_LOG_NESTED_ERROR( exception.what() );       \
                                                        \
    LOG_LOST_PARTICLE_DETAILS( particle );              \
                                                        \
    break;                                              \
  }

//! Macro for catching a lost source particle
#define CATCH_LOST_SOURCE_PARTICLE_AND_CONTINUE( bank ) \
  catch( std::runtime_error& exception )                \
  {                                                   \
    bank.top().setAsLost();                             \
                                                        \
    FRENSIE_LOG_NESTED_ERROR( exception.what() );       \
                                                        \
    LOG_LOST_PARTICLE_DETAILS( bank.top() );            \
                                                        \
    bank.pop();                                         \
                                                        \
    continue;                                           \
  }

namespace MonteCarlo{

// Simulate a resolved particle
template<typename State>
void ParticleSimulationManager::simulateParticle(
                                            ParticleState& unresolved_particle,
                                            ParticleBank& bank,
                                            const bool source_particle )
{
  // Make sure that the particle is embedded in the model
  testPrecondition( !particle.isEmbeddedInModel( *d_model ) );

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
                                 particle.getZPosition()}

  bool subtrack_starting_from_source_point = starting_from_source;
  bool subtrack_starting_from_cell_boundary = false;

  CollisionForcer::SimulateParticleForOpticalPath simulate_unresolved_particle_track =
    std::bind<void>( &ParticleSimulationManager::simulateParticleTrack<State>,
                     std::cref( *this ),
                     std::placeholders::_1,
                     std::placeholders::_2,
                     std::placeholders::_3 );

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
        particle.navigator().fireInternalRay( surface_hit );
    }
    CATCH_LOST_PARTICLE_AND_BREAK( particle );

    // Get the total cross section for the cell
    if( d_model->isCellVoid<State>( particle.getCell() ) )
    {
      cell_total_macro_cross_section =
        d_model->getMacroscopicTotalCrossSectionQuick( particle );
    }
    else
      cell_total_macro_cross_section = 0.0;

    // Convert the distance to the surface to optical path
    op_to_surface_hit = distance_to_surace_hit*cell_total_macro_cross_section;

    // The particle passes through this cell to the next
    if( op_to_surface_hit < remaining_subtrack_op )
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
                                             distance_to_surface_hit,
                                             track_start_point );
      }
      CATCH_LOST_PARTICLE_AND_BREAK( particle );

      // The particle has exited the geometry
      if( d_model->isTerminationCell( particle.getCell() ) )
      {
        d_event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                                      particle,
                                                      track_start_point,
                                                      particle.getPosition() );
        
        particle.setAsGone();

        break;
      }

      // Update the remaining subtrack mfp
      remaining_track_op -= op_to_surface_hit;

      // After the first subtrack the particle can no longer be starting from
      // a source point
      subtrack_starting_from_source_point = false;
      subtrack_starting_from_cell_boundary = true;
    }

    // A collision occurs in this cell
    else
    {
      this->advanceParticleToCollisionSite( particle,
                                            remaining_subtrack_op,
                                            cell_total_macro_cross_section,
                                            track_start_point );

      // Update the particle state before the collision (e.g. roulette/split
      // using weight window mesh)
      ParticleBank local_bank;
      
      d_weight_windows->updateParticleState( particle, local_bank );

      // Undergo a collision with the material in the cell
      if( particle )
        d_collision_kernel->collideWithCellMaterial( particle, bank );

      // All split particles must also undergo a collision
      while( !local_bank.isEmpty() )
      {
        ParticleBank next_gen_local_bank;

        d_collision_kernel->collideWithCellMaterial(
                                      dynamic_cast<State&>( local_bank.top() ),
                                      next_gen_local_bank );

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
    d_event_handler->updateObserversFromParticleGoneGlobalEvent( particle );
}

// Advance a particle to the cell boundary
template<typename State>
void ParticleSimulationManager::advanceParticleToCellBoundary(
                                             State& particle,
                                             ParticleBank& bank,
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
                                                              surface_hit,
                                                              surface_normal );

  if( reflected )
  {
    d_event_handler->updateObserversFromParticleCrossingSurfaceEvent(
                                                              particle,
                                                              surface_hit,
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
    remaining_subtrack_op/cell_total_macro_cross_section;

  // Advance the particle
  particle.navigator().advanceBySubstep( distance_to_collision );

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
