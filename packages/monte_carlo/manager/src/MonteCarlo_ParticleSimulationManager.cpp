//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager.cpp
//! \author Alex Robinson
//! \brief  Particle simulation manager class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize static member data
const std::string ParticleSimulationManager::s_archive_name( "manager" );

// Constructor
ParticleSimulationManager::ParticleSimulationManager(
                 const std::shared_ptr<const FilledGeometryModel>& model,
                 const std::shared_ptr<ParticleSource>& source,
                 const std::shared_ptr<EventHandler>& event_handler,
                 const std::shared_ptr<const SimulationProperties>& properties,
                 const std::string& simulation_name )
  : d_simulation_name( simulation_name ),
    d_model( model ),
    d_collision_kernel( new CollisionKernel( model, *properties ) ),
    d_transport_kernel( new TransportKernel( model ) ),
    d_source( source ),
    d_event_handler( event_handler ),
    d_weight_windows( MonteCarlo::WeightWindows::getDefault() ),
    d_collision_forcer( MonteCarlo::CollisionForcer::getDefault() ),
    d_properties( properties ),
    d_next_history( 0 ),
    d_rendezvous_number( 0 ),
    d_rendezvous_batch_size( 0 ),
    d_batch_size( 0 ),
    d_end_simulation( false );
{
  // Make sure that the simulation name is valid
  testPrecondition( simulation_name.size() > 0 );
  // Make sure that the model pointer is valid
  testPrecondition( model.get() );
  // Make sure that the source pointer is valid
  testPrecondition( source.get() );
  // Make sure that the event handler is valid
  testPrecondition( event_handler.get() );
  // Make sure that the properties pointer is valid
  testPrecondition( properties.get() );

  // Calculate the rendezvous batch size
  uint64_t number_of_histories = d_properties->getMinNumberOfHistories();

  if( number_of_histories > 0 )
  {
    d_rendezvous_batch_size =
      number_of_histories/d_properties->getMinNumberOfRendezvous();

    if( d_rendezvous_batch_size > d_properties->getMaxRendezvousBatchSize() )
      d_rendezvous_batch_size = d_properties->getMaxRendezvousBatchSize();
  }

  // Calculate the batch size
  d_batch_size =
    d_rendezvous_batch_size/d_properties->getMinNumberOfBatchesPerRendezvous();

  if( d_batch_size > d_properties->getMaxBatchSize() )
    d_batch_size = d_properties->getMaxBatchSize();
}

// Restart constructor
ParticleSimulationManager::ParticleSimulationManager(
                         const boost::filesystem::path& archived_manager_name )
{
  this->loadFromFile( file_name_with_path );
}

// Return the rendezvous batch size
uint64_t ParticleSimulationManager::getRendezvousBatchSize() const
{
  return d_rendezvous_batch_size;
}

// Return the batch size
uint64_t ParticleSimulationManager::getBatchSize() const
{
  return d_batch_size;
}

// Set the batch size
void ParticleSimulationManager::setBatchSize( const uint64_t batch_size )
{
  d_batch_size = batch_size;
}

// Return the model
const FilledGeometryModel& ParticleSimulationManager::getModel() const
{
  return *d_model;
}

// Return the source
const ParticleSource& ParticleSimulationManager::getSource() const
{
  return *d_source;
}

// Return the event handler
const EventHandler& ParticleSimulationManager::getEventHandler() const
{
  return *d_event_handler;
}

// Return the event handler
EventHandler& ParticleSimulationManager::getEventHandler()
{
  return *d_event_handler;
}

// Return the next history that will be completed
uint64_t ParticleSimulationManager::getNextHistory() const
{
  return d_next_history;
}

// Set the weight windows
void ParticleSimulationManager::setWeightWindows(
                    const std::shared_ptr<const WeightWindow>& weight_windows )
{
  if( weight_windows )
  {
    if( d_next_history > 0 )
    {
      FRENSIE_LOG_TAGGED_WARNING( "ParticleSimulationManager",
                                  "Setting weight windows after a simulation "
                                  "has been started is not allowed!" );
    }
    else
      d_weight_windows = weight_windows;
  }
}

// Set the collision forcer
void ParticleSimulationManager::setCollisionForcer(
               const std::shared_ptr<const CollisionForcer>& collision_forcer )
{
  if( collision_forcer )
  {
    if( d_next_history > 0 )
    {
      FRENSIE_LOG_TAGGED_WARNING( "ParticleSimulationManager",
                                  "Setting a collision forcer after a "
                                  "simulation has been started is not "
                                  "allowed!" );
    }
    else
      d_collision_forcer = collision_forcer;
  }
}

// Rename the simulation
void ParticleSimulationManager::renameSimulation( const std::string& name )
{
  if( name.size() > 0 )
    d_simulation_name = name;
}

// Run the simulation set up by the user
void ParticleSimulationManager::runSimulation()
{
  FRENSIE_LOG_NOTIFICATION( "Simulation started. " );
  FRENSIE_FLUSH_ALL_LOGS();

  // Set up the random number generator for the number of threads requested
  Utility::RandomNumberGenerator::createStreams();

  // Enable source thread support
  d_source->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  // Enable event handler thread support
  d_event_handler->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  // The simulation has started
  d_event_handler->updateObserversFromParticleSimulationStartedEvent();

  uint64_t next_rendezvous_history = d_next_history + d_rendezvous_batch_size;
  
  while( !d_event_handler->isSimulationComplete() )
  {
    if( !d_end_simulation )
    {
      this->runSimulationBatch( d_next_history, d_next_history+d_batch_size );

      d_next_history += d_batch_size;
    }
    else // end the simulation if requested (from signal handler)
      break;
    
    if( next_rendezvous_history <= d_next_history )
    {
      this->rendezvous();

      next_rendezvous_history += d_rendezvous_batch_size;
    }
  }

  // The simulation has finished
  d_event_handler->updateObserversFromParticleSimiulationStoppedEvent();

  if( !d_end_simulation )
  {
    FRENSIE_LOG_NOTIFICATION( "Simulation finished. " );
  }
  else
  {
    FRENSIE_LOG_WARNING( "Simulation terminated. " );
  }
  FRENSIE_FLUSH_ALL_LOGS();
}

// Rendezvous (cache state)
void ParticleSimulationManager::rendezvous()
{
  std::string archive_name( d_simulation_name );
  archive_name += "_";
  archive_name += Utility::toString( d_rendezvous_number );
  
  this->saveToFile( archive_name, true );

  ++d_rendezvous_number;
}

// Print the simulation data to the desired stream
void ParticleSimulationManager::printSimulationSummary( std::ostream& os ) const
{
  d_source->printSummary( os );
  d_event_handler->printObserverSummaries( os );
}

// Log the simulation data
void ParticleSimulationManager::logSimulationSummary() const
{
  d_source->logSummary();
  d_event_handler->logObserverSummaries();
}

// Run the simulation batch
void ParticleSimulationManager::runSimulationBatch(
                                            const uint64_t batch_start_history,
                                            const uint64_t batch_end_history )
{
  // Make sure the history range is valid
  testPrecondition( batch_start_history <= batch_end_history );

  #pragma omp parallel num_threads( Utility::OpenMPProperties::getRequestedNumberOfThreads() )
  {
    // Create a bank for each thread
    ParticleBank source_bank, bank;
    
    #pragma omp for
    for( uint64_t history = batch_start_history; history < batch_end_history; ++history )
    {
      // Initialize the random number generator for this history
      Utility::RandomNumberGenerator::initialize( history );

      // Sample a particle state from the source
      try{
        d_source->sampleParticleState( source_bank, history );
      }
      CATCH_LOST_SOURCE_PARTICLE_AND_CONTINUE( source_bank );

      // Simulate the particles generated by the source first
      while( source_bank.size() > 0 )
      {
        this->simulateUnresolvedParticle( source_bank.top(), bank, true );

        source_bank.pop();
      }

      // This history only ends when the particle bank is empty
      while( bank.size() > 0 )
      {            
        this->simulateUnresolvedParticle( bank.top(), bank, false );
        
        bank.pop();
      }

      // History complete - commit all observer history contributions
      d_event_handler->commitObserverHistoryContributions();
    }
  }
}

// The name that will be used when archiving the object
const char* ParticleSimulationManager::getArchiveName() const
{
  return s_archive_name.c_str();
}

// The signal handler
/*! \details The first signal will cause the simulation to finish. The
 * second signal will cause the simulation to end without caching its state.
 */
void ParticleSimulationManager::signalHandler( int signal )
{
  static int number_of_signals_handled = 0;

  ++number_of_signals_handled;
  
  FRENSIE_LOG_WARNING( "Terminating simulation..." );
  
  if( number_of_signals_handled == 1 )
    d_end_simulation = true;
  else // number_of_signals_handled > 1 
    exit( 0 );
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleSimulationManager );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ParticleSimulationManager );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager.cpp
//---------------------------------------------------------------------------//
