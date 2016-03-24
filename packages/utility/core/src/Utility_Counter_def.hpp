//---------------------------------------------------------------------------//
//!
//! \file   Utility_Counter_def.hpp
//! \author Alex Robinson
//! \brief  The counter base class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COUNTER_DEF_HPP
#define UTILITY_COUNTER_DEF_HPP

namespace Utility{

// Pre-increment the counter
template<typename T>
Counter<T>& Counter<T>::operator++()
{
  this->increment();

  return *this;
}

// Add to the count
template<typename T>
Counter<T>& Counter<T>::operator+=( const T value )
{
  this->addToCount( value );

  return *this;
}

// Add to the count
template<typename T>
void Counter<T>::addToCount( const Counter<T>& other_counter )
{
  this->addToCount( other_counter.getCount() );
}

// Add to the count
template<typename T>
Counter<T>& Counter<T>::operator+=( const Counter<T>& other_counter )
{
  this->addToCount( other_counter.getCount() );

  return *this;
}

// Conversion operator
template<typename T>
Counter<T>::operator T() const
{
  return this->getCount();
}

} // end Utility namespace

#endif // end UTILITY_COUNTER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Counter_def.hpp
//---------------------------------------------------------------------------//
