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
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace MonteCarlo{

//! The single phase-space dimension particle response function
template<PhaseSpaceDimension dimension>
class SinglePhaseSpaceDimensionParticleResponseFunction : public ParticleResponseFunction
{

public:

  //! Distribution constructor
  SinglePhaseSpaceDimensionParticleResponseFunction(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  dimension_distribution );

  //! Raw distribution constructor
  SinglePhaseSpaceDimensionParticleResponseFunction(
                                   const std::vector<double> dimension_grid,
                                   const std::vector<double> response_values );

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

//! The X dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<PRIMARY_SPATIAL_DIMENSION> XDimensionParticleResponseFunction;

//! The Y dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<SECONDARY_SPATIAL_DIMENSION> YDimensionParticleResponseFunction;

//! The Z dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<TERTIARY_SPATIAL_DIMENSION> ZDimensionParticleResponseFunction;

//! The U dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<PRIMARY_DIRECTIONAL_DIMENSION> UDimensionParticleResponseFunction;

//! The V dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<SECONDARY_DIRECTIONAL_DIMENSION> VDimensionParticleResponseFunction;

//! The W dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<TERTIARY_DIRECTIONAL_DIMENSION> WDimensionParticleResponseFunction;

//! The energy dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<ENERGY_DIMENSION> EnergyDimensionParticleResponseFunction;

//! The time dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<TIME_DIMENSION> TimeDimensionParticleResponseFunction;

//! The weight dimension particle response function
typedef SinglePhaseSpaceDimensionParticleResponseFunction<WEIGHT_DIMENSION> WeightDimensionParticleResponseFunction;
  
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
