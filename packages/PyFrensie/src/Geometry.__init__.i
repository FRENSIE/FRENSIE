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
%ignore Geometry::Ray::Ray( const double[3], const double[3] );

// Ignore the pointer returns
%ignore Geometry::Ray::getPosition();
%ignore Geometry::Ray::getDirection();

// Ignore the change direction overload
%ignore Geometry::Ray::changeDirection( const double[3] );

// Ignore the print method
%ignore Geometry::Ray::print;

// Add some useful methods to the Ray class
%extend Geometry::Ray
{
  // A a new list/sequence/numpy array constructor
  Ray( PyObject* position_py_obj, PyObject* direction_py_obj )
  {
    Teuchos::Array<double> position;

    PyFrensie::copyNumPyToTeuchosWithCheck( position_py_obj, position );

    // Make sure the sequence has 3 elements
    if( position.size() != 3 )
    {
      PyErr_SetString( PyExc_TypeError, 
                       "The input position must have 3 elements." );
    }
    
    Teuchos::Array<double> direction;

    PyFrensie::copyNumPyToTeuchosWithCheck( direction_py_obj, direction );
    
    // Make sure the sequence has 3 elements
    if( direction.size() != 3 )
    {
      PyErr_SetString( PyExc_TypeError, 
                       "The input direction must have 3 elements." );
    }

    return new Geometry::Ray( position.getRawPtr(), direction.getRawPtr() );
  }

  // Return the position of the ray
  PyObject* getPosition() const
  {
    Teuchos::ArrayView<const double> position( $self->getPosition(), 3 );
    
    return PyFrensie::copyTeuchosToNumPy( position );
  }

  // Return the direction of the ray
  PyObject* getDirection() const
  {
    Teuchos::ArrayView<const double> direction( $self->getDirection(), 3 );
    
    return PyFrensie::copyTeuchosToNumPy( direction );
  }

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
