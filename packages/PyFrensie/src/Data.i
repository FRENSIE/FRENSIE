//---------------------------------------------------------------------------//
//!
//! \file   Data.i
//! \author Alex Robinson
//! \brief  The data module swig interface file
//!
//---------------------------------------------------------------------------//

%define %data_docstring
"
PyFrensie.Data is the python interface to the FRENSIE data package...
"
%enddef

%module(package   = "PyFrensie",
        autodoc   = "1",
        docstring = %data_docstring) Data

// Standard exception handling
%include "exception.i"

// Global swig features
%feature("autodoc", "1");

// C++ STL support
%include "stl.i"
%include "std_except.i"

%{
// FRENSIE Includes
#include "Utility_ContractException.hpp"
%}

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

// ACE subpackage support
%include "Data_ACE.i"

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Data.i
//---------------------------------------------------------------------------//
