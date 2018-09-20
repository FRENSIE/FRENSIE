//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronPhotonRelaxationDataGenerator.i
//! \author Luke Kersting
//! \brief  The AdjointElectronPhotonRelaxationDataGenerator class's interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_DesignByContract.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

// %import "Data.Native.i"
// %import "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

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
// Helper macro for setting up an ElectronPhotonRelaxationDataGenerator
// interface
//---------------------------------------------------------------------------//
%define %adjoint_epr_generator_interface_setup_helper( GENERATOR )

%feature("docstring") DataGen::GENERATOR
"The GENERATOR class is used to populate an "
"AdjointElectronPhotonRelaxationDataContainer."

 // Add some useful methods to the GENERATOR class
%extend DataGen::GENERATOR
{
  // String conversion method
  PyObject* __str__() const
  {
    return PyFrensie::convertToPython( Utility::toString( $self->getAtomicNumber() ) );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::string string_rep( "GENERATOR(" );
    string_rep += Utility::toString( $self->getAtomicNumber() );
    string_rep += ")";

    return PyFrensie::convertToPython( string_rep );
  }
}

%enddef

//---------------------------------------------------------------------------//
// Add support for the AdjointElectronPhotonRelaxationDataGenerator base class
//---------------------------------------------------------------------------//
%epr_generator_interface_setup_helper( AdjointElectronPhotonRelaxationDataGenerator )

%include "DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp"

//---------------------------------------------------------------------------//
// Add support for the StandardAdjointElectronPhotonRelaxationDataGenerator class
//---------------------------------------------------------------------------//
%epr_generator_interface_setup_helper( StandardAdjointElectronPhotonRelaxationDataGenerator )

%include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp"

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronPhotonRelaxationDataGenerator.i
//---------------------------------------------------------------------------//

