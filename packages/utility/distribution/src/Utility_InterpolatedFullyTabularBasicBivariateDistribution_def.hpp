//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedFullyTabularBasicBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular basic bivariate dist. class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION4_EXPORT_IMPLEMENT( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution );

namespace Utility{

namespace Details{

//! The TwoDGridPolicy sampling functor creation helper
template<typename TwoDGridPolicy>
struct TwoDGridPolicySamplingFunctorCreationHelper;

/*! \brief The TwoDGridPolicy sampling functor creation helper base for
 * uncorrelated grid policies.
 */
struct TwoDGridPolicySamplingFunctorCreationUncorrelatedBaseHelper
{
  //! Return the basic sampling functor
  template<typename BaseUnivariateDistributionType>
  static inline std::function<typename BaseUnivariateDistributionType::IndepQuantity(const BaseUnivariateDistributionType&)> createBasicSamplingFunctor()
  {
    return std::bind<typename BaseUnivariateDistributionType::IndepQuantity>(
                                       &BaseUnivariateDistributionType::sample,
                                       std::placeholders::_1 );
  }

  //! Return the sampling functor with a trials counter
  template<typename BaseUnivariateDistributionType>
  static inline std::function<typename BaseUnivariateDistributionType::IndepQuantity(const BaseUnivariateDistributionType&)> createSamplingFunctorWithTrialsCounter(
                                  Utility::DistributionTraits::Counter& trials,
                                  std::function<void()>& trials_updater )
  {
    trials_updater = [](){};

    return std::bind<typename BaseUnivariateDistributionType::IndepQuantity>(
                        &BaseUnivariateDistributionType::sampleAndRecordTrials,
                        std::placeholders::_1,
                        std::ref( trials ) );
  }

  //! Return the sampling functor that records the sampled secondary bin index
  template<typename BaseUnivariateDistributionType>
  static inline std::function<typename BaseUnivariateDistributionType::IndepQuantity(const BaseUnivariateDistributionType&)> createSamplingFunctorWithSecondaryBinIndex( size_t& secondary_bin_index )
  {
    return std::bind<typename BaseUnivariateDistributionType::IndepQuantity>(
                      &BaseUnivariateDistributionType::sampleAndRecordBinIndex,
                      std::placeholders::_1,
                      std::ref( secondary_bin_index ) );
  }
};

/*! \brief The TwoDGridPolicy sampling functor creation helper base for
 * correlated grid policies.
 */
struct TwoDGridPolicySamplingFunctorCreationCorrelatedBaseHelper
{
  //! Return the basic sampling functor
  template<typename BaseUnivariateDistributionType>
  static inline std::function<typename BaseUnivariateDistributionType::IndepQuantity(const BaseUnivariateDistributionType&)> createBasicSamplingFunctor()
  {
    // Generate a random number
    double random_number =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    return std::bind<typename BaseUnivariateDistributionType::IndepQuantity>(
                       &BaseUnivariateDistributionType::sampleWithRandomNumber,
                       std::placeholders::_1,
                       random_number );
  }

  //! Return the sampling functor with a trials counter
  template<typename BaseUnivariateDistributionType>
  static inline std::function<typename BaseUnivariateDistributionType::IndepQuantity(const BaseUnivariateDistributionType&)> createSamplingFunctorWithTrialsCounter(
                                  Utility::DistributionTraits::Counter& trials,
                                  std::function<void()>& trials_updater )
  {
    FRENSIE_LOG_TAGGED_WARNING( "InterpolatedFullyTabularBasicBivariateDistribution",
                                "The sampling trial counter cannot be "
                                "accurately updated with correlated "
                                "sampling!" );

    trials_updater = [&trials](){ ++trials; };

    // We can only use a single random number with correlated sampling - the
    // trials counter has to be ignored.
    return TwoDGridPolicySamplingFunctorCreationCorrelatedBaseHelper::createBasicSamplingFunctor<BaseUnivariateDistributionType>();
  }

  //! Return the sampling functor that records the sampled secondary bin index
  template<typename BaseUnivariateDistributionType>
  static inline std::function<typename BaseUnivariateDistributionType::IndepQuantity(const BaseUnivariateDistributionType&)> createSamplingFunctorWithSecondaryBinIndex( size_t& secondary_bin_index )
  {
    FRENSIE_LOG_TAGGED_WARNING( "InterpolatedFullyTabularBasicBivariateDistribution",
                                "The secondary bin index cannot be determined "
                                "with correlated sampling (an index of zero "
                                "will always be returned)!" );

    secondary_bin_index = 0;

    return TwoDGridPolicySamplingFunctorCreationCorrelatedBaseHelper::createBasicSamplingFunctor<BaseUnivariateDistributionType>();
  }
};

/*! \brief Partial specialization of the
 * Utility::Details::TwoDGridPolicySamplingFunctorCreationHelper
 * for Utility::Direct
 */
template<typename TwoDInterpPolicy>
struct TwoDGridPolicySamplingFunctorCreationHelper<Utility::Direct<TwoDInterpPolicy> > : public TwoDGridPolicySamplingFunctorCreationUncorrelatedBaseHelper
{ /* ... */ };

/*! \brief Partial specialization of the
 * Utility::Details::TwoDGridPolicySamplingFunctorCreationHelper
 * for Utility::UnitBase
 */
template<typename TwoDInterpPolicy>
struct TwoDGridPolicySamplingFunctorCreationHelper<Utility::UnitBase<TwoDInterpPolicy> > : public TwoDGridPolicySamplingFunctorCreationUncorrelatedBaseHelper
{ /* ... */ };

/*! \brief Partial specialization of the
 * Utility::Details::TwoDGridPolicySamplingFunctorCreationHelper
 * for Utility::Correlated
 */
template<typename TwoDInterpPolicy>
struct TwoDGridPolicySamplingFunctorCreationHelper<Utility::Correlated<TwoDInterpPolicy> > : public TwoDGridPolicySamplingFunctorCreationCorrelatedBaseHelper
{ /* ... */ };

/*! \brief Partial specialization of the
 * Utility::Details::TwoDGridPolicySamplingFunctorCreationHelper
 * for Utility::Correlated
 */
template<typename TwoDInterpPolicy>
struct TwoDGridPolicySamplingFunctorCreationHelper<Utility::UnitBaseCorrelated<TwoDInterpPolicy> > : public TwoDGridPolicySamplingFunctorCreationCorrelatedBaseHelper
{ /* ... */ };

} // end Details namespace

// Default constructor
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution()
{
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution(
    const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
    const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
    secondary_distributions,
    const double fuzzy_boundary_tol,
    const double evaluate_relative_error_tol,
    const double evaluate_error_tol,
    const unsigned max_number_of_iterations )
  : BaseType( primary_indep_grid,
              secondary_distributions,
              fuzzy_boundary_tol,
              evaluate_relative_error_tol,
              evaluate_error_tol,
              max_number_of_iterations )
{
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Grid constructor
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution(
  const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
  const std::vector<std::vector<SecondaryIndepQuantity> >& secondary_indep_grids,
  const std::vector<std::vector<DepQuantity> >& dependent_values,
  const double fuzzy_boundary_tol,
  const double evaluate_relative_error_tol,
  const double evaluate_error_tol,
  const unsigned max_number_of_iterations )
{
  TEST_FOR_EXCEPTION( primary_indep_grid.size() != secondary_indep_grids.size(),
                      Utility::BadBivariateDistributionParameter,
                      "The interpolated fully tabular basic bivariate "
                      "distribution cannot be constructed because the number "
                      "of primary grid points ("
                      << primary_indep_grid.size() << ") does not match the "
                      "number of secondary indep grids ("
                      << secondary_indep_grids.size() << ")!" );

  TEST_FOR_EXCEPTION( primary_indep_grid.size() != dependent_values.size(),
                      Utility::BadBivariateDistributionParameter,
                      "The interpolated fully tabular basic bivariate "
                      "distribution cannot be constructed because the number "
                      "of primary grid points ("
                      << primary_indep_grid.size() << ") does not match the "
                      "number of dependent value grids ("
                      << dependent_values.size() << ")!" );

  // Construct the univariate distributions
  std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >
    secondary_distributions( primary_indep_grid.size() );

  for( size_t i = 0; i < primary_indep_grid.size(); ++i )
  {
    secondary_distributions[i].reset(
      new UnitAwareTabularDistribution<typename TwoDGridPolicy::TwoDInterpPolicy::SecondaryBasePolicy,SecondaryIndependentUnit,DependentUnit>(
                                                      secondary_indep_grids[i],
                                                      dependent_values[i] ) );
  }

  // Set the distribution data
  this->setDistribution( primary_indep_grid, secondary_distributions );

  this->setEvaluationTolerances( fuzzy_boundary_tol,
                                 evaluate_relative_error_tol,
                                 evaluate_error_tol,
                                 max_number_of_iterations );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

//---------------------------------------------------------------------------//
// EVALUATING METHODS
//---------------------------------------------------------------------------//

// Evaluate the distribution
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluate(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            max_secondary_indep_var_functor ) const -> DepQuantity
{
  return this->template evaluateImpl<DepQuantity>(
                                         primary_indep_var_value,
                                         secondary_indep_var_value,
                                         min_secondary_indep_var_functor,
                                         max_secondary_indep_var_functor,
                                         &BaseUnivariateDistributionType::evaluate );
}

// Evaluate the secondary conditional PDF
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            max_secondary_indep_var_functor ) const
  -> InverseSecondaryIndepQuantity
{
  return this->template evaluateImpl<InverseSecondaryIndepQuantity>(
                                primary_indep_var_value,
                                secondary_indep_var_value,
                                min_secondary_indep_var_functor,
                                max_secondary_indep_var_functor,
                                &BaseUnivariateDistributionType::evaluatePDF );
}

// Evaluate the secondary conditional CDF
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->evaluateCDFImpl( primary_indep_var_value,
                                secondary_indep_var_value,
                                &BaseUnivariateDistributionType::evaluateCDF );
}

template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            max_secondary_indep_var_functor ) const
{
  return this->evaluateCDFImpl( primary_indep_var_value,
                                secondary_indep_var_value,
                                min_secondary_indep_var_functor,
                                max_secondary_indep_var_functor,
                                &BaseUnivariateDistributionType::evaluateCDF );
}

// Evaluate the distribution using the desired CDF evaluation method
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename EvaluationMethod>
double UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateCDFImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluateCDF ) const
{
  // Create the lower bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    min_secondary_indep_var_functor = std::bind<SecondaryIndepQuantity>(
                        &ThisType::getLowerBoundOfSecondaryConditionalIndepVar,
                        std::cref( *this ),
                        std::placeholders::_1 );

  // Create the upper bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    max_secondary_indep_var_functor = std::bind<SecondaryIndepQuantity>(
                        &ThisType::getUpperBoundOfSecondaryConditionalIndepVar,
                        std::cref( *this ),
                        std::placeholders::_1 );

  return this->evaluateCDFImpl( primary_indep_var_value,
                                secondary_indep_var_value,
                                min_secondary_indep_var_functor,
                                max_secondary_indep_var_functor,
                                evaluateCDF );
}

// Evaluate the distribution using the desired CDF evaluation method
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename EvaluationMethod>
double UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateCDFImpl(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity secondary_indep_var_value,
             const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
             min_secondary_indep_var_functor,
             const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
             max_secondary_indep_var_functor,
             EvaluationMethod evaluateCDF,
             unsigned max_number_of_iterations ) const
{
  // Find the bin boundaries
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDGridPolicy::template evaluateCDF<BaseUnivariateDistributionType>(
                                             primary_indep_var_value,
                                             secondary_indep_var_value,
                                             min_secondary_indep_var_functor,
                                             max_secondary_indep_var_functor,
                                             evaluateCDF,
                                             lower_bin_boundary,
                                             upper_bin_boundary,
                                             this->getFuzzyBoundTolerance(),
                                             this->getRelativeErrorTolerance(),
                                             this->getErrorTolerance(),
                                             max_number_of_iterations );
  }
  // Primary value is outside of the primary grid limits
  else
  {
    if( this->arePrimaryLimitsExtended() )
    {
      return ((*lower_bin_boundary->second).*evaluateCDF)(secondary_indep_var_value);
    }
    else
      return 0.0;
  }
}

// Return a random sample from the secondary conditional PDF
/*! \details If the primary value provided is outside of the primary grid
 * limits the appropriate limiting secondary distribution will be used to
 * create the sample. The alternative to this behavior is to throw an exception
 * unless the distribution has been extended by calling the
 * extendBeyondPrimaryIndepLimits method. Since this is a performance critical
 * method we decided against this behavior.
 */
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = Details::TwoDGridPolicySamplingFunctorCreationHelper<TwoDGridPolicy>::template createBasicSamplingFunctor<BaseUnivariateDistributionType>();

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF
/*! \details If the primary value provided is outside of the primary grid
 * limits the appropriate limiting secondary distribution will be used to
 * create the sample. The alternative to this behavior is to throw an exception
 * unless the distribution has been extended by calling the
 * extendBeyondPrimaryIndepLimits method. Since this is a performance critical
 * method we decided against this behavior.
 */
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditional(
            const PrimaryIndepQuantity primary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            max_secondary_indep_var_functor ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = Details::TwoDGridPolicySamplingFunctorCreationHelper<TwoDGridPolicy>::template createBasicSamplingFunctor<BaseUnivariateDistributionType>();

  return this->sampleImpl( primary_indep_var_value,
                           sampling_functor,
                           min_secondary_indep_var_functor,
                           max_secondary_indep_var_functor );
}

// Return a random sample and record the number of trials
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordTrials(
                          const PrimaryIndepQuantity primary_indep_var_value,
                          DistributionTraits::Counter& trials ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor and trials updater functor
  std::function<void()> trials_updater;

  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = Details::TwoDGridPolicySamplingFunctorCreationHelper<TwoDGridPolicy>::template createSamplingFunctorWithTrialsCounter<BaseUnivariateDistributionType>( trials, trials_updater );

  trials_updater();

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF and the index
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            size_t& primary_bin_index,
                            size_t& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Dummy variable
  SecondaryIndepQuantity dummy_raw_sample;

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = Details::TwoDGridPolicySamplingFunctorCreationHelper<TwoDGridPolicy>::template createSamplingFunctorWithSecondaryBinIndex<BaseUnivariateDistributionType>( secondary_bin_index );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sampling_functor,
                                   dummy_raw_sample,
                                   primary_bin_index );
}

// Return a random sample from the secondary conditional PDF
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            size_t& primary_bin_index,
                            size_t& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = Details::TwoDGridPolicySamplingFunctorCreationHelper<TwoDGridPolicy>::template createSamplingFunctorWithSecondaryBinIndex<BaseUnivariateDistributionType>( secondary_bin_index );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sampling_functor,
                                   raw_sample,
                                   primary_bin_index );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                       &BaseUnivariateDistributionType::sampleWithRandomNumber,
                       std::placeholders::_1,
                       random_number );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            max_secondary_indep_var_functor ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                       &BaseUnivariateDistributionType::sampleWithRandomNumber,
                        std::placeholders::_1,
                        random_number );

  return this->sampleImpl( primary_indep_var_value,
                           sampling_functor,
                           min_secondary_indep_var_functor,
                           max_secondary_indep_var_functor );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfSecondaryConditionalIndepVar( primary_indep_var_value ) );

  // Generate a random number
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
             min_secondary_indep_var_functor,
             const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
             max_secondary_indep_var_functor,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
    -> SecondaryIndepQuantity
{
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfSecondaryConditionalIndepVar( primary_indep_var_value ) );

  // Generate a random number
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                    primary_indep_var_value,
                                    random_number,
                                    min_secondary_indep_var_functor,
                                    max_secondary_indep_var_functor,
                                    max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfSecondaryConditionalIndepVar( primary_indep_var_value ) );

  // Create the lower bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    lower_bound_functor = std::bind<SecondaryIndepQuantity>(
                              &ThisType::getLowerBoundOfSecondaryConditionalIndepVar,
                              std::cref( *this ),
                              std::placeholders::_1 );

  // Create the upper bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    upper_bound_functor = std::bind<SecondaryIndepQuantity>(
                              &ThisType::getUpperBoundOfSecondaryConditionalIndepVar,
                              std::cref( *this ),
                              std::placeholders::_1 );

  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                  primary_indep_var_value,
                                  random_number,
                                  lower_bound_functor,
                                  upper_bound_functor,
                                  max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
    const PrimaryIndepQuantity primary_indep_var_value,
    const double random_number,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
    min_secondary_indep_var_functor,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
    max_secondary_indep_var_functor,
    const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    min_secondary_indep_var_functor( primary_indep_var_value ) );

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&, const SecondaryIndepQuantity)>
  subrange_sample_functor = std::bind<SecondaryIndepQuantity>(
            &BaseUnivariateDistributionType::sampleWithRandomNumberInSubrange,
            std::placeholders::_1,
            random_number,
            std::placeholders::_2 );

  // Find the bin boundaries
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                          lower_bin_boundary,
                          upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDGridPolicy::sampleInSubrange( subrange_sample_functor,
                                             min_secondary_indep_var_functor,
                                             max_secondary_indep_var_functor,
                                             primary_indep_var_value,
                                             lower_bin_boundary,
                                             upper_bin_boundary,
                                             max_secondary_indep_var_value );
  }
  else
  {
    if( this->arePrimaryLimitsExtended() )
    {
      if( max_secondary_indep_var_value <
          max_secondary_indep_var_functor( primary_indep_var_value ) )
      {
        return subrange_sample_functor( *lower_bin_boundary->second,
                                        max_secondary_indep_var_value );
      }
      else
      {
        return subrange_sample_functor( *lower_bin_boundary->second,
                                        lower_bin_boundary->second->getUpperBoundOfIndepVar() );
      }
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
                      "Sampling beyond the primary grid boundaries "
                      "cannot be done unless the grid has been extended ("
                      << primary_indep_var_value << " not in ["
                      << this->getLowerBoundOfPrimaryIndepVar() << ","
                      << this->getUpperBoundOfPrimaryIndepVar() << "])!" );
    }
  }
}

// Method for placing the object in an output stream
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
void UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->interpolatedFullyTabularToStreamImpl( os,
                                              "InterpolatedFullyTabularBasicBivariateDistribution" );
}

// Method for placing the object in an output stream
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename... Types>
void UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::interpolatedFullyTabularToStreamImpl(
                                                   std::ostream& os,
                                                   const std::string& name,
                                                   const Types&... data ) const
{
  this->toStreamTabularDistImpl( os,
                                 name,
                                 std::make_pair( "interp", TwoDGridPolicy::TwoDInterpPolicy::name() ),
                                 std::make_pair( "grid", TwoDGridPolicy::name() ),
                                 data... );
}

// Save the distribution to an archive
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

// Load the distribution from an archive
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

} // end Utility namespace

EXTERN_EXPLICIT_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DIST_FULL( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution, void, void, void );

#endif // UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularBasicBivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
