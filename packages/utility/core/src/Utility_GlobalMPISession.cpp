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
#include "Utility_OpenMPProperties.hpp"
#include "Utility_LoggingMacros.hpp"
#include "FRENSIE_config.hpp"

namespace Utility{

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

/*! The ThreadingSupportLevelTagTraits traits class
 * \ingroup mpi
 * \ingroup traits
 */
template<typename ThreadingSupportLevelTag>
struct ThreadingSupportLevelTagTraits
{ /* ... */ };

/*! \brief Specialization of ThreadingSupportLevelTagTraits for
 * GlobalMPISession::SingleThreadingTag
 * \ingroup mpi
 * \ingroup traits
 */
template<>
struct ThreadingSupportLevelTagTraits<GlobalMPISession::SingleThreadingTag> : public std::integral_constant<boost::mpi::threading::level,boost::mpi::threading::single>
{ /* ... */ };

/*! \brief Specialization of ThreadingSupportLevelTagTraits for
 * GlobalMPISession::FunneledThreadingTag
 * \ingroup mpi
 * \ingroup traits
 */
template<>
struct ThreadingSupportLevelTagTraits<GlobalMPISession::FunneledThreadingTag> : public std::integral_constant<boost::mpi::threading::level,boost::mpi::threading::funneled>
{ /* ... */ };

/*! \brief Specialization of ThreadingSupportLevelTagTraits for
 * GlobalMPISession::SerializedThreadingTag
 * \ingroup mpi
 * \ingroup traits
 */
template<>
struct ThreadingSupportLevelTagTraits<GlobalMPISession::SerializedThreadingTag> : public std::integral_constant<boost::mpi::threading::level,boost::mpi::threading::serialized>
{ /* ... */ };

/*! \brief Specialization of ThreadingSupportLevelTagTraits for
 * GlobalMPISession::MultipleThreadingTag
 * \ingroup mpi
 * \ingroup traits
 */
template<>
struct ThreadingSupportLevelTagTraits<GlobalMPISession::MultipleThreadingTag> : public std::integral_constant<boost::mpi::threading::level,boost::mpi::threading::multiple>
{ /* ... */ };

#endif // end HAVE_FRENSIE_MPI

// Initialize static member data
GlobalMPISession::SingleThreadingTag GlobalMPISession::SingleThreading;
GlobalMPISession::FunneledThreadingTag GlobalMPISession::FunneledThreading;
GlobalMPISession::SerializedThreadingTag GlobalMPISession::SerializedThreading;
GlobalMPISession::MultipleThreadingTag GlobalMPISession::MultipleThreading;
int GlobalMPISession::s_rank = 0;
int GlobalMPISession::s_size = 1;

// Convert a GlobalMPISession::SingleThreadingTag to an int
GlobalMPISession::SingleThreadingTag::operator int() const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::threading::single;
#else
  return 0;
#endif
}

// Convert a GlobalMPISession::FunneledThreadingTag to an int
GlobalMPISession::FunneledThreadingTag::operator int() const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::threading::funneled;
#else
  return 0;
#endif
}

// Convert a GlobalMPISession::SerializedThreadingTag to an int
GlobalMPISession::SerializedThreadingTag::operator int() const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::threading::serialized;
#else
  return 0;
#endif
}

// Convert a GlobalMPISession::MultipleThreadingTag to an int
GlobalMPISession::MultipleThreadingTag::operator int() const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::threading::multiple;
#else
  return 0;
#endif
}

/*! The output stream cache
 *
 * This class stores the stream buffers that get replaced when output
 * is suppressed on a certain process by the Utility::GlobalMPISession. These
 * stream buffers can be restored manually or the user can simply wait until
 * an object of this class is destroyed, at which point all of the cached
 * streams will have their buffers restored.
 * \ingroup mpi
 */
class OutputStreamCache
{

public:

  //! Constructor
  OutputStreamCache()
  { /* ... */ }

  //! Destructor
  ~OutputStreamCache()
  {
    this->restoreStreamBuffers();
  }

  //! Cache a stream buffer
  void cacheStreamBuffer( boost::shared_ptr<std::ostream> os )
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

  //! Restore a stream buffer
  void restoreStreamBuffer( boost::shared_ptr<std::ostream> os )
  {
#ifdef HAVE_FRENSIE_MPI
    StreamBufferCache::iterator it =
      d_stream_buffer_cache.find( os.get() );

    if( it != d_stream_buffer_cache.end() )
    {
      os->rdbuf( it->second );

      d_stream_buffer_cache.erase( it );

      d_streams.remove( os );
    }
#endif
  }

  //! Restore all stream buffers
  void restoreStreamBuffers()
  {
#ifdef HAVE_FRENSIE_MPI
    StreamList::iterator list_it, list_end;
    list_it = d_streams.begin();
    list_end = d_streams.end();

    while( list_it != list_end )
    {
      StreamBufferCache::iterator buffer_cache_it =
        d_stream_buffer_cache.find( list_it->get() );

      if( buffer_cache_it != d_stream_buffer_cache.end() )
        (*list_it)->rdbuf( buffer_cache_it->second );

      ++list_it;
    }

    // Clear the cache
    d_stream_buffer_cache.clear();
    d_streams.clear();
#endif
  }

private:

#ifdef HAVE_FRENSIE_MPI
  // The streams that have cached stream buffers
  typedef std::list<boost::shared_ptr<std::ostream> > StreamList;
  StreamList d_streams;

  // The stream buffer cache
  typedef std::map<std::ostream*,std::streambuf*> StreamBufferCache;
  StreamBufferCache d_stream_buffer_cache;
#endif
};

/*! The GlobalMPISession implementation
 *
 * This class simply wraps the boost::mpi::environment object and provides
 * some additional constructors to help with initialization. It MPI has not
 * been configured for use this class is empty but the constructors can
 * still be used (dummy initialization).
 * \ingroup mpi
 */
class GlobalMPISession::GlobalMPISessionImpl
{

public:

  //! Default constructor
  GlobalMPISessionImpl( bool abort_on_exception = true )
#ifdef HAVE_FRENSIE_MPI
    : d_environment( abort_on_exception )
#endif
  {
    this->initializeWorldComm();
  }

  //! Constructor with threading level
  template<typename ThreadSupportLevelTag>
  GlobalMPISessionImpl( ThreadSupportLevelTag level,
                        typename std::enable_if<std::is_empty<ThreadSupportLevelTag>::value,bool>::type abort_on_exception )
#ifdef HAVE_FRENSIE_MPI
    : d_environment( ThreadingSupportLevelTagTraits<ThreadSupportLevelTag>::value, abort_on_exception )
#endif
  {
    this->initializeWorldComm();
  }

  //! Constructor with command-line inputs
  GlobalMPISessionImpl( int& argc, char**& argv, bool abort_on_exception )
#ifdef HAVE_FRENSIE_MPI
    : d_environment( argc, argv, abort_on_exception )
#endif
  {
    this->initializeWorldComm();
  }

  //! Constructor with command-line inputs and threading level
  template<typename ThreadSupportLevelTag>
  GlobalMPISessionImpl( int& argc, char**& argv,
                        ThreadSupportLevelTag level,
                        typename std::enable_if<std::is_empty<ThreadSupportLevelTag>::value,bool>::type abort_on_exception )
#ifdef HAVE_FRENSIE_MPI
    : d_environment( argc, argv, ThreadingSupportLevelTagTraits<ThreadSupportLevelTag>::value, abort_on_exception )
#endif
  {
    this->initializeWorldComm();
  }

  //! Destructor
  ~GlobalMPISessionImpl()
  {
    this->finalizeWorldComm();
    s_ostream_cache.restoreStreamBuffers();
  }

  //! Get the output stream cache
  static OutputStreamCache& getOutputStreamCache()
  { return s_ostream_cache; }

#ifdef HAVE_FRENSIE_MPI
  //! Get the world communicator
  static boost::mpi::communicator& getWorldComm()
  { return *s_world_comm; }
#endif

  //! Gather values on the desired process
  template<typename T>
  static std::vector<T> gatherValues( const int root, const T& local_value )
  {
#ifdef HAVE_FRENSIE_MPI
    if( GlobalMPISessionImpl::getWorldComm().rank() == root )
    {
      std::vector<T> gathered_values;

      boost::mpi::gather( GlobalMPISessionImpl::getWorldComm(),
                          local_value,
                          gathered_values,
                          root );
      return gathered_values;
    }
    else
    {
      boost::mpi::gather( GlobalMPISessionImpl::getWorldComm(), local_value, root );

      return std::vector<T>();
    }
#else
    return std::vector<T>( 1, local_value );
#endif
  }

private:

  // Initialize the world comm
  static void initializeWorldComm()
  {
#ifdef HAVE_FRENSIE_MPI
    s_world_comm.reset( new boost::mpi::communicator );
#endif
  }

  // Finalize the world comm
  static void finalizeWorldComm()
  {
#ifdef HAVE_FRENSIE_MPI
    s_world_comm.reset();
#endif
  }

  // The output stream cache
  static OutputStreamCache s_ostream_cache;

#ifdef HAVE_FRENSIE_MPI
  // The world communicator
  static std::unique_ptr<boost::mpi::communicator> s_world_comm;

  // The boost mpi environment
  boost::mpi::environment d_environment;
#endif
};

// Initialize the output stream cache
OutputStreamCache GlobalMPISession::GlobalMPISessionImpl::s_ostream_cache;

// Initialize the world communicator
#ifdef HAVE_FRENSIE_MPI
  std::unique_ptr<boost::mpi::communicator> GlobalMPISession::GlobalMPISessionImpl::s_world_comm;
#endif // end HAVE_FRENSIE_MPI

// Default constructor
GlobalMPISession::GlobalMPISession( bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Constructor for single threading support level
GlobalMPISession::GlobalMPISession( SingleThreadingTag level,
                                    bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( level, abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Constructor for funneled threading support level
GlobalMPISession::GlobalMPISession( FunneledThreadingTag level,
                                    bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( level, abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Constructor for serialized threading support level
GlobalMPISession::GlobalMPISession( SerializedThreadingTag level,
                                    bool abort_on_exception )
    : d_impl( new GlobalMPISession::GlobalMPISessionImpl( level, abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Constructor for multiple threading support level
GlobalMPISession::GlobalMPISession( MultipleThreadingTag level,
                                    bool abort_on_exception )
    : d_impl( new GlobalMPISession::GlobalMPISessionImpl( level, abort_on_exception ) )
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

// Constructor with command-line inputs for single threading support level
GlobalMPISession::GlobalMPISession( int& argc, char**& argv,
                                    SingleThreadingTag level,
                                    bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( argc, argv, level, abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Constructor with command-line inputs for funneled threading support level
GlobalMPISession::GlobalMPISession( int& argc, char**& argv,
                                    FunneledThreadingTag level,
                                    bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( argc, argv, level, abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Constructor with command-line inputs for serialized threading support level
GlobalMPISession::GlobalMPISession( int& argc, char**& argv,
                                    SerializedThreadingTag level,
                                    bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( argc, argv, level, abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Constructor with command-line inputs for multiple threading support level
GlobalMPISession::GlobalMPISession( int& argc, char**& argv,
                                    MultipleThreadingTag level,
                                    bool abort_on_exception )
  : d_impl( new GlobalMPISession::GlobalMPISessionImpl( argc, argv, level, abort_on_exception ) )
{
  this->initializeRankAndSize();
}

// Destructor
GlobalMPISession::~GlobalMPISession()
{
  s_rank = 0;
  s_size = 1;
}

// Initialize rank and size
void GlobalMPISession::initializeRankAndSize()
{
  static bool rank_size_initialized = false;

  if( !rank_size_initialized )
  {
#ifdef HAVE_FRENSIE_MPI
    boost::mpi::communicator& world = GlobalMPISessionImpl::getWorldComm();
    s_rank = world.rank();
    s_size = world.size();
#else
    s_rank = 0;
    s_size = 1;
#endif
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
 * (see Utility::OpenMPProperties::createTimer).
 */
std::shared_ptr<Timer> GlobalMPISession::createTimer()
{
#ifdef HAVE_FRENSIE_MPI
  if( GlobalMPISession::initialized() && !GlobalMPISession::finalized() )
    return std::shared_ptr<Timer>( new MPITimer() );
#endif

  return OpenMPProperties::createTimer();
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
  return OpenMPProperties::getThreadId() == 0;
#endif
}

// Initialize an output stream
/*! \details If MPI has been configured for use with FRENSIE (HAVE_FRENSIE_MPI
 * is defined) and MPI has been initialized but not finalized, this method
 * can be used to limit stream output to a single process.
 */
void GlobalMPISession::initializeOutputStream(
                                            boost::shared_ptr<std::ostream> os,
                                            const int root_process,
                                            const bool limit_logging_to_root )
{
#ifdef HAVE_FRENSIE_MPI
  if( GlobalMPISession::initialized() && !GlobalMPISession::finalized() )
  {
    if( limit_logging_to_root )
    {
      if( GlobalMPISession::rank() != root_process && os.get() )
      {
        GlobalMPISessionImpl::getOutputStreamCache().cacheStreamBuffer( os );

        os->rdbuf( NULL );
      }
    }
  }
#endif
}

// Restore an output stream
void GlobalMPISession::restoreOutputStream(
                                           boost::shared_ptr<std::ostream> os )
{
  #ifdef HAVE_FRENSIE_MPI
  if( GlobalMPISession::initialized() && !GlobalMPISession::finalized() )
  {
    GlobalMPISessionImpl::getOutputStreamCache().restoreStreamBuffer( os );
  }
#endif
}

// Restore all output streams
void GlobalMPISession::restoreOutputStreams()
{
#ifdef HAVE_FRENSIE_MPI

  if( GlobalMPISession::initialized() && !GlobalMPISession::finalized() )
  {
    GlobalMPISessionImpl::getOutputStreamCache().restoreStreamBuffers();
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
                                      boost::shared_ptr<std::ostream> log_sink,
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
void GlobalMPISession::initializeErrorLog( boost::shared_ptr<std::ostream> log_sink,
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
                                      boost::shared_ptr<std::ostream> log_sink,
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
                                      boost::shared_ptr<std::ostream> log_sink,
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
int GlobalMPISession::rank()
{
  return s_rank;
}

// Return the number of processes (w.r.t. MPI_COMM_WORLD)
int GlobalMPISession::size()
{
  return s_size;
}

// Create an mpi synchronization point
void GlobalMPISession::barrier()
{
#ifdef HAVE_FRENSIE_MPI
  GlobalMPISessionImpl::getWorldComm().barrier();
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
    return boost::mpi::all_reduce( GlobalMPISessionImpl::getWorldComm(),
                                   local_value,
                                   std::plus<int>() );
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
    return boost::mpi::all_reduce( GlobalMPISessionImpl::getWorldComm(),
                                   local_value,
                                   std::plus<double>() );
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

// Gather messages on the desired process
/*! \details If the rank of the process does not equal root, an empty vector
 * will be returned. Otherwise, the vector will store the messages from
 * each process at the index that is equal to the process's rank.
 */
std::vector<std::string> GlobalMPISession::gatherMessages(
                                             const int root,
                                             const std::string& local_message )
{
  return GlobalMPISessionImpl::gatherValues( root, local_message );
}

// Gather bools on the desired process
/*! \details If the rank of the process does not equal root, an empty vector
 * will be returned. Otherwise, the vector will store the bools from each
 * process at the index that is equal to the process's rank.
 */
std::vector<bool> GlobalMPISession::gatherData( const int root,
                                                const bool local_data )
{
  // Note: std::vector<bool> doesn't seem to work with the boost::mpi package.
  //       We will convert the bools to ints, gather the ints, and then convert
  //       back to bools.
  std::vector<int> converted_data =
    GlobalMPISessionImpl::gatherValues( root, (int)local_data );

  std::vector<bool> data( converted_data.size() );

  for( size_t i = 0; i < converted_data.size(); ++i )
    data[i] = (bool)converted_data[i];

  return data;
}

// Gather ints on the desired process
/*! \details If the rank of the process does not equal root, an empty vector
 * will be returned. Otherwise, the vector will store the bools from each
 * process at the index that is equal to the process's rank.
 */
std::vector<int> GlobalMPISession::gatherData( const int root,
                                               const int local_data )
{
  return GlobalMPISessionImpl::gatherValues( root, local_data );
}

// Gather doubles on the desired process
/*! \details If the rank of the process does not equal root, an empty vector
 * will be returned. Otherwise, the vector will store the bools from each
 * process at the index that is equal to the process's rank.
 */
std::vector<double> GlobalMPISession::gatherData( const int root,
                                                  const double local_data )
{
  return GlobalMPISessionImpl::gatherValues( root, local_data );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GlobalMPISession.cpp
//---------------------------------------------------------------------------//
