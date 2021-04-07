//---------------------------------------------------------------------------//
//!
//! \file   Utility_MOABException.hpp
//! \author Alex Robinson
//! \brief  Exception class for handling MOAB errors.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MOAB_EXCEPTION_HPP
#define UTILITY_MOAB_EXCEPTION_HPP

// Std Lib Includes
#include <stdexcept>

namespace Utility{

//! Exception class to be thrown when a MOAB error is detected
class MOABException : public std::runtime_error
{
public:
  MOABException( const std::string &msg )
    : std::runtime_error( msg )
  { /* ... */ }

  virtual ~MOABException() throw()
  { /* ... */ }
};

} // end Utility namespace

#endif // end UTILITY_EXCEPTION_HPP

//---------------------------------------------------------------------------//
// end Utility_MOABException.hpp
//---------------------------------------------------------------------------//
