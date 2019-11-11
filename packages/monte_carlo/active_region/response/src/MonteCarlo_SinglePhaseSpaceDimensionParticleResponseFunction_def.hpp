//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Single phase-space dimension particle response function class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SINGLE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_DEF_HPP
#define MONTE_CARLO_SINGLE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Distribution constructor
/*! \details The dimension response distribution must be continuous.
 */
template<PhaseSpaceDimension dimension>
SinglePhaseSpaceDimensionParticleResponseFunction<dimension>::SinglePhaseSpaceDimensionParticleResponseFunction(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  dimension_distribution )
  : d_dimension_response_distribution( dimension_distribution )
{
  // Make sure that the response distribution pointer is valid
  testPrecondition( dimension_distribution.get() );

  // // Make sure that the response distribution is valid
  // TEST_FOR_EXCEPTION( !dimension_distribution->isContinuous(),
  //                     std::runtime_error,
  //                     "The dimension response distribution must be "
  //                     "continuous!" );
}

// Evaluate the response function at the desired phase space point
template<PhaseSpaceDimension dimension>
double SinglePhaseSpaceDimensionParticleResponseFunction<dimension>::evaluate( const ParticleState& particle ) const
{
  return d_dimension_response_distribution->evaluate(
                            MonteCarlo::getCoordinate<dimension>( particle ) );
}

// Check if the response function is spatially uniform
template<PhaseSpaceDimension dimension>
bool SinglePhaseSpaceDimensionParticleResponseFunction<dimension>::isSpatiallyUniform() const
{
  if( MonteCarlo::PhaseSpaceDimensionTraits<dimension>::getClass() !=
      SPATIAL_DIMENSION_CLASS )
    return true;
  else
  {
    if( d_dimension_response_distribution->getDistributionType() ==
        Utility::UNIFORM_DISTRIBUTION )
      return true;
    else
      return false;
  }
}

// Get a description of the response function
template<PhaseSpaceDimension dimension>
std::string SinglePhaseSpaceDimensionParticleResponseFunction<dimension>::description() const
{
  return std::string("f_custom(") + Utility::toString( dimension ) + ")";
}

// Serialize the particle response function
template<PhaseSpaceDimension dimension>
template<typename Archive>
void SinglePhaseSpaceDimensionParticleResponseFunction<dimension>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleResponseFunction );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_response_distribution );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( XPositionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( YPositionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ZPositionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( XDirectionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( YDirectionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ZDirectionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( EnergyParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TimeParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SourceEnergyParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SourceTimeParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SourceWeightParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_WEIGHT_DIMENSION> );

#endif // end MONTE_CARLO_SINGLE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
