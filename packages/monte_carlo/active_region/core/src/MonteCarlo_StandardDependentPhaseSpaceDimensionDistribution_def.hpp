//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardDependentPhaseSpaceDimensionDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Standard dependent phase space dimension distribution class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_STANDARD_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_FullyTabularTwoDDistribution.hpp"
#include "Utility_PartiallyTabularTwoDDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

namespace Details{

/*! The generic TwoDDistribution traits class
 * \ingroup traits
 */
template<typename T>
struct TwoDDistributionTraits
{
  //! Generate a sample from the TwoDDistribution object
  static inline double sample( const T& distribution,
                               const double indep_dimension_value )
  {
    return distribution.sampleSecondaryConditional( indep_dimension_value );
  }

  //! Generate a sample from the TwoDDistribution object
  static inline double sampleAndRecordTrials(
                                  const T& distribution,
                                  const double indep_dimension_value,
                                  ModuleTraits::InternalCounter& trials )
  {
    return distribution.sampleSecondaryConditionalAndRecordTrials(
                                               indep_dimension_value, trials );
  }

  //! Get the distribution type name
  static inline std::string name()
  {
    return "TwoDDistribution";
  }
};

/*! \brief The TwoDDistribution traits specialization for 
 * the Utility::PartiallyTabularTwoDDistribution class
 * \ingroup traits
 */
template<>
struct TwoDDistributionTraits<Utility::PartiallyTabularTwoDDistribution>
{
  //! Generate a sample from the TwoDDistribution object
  static inline double sample(
                 const Utility::PartiallyTabularTwoDDistribution& distribution,
                 const double indep_dimension_value )
  {
    return distribution.sampleSecondaryConditional( indep_dimension_value );
  }

  //! Generate a sample from the TwoDDistribution object
  static inline double sampleAndRecordTrials(
                 const Utility::PartiallyTabularTwoDDistribution& distribution,
                 const double indep_dimension_value,
                 ModuleTraits::InternalCounter& trials )
  {
    return distribution.sampleSecondaryConditionalAndRecordTrials(
                                               indep_dimension_value, trials );
  }

  //! Get the distribution type name
  static inline std::string name()
  {
    return "PartiallyTabularTwoDDistribution";
  }
};

/*! \brief The TwoDDistribution traits specialization for 
 * the Utility::FullyTabularTwoDDistribution class
 * \ingroup traits
 */
template<>
struct TwoDDistributionTraits<Utility::FullyTabularTwoDDistribution>
{
  //! Generate a sample from the Utility::FullyTabularTwoDDistribution object
  static inline double sample(
                     const Utility::FullyTabularTwoDDistribution& distribution,
                     const double indep_dimension_value )
  {
    return distribution.sampleSecondaryConditionalExact(
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
    
    return distribution.sampleSecondaryConditionalExact(
                                                       indep_dimension_value );
  }

  //! Get the distribution type name
  static inline std::string name()
  {
    return "FullyTabularTwoDDistribution";
  }
};
  
} // end Details namespace

// Constructor
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::StandardDependentPhaseSpaceDimensionDistribution(
                         const std::shared_ptr<const TwoDDistributionBaseType>&
                         dimension_distribution )
  : d_dimension_distribution( dimension_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( dimension_distribution.get() );
}

// Check if the dimension distribution is continuous
/*! \details This method only checks if the distribution is continuous w.r.t.
 * the independent dimension. More information is needed to check if the
 * distribution is continuous w.r.t. the dependent dimension.
 */
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
bool StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::isContinuous() const
{
  return d_dimension_distribution->isPrimaryDimensionContinuous();
}

// Check if the dimension distribution is tabular
/*! \details This method only checks if the distribution is tabular w.r.t.
 * the independent dimension. More information is needed to check if the 
 * distribution is tabular w.r.t. the dependent dimension.
 */
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
bool StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::isTabular() const
{
  return d_dimension_distribution->isPrimaryDimensionTabular();
}

// Check if the dimension distribution is uniform (somewhere)
/*! \details This method will always return false since we cannot test
 * if the two-d distribution is constant everywhere that it is defined.
 */
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
bool StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::isUniform() const
{
  return false;
}

// Check if the underlying distribution has the form of interest
/*! \details This method will always return false since we cannot test
 * if the two-d distribution has the form of interest everywhere that it is 
 * defined.
 */
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
bool StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::hasForm(
                  const Utility::OneDDistributionType distribution_type ) const
{
  return false;
}

// Get the distribution type name
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
std::string StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::getDistributionTypeName() const
{
  return Details::TwoDDistributionTraits<TwoDDistributionBaseType>::name();
}

// Evaluate the dimension distribution without cascade to dependent dists.
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
double StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::evaluateWithoutCascade(
                               const PhaseSpacePoint& phase_space_point ) const
{
  return d_dimension_distribution->evaluate(
                          getCoordinate<parent_dimension>( phase_space_point ),
                          getCoordinate<dimension>( phase_space_point ) );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
void StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::sampleWithoutCascade(
                                    PhaseSpacePoint& phase_space_sample ) const
{
  const double sample =
    Details::TwoDDistributionTraits<TwoDDistributionBaseType>::sample(
                       *d_dimension_distribution,
                       getCoordinate<parent_dimension>( phase_space_sample ) );

  setCoordinate<dimension>( phase_space_sample, sample );
  setCoordinateWeight<dimension>( phase_space_sample, 1.0 );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
void StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::sampleAndRecordTrialsWithoutCascade(
                                  PhaseSpacePoint& phase_space_sample,
                                  ModuleTraits::InternalCounter& trials ) const
{
  const double sample =
    Details::TwoDDistributionTraits<TwoDDistributionBaseType>::sampleAndRecordTrials(
                        *d_dimension_distribution,
                        getCoordinate<parent_dimension>( phase_space_sample ),
                        trials );

  setCoordinate<dimension>( phase_space_sample, sample );
  setCoordinateWeight<dimension>( phase_space_sample, 1.0 );
}

// Set the dimension value (weight appropriately)
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
void StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::setDimensionValueAndApplyWeight(
                                           PhaseSpacePoint& phase_space_sample,
                                           const double dimension_value ) const
{
  const double weight = this->evaluatePDFWithoutCascade(
                         getCoordinate<parent_dimension>( phase_space_sample ),
                         dimension_value );

  // Make sure that the weight is valid
  TEST_FOR_EXCEPTION( weight <= 0.0,
                      std::logic_error,
                      "An invalid weight (" << weight << ") has been "
                      "calculated for dimension " << dimension << "!" );

  setCoordinate<dimension>( phase_space_sample, dimension_value );
  setCoordinateWeight<dimension>( phase_space_sample, weight );
}

// Evaluate the PDF of this dimension distribution
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename TwoDDistributionBaseType>
double StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,TwoDDistributionBaseType>::evaluatePDFWithoutCascade(
                                          const double parent_dimension_value,
                                          const double dimension_value ) const
{
  return d_dimension_distribution->evaluateSecondaryConditionalPDF(
                                     parent_dimension_value, dimension_value );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardDependentPhaseSpaceDimensionDistribution_def.hpp
//---------------------------------------------------------------------------//
