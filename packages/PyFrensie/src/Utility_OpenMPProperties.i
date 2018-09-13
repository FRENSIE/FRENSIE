//---------------------------------------------------------------------------//
//!
//! \file   Utility_OpenMPProperties.i
//! \author Luke Kersting
//! \brief  The OpenMPProperties class interface file
//!
//---------------------------------------------------------------------------//

%{
// Std Includes
#include <fstream>

// FRENSIE Includes
#include "Utility_OpenMPProperties.hpp"

using namespace Utility;
%}

// C++ STL support
%include <stl.i>
// %include <std_string.i>
// %include <std_vector.i>
%include <std_except.i>
// %include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Standard exception handling
%include "exception.i"

// General exception handling
%exception
{
  try{
    $action;
    if( PyErr_Occurred() )
      SWIG_fail;
  }
  catch( Utility::ContractException& e )
  {
    SWIG_exception( SWIG_ValueError, e.what() );
  }
  catch( std::runtime_error& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

// ---------------------------------------------------------------------------//
// Add support for the OpenMPProperties
// ---------------------------------------------------------------------------//

// Wrap OpenMPProperties
%include "Utility_OpenMPProperties.hpp"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo_OpenMPProperties.i
//---------------------------------------------------------------------------//
