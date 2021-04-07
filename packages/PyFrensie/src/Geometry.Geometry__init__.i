//---------------------------------------------------------------------------//
//!
//! \file   Geometry.__init__.i
//! \author Alex Robinson, Luke Kersting
//! \brief  The geometry module swig interface file
//!
//---------------------------------------------------------------------------//

%define %geometry_docstring
"
PyFrensie.Geometry.Geometry__init__ will be imported directly into the
PyFrensie.Geometry module (see PyFrensie.Geometry.__init__.py)
"
%enddef

%module(package   = "PyFrensie.Geometry",
        autodoc   = "1",
        docstring = %geometry_docstring) Geometry__init__

%pythonbegin
%{
  # With python 2.7.14 and swig version 3.0.10 the default generated import
  # code cannot find the ___init__.so file. Unfortunately the 'moduleimport'
  # option of the %module macro does not seem to work with this version
  # of swig either. To get the import code working we have to manually add
  # the current directory to the system path temporarily.

  import os.path
  import sys
  current_dir,file_name = os.path.split(__file__)
  sys.path.insert(0, current_dir)
%}

%pythoncode
%{
# Remove the local current directory from the sys path (added to help
# import code - see comment above)
sys.path.pop(0)
%}

%{
// Std Lib Includes
#include <sstream>
#include <memory>

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Geometry_PointLocation.hpp"
#include "Geometry_EstimatorType.hpp"
#include "Geometry_Model.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Geometry_AdvancedModel.hpp"
#include "Geometry_Ray.hpp"
#include "Geometry_Navigator.hpp"
#include "Geometry_InfiniteMediumNavigator.hpp"
#include "Geometry_Exceptions.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_DesignByContract.hpp"

using namespace Geometry;
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_set.i>
%include <std_map.i>
%include <std_vector.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Include the serialization helpers for macros
%include "Utility_SerializationHelpers.hpp"

// Include the geometry helpers
%include "Geometry_Helpers.i"

// Include the vector support
%include "PyFrensie_Array.i"

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
  catch( Geometry::InvalidGeometryRepresentation& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
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

// General ignore directives
%ignore *::LengthUnit;
%ignore *::Length;
%ignore *::Ray;
%ignore *::AdvanceCompleteCallback;

// Add a few general templates
%template(DoubleVector) std::vector<double>;

// Add a few general typedefs
typedef unsigned long int uint64_t;
typedef unsigned int uint32_t;

//---------------------------------------------------------------------------//
// Add support for the PointLocation enum
//---------------------------------------------------------------------------//
// Include the PointLocation enum
%include "Geometry_PointLocation.hpp"

//---------------------------------------------------------------------------//
// Add support for the EstimatorType enum
//---------------------------------------------------------------------------//
// Include the EstimatorType enum
%include "Geometry_EstimatorType.hpp"

//---------------------------------------------------------------------------//
// Add support for the ParticleType enum
//---------------------------------------------------------------------------//
// Include the ParticleType enum
%include "Geometry_ParticleType.i"

//---------------------------------------------------------------------------//
// Add support for the Ray class
//---------------------------------------------------------------------------//
// Include the Ray class
%include "Geometry_Ray.hpp"

// Add more detailed docstrings for the Ray class
%feature("docstring")
Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>
"
The Ray stores the state of a ray object (position and direction). A brief
usage tutorial for this class is shown below:

   import PyFrensie.Geometry, numpy

   ray1 = PyFrensie.Geometry.Ray( 0, 0, 0, 0, 0, 1 )
   ray2 = PyFrensie.Geometry.Ray( (0.,0.,0.), (0.,0.,1.) )
   ray3 = PyFrensie.Geometry.Ray( [0.,0.,0.], [0.,0.,1.] )
   ray4 = PyFrensie.Geometry.Ray( numpy.array( [0,0,0], dtype=numpy.dtype('d') ), numpy.array( [0,0,1], dtype=numpy.dtype('d') ) )

   ray1.getPosition()
   ray1.getDirection()

   ray1.advanceHead( 1 )
   ray1.changeDirection( 0, 1, 0 )
   ray1.advanceHead( 1 )
"

%feature("docstring")
Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::UnitAwareRay
"
The Ray object can be constructed with 6 doubles or two sequences (list,
tuple, numpy.array or a combination). Make sure that the direction is valid
(If Design-by-Contract is turned on in FRENSIE it will do the check for you.)
"

%feature("docstring")
Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::getPosition
"
A NumPy array will be returned.
"

%feature("docstring")
Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::getDirection
"
A NumPy array will be returned.
"

// Ignore the toStream method
%ignore Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::toStream;

// Add typemaps for converting Length to and from Python float
%typemap(in) const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length {
  $1 = Geometry::Navigator::Length::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

// Add typemaps for converting Length* to and from Python array
%typemap(in) const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length[3] (std::vector<Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length> temp_position){
  std::vector<double> raw_position = PyFrensie::convertFromPython<std::vector<double> >( $input );

  // Make sure the sequence has 3 elements
  if( raw_position.size() != 3 )
  {
    PyErr_SetString( PyExc_TypeError,
                     "The input position must have 3 elements." );
  }
  else
  {
    temp_position.resize(3);
    temp_position[0] = Geometry::Navigator::Length::from_value( raw_position[0] );
    temp_position[1] = Geometry::Navigator::Length::from_value( raw_position[1] );
    temp_position[2] = Geometry::Navigator::Length::from_value( raw_position[2] );

    $1 = temp_position.data();
  }
}

%typemap(out) const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length* {
  Utility::ArrayView<const double>
    output_view( Utility::reinterpretAsRaw( $1 ), 3 );

  $result = PyFrensie::Details::convertArrayToPython( output_view );

  if( !$result )
    SWIG_fail;
}

%typemap(typecheck, precedence=1050) (const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length[3]) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}


// Add typemaps for converting direction (double*) to and from Python array
%typemap(in) const double direction[3] (std::vector<double> temp_direction){
  temp_direction =
    PyFrensie::convertFromPython<std::vector<double> >( $input );

  // Make sure the sequence has 3 elements
  if( temp_direction.size() != 3 )
  {
    PyErr_SetString( PyExc_TypeError,
                     "The input direction must have 3 elements." );
  }

  $1 = temp_direction.data();
}

%typemap(out) const double* {
  Utility::ArrayView<const double> output_view( $1, 3 );

  $result = PyFrensie::Details::convertArrayToPython( output_view );

  if( !$result )
    SWIG_fail;
}

// Add typecheck out for the Ray class
%typemap(typecheck, precedence=1050) (const double[3]) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}


// Add some useful methods to the Ray class
%extend Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>
{
  // String conversion method
  PyObject* __str__() const
  {
    std::ostringstream oss;

    $self->toStream( oss );

    return PyFrensie::convertToPython( oss.str() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::ostringstream oss;

    $self->toStream( oss );

    return PyFrensie::convertToPython( oss.str() );
  }
};

%template(Ray) Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>;

//---------------------------------------------------------------------------//
// Add support for the Navigator classes
//---------------------------------------------------------------------------//

%include "Geometry_Navigator.i"

//---------------------------------------------------------------------------//
// Add support for the Model class
//---------------------------------------------------------------------------//

%include "Geometry_Model.i"

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Geometry.Geometry__init__.i
//---------------------------------------------------------------------------//
