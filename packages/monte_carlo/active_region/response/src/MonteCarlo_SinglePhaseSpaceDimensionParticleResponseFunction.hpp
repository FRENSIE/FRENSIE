//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Single phase-space dimension particle response function class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SINGLE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_SINGLE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleResponseFunction.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace MonteCarlo{

//! The single phase-space dimension particle response function
template<PhaseSpaceDimension dimension>
class SinglePhaseSpaceDimensionParticleResponseFunction : public ParticleResponseFunction
{

public:

  //! Constructor
  SinglePhaseSpaceDimensionParticleResponseFunction(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  dimension_distribution );

  //! Destructor
  ~SinglePhaseSpaceDimensionParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

  //! Get a description of the response function
  std::string description() const final override;

private:

  //! Default constructor
  SinglePhaseSpaceDimensionParticleResponseFunction()
  { /* ... */ }

  // Serialize the particle response function
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The dimension distribution
  std::shared_ptr<const Utility::UnivariateDistribution>
  d_dimension_response_distribution;
};

//! The X position particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<PRIMARY_SPATIAL_DIMENSION> XPositionParticleResponseFunction;

//! The Y position particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<SECONDARY_SPATIAL_DIMENSION> YPositionParticleResponseFunction;

//! The Z position particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<TERTIARY_SPATIAL_DIMENSION> ZPositionParticleResponseFunction;

//! The X direction particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<PRIMARY_DIRECTIONAL_DIMENSION> XDirectionParticleResponseFunction;

//! The Y direction particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<SECONDARY_DIRECTIONAL_DIMENSION> YDirectionParticleResponseFunction;

//! The Z direction particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<TERTIARY_DIRECTIONAL_DIMENSION> ZDirectionParticleResponseFunction;

//! The energy dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<ENERGY_DIMENSION> EnergyParticleResponseFunction;

//! The time dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<TIME_DIMENSION> TimeParticleResponseFunction;

//! The weight dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<WEIGHT_DIMENSION> WeightParticleResponseFunction;

//! The energy dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<SOURCE_ENERGY_DIMENSION> SourceEnergyParticleResponseFunction;

//! The time dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<SOURCE_TIME_DIMENSION> SourceTimeParticleResponseFunction;

//! The weight dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<SOURCE_WEIGHT_DIMENSION> SourceWeightParticleResponseFunction;
  
} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_SINGLE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_VERSION( version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
      SinglePhaseSpaceDimensionParticleResponseFunction, MonteCarlo, version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( MonteCarlo::PhaseSpaceDimension Dim ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( Dim ) )

BOOST_SERIALIZATION_SINGLE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SINGLE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MontCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
