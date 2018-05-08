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

// Import the explicit template instantiation helpers
%include "Data_ExplicitTemplateInstantiationMacros.hpp"

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

// // General ignore directives
// %ignore *::operator<<;

//---------------------------------------------------------------------------//
// Add support for the ZAID
//---------------------------------------------------------------------------//

// Add template for a std::set of ZAIDs
%template(ZaidSet) std::set<Data::ZAID>;

%rename(assign) Data::ZAID::operator=( const ZAID& that );
%rename(make_unsigned) Data::ZAID::operator unsigned() const;

// Import the ZAID
%include "Data_ZAID.hpp"

// // Add typemaps for converting a Python int to a ZAID
// %typemap(in) const Data::ZAID {
//   $1 = PyFrensie::convertFromPython<unsigned>( $input );
// }

// %typemap(typecheck, precedence=25) (const Data::ZAID) {
//   $1 = (PyInt_Check($input)) ? 1 : 0;
// }

//---------------------------------------------------------------------------//
// Add support for the NuclearDataProperties
//---------------------------------------------------------------------------//

// Import the NuclearDataProperties
%include "Data_NuclearDataProperties.hpp"

// Use helper interface setup
%nuclear_properties_interface_setup(NuclearDataProperties);

//---------------------------------------------------------------------------//
// Add support for the ThermalNuclearDataProperties
//---------------------------------------------------------------------------//

// Import the ThermalNuclearDataProperties
%include "Data_ThermalNuclearDataProperties.hpp"

// Use helper interface setup
%thermal_nuclear_properties_interface_setup(ThermalNuclearDataProperties);

//---------------------------------------------------------------------------//
// Add support for the AdjointNuclearDataProperties
//---------------------------------------------------------------------------//

// Import the AdjointNuclearDataProperties
%include "Data_AdjointNuclearDataProperties.hpp"

// Use helper interface setup
%nuclear_properties_interface_setup(AdjointNuclearDataProperties);

//---------------------------------------------------------------------------//
// Add support for the AdjointThermalNuclearDataProperties
//---------------------------------------------------------------------------//

// Import the AdjointThermalNuclearDataProperties
%include "Data_AdjointThermalNuclearDataProperties.hpp"

// Use helper interface setup
%thermal_nuclear_properties_interface_setup(AdjointThermalNuclearDataProperties);

//---------------------------------------------------------------------------//
// Add support for the PhotonuclearDataProperties
//---------------------------------------------------------------------------//

// Add a more detailed docstring
%feature("docstring") Data::PhotonuclearDataProperties
"The PhotonuclearDataProperties class stores photonuclear data properties.
It can be used for querying photonuclear data properties and for creating
photonuclear data extractors or container, which can be used to read
photonuclear data."

// Import the PhotonuclearDataProperties
%include "Data_PhotonuclearDataProperties.hpp"

// Use helper interface setup
%basic_properties_interface_setup(PhotonuclearDataProperties);

%feature("autodoc", "zaid(PhotonuclearDataProperties self) -> ZAID")
Data::PhotonuclearDataProperties::zaid;

%feature("autodoc", "atomicWeight(PhotonuclearDataProperties self) -> AtomicWeight")
Data::PhotonuclearDataProperties::atomicWeight;

// Add typemaps for converting AtomicWeight to and from Python float
%typemap(in) const Data::PhotonuclearDataProperties::AtomicWeight {
  $1 = Data::PhotonuclearDataProperties::AtomicWeight::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Data::PhotonuclearDataProperties::AtomicWeight {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Data::PhotonuclearDataProperties::AtomicWeight) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

//---------------------------------------------------------------------------//
// Add support for the AdjointPhotonuclearDataProperties
//---------------------------------------------------------------------------//

// Add a more detailed docstring
%feature("docstring") Data::AdjointPhotonuclearDataProperties
"The Adjoint PhotonuclearDataProperties class stores adjoint photonuclear data
properties. It can be used for querying adjoint photonuclear data properties
and for creating adjoint photonuclear data extractors or container, which can be
used to read adjoint photonuclear data."

// Use helper interface setup
%basic_properties_interface_setup(AdjointPhotonuclearDataProperties);

%feature("autodoc", "zaid(AdjointPhotonuclearDataProperties self) -> ZAID")
Data::AdjointPhotonuclearDataProperties::zaid;

%feature("autodoc", "atomicWeight(AdjointPhotonuclearDataProperties self) -> AtomicWeight")
Data::AdjointPhotonuclearDataProperties::atomicWeight;

%apply const Data::PhotonuclearDataProperties::AtomicWeight {
  const Data::AdjointPhotonuclearDataProperties::AtomicWeight }

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

// Import the NuclideProperties
%include "Data_NuclideProperties.hpp"

// Add general templates
%template(EnergyVector) std::vector<Data::NuclideProperties::Energy>;
%template(TemperatureVector) std::vector<Data::NuclideProperties::Temperature>;

//---------------------------------------------------------------------------//
// end Data_NuclideProperties.i
//---------------------------------------------------------------------------//e
