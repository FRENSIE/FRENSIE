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
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Distribution constructor
template<PhaseSpaceDimension dimension>
SinglePhaseSpaceDimensionParticleResponseFunction<dimension>::SinglePhaseSpaceDimensionParticleResponseFunction(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  dimension_distribution )
  : d_dimension_response_distribution( dimension_distribution )
{
  // Make sure that the response distribution is valid
  testPrecondition( dimension_distribution.get() );
}

// Raw distribution constructor
template<PhaseSpaceDimension dimension>
SinglePhaseSpaceDimensionParticleResponseFunction<dimension>::SinglePhaseSpaceDimensionParticleResponseFunction(
                                   const std::vector<double> dimension_grid,
                                   const std::vector<double> response_values )
  : d_dimension_response_distribution( std::make_shared<Utility::TabularDistribution>( dimension_grid, response_values ) )
{ /* ... */ }

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
  return std::string("f(") + Utility::toString( dimension ) + ")";
}

// Serialize the particle response function
template<PhaseSpaceDimension dimension>
template<typename Archive>
void SinglePhaseSpaceDimensionParticleResponseFunction<dimension>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleResponseFunction );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_response_function );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MonteCarlo::XDimensionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MonteCarlo::YDimensionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MonteCarlo::ZDimensionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MonteCarlo::UDimensionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MonteCarlo::VDimensionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MonteCarlo::WDimensionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MonteCarlo::EnergyDimensionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MonteCarlo::TimeDimensionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MonteCarlo::WeightDimensionParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION> );

#endif // end MONTE_CARLO_SINGLE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
