//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager.hpp
//! \author Alex Robinson
//! \brief  Particle simulation manager class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_HPP
#define MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/filesystem/path.hpp>

// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_WeightWindow.hpp"
#include "MonteCarlo_CollisionForcer.hpp"
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_CollisionKernel.hpp"
#include "MonteCarlo_TransportKernel.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_Communicator.hpp"

extern "C" void __custom_signal_handler__( int signal );

namespace MonteCarlo{

//! The particle simulation manager base class
class ParticleSimulationManager : public std::enable_shared_from_this<ParticleSimulationManager>
{

public:

  //! Destructor
  virtual ~ParticleSimulationManager()
  { /* ... */ }

  //! Return the next history that will be completed
  uint64_t getNextHistory() const;

  //! Return the number of rendezvous
  uint64_t getNumberOfRendezvous() const;

  //! Return the rendezvous batch size
  uint64_t getRendezvousBatchSize() const;

  //! Return the batch size
  uint64_t getBatchSize() const;

  //! Return the model
  const FilledGeometryModel& getModel() const;

  //! Return the source
  const ParticleSource& getSource() const;

  //! Return the event handler
  const EventHandler& getEventHandler() const;

  //! Return the event handler
  EventHandler& getEventHandler();

  //! Return the simulation properties
  const SimulationProperties& getSimulationProperties() const;

  //! Set the simulation name
  void setSimulationName( const std::string& new_name );

  //! Get the simulation name
  const std::string& getSimulationName() const;

  //! Set the simulation archive type
  void setSimulationArchiveType( const std::string& archive_type );

  //! Get the simulation archive type
  const std::string& getSimulationArchiveType() const;

  //! Set the simulation name and archive type
  void setSimulationNameAndArchiveType( const std::string& new_name,
                                        const std::string& archive_type );

  //! Run the simulation set up by the user
  virtual void runSimulation();

  //! Run the simulation set up by the user with the ability to interrupt
  virtual void runInterruptibleSimulation();

  //! Print the simulation data to the desired stream
  virtual void printSimulationSummary( std::ostream& os ) const;

  //! Log the simulation data
  virtual void logSimulationSummary() const;

protected:

  //! Constructor
  ParticleSimulationManager(
                 const std::string& simulation_name,
                 const std::string& archive_type,
                 const std::shared_ptr<const FilledGeometryModel>& model,
                 const std::shared_ptr<ParticleSource>& source,
                 const std::shared_ptr<EventHandler>& event_handler,
                 const std::shared_ptr<const WeightWindow> weight_windows,
                 const std::shared_ptr<const CollisionForcer> collision_forcer,
                 const std::shared_ptr<const SimulationProperties>& properties,
                 const uint64_t next_history,
                 const uint64_t rendezvous_number );

  //! Set the batch size
  void setBatchSize( const uint64_t batch_size );

  //! Increment the next history
  void incrementNextHistory( const uint64_t increment_size );

  //! Check if the simulation has been ended by the user
  bool hasEndSimulationRequestBeenMade() const;

  //! Run the simulation batch
  void runSimulationBatch( const uint64_t batch_start_history,
                           const uint64_t batch_end_history );

  //! Simulate an unresolved particle
  virtual void simulateUnresolvedParticle(
                                        ParticleState& unresolved_particle,
                                        ParticleBank& bank,
                                        const bool source_particle ) = 0;

  //! Simulate a resolved particle
  template<typename State>
  void simulateParticle( ParticleState& unresolved_particle,
                         ParticleBank& bank,
                         const bool source_particle );

  //! Enable thread support
  void enableThreadSupport();

  //! Reset data
  void resetData();

  //! Reduce distributed data
  void reduceData( const Utility::Communicator& comm,
                   const int root_process );

  //! Register simulation started event
  void registerSimulationStartedEvent();

  //! Register simulation stopped event
  void registerSimulationStoppedEvent();

  //! Check if the simulation is complete
  bool isSimulationComplete();

  //! Rendezvous (cache state)
  virtual void rendezvous();

  //! The signal handler
  virtual void signalHandler( int signal );

  //! Check if a signal type is handled by the manager
  static bool isSignalTypeHandled( const int signal );

  //! Exit if required based on signal count
  void exitIfRequired( const int signal_counter, const int signal ) const;

private:

  // Simulate an unresolved particle track
  template<typename State>
  void simulateUnresolvedParticleTrack(
                                       ParticleState& unresolved_particle,
                                       ParticleBank& bank,
                                       const double optical_path,
                                       const bool starting_from_source );

  // Simulate a resolved particle track
  template<typename State>
  void simulateParticleTrack( State& particle,
                              ParticleBank& bank,
                              const double optical_path,
                              const bool starting_from_source );

  // Advance a particle to the cell boundary
  template<typename State>
  void advanceParticleToCellBoundary(
                              State& particle,
                              const Geometry::Model::EntityId surface_to_cross,
                              const double distance_to_surface );

  // Advance a particle to a collision site
  template<typename State>
  void advanceParticleToCollisionSite(
                                  State& particle,
                                  const double op_to_collision_site,
                                  const double cell_total_macro_cross_section,
                                  const double track_start_position[3] );

  // Conduct a basic rendezvous
  void basicRendezvous() const;

  // Declare the custom signal handler as a friend
  friend void ::__custom_signal_handler__( int );

  // The simulation name
  std::string d_simulation_name;

  // The archive type
  std::string d_archive_type;

  // The filled geometry model
  std::shared_ptr<const FilledGeometryModel> d_model;

  // The collision kernel
  std::unique_ptr<const CollisionKernel> d_collision_kernel;

  // The transport kernel
  std::unique_ptr<const TransportKernel> d_transport_kernel;

  // The particle source
  std::shared_ptr<ParticleSource> d_source;

  // The event handler
  std::shared_ptr<EventHandler> d_event_handler;

  // The weight windows
  std::shared_ptr<const WeightWindow> d_weight_windows;

  // The collision forcer
  std::shared_ptr<const CollisionForcer> d_collision_forcer;

  // The simulation properties
  std::shared_ptr<const SimulationProperties> d_properties;

  // The next history to run
  uint64_t d_next_history;

  // The rendezvous number (counter)
  uint64_t d_rendezvous_number;

  // The rendezvous batch size
  uint64_t d_rendezvous_batch_size;

  // The batch size
  uint64_t d_batch_size;

  // Flag for ending simulation early
  bool d_end_simulation;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleSimulationManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager.hpp
//---------------------------------------------------------------------------//
