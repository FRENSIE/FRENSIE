//---------------------------------------------------------------------------//
//!
//! \file   DataGen.ENDL.i
//! \author Alex Robinson
//! \brief  The DataGen.ENDL sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %data_gen_endl_docstring
"
PyFrensie.DataGen.ENDL is the python interface to the FRENSIE
data_gen/endl subpackage.

The purpose of ENDL is to provide tools for generating ENDL data.
"
%enddef

%module(package   = "PyFrensie.DataGen",
        autodoc   = "1",
        docstring = %data_gen_endl_docstring) ENDL

%{
#define NO_IMPORT_ARRAY
#include "numpy_include.h"

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "DataGen_StandardENDLDataGenerator.hpp"
#include "Data_ENDLPhotoatomicDataProperties.hpp"
#include "Data_ENDLElectroatomicDataProperties.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_DesignByContract.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

%import "Data.ENDL.i"

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
  catch( std::runtime_error& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

// Add typemaps for converting file_path to and from Python string
%typemap(in) const boost::filesystem::path& ( boost::filesystem::path temp ){
  temp = PyFrensie::convertFromPython<std::string>( $input );
  $1 = &temp;
}

%typemap(typecheck, precedence=1140) (const boost::filesystem::path&) {
  $1 = (PyString_Check($input)) ? 1 : 0;
}

//---------------------------------------------------------------------------//
// Helper macro for setting up an ENDLDataGenerator interface
//---------------------------------------------------------------------------//
%define %endl_generator_interface_setup_helper( GENERATOR )

%feature("docstring") DataGen::GENERATOR
"The GENERATOR class is used to populate an ENDLDataContainer."

// Add some useful methods to the GENERATOR class
%extend DataGen::GENERATOR
{
  // String conversion method
  PyObject* __str__() const
  {
    return PyFrensie::convertToPython( Utility::toString( $self->getDataContainer().getAtomicNumber() ) );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::string string_rep( "GENERATOR(" );
    string_rep += Utility::toString( $self->getDataContainer().getAtomicNumber() );
    string_rep += ")";

    return PyFrensie::convertToPython( string_rep );
  }
}

%enddef

//---------------------------------------------------------------------------//
// Add support for the ENDLDataGenerator base class
//---------------------------------------------------------------------------//
%endl_generator_interface_setup_helper( ENDLDataGenerator )

%include "DataGen_ENDLDataGenerator.hpp"

//---------------------------------------------------------------------------//
// Add support for the StandardENDLDataGenerator class
//---------------------------------------------------------------------------//

%endl_generator_interface_setup_helper( StandardENDLDataGenerator )

%include "DataGen_StandardENDLDataGenerator.hpp"

//---------------------------------------------------------------------------//
// end DataGen.ENDL.i
//---------------------------------------------------------------------------//
