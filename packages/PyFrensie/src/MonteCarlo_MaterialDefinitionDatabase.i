//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialDefinitionDatabase.i
//! \author Luke Kersting
//! \brief  The MaterialDefinitionDatabase class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"

// Declare typedef for the MaterialDefinitionArray
typedef MonteCarlo::MaterialDefinitionDatabase::MaterialDefinitionArray MaterialDefinitionArray;

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>

%ignore *::MaterialDefinitionArrayPrivate;
%ignore *::MaterialIdDefinitionMap;
%ignore *::MaterialIdNameBimap;
%ignore *::MaterialDefinitionArray;
%ignore *::MaterialIdSet;
%ignore *::ScatteringCenterNameSet;
%ignore *::MaterialDefinitionIterator;
%ignore *::begin;
%ignore *::end;

//---------------------------------------------------------------------------//
// Add MonteCarlo_MaterialDefinitionDatabase support
//---------------------------------------------------------------------------//

// Add a more detailed docstring for the constructor
%feature("docstring")
MonteCarlo::MaterialDefinitionDatabase::MaterialDefinitionDatabase
"The MaterialDefinitionDatabase holds definitions of materials which
 can be used to access cross sectional data."

%feature("autodoc",
"doesDefinitionExist(RENAMED_DISTRIBUTION self, const std::string& name ) -> bool,
doesDefinitionExist(RENAMED_DISTRIBUTION self, const size_t material_id  ) -> bool" )
MonteCarlo::MaterialDefinitionDatabase::doesDefinitionExist;

%feature("autodoc",
"addDefinition(RENAMED_DISTRIBUTION self, const std::string& material_name, const size_t material_id, const MaterialDefinitionArray& material_components ),
addDefinition(RENAMED_DISTRIBUTION self, const size_t material_id, const MaterialDefinitionArray& material_components ),
addDefinition(RENAMED_DISTRIBUTION self, const std::string& material_name, const size_t material_id, const std::vector<std::string>& material_component_names, const std::vector<double>& material_component_fractions ),
addDefinition(RENAMED_DISTRIBUTION self, const size_t material_id, const std::vector<std::string>& material_component_names, const std::vector<double>& material_component_fractions )" )
MonteCarlo::MaterialDefinitionDatabase::addDefinition;

%feature("autodoc",
"getDefinition(RENAMED_DISTRIBUTION self, const std::string& material_name ) -> const MaterialDefinitionArray&,
getDefinition(RENAMED_DISTRIBUTION self, const size_t material_id  ) -> const MaterialDefinitionArray&" )
MonteCarlo::MaterialDefinitionDatabase::getDefinition;

%feature("autodoc",
"getMaterialId(RENAMED_DISTRIBUTION self, const std::string& material_name ) -> size_t" )
MonteCarlo::MaterialDefinitionDatabase::getMaterialId;

%feature("autodoc",
"getMaterialName(RENAMED_DISTRIBUTION self, const size_t material_id ) -> const std::string&" )
MonteCarlo::MaterialDefinitionDatabase::getMaterialName;

%feature("autodoc",
"removeDefinition(RENAMED_DISTRIBUTION self, const std::string& material_name ),
removeDefinition(RENAMED_DISTRIBUTION self, const size_t material_id )" )
MonteCarlo::MaterialDefinitionDatabase::removeDefinition;

%feature("autodoc",
"getMaterialIds(RENAMED_DISTRIBUTION self, MaterialIdSet& material_ids ) -> MaterialIdSet&,
getMaterialIds(RENAMED_DISTRIBUTION self ) -> MaterialIdSet" )
MonteCarlo::MaterialDefinitionDatabase::getMaterialIds;

%feature("autodoc",
"getUniqueScatteringCenterNames(RENAMED_DISTRIBUTION self, ScatteringCenterNameSet& scattering_center_names ) -> ScatteringCenterNameSet&,
getUniqueScatteringCenterNames(RENAMED_DISTRIBUTION self ) -> ScatteringCenterNameSet" )
MonteCarlo::MaterialDefinitionDatabase::getUniqueScatteringCenterNames;

%feature("autodoc",
"getUniqueScatteringCenterNamesFromIds(RENAMED_DISTRIBUTION self, const std::set<size_t>& material_ids, ScatteringCenterNameSet& scattering_center_names ) -> ScatteringCenterNameSet&,
getUniqueScatteringCenterNamesFromIds(RENAMED_DISTRIBUTION self, const std::set<size_t>& material_ids ) -> ScatteringCenterNameSet" )
MonteCarlo::MaterialDefinitionDatabase::getUniqueScatteringCenterNamesFromIds;

%template(DoubleVector) std::vector<double>;
%template(StringVector) std::vector<std::string>;
%template(StringSet) std::set<std::string>;
%template(UnsignedSet) std::set<unsigned int>;
%template(StringDoublePair) std::pair<std::string,double>;
%template(StringDoublePairArray) std::vector<std::pair<std::string,double> >;

// Add typemaps for converting set<size_t> to and from Python set
%typemap(in) const std::set<size_t>& ( std::set<size_t> temp ){
  temp = PyFrensie::convertFromPython<std::set<size_t> >( $input );
  $1 = &temp;
}

%typemap(typecheck, precedence=SWIG_TYPECHECK_SET) (const std::set<size_t>&) {
  $1 = (PySet_Check($input)) ? 1 : 0;
}

// Add typemaps for converting MaterialIdSet to and from Python set
%typemap(in) MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet& ( std::set<size_t> temp ){
  temp = PyFrensie::convertFromPython<std::set<size_t> >( $input );
  $1 = &temp;
}

%typemap(argout) MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet& {
  %append_output(PyFrensie::convertToPython<std::set<size_t> >( *$1 ) );
}

%typemap(out) MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet {
  return PyFrensie::convertToPython<std::set<size_t> >( $1 );
}

%typemap(typecheck, precedence=SWIG_TYPECHECK_SET) (MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet&) {
  $1 = (PySet_Check($input)) ? 1 : 0;
}

// Add typemaps for converting ScatteringCenterNameSet to and from Python set
%typemap(in) MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet& ( std::set<std::string> temp ){
  temp = PyFrensie::convertFromPython<std::set<std::string> >( $input );
  $1 = &temp;
}

%typemap(argout) MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet& {
  %append_output(PyFrensie::convertToPython<std::set<std::string> >( *$1 ) );
}

%typemap(out) MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet {
  return PyFrensie::convertToPython<std::set<std::string> >( $1 );
}

%typemap(typecheck, precedence=SWIG_TYPECHECK_SET) (MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet&) {
  $1 = (PySet_Check($input)) ? 1 : 0;
}

%shared_ptr(MonteCarlo::MaterialDefinitionDatabase)

%include "MonteCarlo_MaterialDefinitionDatabase.hpp"

%extend MonteCarlo::MaterialDefinitionDatabase
{
  // Get the unique scattering center names from the materials of interest
  void MonteCarlo::MaterialDefinitionDatabase::getUniqueScatteringCenterNamesFromIds(
    const std::set<size_t>& material_ids,
    MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet& scattering_center_names ) const
  {
    $self->getUniqueScatteringCenterNames( material_ids, scattering_center_names );
  }


  // Get the unique scattering center names from the materials of interest
  MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet getUniqueScatteringCenterNamesFromIds(
    const std::set<size_t>& material_ids ) const
  {
    return $self->getUniqueScatteringCenterNames( material_ids );
  }
}


// //---------------------------------------------------------------------------//
// // end MonteCarlo_MaterialDefinitionDatabase.i
// //---------------------------------------------------------------------------//
