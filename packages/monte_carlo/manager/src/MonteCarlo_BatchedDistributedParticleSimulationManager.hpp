//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BatchedDistributedParticleSimulationManager.hpp
//! \author Alex Robinson
//! \brief  The batched distributed particle simulation manager class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_HPP
#define FACEMC_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_HPP

// FRENSIE Includes
#include "FRENSIE_mpi_config.hpp"

// Trilinos Includes
#ifdef HAVE_FRENSIE_MPI
#include <Teuchos_CommHelpers.hpp>
#endif 

namespace MonteCarlo{

//! The batched distributed memory particle simulation manager class
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
class BatchedDistributedParticleSimulationManager : public ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>
{
  
public:

  //! Constructor
  BatchedDistributedParticleSimulationManager(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process,
	    const unsigned number_of_histories,
	    const unsigned start_history = 0u,
	    const unsigned previously_completed_histories = 0u,
	    const double previous_run_time = 0.0 );

  //! Destructor
  ~BatchedDistributedParticleSimulationManager()
  { /* ... */ }

  //! Run the simulation set up by the user
  void runSimulation();

  //! Print the data in all estimators to the desired stream
  void printSimulationSummary( std::ostream &os ) const;

  //! Export the simulation data (to an hdf5 file)
  void exportSimulationData( const std::string& data_file_name ) const;

  // Signal handler
  void signalHandler(int signal);

private:
  
  // The mpi communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > d_comm;

  // The root process
  int d_root_process;
};

} // end MonteCarlo

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_BatchedDistributedParticleSimulationManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BatchedDistributedParticleSimulationManager.hpp
//---------------------------------------------------------------------------//


