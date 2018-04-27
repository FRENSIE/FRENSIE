//---------------------------------------------------------------------------//
//!
//! \file   Data_AtomProperties.i
//! \author Luke Kersting
//! \brief  The AtomProperties classes interface file
//!
//---------------------------------------------------------------------------//

%{
// Std Lib Includes
#include <stdexcept>
#include <sstream>
#include <memory>

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Data_AtomType.hpp"
#include "Data_ScatteringCenterPropertiesHelper.hpp"
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_AdjointPhotoatomicDataProperties.hpp"
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_AdjointElectroatomicDataProperties.hpp"
#include "Data_AtomProperties.hpp"
#include "Data_ZAID.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_Set.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SerializationHelpers.hpp"

// Add the Data namespace to the global lookup scope
using namespace Data;
%}

// C++ STL support
%include <stl.i>
// %include <std_string.i>
%include <std_set.i>
// %include <std_map.i>
// %include <std_vector.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// Import the explicit template instantiation helpers
%include "Data_ExplicitTemplateInstantiationMacros.hpp"

// Standard exception handling
%include "exception.i"

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
  catch( Data::InvalidScatteringCenterPropertiesData& e )
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
%ignore *::operator<<;

// Add general templates
%template(IntSet) std::set< unsigned int>;

//---------------------------------------------------------------------------//
// Add support for the AtomType
//---------------------------------------------------------------------------//
// Import the AtomType
%include "Data_AtomType.hpp"

//---------------------------------------------------------------------------//
// Add support for the PhotoatomicDataProperties
//---------------------------------------------------------------------------//

// Allow shared pointers of PhotoatomicDataProperties objects
%shared_ptr( Data::PhotoatomicDataProperties );

// Import the PhotoatomicDataProperties
%include "Data_PhotoatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the AdjointPhotoatomicDataProperties
//---------------------------------------------------------------------------//

// Allow shared pointers of AdjointPhotoatomicDataProperties objects
%shared_ptr( Data::AdjointPhotoatomicDataProperties );

// Import the AdjointPhotoatomicDataProperties
%include "Data_AdjointPhotoatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the ElectroatomicDataProperties
//---------------------------------------------------------------------------//

// Allow shared pointers of ElectroatomicDataProperties objects
%shared_ptr( Data::ElectroatomicDataProperties );

// Import the ElectroatomicDataProperties
%include "Data_ElectroatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the AdjointElectroatomicDataProperties
//---------------------------------------------------------------------------//

// Allow shared pointers of AdjointElectroatomicDataProperties objects
%shared_ptr( Data::AdjointElectroatomicDataProperties );

// Import the AdjointElectroatomicDataProperties
%include "Data_AdjointElectroatomicDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the AtomProperties
//---------------------------------------------------------------------------//

%ignore *::AtomicWeight;
%ignore Data::AtomProperties::AtomProperties( const Data::AtomType, const AtomicWeight );

// Allow shared pointers of AtomProperties objects
%shared_ptr( Data::AtomProperties );

// Add std::set templates for FileType
%template(PhotoatomicDataPropertiesSet) std::set< Data::PhotoatomicDataProperties::FileType >;

%template(AdjointPhotoatomicDataPropertiesSet) std::set< Data::AdjointPhotoatomicDataProperties::FileType >;

%template(ElectroatomicDataPropertiesSet) std::set< Data::ElectroatomicDataProperties::FileType >;

%template(AdjointElectroatomicDataPropertiesSet) std::set< Data::AdjointElectroatomicDataProperties::FileType >;

// Rename the overloaded getDataFileVersions functions
%rename(getPhotoatomicDataFileVersions) Data::AtomProperties::getDataFileVersions(
  const PhotoatomicDataProperties::FileType file_type ) const;

%rename(getAdjointPhotoatomicDataFileVersions) Data::AtomProperties::getDataFileVersions(
  const AdjointPhotoatomicDataProperties::FileType file_type ) const;

%rename(getElectroatomicDataFileVersions) Data::AtomProperties::getDataFileVersions(
  const ElectroatomicDataProperties::FileType file_type ) const;

%rename(getAdjointElectroatomicDataFileVersions) Data::AtomProperties::getDataFileVersions(
  const AdjointElectroatomicDataProperties::FileType file_type ) const;

// Rename the overloaded getRecommendedDataFileVersion functions
%rename(getRecommendedPhotoatomicDataFileVersion) Data::AtomProperties::getRecommendedDataFileVersion(
  const PhotoatomicDataProperties::FileType file_type ) const;

%rename(getRecommendedAdjointPhotoatomicDataFileVersion) Data::AtomProperties::getRecommendedDataFileVersion(
  const AdjointPhotoatomicDataProperties::FileType file_type ) const;

%rename(getRecommendedElectroatomicDataFileVersion) Data::AtomProperties::getRecommendedDataFileVersion(
  const ElectroatomicDataProperties::FileType file_type ) const;

%rename(getRecommendedAdjointElectroatomicDataFileVersion) Data::AtomProperties::getRecommendedDataFileVersion(
  const AdjointElectroatomicDataProperties::FileType file_type ) const;


// Add typemaps for converting AtomicWeight to and from Python float
// %typemap(in) const Data::AtomProperties::AtomicWeight {
//   $1 = Geometry::Navigator::AtomicWeight::from_value( PyFrensie::convertFromPython<double>( $input ) );
// }

%typemap(out) Data::AtomProperties::AtomicWeight {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Data::AtomProperties::AtomicWeight) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

// typemap(out) Data::AtomProperties::AtomicWeight {
//   $result = Utility::getRawQuantity( $1 )
// }

// Import the AtomProperties
%include "Data_AtomProperties.hpp"

//---------------------------------------------------------------------------//
// end Data_AtomProperties.i
//---------------------------------------------------------------------------//e
