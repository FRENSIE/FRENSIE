//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.Material.i
//! \author Luke Kersting
//! \brief  The MonteCarlo.Material sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_material_docstring
"
PyFrensie.MonteCarlo.Material is the python interface to the FRENSIE Material
definitions in the monte_carlo/collision subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_material_docstring) Material

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"

#include "MonteCarlo_NuclearReactionType.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_AdjointPhotoatomicReactionType.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "MonteCarlo_PositronatomicReactionType.hpp"

#include "MonteCarlo_Nuclide.hpp"
#include "MonteCarlo_Material.hpp"
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_PhotonMaterial.hpp"
#include "MonteCarlo_ElectronMaterial.hpp"
#include "MonteCarlo_PositronMaterial.hpp"
#include "MonteCarlo_AdjointMaterial.hpp"
#include "MonteCarlo_AdjointPhotonMaterial.hpp"
#include "MonteCarlo_AdjointElectronMaterial.hpp"

#include "Utility_ToStringTraitsDecl.hpp"
#include "Utility_TypeTraitsDecl.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_DesignByContract.hpp"

// Declare typedef for the MaterialDefinitionArray
typedef MonteCarlo::MaterialDefinitionDatabase::MaterialDefinitionArray MaterialDefinitionArray;

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <std_string.i>
%include <std_vector.i>
%include <std_map.i>
%include <std_set.i>
%include <std_pair.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Import the TypeTraitsDecl
%import "Utility_TypeTraitsDecl.hpp"

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

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
  catch( std::runtime_error& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

// Global swig features
%feature("autodoc", "1");

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

// ---------------------------------------------------------------------------//
// Add ReactionType support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_NuclearReactionType.hpp"
%include "MonteCarlo_PhotonuclearReactionType.hpp"
%include "MonteCarlo_PhotoatomicReactionType.hpp"
%include "MonteCarlo_AdjointPhotoatomicReactionType.hpp"
%include "MonteCarlo_ElectroatomicReactionType.hpp"
%include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
%include "MonteCarlo_PositronatomicReactionType.hpp"

//---------------------------------------------------------------------------//
// Add Nuclide support
//---------------------------------------------------------------------------//

%include "MonteCarlo_Nuclide.hpp"

//---------------------------------------------------------------------------//
// Add MonteCarlo_Material support
//---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::Material<AdjointPhotoatom>)

%include "MonteCarlo_Material.hpp"

// The nuclide material template
%template( NulcideMaterial ) MonteCarlo::Material<MonteCarlo::Nuclide>;
// The photoatom material template
%template( PhotoatomMaterial ) MonteCarlo::Material<Photoatom>;
// The electroatom material template
%template( ElectroatomMaterial ) MonteCarlo::Material<Electroatom>;
// The positronatom material template
%template( PositronatomMaterial ) MonteCarlo::Material<Positronatom>;

//---------------------------------------------------------------------------//
// Add particle specific material support
//---------------------------------------------------------------------------//

// Support for NeutronMaterial
%include "MonteCarlo_NeutronMaterial.hpp"

// Support for PhotonMaterial
%extend MonteCarlo::PhotonMaterial
{
  typedef MonteCarlo::PhotoatomicReactionType ReactionEnumType;
}

%include "MonteCarlo_PhotonMaterial.hpp"

// Support for ElectronMaterial
%extend MonteCarlo::ElectronMaterial
{
  typedef MonteCarlo::ElectroatomicReactionType ReactionEnumType;
}

%include "MonteCarlo_ElectronMaterial.hpp"

// Support for PositronMaterial
%extend MonteCarlo::PositronMaterial
{
  typedef MonteCarlo::PositronatomicReactionType ReactionEnumType;
}

%include "MonteCarlo_PositronMaterial.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo.Material.i
//---------------------------------------------------------------------------//
