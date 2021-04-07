//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Importance sampled independent phase space dimension distribution
//!         class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"

namespace MonteCarlo{

//! The importance sampled independent phase space dimension distribution class
template<PhaseSpaceDimension dimension>
class ImportanceSampledIndependentPhaseSpaceDimensionDistribution : public IndependentPhaseSpaceDimensionDistribution<dimension>
{

  // Typedef for the base type
  typedef IndependentPhaseSpaceDimensionDistribution<dimension> BaseType;

public:

  //! The trial counter type
  typedef PhaseSpaceDimensionDistribution::Counter Counter;

  //! Constructor
  ImportanceSampledIndependentPhaseSpaceDimensionDistribution(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  dimension_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  importance_distribution );

  //! Destructor
  ~ImportanceSampledIndependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Sample a dimension value without a cascade to the dependent dists.
  void sampleWithoutCascade(
                    PhaseSpacePoint& phase_space_sample ) const final override;

  //! Sample a dimension value without a cascade to the dependent dists.
  void sampleAndRecordTrialsWithoutCascade(
                                        PhaseSpacePoint& phase_space_sample,
                                        Counter& trials ) const final override;
  
private:

  // Default constructor
  ImportanceSampledIndependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  // Calculate the weight of a sample
  double calculateSampleWeight( const double dimension_sample ) const;

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The dimension importance distribution
  std::shared_ptr<const Utility::UnivariateDistribution>
  d_dimension_importance_distribution;
};

//! The independent primary spatial phase space dimension distribution
typedef ImportanceSampledIndependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION> ImportanceSampledIndependentPrimarySpatialDimensionDistribution;

//! The importance sampled independent secondary spatial phase space dimension distribution
typedef ImportanceSampledIndependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION> ImportanceSampledIndependentSecondarySpatialDimensionDistribution;

//! The importance sampled independent tertiary spatial phase space dimension distribution
typedef ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION> ImportanceSampledIndependentTertiarySpatialDimensionDistribution;

//! The importance sampled independent primary directional phase space dimension distribution
typedef ImportanceSampledIndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION> ImportanceSampledIndependentPrimaryDirectionalDimensionDistribution;

//! The importance sampled independent secondary directional phase space dimension distribution
typedef ImportanceSampledIndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION> ImportanceSampledIndependentSecondaryDirectionalDimensionDistribution;

//! The importance sampled independent tertiary directional phase space dimension distribution
typedef ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION> ImportanceSampledIndependentTertiaryDirectionalDimensionDistribution;

//! The importance sampled independent energy phase space dimension distribution
typedef ImportanceSampledIndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION> ImportanceSampledIndependentEnergyDimensionDistribution;

//! The importance sampled independent time phase space dimension distribution
typedef ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TIME_DIMENSION> ImportanceSampledIndependentTimeDimensionDistribution;

//! The importance sampled independent weight phase space dimension distribution
typedef ImportanceSampledIndependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION> ImportanceSampledIndependentWeightDimensionDistribution;
  
} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_VERSION( version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    ImportanceSampledIndependentPhaseSpaceDimensionDistribution, MonteCarlo, version,      \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( MonteCarlo::PhaseSpaceDimension Dim ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( Dim ) )

BOOST_SERIALIZATION_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
