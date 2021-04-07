//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.Collision.i
//! \author Alex Robinson, Luke Kersting
//! \brief  The MonteCarlo.Collision sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_collision_docstring
"
PyFrensie.MonteCarlo.Collision is the python interface to the FRENSIE
monte_carlo/collision subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_collision_docstring) Collision

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_ScatteringCenterDefinition.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"

#include "Utility_SerializationHelpers.hpp"
#include "Utility_ToStringTraitsDecl.hpp"
#include "Utility_DesignByContract.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// Simulation properties handling
%import(module="PyFrensie.MonteCarlo") MonteCarlo_SimulationProperties.i

// Atom properties handling
%import(module="PyFrensie.Data") Data_AtomProperties.i

// Nuclide properties handling
%import(module="PyFrensie.Data") Data_NuclideProperties.i

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
// ScatteringCenterDefinition support
//---------------------------------------------------------------------------//

%include "MonteCarlo_ScatteringCenterDefinition.i"

//---------------------------------------------------------------------------//
// Material support
//---------------------------------------------------------------------------//
%pythoncode
%{
from PyFrensie.MonteCarlo.Material import *
%}

//---------------------------------------------------------------------------//
// Geometry Model support
//---------------------------------------------------------------------------//
%pythoncode
%{
from PyFrensie.MonteCarlo.GeometryModel import *
%}

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo.Collision.i
//---------------------------------------------------------------------------//
