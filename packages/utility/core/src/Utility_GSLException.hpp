//---------------------------------------------------------------------------//
//!
//! \file   Utility_GSLExcpetion.hpp
//! \author Alex Robinson
//! \brief  Exception class for handling GSL errors.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GSL_EXCEPTION_HPP
#define UTILITY_GSL_EXCEPTION_HPP

// Std Lib Includes
#include <stdexcept>

namespace Utility{

//! Exception class to be thrown when a GSL error is detected
class GSLException : public std::runtime_error
{
public:
  GSLException( const std::string& msg )
    : std::runtime_error( msg )
  { /* ... */ }

  virtual ~GSLException() throw()
  { /* ... */ }
};

} // end Utility namespace

#endif // end UTILITY_GSL_EXCEPTION_HPP

//---------------------------------------------------------------------------//
// end Utility_GSLException.hpp
//---------------------------------------------------------------------------//
