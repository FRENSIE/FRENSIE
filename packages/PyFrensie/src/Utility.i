//---------------------------------------------------------------------------//
//!
//! \file   Utility.i
//! \author Alex Robinson
//! \brief  The utility module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_docstring
"
PyFrensie.Utility is the python interface to the FRENSIE utilities package
Utility: ...
"
%enddef

%module(package    = "PyFrensie",
        autodoc    = "1",
        docstring  = %utility_docstring) Utility

// Standard exception handling
%include "exception.i"

// Global swig features
%feature("autodoc", "1");

// C++ STL support
%include "stl.i"
%include "std_except.i"

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
  catch( Utility::InvalidDistributionStringRepresentation& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

%{
#include "Utility_RandomNumberGenerator.hpp"
%}

%inline %{
//! Initialize the random number generator
void initFrensiePrng()
{
  // Initilize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}
%}

// Distribution support
%include "Utility_OneDDistribution.i"

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Utility.i
//---------------------------------------------------------------------------//
