//---------------------------------------------------------------------------//
//!
//! \file   Utility_OpenMPProperties.hpp
//! \author Alex Robinson
//! \brief  Global OpenMP session details
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_OPEN_MP_PROPERTIES_HPP
#define UTILITY_OPEN_MP_PROPERTIES_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_Timer.hpp"

namespace Utility{

//! Global OpenMP session details
class OpenMPProperties
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

  //! Create a timer using the OpenMP interface
  static std::shared_ptr<Timer> createTimer();

  //! Return if OpenMP has been configured for use
  static bool isOpenMPUsed();

private:

  // The number of threads to use in parallel blocks
  static unsigned threads;
};

} // end Utility namespace

#endif // end UTILITY_OPEN_MP_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Utility_OpenMPProperties.hpp
//---------------------------------------------------------------------------//
