//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSimulationManager.hpp
//! \author Alex Robinson
//! \brief  The particle simulation manager class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SIMULATION_MANAGER_HPP
#define FACEMC_PARTICLE_SIMULATION_MANAGER_HPP

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Facemc_SourceModuleInterface.hpp"
#include "Facemc_EstimatorModuleInterface.hpp"
#include "Facemc_CollisionModuleInterface.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_ParticleBank.hpp"
#include "Facemc_SimulationManager.hpp"
#include "Geometry_ModuleInterface.hpp"

namespace Facemc{

//! The generic particle simulation manager class
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
class ParticleSimulationManager : public SimulationManager
{

private:

  // Typedef for geometry module interface
  typedef Geometry::ModuleInterface<GeometryHandler> GMI;
  
  // Typedef for source module interface
  typedef SourceModuleInterface<SourceHandler> SMI;
  
  // Typedef for estimator module interface
  typedef EstimatorModuleInterface<EstimatorHandler> EMI;
  
  // Typedef for collision module interface
  typedef CollisionModuleInterface<CollisionHandler> CMI;

public:

  // Constructor
  ParticleSimulationManager( const unsigned number_of_histories );

  //! Destructor
  ~ParticleSimulationManager()
  { /* ... */ }

  //! Run the simulation set up by the user
  void runSimulation();

  //! Print the data in all estimators to the desired stream
  void printSimulationSummary( std::ostream &os ) const;

private:

  // Simulate an individual particle
  void simulateParticle( ParticleState& particle,
			 ParticleBank& particle_bank );
  
  // Number of particle histories to simulate
  unsigned d_history_number_wall;

  // The simulation start time
  double d_start_time;

  // The simulation end time
  double d_end_time;
};

} // end Facemc namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Facemc_ParticleSimulationManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_PARTICLE_SIMULATION_MANAGER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleSimulationManager.hpp
//---------------------------------------------------------------------------//
