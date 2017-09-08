//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardTimer.hpp
//! \author Alex Robinson
//! \brief  The standard timer class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_TIMER_HPP
#define UTILITY_STANDARD_TIMER_HPP

// FRENSIE Includes
#include "Utility_Timer.hpp"

namespace Utility{

//! The standard timer class
template<typename STLCompliantClock>
class StandardTimer : public Timer
{

public:

  //! Constructor
  StandardTimer() noexcept;

  //! Destructor
  ~StandardTimer();

  //! Check if the timer is stopped
  bool isStopped() const override;

  //! Get the elapsed time (in seconds)
  std::chrono::duration<double> elpased() const override;

  //! Start the timer
  void start() override;

  //! Stop the timer
  void stop() override;

  //! Resume the timer
  void resume() override;

private:

  // The start time point
  typename STLCompliantClock::time_point d_start_time_point;

  // The timer duration
  typename STLCompliantClock::duration d_duration;

  // Record when the timer is running
  bool d_is_running;
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_StandardTimer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_STANDARD_TIMER_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardTimer.hpp
//---------------------------------------------------------------------------//
