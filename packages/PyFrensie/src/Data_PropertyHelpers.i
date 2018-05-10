//---------------------------------------------------------------------------//
//!
//! \file   Data_PropertyHelpers.i
//! \author Luke Kersting
//! \brief  The data property helper macros
//!
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic properties class python interface
//---------------------------------------------------------------------------//
%define %basic_properties_setup_helper( PROPERTIES )

// Allow shared pointers of PROPERTIES objects
%shared_ptr(Data::PROPERTIES);

%feature("autodoc", "fileType(PROPERTIES self) -> FileType")
Data::PROPERTIES::fileType;

%feature("autodoc", "filePath(PROPERTIES self) -> string")
Data::PROPERTIES::filePath;

%feature("autodoc", "fileStartLine(PROPERTIES self) -> size_t")
Data::PROPERTIES::fileStartLine;

%feature("autodoc", "fileVersion(PROPERTIES self) -> unsigned")
Data::PROPERTIES::fileVersion;

%feature("autodoc", "tableName(PROPERTIES self) -> string")
Data::PROPERTIES::tableName;

%feature("autodoc", "clone(PROPERTIES self) -> PROPERTIES*")
Data::PROPERTIES::clone;

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up an Atomic properties class python interface
//---------------------------------------------------------------------------//
%define %atomic_properties_setup_helper( PROPERTIES )

%feature("docstring") Data::PROPERTIES
"The PROPERTIES class stores a atomic data properties. It can be used for
querying atomic data properties and for creating atomic data extractors or
container, which can be used to read atomic data."

%feature("autodoc", "atom(PROPERTIES self) -> AtomType")
Data::PROPERTIES::atom;

%feature("autodoc", "atomicNumber(PROPERTIES self) -> unsigned")
Data::PROPERTIES::atomicNumber;

%feature("autodoc", "atomicWeight(PROPERTIES self) -> AtomicWeight")
Data::PROPERTIES::atomicWeight;

%basic_properties_setup_helper( PROPERTIES )

// // Add std::set templates for FileType
// %template(PROPERTIES ## Set) std::set< Data::PROPERTIES::FileType >;

// Add typemaps for converting AtomicWeight to and from Python float
%typemap(in) const Data::PROPERTIES::AtomicWeight {
  $1 = Data::PROPERTIES::AtomicWeight::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Data::PROPERTIES::AtomicWeight {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Data::PROPERTIES::AtomicWeight) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up an Nuclide properties class python interface
//---------------------------------------------------------------------------//
%define %nuclide_properties_setup_helper( PROPERTIES )

%feature("docstring") Data::PROPERTIES
"The PROPERTIES class stores nuclear data properties. It can be used for
querying nuclear data properties and for creating nuclear data extractors or
container, which can be used to read nuclear data."

%feature("autodoc", "evaluationTemperatureInMeV(PROPERTIES self) -> Energy")
Data::PROPERTIES::evaluationTemperatureInMeV;

%feature("autodoc", "evaluationTemperature(PROPERTIES self) -> Temperature")
Data::PROPERTIES::evaluationTemperature;

%feature("autodoc", "fileMajorVersion(PROPERTIES self) -> unsigned")
Data::PROPERTIES::fileMajorVersion;

%basic_properties_setup_helper( PROPERTIES )

// // Add std::set template for FileType
// %template(PROPERTIES ## Set) std::set< Data::PROPERTIES::FileType >;

// Add typemaps for converting Energy to and from Python float
%typemap(in) const Data::PROPERTIES::Energy {
  $1 = Data::PROPERTIES::Energy::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Data::PROPERTIES::Energy {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Data::PROPERTIES::Energy) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

// Add typemaps for converting Temperature to and from Python float
%typemap(in) const Data::PROPERTIES::Temperature {
  $1 = Data::PROPERTIES::Temperature::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Data::PROPERTIES::Temperature {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Data::PROPERTIES::Temperature) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

%enddef

//---------------------------------------------------------------------------//
// Macro for renaming the getDataFileVersions function
//---------------------------------------------------------------------------//
%define %rename_data_file_version( BASE_NAME, BASE_TYPE )

%feature("autodoc", "get ## BASE_NAME ## DataFileVersions(BASE_TYPE self, const BASE_NAME ## DataProperties::FileType file_type) -> std::set<unsigned>")
Data::BASE_TYPE::get ## BASE_NAME ## DataFileVersions;

// Rename the overloaded getDataFileVersions functions
%rename(get ## BASE_NAME ## DataFileVersions) Data::BASE_TYPE::getDataFileVersions(
  const BASE_NAME ## DataProperties::FileType file_type ) const;

%feature("autodoc", "getRecommended ## BASE_NAME ## DataFileVersion(BASE_TYPE self, const BASE_NAME ## DataProperties::FileType file_type) -> unsigned")
Data::BASE_TYPE::getRecommended ## BASE_NAME ## DataFileVersion;

// Rename the overloaded getRecommendedDataFileVersion functions
%rename(getRecommended ## BASE_NAME ## DataFileVersion) Data::BASE_TYPE::getRecommendedDataFileVersion(
  const BASE_NAME ## DataProperties::FileType file_type ) const;

%enddef

//---------------------------------------------------------------------------//
// Macro for renaming nuclide data functions
//---------------------------------------------------------------------------//
%define %rename_nuclide_data_functions( BASE_NAME, baseName )

%feature("autodoc", "baseName ## DataAvailable(NuclideProperties self, const BASE_NAME ## DataProperties::FileType file_type) -> bool,
baseName ## DataAvailable(NuclideProperties self, const BASE_NAME ## DataProperties::FileType file_type, const unsigned table_major_version) -> bool,
baseName ## DataAvailable(NuclideProperties self, const BASE_NAME ## DataProperties::FileType file_type, const unsigned table_major_version, const Temperature evaluation_temp) -> bool")
Data::NuclideProperties::baseName ## DataAvailable;

%feature("autodoc", "baseName ## DataAvailableAtMeV(NuclideProperties self, const BASE_NAME ## DataProperties::FileType file_type, const unsigned table_major_version, const Energy evaluation_temp) -> bool")
Data::NuclideProperties::baseName ## DataAvailableAtMeV;

// Rename the overloaded baseName ## DataAvailable functions
%rename(baseName ## DataAvailableAtMeV) Data::NuclideProperties::baseName ## DataAvailable(
  const BASE_NAME ## DataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp ) const;

%feature("autodoc", "get ## BASE_NAME ## DataProperties(NuclideProperties self, const BASE_NAME ## DataProperties::FileType file_type, const unsigned table_major_version, const Temperature evaluation_temp, const bool find_exact) -> const BASE_NAME ## DataProperties")
Data::NuclideProperties::get ## BASE_NAME ## DataProperties;

%feature("autodoc", "get ## BASE_NAME ## DataPropertiesAtMeV(NuclideProperties self, const BASE_NAME ## DataProperties::FileType file_type, const unsigned table_major_version, const Energy evaluation_temp, const bool find_exact) -> const BASE_NAME ## DataProperties")
Data::NuclideProperties::get ## BASE_NAME ## DataPropertiesAtMeV;

// Rename the overloaded get ## BASE_NAME ## DataProperties function
%rename(get ## BASE_NAME ## DataPropertiesAtMeV) get ## BASE_NAME ## DataProperties(
  const BASE_NAME ## DataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

%feature("autodoc", "getShared ## BASE_NAME ## DataProperties(NuclideProperties self, const BASE_NAME ## DataProperties::FileType file_type, const unsigned table_major_version, const Temperature evaluation_temp, const bool find_exact) -> std::shared_ptr<const BASE_NAME ## DataProperties>&")
Data::NuclideProperties::getShared ## BASE_NAME ## DataProperties;

%feature("autodoc", "getShared ## BASE_NAME ## DataPropertiesAtMeV(NuclideProperties self, const BASE_NAME ## DataProperties::FileType file_type, const unsigned table_major_version, const Energy evaluation_temp, const bool find_exact) -> const std::shared_ptr<const BASE_NAME ## DataProperties>&")
Data::NuclideProperties::getShared ## BASE_NAME ## DataPropertiesAtMeV;

// Rename the overloaded getShared ## BASE_NAME ## DataProperties function
%rename(getShared ## BASE_NAME ## DataPropertiesAtMeV) getShared ## BASE_NAME ## DataProperties(
  const BASE_NAME ## DataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

// Rename the overloaded getDataFileVersions functions
%rename_data_file_version( BASE_NAME, NuclideProperties )

%enddef

//---------------------------------------------------------------------------//
// Macro for renaming thermal nuclide data functions
//---------------------------------------------------------------------------//
%define %rename_thermal_nuclide_data_functions( BASE_NAME, baseName )

// Rename the overloaded baseName ## DataAvailable functions
%rename(baseName ## DataAvailableAtMeV) Data::NuclideProperties::baseName ## DataAvailable(
  const std::string& name,
  const BASE_NAME ## DataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp ) const;

// Rename the overloaded getNuclearDataProperties function
%rename(get ## BASE_NAME ## DataPropertiesAtMeV) get ## BASE_NAME ## DataProperties(
  const std::string& name,
  const  BASE_NAME ## DataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

// Rename the overloaded getShared ## BASE_NAME ## DataProperties function
%rename( getShared ## BASE_NAME ## DataPropertiesAtMeV) getShared ## BASE_NAME ## DataProperties(
  const std::string& name,
  const BASE_NAME ## DataProperties::FileType file_type,
  const unsigned table_major_version,
  const Energy evaluation_temp,
  const bool find_exact ) const;

// Rename the overloaded getDataFileVersions functions
%rename(get ## BASE_NAME ## DataFileVersions) Data::NuclideProperties::getDataFileVersions(
  const std::string& name,
  const BASE_NAME ## DataProperties::FileType file_type ) const;

// Rename the overloaded getRecommendedDataFileVersion functions
%rename(getRecommended ## BASE_NAME ## DataFileVersion) Data::NuclideProperties::getRecommendedDataFileVersion(
  const std::string& name,
  const BASE_NAME ## DataProperties::FileType file_type ) const;

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic data property class python interface
//---------------------------------------------------------------------------//
%define %basic_properties_interface_setup( PROPERTIES )

// Set up the basic data properties interface
%basic_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a atomic data property class python interface
//---------------------------------------------------------------------------//
%define %atomic_properties_interface_setup( PROPERTIES )

// Set up the basic data properties interface
%atomic_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a nuclear data property class python interface
//---------------------------------------------------------------------------//
%define %nuclear_properties_interface_setup( PROPERTIES )

// Set up the basic data properties interface
%nuclide_properties_setup_helper( PROPERTIES )

%feature("autodoc", "zaid(PROPERTIES self) -> ZAID")
Data::PROPERTIES::zaid;

%feature("autodoc", "atomicWeightRatio(PROPERTIES self) -> unsigned")
Data::PROPERTIES::atomicWeightRatio;

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a thermal nuclear data property class python interface
//---------------------------------------------------------------------------//
%define %thermal_nuclear_properties_interface_setup( PROPERTIES )

// Set up the basic data properties interface
%nuclide_properties_setup_helper( PROPERTIES )

%feature("autodoc", "name(PROPERTIES self) -> std::string")
Data::ThermalNuclearDataProperties::name;

%feature("autodoc", "hasDataForZAID(PROPERTIES self, const Data::ZAID& zaid) -> bool")
Data::ThermalNuclearDataProperties::hasDataForZAID;

%feature("autodoc", "zaids(PROPERTIES self) -> std::set<Data::ZAID>")
Data::ThermalNuclearDataProperties::zaids;

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a photonuclear data property class python interface
//---------------------------------------------------------------------------//
%define %photonuclear_properties_interface_setup( PROPERTIES )

// Add a more detailed docstring
%feature("docstring") Data::PROPERTIES
"The PROPERTIES class stores photonuclear data properties.
It can be used for querying photonuclear data properties and for creating
photonuclear data extractors or container, which can be used to read
photonuclear data."

// Use helper interface setup
%basic_properties_interface_setup(PROPERTIES);

%feature("autodoc", "zaid(PROPERTIES self) -> ZAID")
Data::PROPERTIES::zaid;

%feature("autodoc", "atomicWeight(PROPERTIES self) -> AtomicWeight")
Data::PROPERTIES::atomicWeight;

// Add typemaps for converting AtomicWeight to and from Python float
%typemap(in) const Data::PROPERTIES::AtomicWeight {
  $1 = Data::PROPERTIES::AtomicWeight::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Data::PROPERTIES::AtomicWeight {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Data::PROPERTIES::AtomicWeight) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a adjoint photonuclear data property class python interface
//---------------------------------------------------------------------------//
%define %adjoint_photonuclear_properties_interface_setup( PROPERTIES )

// Add a more detailed docstring
%feature("docstring") Data::PROPERTIES
"The PROPERTIES class stores adjoint photonuclear data
properties. It can be used for querying adjoint photonuclear data properties
and for creating adjoint photonuclear data extractors or container, which can be
used to read adjoint photonuclear data."

// Use helper interface setup
%basic_properties_interface_setup(PROPERTIES);

%feature("autodoc", "zaid(PROPERTIES self) -> ZAID")
Data::PROPERTIES::zaid;

%feature("autodoc", "atomicWeight(PROPERTIES self) -> AtomicWeight")
Data::PROPERTIES::atomicWeight;

%apply const Data::PhotonuclearDataProperties::AtomicWeight {
  const Data::PROPERTIES::AtomicWeight }

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up an atom properties class interface
//---------------------------------------------------------------------------//
%define %atom_properties_interface_setup( BASE_NAME, baseName )

%feature("autodoc", "baseName ## DataAvailable(AtomProperties self, const BASE_NAME ## DataProperties::FileType file_type) -> bool,
baseName ## DataAvailable(AtomProperties self, const BASE_NAME ## DataProperties::FileType file_type, const unsigned table_version) -> bool")
Data::AtomProperties::baseName ## DataAvailable;

%feature("autodoc", "get ## BASE_NAME ## DataFileTypes(AtomProperties self) ->  std::set<BASE_NAME ## DataProperties::FileType>")
Data::AtomProperties::getNuclearDataFileTypes;

%feature("autodoc", "get ## BASE_NAME ## DataProperties(AtomProperties self, const BASE_NAME ## DataProperties::FileType file_type, const unsigned table_version) -> const BASE_NAME ## DataProperties&")
Data::AtomProperties::get ## BASE_NAME ## DataProperties;

%feature("autodoc", "getShared ## BASE_NAME ## DataProperties(AtomProperties self, const BASE_NAME ## DataProperties::FileType file_type, const unsigned table_version) -> std::shared_ptr<const BASE_NAME ## DataProperties>&")
Data::AtomProperties::getShared ## BASE_NAME ## DataProperties;

%feature("autodoc", "set ## BASE_NAME ## DataProperties(AtomProperties self, const BASE_NAME ## DataProperties::FileType file_type, const std::shared_ptr<const BASE_NAME ## DataProperties>& properties) -> void")
Data::AtomProperties::set ## BASE_NAME ## DataProperties;

// Rename the overloaded getDataFileVersions functions
%rename_data_file_version( BASE_NAME, AtomProperties )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a scattering center properties database class interface
//---------------------------------------------------------------------------//
%define %database_interface_setup( DATABASE )

%feature("docstring") Data::DATABASE
"The DATABASE class stores a database of nuclear and
atomic data. It can be used for loading/saving nuclide and atom data."

%feature("autodoc", "doAtomPropertiesExist(DATABASE self, const AtomType atom) -> bool,
doAtomPropertiesExist(DATABASE self, const Data::ZAID zaid) -> bool")
Data::DATABASE::doAtomPropertiesExist;

%feature("autodoc", "doNuclidePropertiesExist(DATABASE self, const Data::ZAID zaid) -> bool")
Data::DATABASE::doNuclidePropertiesExist;

%feature("autodoc", "removeAtomProperties(DATABASE self, const AtomType atom) -> void,
removeAtomProperties(DATABASE self, const Data::ZAID zaid) -> void")
Data::DATABASE::removeAtomProperties;

%feature("autodoc", "removeAtomProperties(DATABASE self, const Data::ZAID zaid) -> void")
Data::DATABASE::removeAtomProperties;

%feature("autodoc", "removeEmptyProperties(DATABASE self, const bool include_atom_properties = false) -> void")
Data::DATABASE::removeEmptyProperties;

%feature("autodoc", "getAtomProperties(DATABASE self, const AtomType atom) -> AtomProperties,
getAtomProperties(DATABASE self, const Data::ZAID zaid) -> AtomProperties")
Data::DATABASE::getAtomProperties;

%feature("autodoc", "initializeAtomProperties(DATABASE self, const AtomType atom, const double atomic_weight_ratio) -> AtomProperties,
initializeAtomProperties(DATABASE self, const Data::ZAID zaid, const double atomic_weight_ratio) -> AtomProperties")
Data::DATABASE::initializeAtomProperties;

%feature("autodoc", "initializeAtomPropertiesFromAtomicWeight(DATABASE self, const AtomType atom, const AtomProperties::AtomicWeight atomic_weight) -> AtomProperties,
initializeAtomPropertiesFromAtomicWeight(DATABASE self, const Data::ZAID zaid, const AtomProperties::AtomicWeight atomic_weight) -> AtomProperties")
Data::DATABASE::initializeAtomPropertiesFromAtomicWeight;

%feature("autodoc", "getNuclideProperties(DATABASE self, const Data::ZAID zaid) -> NuclideProperties")
Data::DATABASE::getNuclideProperties;

%feature("autodoc", "initializeNuclideProperties(DATABASE self, const Data::ZAID zaid, const double atomic_weight_ratio) -> NuclideProperties")
Data::DATABASE::initializeNuclideProperties;

%feature("autodoc", "initializeNuclidePropertiesFromAtomicWeight(DATABASE self, const Data::ZAID zaid, const NuclideProperties::AtomicWeight atomic_weight) -> NuclideProperties")
Data::DATABASE::initializeNuclidePropertiesFromAtomicWeight;

%feature("autodoc", "getNumberOfAtomProperties(DATABASE self) -> size_t")
Data::DATABASE::getNumberOfAtomProperties;

%feature("autodoc", "getNumberOfNuclideProperties(DATABASE self) -> size_t")
Data::DATABASE::getNumberOfNuclideProperties;

%feature("autodoc", "listAtoms(DATABASE self) -> std::cout")
Data::DATABASE::listAtoms;

%feature("autodoc", "listAtomsAsString(DATABASE self) -> std::cout")
Data::DATABASE::listAtomsAsString;

%feature("autodoc", "listZaidsAsString(DATABASE self) -> std::cout,
listZaidsAsString(DATABASE self, const AtomType atom) -> std::cout")
Data::DATABASE::listZaidsAsString;

%rename(initializeAtomPropertiesFromAtomicWeight) Data::DATABASE::initializeAtomProperties( const AtomType atom, const AtomProperties::AtomicWeight atomic_weight );

%rename(initializeAtomPropertiesFromAtomicWeight) Data::DATABASE::initializeAtomProperties( const Data::ZAID zaid, const AtomProperties::AtomicWeight atomic_weight );

%ignore Data::DATABASE::initializeNuclideProperties( const Data::ZAID zaid, const NuclideProperties::AtomicWeight atomic_weight );

%extend Data::DATABASE
{
  std::string Data::DATABASE::listAtomsAsString() const
  {
    std::ostringstream oss;

    $self->listAtoms( oss );
    return oss.str();
  }

  std::string Data::DATABASE::listZaidsAsString() const
  {
    std::ostringstream oss;

    $self->listZaids( oss );
    return oss.str();
  }

  std::string Data::DATABASE::listZaidsAsString( const AtomType atom ) const
  {
    std::ostringstream oss;

    $self->listZaids( atom, oss );
    return oss.str();
  }
}

%enddef

//---------------------------------------------------------------------------//
// end Data_PropertyHelpers.i
//---------------------------------------------------------------------------//