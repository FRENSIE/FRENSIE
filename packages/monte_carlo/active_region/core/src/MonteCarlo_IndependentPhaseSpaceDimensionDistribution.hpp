//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Independent phase space dimension distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace MonteCarlo{

//! The independent phase space dimension distribution class
template<PhaseSpaceDimension dimension>
class IndependentPhaseSpaceDimensionDistribution : public PhaseSpaceDimensionDistribution
{

public:

  //! The trial counter type
  typedef PhaseSpaceDimensionDistribution::Counter Counter;

  //! Constructor
  IndependentPhaseSpaceDimensionDistribution(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  dimension_distribution );

  //! Destructor
  virtual ~IndependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Return the phase space dimension
  PhaseSpaceDimension getDimension() const final override;

  //! Return the phase space dimension class
  PhaseSpaceDimensionClass getDimensionClass() const final override;

  //! Get the distribution type name
  std::string getDistributionTypeName() const final override;

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
  IndependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Evaluate the PDF of this dimension distribution
  double evaluatePDFWithoutCascade( const double dimension_value ) const;

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
  std::shared_ptr<const Utility::UnivariateDistribution> d_dimension_distribution;
};

//! The independent primary spatial phase space dimension distribution
typedef IndependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION> IndependentPrimarySpatialDimensionDistribution;

//! The independent secondary spatial phase space dimension distribution
typedef IndependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION> IndependentSecondarySpatialDimensionDistribution;

//! The independent tertiary spatial phase space dimension distribution
typedef IndependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION> IndependentTertiarySpatialDimensionDistribution;

//! The independent primary directional phase space dimension distribution
typedef IndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION> IndependentPrimaryDirectionalDimensionDistribution;

//! The independent secondary directional phase space dimension distribution
typedef IndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION> IndependentSecondaryDirectionalDimensionDistribution;

//! The independent tertiary directional phase space dimension distribution
typedef IndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION> IndependentTertiaryDirectionalDimensionDistribution;

//! The independent energy phase space dimension distribution
typedef IndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION> IndependentEnergyDimensionDistribution;

//! The independent time phase space dimension distribution
typedef IndependentPhaseSpaceDimensionDistribution<TIME_DIMENSION> IndependentTimeDimensionDistribution;

//! The independent weight phase space dimension distribution
typedef IndependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION> IndependentWeightDimensionDistribution;
  
} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_VERSION( version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    IndependentPhaseSpaceDimensionDistribution, MonteCarlo, version,      \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( MonteCarlo::PhaseSpaceDimension Dim ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( Dim ) )

BOOST_SERIALIZATION_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
