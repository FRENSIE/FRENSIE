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
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Data_NativeEPRPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRElectroatomicDataProperties.hpp"
#include "Data_NativeMomentPreservingElectroatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointElectroatomicDataProperties.hpp"

#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_ArchivableObject.hpp"

#include "Utility_SerializationHelpers.hpp"
#include "Utility_DesignByContract.hpp"

// Add the Data namespace to the global lookup scope
using namespace Data;
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_except.i>
%include <std_set.i>
%include <std_pair.i>
%include <std_vector.i>

// Include typemaps support
%include <typemaps.i>

// AtomProperties handling
%import(module="PyFrensie.Data") Data_AtomProperties.i

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

// Add some general templates
%template(DoubleVector) std::vector<double>;
%template(UnsignedPair) std::pair<unsigned,unsigned>;
%template(UnsignedPairVector) std::vector<std::pair<unsigned,unsigned> >;
%template(DoubleVectorMap) std::map<double,std::vector<double> >;
%template(DoubleVectorVector) std::vector<std::vector<double> >;

//---------------------------------------------------------------------------//
// Add support for the NativeEPRPhotoatomicDataProperties
//---------------------------------------------------------------------------//

%atomic_properties_interface_setup( NativeEPRPhotoatomicDataProperties );

// Import the NativeEPRPhotoatomicDataProperties
%include "Data_NativeEPRPhotoatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the NativeEPRElectroatomicDataProperties
//---------------------------------------------------------------------------//

%atomic_properties_interface_setup( NativeEPRElectroatomicDataProperties );

// Import the NativeEPRElectroatomicDataProperties
%include "Data_NativeEPRElectroatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the NativeMomentPreservingElectroatomicDataProperties
//---------------------------------------------------------------------------//

%atomic_properties_interface_setup( NativeMomentPreservingElectroatomicDataProperties );

// Import the NativeMomentPreservingElectroatomicDataProperties
%include "Data_NativeMomentPreservingElectroatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the NativeEPRAdjointPhotoatomicDataProperties
//---------------------------------------------------------------------------//

%atomic_properties_interface_setup( NativeEPRAdjointPhotoatomicDataProperties );

// Import the NativeEPRAdjointPhotoatomicDataProperties
%include "Data_NativeEPRAdjointPhotoatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the NativeEPRAdjointElectroatomicDataProperties
//---------------------------------------------------------------------------//

%atomic_properties_interface_setup( NativeEPRAdjointElectroatomicDataProperties );

// Import the NativeEPRAdjointElectroatomicDataProperties
%include "Data_NativeEPRAdjointElectroatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Use this general setup macro with all native tables
//---------------------------------------------------------------------------//
%define %standard_native_data_container_setup( NATIVE_DATA_CONTAINER, SHORT_NAME )

%extend Data::NATIVE_DATA_CONTAINER
{
  // Save the container to a file
  void saveToFile( const std::string& filename, const bool overwrite = false )
  {
    $self->saveToFile( filename, overwrite );
  }

  // String conversion method
  PyObject* __str__() const
  {
    std::ostringstream oss;
    oss << "SHORT_NAME for Z=" << $self->getAtomicNumber();

    return PyString_FromString( oss.str().c_str() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::ostringstream oss;
    oss << "NATIVE_DATA_CONTAINER(SHORT_NAME for Z="
        << $self->getAtomicNumber() << ")";

    return PyString_FromString( oss.str().c_str() );
  }
}

%enddef

// //---------------------------------------------------------------------------//
// // Create aliases for common type found in native data tables
// //---------------------------------------------------------------------------//

// // Allow std::set<unsigned> output type
// %template(SubshellSet) std::set<unsigned>;

// // Allow std::vector<std::pair<unsigned,unsigned> > output type
// %template(RelaxationVacancyArray) std::vector<std::pair<unsigned,unsigned> >;

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

  import PyFrensie.Data.Native, numpy, matplotlib.pyplot

  h_native_data = PyFrensie.Data.Native.ElectronPhotonRelaxationDataContainer( 'h_native_file_name' )

  matplotlib.pyplot.loglog( h_native_data.getPhotonEnergyGrid(), h_native_data.getWallerHartreeIncoherentCrossSection() )
  matplotlib.pyplot.loglog( h_native_data.getPhotonEnergyGrid(), h_native_data.getImpulseApproxIncoherentCrossSection() )
  matplotlib.pyplot.show()
"

%standard_native_data_container_setup( ElectronPhotonRelaxationDataContainer, EPR )

%shared_ptr(Data::ElectronPhotonRelaxationDataContainer);

// Include the ElectronPhotonRelaxationDataContainer
%include "Data_ElectronPhotonRelaxationDataContainer.hpp"

//---------------------------------------------------------------------------//
// Add support for the AdjointElectronPhotonRelaxationDataContainer
//---------------------------------------------------------------------------//
// Add a more detailed docstring for the AdjointElectronPhotonRelaxationDataContainer
%feature("docstring")
Data::AdjointElectronPhotonRelaxationDataContainer
"
The AdjointElectronPhotonRelaxationDataContainer can be used to read in a Native
format AEPR data file and extract the data contained in it. A brief usage
tutorial for this class is shown below:

  import PyFrensie.Data.Native, numpy, matplotlib.pyplot

  h_adj_native_data = PyFrensie.Data.Native.AdjointElectronPhotonRelaxationDataContainer( 'h_adj_native_file_name' )

  matplotlib.pyplot.loglog( h_adj_native_data.getAdjointPhotonEnergyGrid(), h_adj_native_data.getAdjointWallerHartreeIncoherentCrossSection()[0] )
  matplotlib.pyplot.loglog( h_adj_native_data.getAdjointPhotonEnergyGrid(), h_adj_native_data.getImpulseApproxIncoherentCrossSection()[0] )
  matplotlib.pyplot.show()
"

%standard_native_data_container_setup( AdjointElectronPhotonRelaxationDataContainer, AEPR )

%shared_ptr(Data::AdjointElectronPhotonRelaxationDataContainer);

// Include the ElectronPhotonRelaxationDataContainer
%include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end Data.Native.i
//---------------------------------------------------------------------------//
