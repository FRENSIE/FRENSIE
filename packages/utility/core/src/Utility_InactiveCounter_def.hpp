//---------------------------------------------------------------------------//
//!
//! \file   Utility_InactiveCounter.hpp
//! \author Alex Robinson
//! \brief  The inactive counter class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INACTIVE_COUNTER_DEF_HPP
#define UTILITY_INACTIVE_COUNTER_DEF_HPP

namespace Utility{

// Constructor
template<typename T>
InactiveCounter<T>::InactiveCounter()
  : Counter<T>()
{ /* ... */ }

// Increment the counter
template<typename T>
void InactiveCounter<T>::increment()
{ /* ... */ }

// Add to the count
template<typename T>
void InactiveCounter<T>::addToCount( const T value )
{ /* ... */ }

// Get the count
template<typename T>
T InactiveCounter<T>::getCount() const
{
  return 0;
}

} // end Utility namespace

#endif // end UTILITY_INACTIVE_COUNTER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InactiveCounter_def.hpp
//---------------------------------------------------------------------------//
