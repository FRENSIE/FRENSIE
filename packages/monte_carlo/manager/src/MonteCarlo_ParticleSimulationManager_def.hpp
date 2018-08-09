//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager_def.hpp
//! \author Alex Robinson
//! \brief  Particle simulation manager template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_DEF_HPP
#define MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_DEF_HPP

namespace MonteCarlo{

// Simulate a resolved particle
template<typename State>
void ParticleSimulationManager::simulateParticle(
                                            ParticleState& unresolved_particle,
                                            ParticleBank& bank,
                                            const bool source_particle ) const
{

}

// Simulate an unresolved particle track
template<typename State>
void ParticleSimulationManager::simulateUnresolvedParticleTrack(
                                        ParticleState& unresolved_particle,
                                        ParticleBank& bank,
                                        const double optical_path,
                                        const bool starting_from_source ) const
{

}

// Simulate a resolved particle track
template<typename State>
void ParticleSimulationManager::simulateParticleTrack(
                                        State& particle,
                                        ParticleBank& bank,
                                        const double optical_path,
                                        const bool starting_from_source ) const
{

}

// Simulate an unresolved particle collision
template<typename State>
void ParticleSimulationManager::simulateUnresolvedParticleCollision(
                                            ParticleState& unresolved_particle,
                                            ParticleBank& bank ) const
{

}

// Simulate a resolved particle collision
template<typename State>
void ParticleSimulationManager::simulateParticleCollision( State& particle,
                                                           ParticleBank& bank )
{

}

// Advance a particle to the cell boundary
template<typename State>
void ParticleSimulationManager::advanceParticleToCellBoundary(
                                       State& particle,
                                       ParticleBank& bank,
                                       const double distance_to_surface,
                                       const double subtrack_start_time ) const
{

}

// Advance a particle to a collision site
template<typename State>
void ParticleSimulationManager::advanceParticleToCollisionSite(
                                   State& particle,
                                   const double op_to_collision_site,
                                   const double cell_total_macro_cross_section,
                                   const double subtrack_start_time,
                                   const double track_start_time,
                                   const double track_start_position[3] ) const
{

}

// Save the data to an archive
template<typename Archive>
void ParticleSimulationManager::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_simulation_name );
  ar & BOOST_SERIALIZATION_NVP( d_model );
  ar & BOOST_SERIALIZATION_NVP( d_source );
  ar & BOOST_SERIALIZATION_NVP( d_event_handler );
  ar & BOOST_SERIALIZATION_NVP( d_weight_windows );
  ar & BOOST_SERIALIZATION_NVP( d_collision_forcer );
  ar & BOOST_SERIALIZATION_NVP( d_properties );
  ar & BOOST_SERIALIZATION_NVP( d_next_history );
  ar & BOOST_SERIALIZATION_NVP( d_rendezvous_number );
  ar & BOOST_SERIALIZATION_NVP( d_rendezvous_batch_size );
  ar & BOOST_SERIALIZATION_NVP( d_batch_size );
}

// Load the data from an archive
template<typename Archive>
void ParticleSimulationManager::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_simulation_name );
  ar & BOOST_SERIALIZATION_NVP( d_model );
  ar & BOOST_SERIALIZATION_NVP( d_source );
  ar & BOOST_SERIALIZATION_NVP( d_event_handler );
  ar & BOOST_SERIALIZATION_NVP( d_weight_windows );
  ar & BOOST_SERIALIZATION_NVP( d_collision_forcer );
  ar & BOOST_SERIALIZATION_NVP( d_properties );
  ar & BOOST_SERIALIZATION_NVP( d_next_history );
  ar & BOOST_SERIALIZATION_NVP( d_rendezvous_number );
  ar & BOOST_SERIALIZATION_NVP( d_rendezvous_batch_size );
  ar & BOOST_SERIALIZATION_NVP( d_batch_size );

  d_collision_kernel.reset( new CollisionKernel( d_model, *d_properties ) );
  d_transport_kernel.reset( new TransportKernel( d_model ) );
  d_end_simulation = false;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//
