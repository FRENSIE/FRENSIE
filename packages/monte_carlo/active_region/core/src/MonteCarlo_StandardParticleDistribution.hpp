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
  // Typedef for scalar traits
  typedef Utility::QuantityTraits<double> QT;

  //! Typedef for the phase space dimension distribution map
  typedef std::map<PhaseSpaceDimension,std::shared_ptr<PhaseSpaceDimensionDistribution> > DimensionDistributionMap;

  // Typedef for the dimension sampling function
  typedef std::function<void(const PhaseSpaceDimensionDistribution&,PhaseSpacePoint&)> DimensionSamplingFunction;

public:

  //! Typedef for the phase space dimension set
  typedef ParticleDistribution::DimensionSet DimensionSet;

  //! The dimension trial counter map
  typedef ParticleDistribution::DimensionCounterMap DimensionCounterMap;

  //! Basic Constructor
  StandardParticleDistribution( const std::string& name );

  //! Constructor
  StandardParticleDistribution(
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy );

  //! Constructor
  StandardParticleDistribution(
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

  //! Set the energy that will be sampled by the distribution
  void setEnergy( const double energy );

  //! Set the time that will be sampled by the distribution
  void setTime( const double time );

  //! Set the position that will be sampled by the distribution
  void setPosition( const double x_position,
                    const double y_position,
                    const double z_position );

  //! Set the position that will be sampled by the distribution
  void setPosition( const double position[3] );

  //! Set the direction that will be sampled by the distribution
  void setDirection( const double x_direction,
                     const double y_direction,
                     const double z_direction );

  //! Set the direction that will be sampled by the distribution
  void setDirection( const double direction[3] );

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

protected:

  //! Default Constructor
  StandardParticleDistribution();

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

  // Save the state to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

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

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( StandardParticleDistribution, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardParticleDistribution, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, StandardParticleDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardParticleDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PARTICLE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleDistribution.hpp
//---------------------------------------------------------------------------//
