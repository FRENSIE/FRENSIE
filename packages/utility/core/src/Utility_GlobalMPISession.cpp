//---------------------------------------------------------------------------//
//!
//! \file   Utility_GlobalMPISession.cpp
//! \author Alex Robinson
//! \brief  The global mpi session class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>
#include <exception>
#include <functional>

// FRENSIE Includes
#include "Utility_GlobalMPISession.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_LoggingMacros.hpp"
#include "FRENSIE_config.hpp"

namespace Utility{

// Initialize static member data
int GlobalMPISession::s_rank = 0;
int GlobalMPISession::s_size = 1;

/*! The GlobalMPISession implementation
 * \ingroup mpi
 */
class GlobalMPISession::GlobalMPISessionImpl
{

public:

  //! Detault constructor
  GlobalMPISessionImpl( bool abort_on_exception = true )
#ifdef HAVE_FRENSIE_MPI
    : d_environment( abort_on_exception )
#endif
  { /* ... */ }

  //! Constructor with threading level
  GlobalMPISessionImpl( boost::mpi::threading::level level,
                               bool abort_on_exception )
#ifdef HAVE_FRENSIE_MPI
    : d_environment( level, abort_on_exception )
#endif
  { /* ... */ }

  //! Constructor with command-line inputs
  GlobalMPISessionImpl( int& argc, char**& argv, bool abort_on_exception )
#ifdef HAVE_FRENSIE_MPI
    : d_environment( argc, argv, abort_on_exception )
#endif
  { /* ... */ }

  //! Constructor with command-line inputs and threading level
  GlobalMPISessionImpl( int& argc, char**& argv,
                               boost::mpi::threading::level level,
                               bool abort_on_exception )
#ifdef HAVE_FRENSIE_MPI
    : d_environment( argc, argv, level, abort_on_exception )
#endif
  { /* ... */ }

  //! Destructor
  ~GlobalMPISessionImpl()
  {
#ifdef HAVE_FRENSIE_MPI
    // Restore stream buffers
    StreamList::iterator stream_it, stream_end;
    stream_it = d_streams.begin();
    stream_end = d_streams.end();

    while( stream_it != stream_end )
    {
      (*stream_it)->rdbuf( d_stream_buffer_cache[stream_it->get()] );
      
      ++stream_it;
    }
#endif
  }

  //! Cache a stream buffer
  void cacheStreamBuffer( boost::shared_ptr<std::ostream>& os )
  {
#ifdef HAVE_FRENSIE_MPI
    StreamBufferCache::iterator it = 
      d_stream_buffer_cache.find( os.get() );

    if( it == d_stream_buffer_cache.end() )
    {
      d_stream_buffer_cache[os.get()] = os->rdbuf();
      d_streams.push_back( os );
    }
#endif
  }

private:

#ifdef HAVE_FRENSIE_MPI
  // The boost mpi environment
  boost::mpi::environment d_environment;

  // The streams that have cached stream buffers
  typedef std::list<boost::shared_ptr<std::ostream> > StreamList;
  StreamList d_streams;

  // The stream buffer cache
  typedef std::map<std::ostream*,std::streambuf*> StreamBufferCache;
  StreamBufferCache d_stream_buffer_cache;
#endif
};

#ifdef HAVE_FRENSIE_MPI

/*! The mpi timer
 *
 * This class wraps the boost::mpi::timer class.
 * \ingroup mpi
 */
class MPITimer : public Timer
{

public:

  //! Constructor
  MPITimer() noexcept
    : d_raw_timer(),
      d_duration( std::chrono::duration<double>::zero() )
  { /* ... */ }

  //! Destructor
  ~MPITimer()
  { /* ... */ }

  //! Check if the timer is stopped
  bool isStopped() const override
  { return d_raw_timer == NULL; }

  //! Get the elapsed time (in seconds)
  std::chrono::duration<double> elapsed() const override
  {
    if( this->isStopped() )
      return d_duration;
    else
    {
      return d_duration +
        std::chrono::duration<double>(d_raw_timer->elapsed());
    }
  }

  //! Start the timer
  void start() override
  {
    if( this->isStopped() )
    {
      d_duration = std::chrono::duration<double>::zero();

      d_raw_timer.reset( new boost::mpi::timer );
    }
  }

  //! Stop the timer
  void stop() override
  {
    if( !this->isStopped() )
    {
      d_duration += std::chrono::duration<double>(d_raw_timer->elapsed());

      d_raw_timer.reset();
    }
  }

  //! Resume the timer
  void resume() override
  {
    if( this->isStopped() )
      d_raw_timer.reset( new boost::mpi::timer );
  }

private:

  // The boost::mpi::timer object
  std::unique_ptr<boost::mpi::timer> d_raw_timer;

  // The timer duration
  std::chrono::duration<double> d_duration;
};

/*! \brief The ThreadSupportLevelTraits class
 * \ingroup mpi
 * \ingroup traits
 */
template<typename ThreadSupportLevelTag>
struct ThreadSupportLevelTraits
{ /* ... */ };

/*! \brief Specialization of ThreadSupportLevelTraits class for
 * GlobalMPISession::SingleThreading
 * \ingroup mpi
 * \ingroup traits
 */
template<>
struct ThreadSupportLevelTraits<GlobalMPISession::SingleThreading> : public std::integral_constant<boost::mpi::threading::level,boost::mpi::threading::single>
{ /* ... */ };

/*! \brief Specialization of ThreadSupportLevelTraits class for
 * GlobalMPISession::FunneledThreading
 * \ingroup mpi
 * \ingroup traits
 */
template<>
struct ThreadSupportLevelTraits<GlobalMPISession::FunneledThreading> : public std::integral_constant<boost::mpi::threading::level,boost::mpi::threading::funneled>
{ /* ... */ };

/*! \brief Specialization of ThreadSupportLevelTraits class for
 * GlobalMPISession::FunneledThreading
 * \ingroup mpi
 * \ingroup traits
 */
template<>
struct ThreadSupportLevelTraits<GlobalMPISession::SerializedThreading> : public std::integral_constant<boost::mpi::threading::level,boost::mpi::threading::serialized>
{ /* ... */ };

/*! \brief Specialization of ThreadSupportLevelTraits class for
 * GlobalMPISession::MultipleThreading
 * \ingroup mpi
 * \ingroup traits
 */
template<>
struct ThreadSupportLevelTraits<GlobalMPISession::MultipleThreading> : public std::integral_constant<boost::mpi::threading::level,boost::mpi::threading::multiple>
{ /* ... */ };
  
#endif // end HAVE_FRENSIE_MPI

// Detault constructor
GlobalMPISession::GlobalMPISession( bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( abort_on_exception ) )
{ 
  this->initializeRankAndSize();
}

// Constructor with threading level
template<typename ThreadSupportLevelTag>
GlobalMPISession::GlobalMPISession( ThreadSupportLevelTag level_tag,
                                    bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( ThreadSupportLevelTraits<ThreadSupportLevelTag>::value, abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Constructor with command-line inputs
GlobalMPISession::GlobalMPISession( int& argc, char**& argv,
                                    bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( argc, argv, abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Constructor with command-line inputs and threading level
template<typename ThreadSupportLevelTag>
GlobalMPISession::GlobalMPISession( int& argc, char**& argv,
                                    ThreadSupportLevelTag level_tag,
                                    bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( argc, argv, ThreadSupportLevelTraits<ThreadSupportLevelTag>::value, abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Destructor
GlobalMPISession::~GlobalMPISession()
{ /* ... */ }

// Initialize rank and size
void GlobalMPISession::initializeRankAndSize()
{
  static bool rank_size_initialized = false;

  if( !rank_size_initialized )
  {
    boost::mpi::communicator world;
    s_rank = world.rank();
    s_size = world.size();

    rank_size_initialized = true;
  }
}

// Check if MPI has been configured for use
bool GlobalMPISession::isMPIUsed()
{
#ifdef HAVE_FRENSIE_MPI
  return true;
#else
  return false;
#endif
}

// Create a timer
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) and MPI has been initialized, a Utility::MPITimer object will 
 * be created. Otherwise, an OpenMP timer will be created 
 * (see Utility::GlobalOpenMPSession::createTimer).
 */
std::shared_ptr<Timer> GlobalMPISession::createTimer()
{
#ifdef HAVE_FRENSIE_MPI
  if( GlobalMPISession::initialized() && !GlobalMPISession::finalized() )
    return std::shared_ptr<Timer>( new MPITimer() );
#endif

  return GlobalOpenMPSession::createTimer();
}

// Abort all MPI processes
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) make a request to abort all mpi processes with the provided
 * error code.
 */
void GlobalMPISession::abort( int error_code )
{
#ifdef HAVE_FRENSIE_MPI
  boost::mpi::environment::abort( error_code );
#endif
}

// Check if mpi has been initialized
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) return true if MPI has been initialized. If MPI has not
 * been configured for use with FRENSIE, always return true.
 */
bool GlobalMPISession::initialized()
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::environment::initialized();
#else
  return true;
#endif
}

// Check if MPI has been finalized
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) return true if MPI has been finalized.  If MPI has not
 * been configured for use with FRENSIE, always return false.
 */
bool GlobalMPISession::finalized()
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::environment::finalized();
#else
  return false;
#endif
}

// Get the maximum tag value
int GlobalMPISession::maxTag()
{
  return GlobalMPISession::max_tag();
}

// Get the maximum tag value (mirror boost::mpi interface)
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) return the maximum value that may be used for the tag
 * parameter of send/receive ops. Otherwise, return 0.
 */
int GlobalMPISession::max_tag()
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::environment::max_tag();
#else
  return 0;
#endif
}

// Get the tag value used for collective operations
int GlobalMPISession::collectivesTag()
{
  return GlobalMPISession::collectives_tag();
}

// Get the tag value used for collective operations (mirror boost::mpi interface)
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) return the tag value that is reserved for collective ops. 
 * Otherwise, return 1.
 */
int GlobalMPISession::collectives_tag()
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::environment::collectives_tag();
#else
  return 1;
#endif
}

// Get the name of the calling processor
std::string GlobalMPISession::processorName()
{
  return GlobalMPISession::processor_name();
}

// Get the name of the calling processor (mirror boost::mpi interface)
std::string GlobalMPISession::processor_name()
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::environment::processor_name();
#else
  return std::string();
#endif
}

// Get the current level of thread support
int GlobalMPISession::threadLevel()
{
  return GlobalMPISession::thread_level();
}

// Get the current level of thread support (mirror boost::mpi interface)
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) return current level of thread support. Possible values that
 * can be returned are:
 * <ul>
 *  <li>boost::mpi::MPI_THREAD_SINGLE == only one thread will execute,</li>
 *  <li>boost::mpi::MPI_THREAD_FUNNELED == only main thread will do MPI 
 *       calls,</li>
 *  <li>boost::mpi::MPI_THREAD_SERIALIZED == only one thread at a time will
 *       do MPI calls,</li>
 *  <li>boost::mpi::MPI_THREAD_MULTIPLE == multiple threads may do MPI 
 *       calls.</li>
 * </ul>
 * Othersise, return 0.
 */
int GlobalMPISession::thread_level()
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::environment::thread_level();
#else
  return 0;
#endif
}

// Check if the calling process is the main thread
bool GlobalMPISession::isMainThread()
{
  return GlobalMPISession::is_main_thread();
}

// Check if the calling process is the main thread (mirror boost::mpi
// interface)
/*! \details The main thread is w.r.t. the local calling process (e.g.
 * each MPI process may have multiple local threads running).
 */
bool GlobalMPISession::is_main_thread()
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::environment::is_main_thread();
#else
  return GlobalOpenMPISession::getThreadId() == 0;
#endif
}

// Initialize an output stream
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) and MPI has been initialized but not finalized, this method
 * can be used to limit stream output to a single process.
 */
void GlobalMPISession::initializeOutputStream(
                                           boost::shared_ptr<std::ostream>& os,
                                           const int root_process,
                                           const bool limit_logging_to_root )
{
#ifdef HAVE_FRENSIE_MPI
  if( GlobalMPISession::initialized() && !GlobalMPISession::finalized() )
  {
    if( limit_logging_to_root )
    {
      if( this->getRank() != root_process && os.get() )
      {
        d_impl->cacheStreamBuffer( os );
        
        os->rdbuf( NULL );
      }
    }
  }
#endif
}

// Initialize logs
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) and MPI has been initialized but not finalized, this method
 * can be used to limit logging to a single process. The type of logging
 * (synchronous or asynchronous) can also be specified.
 */
void GlobalMPISession::initializeLogs(
                                     boost::shared_ptr<std::ostream>& log_sink,
                                     const int root_process,
                                     const bool limit_logging_to_root,
                                     const bool synchronous_logging )
{
  this->initializeOutputStream(log_sink, root_process, limit_logging_to_root);

  if( GlobalMPISession::initialized() && !GlobalMPISession::finalized() )
  {
    if( synchronous_logging )
    {
      FRENSIE_SETUP_STANDARD_SYNCHRONOUS_LOGS( log_sink );
    }
    else
    {
      FRENSIE_SETUP_STANDARD_ASYNCHRONOUS_LOGS( log_sink );
    }
  }
}

// Initialize error log
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) and MPI has been initialized but not finalized, this method
 * can be used to limit error logging to a single process. The type of 
 * error logging (synchronous or asynchronous) can also be specified.
 */
void GlobalMPISession::initializeErrorLog( boost::shared_ptr<std::ostream>& log_sink,
                                           const int root_process,
                                           const bool limit_logging_to_root,
                                           const bool synchronous_logging )
{
  this->initializeOutputStream(log_sink, root_process, limit_logging_to_root);

  if( GlobalMPISession::initialized() && !GlobalMPISession::finalized() )
  {
    if( synchronous_logging )
    {
      FRENSIE_SETUP_SYNCHRONOUS_ERROR_LOG( log_sink );
    }
    else
    {
      FRENSIE_SETUP_ASYNCHRONOUS_ERROR_LOG( log_sink );
    }
  }
}

// Initialize warning log
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) and MPI has been initialized but not finalized, this method
 * can be used to limit warning logging to a single process. The type of 
 * warning logging (synchronous or asynchronous) can also be specified.
 */
void GlobalMPISession::initializeWarningLog(
                                     boost::shared_ptr<std::ostream>& log_sink,
                                     const int root_process,
                                     const bool limit_logging_to_root,
                                     const bool synchronous_logging )
{
  this->initializeOutputStream(log_sink, root_process, limit_logging_to_root);

  if( GlobalMPISession::initialized() && !GlobalMPISession::finalized() )
  {
    if( synchronous_logging )
    {
      FRENSIE_SETUP_SYNCHRONOUS_WARNING_LOG( log_sink );
    }
    else
    {
      FRENSIE_SETUP_ASYNCHRONOUS_WARNING_LOG( log_sink );
    }
  }
}

// Initialize notification log
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) and MPI has been initialized but not finalized, this method
 * can be used to limit notification logging to a single process. The type of 
 * notification logging (synchronous or asynchronous) can also be specified.
 */
void GlobalMPISession::initializeNotificationLog(
                                     boost::shared_ptr<std::ostream>& log_sink,
                                     const int root_process,
                                     const bool limit_logging_to_root,
                                     const bool synchronous_logging )
{
  this->initializeOutputStream(log_sink, root_process, limit_logging_to_root);

  if( GlobalMPISession::initialized() && !GlobalMPISession::finalized() )
  {
    if( synchronous_logging )
    {
      FRENSIE_SETUP_SYNCHRONOUS_NOTIFICATION_LOG( log_sink );
    }
    else
    {
        FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( log_sink );
    }
  }
}

// Return the rank of the calling process (w.r.t. MPI_COMM_WORLD)
int GlobalMPISession::getRank()
{
  return s_rank;
}

// Return the number of processes (w.r.t. MPI_COMM_WORLD)
int GlobalMPISession::getSize()
{
  return s_size;
}

// Create an mpi synchronization point
void GlobalMPISession::barrier()
{
#ifdef HAVE_FRENSIE_MPI
  boost::mpi::communicator world;
  world.barrier();
#endif
}

// Sum a set of integers across all processes
int GlobalMPISession::sum( const int local_value )
{
#ifdef HAVE_FRENSIE_MPI
  if( !GlobalMPISession::initialized() || GlobalMPISession::finalized() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "GlobalMPISession",
                                "call to sum(int) ignored since mpi is not "
                                "initialized!" );

    return local_value;
  }
  else
  {
    boost::mpi::communicator world;

    return boost::mpi::all_reduce( world, local_value, std::plus<int>() );
  }
#else
  return local_value;
#endif
}

// Sum a set of doubles across all processes
double GlobalMPISession::sum( const double local_value )
{
#ifdef HAVE_FRENSIE_MPI
  if( !GlobalMPISession::initialized() || GlobalMPISession::finalized() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "GlobalMPISession",
                                "call to sum(double) ignored since mpi is not "
                                "initialized!" );

    return local_value;
  }
  else
  {
    boost::mpi::communicator world;

    return boost::mpi::all_reduce( world, local_value, std::plus<double>() );
  }
#else
  return local_value;
#endif
}

// Check if a boolean is true on all processes
bool GlobalMPISession::isGloballyTrue( const bool local_boolean )
{
  return (GlobalMPISession::sum( local_boolean ? 0 : 1 ) == 0 ? true : false);
}

// Check if a boolean is false on all processes
bool GlobalMPISession::isGloballyFalse( const bool local_boolean )
{
  return (GlobalMPISession::sum( local_boolean ? 1 : 0 ) == 0 ? true : false);
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GlobalMPISession.cpp
//---------------------------------------------------------------------------//
