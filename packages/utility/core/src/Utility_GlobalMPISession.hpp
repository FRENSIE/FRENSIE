//---------------------------------------------------------------------------//
//!
//! \file   Utility_GlobalMPISession.hpp
//! \author Alex Robinson
//! \brief  The global mpi session class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GLOBAL_MPI_SESSION_HPP
#define UTILITY_GLOBAL_MPI_SESSION_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

// FRENSIE Includes
#include "Utility_Timer.hpp"
#include "Utility_Vector.hpp"

/*! \defgroup mpi MPI
 *
 * A custom MPI interface has been created using insights gained by using
 * both the boost::mpi library and the Teuchos::Comm library. Like the
 * Teuchos::Comm library, the FRENSIE MPI interface can be used whether or not
 * the external MPI libraries have been built (without having to enclose
 * interface code in preprocessor logic blocks). To accomplish this behavior
 * the FRENSIE MPI interface simply provides wrappers around various
 * boost::mpi methods and classes.
 * \ingroup traits
 */

namespace Utility{

/*! The global mpi session class
 *
 * This class is based off of the Teuchos::GlobalMPISession class and the
 * boost::mpi::environment class.
 * \ingroup mpi
 */
class GlobalMPISession : private boost::noncopyable
{

public:

  //! The mpi single thread support level tag
  struct SingleThreadingTag
  {
    operator int() const;
  };

  //! The mpi single thread support level tag object
  static SingleThreadingTag SingleThreading;

  //! The mpi funneled thread support level tag
  struct FunneledThreadingTag
  {
    operator int() const;
  };

  //! The mpi funneled thread support level tag object
  static FunneledThreadingTag FunneledThreading;

  //! The mpi serialized thread support level tag
  struct SerializedThreadingTag
  {
    operator int() const;
  };

  //! The mpi serialized thread support level tag object
  static SerializedThreadingTag SerializedThreading;

  //! The mpi multiple threading support level tag
  struct MultipleThreadingTag
  {
    operator int() const;
  };

  //! The mpi multiple threading support level tag object
  static MultipleThreadingTag MultipleThreading;

  //! Default constructor
  explicit GlobalMPISession( bool abort_on_exception = true );

  //! Constructor for single threading support level
  explicit GlobalMPISession( SingleThreadingTag level,
                             bool abort_on_exception = true );

  //! Constructor for funneled threading support level
  explicit GlobalMPISession( FunneledThreadingTag level,
                             bool abort_on_exception = true );

  //! Constructor for serialized threading support level
  explicit GlobalMPISession( SerializedThreadingTag level,
                             bool abort_on_exception = true );

  //! Constructor for multiple threading support level
  explicit GlobalMPISession( MultipleThreadingTag level,
                             bool abort_on_exception = true );

  //! Constructor with command-line inputs
  GlobalMPISession( int& argc, char**& argv, bool abort_on_exception = true );

  //! Constructor with command-line inputs for single threading support level
  GlobalMPISession( int& argc, char**& argv,
                    SingleThreadingTag level,
                    bool abort_on_exception = true );

  //! Constructor with command-line inputs for funneled threading support level
  GlobalMPISession( int& argc, char**& argv,
                    FunneledThreadingTag level,
                    bool abort_on_exception = true );

  //! Constructor with command-line inputs for serialized threading support level
  GlobalMPISession( int& argc, char**& argv,
                    SerializedThreadingTag level,
                    bool abort_on_exception = true );

  //! Constructor with command-line inputs for multiple threading support level
  GlobalMPISession( int& argc, char**& argv,
                    MultipleThreadingTag level,
                    bool abort_on_exception = true );

  //! Destructor
  ~GlobalMPISession();

  //! Initialize logs
  void initializeLogs( boost::shared_ptr<std::ostream> log_sink,
                       const int root_process = 0,
                       const bool limit_logging_to_root = false,
                       const bool synchronous_logging = true );

  //! Initialize error log
  void initializeErrorLog( boost::shared_ptr<std::ostream> log_sink,
                           const int root_process = 0,
                           const bool limit_logging_to_root = false,
                           const bool synchronous_logging = true );

  //! Initialize warning log
  void initializeWarningLog( boost::shared_ptr<std::ostream> log_sink,
                             const int root_process = 0,
                             const bool limit_logging_to_root = false,
                             const bool synchronous_logging = true );

  //! Initialize notification log
  void initializeNotificationLog( boost::shared_ptr<std::ostream> log_sink,
                                  const int root_process = 0,
                                  const bool limit_logging_to_root = false,
                                  const bool synchronous_logging = true );

  //! Initialize an output stream
  static void initializeOutputStream( boost::shared_ptr<std::ostream> os,
                                      const int root_process = 0,
                                      const bool limit_logging_to_root = false );

  //! Restore an output stream
  static void restoreOutputStream( boost::shared_ptr<std::ostream> os );

  //! Restore all output streams
  static void restoreOutputStreams();

  //! Check if MPI has been configured for use
  static bool isMPIUsed();

  //! Create a timer
  static std::shared_ptr<Timer> createTimer();

  //! Abort all MPI processes
  static void abort( int error_code );

  //! Check if mpi has been initialized
  static bool initialized();

  //! Check if MPI has been finalized
  static bool finalized();

  //! Get the maximum tag value
  static int maxTag();

  //! Get the maximum tag value (mirror boost::mpi interface)
  static int max_tag();

  //! Get the tag value used for collective operations
  static int collectivesTag();

  //! Get the tag value used for collective operations (mirror boost::mpi interface)
  static int collectives_tag();

  //! Get the name of the calling processor
  static std::string processorName();

  //! Get the name of the calling processor (mirror boost::mpi interface)
  static std::string processor_name();

  //! Get the current level of thread support
  static int threadLevel();

  //! Get the current level of thread support (mirror boost::mpi interface)
  static int thread_level();

  //! Check if the calling process is the main thread
  static bool isMainThread();

  //! Check if the calling process is the main thread (mirror boost::mpi interface)
  static bool is_main_thread();

  //! Return the rank of the calling process (w.r.t. MPI_COMM_WORLD)
  static int rank();

  //! Return the number of processes (w.r.t. MPI_COMM_WORLD)
  static int size();

  //! Create an mpi synchronization point
  static void barrier();

  //! Sum a set of integers across all processes
  static int sum( const int local_value );

  //! Sum a set of doubles across all processes
  static double sum( const double local_value );

  //! Check if a boolean is true on all processes
  static bool isGloballyTrue( const bool local_boolean );

  //! Check if a boolean is false on all processes
  static bool isGloballyFalse( const bool local_boolean );

  //! Gather messages on the desired process
  static std::vector<std::string> gatherMessages( const int root, const std::string& local_message );

  //! Gather bools on the desired process
  static std::vector<bool> gatherData( const int root, const bool local_data );

  //! Gather ints on the desired process
  static std::vector<int> gatherData( const int root, const int local_data );

  //! Gather doubles on the desired process
  static std::vector<double> gatherData( const int root, const double local_data );

private:

  // Initialize rank and size
  static void initializeRankAndSize();

  // The global mpi session implementation
  class GlobalMPISessionImpl;
  std::unique_ptr<GlobalMPISessionImpl> d_impl;

  // The MPI_COMM_WORLD rank
  static int s_rank;

  // The MPI_COMM_WORLD size
  static int s_size;
};

} // end Utility namespace

#endif // end UTILITY_GLOBAL_MPI_SESSION_HPP

//---------------------------------------------------------------------------//
// end Utility_GlobalMPISession.hpp
//---------------------------------------------------------------------------//
