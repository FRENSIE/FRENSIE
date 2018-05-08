//---------------------------------------------------------------------------//
//!
//! \file   Utility.Prng.i
//! \author Alex Robinson
//! \brief  The Utility.Prng sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_prng_docstring
"
PyFrensie.Utility.Prng is the python inteface to the FRENSIE utility/prng
subpackage.

The purpose of Prng is to provide a variety of pseudo-random number generators
that can be used in FRENSIE and PyFrensie. All FRENSIE packages interact with
the random number generators through the Utility::RandomNumberGenerator class.
In PyFrensie the Prng.RandomNumberGenerator proxy class is used. Before using
classes in other PyFrensie modules (e.g. the distribution classes in
PyFrensie.Utility.Distribution), make sure to initialize the
Prng.RandomNumberGenerator proxy class.
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_prng_docstring) Prng

%{
// Std Lib Includes
#include <sstream>

#define NO_IMPORT_ARRAY
#include "numpy_include.h"

// Frensie Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Utility_RandomNumberGenerator.hpp"
%}

// Include the vector support
%include "PyFrensie_Array.i"

// Include macros to find initialized numpy
%include "numpy.i"

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
// Add support for the 64bit-LCG
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the 64bit-LCG
%feature("docstring")
Utility::LinearCongruentialGenerator
"
The LinearCongruentialGenerator can be used to generate a uniform deviate
in [0,1). This generator uses a modulus of 2^64. Unlike other 64-bit LCGs, this
generator is designed for use in Monte Carlo particle simulations, which is
why the methods 'changeHistory' and 'nextHistory' are provided. These methods
advance the stream state using a hidden stride and can be used to create
reproducible streams for every history number. A brief usage tutorial for
this class is shown below:

  import PyFrensie.Utility.Prng

  generator = PyFrensie.Utility.Prng.LinearCongruentialGenerator()
  generator.getRandomNumber()
  generator.getGeneratorState()

  generator.nextHistory()
  generator.getRandomNumber()
  generator.getGeneratorState()

  generator.changeHistory( 10 )
  generator.getRandomNumber()
  generator.getGeneratorState()
"

// Add some useful methods to the 64bit-LCG
%extend Utility::LinearCongruentialGenerator
{
  // String conversion method
  PyObject* __str__() const
  {
    std::ostringstream oss;
    oss << "stream state: " << $self->getGeneratorState();

    return PyString_FromString( oss.str().c_str() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::ostringstream oss;
    oss << "LinearCongruentialGenerator(stream state: "
        << $self->getGeneratorState() << ")";

    return PyString_FromString( oss.str().c_str() );
  }
};

// Include LinearCongruentialGenerator
%include "Utility_LinearCongruentialGenerator.hpp"

//---------------------------------------------------------------------------//
// Add support for the RandomNumberGenerator interface
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the RandomNumberGenerator interface
%feature("docstring")
Utility::RandomNumberGenerator
"
All FRENSIE packages interact with the random number generators through the
Utility::RandomNumberGenerator class. In PyFrensie the this proxy class is
used. Before using classes in other PyFrensie modules (e.g. the distribution
classes in PyFrensie.Utility.Distribution), make sure to initialize the
Prng.RandomNumberGenerator proxy class (by calling 'createStreams'). It is
usually not necessary to interact with this class directly. However, it can
be useful to interact with it when debugging or exploring sampling methods by
using the setFakeStream method. The setFakeStream method allows one to specify
a fake random number stream that will be used instead of the stream from the
underlying random number generator. Make sure to call the 'unsetFakeStream'
method after completing the task that needed the fake stream. Note that a
numpy array should be used to specify the fake stream.
"

%feature("docstring")
Utility::RandomNumberGenerator::hasStreams
"
This method can be used to check if the random number streams have been
created (from a call to 'createStreams()').
"

%feature("docstring")
Utility::RandomNumberGenerator::createStreams
"
This method must be called before using classes in other PyFrensie modules that
use the RandomNumberGenerator internally (e.g. the distribution classes in
PyFrensie.Utility.Distribution).
"

%feature("docstring")
Utility::RandomNumberGenerator::initialize
"
This method initializes the random number stream for desired particle history
number (or history 0 if no history number is provided).
"

%feature("docstring")
Utility::RandomNumberGenerator::initializeNextHistory
"
This method initializes the random number stream for the next particle history
number.
"

%feature("docstring")
Utility::RandomNumberGenerator::setFakeStream
"
Allows one to specify a fake random number stream that will be used instead of
the stream from the underlying random number generator. Make sure to call the
'unsetFakeStream' method after completing the task that needed the fake stream.
Only numpy arrays should be used to specify the fake stream.
"

%feature("docstring")
Utility::RandomNumberGenerator::unsetFakeStream
"
Deletes the fake stream and reinstates the original random number stream. Note
that the original random number stream state will be reset as well.
"

// Typemap which will allow use of NumPy arrays, lists or tuples to set
// the fake stream
%typemap(in) const std::vector<double>& fake_stream (std::vector<double> temp)
{
  temp = PyFrensie::convertFromPython<std::vector<double> >( $input );

  $1 = &temp;
}

// The typecheck precedence, which is used by SWIG to determine which
// overloaded method should be called, should be set to
// SWIG_TYPECHECK_DOUBLE_ARRAY (1050) for the std::vector<double>&. You will
// get a Python error when calling the overloaded method in Python without this
// typecheck
%typemap(typecheck, precedence=1090) (const std::vector<double>&) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// Include the RandomNumberGenerator
%include "Utility_RandomNumberGenerator.hpp"

// Instantiate the getRandomNumber template method
%template(getRandomNumber) Utility::RandomNumberGenerator::getRandomNumber<double>;

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end Utility.Prng.i
//---------------------------------------------------------------------------//
