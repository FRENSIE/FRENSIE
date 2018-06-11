//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.ActiveRegion.i
//! \author Luke Kersting
//! \brief  The MonteCarlo.ActiveRegion sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_active_region_docstring
"
PyFrensie.MonteCarlo.ActiveRegion is the python interface to the FRENSIE
monte_carlo/active_region subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_active_region_docstring) ActiveRegion

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

// Global swig features
%feature("autodoc", "1");

// PhaseSpaceDimension support
%pythoncode
%{
from PyFrensie.MonteCarlo.PhaseSpaceDimension import *
%}

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo.ActiveRegion.i
//---------------------------------------------------------------------------//
