//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.Event.i
//! \author Luke Kersting
//! \brief  The MonteCarlo.Event sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_event_docstring
"
PyFrensie.MonteCarlo.Event is the python interface to the FRENSIE
monte_carlo/event subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_event_docstring) Event


%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

// using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <typemaps.i>

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

// Add ObserverPhaseSpaceDimensionDiscretization support
%include "MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.i"

// Add Estimator support
%include "MonteCarlo_Estimator.i"

// Add Particle Tracker support
%include "MonteCarlo_ParticleTracker.i"

// Add EventHandler support
%include "MonteCarlo_EventHandler.i"

 // Add CollisionForcer support
%include "MonteCarlo_CollisionForcer.i"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo.Event.i
//---------------------------------------------------------------------------//
