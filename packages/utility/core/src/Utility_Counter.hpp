//---------------------------------------------------------------------------//
//!
//! \file   Utility_Counter.hpp
//! \author Alex Robinson
//! \brief  The counter class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COUNTER_HPP
#define UTILITY_COUNTER_HPP

namespace Utility{

//! The counter class
template<typename T>
class Counter
{

public:

  //! Constructor
  Counter()
  { /* ... */ }

  //! Destructor
  virtual ~Counter()
  { /* ... */ }

  //! Increment the counter
  virtual void increment() = 0;

  //! Pre-increment the counter
  Counter<T>& operator++();

  //! Add to the count
  virtual void addToCount( const T value ) = 0;

  //! Add to the count
  Counter<T>& operator+=( const T value );

  //! Add to the count
  void addToCount( const Counter<T>& other_counter );

  //! Add to the count
  Counter<T>& operator+=( const Counter<T>& other_counter );

  //! Get the count
  virtual T getCount() const = 0;

  //! Conversion operator
  operator T() const;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_Counter_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_COUNTER_HPP

//---------------------------------------------------------------------------//
// end Utility_Counter.hpp
//---------------------------------------------------------------------------//
