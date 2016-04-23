//---------------------------------------------------------------------------//
//!
//! \file   Data.Native.i
//! \author Alex Robinson
//! \brief  The Data.Native sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %data_native_docstring
"
PyFrensie.Data.Native is the python interface to the FRENSIE data/native
subpackage.

The purpose of Native is to provide tools for reading the data from a Native
FRENSIE formate data file.
"
%enddef

%module(package   = "PyFrensie.Data",
        autodoc   = "1",
        docstring = %data_native_docstring) Native

%{
// Std Lib Includes
#include <sstream>

// PyTrilinos Includes
#define NO_IMPORT_ARRAY
#include "numpy_include.h"

// FRENSIE Includes
#include "PyFrensie_TeuchosArrayConversionHelpers.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_ArchivableObject.hpp"
#include "Utility_ContractException.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_except.i>
%include <std_set.i>
%include <std_pair.i>
%include <std_vector.i>

// Include the Teuchos::ArrayRCP support
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
// Add support for the ArchivableObject::ArchiveType enum
//---------------------------------------------------------------------------//
%import "Utility_ArchivableObject.hpp"

//---------------------------------------------------------------------------//
// Add support for the ElectronPhotonRelaxationDataContainer
//---------------------------------------------------------------------------//
// Add a more detailed docstring for the ElectronPhotonRelaxationDataContainer
%feature("docstring")
Data::ElectronPhotonRelaxationDataContainer
"
The ElectronPhotonRelaxationDataContainer can be used to read in a Native
format EPR data file and extract the data contained in it. A brief usage
tutorial for this class is shown below:

  import PyFrensie.Data.Native, PyTrilinos.Teuchos, numpy, matplotlib.pyplot

  source = PyTrilinos.Teuchos.FileInputSource( 'datadir/cross_sections.xml' )
  xml_obj = source.getObject()
  cs_list = PyTrilinos.Teuchos.XMLParameterListReader().toParameterList( xml_obj )
  
  h_data_list = cs_list.get( 'H-Native' )
  h_native_file_name = 'datadir' + h_data_list.get( 'photoatomic_file_path' )
  
  h_native_data = PyFrensie.Data.Native.ElectronPhotonRelaxationDataContainer( h_native_file_name )

  matplotlib.pyplot.loglog( h_native_data.getPhotonEnergyGrid(), h_native_data.getWallerHartreeIncoherentCrossSection() )
  matplotlib.pyplot.loglog( h_native_data.getPhotonEnergyGrid(), h_native_data.getImpulseApproxIncoherentCrossSection() )
  matplotlib.pyplot.show()  
"

// Allow std::set<unsigned> output type
%template(SubshellSet) std::set<unsigned>;

// Allow std::vector<std::pair<unsigned,unsigned> > output type
%template(RelaxationVacancyArray) std::vector<std::pair<unsigned,unsigned> >;

// Keep the Utility::ArchivableObject hidden and instead add static constants
// to the ElectronPhotonRelaxationDataContainer that can be used to read in
// data tables with the different archive formats. Also add some useful
// methods.
%extend Data::ElectronPhotonRelaxationDataContainer
{
  static const Utility::ArchivableObject::ArchiveType ASCII = 
    Utility::ArchivableObject::ASCII_ARCHIVE;
  static const Utility::ArchivableObject::ArchiveType BINARY = 
    Utility::ArchivableObject::BINARY_ARCHIVE;
  static const Utility::ArchivableObject::ArchiveType XML = 
    Utility::ArchivableObject::XML_ARCHIVE;

  // String conversion method
  PyObject* __str__() const
  {
    std::ostringstream oss;
    oss << "EPR for Z=" << $self->getAtomicNumber();
    
    return PyString_FromString( oss.str().c_str() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::ostringstream oss;
    oss << "ElectronPhotonRelaxationDataContainer(EPR for Z=" 
        << $self->getAtomicNumber() << ")";
          
    return PyString_FromString( oss.str().c_str() );
  }
}

// Include the ElectronPhotonRelaxationDataContainer
%include "Data_ElectronPhotonRelaxationDataContainer.hpp"

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Data.Native.i
//---------------------------------------------------------------------------//
