//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BatchedDistributedStandardParticleSimulationManager.hpp
//! \author Alex Robinson
//! \brief  Batched distributed standard particle simulation manager class decl
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_HPP
#define MONTE_CARLO_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSimulationManager.hpp"
#include "Utility_Communicator.hpp"

namespace MonteCarlo{

//! The batched distributed standard particle simulation manager
template<ParticleModeType mode>
class BatchedDistributedStandardParticleSimulationManager : public StandardParticleSimulationManager<mode>
{

public:

  //! Constructor
  BatchedDistributedStandardParticleSimulationManager(
                 const std::string& simulation_name,
                 const std::string& archive_type,
                 const std::shared_ptr<const FilledGeometryModel>& model,
                 const std::shared_ptr<ParticleSource>& source,
                 const std::shared_ptr<EventHandler>& event_handler,
                 const std::shared_ptr<PopulationControl> population_controller,
                 const std::shared_ptr<const CollisionForcer> collision_forcer,
                 const std::shared_ptr<const SimulationProperties>& properties,
                 const uint64_t next_history,
                 const uint64_t rendezvous_number,
                 const bool use_single_rendezvous_file,
                 const std::shared_ptr<const Utility::Communicator>& comm );

  //! Destructor
  ~BatchedDistributedStandardParticleSimulationManager()
  { /* ... */ }

  //! Run the simulation set up by the user
  void runSimulation() final override;

  //! Run the simulation set up by the user with the ability to interrupt
  void runInterruptibleSimulation() final override;
  
  //! Print the simulation data to the desired stream
  void printSimulationSummary( std::ostream& os ) const final override;

  //! Log the simulation data
  void logSimulationSummary() const final override;

protected:

  //! Rendezvous (cache state)
  void rendezvous() final override;

  //! The signal handler
  void signalHandler( int signal ) final override;

private:

  // Coorindate workers
  void coordinateWorkers();

  // Tell workers to stop working
  void stopWorkersAndRecordWork( const bool simulation_complete,
                                 const bool rendezvous_required,
                                 const uint64_t batch_number );

  // Check for idle worker
  bool isIdleWorkerPresent( Utility::Communicator::Status& idle_worker_info );

  // Assign work to idle worker
  void assignWorkToIdleWorker( const Utility::Communicator::Status& idle_worker_info,
                               const std::pair<uint64_t,uint64_t>& task );

  // Complete assigned work
  void work();

  // The communicator
  std::shared_ptr<const Utility::Communicator> d_comm;

  // The number of batches per rendezvous
  uint64_t d_batches_per_rendezvous;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_BatchedDistributedStandardParticleSimulationManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BatchedDistributedStandardParticleSimulationManager.hpp
//---------------------------------------------------------------------------//
