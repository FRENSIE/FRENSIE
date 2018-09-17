//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElectronPhotonRelaxationDataGenerator.i
//! \author Alex Robinson
//! \brief  The ElectronPhotonRelaxationDataGenerator class's interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "DataGen_ElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_ENDLElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_ACEAndENDLElectronPhotonRelaxationDataGenerator.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_ACEPhotoatomicDataProperties.hpp"
#include "Data_ACEElectroatomicDataProperties.hpp"
#include "Data_ACENuclearDataProperties.hpp"
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Data_ACEPhotonuclearDataProperties.hpp"
#include "Data_ENDLPhotoatomicDataProperties.hpp"
#include "Data_ENDLElectroatomicDataProperties.hpp"
#include "Data_NativeEPRPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRElectroatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointElectroatomicDataProperties.hpp"
#include "Data_NativeMomentPreservingElectroatomicDataProperties.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_DesignByContract.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

%import "Data.ENDL.i"
%import "Data.ACE.i"
%import "Data.Native.i"
%import(module="PyFrensie.MonteCarlo") MonteCarlo_SimulationProperties.i

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
%define %epr_generator_interface_setup_helper( GENERATOR )

%feature("docstring") DataGen::GENERATOR
"The GENERATOR class is used to populate an "
"ElectronPhotonRelaxationDataContainer."

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
// Add support for the ElectronPhotonRelaxationDataGenerator base class
//---------------------------------------------------------------------------//
%epr_generator_interface_setup_helper( ElectronPhotonRelaxationDataGenerator )

%include "DataGen_ElectronPhotonRelaxationDataGenerator.hpp"

//---------------------------------------------------------------------------//
// Add support for the ENDLElectronPhotonRelaxationDataGenerator class
//---------------------------------------------------------------------------//
%epr_generator_interface_setup_helper( ENDLElectronPhotonRelaxationDataGenerator )

%include "DataGen_ENDLElectronPhotonRelaxationDataGenerator.hpp"

//---------------------------------------------------------------------------//
// Add support for the ACEAndENDLElectronPhotonRelaxationDataGenerator class
//---------------------------------------------------------------------------//
%epr_generator_interface_setup_helper( ACEAndENDLElectronPhotonRelaxationDataGenerator )

%include "DataGen_ACEAndENDLElectronPhotonRelaxationDataGenerator.hpp"

//---------------------------------------------------------------------------//
// end DataGen_ElectronPhotonRelaxationDataGenerator.i
//---------------------------------------------------------------------------//

