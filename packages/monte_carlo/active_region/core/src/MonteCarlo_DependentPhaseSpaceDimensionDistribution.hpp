//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Dependent phase space dimension distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_BasicBivariateDistribution.hpp"

namespace MonteCarlo{

/*! The dependent phase space dimension distribution class helper
 * \details This class will be used if parent_dimension == dimension.
 * Compilation should fail.
 */
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename Enabled = void>
class DependentPhaseSpaceDimensionDistributionHelper
{ /* ... */ };

/*! The dependent phase space dimension distribution class
 * \details This class will be used if parent_dimension != dimension.
 */
template<PhaseSpaceDimension parent_dimension, PhaseSpaceDimension dimension>
class DependentPhaseSpaceDimensionDistribution :
#if !defined SWIG
public DependentPhaseSpaceDimensionDistributionHelper<parent_dimension,dimension, typename std::enable_if<parent_dimension!=dimension>::type>,
#endif // end !defined SWIG
 public PhaseSpaceDimensionDistribution
{

public:

  //! The trial counter type
  typedef PhaseSpaceDimensionDistribution::Counter Counter;

  //! Constructor
  DependentPhaseSpaceDimensionDistribution(
              const std::shared_ptr<const Utility::BasicBivariateDistribution>&
              dimension_distribution );

  //! Destructor
  virtual ~DependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Return the phase space dimension
  PhaseSpaceDimension getDimension() const final override;

  //! Return the phase space dimension class
  PhaseSpaceDimensionClass getDimensionClass() const final override;

  //! Return the parent phase space dimension
  PhaseSpaceDimension getParentDimension() const;

  //! Return the parent phase space dimension class
  PhaseSpaceDimensionClass getParentDimensionClass() const;

  //! Check if the dimension distribution is independent
  bool isIndependent() const final override;

  //! Check if the dimension is dependent on the dimension of interest
  bool isDependentOnDimension(
              const PhaseSpaceDimension other_dimension ) const final override;

  //! Check if the dimension distribution is continuous
  bool isContinuous() const final override;

  //! Check if the dimension distribution is tabular
  bool isTabular() const final override;

  //! Check if the dimension distribution is uniform (somewhere)
  bool isUniform() const final override;

  //! Check if the underlying distribution has the form of interest
  bool hasForm( const Utility::UnivariateDistributionType distribution_type ) const final override;

  //! Get the distribution type name
  std::string getDistributionTypeName() const final override;

  //! Evaluate the dimension distribution without cascade to dependent dists.
  double evaluateWithoutCascade(
               const PhaseSpacePoint& phase_space_point ) const final override;

  //! Sample a dimension value without a cascade to the dependent dists.
  virtual void sampleWithoutCascade(
                          PhaseSpacePoint& phase_space_sample ) const override;

  //! Sample a dimension value without a cascade to the dependent dists.
  virtual void sampleAndRecordTrialsWithoutCascade(
                                           PhaseSpacePoint& phase_space_sample,
                                           Counter& trials ) const override;

  //! Set the dimension value (weight appropriately)
  void setDimensionValueAndApplyWeight(
                           PhaseSpacePoint& phase_space_sample,
                           const double dimension_value ) const final override;

protected:

  //! Default constructor
  DependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Evaluate the PDF of this dimension distribution
  double evaluatePDFWithoutCascade( const double parent_dimension_value,
                                    const double dimension_value ) const;

private:

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The dimension distribution
  std::shared_ptr<const Utility::BasicBivariateDistribution>
  d_dimension_distribution;
};

//---------------------------------------------------------------------------//
// DependentPrimarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

//! The secondary spatial dimension dependent primary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> SecondarySpatialDependentPrimarySpatialDimensionDistribution;

//! The tertiary spatial dimension dependent primary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> TertiarySpatialDependentPrimarySpatialDimensionDistribution;

//! The primary directional dimension dependent primary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> PrimaryDirectionalDependentPrimarySpatialDimensionDistribution;

//! The secondary directional dimension dependent primary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> SecondaryDirectionalDependentPrimarySpatialDimensionDistribution;

//! The tertiary directional dimension dependent primary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> TertiaryDirectionalDependentPrimarySpatialDimensionDistribution;

//! The energy dimension dependent primary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,PRIMARY_SPATIAL_DIMENSION> EnergyDependentPrimarySpatialDimensionDistribution;

//! The time dimension dependent primary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,PRIMARY_SPATIAL_DIMENSION> TimeDependentPrimarySpatialDimensionDistribution;

//! The weight dimension dependent primary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,PRIMARY_SPATIAL_DIMENSION> WeightDependentPrimarySpatialDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentSecondarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent secondary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> PrimarySpatialDependentSecondarySpatialDimensionDistribution;

//! The tertiary spatial dimension dependent secondary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> TertiarySpatialDependentSecondarySpatialDimensionDistribution;

//! The primary directional dimension dependent secondary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> PrimaryDirectionalDependentSecondarySpatialDimensionDistribution;

//! The secondary directional dimension dependent secondary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> SecondaryDirectionalDependentSecondarySpatialDimensionDistribution;

//! The tertiary directional dimension dependent secondary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> TertiaryDirectionalDependentSecondarySpatialDimensionDistribution;

//! The energy dimension dependent secondary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,SECONDARY_SPATIAL_DIMENSION> EnergyDependentSecondarySpatialDimensionDistribution;

//! The time dimension dependent secondary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,SECONDARY_SPATIAL_DIMENSION> TimeDependentSecondarySpatialDimensionDistribution;

//! The weight dimension dependent secondary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,SECONDARY_SPATIAL_DIMENSION> WeightDependentSecondarySpatialDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentTertiarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent tertiary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> PrimarySpatialDependentTertiarySpatialDimensionDistribution;

//! The secondary spatial dimension dependent tertiary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> SecondarySpatialDependentTertiarySpatialDimensionDistribution;

//! The primary directional dimension dependent tertiary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> PrimaryDirectionalDependentTertiarySpatialDimensionDistribution;

//! The secondary directional dimension dependent tertiary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> SecondaryDirectionalDependentTertiarySpatialDimensionDistribution;

//! The tertiary directional dimension dependent tertiary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> TertiaryDirectionalDependentTertiarySpatialDimensionDistribution;

//! The energy dimension dependent tertiary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TERTIARY_SPATIAL_DIMENSION> EnergyDependentTertiarySpatialDimensionDistribution;

//! The time dimension dependent tertiary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,TERTIARY_SPATIAL_DIMENSION> TimeDependentTertiarySpatialDimensionDistribution;

//! The weight dimension dependent tertiary spatial dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TERTIARY_SPATIAL_DIMENSION> WeightDependentTertiarySpatialDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentPrimaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent primary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> PrimarySpatialDependentPrimaryDirectionalDimensionDistribution;

//! The secondary spatial dimension dependent primary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> SecondarySpatialDependentPrimaryDirectionalDimensionDistribution;

//! The tertiary spatial dimension dependent primary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> TertiarySpatialDependentPrimaryDirectionalDimensionDistribution;

//! The secondary directional dimension dependent primary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> SecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution;

//! The tertiary directional dimension dependent primary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> TertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution;

//! The energy dimension dependent primary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> EnergyDependentPrimaryDirectionalDimensionDistribution;

//! The time dimension dependent primary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> TimeDependentPrimaryDirectionalDimensionDistribution;

//! The weight dimension dependent primary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> WeightDependentPrimaryDirectionalDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentSecondaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent secondary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> PrimarySpatialDependentSecondaryDirectionalDimensionDistribution;

//! The secondary spatial dimension dependent secondary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> SecondarySpatialDependentSecondaryDirectionalDimensionDistribution;

//! The tertiary spatial dimension dependent secondary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> TertiarySpatialDependentSecondaryDirectionalDimensionDistribution;

//! The primary directional dimension dependent secondary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> PrimaryDirectionalDependentSecondaryDirectionalDimensionDistribution;

//! The tertiary directional dimension dependent secondary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> TertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution;

//! The energy dimension dependent secondary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> EnergyDependentSecondaryDirectionalDimensionDistribution;

//! The time dimension dependent secondary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> TimeDependentSecondaryDirectionalDimensionDistribution;

//! The weight dimension dependent secondary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> WeightDependentSecondaryDirectionalDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentTertiaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent tertiary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> PrimarySpatialDependentTertiaryDirectionalDimensionDistribution;

//! The secondary spatial dimension dependent tertiary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> SecondarySpatialDependentTertiaryDirectionalDimensionDistribution;

//! The tertiary spatial dimension dependent tertiary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> TertiarySpatialDependentTertiaryDirectionalDimensionDistribution;

//! The primary directional dimension dependent tertiary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> PrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution;

//! The secondary directional dimension dependent tertiary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> SecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution;

//! The energy dimension dependent tertiary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> EnergyDependentTertiaryDirectionalDimensionDistribution;

//! The time dimension dependent tertiary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> TimeDependentTertiaryDirectionalDimensionDistribution;

//! The weight dimension dependent tertiary directional dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> WeightDependentTertiaryDirectionalDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentEnergyDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent energy dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> PrimarySpatialDependentEnergyDimensionDistribution;

//! The secondary spatial dimension dependent energy dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> SecondarySpatialDependentEnergyDimensionDistribution;

//! The tertiary spatial dimension dependent energy dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> TertiarySpatialDependentEnergyDimensionDistribution;

//! The primary directional dimension dependent energy dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> PrimaryDirectionalDependentEnergyDimensionDistribution;

//! The secondary directional dimension dependent energy dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> SecondaryDirectionalDependentEnergyDimensionDistribution;

//! The tertiary directional dimension dependent energy dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> TertiaryDirectionalDependentEnergyDimensionDistribution;

//! The time dimension dependent energy dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,ENERGY_DIMENSION> TimeDependentEnergyDimensionDistribution;

//! The weight dimension dependent energy dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,ENERGY_DIMENSION> WeightDependentEnergyDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentTimeDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent time dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TIME_DIMENSION> PrimarySpatialDependentTimeDimensionDistribution;

//! The secondary spatial dimension dependent time dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TIME_DIMENSION> SecondarySpatialDependentTimeDimensionDistribution;

//! The tertiary spatial dimension dependent time dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TIME_DIMENSION> TertiarySpatialDependentTimeDimensionDistribution;

//! The primary directional dimension dependent time dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> PrimaryDirectionalDependentTimeDimensionDistribution;

//! The secondary directional dimension dependent time dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> SecondaryDirectionalDependentTimeDimensionDistribution;

//! The tertiary directional dimension dependent time dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> TertiaryDirectionalDependentTimeDimensionDistribution;

//! The energy dimension dependent time dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TIME_DIMENSION> EnergyDependentTimeDimensionDistribution;

//! The weight dimension dependent time dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TIME_DIMENSION> WeightDependentTimeDimensionDistribution;

//---------------------------------------------------------------------------//
// DependentWeightDimensionDistributions
//---------------------------------------------------------------------------//

//! The primary spatial dimension dependent weight dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> PrimarySpatialDependentWeightDimensionDistribution;

//! The secondary spatial dimension dependent weight dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> SecondarySpatialDependentWeightDimensionDistribution;

//! The tertiary spatial dimension dependent weight dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> TertiarySpatialDependentWeightDimensionDistribution;

//! The primary directional dimension dependent weight dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> PrimaryDirectionalDependentWeightDimensionDistribution;

//! The secondary directional dimension dependent weight dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> SecondaryDirectionalDependentWeightDimensionDistribution;

//! The tertiary directional dimension dependent weight dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> TertiaryDirectionalDependentWeightDimensionDistribution;

//! The energy dimension dependent weight dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,WEIGHT_DIMENSION> EnergyDependentWeightDimensionDistribution;

//! The time dimension dependent weight dimension distribution
typedef DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,WEIGHT_DIMENSION> TimeDependentWeightDimensionDistribution;

} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_VERSION( version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    DependentPhaseSpaceDimensionDistribution, MonteCarlo, version,      \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( MonteCarlo::PhaseSpaceDimension ParentDim, MonteCarlo::PhaseSpaceDimension Dim ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( ParentDim, Dim ) )

BOOST_SERIALIZATION_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
