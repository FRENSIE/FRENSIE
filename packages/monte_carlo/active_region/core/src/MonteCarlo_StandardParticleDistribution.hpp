//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleDistribution.hpp
//! \author Alex Robinson
//! \brief  Standard particle distribution declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_DISTRIBUTION_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_ParticleDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "Utility_SpatialCoordinateConversionPolicy.hpp"
#include "Utility_DirectionalCoordinateConversionPolicy.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The standard particle distribution class
class StandardParticleDistribution : public ParticleDistribution
{

private:

  // Typedef for scalar traits
  typedef Utility::QuantityTraits<double> QT;

  //! Typedef for the phase space dimension distribution map
  typedef std::map<PhaseSpaceDimension,std::shared_ptr<PhaseSpaceDimensionDistribution> > DimensionDistributionMap;

  // Typedef for the dimension sampling function
  typedef std::function<void(const PhaseSpaceDimensionDistribution&,PhaseSpacePoint&)> DimensionSamplingFunction;

public:

  //! Typedef for the phase space dimension set
  typedef std::set<PhaseSpaceDimension> DimensionSet;

  //! Basic Constructor
  StandardParticleDistribution( const size_t id, const std::string& name );
  
  //! Constructor
  StandardParticleDistribution(
   const size_t id,
   const std::string& name,
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy );

  //! Destructor
  ~StandardParticleDistribution()
  { /* ... */ }

  //! Set a dimension distribution
  void setDimensionDistribution(
                        const std::shared_ptr<PhaseSpaceDimensionDistribution>&
                        dimension_distribution );

  //! Construct the dimension distribution dependency tree
  void constructDimensionDistributionDependencyTree();

  //! Reset the distribution
  void reset();

  //! Return the dimension distribution type name
  std::string getDimensionDistributionTypeName(
                          const PhaseSpaceDimension dimension ) const override;

  //! Check if the distribution is spatially uniform (somewhere)
  bool isSpatiallyUniform() const override;

  //! Check if the distribution is directionally uniform (isotropic)
  bool isDirectionallyUniform() const override;

  //! Initialize dimension counter map
  void initializeDimensionCounters( DimensionCounterMap& trials ) const override;

  //! Evaluate the distribution at the desired phase space point
  double evaluate( const ParticleState& particle ) const override;

  //! Sample a particle state from the distribution
  void sample( ParticleState& particle ) const override;

  //! Sample a particle state from the dist. and record the number of trials
  void sampleAndRecordTrials( ParticleState& particle,
                              DimensionCounterMap& trials ) const override;

  //! Sample a particle state with the desired dimension value
  void sampleWithDimensionValue( ParticleState& particle,
                                 const PhaseSpaceDimension dimension,
                                 const double dimension_value ) const override;

  //! Sample a particle state with the desired dim. value and record trials
  void sampleWithDimensionValueAndRecordTrials(
                                 ParticleState& particle,
                                 DimensionCounterMap& trials,
                                 const PhaseSpaceDimension dimension,
                                 const double dimension_value ) const override;

private:

  // Reset the spatial distributions
  void resetSpatialDistributions();
  
  // Reset the directional distributions
  void resetDirectionalDistributions();

  // Sample the particle state using the desired sampling functor
  template<typename DimensionSamplingFunctor>
  void sampleImpl( DimensionSamplingFunctor& dimension_sampling_function,
                   ParticleState& particle ) const;

  // Check the dependency tree for orphans
  void checkDependencyTreeForOrphans();

  // The spatial coordinate conversion policy
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
  d_spatial_coord_conversion_policy;

  // The directional coordinate conversion policy
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
  d_directional_coord_conversion_policy;

  // The independent particle source dimensions
  DimensionSet d_independent_dimensions;

  // The particle source dimensions
  DimensionDistributionMap d_dimension_distributions;

  // Determines if the distribution is ready for use
  bool d_ready;
};

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
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleDistribution.hpp
//---------------------------------------------------------------------------//
