//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleResponse.i
//! \author Luke Kersting
//! \brief  The ParticleResponse classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "MonteCarlo_ParticleResponseFunction.hpp"
#include "MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp"
#include "MonteCarlo_FullPhaseSpaceParticleResponseFunction.hpp"
#include "MonteCarlo_MaterialParticleResponseFunction.hpp"
#include "MonteCarlo_PhotonMaterialParticleResponseFunction.hpp"
#include "MonteCarlo_MaterialComponentParticleResponseFunction.hpp"
#include "MonteCarlo_PhotonMaterialComponentParticleResponseFunction.hpp"

#include "MonteCarlo_ParticleResponse.hpp"
#include "MonteCarlo_StandardParticleResponse.hpp"

#include "Geometry_InfiniteMediumModel.hpp"
#include "Geometry_AdvancedModel.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"

#include "Utility_ToStringTraits.hpp"
#include "Utility_ToStringTraitsDecl.hpp"
#include "Utility_SerializationHelpers.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <std_vector.i>

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

// Material definitions handling
%import MonteCarlo.Material.i
// GeometryModel definitions handling
%import MonteCarlo.GeometryModel.i

// Helper macro for extending the class with arithmetic operators
%define %extend_setup_helper( RESPONSE_FUNCTION )

  %extend RESPONSE_FUNCTION
  {
    // Create a new response function from the addition of two response functions
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction> __add__(
          const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs )
    {
      return $self->getShared() + rhs;
    }

    // Create a new response function from the subtraction of two response functions
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction> __sub__(
          const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs )
    {
      return $self->getShared() - rhs;
    }

    // Create a new response function from the multiplication of two response functions
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction> __mul__(
          const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs )
    {
      return $self->getShared() * rhs;
    }

    // Create a new response function from the multiplication of a response function and a scalar
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction> __mul__(
          const double rhs )
    {
      return $self->getShared() * rhs;
    }

    // Create a new response function from the division of two response functions
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction> __div__(
          const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs )
    {
      return $self->getShared() / rhs;
    }

    // Create a new response function from the division of a response function and a scalar
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction> __div__(
        const double rhs )
    {
      return $self->getShared() / rhs;
    }
  }

%enddef

// ---------------------------------------------------------------------------//
// Add ParticleResponseFunction support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::ParticleResponseFunction )

// Rename the arithmetic operators
%rename(add) ::operator+(
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

%rename(subtract) ::operator-(
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

%rename(multiply) ::operator*(
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

%rename(multiply) ::operator*(
      const double lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

%rename(multiply) ::operator*(
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
      const double rhs );

%rename(divide) ::operator/(
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

%rename(divide) ::operator/(
      const double lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

%rename(divide) ::operator/(
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
      const double rhs );

%include "MonteCarlo_ParticleResponseFunction.hpp"

%extend_setup_helper( MonteCarlo::ParticleResponseFunction )

// ---------------------------------------------------------------------------//
// Add SinglePhaseSpaceDimensionParticleResponseFunction support
// ---------------------------------------------------------------------------//

// The particle response functions (typedefs and shared ptrs)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>, XPositionParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>, YPositionParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>, ZPositionParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>, XDirectionParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>, YDirectionParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>, ZDirectionParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION>, EnergyParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION>, TimeParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION>, WeightParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_ENERGY_DIMENSION>, SourceEnergyParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_TIME_DIMENSION>, SourceTimeParticleResponseFunction)
%pre_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_WEIGHT_DIMENSION>, SourceWeightParticleResponseFunction)

// (use template instantiation typedefs as python %template names)
%include "MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp"

// Extend the class to include arithmetic operators
%extend_setup_helper(MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction)

// The particle response functions (templates)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>, XPositionParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>, YPositionParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>, ZPositionParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>, XDirectionParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>, YDirectionParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>, ZDirectionParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION>, EnergyParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION>, TimeParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION>, WeightParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_ENERGY_DIMENSION>, SourceEnergyParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_TIME_DIMENSION>, SourceTimeParticleResponseFunction)
%post_template_setup_helper( SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_WEIGHT_DIMENSION>, SourceWeightParticleResponseFunction)

// ---------------------------------------------------------------------------//
// Add FullPhaseSpaceParticleResponseFunction support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::FullPhaseSpaceParticleResponseFunction )
%include "MonteCarlo_FullPhaseSpaceParticleResponseFunction.hpp"

// ---------------------------------------------------------------------------//
// Add MaterialParticleResponseFunction support
// ---------------------------------------------------------------------------//

// The material particle response functions (typedefs and shared ptrs)
%pre_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial>, NeutronMaterialParticleResponseFunction)
%pre_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::PhotonMaterial>, PhotonMaterialParticleResponseFunction)
%pre_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial>, ElectronMaterialParticleResponseFunction)
%pre_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::PositronMaterial>, PositronMaterialParticleResponseFunction)
%pre_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial>, AdjointPhotonMaterialParticleResponseFunction)
%pre_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial>, AdjointElectronMaterialParticleResponseFunction)

// Add typemaps for converting ReactionEnumType to AdjointPhotoatomicReactionType
%typemap(in) const MonteCarlo::AdjointPhotonMaterial::ReactionEnumType ( MonteCarlo::AdjointPhotoatomicReactionType temp ){
  temp = static_cast<MonteCarlo::AdjointPhotoatomicReactionType>(PyInt_AsLong($input) );

  $1 = temp;
}

%typemap(typecheck, precedence=70) (const MonteCarlo::AdjointPhotonMaterial::ReactionEnumType) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

// Add typemaps for converting ReactionEnumType to AdjointElectroatomicReactionType
%typemap(in) const MonteCarlo::AdjointElectronMaterial::ReactionEnumType ( MonteCarlo::AdjointElectroatomicReactionType temp ){
  temp = static_cast<MonteCarlo::AdjointElectroatomicReactionType>(PyInt_AsLong($input) );

  $1 = temp;
}

%typemap(typecheck, precedence=70) (const MonteCarlo::AdjointElectronMaterial::ReactionEnumType) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

// (use template instantiation typedefs as python %template names)
%include "MonteCarlo_MaterialParticleResponseFunction.hpp"

// Extend the class to include arithmetic operators
%extend_setup_helper(MonteCarlo::MaterialParticleResponseFunction)

// The material particle response functions (templates)
%post_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial>, NeutronMaterialParticleResponseFunction)
%post_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::PhotonMaterial>, PhotonMaterialParticleResponseFunction)
%post_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial>, ElectronMaterialParticleResponseFunction)
%post_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::PositronMaterial>, PositronMaterialParticleResponseFunction)
%post_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial>, AdjointPhotonMaterialParticleResponseFunction)
%post_template_setup_helper( MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial>, AdjointElectronMaterialParticleResponseFunction)

// ---------------------------------------------------------------------------//
// Add PhotonMaterialParticleResponseFunction support
// ---------------------------------------------------------------------------//
%include "MonteCarlo_PhotonMaterialParticleResponseFunction.hpp"

// ---------------------------------------------------------------------------//
// Add MaterialComponentParticleResponseFunction support
// ---------------------------------------------------------------------------//


// The material component particle response functions (typedefs and shared ptrs)
%pre_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::NeutronMaterial>, NeutronMaterialComponentParticleResponseFunction)
%pre_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::PhotonMaterial>, PhotonMaterialComponentParticleResponseFunction)
%pre_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::ElectronMaterial>, ElectronMaterialComponentParticleResponseFunction)
%pre_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::PositronMaterial>, PositronMaterialComponentParticleResponseFunction)
%pre_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial>, AdjointPhotonMaterialComponentParticleResponseFunction)
%pre_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::AdjointElectronMaterial>, AdjointElectronMaterialComponentParticleResponseFunction)

// (use template instantiation typedefs as python %template names)
%include "MonteCarlo_MaterialComponentParticleResponseFunction.hpp"

// Extend the class to include arithmetic operators
%extend_setup_helper(MonteCarlo::MaterialComponentParticleResponseFunction)

// The material particle response functions (templates)
%post_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::NeutronMaterial>, NeutronMaterialComponentParticleResponseFunction)
%post_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::PhotonMaterial>, PhotonMaterialComponentParticleResponseFunction)
%post_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::ElectronMaterial>, ElectronMaterialComponentParticleResponseFunction)
%post_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::PositronMaterial>, PositronMaterialComponentParticleResponseFunction)
%post_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial>, AdjointPhotonMaterialComponentParticleResponseFunction)
%post_template_setup_helper( MaterialComponentParticleResponseFunction<MonteCarlo::AdjointElectronMaterial>, AdjointElectronMaterialComponentParticleResponseFunction)

// ---------------------------------------------------------------------------//
// Add PhotonMaterialComponentParticleResponseFunction support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::PhotonMaterialComponentParticleResponseFunction )
%include "MonteCarlo_PhotonMaterialComponentParticleResponseFunction.hpp"

// ---------------------------------------------------------------------------//
// Add ParticleResponse support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::ParticleResponse )
%include "MonteCarlo_ParticleResponse.hpp"

// ---------------------------------------------------------------------------//
// Add StandardParticleResponse support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::StandardParticleResponse )
%include "MonteCarlo_StandardParticleResponse.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleResponse.i
//---------------------------------------------------------------------------//
