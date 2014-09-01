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

  //! Constructor for multiple threads
  ParticleSimulationManager( const unsigned number_of_histories );

  //! Destructor
  ~ParticleSimulationManager()
  { /* ... */ }

  //! Run the simulation set up by the user
  void runSimulation();

  //! Print the data in all estimators to the desired stream
  void printSimulationSummary( std::ostream &os ) const;

  // Signal handler
  void signalHandler(int signal);

private:

  // Simulate an individual particle
  void simulateParticle( ParticleState& particle,
			 ParticleBank& particle_bank );

  // Print simulation state info in collision handler
  void printSimulationStateInfo();
  
  // Number of particle histories to simulate
  unsigned d_history_number_wall;

  // Number of histories completed
  unsigned d_histories_completed;

  // Flag for ending simulation early
  bool d_end_simulation;

  // The simulation start time
  double d_start_time;

  // The simulation end time
  double d_end_time;
};

//! Macro for catching a lost particle and breaking a loop
#define CATCH_LOST_PARTICLE_AND_BREAK( particle )			\
  catch( std::runtime_error& exception )				\
  {									\
    std::cout << exception.what() << std::endl;				\
    std::cout << "Lost particle info: " << std::endl;			\
    std::cout << " History: " << particle.getHistoryNumber() << std::endl; \
    std::cout << " Cell: " << particle.getCell() << std::endl;		\
    std::cout << " Position: " << particle.getXPosition() << " ";	\
    std::cout << particle.getYPosition() << " ";			\
    std::cout << particle.getZPosition() << std::endl;			\
    std::cout << " Direction: " << particle.getXDirection() << " ";	\
    std::cout << particle.getYDirection() << " ";			\
    std::cout << particle.getZDirection() << std::endl;			\
    particle.setAsLost();						\
    break;								\
  }

//! Macro for catching a lost source particle
#define CATCH_LOST_SOURCE_PARTICLE_AND_CONTINUE( bank )			\
  catch( std::runtime_error& exception )				\
  {									\
    std::cout << exception.what() << std::endl;				\
    std::cout << "Lost particle info: " << std::endl;			\
    std::cout << " History: " << bank.top()->getHistoryNumber() << std::endl; \
    std::cout << " Cell: " << bank.top()->getCell() << std::endl;	\
    std::cout << " Position: " << bank.top()->getXPosition() << " ";	\
    std::cout << bank.top()->getYPosition() << " ";			\
    std::cout << bank.top()->getZPosition() << std::endl;		\
    std::cout << " Direction: " << bank.top()->getXDirection() << " ";	\
    std::cout << bank.top()->getYDirection() << " ";			\
    std::cout << bank.top()->getZDirection() << std::endl;		\
    bank.pop();								\
    continue;								\
  }

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
