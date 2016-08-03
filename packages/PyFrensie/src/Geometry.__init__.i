//---------------------------------------------------------------------------//
//!
//! \file   Geometry.__init__.i
//! \author Alex Robinson
//! \brief  The geometry module swig interface file
//!
//---------------------------------------------------------------------------//

%define %geometry_docstring
"
PyFrensie.Geometry is the python interface to the FRENSIE geometry package
"
%enddef

%module(package   = "PyFrensie.Geometry",
        autodoc   = "1",
        docstring = %geometry_docstring) __init__

%include "Geometry_Config.i"

%{
// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "PyFrensie_ArrayConversionHelpers.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_PointLocation.hpp"
#include "Geometry_Ray.hpp"
#include "Utility_ContractException.hpp"
%}

// Import the PyFrensie Teuchos Array conversion helpers
%import "PyFrensie_ArrayConversionHelpers.hpp"

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
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

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

//---------------------------------------------------------------------------//
// Add support for the PointLocation enum
//---------------------------------------------------------------------------//
// Include the PointLocation enum
%include "Geometry_PointLocation.hpp"

//---------------------------------------------------------------------------//
// Add support for the Ray class
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the Ray class
%feature("docstring")
Geometry::Ray
"
The Ray stores the state of a ray object (position and direction). It is
primarily used for ray tracing. A brief usage tutorial for this class is
shown below:

   import PyFrensie.Geometry, numpy

   ray1 = PyFrensie.Geometry.Ray( 0, 0, 0, 0, 0, 1 )
   ray2 = PyFrensie.Geometry.Ray( (0.,0.,0.), (0.,0.,1.) )
   ray3 = PyFrensie.Geometry.Ray( [0.,0.,0.], [0.,0.,1.] )
   ray4 = PyFrensie.Geometry.Ray( numpy.array( [0,0,0], dtype=np.dtype('d') ), numpy.array( [0,0,1], dtype=np.dtype('d') ) )

   ray1.getPosition()
   ray1.getDirection()

   ray1.advanceHead( 1 )
   ray1.changeDirection( 0, 1, 0 )
   ray1.advanceHead( 1 )
"

%feature("docstring")
Geometry::Ray::Ray
"
The Ray object can be constructed with 6 doubles or two sequences (list,
tuple, numpy.array or a combination). Make sure that the direction is valid
(If Design-by-Contract is turned on in FRENSIE it will do the check for you.)
"

%feature("docstring")
Geometry::Ray::getPosition
"
A NumPy array will be returned.
"

%feature("docstring")
Geometry::Ray::getDirection
"
A NumPy array will be returned.
"

// Ignore the extra contructors
%ignore Geometry::Ray::Ray( double[3], double[3], const bool );
%ignore Geometry::Ray::Ray( double[3], double[3] );

// Ignore the print method
%ignore Geometry::Ray::print;

// Add a general typemap that will convert the input position from a Python
// Array object to a double*.
%typemap(in) const double position[3] (Teuchos::Array<double> temp_position){
  PyFrensie::copyNumPyToTeuchosWithCheck( $input, temp_position );

  // Make sure the sequence has 3 elements
  if( temp_position.size() != 3 )
  {
    PyErr_SetString( PyExc_TypeError,
                     "The input position must have 3 elements." );
  }

  $1 = temp_position.getRawPtr();
}

// Add a general typemap that will convert the input direction from a Python
// array object to a double*
%typemap(in) const double direction[3] (Teuchos::Array<double> temp_direction){
  PyFrensie::copyNumPyToTeuchosWithCheck( $input, temp_direction );

  // Make sure the sequence has 3 elements
  if( temp_direction.size() != 3 )
  {
    PyErr_SetString( PyExc_TypeError,
                     "The input direction must have 3 elements." );
  }

  $1 = temp_direction.getRawPtr();
}

// The typecheck precedence, which is used by SWIG to determine which
// overloaded method should be called, should be set to
// SWIG_TYPECHECK_DOUBLE_ARRAY (1050) for the C double arrays. You will get a
// Python error when calling the overloaded method in Python without this
// typecheck
%typemap(typecheck, precedence=1050) (const double[3]) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// Add a general typemap that will convert the output position or direction
// from a double* to a Python array object
%typemap(out) const double* {
  Teuchos::ArrayView<const double> output_view( $1, 3 );

  $result = PyFrensie::copyTeuchosToNumPy( output_view );
}

// Add some useful methods to the Ray class
%extend Geometry::Ray
{
  // String conversion methd
  PyObject* __str__() const
  {
    std::ostringstream oss;

    $self->print( oss );

    return PyString_FromString( oss.str().c_str() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::ostringstream oss;

    $self->print( oss );

    return PyString_FromString( oss.str().c_str() );
  }
};

// Include the Ray class
%include "Geometry_Ray.hpp"

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Geometry.__init__.i
//---------------------------------------------------------------------------//
