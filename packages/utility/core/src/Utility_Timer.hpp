//---------------------------------------------------------------------------//
//!
//! \file   Utility_Timer.hpp
//! \author Alex Robinson
//! \brief  The timer base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TIMER_HPP
#define UTILITY_TIMER_HPP

// Std Lib Includes
#include <chrono>
#include <memory>

namespace Utility{

//! The timer base class
class Timer
{

public:

  //! Constructor
  Timer() noexcept
  { /* ... */ }

  //! Destructor
  virtual ~Timer()
  { /* ... */ }

  //! Check if the timer is stopped
  virtual bool isStopped() const = 0;

  //! Get the elapsed time (in seconds)
  virtual std::chrono::duration<double> elapsed() const = 0;

  //! Start the timer
  virtual void start() = 0;

  //! Stop the timer
  virtual void stop() = 0;

  //! Resume the timer
  virtual void resume() = 0;
};

//! Create a default timer
std::shared_ptr<Timer> createDefaultTimer();
  
} // end Utility namespace

#endif // end UTILITY_TIMER_HPP

//---------------------------------------------------------------------------//
// end Utility_Timer.hpp
//---------------------------------------------------------------------------//
