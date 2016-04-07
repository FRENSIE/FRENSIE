//---------------------------------------------------------------------------//
//!
//! \file   Utility_ActiveCounter_def.hpp
//! \author Alex Robinson
//! \brief  The active counter class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ACTIVE_COUNTER_DEF_HPP
#define UTILITY_ACTIVE_COUNTER_DEF_HPP

namespace Utility{

// Constructor
template<typename T>
ActiveCounter<T>::ActiveCounter()
  : d_count( 0 )
{ /* ... */ }

// Increment the counter
template<typename T>
void ActiveCounter<T>::increment()
{
  ++d_count;
}

// Add to the count
template<typename T>
void ActiveCounter<T>::addToCount( const T value )
{
  d_count += value;
}

// Get the count
template<typename T>
T ActiveCounter<T>::getCount() const
{
  return d_count;
}

} // end Utility namespace

#endif // end UTILITY_ACTIVE_COUNTER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ActiveCounter_def.hpp
//---------------------------------------------------------------------------//
