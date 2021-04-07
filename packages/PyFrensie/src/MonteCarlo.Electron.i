//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.Electron.i
//! \author Luke Kersting
//! \brief  The MonteCarlo.Electron sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_electron_docstring
"
PyFrensie.MonteCarlo.Electron is the python interface to the FRENSIE
monte_carlo/collision/electron subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_electron_docstring) Electron

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <std_shared_ptr.i>

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

// Global swig features
%feature("autodoc", "1");

//---------------------------------------------------------------------------//
// Electron Scattering Distribution support
//---------------------------------------------------------------------------//

%include MonteCarlo_ElectronScatteringDistribution.i

//---------------------------------------------------------------------------//
// Electroatomic Reaction support
//---------------------------------------------------------------------------//

%include MonteCarlo_ElectroatomicReaction.i

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo.Electron.i
//---------------------------------------------------------------------------//
