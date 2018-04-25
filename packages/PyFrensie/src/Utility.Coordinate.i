//---------------------------------------------------------------------------//
//!
//! \file   Utility.Coordinate.i
//! \author Luke Kersting
//! \brief  The Utility.Coordinate sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_coordinate_docstring
"
PyFrensie.Utility.Coordinate is the python interface to the FRENSIE utility/coordinate
subpackage.

The purpose of the Coordinate package is to provide a variety of spatial coordinate
conversion policies that can be used in FRENSIE and PyFrensie.
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_coordinate_docstring) Coordinate

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"

#include "Utility_SpatialCoordinateSystemType.hpp"
#include "Utility_SpatialCoordinateSystemTraitsDecl.hpp"
#include "Utility_SpatialCoordinateSystemTraits.hpp"
#include "Utility_SpatialCoordinateConversionPolicy.hpp"

#include "Utility_DirectionalCoordinateSystemType.hpp"
#include "Utility_DirectionalCoordinateSystemTraitsDecl.hpp"
#include "Utility_DirectionalCoordinateSystemTraits.hpp"
#include "Utility_DirectionalCoordinateConversionPolicy.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

// Standard exception handling
%include "exception.i"

// Global swig features
%feature("autodoc", "1");

// C++ STL support
%include "stl.i"
%include "std_except.i"

// General ignore directives
%ignore *::operator<<;

// Include the coordinate helpers
%include "Utility_CoordinateHelpers.i"

// Include the spatial coordinate system type and traits
%include "Utility_SpatialCoordinateSystemType.hpp"
%include "Utility_SpatialCoordinateSystemTraitsDecl.hpp"
%include "Utility_SpatialCoordinateSystemTraits.hpp"

// Include the directional coordinate system type and traits
%include "Utility_DirectionalCoordinateSystemType.hpp"
%include "Utility_DirectionalCoordinateSystemTraitsDecl.hpp"
%include "Utility_DirectionalCoordinateSystemTraits.hpp"

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

//---------------------------------------------------------------------------//
// Add support for the SpatialCoordinateSystemPolicy
//---------------------------------------------------------------------------//
// Import the SpatialCoordinateSystemPolicy
%include "Utility_SpatialCoordinateConversionPolicy.hpp"

%basic_spatial_coordinate_interface_setup( SpatialCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// Add support for the DirectionalCoordinateSystemPolicy
//---------------------------------------------------------------------------//
// Import the DirectionalCoordinateSystemPolicy
%include "Utility_DirectionalCoordinateConversionPolicy.hpp"


%basic_directional_coordinate_interface_setup( DirectionalCoordinateConversionPolicy )


// Support for specific coordinate types
%include "Utility_CartesianCoordinate.i"
%include "Utility_SphericalCoordinate.i"
%include "Utility_CylindricalCoordinate.i"

//---------------------------------------------------------------------------//
// end Utility.Coordinate.i
//---------------------------------------------------------------------------//e
