//---------------------------------------------------------------------------//
//!
//! \file   Data_NuclideProperties.i
//! \author Luke Kersting
//! \brief  The NuclideProperties classes interface file
//!
//---------------------------------------------------------------------------//

%{
// Std Lib Includes
#include <stdexcept>
#include <sstream>
#include <memory>

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesHelper.hpp"
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Data_ThermalNuclearDataProperties.hpp"
#include "Data_AdjointNuclearDataProperties.hpp"
#include "Data_AdjointThermalNuclearDataProperties.hpp"
#include "Data_PhotonuclearDataProperties.hpp"
#include "Data_AdjointPhotonuclearDataProperties.hpp"
#include "Data_NuclideProperties.hpp"
#include "Data_ZAID.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
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
%include <std_vector.i>
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

// // General ignore directives
// %ignore *::operator<<;

// Add general templates
%template(EnergyVector) std::vector<Data::NuclideProperties::Energy>;
%template(TemperatureVector) std::vector<Data::NuclideProperties::Temperature>;

//---------------------------------------------------------------------------//
// Add support for the ZAID
//---------------------------------------------------------------------------//
// Import the ZAID
%include "Data_ZAID.hpp"

// Add typemaps for converting ZAID to and from Python int
%typemap(in) const Data::ZAID {
  $1 = PyFrensie::convertFromPython<unsigned>( $input );
}

%typemap(out) Data::ZAID {
  %append_output( (unsigned)$1 );
}

%typemap(typecheck, precedence=25) (const Data::ZAID) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

//---------------------------------------------------------------------------//
// Add support for the NuclearDataProperties
//---------------------------------------------------------------------------//

// Allow shared pointers of NuclearDataProperties objects
%shared_ptr( Data::NuclearDataProperties );

// Import the NuclearDataProperties
%include "Data_NuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the ThermalNuclearDataProperties
//---------------------------------------------------------------------------//

// Allow shared pointers of ThermalNuclearDataProperties objects
%shared_ptr( Data::ThermalNuclearDataProperties );

// Import the ThermalNuclearDataProperties
%include "Data_ThermalNuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the AdjointNuclearDataProperties
//---------------------------------------------------------------------------//

// Allow shared pointers of AdjointNuclearDataProperties objects
%shared_ptr( Data::AdjointNuclearDataProperties );

// Import the AdjointNuclearDataProperties
%include "Data_AdjointNuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the AdjointThermalNuclearDataProperties
//---------------------------------------------------------------------------//

// Allow shared pointers of AdjointThermalNuclearDataProperties objects
%shared_ptr( Data::AdjointThermalNuclearDataProperties );

// Import the AdjointThermalNuclearDataProperties
%include "Data_AdjointThermalNuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the PhotonuclearDataProperties
//---------------------------------------------------------------------------//

// Allow shared pointers of PhotonuclearDataProperties objects
%shared_ptr( Data::PhotonuclearDataProperties );

// Import the PhotonuclearDataProperties
%include "Data_PhotonuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the AdjointPhotonuclearDataProperties
//---------------------------------------------------------------------------//

// Allow shared pointers of AdjointPhotonuclearDataProperties objects
%shared_ptr( Data::AdjointPhotonuclearDataProperties );

// Import the AdjointPhotonuclearDataProperties
%include "Data_AdjointPhotonuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the NuclideProperties
//---------------------------------------------------------------------------//

%ignore *::AtomicWeight;
%ignore Data::NuclideProperties::NuclideProperties( const Data::ZAID, const AtomicWeight );

// Allow shared pointers of NuclideProperties objects
%shared_ptr( Data::NuclideProperties );

// Add std::set templates for FileType
%template(NuclearDataPropertiesSet) std::set< Data::NuclearDataProperties::FileType >;
%template(ThermalNuclearDataPropertiesSet) std::set< Data::ThermalNuclearDataProperties::FileType >;
%template(AdjointNuclearDataPropertiesSet) std::set< Data::AdjointNuclearDataProperties::FileType >;
%template(AdjointThermalNuclearDataPropertiesSet) std::set< Data::AdjointThermalNuclearDataProperties::FileType >;
%template(PhotonuclearDataPropertiesSet) std::set< Data::PhotonuclearDataProperties::FileType >;
%template(AdjointPhotonuclearDataPropertiesSet) std::set< Data::AdjointPhotonuclearDataProperties::FileType >;


// Rename the overloaded nuclearDataAvailable functions
%rename(nuclearDataAvailableAtMeV) Data::NuclideProperties::nuclearDataAvailable(
  const NuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp ) const;

%rename(thermalNuclearDataAvailableAtMeV) Data::NuclideProperties::thermalNuclearDataAvailable(
  const std::string& name,
  const ThermalNuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp ) const;

%rename(adjointNuclearDataAvailableAtMeV) Data::NuclideProperties::adjointNuclearDataAvailable(
  const AdjointNuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp ) const;

%rename(adjointThermalNuclearDataAvailableAtMeV) Data::NuclideProperties::adjointThermalNuclearDataAvailable(
  const std::string& name,
  const AdjointThermalNuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp ) const;

// Rename the overloaded getDataFileVersions functions
%rename(getNuclearDataFileVersions) Data::NuclideProperties::getDataFileVersions(
  const NuclearDataProperties::FileType file_type ) const;

%rename(getThermalNuclearDataFileVersions) Data::NuclideProperties::getDataFileVersions(
  const std::string& name,
  const ThermalNuclearDataProperties::FileType file_type ) const;

%rename(getAdjointNuclearDataFileVersions) Data::NuclideProperties::getDataFileVersions(
  const AdjointNuclearDataProperties::FileType file_type ) const;

%rename(getAdjointThermalNuclearDataFileVersions) Data::NuclideProperties::getDataFileVersions(
  const std::string& name,
  const AdjointThermalNuclearDataProperties::FileType file_type ) const;

%rename(getPhotonuclearDataFileVersions) Data::NuclideProperties::getDataFileVersions(
  const PhotonuclearDataProperties::FileType file_type ) const;

%rename(getAdjointPhotonuclearDataFileVersions) Data::NuclideProperties::getDataFileVersions(
  const AdjointPhotonuclearDataProperties::FileType file_type ) const;

// Rename the overloaded getRecommendedDataFileVersion functions
%rename(getRecommendedNuclearDataFileVersion) Data::NuclideProperties::getRecommendedDataFileVersion(
  const NuclearDataProperties::FileType file_type ) const;

%rename(getRecommendedThermalNuclearDataFileVersion) Data::NuclideProperties::getRecommendedDataFileVersion(
  const std::string& name,
  const ThermalNuclearDataProperties::FileType file_type ) const;

%rename(getRecommendedAdjointNuclearDataFileVersion) Data::NuclideProperties::getRecommendedDataFileVersion(
  const AdjointNuclearDataProperties::FileType file_type ) const;

%rename(getRecommendedAdjointThermalNuclearDataFileVersion) Data::NuclideProperties::getRecommendedDataFileVersion(
  const std::string& name,
  const AdjointThermalNuclearDataProperties::FileType file_type ) const;

%rename(getRecommendedPhotonuclearDataFileVersion) Data::NuclideProperties::getRecommendedDataFileVersion(
  const PhotonuclearDataProperties::FileType file_type ) const;

%rename(getRecommendedAdjointPhotonuclearDataFileVersion) Data::NuclideProperties::getRecommendedDataFileVersion(
  const AdjointPhotonuclearDataProperties::FileType file_type ) const;

// Rename the overloaded getDataEvaluationTemps function
%rename(getAdjointDataEvaluationTemps) Data::NuclideProperties::getDataEvaluationTemps(
  const AdjointNuclearDataProperties::FileType file_type,
  const unsigned table_major_version ) const;

%rename(getAdjointDataEvaluationTemps) Data::NuclideProperties::getDataEvaluationTemps(
  const std::string& name,
  const AdjointThermalNuclearDataProperties::FileType file_type,
  const unsigned table_major_version ) const;

// Rename the overloaded getDataEvaluationTempsInMeV function
%rename(getAdjointDataEvaluationTempsInMeV) Data::NuclideProperties::getDataEvaluationTempsInMeV(
  const AdjointNuclearDataProperties::FileType file_type,
  const unsigned table_major_version ) const;

%rename(getAdjointDataEvaluationTempsInMeV) Data::NuclideProperties::getDataEvaluationTempsInMeV(
  const std::string& name,
  const AdjointThermalNuclearDataProperties::FileType file_type,
  const unsigned table_major_version ) const;

// Rename the overloaded getNuclearDataProperties function
%rename(getNuclearDataPropertiesAtMeV) getNuclearDataProperties(
  const NuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

%rename(getThermalNuclearDataPropertiesAtMeV) getThermalNuclearDataProperties(
  const std::string& name,
  const ThermalNuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

%rename(getAdjointNuclearDataPropertiesAtMeV) getAdjointNuclearDataProperties(
  const AdjointNuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

%rename(getAdjointThermalNuclearDataPropertiesAtMeV) getAdjointThermalNuclearDataProperties(
  const std::string& name,
  const AdjointThermalNuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

// Rename the overloaded getSharedNuclearDataProperties function
%rename(getSharedNuclearDataPropertiesAtMeV) getSharedNuclearDataProperties(
  const NuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

%rename( getSharedThermalNuclearDataPropertiesAtMeV) getSharedThermalNuclearDataProperties(
  const std::string& name,
  const ThermalNuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

%rename(getSharedAdjointNuclearDataPropertiesAtMeV) getSharedAdjointNuclearDataProperties(
  const AdjointNuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

%rename( getSharedAdjointThermalNuclearDataPropertiesAtMeV) getSharedAdjointThermalNuclearDataProperties(
  const std::string& name,
  const AdjointThermalNuclearDataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;


// Add typemaps for converting AtomicWeight to and from Python float
%typemap(in) const Data::NuclideProperties::AtomicWeight {
  $1 = Data::NuclideProperties::AtomicWeight::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Data::NuclideProperties::AtomicWeight {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Data::NuclideProperties::AtomicWeight) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

// Apply AtomicWeight typemaps to other classes
%apply const Data::NuclideProperties::AtomicWeight {
  const Data::NuclearDataProperties::AtomicWeight,
  const Data::AdjointNuclearDataProperties::AtomicWeight,
  const Data::PhotonuclearDataProperties::AtomicWeight,
  const Data::AdjointPhotonuclearDataProperties::AtomicWeight };

%apply Data::NuclideProperties::AtomicWeight {
  Data::NuclearDataProperties::AtomicWeight,
  Data::AdjointNuclearDataProperties::AtomicWeight,
  Data::PhotonuclearDataProperties::AtomicWeight,
  Data::AdjointPhotonuclearDataProperties::AtomicWeight };

// Add typemaps for converting Energy to and from Python float
%typemap(in) const Data::NuclideProperties::Energy {
  $1 = Data::NuclideProperties::Energy::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Data::NuclideProperties::Energy {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Data::NuclideProperties::Energy) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

// Add typemaps for converting Temperature to and from Python float
%typemap(in) const Data::NuclideProperties::Temperature {
  $1 = Data::NuclideProperties::Temperature::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Data::NuclideProperties::Temperature {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Data::NuclideProperties::Temperature) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

// Import the NuclideProperties
%include "Data_NuclideProperties.hpp"


//---------------------------------------------------------------------------//
// end Data_NuclideProperties.i
//---------------------------------------------------------------------------//e
