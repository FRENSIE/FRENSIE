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


// #include "MonteCarlo_Material.hpp"
// #include "MonteCarlo_AdjointMaterial.hpp"

#include "MonteCarlo_PhotonuclearReactionType.hpp"

#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_PhotonMaterial.hpp"
#include "MonteCarlo_AdjointPhotonMaterial.hpp"
#include "MonteCarlo_ElectronMaterial.hpp"
#include "MonteCarlo_AdjointElectronMaterial.hpp"
#include "MonteCarlo_PositronMaterial.hpp"

#include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ContractException.hpp"

// Declare typedef for the MaterialDefinitionArray
typedef MonteCarlo::MaterialDefinitionDatabase::MaterialDefinitionArray MaterialDefinitionArray;
// typedef MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet ScatteringCenterNameSet;
// typedef MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet MaterialIdSet;
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

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// Include the explicit template instantiation helpers
%include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"

// Simulation properties handling
// %import(module="PyFrensie.MonteCarlo") MonteCarlo_SimulationProperties.i

// // Atom properties handling
// %import(module="PyFrensie.Data") Data_AtomProperties.i

// // Nuclide properties handling
// %import(module="PyFrensie.Data") Data_NuclideProperties.i

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

// %template(MaterialDefinitionArrayPrivate) std::vector<std::pair<std::string,double> >;
// %template(MaterialIdDefinitionMap) std::map<size_t,std::vector<std::pair<std::string,double> > >;
// // %template(MaterialIdNameBimap) boost::bimap<size_t,std::string>;
// %template(MaterialDefinitionArray) std::vector<std::pair<std::string,double> >;
// %template(MaterialIdSet) std::set<size_t>;
// %template(ScatteringCenterNameSet) std::set<std::string>;
// // %template(MaterialDefinitionIterator) std::map<size_t,std::vector<std::pair<std::string,double>>>::const_iterator;
// typedef MaterialIdDefinitionMap::const_iterator MaterialDefinitionIterator;


// typedef std::vector<std::pair<std::string,double> > MaterialDefinitionArray;

//   typedef std::vector<std::pair<std::string,double> > MaterialDefinitionArrayPrivate;
//   typedef std::map<size_t,MaterialDefinitionArrayPrivate> MaterialIdDefinitionMap;
//   typedef boost::bimap<size_t,std::string> MaterialIdNameBimap;
//   typedef MaterialDefinitionArrayPrivate MaterialDefinitionArray;
  // typedef std::set<size_t> MaterialIdSet;
  // typedef MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet TESTSET;
  // typedef std::set<std::string> ScatteringCenterNameSet;
//   typedef MaterialIdDefinitionMap::const_iterator MaterialDefinitionIterator;

//---------------------------------------------------------------------------//
// Add MonteCarlo_MaterialDefinitionDatabase support
//---------------------------------------------------------------------------//

%template(DoubleVector) std::vector<double>;
%template(StringVector) std::vector<std::string>;
%template(StringSet) std::set<std::string>;
%template(UnsignedSet) std::set<unsigned int>;
// %template(SizeSet) std::set<size_t>;
%template(StringDoublePair) std::pair<std::string,double>;
%template(StringDoublePairArray) std::vector<std::pair<std::string,double> >;
// %shared_ptr(std::set<size_t>)

// %typemap(in) MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet& = std::set<size_t>;
// %typemap(out) std::set<size_t>& = std::set<size_t>;

// %shared_ptr(MonteCarlo::ScatteringCenterDefinition);

// Add typemaps for converting set<size_t> to and from Python set
%typemap(in) const std::set<size_t>& ( std::set<size_t> temp ){
  temp = PyFrensie::convertFromPython<std::set<size_t> >( $input );
  $1 = &temp;
}

%typemap(typecheck, precedence=SWIG_TYPECHECK_SET) (const std::set<size_t>&) {
  $1 = (PySet_Check($input)) ? 1 : 0;
}

// %clear MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet& INPUT;
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


// // Add typemaps for converting ScatteringCenterNameSet to and from Python set
// %typemap(in) MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet& ( std::set<std::string> temp ){

//   std::set<std::string> *ptr = (std::set<std::string> *)0;
//   int res = swig::asptr($input, &ptr);

//   if (!SWIG_IsOK(res)) {
//     SWIG_exception_fail(SWIG_ArgError(res), "argument " "1"" of type '" "std::set<std::string>& ""'");
//   }
//   if (!ptr) {
//     SWIG_exception_fail(SWIG_ValueError, "invalid null reference, argument " "1"" of type '" "std::set<std::string>& ""'");
//   }

//   $1 = ptr;
// }

// %typemap(argout) MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet& {
//   %append_output(swig::from( *$1 ) );
// }

// %typemap(out) MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet {
//   return swig::from( $1 );
// }

// %typemap(in,numinputs=0) MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet& ( std::set<std::string> temp ) "$1 = &temp;"

// %typemap(argout) MonteCarlo::MaterialDefinitionDatabase::ScatteringCenterNameSet& {
//   %append_output(PyFrensie::convertToPython( *$1 ));
// }

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

%include "MonteCarlo_MaterialDefinitionDatabase.hpp"
// %typemap(in) MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet& = std::set<size_t>;
// %typemap(in) std::set<size_t>& = std::set<size_t>;

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

  // MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet& MonteCarlo::MaterialDefinitionDatabase::getMaterialIds(std::set<size_t> material_ids) const
  // {
  //   $self->getMaterialIds(material_ids);
  //   return material_ids;
  // }
}

// // ---------------------------------------------------------------------------//
// // Add Material support
// // ---------------------------------------------------------------------------//

// %import "MonteCarlo_Material.hpp"

// // ---------------------------------------------------------------------------//
// // Add AdjointMaterial support
// // ---------------------------------------------------------------------------//

// %import "MonteCarlo_AdjointMaterial.hpp"

// ---------------------------------------------------------------------------//
// Add NeutronMaterial support
// ---------------------------------------------------------------------------//

%ignore MonteCarlo::NeutronMaterial::NeutronMaterial;

%include "MonteCarlo_NeutronMaterial.hpp"

//---------------------------------------------------------------------------//
// Add PhotonMaterial support
//---------------------------------------------------------------------------//

%ignore MonteCarlo::PhotonMaterial::PhotonMaterial;

%import "MonteCarlo_PhotonuclearReactionType.hpp"
%include "MonteCarlo_PhotonMaterial.hpp"

//---------------------------------------------------------------------------//
// Add AdjointPhotonMaterial support
//---------------------------------------------------------------------------//

%ignore MonteCarlo::AdjointPhotonMaterial::AdjointPhotonMaterial;

%include "MonteCarlo_AdjointPhotonMaterial.hpp"

//---------------------------------------------------------------------------//
// Add ElectronMaterial support
//---------------------------------------------------------------------------//

%include "MonteCarlo_ElectronMaterial.hpp"

//---------------------------------------------------------------------------//
// Add AdjointElectronMaterial support
//---------------------------------------------------------------------------//

%include "MonteCarlo_AdjointElectronMaterial.hpp"

//---------------------------------------------------------------------------//
// Add PositronMaterial support
//---------------------------------------------------------------------------//

%include "MonteCarlo_PositronMaterial.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo.Material.i
//---------------------------------------------------------------------------//
