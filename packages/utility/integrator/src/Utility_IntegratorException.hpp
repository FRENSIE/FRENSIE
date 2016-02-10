//---------------------------------------------------------------------------//
//!
//! \file   Utility_IntegratorExcpetion.hpp
//! \author Luke Kersting
//! \brief  Exception class for handling Integrator errors.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTEGRATOR_EXCEPTION_HPP
#define UTILITY_INTEGRATOR_EXCEPTION_HPP

// Std Lib Includes
#include <stdexcept>

namespace Utility{

//! Exception class to be thrown when a Integrator error is detected
class IntegratorException : public std::runtime_error
{
public:
  IntegratorException( const std::string& msg )
    : std::runtime_error( msg )
  { /* ... */ }

  virtual ~IntegratorException() throw()
  { /* ... */ }
};

} // end Utility namespace

#endif // end UTILITY_INTEGRATOR_EXCEPTION_HPP

//---------------------------------------------------------------------------//
// end Utility_IntegratorExcpetion.hpp
//---------------------------------------------------------------------------//
