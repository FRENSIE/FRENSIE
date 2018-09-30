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
#include "Utility_DesignByContract.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ToStringTraitsDecl.hpp"
#include "Utility_TypeTraitsDecl.hpp"

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

// Import the ToString Traits and Type Traits Decl
%import "Utility_ToStringTraitsDecl.hpp"
%import "Utility_TypeTraitsDecl.hpp"

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// Include the data property helpers
%include "Data_PropertyHelpers.i"

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

// Add typemaps for converting file_path to and from Python string
%typemap(in) const boost::filesystem::path& ( boost::filesystem::path temp ){
  temp = PyFrensie::convertFromPython<std::string>( $input );
  $1 = &temp;
}

%typemap(out) boost::filesystem::path {
  %append_output(PyFrensie::convertToPython( $1.string() ) );
}

%typemap(out) const boost::filesystem::path& {
  %append_output(PyFrensie::convertToPython( $1->string() ) );
}

%typemap(typecheck, precedence=1140) (const boost::filesystem::path&) {
  $1 = (PyString_Check($input)) ? 1 : 0;
}

//---------------------------------------------------------------------------//
// Add support for the ZAID
//---------------------------------------------------------------------------//

%rename(assign) Data::ZAID::operator=( const ZAID& that );
%rename(make_unsigned) Data::ZAID::operator unsigned() const;

// Import the ZAID
%include "Data_ZAID.hpp"

// Add template for a std::set of ZAIDs
%template(ZaidSet) std::set<Data::ZAID>;

//---------------------------------------------------------------------------//
// Add support for the NuclearDataProperties
//---------------------------------------------------------------------------//

// Use helper interface setup
%nuclear_properties_interface_setup(NuclearDataProperties);

// Import the NuclearDataProperties
%include "Data_NuclearDataProperties.hpp"

// Add std::set template for FileType
%template(NuclearDataPropertiesSet) std::set< Data::NuclearDataProperties::FileType >;

//---------------------------------------------------------------------------//
// Add support for the ThermalNuclearDataProperties
//---------------------------------------------------------------------------//

// Use helper interface setup
%thermal_nuclear_properties_interface_setup(ThermalNuclearDataProperties);

// Import the ThermalNuclearDataProperties
%include "Data_ThermalNuclearDataProperties.hpp"

// Add std::set template for FileType
%template(ThermalNuclearDataPropertiesSet) std::set< Data::ThermalNuclearDataProperties::FileType >;

//---------------------------------------------------------------------------//
// Add support for the AdjointNuclearDataProperties
//---------------------------------------------------------------------------//

// Use helper interface setup
%nuclear_properties_interface_setup(AdjointNuclearDataProperties);

// Import the AdjointNuclearDataProperties
%include "Data_AdjointNuclearDataProperties.hpp"

// Add std::set template for FileType
%template(AdjointNuclearDataPropertiesSet) std::set< Data::AdjointNuclearDataProperties::FileType >;

//---------------------------------------------------------------------------//
// Add support for the AdjointThermalNuclearDataProperties
//---------------------------------------------------------------------------//

// Use helper interface setup
%thermal_nuclear_properties_interface_setup(AdjointThermalNuclearDataProperties);

// Import the AdjointThermalNuclearDataProperties
%include "Data_AdjointThermalNuclearDataProperties.hpp"

// Add std::set template for FileType
%template(AdjointThermalNuclearDataPropertiesSet) std::set< Data::AdjointThermalNuclearDataProperties::FileType >;

//---------------------------------------------------------------------------//
// Add support for the PhotonuclearDataProperties
//---------------------------------------------------------------------------//

%photonuclear_properties_interface_setup(PhotonuclearDataProperties);

// Import the PhotonuclearDataProperties
%include "Data_PhotonuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the AdjointPhotonuclearDataProperties
//---------------------------------------------------------------------------//

%adjoint_photonuclear_properties_interface_setup(AdjointPhotonuclearDataProperties)

// Import the AdjointPhotonuclearDataProperties
%include "Data_AdjointPhotonuclearDataProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the NuclideProperties
//---------------------------------------------------------------------------//

%ignore *::AtomicWeight;
%ignore Data::NuclideProperties::NuclideProperties( const Data::ZAID, const AtomicWeight );

%feature("docstring") Data::NuclideProperties
"The NuclideProperties class stores a nuclear data properties. It can be used for
querying nuclear data properties and for creating nuclear data extractors or
container, which can be used to read nuclear data."

%feature("autodoc", "zaid(NuclideProperties self) -> ZAID")
Data::NuclideProperties::zaid;

%feature("autodoc", "atomicWeight(NuclideProperties self) -> AtomicWeight")
Data::NuclideProperties::atomicWeight;

%feature("autodoc", "atomicWeightRatio(NuclideProperties self) -> double")
Data::NuclideProperties::atomicWeightRatio;

// Docstrings for getDataEvaluationTempsInMeV
%feature("autodoc", "getDataEvaluationTempsInMeV(NuclideProperties self, const NuclearDataProperties::FileType file_type, const unsigned table_major_version) ->  std::vector<Energy>")
Data::NuclideProperties::getDataEvaluationTempsInMeV;

%feature("autodoc", "getAdjointDataEvaluationTempsInMeV(NuclideProperties self, const AdjointNuclearDataProperties::FileType file_type, const unsigned table_major_version) ->  std::vector<Energy>")
Data::NuclideProperties::getAdjointDataEvaluationTempsInMeV;

%feature("autodoc", "getDataEvaluationTempsInMeV(NuclideProperties self, const std::string& name, const NuclearDataProperties::FileType file_type, const unsigned table_major_version) ->  std::vector<Energy>")
Data::NuclideProperties::getDataEvaluationTempsInMeV;

%feature("autodoc", "getAdjointDataEvaluationTempsInMeV(NuclideProperties self, const std::string& name, const AdjointNuclearDataProperties::FileType file_type, const unsigned table_major_version) ->  std::vector<Energy>")
Data::NuclideProperties::getAdjointDataEvaluationTempsInMeV;

// Docstrings for getDataEvaluationTemps
%feature("autodoc", "getDataEvaluationTemps(NuclideProperties self, const NuclearDataProperties::FileType file_type, const unsigned table_major_version) ->  std::vector<Temperature>")
Data::NuclideProperties::getDataEvaluationTemps;

%feature("autodoc", "getAdjointDataEvaluationTemps(NuclideProperties self, const AdjointNuclearDataProperties::FileType file_type, const unsigned table_major_version) ->  std::vector<Temperature>")
Data::NuclideProperties::getAdjointDataEvaluationTemps;

%feature("autodoc", "getDataEvaluationTemps(NuclideProperties self, const std::string& name, const NuclearDataProperties::FileType file_type, const unsigned table_major_version) ->  std::vector<Temperature>")
Data::NuclideProperties::getDataEvaluationTemps;

%feature("autodoc", "getAdjointDataEvaluationTemps(NuclideProperties self, const std::string& name, const AdjointNuclearDataProperties::FileType file_type, const unsigned table_major_version) ->  std::vector<Temperature>")
Data::NuclideProperties::getAdjointDataEvaluationTemps;

// Docstrings for getDataFileTypes
%feature("autodoc", "getNuclearDataFileTypes(NuclideProperties self) ->  std::set<NuclearDataProperties::FileType>")
Data::NuclideProperties::getNuclearDataFileTypes;

%feature("autodoc", "getAdjointNuclearDataFileTypes(NuclideProperties self) -> std::set<AdjointNuclearDataProperties::FileType>")
Data::NuclideProperties::getAdjointNuclearDataFileTypes;

%feature("autodoc", "getThermalNuclearDataFileTypes(NuclideProperties self, const std::string& name) -> std::set<ThermalNuclearDataProperties::FileType>")
Data::NuclideProperties::getThermalNuclearDataFileTypes;

%feature("autodoc", "getAdjointThermalNuclearDataFileTypes(NuclideProperties self, const std::string& name) -> std::set<AdjointThermalNuclearDataProperties::FileType>")
Data::NuclideProperties::getAdjointThermalNuclearDataFileTypes;

// Allow shared pointers of NuclideProperties objects
%shared_ptr( Data::NuclideProperties );

%rename_data_file_version( Photonuclear, NuclideProperties )
%rename_data_file_version( AdjointPhotonuclear, NuclideProperties )
%rename_nuclide_data_functions( Nuclear, nuclear )
%rename_nuclide_data_functions( AdjointNuclear, adjointNuclear )
%rename_thermal_nuclide_data_functions( ThermalNuclear, thermalNuclear )
%rename_thermal_nuclide_data_functions( AdjointThermalNuclear, adjointThermalNuclear )

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

// Add typemaps for converting AtomicWeight to and from Python float
%apply const Data::PhotonuclearDataProperties::AtomicWeight {
  const Data::NuclideProperties::AtomicWeight }
%apply Data::PhotonuclearDataProperties::AtomicWeight {
  Data::NuclideProperties::AtomicWeight }

// Add general templates
%typemap(out) std::vector<Data::NuclideProperties::Energy> {
  %append_output(PyFrensie::convertToPython( std::vector<double>( Utility::reinterpretAsRaw( $1.data() ), Utility::reinterpretAsRaw( $1.data()+$1.size() ) ) ));
}

%typemap(out) std::vector<Data::NuclideProperties::Temperature> {
  %append_output(PyFrensie::convertToPython( std::vector<double>( Utility::reinterpretAsRaw( $1.data() ), Utility::reinterpretAsRaw( $1.data()+$1.size() ) ) ));
}


// Import the NuclideProperties
%include "Data_NuclideProperties.hpp"

//---------------------------------------------------------------------------//
// end Data_NuclideProperties.i
//---------------------------------------------------------------------------//e
