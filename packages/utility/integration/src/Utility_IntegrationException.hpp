//---------------------------------------------------------------------------//
//!
//! \file   Utility_IntegrationExcpetion.hpp
//! \author Luke Kersting
//! \brief  Exception class for handling Integration errors.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTEGRATION_EXCEPTION_HPP
#define UTILITY_INTEGRATION_EXCEPTION_HPP

// Std Lib Includes
#include <stdexcept>

namespace Utility{

//! Exception class to be thrown when a Integration error is detected
class IntegrationException : public std::runtime_error
{
public:
  IntegrationException( const std::string& msg )
    : std::runtime_error( msg )
  { /* ... */ }

  virtual ~IntegrationException() throw()
  { /* ... */ }
};

} // end Utility namespace

#endif // end UTILITY_INTEGRATION_EXCEPTION_HPP

//---------------------------------------------------------------------------//
// end Utility_IntegrationExcpetion.hpp
//---------------------------------------------------------------------------//
