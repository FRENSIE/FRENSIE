//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardDependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Standard dependent phase space dimension distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_STANDARD_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"

namespace MonteCarlo{

//! The standard dependent phase space dimension distribution class
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
class StandardDependentPhaseSpaceDimensionDistribution : public DependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension>
{

public:

  //! Constructor
  StandardDependentPhaseSpaceDimensionDistribution(
                         const std::shared_ptr<const TwoDDistributionBaseType>&
                         dimension_distribution );

  //! Destructor
  virtual ~StandardDependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Check if the dimension distribution is continuous
  bool isContinuous() const override;

  //! Check if the dimension distribution is tabular
  bool isTabular() const override;

  //! Check if the dimension distribution is uniform (somewhere)
  bool isUniform() const;

  //! Check if the underlying distribution has the form of interest
  bool hasForm( const OneDDistributionType distribution_type ) const override;

  //! Evaluate the dimension distribution without cascade to dependent dists.
  double evaluateWithoutCascade(
                     const PhaseSpacePoint& phase_space_point ) const override;

  //! Sample a dimension value without a cascade to the dependent dists.
  virtual void sampleWithoutCascade(
                          PhaseSpacePoint& phase_space_sample ) const override;

  //! Sample a dimension value without a cascade to the dependent dists.
  virtual void sampleAndRecordTrialsWithoutCascade(
                        PhaseSpacePoint& phase_space_sample,
                        ModuleTraits::InternalCounter& trials ) const override;

  //! Set the dimension value (weight appropriately)
  void setDimensionValueAndApplyWeight(
                                 PhaseSpacePoint& phase_space_sample,
                                 const double dimension_value ) const override;

protected:

  //! Evaluate the PDF of this dimension distribution
  double evaluatePDFWithoutCascade( const double indep_dimension_value,
                                    const double dimension_value ) const;
  
private:

  // The dimension distribution
  std::shared_ptr<const TwoDDistributionBaseType> d_dimension_distribution;
};

/*! The generic TwoDDistribution sampling policy class
 * \ingroup policy
 */
template<typename T>
struct TwoDDistributionSamplingPolicy
{
  //! Generate a sample from the TwoDDistribution object
  static inline double sample( const T& distribution,
                               const double indep_dimension_value )
  {
    return distribution->sampleSecondaryConditional( indep_dimension_value );
  }

  //! Generate a sample from the TwoDDistribution object
  static inline double sampleAndRecordTrials(
                                  const T& distribution,
                                  const double indep_dimension_value,
                                  ModuleTraits::InternalCounter& trials )
  {
    return distribution->sampleSecondaryConditionAndRecordTrials(
                                               indep_dimension_value, trials );
  }
};

/*! \brief The TwoDDistribution sampling policy specialization for 
 * the Utility::FullyTabularTwoDDistribution class
 * \ingroup policy
 */
template<>
struct TwoDDistributionSamplingPolicy<Utility::FullyTabularTwoDDistribution>
{
  //! Generate a sample from the Utility::FullyTabularTwoDDistribution object
  static inline double sample(
                     const Utility::FullyTabularTwoDDistribution& distribution,
                     const double indep_dimension_value )
  {
    return distribution->sampleSecondaryConditionalExact(
                                                       indep_dimension_value );
  }

  //! Generate a sample from the Utility::FullyTabularTwoDDistribution object
  static inline double sampleAndRecordTrials(
                     const Utility::FullyTabularTwoDDistribution& distribution,
                     const double indep_dimension_value,
                     ModuleTraits::InternalCounter& trials )
  {
    // The number of trials can be tracked when we use exact sampling. We
    // will simply increment the trials counter. Since the underlying
    // conditional distributions are tabular the sampling efficiency should
    // always be one anyway.
    ++trials;
    
    return distribution->sampleSecondaryConditionalExact(
                                                       indep_dimension_value );
  }
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardDependentPhaseSpaceDimensionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardDependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
