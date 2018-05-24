//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Standard particle distribution template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_DISTRIBUTION_DEF_HPP

namespace MonteCarlo{

// Sample the particle state using the desired dimension sampling functor
template<typename DimensionSamplingFunctor>
inline void StandardParticleDistribution::sampleImpl(
                         DimensionSamplingFunctor& dimension_sampling_function,
                         ParticleState& particle ) const
{
  // Initialize a phase space point
  PhaseSpacePoint phase_space_sample( d_spatial_coord_conversion_policy,
                                      d_directional_coord_conversion_policy );

  // Sample the particle state
  DimensionSet::const_iterator
    indep_dimension_it = d_independent_dimensions.begin();

  // Sample independent dimensions first. We will have the sampling process
  // cascade from the independent dimensions down to all dependent dimensions
  while( indep_dimension_it != d_independent_dimensions.end() )
  {
    dimension_sampling_function(
                  *d_dimension_distributions.find(*indep_dimension_it)->second,
                  phase_space_sample );

    ++indep_dimension_it;
  }
  
  // Convert the sampled phase space point to a particle state. This will
  // use the spatial and directional conversion policies
  phase_space_sample.setParticleState( particle );
}

// Save the state to an archive
template<typename Archive>
void StandardParticleDistribution::save( Archive& ar, const unsigned version ) const
{
  // Save the base class member data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleDistribution );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_spatial_coord_conversion_policy );
  ar & BOOST_SERIALIZATION_NVP( d_directional_coord_conversion_policy );
  ar & BOOST_SERIALIZATION_NVP( d_independent_dimensions );
  ar & BOOST_SERIALIZATION_NVP( d_dimension_distributions );
  ar & BOOST_SERIALIZATION_NVP( d_ready );
}

// Load the data from an archive
template<typename Archive>
void StandardParticleDistribution::load( Archive& ar, const unsigned version )
{
  // Load the base class member data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleDistribution );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_spatial_coord_conversion_policy );
  ar & BOOST_SERIALIZATION_NVP( d_directional_coord_conversion_policy );
  ar & BOOST_SERIALIZATION_NVP( d_independent_dimensions );
  ar & BOOST_SERIALIZATION_NVP( d_dimension_distributions );
  ar & BOOST_SERIALIZATION_NVP( d_ready );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleDistribution_def.hpp
//---------------------------------------------------------------------------//
