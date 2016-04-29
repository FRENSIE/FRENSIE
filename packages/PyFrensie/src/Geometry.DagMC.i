//---------------------------------------------------------------------------//
//!
//! \file    Geometry.DagMC.i
//! \author  Alex Robinson
//! \brief   The Geometry.DagMC sub-module
//!
//---------------------------------------------------------------------------//

%define %geometry_dagmc_docstring
"
PyFrensie.Geometry.DagMC is the python interface to the FRENSIE geometry/dagmc
subpackage. 

The purpose of DagMC is to allow a user to query CAD geometry data and to
ray trace on a CAD geometry using python. This can be useful for debugging
geometries.
"
%enddef

%module(package   = "PyFrensie.Geometry.DagMC",
        autodoc   = "1",
        docstring = %geometry_dagmc_docstring) DagMC

%{
// FRENSIE Includes
#include "PyFrensie_ArrayConversionHelpers.hpp"
#include "Geometry_DagMC.hpp"
#include "Utility_ContractException.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_set.i>
%include <std_except.i>

// Import the PyFrensie Teuchos Array conversion helpers
%import "PyFrensie_ArrayConversionHelpers.hpp"

// Import the Geometry.__init__.i file
%import "Geometry.__init__.i"

// Standard exception handling
%include "exception.i"

// Global swig features
%feature("autodoc", "1");

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
  catch( Geometry::InvalidDagMCGeometry& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( Geometry::DagMCGeometryError& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

//---------------------------------------------------------------------------//
// Add support for the DagMC class
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the DagMC class
%feature("docstring")
Geometry::DagMC
"

"

// SWIG will not parse typedefs. Create some typemaps that map the typedefs
// to their true type
%typemap(in) Geometry::ModuleTraits::InternalCellHandle
{
  $1 = PyInt_AsLong($input);
}

%typemap(in) Geometry::ModuleTraits::InternalSurfaceHandle
{
  $1 = PyInt_AsLong($input);
}

%typemap(out) Geometry::ModuleTraits::InternalCellHandle
{
  $result = PyInt_FromLong($1);
}

%typemap(out) Geometry::ModuleTraits::InternalSurfaceHandle
{
  $result = PyInt_AsLong($1);
}

// Ignore the methods that receive or return pointers - new ones will be
// created that receive or return Python objects
%ignore Geometry::DagMC::setInternalRay( const double[3], const double[3], const bool );
%ignore Geometry::DagMC::setInternalRay( const double[3], const double[3], const ModuleTraits::InternalCellHandle, const bool );
%ignore Geometry::DagMC::changeInternalRayDirection( const double[3] );
%ignore Geometry::DagMC::getInternalRayPosition();
%ignore Geometry::DagMC::getInternalRayDirection();

// Add some useful methods to the DagMC class
%extend Geometry::DagMC
{
  // Set the internal ray
  static void setInternalRay( PyObject* py_array_position,
                              PyObject* py_array_direction,
                              const bool cache_start_cell )
  {
    Teuchos::Array<double> position;

    PyFrensie::CopyNumPyToTeuchosWithCheck( py_array_position, position );

    // Make sure the sequence has 3 elements
    if( position.size() != 3 )
    {
      PyErr_SetString( PyExc_TypeError, 
                       "The input position must have 3 elements." );
    }

    Teuchos::Array<double> direction;

    PyFrensie::CopyNumPyToTeuchosWithCheck( py_array_direction, direction );

    // Make sure the sequence has 3 elements
    if( direction.size() != 3 )
    {
      PyErr_SetString( PyExc_TypeError, 
                       "The input direction must have 3 elements." );
    }

    Geometry::DagMC::setInternalRay( position.getRawPtr(),
                                     direction.getRawPtr(),
                                     cache_start_cell );
  }

  // Set the internal ray
  static void setInternalRay(
                           PyObject* py_array_position,
                           PyObject* py_array_direction,
                           const ModuleTraits::InternalCellHandle current_cell,
                           const bool cache_start_cell )
  {
    Teuchos::Array<double> position;

    PyFrensie::CopyNumPyToTeuchosWithCheck( py_array_position, position );

    // Make sure the sequence has 3 elements
    if( position.size() != 3 )
    {
      PyErr_SetString( PyExc_TypeError, 
                       "The input position must have 3 elements." );
    }

    Teuchos::Array<double> direction;

    PyFrensie::CopyNumPyToTeuchosWithCheck( py_array_direction, direction );

    // Make sure the sequence has 3 elements
    if( direction.size() != 3 )
    {
      PyErr_SetString( PyExc_TypeError, 
                       "The input direction must have 3 elements." );
    }

    Geometry::DagMC::setInternalRay( position.getRawPtr(),
                                     direction.getRawPtr(),
                                     current_cell,
                                     cache_start_cell );
  }
  
  // Set the internal ray
  static void setInternalRay( PyObject* py_array_position,
                              PyObject* py_array_direction )
  {
    Geometry::DagMC::setInternalRay( py_array_position,
                                     py_array_direction,
                                     false );
  }

  // Set the internal ray
  static void setInternalRay(
                          PyObject* py_array_position,
                          PyObject* py_array_direction,
                          const ModuleTraits::InternalCellHandle current_cell )
  {
    Geometry::DagMC::setInternalRay( py_array_position,
                                     py_array_direction,
                                     current_cell,
                                     false );
  }                              
                              
  // Get the internal DagMC ray position
  static PyObject* getInternalRayPosition()
  {
    Teuchos::ArrayView<const double> position(
                                Geometry::DagMC::getInternalRayPosition(), 3 );

    return PyFrensie::CopyTeuchosToNumPy( position );
  }

  // Get the internal DagMC ray direction
  static PyObject* getInternalRayDirection()
  {
    Teuchos::ArrayView<const double> direction(
                               Geometry::DagMC::getInternalRayDirection(), 3 );

    return PyFrensie::CopyTeuchosToNumPy( direction );
  }
};

// Include the DagMC class
%include "Geometry_DagMC.hpp"

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// Geometry.DagMC.i
//---------------------------------------------------------------------------//
