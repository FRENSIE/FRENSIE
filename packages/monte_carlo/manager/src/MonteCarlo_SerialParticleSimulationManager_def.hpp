//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager_def.hpp
//! \author Alex Robinson
//! \brief  The particle simulation manager class definition.
//!
//---------------------------------------------------------------------------//

#ifndef FRENSIE_PARTICLE_SIMULATION_MANAGER_DEF_HPP
#define FRENSIE_PARTICLE_SIMULATION_MANAGER_DEF_HPP

// std includes
#include <iostream>

// Boost Includes
#include <boost/mpl/find.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/begin_end.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

namespace Details{

// The mode initialization helper class
template<typename BeginParticleIterator, typename EndParticleIterator>
struct ModeInitializationHelper
{
  //! Initialize simulate particle functors map
  template<typename Manager>
  static inline void initializeSimulateParticleFunctions(
                                                       const Manager& manager )
  {
    manager.addSimulateParticleFunction<typename boost::mpl::deref<BeginParticleIterator>::type>();

    ModeInitializationHelper<typename boost::mpl::next<BeginParticleIterator>::type,
                             EndParticleIterator>::initializeSimulateParticleFunctions( manager );
  }
};

// End initialization
template<typename EndParticleIterator>
struct ModeInitializationHelper
{
  //! Initialize simulate particle functors map
  template<typename Manager>
  static inline void initializeSimulateParticleFunctions(
                                                       const Manager& manager )
  { /* ... */ }
};
  
} // end Details namespace
  
// Constructor for multiple threads
/*! \details If OpenMP is not being used, the number of threads requested will
 * be ignored.
 */
template<ParticleModeType mode>
ParticleSimulationManager<mode>::ParticleSimulationManager(
                  const std::shared_ptr<const SimulationProperties> properties,
                  const std::shared_ptr<const Geometry::Model>& model,
                  const unsigned long long start_history,
                  const unsigned long long previously_completed_histories,
                  const double previous_run_time )
  : d_properties( properties ),
    d_model( model ),
    d_history_number_wall( start_history+properties->getNumberOfHistories() ),
    d_histories_completed( previously_completed_histories ),
    d_end_simulation( false ),
    d_previous_run_time( previous_run_time ),
    d_start_time( 0.0 ),
    d_end_time( 0.0 )
{
  // The properties must be valid
  testPrecondition( properties.get() );
  // The model must be valid
  testPrecondition( model.get() );
  // At least one history must be simulated
  testPrecondition( properties->getNumberOfHistories() > 0 );
  // Make sure that the modes are consistent
  testPrecondition( mode == properties->getParticleMode() );

  // Initialize the simulate particle functions
  this->initializeSimulateParticleFunctions();
}

// Initialize the simulate particle functions
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::initializeSimulateParticleFunctions()
{
  typedef typename boost::mpl::begin<typename ParticleModeTypeTraits<mode>::ActiveParticles>::type
    BeginParticleIterator;
  typedef typename boost::mpl::begin<typename ParticleModeTypeTraits<mode>::ActiveParticles>::type
    EndParticleIterator;
  
  Details::ModeInitializationHelper<BeginParticleIterator,EndParticleIterator>::initializeSimulateParticleFunctions( *this );
}

// Run the simulation set up by the user
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::runSimulation()
{
  std::cout << "Starting simulation ... ";
  std::cout.flush();

  // Set up the random number generator for the number of threads requested
  Utility::RandomNumberGenerator::createStreams();

  // Enable source thread support
  SMI::enableThreadSupport(
                 Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  // Enable estimator thread support
  EMI::enableThreadSupport(
                 Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  // Set the start time
  EMI::updateObserversFromParticleSimulationStartedEvent();
  //this->setStartTime( Utility::OpenMPProperties::getTime() );

  // Simulate the batch
  this->runSimulationBatch( d_start_history, d_history_number_wall );

  // Set the end time
  EMI::updateObserversFromParticleSImiulationStoppedEvent();
  this->setEndTime( Utility::OpenMPProperties::getTime() );

  std::cout << "done." << std::endl;
}

// Run the simulation batch
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::runSimulationBatch(
                                  const unsigned long long batch_start_history,
                                  const unsigned long long batch_end_history )
{
  // Make sure the history range is valid
  testPrecondition( batch_start_history <= batch_end_history );
  testPrecondition( batch_start_history >= d_start_history );
  testPrecondition( batch_end_history <= d_history_number_wall );

  #pragma omp parallel num_threads( Utility::OpenMPProperties::getRequestedNumberOfThreads() )
  {
    // Create a bank for each thread
    ParticleBank source_bank, bank;

    #pragma omp for
    for( unsigned long long history = batch_start_history; history < batch_end_history; ++history )
    {
      double history_start_time =
        Utility::OpenMPProperties::getTime(); - d_start_time;

      // Do useful work unless the user requests an end to the simulation
      #pragma omp flush( d_end_simulation )
      if( !d_end_simulation )
      {
        // Initialize the random number generator for this history
        Utility::RandomNumberGenerator::initialize( history );

	// Sample a particle state from the source
        try{
          SMI::sampleParticleState( source_bank, history );
        }
        CATCH_LOST_SOURCE_PARTICLE_AND_CONTINUE( source_bank );

        // Simulate the particles generated by the source first
        while( source_bank.size() > 0 )
        {
          this->simulateUnresolvedParticle( source_bank.top(), bank, true );

          source_bank.pop();
        }

	// This history only ends when the particle bank is empty
	while( bank.size() > 0 )
	{            
	  this->simulateUnresolvedParticle( bank.top(), bank, false );

          bank.pop();
	}

	// Commit all observer history contributions
	EMI::commitObserverHistoryContributions();

	// Increment the number of histories completed
        #pragma omp atomic
        ++d_histories_completed;
      }
    }
  }
}

// Simulate an unresolved particle
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::simulateUnresolvedParticle(
                                         ParticleState& unresolved_particle,
                                         ParticleBank& bank,
                                         const bool source_particle ) const
{
  SimulateParticleFunctionMap::const_iterator simulation_function_it =
    d_simulate_particle_function_map.find( unresolved_particle.getParticleType() );

  // Only simulate the particle if there is a simulation function associated
  // with the type
  if( simulation_function_it != d_simulate_particle_function_map.end() )
    simulation_function_it->second( unresolved_particle, bank, source_particle );
  else
    unresolved_particle.setAsGone();
}

// Set the number of particle histories to simulate
template<ParticleModeType mode>
template<typename State>
void ParticleSimulationManager<mode>::simulateParticle(
                                         ParticleState& unresolved_particle,
                                         ParticleBank& bank,
                                         const bool source_particle ) const
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
      particle.setAsGone();
    else
    {
      this->simulateParticleTrack( particle,
                                   bank,
                                   CMI::sampleOpticalPathLength(),
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
  
    this->simulateParticleTrack( particle,
                                 bank,
                                 CMI::sampleOpticalPathLength(),
                                 false );
  }
}

// Simulate an individual particle track of the desired optical path length
template<ParticleModeType mode> 
template<typename State>
void ParticleSimulateManager<mode>::simulateUnresolvedParticleTrack(
                                        ParticleState& unresolved_particle,
                                        ParticleBank& bank,
                                        const double optical_path,
                                        const bool starting_from_source ) const
{
  this->simulateParticleTrack( dynamic_cast<State&>( unresolved_particle ),
                               bank,
                               optical_path,
                               starting_from_source );
}

// Simulate a particle collision
template<ParticleModeType mode> 
template<typename State>
void ParticleSimulateManager<mode>::simulateUnresolvedParticleCollision(
                                            ParticleState& unresolved_particle,
                                            ParticleBank& bank ) const
{
  CMI::collideWithCellMaterial( dynamic_cast<State&>( unresolved_particle ), bank );
}

// Simulate an individual particle track of the desired optical path length
template<ParticleModeType mode> 
template<typename State>
void ParticleSimulateManager<mode>::simulateParticleTrack(
                                        State& particle,
                                        ParticleBank& bank,
                                        const double optical_path,
                                        const bool starting_from_source ) const
{
  // Particle tracking information (op = optical_path)
  double distance_to_surface_hit;
  double op_to_surface_hit;
  double remaining_track_op = optical_path;
  double track_start_time = particle.getTime();
  double track_start_point[3];
  track_start_point[0] = particle.getXPosition();
  track_start_point[1] = particle.getYPosition();
  track_start_point[2] = particle.getZPosition();

  bool subtrack_starting_from_source_point = starting_from_source;
  bool subtrack_starting_from_cell_boundary = false;

  const SimulateUnresolvedParticleTrackFunction simulate_unresolved_particle_track =
    d_simulate_unresolved_particle_track_function_map.find( State::type );

  // Surface information
  Geometry::ModuleTraits::EntityId surface_hit;

  // Cell information
  double cell_total_macro_cross_section;

  // If the particle started from a source point, update the relevant
  // particle entering cell event observers
  if( starting_from_source )
  {
    EMI::updateObserversFromParticleEnteringCellEvent( particle,
                                                       particle.getCell() );
  }

  // Ray trace until the necessary number of optical paths have be traveled
  while( true )
  {
    // Fire a ray at the cell currently containing the particle
    try
    {
      distance_to_surface_hit =
        particle.navigator().fireInternalRay( surface_hit );
    }
    CATCH_LOST_PARTICLE_AND_BREAK( particle );

    // Get the total cross section for the cell
    if( !CMI::isCellVoid<State>( particle.getCell() ) )
    {
      cell_total_macro_cross_section =
        CMI::getMacroscopicTotalForwardCrossSectionQuick( particle );
    }
    else
      cell_total_macro_cross_section = 0.0;

    // Convert the distance to the surface to optical path
    op_to_surface_hit = distance_to_surface_hit*cell_total_macro_cross_section;

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
                                             particle.getTime(),
                                             track_start_point );
      }
      CATCH_LOST_PARTICLE_AND_BREAK( particle );

      // The particle has exited the geometry
      if( d_model->isTerminationCell( particle.getCell() ) )
      {
        // Update the global observers: particle subtrack ending global event
        EMI::updateObserversFromParticleSubtrackEndingGlobalEvent(
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
                                            particle.getTime(),
                                            track_start_time,
                                            track_start_point );

      // Update the particle state before the collision (e.g. roulette/split
      // using weight window mesh)
      ParticleBank local_bank;
      d_weight_windows->updateParticleState( particle, local_bank );
      
      // Undergo a collision with the material in the cell
      if( particle )
        CMI::collideWithCellMaterial( particle, bank );

      while( !local_bank.isEmpty() )
      {
        ParticleBank next_gen_local_bank;
        CMI::collideWithCellMaterial( local_bank.top(), next_gen_local_bank );

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
    EMI::updateObserversFromParticleGoneGlobalEvent( particle );
}

// Advance a particle to the cell boundary
template<ParticleModeType mode> 
template<typename State>
void ParticleSimulateManager<mode>::advanceParticleToCellBoundary(
                                 State& particle,
                                 const double distance_to_surface,
                                 const double subtrack_start_time,
                                 const bool starting_from_source,
                                 const bool starting_from_cell_boundary ) const
{
  // Advance the particle to the cell boundary
  // Note: this will change the particle's cell
  Geometry::ModuleTraits::EntityId start_cell = particle.getCell();
  double surface_normal[3];
  bool reflected =
    particle.navigator().advanceInternalRayToCellBoundary( surface_normal );

  // Update the observers: particle subtrack ending in cell event
  EMI::updateObserversFromParticleSubtrackEndingInCellEvent(
                                                         particle,
                                                         start_cell,
                                                         distance_to_surface,
                                                         subtrack_start_time );

  // Update the observers: particle leaving cell event
  EMI::updateObserversFromParticleLeavingCellEvent( particle, start_cell );
    
  // Update the observers: particle crossing surface event
  EMI::updateObserversFromParticleCrossingSurfaceEvent( particle,
                                                        surface_hit,
                                                        surface_normal );
  if( reflected )
  {
    EMI::updateObserversFromParticleCrossingSurfaceEvent( particle,
                                                          surface_hit,
                                                          surface_normal );
  }

  // Update the observers: particle entering cell event
  EMI::updateObserversFromParticleEnteringCellEvent( particle, particle.getCell() );
}

// Advance a particle to a collision site
template<ParticleModeType mode> 
template<typename State>
void ParticleSimulateManager<mode>::advanceParticleToCollisionSite(
                                   State& particle,
                                   const double op_to_collision_site,
                                   const double cell_total_macro_cross_section,
                                   const double subtrack_start_time,
                                   const double track_start_time,
                                   const double track_start_position[3] ) const
{
  // Calculate the distance to the collision site
  double distance_to_collision =
    remaining_subtrack_op/cell_total_macro_cross_section;

  // Advance the particle
  particle.navigator().advanceBySubstep( distance_to_collision );

  // Update the observers: particle subtrack ending in cell event
  EMI::updateObserversFromParticleSubtrackEndingInCellEvent(
                                                       particle,
                                                       particle.getCell(),
                                                       distance_to_collision,
                                                       subtrack_start_time );

  // Update the observers: particle colliding in cell event
  EMI::updateObserversFromParticleCollidingInCellEvent(
                                          particle,
                                          1.0/cell_total_macro_cross_section );
        
  // Update the global observers: particle subtrack ending global event
  EMI::updateObserversFromParticleSubtrackEndingGlobalEvent(
                                                      particle,
                                                      ray_start_point,
                                                      particle.getPosition() );
}

// Add simulate particle function for particle type
template<ParticleModeType mode> 
template<typename State>
void ParticleSimulateManager<mode>::addSimulateParticleFunction()
{
  // Make sure that the state is compatible with the mode
  testPrecondition( MonteCarlo::isParticleModeCompatible<mode>( State::type ) );

  d_simulate_particle_function_map[State::type] =
    std::bind<void>( ParticleSimulationManager<mode>::simulateParticle<State>,
                     std::cref( *this )
                     std::placeholders::_1,
                     std::placeholders::_2,
                     std::placeholders::_3 );

  d_simulate_unresolved_particle_track_function_map[State::type] = 
    boost::bind<void>( &ParticleSimulationManager<mode>::simulateUnresolvedParticleTrack<State>,
                       std::cref(*this),
                       std::placeholders::_1,
                       std::placeholders::_2,
                       std::placeholders::_3,
                       false );

  d_simulate_unresolved_particle_collision_function_map[State::type] =
    boost::bind<void>( &ParticleSimulateManager<mode>::simulateUnresolvedParticleCollision,
                       std::cref(*this),
                       std::placeholders::_1,
                       std::placeholders::_2 );
}

// Return the number of histories
template<ParticleModeType mode>
unsigned long long
ParticleSimulationManager<mode>::getNumberOfHistories() const
{
  return d_history_number_wall - d_start_history;
}

// Return the number of histories completed
template<ParticleModeType mode>
unsigned long long
ParticleSimulationManager<mode>::getNumberOfHistoriesCompleted() const
{
  return d_histories_completed;
}

// Increment the number of histories completed
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::incrementHistoriesCompleted(
					   const unsigned long long histories )
{
  d_histories_completed += histories;
}

// Set the number of histories completed
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::setHistoriesCompleted(
					   const unsigned long long histories )
{
  d_histories_completed = histories;
}

// Set the start time
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::setStartTime( const double start_time )
{
  d_start_time = start_time;
}

// Set the end time
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::setEndTime( const double end_time )
{
  // Make sure the end time is valid
  testPrecondition( end_time >= d_start_time );

  d_end_time = end_time;
}

// Print the data in all estimators to the desired stream
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::printSimulationSummary(
						       std::ostream &os ) const
{
  os << "Number of histories completed: " << d_histories_completed <<std::endl;
  os << "Simulation Time (s): " << d_end_time - d_start_time << std::endl;
  if( d_previous_run_time > 0.0 )
    os << "Previous Simulation Time (s): " << d_previous_run_time << std::endl;
  os << std::endl;

  SMI::printSourceSummary( os );

  EMI::printObserverSummaries( os,
                               d_histories_completed,
                               d_start_time,
                               d_end_time+d_previous_run_time );
}

// Print the data in all estimators to a parameter list
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::exportSimulationData(
                                             const std::string& data_file_name,
                                             std::ostream& os ) const
{
  os << "Exporting simulation data ... ";
  os.flush();

  // Initialize the HDF5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );

  hdf5_file->openHDF5FileAndOverwrite( data_file_name );

  EMI::exportObserverData( hdf5_file,
                           d_start_history+d_histories_completed,
                           d_histories_completed,
                           d_start_time,
                           d_end_time+d_previous_run_time,
                           true );

  SMI::exportSourceData( hdf5_file );

  os << "done." << std::endl;
}

// Signal handler
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::signalHandler(int signal)
{
  // Ask the user what to do
  std::cerr << " Status (s), End (e), Kill (k)" << std::endl;
  std::string option;
  std::cin >> option;

  if( option.compare( "s" ) == 0 )
  {
    printSimulationStateInfo();
  }
  else if( option.compare( "e" ) == 0 )
  {
    d_end_simulation = true;
  }
  else if( option.compare( "k" ) == 0 )
  {
    exit(0);
  }
}

// Print simulation state info in collision handler
template<ParticleModeType mode>
void ParticleSimulationManager<mode>::printSimulationStateInfo()
{
  double time = Utility::OpenMPProperties::getTime();

  #pragma omp critical( ostream_update )
  {
    #pragma omp flush( d_histories_completed )
    std::cerr << " History: " << d_histories_completed
              << " Run Time: " << time - d_start_time
              << std::endl;
  }
}

} // end MonteCarlo namespace

#endif // end FRENSIE_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//
