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
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_WeightWindow.hpp"
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

//! The particle simulation manager base class
class ParticleSimulationManager : private ArchivableObject<ParticleSimulationManager>
{

public:

  //! Constructor
  ParticleSimulationManager(
               const std::shared_ptr<const FilledGeometryModel>& model,
               const std::shared_ptr<ParticleSource>& source,
               const std::shared_ptr<EventHandler>& event_handler,
               const std::shared_ptr<const SimulationProperties>& properties,
               const std::string& simulation_name = "simulation.xml" );

  //! Restart constructor
  ParticleSimulationManager( const boost::filesystem::path& archived_manager_name );

  //! Destructor
  virtual ~ParticleSimulationManager()
  { /* ... */ }

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

  //! Return the next history that will be completed
  uint64_t getNextHistory() const;

  //! Set the weight windows
  void setWeightWindows(
                   const std::shared_ptr<const WeightWindow>& weight_windows );

  //! Set the collision forcer
  void setCollisionForcer(
              const std::shared_ptr<const CollisionForcer>& collision_forcer );

  //! Run the simulation set up by the user
  virtual void runSimulation();

  //! Rename the simulation
  void renameSimulation( const std::string& name );

  //! Print the simulation data to the desired stream
  virtual void printSimulationSummary( std::ostream& os ) const;

  //! Log the simulation data
  virtual void logSimulationSummary() const;

  //! The signal handler
  virtual void signalHandler( int signal );

protected:

  //! Set the batch size
  void setBatchSize( const uint64_t batch_size );

  //! Run the simulation batch
  void runSimulationBatch( const uint64_t batch_start_history,
                           const uint64_t batch_end_history );

  //! Simulate an unresolved particle
  virtual void simulateUnresolvedParticle(
                                        ParticleState& unresolved_particle,
                                        ParticleBank& bank,
                                        const bool source_particle ) const = 0;

  //! Simulate a resolved particle
  template<typename State>
  void simulateParticle( ParticleState& unresolved_particle,
                         ParticleBank& bank,
                         const bool source_particle ) const;

  //! Rendezvous (cache state)
  virtual void rendezvous();

private:

  // Simulate an unresolved particle track
  template<typename State>
  void simulateUnresolvedParticleTrack(
                                       ParticleState& unresolved_particle,
                                       ParticleBank& bank,
                                       const double optical_path,
                                       const bool starting_from_source ) const;

  // Simulate a resolved particle track
  template<typename State>
  void simulateParticleTrack( State& particle,
                              ParticleBank& bank,
                              const double optical_path,
                              const bool starting_from_source ) const;

  // Simulate an unresolved particle collision
  template<typename State>
  void simulateUnresolvedParticleCollision( ParticleState& unresolved_particle,
                                            ParticleBank& bank ) const;

  // Simulate a resolved particle collision
  template<typename State>
  void simulateParticleCollision( State& particle,
                                  ParticleBank& bank );

  // Advance a particle to the cell boundary
  template<typename State>
  void advanceParticleToCellBoundary( State& particle,
                                      ParticleBank& bank,
                                      const double distance_to_surface,
                                      const double subtrack_start_time ) const;

  // Advance a particle to a collision site
  template<typename State>
  void advanceParticleToCollisionSite(
                                  State& particle,
                                  const double op_to_collision_site,
                                  const double cell_total_macro_cross_section,
                                  const double subtrack_start_time,
                                  const double track_start_time,
                                  const double track_start_position[3] ) const;

  // The name that will be used when archiving the object
  const char* getArchiveName() const final override;

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The name used in archive name-value pairs
  static const std::string s_archive_name;

  // The simulation name
  std::string d_simulation_name;

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
  std::shared_ptr<const WeightWindows> d_weight_windows;

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

BOOST_SERIALIZATION_CLASS_VERSION( ParticleSimulationManager, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleSimulationManager, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ParticleSimulationManager );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleSimulationManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_SIMULATION_MANAGER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager.hpp
//---------------------------------------------------------------------------//
