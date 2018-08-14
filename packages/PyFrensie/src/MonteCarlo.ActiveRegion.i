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
%include <std_string.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// Import the UnivariateDistribution handling
%import "Utility.UnivariateDistribution.i"

// Import the BivariateDistribution handling
%import "Utility.BivariateDistribution.i"

// Import the Coordinate handling
%import "Utility.Coordinate.i"

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

// Helper macro for the pre template setup
%define %pre_template_setup_helper( NAME, RENAME )
  %inline %{ typedef MonteCarlo::NAME RENAME; %}
  %shared_ptr( MonteCarlo::NAME )
%enddef

// Helper macro for the post template setup
%define %post_template_setup_helper( NAME, RENAME )
  %template( RENAME ) MonteCarlo::NAME;
%enddef

%import(module="PyFrensie.MonteCarlo") MonteCarlo_ParticleState.i

// Add support for the PhaseSpaceDimension classes
%include "MonteCarlo_PhaseSpaceDimension.i"

// Add support for the ParticleDistribution classes
%include "MonteCarlo_ParticleDistribution.i"

// Add support for the ParticleResponse classes
%include "MonteCarlo_ParticleResponse.i"

// Add support for the ParticleSource classes
%include "MonteCarlo_ParticleSource.i"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo.ActiveRegion.i
//---------------------------------------------------------------------------//
