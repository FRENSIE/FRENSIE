//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager.cpp
//! \author Alex Robinson
//! \brief  Particle simulation manager class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <csignal>

// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

// The registered managers (these must be global so that the custom signal
// handler can access them)
std::set<std::shared_ptr<MonteCarlo::ParticleSimulationManager> > __registered_managers__;

// The default signal handler (cache so that it can be restored later)
void (*__default_signal_handler__)( int );

// The custom signal handler that will forward signals to the registered
// managers
extern "C" void __custom_signal_handler__( int signal )
{
  for( auto&& registered_manager : __registered_managers__ )
  {
    if( registered_manager )
      registered_manager->signalHandler( signal );
  }
}

namespace MonteCarlo{

// Constructor
ParticleSimulationManager::ParticleSimulationManager(
                 const std::string& simulation_name,
                 const std::string& archive_type,
                 const std::shared_ptr<const FilledGeometryModel>& model,
                 const std::shared_ptr<ParticleSource>& source,
                 const std::shared_ptr<EventHandler>& event_handler,
                 const std::shared_ptr<const WeightWindow> weight_windows,
                 const std::shared_ptr<const CollisionForcer> collision_forcer,
                 const std::shared_ptr<const SimulationProperties>& properties,
                 const uint64_t next_history,
                 const uint64_t rendezvous_number )
  : d_simulation_name( simulation_name ),
    d_archive_type( archive_type ),
    d_model( model ),
    d_collision_kernel( new CollisionKernel( model, *properties ) ),
    d_transport_kernel( new TransportKernel( model ) ),
    d_source( source ),
    d_event_handler( event_handler ),
    d_weight_windows( weight_windows ),
    d_collision_forcer( collision_forcer ),
    d_properties( properties ),
    d_next_history( next_history ),
    d_rendezvous_number( rendezvous_number ),
    d_rendezvous_batch_size( 0 ),
    d_batch_size( 0 ),
    d_end_simulation( false )
{
  // Make sure that the simulation name is valid
  testPrecondition( simulation_name.size() > 0 );
  // Make sure that the archive type is valid
  testPrecondition( archive_type.size() > 0 );
  // Make sure that the model pointer is valid
  testPrecondition( model.get() );
  // Make sure that the source pointer is valid
  testPrecondition( source.get() );
  // Make sure that the event handler is valid
  testPrecondition( event_handler.get() );
  // Make sure that the weight windows pointer is valid
  testPrecondition( weight_windows.get() );
  // Make sure that the collision forcer pointer is valid
  testPrecondition( collision_forcer.get() );
  // Make sure that the properties pointer is valid
  testPrecondition( properties.get() );

  // Calculate the rendezvous batch size
  uint64_t number_of_histories = d_properties->getNumberOfHistories();

  if( number_of_histories > 0 )
  {
    d_rendezvous_batch_size =
      number_of_histories/d_properties->getMinNumberOfRendezvous();

    if( d_rendezvous_batch_size > d_properties->getMaxRendezvousBatchSize() )
      d_rendezvous_batch_size = d_properties->getMaxRendezvousBatchSize();
  }
  else
    d_rendezvous_batch_size = d_properties->getMaxRendezvousBatchSize();

  // Calculate the batch size
  d_batch_size =
    d_rendezvous_batch_size/d_properties->getMinNumberOfBatchesPerRendezvous();

  if( d_batch_size > d_properties->getMaxBatchSize() )
    d_batch_size = d_properties->getMaxBatchSize();
}

// Return the next history that will be completed
uint64_t ParticleSimulationManager::getNextHistory() const
{
  return d_next_history;
}

// Return the number of rendezvous
uint64_t ParticleSimulationManager::getNumberOfRendezvous() const
{
  return d_rendezvous_number;
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

// Increment the next history
void ParticleSimulationManager::incrementNextHistory( const uint64_t increment_size )
{
  d_next_history += increment_size;
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

// Get the simulation name
const std::string& ParticleSimulationManager::getSimulationName() const
{
  return d_simulation_name;
}

// Set the simulation name
/*! \details A simulation archive will be generated with the the new name.
 */
void ParticleSimulationManager::setSimulationName( const std::string& new_name )
{
  if( new_name.size() > 0 )
    d_simulation_name = new_name;

  this->basicRendezvous();
}

// Get the simulation archive type
const std::string& ParticleSimulationManager::getSimulationArchiveType() const
{
  return d_archive_type;
}

// Set the simulation archive type
/*! \details Acceptable values are "xml", "txt", "bin", "h5fa". A simulation 
 * archive of the new type will be generated.
 */
void ParticleSimulationManager::setSimulationArchiveType( const std::string& archive_type )
{
  if( archive_type.size() > 0 )
    d_archive_type = archive_type;

  this->basicRendezvous();
}

// Set the simulation name and archive type
/*! \details Acceptable values for the archive type are "xml", "txt", "bin", 
 * "h5fa". A simulation archive with the new name and type will be generated.
 */
void ParticleSimulationManager::setSimulationNameAndArchiveType(
                                              const std::string& new_name,
                                              const std::string& archive_type )
{
  if( new_name.size() > 0 )
    d_simulation_name = new_name;
  
  if( archive_type.size() > 0 )
    d_archive_type = archive_type;

  this->basicRendezvous();
}

// Run the simulation set up by the user
void ParticleSimulationManager::runSimulation()
{
  FRENSIE_LOG_NOTIFICATION( "Simulation started. " );
  FRENSIE_FLUSH_ALL_LOGS();

  // Enable thread support
  this->enableThreadSupport();

  // Conduct the first rendezvous (for caching only)
  this->rendezvous();

  // The simulation has started
  this->registerSimulationStartedEvent();

  uint64_t next_rendezvous_history = d_next_history + d_rendezvous_batch_size;
  
  while( !d_event_handler->isSimulationComplete() )
  {
    if( !d_end_simulation )
    {
      this->runSimulationBatch( d_next_history, d_next_history+d_batch_size );

      this->incrementNextHistory( d_batch_size );
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
  this->registerSimulationStoppedEvent();

  if( !d_end_simulation )
  {
    FRENSIE_LOG_NOTIFICATION( "Simulation finished. " );
  }
  else
  {
    FRENSIE_LOG_NOTIFICATION( "Simulation terminated. " );
  }
  FRENSIE_FLUSH_ALL_LOGS();

  this->rendezvous();
}

// Run the simulation set up by the user with the ability to interrupt
/*! \details Sending a SIGINT signal (usually Ctrl+C) will cause the
 * simulation to be terminated once the current batch is completed. Sending
 * a second SIGINT signal before the simulation has been terminated will 
 * cause the program to exit immediately.
 */ 
void ParticleSimulationManager::runInterruptibleSimulation()
{
  #pragma omp critical (register_manager)
  {
    if( __registered_managers__.empty() )
    {
      __default_signal_handler__ =
        std::signal( SIGINT, __custom_signal_handler__ );
    }
        
    __registered_managers__.insert( this->shared_from_this() );
  }

  this->runSimulation();

  #pragma omp critical (register_manager)
  {
    __registered_managers__.erase( this->shared_from_this() );
    
    if( __registered_managers__.empty() )
      std::signal( SIGINT, __default_signal_handler__ );
  }
}

// Enable thread support
void ParticleSimulationManager::enableThreadSupport()
{
  // Set up the random number generator for the number of threads requested
  Utility::RandomNumberGenerator::createStreams();

  // Enable source thread support
  d_source->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  // Enable event handler thread support
  d_event_handler->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );
}

// Reset data
void ParticleSimulationManager::resetData()
{
  d_event_handler->resetObserverData();
  d_source->resetData();
}

// Reduce distributed data
void ParticleSimulationManager::reduceData( const Utility::Communicator& comm,
                                            const int root_process )
{
  comm.barrier();
  
  d_source->reduceData( comm, root_process );
  d_event_handler->reduceObserverData( comm, root_process );

  comm.barrier();
}

// Register simulation started event
void ParticleSimulationManager::registerSimulationStartedEvent()
{
  d_event_handler->updateObserversFromParticleSimulationStartedEvent();
}

// Register simulation stopped event
void ParticleSimulationManager::registerSimulationStoppedEvent()
{
  d_event_handler->updateObserversFromParticleSimulationStoppedEvent();
}

// Check if the simulation is complete
bool ParticleSimulationManager::isSimulationComplete()
{
  return d_event_handler->isSimulationComplete();
}

// Rendezvous (cache state)
void ParticleSimulationManager::rendezvous()
{
  this->basicRendezvous();

  ++d_rendezvous_number;
}

// Conduct a basic rendezvous
void ParticleSimulationManager::basicRendezvous() const
{
  std::string archive_name( d_simulation_name );
  archive_name += "_rendezvous_";
  archive_name += Utility::toString( d_rendezvous_number );
  archive_name += ".";
  archive_name += d_archive_type;

  FRENSIE_LOG_NOTIFICATION( "Rendezvous "
                            << d_rendezvous_number << ": "
                            << d_next_history );

  FRENSIE_FLUSH_ALL_LOGS();
  
  ParticleSimulationManagerFactory
    tmp_factory( d_model,
                 d_source,
                 d_event_handler,
                 d_weight_windows,
                 d_collision_forcer,
                 d_properties,
                 d_simulation_name,
                 d_archive_type,
                 d_next_history,
                 d_rendezvous_number+1 );

  tmp_factory.saveToFile( archive_name, true );
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
      catch( const std::runtime_error& exception )
      {
        LOG_LOST_PARTICLE_DETAILS( source_bank.top() );
        
        FRENSIE_LOG_NESTED_ERROR( exception.what() );
        
        continue;
      }
      // The source has likely been constructed incorrectly
      catch( const std::logic_error& exception )
      {        
        FRENSIE_LOG_NESTED_ERROR( exception.what() );

        std::exit( 1 );
      }

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

// The signal handler
/*! \details The first signal will cause the simulation to finish. The
 * second signal will cause the simulation to end without caching its state.
 * Only the SIGINT signal can currently cause the simulation to finish.
 */
void ParticleSimulationManager::signalHandler( int signal )
{
  if( this->isSignalTypeHandled( signal ) )
  {
    static int number_of_signals_handled = 0;

    ++number_of_signals_handled;
    
    FRENSIE_LOG_NOTIFICATION( "Terminating simulation..." );
    
    if( number_of_signals_handled == 1 )
      d_end_simulation = true;
    
    this->exitIfRequired( number_of_signals_handled, signal );
  }
}

// Check if a signal type is handled by the manager
bool ParticleSimulationManager::isSignalTypeHandled( const int signal )
{
  return signal == SIGINT;
}

// Exit if required based on signal count
void ParticleSimulationManager::exitIfRequired( const int signal_counter,
                                                const int signal ) const
{
  if( signal_counter > 1 )
    exit( signal );
}

// Check if the simulation has been ended by the user
bool ParticleSimulationManager::hasEndSimulationRequestBeenMade() const
{
  return d_end_simulation;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager.cpp
//---------------------------------------------------------------------------//
