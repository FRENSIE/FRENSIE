//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager.hpp
//! \author Alex Robinson
//! \brief  The particle simulation manager class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FRENSIE_PARTICLE_SIMULATION_MANAGER_HPP
#define FRENSIE_PARTICLE_SIMULATION_MANAGER_HPP

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_SourceModuleInterface.hpp"
#include "MonteCarlo_EventModuleInterface.hpp"
#include "MonteCarlo_CollisionModuleInterface.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_SimulationManager.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

namespace Details{

//! The mode initialization helper class
template<typename BeginParticleIterator, typename EndParticleIterator>
struct ModeInitializationHelper;
  
} // end Details namespace

//! The generic particle simulation manager class
template<ParticleModeType mode>
class ParticleSimulationManager : public SimulationManager
{

public:

  //! Constructor
  ParticleSimulationManager(
                const std::shared_ptr<const SimulationProperties> properties,
                const std::shared_ptr<const Geometry::Model>& model,
		const unsigned long long start_history = 0ull,
		const unsigned long long previously_completed_histories = 0ull,
		const double previous_run_time = 0.0 );

  //! Destructor
  virtual ~ParticleSimulationManager()
  { /* ... */ }

  //! Run the simulation set up by the user
  virtual void runSimulation();

  //! Print the data in all estimators to the desired stream
  virtual void printSimulationSummary( std::ostream& os ) const;

  //! Export the simulation data (to an hdf5 file)
  virtual void exportSimulationData( const std::string& data_file_name,
                                     std::ostream& os ) const;

  // Signal handler
  virtual void signalHandler(int signal);

protected:

  //! Run the simulation batch
  void runSimulationBatch( const unsigned long long start_history,
			   const unsigned long long end_history );

  //! Return the number of histories
  unsigned long long getNumberOfHistories() const;

  //! Return the number of histories completed
  unsigned long long getNumberOfHistoriesCompleted() const;

  //! Increment the number of histories completed
  void incrementHistoriesCompleted( const unsigned long long histories = 1ull );
  //! Set the number of histories completed
  void setHistoriesCompleted( const unsigned long long histories );

  //! Set the start time
  void setStartTime( const double start_time );

  //! Set the end time
  void setEndTime( const double end_time );

  //! Print simulation state info in collision handler
  void printSimulationStateInfo();

private:

  // Initialize the simulate particle functions
  void initializeSimulateParticleFunctions();

  // Add simulate particle function for particle type
  template<typename State>
  void addSimulateParticleFunction();

  // Simulate an unresolved particle
  void simulateUnresolvedParticle( ParticleState& unresolved_particle,
                                   ParticleBank& bank,
                                   Geometry::Navigator& navigator ) const;

  // Simulate an individual particle
  template<typename State>
  void simulateParticle( ParticleState& unresolved_particle,
                         ParticleBank& bank,
                         Geometry::Navigator& navigator ) const;

  // Simulate an individual particle track of the desired optical path length
  template<typename State>
  void simulateParticleTrack( State& particle,
                              Geometry::Navigator& navigator,
                              const double optical_path ) const;

  // Advance a particle to the cell boundary
  template<typename State>
  void advanceParticleToCellBoundary( State& particle,
                                      Geometry::Navigator& navigator,
                                      const double distance_to_surface,
                                      const double subtrack_start_time ) const;

  // Advance a particle to a collision site
  template<typename State>
  void advanceParticleToCollisionSite(
                                  State& particle,
                                  Geometry::Navigator& navigator,
                                  const double op_to_collision_site,
                                  const double cell_total_macro_cross_section,
                                  const double subtrack_start_time,
                                  const double track_start_time,
                                  const double track_start_position[3] ) const;
                                      
  // Add the mode initialization helper as a friend class
  template<typename T1, typename T2>
  friend class Details::ModeInitializationHelper;

  // The simulation properties
  std::shared_ptr<const SimulationProperties> d_properties;

  // The geometry model
  std::shared_ptr<const Geometry::Model> d_model;

  // Starting history
  unsigned long long d_start_history;

  // Number of particle histories to simulate
  unsigned long long d_history_number_wall;

  // Number of histories completed
  unsigned long long d_histories_completed;

  // Flag for ending simulation early
  bool d_end_simulation;

  // The previous run time
  double d_previous_run_time;

  // The simulation start time
  double d_start_time;

  // The simulation end time
  double d_end_time;

  // The simulation functions
  typedef std::function<void(ParticleState&, ParticleBank&, Geometry::Navigator&)>
  SimulateParticleFunction;
  
  typedef std::map<ParticleType,SimulatParticleFunction>
  SimulateParticleFunctionMap;
  
  SimulateParticleFunctionMap d_simulate_particle_function_map;
};

//! Macro for catching a lost particle and breaking a loop
#define CATCH_LOST_PARTICLE_AND_BREAK( particle )			\
  catch( std::runtime_error& exception )				\
  {									\
    particle.setAsLost();						\
                                                                        \
    FRENSIE_LOG_NESTED_ERROR( exception.what() );                       \
                                                                        \
    FRENSIE_LOG_TAGGED_WARNING(                                         \
                   "Lost Particle",                                     \
                   "history " << particle.getHistoryNumber() <<         \
                   ", generation " << particle.getGenerationNumber() ); \
                                                                        \
    FRENSIE_LOG_TAGGED_NOTIFICATION( "Lost Particle State Dump",        \
                                     particle );                        \
                                                                        \
    break;								\
  }

//! Macro for catching a lost source particle
#define CATCH_LOST_SOURCE_PARTICLE_AND_CONTINUE( bank )			\
  catch( std::runtime_error& exception )				\
  {									\
    bank.top().setAsLost();                                             \
                                                                        \
    FRENSIE_LOG_NESTED_ERROR( exception.what() );                       \
                                                                        \
    FRENSIE_LOG_TAGGED_WARNING(                                         \
                       "Lost Source Particle",                          \
                       "history " << particle.getHistoryNumber() );     \
                                                                        \
    FRENSIE_LOG_TAGGED_NOTIFICATION( "Lost Source Particle State Dump", \
                                     particle );                        \
                                                                        \
    bank.pop();								\
                                                                        \
    continue;								\
  }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleSimulationManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FRENSIE_PARTICLE_SIMULATION_MANAGER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager.hpp
//---------------------------------------------------------------------------//
