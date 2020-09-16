//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManagerFactory.cpp
//! \author Alex Robinson
//! \brief  Particle simulation manager factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "MonteCarlo_StandardParticleSimulationManager.hpp"
#include "MonteCarlo_BatchedDistributedStandardParticleSimulationManager.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize static member data
const std::string ParticleSimulationManagerFactory::s_archive_name( "manager" );

// Archive constructor
ParticleSimulationManagerFactory::ParticleSimulationManagerFactory(
                const std::shared_ptr<const FilledGeometryModel>& model,
                const std::shared_ptr<ParticleSource>& source,
                const std::shared_ptr<EventHandler>& event_handler,
                const std::shared_ptr<PopulationControl>& population_controller,
                const std::shared_ptr<const CollisionForcer>& collision_forcer,
                const std::shared_ptr<const SimulationProperties>& properties,
                const std::string& simulation_name,
                const std::string& archive_type,
                const uint64_t next_history,
                const uint64_t rendezvous_number,
                const bool use_single_rendezvous_file )
  : d_simulation_name( simulation_name ),
    d_archive_type( archive_type ),
    d_model( model ),
    d_source( source ),
    d_event_handler( event_handler ),
    d_population_controller( population_controller ),
    d_collision_forcer( collision_forcer ),
    d_properties( properties ),
    d_next_history( next_history ),
    d_rendezvous_number( rendezvous_number ),
    d_use_single_rendezvous_file( use_single_rendezvous_file )
{ 
  TEST_FOR_EXCEPTION( next_history == std::numeric_limits<uint64_t>::max(),
                      std::runtime_error,
                      "No more histories can be simulated (the max history "
                      "number has been reached)!" );
  TEST_FOR_EXCEPTION( rendezvous_number == std::numeric_limits<uint64_t>::max(),
                      std::runtime_error,
                      "No more histories can be simulated (the max rendezvous "
                      "number has been)!" );
}

// Constructor
ParticleSimulationManagerFactory::ParticleSimulationManagerFactory(
               const std::shared_ptr<const FilledGeometryModel>& model,
               const std::shared_ptr<ParticleSource>& source,
               const std::shared_ptr<EventHandler>& event_handler,
               const std::shared_ptr<const SimulationProperties>& properties,
               const std::string& simulation_name,
               const std::string& archive_type,
               const unsigned threads )
  : d_simulation_name( simulation_name ),
    d_archive_type( archive_type ),
    d_model( model ),
    d_source( source ),
    d_event_handler( event_handler ),
    d_population_controller( MonteCarlo::PopulationControl::getDefault() ),
    d_collision_forcer( MonteCarlo::CollisionForcer::getDefault() ),
    d_properties( properties ),
    d_next_history( 0 ),
    d_rendezvous_number( 0 ),
    d_use_single_rendezvous_file( true )
{
  // Make sure that the model pointer is valid
  testPrecondition( model.get() );
  // Make sure that the source pointer is valid
  testPrecondition( source.get() );
  // Make sure that the event handler is valid
  testPrecondition( event_handler.get() );
  // Make sure that the properties pointer is valid
  testPrecondition( properties.get() );
  
  TEST_FOR_EXCEPTION( simulation_name.empty(),
                      std::runtime_error,
                      "The simulation name cannot be empty!" );
  TEST_FOR_EXCEPTION( archive_type.empty(),
                      std::runtime_error,
                      "The archive type cannot be empty!" );
  
  Utility::OpenMPProperties::setNumberOfThreads( threads );
}

// Restart constructor
ParticleSimulationManagerFactory::ParticleSimulationManagerFactory(
                          const boost::filesystem::path& archived_manager_name,
                          const unsigned threads )
{
  this->loadFromFile( archived_manager_name );

  // Update the properties
  Utility::OpenMPProperties::setNumberOfThreads( threads );
}

// Restart constructor
/*! \details All rendezvous and batch size properties will be unchanged.
 */
ParticleSimulationManagerFactory::ParticleSimulationManagerFactory(
                          const boost::filesystem::path& archived_manager_name,
                          const uint64_t number_of_additional_histories,
                          const unsigned threads )
{
  this->loadFromFile( archived_manager_name );

  // Update the properties
  const_cast<SimulationProperties&>( *d_properties ).setNumberOfHistories( number_of_additional_histories );
  Utility::OpenMPProperties::setNumberOfThreads( threads );

  // Update the completion criterion
  d_event_handler->setSimulationCompletionCriterion( number_of_additional_histories );
}

// Restart constructor
ParticleSimulationManagerFactory::ParticleSimulationManagerFactory(
                          const boost::filesystem::path& archived_manager_name,
                          const double wall_time,
                          const unsigned threads )
{
  this->loadFromFile( archived_manager_name );

  // Update the properties
  const_cast<SimulationProperties&>( *d_properties ).setSimulationWallTime( wall_time );
  Utility::OpenMPProperties::setNumberOfThreads( threads );

  // Update the completion criterion
  d_event_handler->setSimulationCompletionCriterion( wall_time );
}

// Restart constructor
/*! \details All rendezvous and batch size properties will be unchanged.
 */
ParticleSimulationManagerFactory::ParticleSimulationManagerFactory(
                          const boost::filesystem::path& archived_manager_name,
                          const uint64_t number_of_additional_histories,
                          const double wall_time,
                          const unsigned threads )
{
  this->loadFromFile( archived_manager_name );

  // Update the properties
  const_cast<SimulationProperties&>( *d_properties ).setNumberOfHistories( number_of_additional_histories );
  const_cast<SimulationProperties&>( *d_properties ).setSimulationWallTime( wall_time );
  Utility::OpenMPProperties::setNumberOfThreads( threads );

  // Update the completion criterion
  d_event_handler->setSimulationCompletionCriterion( number_of_additional_histories,
                                                     wall_time );
}

// Restart constructor
/*! \details The following simulation general properties will be used to
 * restart the simulation:
 * <ul>
 *  <li>MonteCarlo::SimulationGeneralProperties::getNumberOfHistories()</li>
 *  <li>MonteCarlo::SimulationGeneralProperties::getMinNumberOfRendezvous()</li>
 *  <li>MonteCarlo::SimulationGeneralProperties::getMaxRendezvousBatchSize()</li>
 *  <li>MonteCarlo::SimulationGeneralProperties::getMinNumberOfBatchersPerRendezvous()</li>
 *  <li>MonteCarlo::SimulationGeneralProperties::getMaxBatchSize()</li>
 *  <li>MonteCarlo::SimulationGeneralProperties::getNumberOfBatchesPerProcessor()</li>
 *  <li>MonteCarlo::SimulationGeneralProperties::getNumberOfSnapshotsPerBatch()</li>
 *  <li>MonteCarlo::SimulationGeneralProperties::getSimulationWallTime()</li>
 * </ul>
 */
ParticleSimulationManagerFactory::ParticleSimulationManagerFactory(
                      const boost::filesystem::path& archived_manager_name,
                      const SimulationGeneralProperties& updated_general_props,
                      const unsigned threads )
{
  this->loadFromFile( archived_manager_name );

  // Update the properties
  const_cast<SimulationProperties&>( *d_properties ).setNumberOfHistories( updated_general_props.getNumberOfHistories() );
  const_cast<SimulationProperties&>( *d_properties ).setMinNumberOfRendezvous( updated_general_props.getMinNumberOfRendezvous() );
  const_cast<SimulationProperties&>( *d_properties ).setMaxRendezvousBatchSize( updated_general_props.getMaxRendezvousBatchSize() );
  const_cast<SimulationProperties&>( *d_properties ).setMinNumberOfBatchesPerRendezvous( updated_general_props.getMinNumberOfBatchesPerRendezvous() );
  const_cast<SimulationProperties&>( *d_properties ).setMaxBatchSize( updated_general_props.getMaxBatchSize() );
  const_cast<SimulationProperties&>( *d_properties ).setNumberOfBatchesPerProcessor( updated_general_props.getNumberOfBatchesPerProcessor() );
  const_cast<SimulationProperties&>( *d_properties ).setNumberOfSnapshotsPerBatch( updated_general_props.getNumberOfSnapshotsPerBatch() );
  const_cast<SimulationProperties&>( *d_properties ).setSimulationWallTime( updated_general_props.getSimulationWallTime() );
  Utility::OpenMPProperties::setNumberOfThreads( threads );

  // Update the completion criterion
  d_event_handler->setSimulationCompletionCriterion( updated_general_props );
}

// Load the archived object (implementation)
void ParticleSimulationManagerFactory::loadFromFileImpl(
                        const boost::filesystem::path& archive_name_with_path )
{
  std::string extension = archive_name_with_path.extension().string();

  // The bpis pointer must be NULL. Depending on the libraries that have been
  // loaded the bpis might be initialized to a non-NULL value
  const boost::archive::detail::basic_pointer_iserializer* zaid_bpis =
    this->resetBpisPointer<Data::ZAID>( extension );
  
  // Import the data in the archive
  BaseArchivableObjectType::loadFromFileImpl( archive_name_with_path );

  // The bpis pointer must be restored to its original value so that libraries
  // that expect it to be non-NULL behave correctly
  this->restoreBpisPointer<Data::ZAID>( extension, zaid_bpis );
}

// Archive the object (implementation)
void ParticleSimulationManagerFactory::saveToFileImpl(
                         const boost::filesystem::path& archive_name_with_path,
                         const bool overwrite ) const
{
  std::string extension = archive_name_with_path.extension().string();

  // The bpos pointer must be NULL. Depending on the libraries that have been
  // loaded the bpos might be initialized to a non-NULL value
  const boost::archive::detail::basic_pointer_oserializer* zaid_bpos =
    this->resetBposPointer<Data::ZAID>( extension );
  
  // Import the data in the archive
  BaseArchivableObjectType::saveToFileImpl( archive_name_with_path, overwrite );

  // The bpos pointer must be restored to its original value so that libraries
  // that expect it to be non-NULL behave correctly
  this->restoreBposPointer<Data::ZAID>( extension, zaid_bpos );
}

// Set the weight windows that will be used by the manager
void ParticleSimulationManagerFactory::setPopulationControl(
                    const std::shared_ptr<PopulationControl>& population_controller )
{
  if( population_controller )
  {
    d_population_controller = population_controller;
  }
}

// Set the collision forcer that will be used by the manager
void ParticleSimulationManagerFactory::setCollisionForcer(
               const std::shared_ptr<const CollisionForcer>& collision_forcer )
{
  if( collision_forcer )
  {
    if( d_next_history > 0 || d_simulation_manager )
    {
      FRENSIE_LOG_TAGGED_WARNING( "ParticleSimulationManagerFactory",
                                  "Setting a collision forcer after a "
                                  "simulation has been started is not "
                                  "allowed!" );
    }
    else
      d_collision_forcer = collision_forcer;
  }
}

namespace Details{

//! The create model helper struct
struct ParticleSimulationManagerFactoryCreateHelper
{
  //! Create the manager
  template<ParticleModeType mode>
  static void createManager( ParticleSimulationManagerFactory& factory )
  {
    if( factory.d_comm->size() > 1 )
    {
      factory.d_simulation_manager.reset(
                 new BatchedDistributedStandardParticleSimulationManager<mode>(
                                          factory.d_simulation_name,
                                          factory.d_archive_type,
                                          factory.d_model,
                                          factory.d_source,
                                          factory.d_event_handler,
                                          factory.d_population_controller,
                                          factory.d_collision_forcer,
                                          factory.d_properties,
                                          factory.d_next_history,
                                          factory.d_rendezvous_number,
                                          factory.d_use_single_rendezvous_file,
                                          factory.d_comm ) );
    }
    else
    {
      factory.d_simulation_manager.reset(
                 new StandardParticleSimulationManager<mode>(
                                      factory.d_simulation_name,
                                      factory.d_archive_type,
                                      factory.d_model,
                                      factory.d_source,
                                      factory.d_event_handler,
                                      factory.d_population_controller,
                                      factory.d_collision_forcer,
                                      factory.d_properties,
                                      factory.d_next_history,
                                      factory.d_rendezvous_number,
                                      factory.d_use_single_rendezvous_file ) );
    }
  }
};
  
} // end Details namespace

// Return the manager
std::shared_ptr<ParticleSimulationManager>
ParticleSimulationManagerFactory::getManager()
{
  if( !d_simulation_manager )
  {
    d_comm = Utility::Communicator::getDefault();
    
    switch( d_properties->getParticleMode() )
    {
      case NEUTRON_MODE:
      {
        Details::ParticleSimulationManagerFactoryCreateHelper::createManager<NEUTRON_MODE>( *this );
        break;
      }
      case PHOTON_MODE:
      {
        Details::ParticleSimulationManagerFactoryCreateHelper::createManager<PHOTON_MODE>( *this );
        break;
      }
      case ELECTRON_MODE:
      {
        Details::ParticleSimulationManagerFactoryCreateHelper::createManager<ELECTRON_MODE>( *this );
        break;
      }
      case NEUTRON_PHOTON_MODE:
      {
        Details::ParticleSimulationManagerFactoryCreateHelper::createManager<NEUTRON_PHOTON_MODE>( *this );
        break;
      }
      case PHOTON_ELECTRON_MODE:
      {
        Details::ParticleSimulationManagerFactoryCreateHelper::createManager<PHOTON_ELECTRON_MODE>( *this );
        break;
      }
      case NEUTRON_PHOTON_ELECTRON_MODE:
      {
        Details::ParticleSimulationManagerFactoryCreateHelper::createManager<NEUTRON_PHOTON_ELECTRON_MODE>( *this );
        break;
      }
      case ADJOINT_NEUTRON_MODE:
      {
        Details::ParticleSimulationManagerFactoryCreateHelper::createManager<ADJOINT_NEUTRON_MODE>( *this );
        break;
      }
      case ADJOINT_PHOTON_MODE:
      {
        Details::ParticleSimulationManagerFactoryCreateHelper::createManager<ADJOINT_PHOTON_MODE>( *this );
        break;
      }
      case ADJOINT_ELECTRON_MODE:
      {
        Details::ParticleSimulationManagerFactoryCreateHelper::createManager<ADJOINT_ELECTRON_MODE>( *this );
        break;
      }
      default:
      {
        THROW_EXCEPTION( std::runtime_error,
                         "The particle mode type ("
                         << d_properties->getParticleMode() <<
                         ") is not supported!" );
      }
    }
  }

  return d_simulation_manager;
}



// The name that will be used when archiving the object
const char* ParticleSimulationManagerFactory::getArchiveName() const
{
  return s_archive_name.c_str();
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleSimulationManagerFactory );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManagerFactory.cpp
//---------------------------------------------------------------------------//
