//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSource.i
//! \author Luke Kersting
//! \brief  The ParticleSource classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"

#include "MonteCarlo_ParticleSourceComponent.hpp"
#include "MonteCarlo_StandardParticleSourceComponent.hpp"
#include "MonteCarlo_StandardAdjointParticleSourceComponent.hpp"
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "Utility_SerializationHelpers.hpp"

using namespace MonteCarlo;
%}

// Include std::string support
%include <std_string.i>

// Include typemaps support
%include <typemaps.i>

// C++ STL support
%include <std_vector.i>
%include <std_set.i>

// Import the PyFrensie_ArraySharedPtr.i
%include "PyFrensie_ArraySharedPtr.i"

// Geometry model handling
%import(module="PyFrensie.Geometry") Geometry_Navigator.hpp
%import(module="PyFrensie.Geometry") Geometry_Model.i
%import MonteCarlo_ParticleDistribution.i

// Add a few general typedefs
typedef unsigned long int uint64_t;
typedef unsigned int uint32_t;

// Add general template
%template(EntityIdVector) std::vector<long unsigned int>;
%template(EntityIdSet) std::set<long unsigned int>;

// ---------------------------------------------------------------------------//
// Add ParticleSourceComponentsupport
// ---------------------------------------------------------------------------//

// Add a typemap for CellIdSet starting_cells
%typemap(in,numinputs=0) MonteCarlo::ParticleSourceComponent::CellIdSet& starting_cells(MonteCarlo::ParticleSourceComponent::CellIdSet temp) "$1 = &temp;"

%typemap(argout) MonteCarlo::ParticleSourceComponent::CellIdSet& starting_cells {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%shared_ptr( MonteCarlo::ParticleSourceComponent )
%include "MonteCarlo_ParticleSourceComponent.hpp"

// ---------------------------------------------------------------------------//
// Add StandardParticleSourceComponent support
// ---------------------------------------------------------------------------//

// Pre-include helper macro for the StandardParticleSourceComponent class
%define %pre_particle_source_component_setup_helper( PARTICLE, RENAME )
  %pre_template_setup_helper( StandardParticleSourceComponent<MonteCarlo::PARTICLE ## State>, RENAME)
%enddef

// The standard neutron source component
%pre_particle_source_component_setup_helper( Neutron, StandardNeutronSourceComponent )

// The standard photon source component
%pre_particle_source_component_setup_helper( Photon, StandardPhotonSourceComponent )

// The standard electron source component
%pre_particle_source_component_setup_helper( Electron, StandardElectronSourceComponent )

// The standard positron source component
%pre_particle_source_component_setup_helper( Positron, StandardPositronSourceComponent )

// The standard adjoint photon source component (base type)
%pre_particle_source_component_setup_helper( AdjointPhoton, StandardAdjointPhotonSourceComponentBaseType )

// The standard adjoint electron source component (base type)
%pre_particle_source_component_setup_helper( AdjointElectron, StandardAdjointElectronSourceComponentBaseType )

%include "MonteCarlo_StandardParticleSourceComponent.hpp"

// Post-include helper macro for the StandardParticleSourceComponent class
%define %post_particle_source_component_setup_helper( PARTICLE, RENAME )
  %post_template_setup_helper( StandardParticleSourceComponent<MonteCarlo::PARTICLE ## State>, RENAME)
%enddef

// The standard neutron source component
%post_particle_source_component_setup_helper( Neutron, StandardNeutronSourceComponent )

// The standard photon source component
%post_particle_source_component_setup_helper( Photon, StandardPhotonSourceComponent )

// The standard electron source component
%post_particle_source_component_setup_helper( Electron, StandardElectronSourceComponent )

// The standard positron source component
%post_particle_source_component_setup_helper( Positron, StandardPositronSourceComponent )

// The standard adjoint photon source component (base type)
%post_particle_source_component_setup_helper( AdjointPhoton, StandardAdjointPhotonSourceComponentBaseType )

// The standard adjoint electron source component (base type)
%post_particle_source_component_setup_helper( AdjointElectron, StandardAdjointElectronSourceComponentBaseType )

// ---------------------------------------------------------------------------//
// Add StandardAdjointParticleSourceComponent support
// ---------------------------------------------------------------------------//

// Pre-include helper macro for the StandardAdjointParticleSourceComponent class
%define %pre_adjoint_particle_source_component_setup_helper( PARTICLE )
  %inline %{
    typedef MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::Adjoint ## PARTICLE ## State,MonteCarlo::Adjoint ## PARTICLE ## ProbeState> StandardAdjoint ## PARTICLE ## SourceComponent;
  %}
  %shared_ptr( MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::Adjoint ## PARTICLE ## State,MonteCarlo::Adjoint ## PARTICLE ## ProbeState> )
%enddef

// The standard adjoint photon source component
%pre_adjoint_particle_source_component_setup_helper( Photon )

// The standard adjoint electron source component
%pre_adjoint_particle_source_component_setup_helper( Electron )

%include "MonteCarlo_StandardAdjointParticleSourceComponent.hpp"

// Post-include helper macro for the StandardAdjointParticleSourceComponent class
%define %post_adjoint_particle_source_component_setup_helper( PARTICLE )
  %template( StandardAdjoint ## PARTICLE ## SourceComponent ) MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::Adjoint ## PARTICLE ## State,MonteCarlo::Adjoint ## PARTICLE ## ProbeState>;
%enddef

// The standard adjoint photon source component
%post_adjoint_particle_source_component_setup_helper( Photon )

// The standard adjoint electron source component
%post_adjoint_particle_source_component_setup_helper( Electron )

// ---------------------------------------------------------------------------//
// Add ParticleSource support
// ---------------------------------------------------------------------------//

// Apply a typemap for CellIdSet starting_cells
%apply MonteCarlo::ParticleSourceComponent::CellIdSet& starting_cells { MonteCarlo::ParticleSource::CellIdSet& starting_cells }

%shared_ptr( MonteCarlo::ParticleSource);
%include "MonteCarlo_ParticleSource.hpp"

// ---------------------------------------------------------------------------//
// Add StandardParticleSource support
// ---------------------------------------------------------------------------//

// Extend class constructor to take a list of shared pointers as a PyObject
%extend MonteCarlo::StandardParticleSource
{
  // Constructor
  StandardParticleSource( PyObject* raw_source_components )
  {
    std::vector<std::shared_ptr<MonteCarlo::ParticleSourceComponent> > source_components;

    bool conversion_success;

    CONVERT_PYOBJECT_TO_VECTOR_OF_BASE_SHARED_PTR( raw_source_components, source_components, SWIGTYPE_p_std__shared_ptrT_MonteCarlo__ParticleSourceComponent_t, conversion_success );

    if( conversion_success )
    {
      return new MonteCarlo::StandardParticleSource( source_components );
    }
    // SWIG will check for a NULL return type and throw an exception
    else
      return NULL;
  }
};

%shared_ptr( MonteCarlo::StandardParticleSource );
%include "MonteCarlo_StandardParticleSource.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSource.i
//---------------------------------------------------------------------------//
