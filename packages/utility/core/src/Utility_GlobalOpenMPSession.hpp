//---------------------------------------------------------------------------//
//!
//! \file   Utility_GlobalOpenMPSession.hpp
//! \author Alex Robinson
//! \brief  Global OpenMP session details
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GLOBAL_OPEN_MP_SESSION_HPP
#define UTILITY_GLOBAL_OPEN_MP_SESSION_HPP

// Std Lib Includes
#include <time.h>

// FRENSIE Includes
#include "FRENSIE_config.hpp"

namespace Utility{

//! Global OpenMP session details
class GlobalOpenMPSession
{
public:

  //! Set the number of threads to use in parallel blocks
  static void setNumberOfThreads( const unsigned number_of_threads );

  //! Get the number of threads that have been requested in parallel blocks
  static unsigned getRequestedNumberOfThreads();

  //! Get the default number of threads used in the current parallel block
  static unsigned getNumberOfThreads();

  //! Get the thread id within the current scope
  static unsigned getThreadId();

  //! Get the current wall time (s)
  static double getTime();

  //! Return if OpenMP has been configured for use
  static bool isOpenMPUsed();

private:

  // The number of threads to use in parallel blocks
  static unsigned threads;
};

// Get the number of threads that have been requested in parallel blocks
/*! \details The return value from this function can be used to manually set
 * the number of threads that are active within omp parallel blocks.
 */
inline unsigned GlobalOpenMPSession::getRequestedNumberOfThreads()
{
  return GlobalOpenMPSession::threads;
}

// Get the default number of threads used in the current parallel scope
/*! \details If OpenMP is not used or if the program execution state is not
 * within an omp parallel block only the master thread will be active
 */
inline unsigned GlobalOpenMPSession::getNumberOfThreads()
{
#ifdef HAVE_FRENSIE_OPENMP
  return omp_get_num_threads();
#else
  return 1u;
#endif
}

// Get the thread id within the current parallel scope
/*! \details If OpenMP is not used or if the program execution state is not
 *  within an omp parallel block the master thread id (0) will be returned.
 */
inline unsigned GlobalOpenMPSession::getThreadId()
{
#ifdef HAVE_FRENSIE_OPENMP
  return omp_get_thread_num();
#else
  return 0u;
#endif
}

// Get the current wall time (s)
inline double GlobalOpenMPSession::getTime()
{
#ifdef HAVE_FRENSIE_OPENMP
  return omp_get_wtime();
#else
  return clock()/((double)CLOCKS_PER_SEC);
#endif
}

// Return if OpenMP has been configured for use
inline bool GlobalOpenMPSession::isOpenMPUsed()
{
#ifdef HAVE_FRENSIE_OPENMP
  return true;
#else
  return false;
#endif
}

} // end Utility namespace

#endif // end UTILITY_GLOBAL_OPEN_MP_SESSION_HPP

//---------------------------------------------------------------------------//
// end Utility_GlobalOpenMPSession.hpp
//---------------------------------------------------------------------------//
