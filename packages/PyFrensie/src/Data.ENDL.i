//---------------------------------------------------------------------------//
//!
//! \file   Data.ENDL.i
//! \author Luke Kersting
//! \brief  The Data.ENDL sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %data_endl_docstring
"
PyFrensie.Data.ENDL is the python interface to the FRENSIE data/endl
subpackage.

The purpose of ENDL is to provide tools for reading the data from a ENDL
FRENSIE format data file.
"
%enddef

%module(package   = "PyFrensie.Data",
        autodoc   = "1",
        docstring = %data_endl_docstring) ENDL

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Data_ENDLPhotoatomicDataProperties.hpp"
#include "Data_ENDLElectroatomicDataProperties.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_DesignByContract.hpp"

// Add the Data namespace to the global lookup scope
using namespace Data;
%}

// C++ STL support
%include <stl.i>
%include <std_set.i>
%include <std_map.i>
%include <std_vector.i>
%include <std_except.i>
%include <std_shared_ptr.i>

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

//---------------------------------------------------------------------------//
// Add support for the ENDLPhotoatomicDataProperties
//---------------------------------------------------------------------------//

%atomic_properties_interface_setup( ENDLPhotoatomicDataProperties );

// Import the ENDLPhotoatomicDataProperties
%include "Data_ENDLPhotoatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the ENDLElectroatomicDataProperties
//---------------------------------------------------------------------------//

%atomic_properties_interface_setup( ENDLElectroatomicDataProperties );

// Import the ENDLElectroatomicDataProperties
%include "Data_ENDLElectroatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the ENDLDataContainer
//---------------------------------------------------------------------------//
// Add a more detailed docstring for the ENDLDataContainer
%feature("docstring")
Data::ENDLDataContainer
"
The ENDLDataContainer can be used to read in a ENDL
format EPR data file and extract the data contained in it. A brief usage
tutorial for this class is shown below:

  import PyFrensie.Data.ENDL, numpy, matplotlib.pyplot

  h_native_data = PyFrensie.Data.ENDL.ENDLDataContainer( 'h_endl_file_name' )

  matplotlib.pyplot.loglog( h_native_data.getElasticEnergyGrid(), h_native_data.getCutoffElasticCrossSection() )
  matplotlib.pyplot.loglog( h_native_data.getElasticEnergyGrid(), h_native_data.getElasticTransportCrossSection() )
  matplotlib.pyplot.show()
"

// Allow std::vector<double> output type
%template(DoubleVector) std::vector<double>;

// Allow std::vector<std::pair<unsigned,unsigned> > output type
%template(RelaxationVacancyArray) std::vector<std::pair<unsigned,unsigned> >;

// Allow std::map<double,std::vector<double> > output type
%template(DoubleVectorMap) std::map<double,std::vector<double> >;

%extend Data::ENDLDataContainer
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
    oss << "EPR for Z=" << $self->getAtomicNumber();

    return PyString_FromString( oss.str().c_str() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::ostringstream oss;
    oss << "ENDLDataContainer(EPR for Z="
        << $self->getAtomicNumber() << ")";

    return PyString_FromString( oss.str().c_str() );
  }
}

%shared_ptr( Data::ENDLDataContainer )

// Include the ENDLDataContainer
%include "Data_ENDLDataContainer.hpp"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end Data.ENDL.i
//---------------------------------------------------------------------------//
