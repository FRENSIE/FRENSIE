//---------------------------------------------------------------------------//
//!
//! \file   ParticleSimulationManager.hpp
//! \author Alex Robinson
//! \brief  The particle simulation manager class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_SIMULATION_MANAGER_HPP
#define PARTICLE_SIMULATION_MANAGER_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

namespace FACEMC{

//! The generic particle simulation manager class
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
class ParticleSimulationManager 
{

public:

  //! Typedef for a pointer to a simulation manager
  typedef Teuchos::RCP<ParticleSimulationManager> Pointer;

private:

  // Typedef for geometry handler traits
  typedef GeometryHandlerTraits<GeometryHandler> GHT;
  // Typedef for source handler traits
  typedef SourceHandlerTraits<SourceHandler> SHT;
  // Typedef for estimator handler traits
  typedef EstimatorHandlerTraits<EstimatorHandler> EHT;
  // Typedef for collision handler traits
  typedef CollisionHandlerTraits<CollisionHandler> CHT;

public:

  //! Get an instance of the simulation manager (singleton pattern)
  static Pointer getInstance();	

  //! Destructor
  ~ParticleSimulationManager()
  { /* ... */ }

  //! Set the number of particle histories to simulate
  void setNumberOfParticleHistories( const unsigned number_of_histories );

  //! Run the simulation set up by the user
  void runSimulation();
  
  //! Print the info tables to std::cout
  void printTables() const;

  //! Print the info tables to the desired stream
  void printTables( std::ostream &os ) const;

  //! Print the data in all estimators to std::cout
  void printEstimators() const;

  //! Print the data in all estimators to the desired stream
  void printEstimators( std::ostream &os ) const;

private:

  // Default constructor
  ParticleSimulationManager();

  // Copy constructor
  ParticleSimulationManager( 
			   const ParticleSimulationManager& existing_manager );

  // Assignment operator
  ParticleSimulationManager& operator=( 
			  const ParticleSimulatioinManager& existing_manager );

  // Simulate an individual particle
  void simulateParticle( ParticleState& particle,
			 std::vector<ParticleState>& particle_bank );

  // Sole instance of manager
  static Pointer instance;

  // Number of particle histories to simulate
  unsigned d_history_number_wall;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "ParticleSimulationManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end PARTICLE_SIMULATION_MANAGER_HPP

//---------------------------------------------------------------------------//
// end ParticleSimulationManager.hpp
//---------------------------------------------------------------------------//
