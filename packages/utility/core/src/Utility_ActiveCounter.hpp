//---------------------------------------------------------------------------//
//!
//! \file   Utility_ActiveCounter.hpp
//! \author Alex Robinson
//! \brief  The active counter class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ACTIVE_COUNTER_HPP
#define UTILITY_ACTIVE_COUNTER_HPP

// FRENSIE Includes
#include "Utility_Counter.hpp"

namespace Utility{

template<typename T>
class ActiveCounter : public Counter<T>
{

public:

  //! Constructor
  ActiveCounter();

  //! Destructor
  ~ActiveCounter()
  { /* ... */ }

  //! Increment the counter
  void increment();

  //! Add to the count
  void addToCount( const T value );

  //! Get the count
  T getCount() const;

private:

  // The count
  T d_count;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_ActiveCounter_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_ACTIVE_COUNTER_HPP

//---------------------------------------------------------------------------//
// end Utility_ActiveCounter.hpp
//---------------------------------------------------------------------------//
