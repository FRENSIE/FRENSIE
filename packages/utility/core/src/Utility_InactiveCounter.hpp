//---------------------------------------------------------------------------//
//!
//! \file   Utility_InactiveCounter.hpp
//! \author Alex Robinson
//! \brief  The inactive counter class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INACTIVE_COUNTER_HPP
#define UTILITY_INACTIVE_COUNTER_HPP

// FRENSIE Includes
#include "Utility_Counter.hpp"

namespace Utility{

template<typename T>
class InactiveCounter : public Counter<T>
{

public:

  //! Constructor
  InactiveCounter();

  //! Destructor
  ~InactiveCounter()
  { /* ... */ }

  //! Increment the counter
  void increment();

  //! Add to the count
  void addToCount( const T value );

  //! Get the count
  T getCount() const;
};

} // end Utility

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_InactiveCounter_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INACTIVE_COUNTER_HPP

//---------------------------------------------------------------------------//
// end Utility_InactiveCounter.hpp
//---------------------------------------------------------------------------//
