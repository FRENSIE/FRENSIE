//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Importance sampled dependent phase space dimension distribution
//!         class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"

namespace MonteCarlo{

template<PhaseSpaceDimension parent_dimension, PhaseSpaceDimension dimension>
class ImportanceSampledDependentPhaseSpaceDimensionDistribution : public DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>
{

  // Typedef for the base type
  typedef DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension> BaseType;

public:

  //! The trial counter type
  typedef typename BaseType::Counter Counter;

  //! Constructor
  ImportanceSampledDependentPhaseSpaceDimensionDistribution(
              const std::shared_ptr<const Utility::BasicBivariateDistribution>&
              dimension_distribution,
              const std::shared_ptr<const Utility::BasicBivariateDistribution>&
              importance_distribution );

  //! Destructor
  ~ImportanceSampledDependentPhaseSpaceDimensionDistribution()
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
  ImportanceSampledDependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  // Calculate the weight of a sample
  double calculateSampleWeight( const double indep_dimension_value,
                                const double dep_dimension_sample ) const;

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
  std::shared_ptr<const Utility::BasicBivariateDistribution>
  d_dimension_importance_distribution;
};

//---------------------------------------------------------------------------//
// DependentPrimarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

//! The secondary spatial dimension dependent primary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> ImportanceSampledSecondarySpatialDependentPrimarySpatialDimensionDistribution;

//! The tertiary spatial dimension dependent primary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> ImportanceSampledTertiarySpatialDependentPrimarySpatialDimensionDistribution;

//! The primary directional dimension dependent primary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> ImportanceSampledPrimaryDirectionalDependentPrimarySpatialDimensionDistribution;

//! The secondary directional dimension dependent primary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> ImportanceSampledSecondaryDirectionalDependentPrimarySpatialDimensionDistribution;

//! The tertiary directional dimension dependent primary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> ImportanceSampledTertiaryDirectionalDependentPrimarySpatialDimensionDistribution;

//! The energy dimension dependent primary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,PRIMARY_SPATIAL_DIMENSION> ImportanceSampledEnergyDependentPrimarySpatialDimensionDistribution;

//! The time dimension dependent primary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,PRIMARY_SPATIAL_DIMENSION> ImportanceSampledTimeDependentPrimarySpatialDimensionDistribution;

//! The weight dimension dependent primary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,PRIMARY_SPATIAL_DIMENSION> ImportanceSampledWeightDependentPrimarySpatialDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentSecondarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent secondary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> ImportanceSampledPrimarySpatialDependentSecondarySpatialDimensionDistribution;

//! The tertiary spatial dimension dependent secondary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> ImportanceSampledTertiarySpatialDependentSecondarySpatialDimensionDistribution;

//! The primary directional dimension dependent secondary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> ImportanceSampledPrimaryDirectionalDependentSecondarySpatialDimensionDistribution;

//! The secondary directional dimension dependent secondary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> ImportanceSampledSecondaryDirectionalDependentSecondarySpatialDimensionDistribution;

//! The tertiary directional dimension dependent secondary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> ImportanceSampledTertiaryDirectionalDependentSecondarySpatialDimensionDistribution;

//! The energy dimension dependent secondary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,SECONDARY_SPATIAL_DIMENSION> ImportanceSampledEnergyDependentSecondarySpatialDimensionDistribution;

//! The time dimension dependent secondary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,SECONDARY_SPATIAL_DIMENSION> ImportanceSampledTimeDependentSecondarySpatialDimensionDistribution;

//! The weight dimension dependent secondary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,SECONDARY_SPATIAL_DIMENSION> ImportanceSampledWeightDependentSecondarySpatialDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentTertiarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent tertiary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> ImportanceSampledPrimarySpatialDependentTertiarySpatialDimensionDistribution;

//! The secondary spatial dimension dependent tertiary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> ImportanceSampledSecondarySpatialDependentTertiarySpatialDimensionDistribution;

//! The primary directional dimension dependent tertiary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> ImportanceSampledPrimaryDirectionalDependentTertiarySpatialDimensionDistribution;

//! The secondary directional dimension dependent tertiary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> ImportanceSampledSecondaryDirectionalDependentTertiarySpatialDimensionDistribution;

//! The tertiary directional dimension dependent tertiary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> ImportanceSampledTertiaryDirectionalDependentTertiarySpatialDimensionDistribution;

//! The energy dimension dependent tertiary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TERTIARY_SPATIAL_DIMENSION> ImportanceSampledEnergyDependentTertiarySpatialDimensionDistribution;

//! The time dimension dependent tertiary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,TERTIARY_SPATIAL_DIMENSION> ImportanceSampledTimeDependentTertiarySpatialDimensionDistribution;

//! The weight dimension dependent tertiary spatial dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TERTIARY_SPATIAL_DIMENSION> ImportanceSampledWeightDependentTertiarySpatialDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentPrimaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent primary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> ImportanceSampledPrimarySpatialDependentPrimaryDirectionalDimensionDistribution;

//! The secondary spatial dimension dependent primary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> ImportanceSampledSecondarySpatialDependentPrimaryDirectionalDimensionDistribution;

//! The tertiary spatial dimension dependent primary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> ImportanceSampledTertiarySpatialDependentPrimaryDirectionalDimensionDistribution;

//! The secondary directional dimension dependent primary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> ImportanceSampledSecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution;

//! The tertiary directional dimension dependent primary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> ImportanceSampledTertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution;

//! The energy dimension dependent primary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> ImportanceSampledEnergyDependentPrimaryDirectionalDimensionDistribution;

//! The time dimension dependent primary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> ImportanceSampledTimeDependentPrimaryDirectionalDimensionDistribution;

//! The weight dimension dependent primary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> ImportanceSampledWeightDependentPrimaryDirectionalDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentSecondaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent secondary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> ImportanceSampledPrimarySpatialDependentSecondaryDirectionalDimensionDistribution;

//! The secondary spatial dimension dependent secondary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> ImportanceSampledSecondarySpatialDependentSecondaryDirectionalDimensionDistribution;

//! The tertiary spatial dimension dependent secondary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> ImportanceSampledTertiarySpatialDependentSecondaryDirectionalDimensionDistribution;

//! The primary directional dimension dependent secondary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> ImportanceSampledPrimaryDirectionalDependentSecondaryDirectionalDimensionDistribution;

//! The tertiary directional dimension dependent secondary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> ImportanceSampledTertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution;

//! The energy dimension dependent secondary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> ImportanceSampledEnergyDependentSecondaryDirectionalDimensionDistribution;

//! The time dimension dependent secondary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> ImportanceSampledTimeDependentSecondaryDirectionalDimensionDistribution;

//! The weight dimension dependent secondary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> ImportanceSampledWeightDependentSecondaryDirectionalDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentTertiaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//
  
//! The primary spatial dimension dependent tertiary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> ImportanceSampledPrimarySpatialDependentTertiaryDirectionalDimensionDistribution;

//! The secondary spatial dimension dependent tertiary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> ImportanceSampledSecondarySpatialDependentTertiaryDirectionalDimensionDistribution;

//! The tertiary spatial dimension dependent tertiary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> ImportanceSampledTertiarySpatialDependentTertiaryDirectionalDimensionDistribution;

//! The primary directional dimension dependent tertiary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> ImportanceSampledPrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution;

//! The secondary directional dimension dependent tertiary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> ImportanceSampledSecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution;

//! The energy dimension dependent tertiary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> ImportanceSampledEnergyDependentTertiaryDirectionalDimensionDistribution;

//! The time dimension dependent tertiary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> ImportanceSampledTimeDependentTertiaryDirectionalDimensionDistribution;

//! The weight dimension dependent tertiary directional dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> ImportanceSampledWeightDependentTertiaryDirectionalDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentEnergyDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent energy dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> ImportanceSampledPrimarySpatialDependentEnergyDimensionDistribution;

//! The secondary spatial dimension dependent energy dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> ImportanceSampledSecondarySpatialDependentEnergyDimensionDistribution;

//! The tertiary spatial dimension dependent energy dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> ImportanceSampledTertiarySpatialDependentEnergyDimensionDistribution;

//! The primary directional dimension dependent energy dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> ImportanceSampledPrimaryDirectionalDependentEnergyDimensionDistribution;

//! The secondary directional dimension dependent energy dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> ImportanceSampledSecondaryDirectionalDependentEnergyDimensionDistribution;

//! The tertiary directional dimension dependent energy dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> ImportanceSampledTertiaryDirectionalDependentEnergyDimensionDistribution;

//! The time dimension dependent energy dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,ENERGY_DIMENSION> ImportanceSampledTimeDependentEnergyDimensionDistribution;

//! The weight dimension dependent energy dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,ENERGY_DIMENSION> ImportanceSampledWeightDependentEnergyDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentTimeDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent time dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TIME_DIMENSION> ImportanceSampledPrimarySpatialDependentTimeDimensionDistribution;

//! The secondary spatial dimension dependent time dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TIME_DIMENSION> ImportanceSampledSecondarySpatialDependentTimeDimensionDistribution;

//! The tertiary spatial dimension dependent time dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TIME_DIMENSION> ImportanceSampledTertiarySpatialDependentTimeDimensionDistribution;

//! The primary directional dimension dependent time dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> ImportanceSampledPrimaryDirectionalDependentTimeDimensionDistribution;

//! The secondary directional dimension dependent time dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> ImportanceSampledSecondaryDirectionalDependentTimeDimensionDistribution;

//! The tertiary directional dimension dependent time dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> ImportanceSampledTertiaryDirectionalDependentTimeDimensionDistribution;

//! The energy dimension dependent time dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TIME_DIMENSION> ImportanceSampledEnergyDependentTimeDimensionDistribution;

//! The weight dimension dependent time dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TIME_DIMENSION> ImportanceSampledWeightDependentTimeDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentWeightDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent weight dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> ImportanceSampledPrimarySpatialDependentWeightDimensionDistribution;

//! The secondary spatial dimension dependent weight dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> ImportanceSampledSecondarySpatialDependentWeightDimensionDistribution;

//! The tertiary spatial dimension dependent weight dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> ImportanceSampledTertiarySpatialDependentWeightDimensionDistribution;

//! The primary directional dimension dependent weight dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> ImportanceSampledPrimaryDirectionalDependentWeightDimensionDistribution;

//! The secondary directional dimension dependent weight dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> ImportanceSampledSecondaryDirectionalDependentWeightDimensionDistribution;

//! The tertiary directional dimension dependent weight dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> ImportanceSampledTertiaryDirectionalDependentWeightDimensionDistribution;

//! The energy dimension dependent weight dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,WEIGHT_DIMENSION> ImportanceSampledEnergyDependentWeightDimensionDistribution;

//! The time dimension dependent weight dimension distribution
typedef ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,WEIGHT_DIMENSION> ImportanceSampledTimeDependentWeightDimensionDistribution;
  
} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_VERSION( version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    ImportanceSampledDependentPhaseSpaceDimensionDistribution, MonteCarlo, version,      \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( MonteCarlo::PhaseSpaceDimension ParentDim, MonteCarlo::PhaseSpaceDimension Dim ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( ParentDim, Dim ) )

BOOST_SERIALIZATION_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
