//---------------------------------------------------------------------------//
//!
//! \file   Utility_OpenMPProperties.cpp
//! \author Alex Robinson
//! \brief  Global OpenMP session definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_OpenMPProperties.hpp"
#include "Utility_LoggingMacros.hpp"
#include "FRENSIE_config.hpp"

namespace Utility{

#ifdef HAVE_FRENSIE_OPENMP
  
/*! The OpenMP timer
 *
 * This class wraps calls to omp_get_wtime().
 */
class OpenMPTimer : public Timer
{

public:

  //! Constructor
  OpenMPTimer() noexcept
    : d_start_time_point( 0.0 ),
      d_duration( std::chrono::duration<double>::zero() ),
      d_is_running( false )
  { /* ... */ }

  //! Destructor
  ~OpenMPTimer()
  { /* ... */ }

  //! Check if the timer is stopped
  bool isStopped() const override
  { return !d_is_running; }

  //! Get the elapsed time (in seconds)
  std::chrono::duration<double> elapsed() const override
  {
    if( d_is_running )
    {
      return d_duration +
        std::chrono::duration<double>(omp_get_wtime()-d_start_time_point);
    }
    else
      return d_duration;
  }

  //! Start the timer
  void start() override
  {
    if( !d_is_running )
    {
      d_duration = std::chrono::duration<double>::zero();

      d_start_time_point = omp_get_wtime();

      d_is_running = true;
    }
  }

  //! Stop the timer
  void stop() override
  {
    if( d_is_running )
    {
      d_duration += std::chrono::duration<double>(omp_get_wtime()-d_start_time_point);

      d_is_running = false;
    }
  }

  //! Resume the timer
  void resume() override
  {
    if( !d_is_running )
    {
      d_start_time_point = omp_get_wtime();

      d_is_running = true;
    }
  }

private:

  // The start time point
  double d_start_time_point;

  // The timer duration
  std::chrono::duration<double> d_duration;

  // Record when the time is running
  bool d_is_running;
};

#endif // end HAVE_FRENSIE_OPENMP

// Initialize static member data
unsigned OpenMPProperties::threads = 1u;

// Set the number of threads to use in parallel blocks
/*! \details This function will set the number of threads that will usually
 * be used by omp parallel blocks.
 */
void OpenMPProperties::setNumberOfThreads( const unsigned number_of_threads)
{
#ifdef HAVE_FRENSIE_OPENMP
  OpenMPProperties::threads = number_of_threads;
#else
  if( number_of_threads > 1u )
  {
    FRENSIE_LOG_TAGGED_WARNING( "OpenMPProperties",
                                "call to setNumberOfThreads ignored since "
                                "FRENSIE has not been configured to use "
                                "OpenMP (only a single thread can be used)!" );
  }
#endif
}

// Get the number of threads that have been requested in parallel blocks
/*! \details The return value from this function can be used to manually set
 * the number of threads that are active within omp parallel blocks.
 */
unsigned OpenMPProperties::getRequestedNumberOfThreads()
{
  return OpenMPProperties::threads;
}

// Get the default number of threads used in the current parallel scope
/*! \details If OpenMP is not used or if the program execution state is not
 * within an omp parallel block only the master thread will be active
 */
unsigned OpenMPProperties::getNumberOfThreads()
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
unsigned OpenMPProperties::getThreadId()
{
#ifdef HAVE_FRENSIE_OPENMP
  return omp_get_thread_num();
#else
  return 0u;
#endif
}

// Return if OpenMP has been configured for use
bool OpenMPProperties::isOpenMPUsed()
{
#ifdef HAVE_FRENSIE_OPENMP
  return true;
#else
  return false;
#endif
}

// Create a timer
std::shared_ptr<Timer> OpenMPProperties::createTimer()
{
#ifdef HAVE_FRENSIE_OPENMP
  return std::shared_ptr<Timer>( new OpenMPTimer() );
#else
  return Utility::createDefaultTimer();
#endif
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_OpenMPProperties.cpp
//---------------------------------------------------------------------------//
