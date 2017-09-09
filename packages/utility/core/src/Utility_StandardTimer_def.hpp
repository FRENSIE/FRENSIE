//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardTimer_def.hpp
//! \author Alex Robinson
//! \brief  The standard timer class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_TIMER_DEF_HPP
#define UTILITY_STANDARD_TIMER_DEF_HPP

namespace Utility{

// Constructor
template<typename STLCompliantClock>
StandardTimer<STLCompliantClock>::StandardTimer()
  : d_start_time_point( STLCompliantClock::now() ),
    d_duration( STLCompliantClock::duration::zero() ),
    d_is_running( false )
{ /* ... */ }

// Destructor
template<typename STLCompliantClock>
StandardTimer<STLCompliantClock>::~StandardTimer()
{ /* ... */ }

// Check if the timer is stopped
template<typename STLCompliantClock>
bool StandardTimer<STLCompliantClock>::isStopped() const
{
  return !d_is_running;
}

// Get the elapsed time (in seconds)
template<typename STLCompliantClock>
std::chrono::duration<double> StandardTimer<STLCompliantClock>::elapsed() const
{
  if( d_is_running )
  {
    return d_duration + typename STLCompliantClock::duration(STLCompliantClock::now() - d_start_time_point);
  }
  else
    return d_duration;
}

// Start the timer
template<typename STLCompliantClock>
void StandardTimer<STLCompliantClock>::start()
{
  if( !d_is_running )
  {
    d_duration = STLCompliantClock::duration::zero();
    
    d_start_time_point = STLCompliantClock::now();
    
    d_is_running = true;
  }
}

// Stop the timer
template<typename STLCompliantClock>
void StandardTimer<STLCompliantClock>::stop()
{
  if( d_is_running )
  {
    d_duration += typename STLCompliantClock::duration(STLCompliantClock::now()-d_start_time_point);

    d_is_running = false;
  }
}

// Resume the timer
template<typename STLCompliantClock>
void StandardTimer<STLCompliantClock>::resume()
{
  if( !d_is_running )
  {
    d_start_time_point = STLCompliantClock::now();
    
    d_is_running = true;
  }
}
  
} // end Utility namespace

#endif // end UTILITY_STANDARD_TIMER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardTimer_def.hpp
//---------------------------------------------------------------------------//
