//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManagerFactory.hpp
//! \author Alex Robinson
//! \brief  Particle simulation manager factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FRENSIE_PARTICLE_SIMULATION_MANAGER_FACTORY_HPP
#define FRENSIE_PARTICLE_SIMULATION_MANAGER_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "Utility_Communicator.hpp"
#include "Utility_ArchivableObject.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

namespace Details{

struct ParticleSimulationManagerFactoryCreateHelper;
  
} // end Details namespace

//! The particle simulation manager factory class
class ParticleSimulationManagerFactory : public Utility::ArchivableObject<ParticleSimulationManagerFactory>
{

public:

  //! Constructor
  ParticleSimulationManagerFactory(
               const std::shared_ptr<const FilledGeometryModel>& model,
               const std::shared_ptr<ParticleSource>& source,
               const std::shared_ptr<EventHandler>& event_handler,
               const std::shared_ptr<SimulationProperties>& properties,
               const std::string& simulation_name = "simulation",
               const std::string& archive_type = "xml",
               const unsigned threads = 1 );

  //! Restart constructor
  ParticleSimulationManagerFactory(
                          const boost::filesystem::path& archived_manager_name,
                          const unsigned threads = 1 );

  //! Restart constructor
  ParticleSimulationManagerFactory(
                          const boost::filesystem::path& archived_manager_name,
                          const uint64_t number_of_additional_histories,
                          const unsigned threads = 1 );

  //! Restart constructor
  ParticleSimulationManagerFactory(
                          const boost::filesystem::path& archived_manager_name,
                          const double wall_time,
                          const unsigned threads = 1 );

  //! Restart constructor
  ParticleSimulationManagerFactory(
                          const boost::filesystem::path& archived_manager_name,
                          const uint64_t number_of_additional_histories,
                          const double wall_time,
                          const unsigned threads = 1 );

  //! Set the weight windows that will be used by the manager
  void setWeightWindows( const std::shared_ptr<const WeightWindow>& weight_windows );

  //! Set the collision forcer that will be used by the manager
  void setCollisionForcer( const std::shared_ptr<const CollisionForcer>& collision_forcer );

  //! Return the manager
  std::shared_ptr<ParticleSimulationManager> getManager();

private:

  //! Archive constructor
  ParticleSimulationManagerFactory(
                const std::shared_ptr<const FilledGeometryModel>& model,
                const std::shared_ptr<ParticleSource>& source,
                const std::shared_ptr<EventHandler>& event_handler,
                const std::shared_ptr<const WeightWindow>& weight_windows,
                const std::shared_ptr<const CollisionForcer>& collision_forcer,
                const std::shared_ptr<SimulationProperties>& properties,
                const std::string& simulation_name,
                const std::string& archive_type,
                const uint64_t next_history,
                const uint64_t rendezvous_number );

  // The name that will be used when archiving the object
  const char* getArchiveName() const final override;

  // Serialize the simulation manager data 
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Declare the particle simulation manager as a friend
  friend class ParticleSimulationManager;

  // Declare the create manager helper as a friend
  friend class Details::ParticleSimulationManagerFactoryCreateHelper;

  // The name used in archive name-value pairs
  static const std::string s_archive_name;

  // The simulation name
  std::string d_simulation_name;

  // The archive type
  std::string d_archive_type;

  // The filled geometry model
  std::shared_ptr<const FilledGeometryModel> d_model;

  // The particle source
  std::shared_ptr<ParticleSource> d_source;

  // The event handler
  std::shared_ptr<EventHandler> d_event_handler;

  // The weight windows
  std::shared_ptr<const WeightWindow> d_weight_windows;

  // The collision forcer
  std::shared_ptr<const CollisionForcer> d_collision_forcer;

  // The simulation properties
  std::shared_ptr<SimulationProperties> d_properties;

  // The next history to run
  uint64_t d_next_history;

  // The rendezvous number (counter)
  uint64_t d_rendezvous_number;

  // The communicator
  std::shared_ptr<const Utility::Communicator> d_comm;

  // The particle simulation manager
  std::shared_ptr<ParticleSimulationManager> d_simulation_manager;
};

// Save the data to an archive
template<typename Archive>
void ParticleSimulationManagerFactory::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_simulation_name );
  ar & BOOST_SERIALIZATION_NVP( d_model );
  ar & BOOST_SERIALIZATION_NVP( d_source );
  ar & BOOST_SERIALIZATION_NVP( d_event_handler );
  ar & BOOST_SERIALIZATION_NVP( d_weight_windows );
  ar & BOOST_SERIALIZATION_NVP( d_collision_forcer );
  ar & BOOST_SERIALIZATION_NVP( d_properties );
  ar & BOOST_SERIALIZATION_NVP( d_next_history );
  ar & BOOST_SERIALIZATION_NVP( d_rendezvous_number );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ParticleSimulationManagerFactory, MonteCarlo, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleSimulationManagerFactory );

//---------------------------------------------------------------------------//

#endif // end FRENSIE_PARTICLE_SIMULATION_MANAGER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManagerFactory.hpp
//---------------------------------------------------------------------------//
