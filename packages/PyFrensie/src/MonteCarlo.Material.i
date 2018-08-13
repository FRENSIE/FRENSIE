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

%ignore *::operator <<;

//---------------------------------------------------------------------------//
// Add MonteCarlo_MaterialDefinitionDatabase support
//---------------------------------------------------------------------------//

%include "MonteCarlo_MaterialDefinitionDatabase.i"

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
