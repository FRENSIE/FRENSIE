//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.GeometryModel.i
//! \author Luke Kersting
//! \brief  The MonteCarlo.GeometryModel sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_geometry_model_docstring
"
PyFrensie.MonteCarlo.GeometryModel is the python interface to the FRENSIE
GeometryModel definitions in the monte_carlo/collision subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_geometry_model_docstring) GeometryModel

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Geometry_Model.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Geometry_AdvancedModel.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "MonteCarlo_StandardFilledParticleGeometryModel.hpp"
#include "MonteCarlo_StandardFilledAdjointParticleGeometryModel.hpp"
#include "MonteCarlo_FilledNeutronGeometryModel.hpp"
#include "MonteCarlo_FilledPhotonGeometryModel.hpp"
#include "MonteCarlo_FilledAdjointPhotonGeometryModel.hpp"
#include "MonteCarlo_FilledElectronGeometryModel.hpp"
#include "MonteCarlo_FilledAdjointElectronGeometryModel.hpp"
#include "MonteCarlo_FilledPositronGeometryModel.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_DesignByContract.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <std_string.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// Simulation properties handling
%import(module="PyFrensie.MonteCarlo") MonteCarlo_SimulationProperties.i

// ScatteringCenterDefinition definitions handling
%import(module="PyFrensie.MonteCarlo.Collision") MonteCarlo_ScatteringCenterDefinition.i

// Material definitions handling
%import(module="PyFrensie.MonteCarlo.Material")
MonteCarlo_MaterialDefinitionDatabase.i

// Geometry model handling
%import(module="PyFrensie.Geometry") Geometry_Model.i

// Array typenames
%import PyFrensie_Array.i

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

%ignore *::begin;
%ignore *::end;

// ---------------------------------------------------------------------------//
// Add StandardFilledParticleGeometryModel support
// ---------------------------------------------------------------------------//

%ignore MonteCarlo::StandardFilledParticleGeometryModel::getMacroscopicTotalForwardCrossSectionQuick;
%ignore MonteCarlo::StandardFilledParticleGeometryModel::getMacroscopicTotalForwardCrossSection;

// Add typemaps for converting EntityId to and from Python string
%typemap(in) const Geometry::Model::EntityId ( Geometry::Model::EntityId temp ){
  temp = PyInt_AsUnsignedLongMask( $input );
  $1 = temp;
}

%typemap(typecheck, precedence=70) (const Geometry::Model::EntityId) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

%import "MonteCarlo_StandardFilledParticleGeometryModel.hpp"

// Helper macro for templating the StandardFilledParticleGeometryModel
%define %standard_filled_particle_geometry_model_interface_setup( PARTICLE )

// Add a more detailed docstring
%feature("docstring")
MonteCarlo::StandardFilledParticleGeometryModel<PARTICLE ## Material>
"The StandardFilledParticleGeometryModel is templated on the particle material
 type. It is used as a base class for the Filled Geometry Model classes."

// Allow shared pointers of StandardFilledParticleGeometryModel objects
%shared_ptr( MonteCarlo::StandardFilledParticleGeometryModel<PARTICLE ## Material> );

%template(StandardFilledParticleGeometryModel_ ## PARTICLE ) MonteCarlo::StandardFilledParticleGeometryModel<PARTICLE ## Material>;

%extend MonteCarlo::StandardFilledParticleGeometryModel<PARTICLE ## Material>
{
  double MonteCarlo::StandardFilledParticleGeometryModel<PARTICLE ## Material>::get ## PARTICLE ## MacroscopicTotalForwardCrossSection(
      const Geometry::Model::EntityId cell,
      const double energy ) const
  {
    return $self->getMacroscopicTotalForwardCrossSection( cell, energy );
  }

  double MonteCarlo::StandardFilledParticleGeometryModel<PARTICLE ## Material>::get ## PARTICLE ## MacroscopicTotalForwardCrossSectionQuick(
      const Geometry::Model::EntityId cell,
      const double energy ) const
  {
    return $self->getMacroscopicTotalForwardCrossSectionQuick( cell, energy );
  }
}

%enddef

%standard_filled_particle_geometry_model_interface_setup( Neutron )
%standard_filled_particle_geometry_model_interface_setup( Photon )
%standard_filled_particle_geometry_model_interface_setup( AdjointPhoton )
%standard_filled_particle_geometry_model_interface_setup( Electron )
%standard_filled_particle_geometry_model_interface_setup( AdjointElectron )
%standard_filled_particle_geometry_model_interface_setup( Positron )

// ---------------------------------------------------------------------------//
// Add StandardFilledAdjointParticleGeometryModel support
// ---------------------------------------------------------------------------//

%typemap(out) const std::vector<double>& {
  %append_output(PyFrensie::convertToPython( *$1 ) );
}

%import "MonteCarlo_StandardFilledAdjointParticleGeometryModel.hpp"

// Helper macro for templating the StandardFilledAdjointParticleGeometryModel
%define %standard_filled_adjoint_particle_geometry_model_interface_setup( PARTICLE )

// Add a more detailed docstring
%feature("docstring")
MonteCarlo::StandardFilledAdjointParticleGeometryModel<PARTICLE ## Material>
"The StandardFilledAdjointParticleGeometryModel is templated on the adjoint
particle material type.
It is used as a base class for the Filled Geometry Model classes."

// Allow shared pointers of StandardFilledAdjointParticleGeometryModel objects
%shared_ptr( MonteCarlo::StandardFilledAdjointParticleGeometryModel<PARTICLE ## Material> );

%template(StandardFilledAdjointParticleGeometryModel_ ## PARTICLE ) MonteCarlo::StandardFilledAdjointParticleGeometryModel<PARTICLE ## Material>;

%enddef

%standard_filled_adjoint_particle_geometry_model_interface_setup( AdjointPhoton )
%standard_filled_adjoint_particle_geometry_model_interface_setup( AdjointElectron )

// ---------------------------------------------------------------------------//
// Add FilledNeutronGeometryModel support
// ---------------------------------------------------------------------------//

// Allow shared pointers of FilledNeutronGeometryModel objects
%shared_ptr( MonteCarlo::FilledNeutronGeometryModel );

%include "MonteCarlo_FilledNeutronGeometryModel.hpp"

//---------------------------------------------------------------------------//
// Add FilledPhotonGeometryModel support
//---------------------------------------------------------------------------//

// Allow shared pointers of FilledPhotonGeometryModel objects
%shared_ptr( MonteCarlo::FilledPhotonGeometryModel );

%include "MonteCarlo_FilledPhotonGeometryModel.hpp"

//---------------------------------------------------------------------------//
// Add FilledAdjointPhotonGeometryModel support
//---------------------------------------------------------------------------//

// Allow shared pointers of FilledAdjointPhotonGeometryModel objects
%shared_ptr( MonteCarlo::FilledAdjointPhotonGeometryModel );

%include "MonteCarlo_FilledAdjointPhotonGeometryModel.hpp"

//---------------------------------------------------------------------------//
// Add FilledElectronGeometryModel support
//---------------------------------------------------------------------------//

// Allow shared pointers of FilledElectronGeometryModel objects
%shared_ptr( MonteCarlo::FilledElectronGeometryModel );

%include "MonteCarlo_FilledElectronGeometryModel.hpp"

//---------------------------------------------------------------------------//
// Add FilledAdjointElectronGeometryModel support
//---------------------------------------------------------------------------//

// Allow shared pointers of FilledAdjointElectronGeometryModel objects
%shared_ptr( MonteCarlo::FilledAdjointElectronGeometryModel );

%include "MonteCarlo_FilledAdjointElectronGeometryModel.hpp"

//---------------------------------------------------------------------------//
// Add FilledPositronGeometryModel support
//---------------------------------------------------------------------------//

// Allow shared pointers of FilledPositronGeometryModel objects
%shared_ptr( MonteCarlo::FilledPositronGeometryModel );

%include "MonteCarlo_FilledPositronGeometryModel.hpp"

// ---------------------------------------------------------------------------//
// Add FilledGeometryModel support
// ---------------------------------------------------------------------------//

%ignore *::operator const Geometry::Model&() const;
%ignore *::operator std::shared_ptr<const Geometry::Model>() const;

// %ignore the templated version of isCellVoid
%ignore MonteCarlo::FilledGeometryModel::isCellVoid( const Geometry::Model::EntityId cell ) const;

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

// Allow shared pointers of FilledGeometryModel objects
%shared_ptr( MonteCarlo::FilledGeometryModel );

%include "MonteCarlo_FilledGeometryModel.hpp"

// Helper macro for templating the FilledGeometryModel
%define %filled_geometry_model_interface_setup( PARTICLE )

// Instantiate template versions of getMacroscopicTotalCrossSection
%template(get ## PARTICLE ## MacroscopicTotalCrossSection) MonteCarlo::FilledGeometryModel::getMacroscopicTotalCrossSection<MonteCarlo:: ## PARTICLE ## Material::ParticleStateType>;

// Instantiate template versions of getMacroscopicTotalCrossSectionQuick
%template(get ## PARTICLE ## MacroscopicTotalCrossSectionQuick) MonteCarlo::FilledGeometryModel::getMacroscopicTotalCrossSectionQuick<MonteCarlo:: ## PARTICLE ## Material::ParticleStateType>;

%enddef

%filled_geometry_model_interface_setup( Neutron )
%filled_geometry_model_interface_setup( Photon )
%filled_geometry_model_interface_setup( AdjointPhoton )
%filled_geometry_model_interface_setup( Electron )
%filled_geometry_model_interface_setup( AdjointElectron )
%filled_geometry_model_interface_setup( Positron )

// Helper macro for templating the adjoint FilledGeometryModel
%define %adjoint_filled_geometry_model_interface_setup( PARTICLE )

// Instantiate template versions of getAdjointWeightFactor
%template(getAdjoint ## PARTICLE ## WeightFactor) MonteCarlo::FilledGeometryModel::getAdjointWeightFactor<MonteCarlo::Adjoint ## PARTICLE ## Material::ParticleStateType>;

// Instantiate template versions of getAdjointWeightFactorQuick
%template(getAdjoint ## PARTICLE ## WeightFactorQuick) MonteCarlo::FilledGeometryModel::getAdjointWeightFactorQuick<MonteCarlo::Adjoint ## PARTICLE ## Material::ParticleStateType>;

%enddef

%adjoint_filled_geometry_model_interface_setup( Photon )
%adjoint_filled_geometry_model_interface_setup( Electron )

//---------------------------------------------------------------------------//
// end MonteCarlo.GeometryModel.i
//---------------------------------------------------------------------------//
