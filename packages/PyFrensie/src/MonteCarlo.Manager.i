//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.Manager.i
//! \author Luke Kersting
//! \brief  The MonteCarlo.Manager sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_manager_docstring
"
PyFrensie.MonteCarlo.Manager is the python interface to the FRENSIE
monte_carlo/manager subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_manager_docstring) Manager


%{
// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ToStringTraitsDecl.hpp"

// using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

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

// Add support for the ParticleSimulationManager classes
%include "MonteCarlo_ParticleSimulationManager.i"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo.Manager.i
//---------------------------------------------------------------------------//
