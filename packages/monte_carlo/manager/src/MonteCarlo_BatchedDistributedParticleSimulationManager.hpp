//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BatchedDistributedParticleSimulationManager.hpp
//! \author Alex Robinson
//! \brief  The batched distributed particle simulation manager class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FRENSIE_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_HPP
#define FRENSIE_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManager.hpp"

namespace MonteCarlo{

//! The batched distributed memory particle simulation manager class
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
class BatchedDistributedParticleSimulationManager : public ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>
{

private:

  // Typedef for geometry module interface
  typedef typename ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::GMI GMI;

  // Typedef for estimator module interface
  typedef typename ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::EMI EMI;
  
public:

  //! Constructor
  BatchedDistributedParticleSimulationManager(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process,
	    const unsigned long long number_of_histories,
	    const unsigned number_of_batches_per_processor = 1,
	    const unsigned long long start_history = 0ull,
	    const unsigned long long previously_completed_histories = 0ull,
	    const double previous_run_time = 0.0 );

  //! Destructor
  ~BatchedDistributedParticleSimulationManager()
  { /* ... */ }

  //! Run the simulation set up by the user
  void runSimulation();

  //! Print the data in all estimators to the desired stream
  void printSimulationSummary( std::ostream &os ) const;

  //! Export the simulation data (to an hdf5 file)
  void exportSimulationData( const std::string& data_file_name,
                             std::ostream& os ) const;

  // Signal handler
  void signalHandler(int signal);

private:

  // Coordinate workers (master only)
  void coordinateWorkers();

  // Tell workers to stop working
  void stopWorkersAndRecordWork();

  // Check for idle worker
  bool isIdleWorkerPresent( 
    Teuchos::RCP<Teuchos::CommStatus<unsigned long long> >& idle_worker_info );
  
  // Assign work to idle workers
  void assignWorkToIdleWorker(
               const Teuchos::CommStatus<unsigned long long>& idle_worker_info,
	       const Teuchos::Tuple<unsigned long long,2>& task );
  
  // Complete work for the master
  void work();  

  // The mpi communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > d_comm;

  // The root process
  int d_root_process;
  
  // The ideal umber of batches per processor
  unsigned d_number_of_batches_per_processor;

  // The initial histories completed (from a previous run)
  unsigned long long d_initial_histories_completed;
};

} // end MonteCarlo

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_BatchedDistributedParticleSimulationManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FRENSIE_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BatchedDistributedParticleSimulationManager.hpp
//---------------------------------------------------------------------------//


