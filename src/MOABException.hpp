//---------------------------------------------------------------------------//
//!
//! \file   MOABException.hpp
//! \author Alex Robinson
//! \brief  Exception class for handling MOAB errors.
//!
//---------------------------------------------------------------------------//

#ifndef MOAB_EXCEPTION_HPP
#define MOAB_EXCEPTION_HPP

// Std Lib Includes
#include <stdexcept>

namespace FACEMC{

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

} // end FACEMC namespace

#endif // end MOAB_EXCEPTION_HPP

//---------------------------------------------------------------------------//
// end MOABException.hpp
//---------------------------------------------------------------------------//
