//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleResponseFunction.i
//! \author Luke Kersting
//! \brief  The ParticleResponseFunction classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "MonteCarlo_ParticleResponseFunction.hpp"
// #include "MonteCarlo_ParticleResponseFunction.cpp"
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

// Collision definitions handling
// %import MonteCarlo.Collision.i
%import MonteCarlo.GeometryModel.i
// %import(module="PyFrensie.MonteCarlo") MonteCarlo.GeometryModel.i

// Helper macro for the pre setup
%define %pre_setup_helper( RESPONSE_FUNCTION, TEMPLATE_NAME )

  // The particle response function typedef
  %inline %{
  typedef RESPONSE_FUNCTION TEMPLATE_NAME;
  %}

  // The particle response function shared ptr
  %shared_ptr( RESPONSE_FUNCTION )

%enddef

// Helper macro for the post setup
%define %post_setup_helper( RESPONSE_FUNCTION, TEMPLATE_NAME )

  // The particle response function template
  %template( TEMPLATE_NAME ) RESPONSE_FUNCTION;

%enddef

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

// Primatives types like double cannot be extended directly, so a std::vector<double> is used instead.


// Add typemaps for converting float to Double
%typemap(in) Double ( double temp ){
  temp = PyFloat_AsDouble( $input );
  $1 = &temp;
}

%typemap(typecheck, precedence=1140) (Double) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

// %shared_ptr( MonteCarlo::FilledGeometryModel )

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
%pre_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>, XPositionParticleResponseFunction)
%pre_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>, YPositionParticleResponseFunction)
%pre_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>, ZPositionParticleResponseFunction)
%pre_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>, XDirectionParticleResponseFunction)
%pre_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>, YDirectionParticleResponseFunction)
%pre_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>, ZDirectionParticleResponseFunction)
%pre_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION>, EnergyParticleResponseFunction)
%pre_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION>, TimeParticleResponseFunction)
%pre_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION>, WeightParticleResponseFunction)

// (use template instantiation typedefs as python %template names)
%include "MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp"

// Extend the class to include arithmetic operators
%extend_setup_helper(MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction)

// The particle response functions (templates)
%post_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>, XPositionParticleResponseFunction)
%post_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>, YPositionParticleResponseFunction)
%post_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>, ZPositionParticleResponseFunction)
%post_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>, XDirectionParticleResponseFunction)
%post_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>, YDirectionParticleResponseFunction)
%post_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>, ZDirectionParticleResponseFunction)
%post_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION>, EnergyParticleResponseFunction)
%post_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION>, TimeParticleResponseFunction)
%post_setup_helper( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION>, WeightParticleResponseFunction)

// ---------------------------------------------------------------------------//
// Add FullPhaseSpaceParticleResponseFunction support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::FullPhaseSpaceParticleResponseFunction )
%include "MonteCarlo_FullPhaseSpaceParticleResponseFunction.hpp"

// ---------------------------------------------------------------------------//
// Add MaterialParticleResponseFunction support
// ---------------------------------------------------------------------------//

// The material particle response functions (typedefs and shared ptrs)
%pre_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial>, NeutronMaterialParticleResponseFunction)
%pre_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PhotonMaterial>, PhotonMaterialParticleResponseFunction)
%pre_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial>, ElectronMaterialParticleResponseFunction)
%pre_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PositronMaterial>, PositronMaterialParticleResponseFunction)
%pre_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial>, AdjointPhotonMaterialParticleResponseFunction)
%pre_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial>, AdjointElectronMaterialParticleResponseFunction)

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
%post_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial>, NeutronMaterialParticleResponseFunction)
%post_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PhotonMaterial>, PhotonMaterialParticleResponseFunction)
%post_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial>, ElectronMaterialParticleResponseFunction)
%post_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PositronMaterial>, PositronMaterialParticleResponseFunction)
%post_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial>, AdjointPhotonMaterialParticleResponseFunction)
%post_setup_helper( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial>, AdjointElectronMaterialParticleResponseFunction)

// ---------------------------------------------------------------------------//
// Add PhotonMaterialParticleResponseFunction support
// ---------------------------------------------------------------------------//
%include "MonteCarlo_PhotonMaterialParticleResponseFunction.hpp"

// ---------------------------------------------------------------------------//
// Add MaterialComponentParticleResponseFunction support
// ---------------------------------------------------------------------------//


// The material component particle response functions (typedefs and shared ptrs)
%pre_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::NeutronMaterial>, NeutronMaterialComponentParticleResponseFunction)
%pre_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::PhotonMaterial>, PhotonMaterialComponentParticleResponseFunction)
%pre_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::ElectronMaterial>, ElectronMaterialComponentParticleResponseFunction)
%pre_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::PositronMaterial>, PositronMaterialComponentParticleResponseFunction)
%pre_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial>, AdjointPhotonMaterialComponentParticleResponseFunction)
%pre_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointElectronMaterial>, AdjointElectronMaterialComponentParticleResponseFunction)

// (use template instantiation typedefs as python %template names)
%include "MonteCarlo_MaterialComponentParticleResponseFunction.hpp"

// Extend the class to include arithmetic operators
%extend_setup_helper(MonteCarlo::MaterialComponentParticleResponseFunction)

// The material particle response functions (templates)
%post_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::NeutronMaterial>, NeutronMaterialComponentParticleResponseFunction)
%post_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::PhotonMaterial>, PhotonMaterialComponentParticleResponseFunction)
%post_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::ElectronMaterial>, ElectronMaterialComponentParticleResponseFunction)
%post_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::PositronMaterial>, PositronMaterialComponentParticleResponseFunction)
%post_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial>, AdjointPhotonMaterialComponentParticleResponseFunction)
%post_setup_helper( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointElectronMaterial>, AdjointElectronMaterialComponentParticleResponseFunction)

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
