//---------------------------------------------------------------------------//
//!
//! \file   Data.ACE.i
//! \author Alex Robinson
//! \brief  The Data.ACE sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %data_ace_docstring
"
PyFrensie.Data.ACE is the python interface to the FRENSIE data/ace
subpackage.

The purpose of ACE is to provide tools for reading data from an ACE table
and extracting data blocks from the XSS array.
"
%enddef

%module(package   = "PyFrensie.Data",
        autodoc   = "1",
        docstring = %data_ace_docstring) ACE

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"

#include "Data_ACETableName.hpp"
#include "Data_ACEPhotoatomicDataProperties.hpp"
#include "Data_ACEElectroatomicDataProperties.hpp"
#include "Data_ACENuclearDataProperties.hpp"
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Data_ACEPhotonuclearDataProperties.hpp"

#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_XSSSabDataExtractor.hpp"
#include "Data_XSSElectronDataExtractor.hpp"
#include "Data_XSSPhotoatomicDataExtractor.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"

#include "Utility_SerializationHelpers.hpp"
#include "Utility_DesignByContract.hpp"

// Add the Data namespace to the global lookup scope
using namespace Data;
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include the ArrayView support
%include "PyFrensie_Array.i"

// AtomProperties handling
%import(module="PyFrensie.Data") Data_AtomProperties.i

// NuclideProperties handling
%import(module="PyFrensie.Data") Data_NuclideProperties.i

// Include the data property helpers
%include "Data_PropertyHelpers.i"

// Include the serialization helpers for macros
%include "Utility_SerializationHelpers.hpp"

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
// Add support for the ACETableName
//---------------------------------------------------------------------------//

%ignore Data::ACETableName::operator std::string() const;

%rename(assign) Data::ACETableName::operator=( const ACETableName& that );

// Import the ACETableName
%include "Data_ACETableName.hpp"

// Add typemap for converting ACETableName to and from python string
%typemap(in) const Data::ACETableName& (Data::ACETableName temp){
  temp = PyFrensie::convertFromPython<std::string>( $input );
  $1 = &temp;
}

%typename(typecheck, precedence=1140) (const Data::ACETableName& ) {
  $1 = (PyString_Check($input)) ? 1 : 0;
}

// Add some useful methods to the ACETableName class
%extend Data::ACETableName
{
  // String conversion method
  PyObject* __str__() const
  {
    return PyString_FromString( $self->toRaw().c_str() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    return PyString_FromString( $self->toRaw().c_str() );
  }

};

//---------------------------------------------------------------------------//
// Add support for the ACEPhotoatomicDataProperties
//---------------------------------------------------------------------------//

%atomic_properties_interface_setup( ACEPhotoatomicDataProperties );

// Import the ACEPhotoatomicDataProperties
%include "Data_ACEPhotoatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the ACEElectroatomicDataProperties
//---------------------------------------------------------------------------//

%atomic_properties_interface_setup( ACEElectroatomicDataProperties );

// Import the ACEElectroatomicDataProperties
%include "Data_ACEElectroatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the NuclearDataProperties
//---------------------------------------------------------------------------//

%nuclear_properties_interface_setup( ACENuclearDataProperties );

// Import the ACENuclearDataProperties
%include "Data_ACENuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the ThermalNuclearDataProperties
//---------------------------------------------------------------------------//

%nuclear_properties_interface_setup( ACEThermalNuclearDataProperties );

// Import the ACEThermalNuclearDataProperties
%include "Data_ACEThermalNuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the PhotonuclearDataProperties
//---------------------------------------------------------------------------//

%photonuclear_properties_interface_setup(ACEPhotonuclearDataProperties );

%include "Data_ACEPhotonuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the ACEFileHandler
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the ACEFileHandler
%feature("docstring")
Data::ACEFileHandler
"
The ACEFileHandler can be used to read in any ACE table and extract
the NXS array, JXS array and XSS array. Usually, these arrays are then
passed to one of the XSSDataExtractor classes to extract the individual
data blocks from the XSS array. A brief usage tutorial for this class is
shown below:

  import PyFrensie.Data.ACE, numpy

  h_ace_file = PyFrensie.Data.ACE.ACEFileHandler( 'h_ace_file_name', 'photoatomic_table_name' )

  nxs_array = h_ace_file.getTableNXSArray()
  jxs_array = h_ace_file.getTableJXSArray()
  xss_array = h_ace_file.getTableXSSArray()
"

// Add typemaps for converting Energy to and from Python float
%typemap(in) const Data::ACEFileHandler::Energy {
  $1 = Data::ACEFileHandler::Energy::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Data::ACEFileHandler::Energy {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Data::ACEFileHandler::Energy) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}


// Add support for std::shared_ptr<std::vector<double> >
%shared_ptr(std::vector<double>);
%template(DoubleVector) std::vector<double>;


// Swig will return an ArrayView<int> instead of ArrayView<Zaid>. To avoid this
// the class is extended to return a std::vector<Zaid> instead.

// %array_typemaps(Data::ZAID , NPY_INT )

%template(ZaidVector) std::vector<Data::ZAID>;

// Add some useful methods to the ACEFileHandler class
%extend Data::ACEFileHandler
{
  // Return the table's ZAIDs
  std::vector<Data::ZAID> Data::ACEFileHandler::getTableZAIDs() const
  {
    std::vector<Data::ZAID> temp( $self->getTableZAIDs().begin(), $self->getTableZAIDs().end() );

    return temp;
  }

  // String conversion method
  PyObject* __str__() const
  {
    std::string string_rep( $self->getTableName() );
    string_rep += " from ";
    string_rep += $self->getLibraryName().string();

    return PyString_FromString( string_rep.c_str() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::string string_rep( "ACEFileHandler(" );
    string_rep += $self->getTableName();
    string_rep += " from ";
    string_rep += $self->getLibraryName().string();
    string_rep += ")";

    return PyString_FromString( string_rep.c_str() );
  }
};

// Ignore the original getTableZAIDs but keep the extened version
%ignore Data::ACEFileHandler::getTableZAIDs() const;

// Include ACEFileHandler
%include "Data_ACEFileHandler.hpp"

//---------------------------------------------------------------------------//
// Add support for the XSSNeutronDataExtractor
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the XSSNeutronDataExtractor
%feature("docstring")
Data::XSSNeutronDataExtractor
"
The XSSNeutronDataExtractor can be used to extract the data blocks from the
xss array found in an ACE data table.  A brief usage tutorial for this class is
shown below:

  import PyFrensie.Data.ACE, numpy, matplotlib.pyplot

  h_1_ace_file = PyFrensie.Data.ACE.ACEFileHandler( ace_file_name, ace_table_name )

  neutron_data_extractor = PyFrensie.Data.ACE.XSSNeutronDataExtractor( h_1_ace_file.getTableNXSArray(), h_1_ace_file.getTableJXSArray(), h_1_ace_file.getTableXSSArray() )

  matplotlib.pyplot.loglog( neutron_data_extractor.extractEnergyGrid(), neutron_data_extractor.extractTotalCrossSection() )
  matplotlib.pyplot.show()
"

// Include XSSNeutronDataExtractor
%include "Data_XSSNeutronDataExtractor.hpp"

// ---------------------------------------------------------------------------//
// Add support for the XSSEPRDataExtractor
// ---------------------------------------------------------------------------//

// Add more detailed docstrings for the XSSEPRDataExtractor
%feature("docstring")
Data::XSSEPRDataExtractor
"
The XSSEPRDataExtractor can be used to extract the data blocks from the
xss array found in an ACE data table.  A brief usage tutorial for this class is
shown below:

  import PyFrensie.Data.ACE, numpy, matplotlib.pyplot

  h_1_ace_file = PyFrensie.Data.ACE.ACEFileHandler( ace_file_name, ace_table_name )

  neutron_data_extractor = PyFrensie.Data.ACE.XSSEPRDataExtractor( h_1_ace_file.getTableNXSArray(), h_1_ace_file.getTableJXSArray(), h_1_ace_file.getTableXSSArray() )

  matplotlib.pyplot.loglog( neutron_data_extractor.extractPhotonEnergyGrid(), neutron_data_extractor.extractIncoherentCrossSection() )
  matplotlib.pyplot.loglog( neutron_data_extractor.extractPhotonEnergyGrid(), neutron_data_extractor.extractCoherentCrossSection() )
  matplotlib.pyplot.loglog( neutron_data_extractor.extractPhotonEnergyGrid(), neutron_data_extractor.extractPhotoelectricCrossSection() )
  matplotlib.pyplot.loglog( neutron_data_extractor.extractPhotonEnergyGrid(), neutron_data_extractor.extractPairProductionCrossSection() )
  matplotlib.pyplot.show()
"

%shared_ptr( Data::XSSEPRDataExtractor )

// Include XSSEPRDataExtractor
%include "Data_XSSEPRDataExtractor.hpp"

// ---------------------------------------------------------------------------//
// Add support for the XSSElectronDataExtractor
// ---------------------------------------------------------------------------//

// Include XSSElectronDataExtractor
%include "Data_XSSElectronDataExtractor.hpp"

// ---------------------------------------------------------------------------//
// Add support for the XSSPhotonuclearDataExtractor
// ---------------------------------------------------------------------------//

// Include XSSPhotonuclearDataExtractor
%include "Data_XSSPhotonuclearDataExtractor.hpp"

// ---------------------------------------------------------------------------//
// Add support for the XSSPhotoatomicDataExtractor
// ---------------------------------------------------------------------------//

// Include XSSPhotoatomicDataExtractor
%include "Data_XSSPhotoatomicDataExtractor.hpp"


// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Data_ACE.i
//---------------------------------------------------------------------------//
