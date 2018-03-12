//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElasticBasicBivariateDistribution_def.hpp
//! \author Luke Kersting
//! \brief  The elastic bivariate dist. class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ELASTIC_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_ELASTIC_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_SERIALIZATION_DISTRIBUTION5_EXPORT_IMPLEMENT( UnitAwareElasticBasicBivariateDistribution );

namespace Utility{

namespace Details{

//! Helper class used to construct a cosine sampling policy
template<typename TwoDGridPolicy>
struct CosGridHelper
{
  //! The cosine sampling policy
  using CosGridPolicy = TwoDGridPolicy;
};

//! Helper class used to construct a UnitBase cosine sampling policy
template<typename TwoDInterpPolicy>
struct CosGridHelper<UnitBase<TwoDInterpPolicy> >
{
  //! The cosine sampling policy
  using CosGridPolicy = Direct<TwoDInterpPolicy>;
};

//! Helper class used to construct a UnitBaseCorrelated cosine sampling policy
template<typename TwoDInterpPolicy>
struct CosGridHelper<UnitBaseCorrelated<TwoDInterpPolicy> >
{
  //! The cosine sampling policy
  using CosGridPolicy = Correlated<TwoDInterpPolicy>;
};
  
} // end Details namespace

// Constructor
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareElasticBasicBivariateDistribution(
      const DistributionType& distribution,
      const SecondaryIndepQuantity upper_bound_conditional_indep_var,
      const double fuzzy_boundary_tol,
      const double evaluate_relative_error_tol,
      const double evaluate_error_tol )
  : ParentType( distribution,
                fuzzy_boundary_tol,
                evaluate_relative_error_tol,
                evaluate_error_tol ),
    d_upper_bound_conditional_indep_var( upper_bound_conditional_indep_var ),
    d_max_upper_bound_conditional_indep_var( SIQT::one() ),
    d_lower_bound_conditional_indep_var( -1.0*SIQT::one() )
{
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareElasticBasicBivariateDistribution(
      const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
      const std::vector<std::shared_ptr<const UnitAwareTabularUnivariateDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions,
      const SecondaryIndepQuantity upper_bound_conditional_indep_var,
      const double fuzzy_boundary_tol,
      const double evaluate_relative_error_tol,
      const double evaluate_error_tol )
  : BaseType( primary_indep_grid,
              secondary_distributions,
              fuzzy_boundary_tol,
              evaluate_relative_error_tol,
              evaluate_error_tol ),
    d_upper_bound_conditional_indep_var( upper_bound_conditional_indep_var ),
    d_max_upper_bound_conditional_indep_var( SIQT::one() ),
    d_lower_bound_conditional_indep_var( -1.0*SIQT::one() )
{
  this->verifyValidSecondIndepVarProcessingType();

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
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  return ThisType::evaluateImpl<DepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluate );
}

// Evaluate the secondary conditional PDF
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateImpl<InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseUnivariateDistributionType::evaluatePDF );
}

// Evaluate the secondary conditional PDF
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateImpl<InverseSecondaryIndepQuantity>(
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
double UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->evaluateCDFImpl( primary_indep_var_value,
                                secondary_indep_var_value,
                                &BaseOneDDistributionType::evaluateCDF );
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateImpl(
                        const PrimaryIndepQuantity incoming_energy,
                        const SecondaryIndepQuantity angle_cosine,
                        EvaluationMethod evaluate ) const
{
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= d_lower_bound_conditional_indep_var );
  testPrecondition( angle_cosine <= d_max_upper_bound_conditional_indep_var );

  // Find the bin boundaries
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( incoming_energy,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    // Create the lower bound functor
    std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
      min_secondary_indep_var_functor =
        [this](const PrimaryIndepQuantity x){
          return d_lower_bound_conditional_indep_var;
        };

    // Create the upper bound functor
    std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
      max_secondary_indep_var_functor =
        [this](const PrimaryIndepQuantity x){
          return d_upper_bound_conditional_indep_var;
        };

    return Details::CosGridHelper<TwoDGridPolicy>::CosGridPolicy::template evaluatePDFCos<BaseOneDDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity,ReturnType>(
        incoming_energy,
        angle_cosine,
        min_secondary_indep_var_functor,
        max_secondary_indep_var_functor,
        evaluate,
        lower_bin_boundary,
        upper_bin_boundary,
        this->getFuzzyBoundTolerance(),
        this->getRelativeErrorTolerance(),
        this->getErrorTolerance(),
        500 );
  }
  // Check for a primary value outside of the primary grid limits
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
    else
      return QuantityTraits<ReturnType>::zero();
  }
  // else if( lower_bin_boundary->first == primary_indep_var_value )
  // {
  //   return ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
  // }
  // else if( upper_bin_boundary->first == primary_indep_var_value )
  // {
  //   return ((*upper_bin_boundary->second).*evaluate)(angle_cosine);
  // }
  // else
  // {
  //   // Get the evaluation at the lower and upper bin boundaries
  //   ReturnType min_eval_0 = ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
  //   ReturnType min_eval_1 = ((*upper_bin_boundary->second).*evaluate)(angle_cosine);

  //   if ( min_eval_0 == min_eval_1 )
  //     return min_eval_0;
  //   else
  //   {
  //     // Return the interpolated evaluation
  //     return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
  //             lower_bin_boundary->first,
  //             upper_bin_boundary->first,
  //             primary_indep_var_value,
  //             min_eval_0,
  //             min_eval_1 );
  //   }
  // }
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateImpl(
            const PrimaryIndepQuantity incoming_energy,
            const SecondaryIndepQuantity angle_cosine,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            EvaluationMethod evaluate,
            unsigned max_number_of_iterations ) const
{
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= d_lower_bound_conditional_indep_var );
  testPrecondition( angle_cosine <= d_max_upper_bound_conditional_indep_var );

  // Find the bin boundaries
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( incoming_energy,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return Details::CosGridHelper<TwoDGridPolicy>::CosGridPolicy::template evaluatePDFCos<BaseOneDDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity,ReturnType>(
        incoming_energy,
        angle_cosine,
        min_secondary_indep_var_functor,
        max_secondary_indep_var_functor,
        evaluate,
        lower_bin_boundary,
        upper_bin_boundary,
        this->getFuzzyBoundTolerance(),
        this->getRelativeErrorTolerance(),
        this->getErrorTolerance(),
        500 );
  }
  // Check for a primary value outside of the primary grid limits
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
    else
      return QuantityTraits<ReturnType>::zero();
  }
}

// Evaluate the CDF using the desired evaluation method
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename EvaluationMethod>
inline double UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateCDFImpl(
                        const PrimaryIndepQuantity incoming_energy,
                        const SecondaryIndepQuantity angle_cosine,
                        EvaluationMethod evaluateCDF ) const
{
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= d_lower_bound_conditional_indep_var );
  testPrecondition( angle_cosine <= d_max_upper_bound_conditional_indep_var );

  // Find the bin boundaries
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( incoming_energy,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    // Create the lower bound functor
    std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
      min_secondary_indep_var_functor =
        [this](const PrimaryIndepQuantity x){
          return d_lower_bound_conditional_indep_var;
        };

    // Create the upper bound functor
    std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
      max_secondary_indep_var_functor =
        [this](const PrimaryIndepQuantity x){
          return d_upper_bound_conditional_indep_var;
        };

    return Details::CosGridHelper<TwoDGridPolicy>::CosGridPolicy::template evaluateCDFCos<BaseOneDDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity>(
        incoming_energy,
        angle_cosine,
        min_secondary_indep_var_functor,
        max_secondary_indep_var_functor,
        evaluateCDF,
        lower_bin_boundary,
        upper_bin_boundary,
        this->getFuzzyBoundTolerance(),
        this->getRelativeErrorTolerance(),
        this->getErrorTolerance(),
        500 );
  }
  // Check for a primary value outside of the primary grid limits
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluateCDF)(angle_cosine);
    else
      return 0.0;
  }
}

// Evaluate the CDF using the desired evaluation method
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename EvaluationMethod>
inline double UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateCDFImpl(
            const PrimaryIndepQuantity incoming_energy,
            const SecondaryIndepQuantity angle_cosine,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            EvaluationMethod evaluateCDF,
            unsigned max_number_of_iterations ) const
{
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= d_lower_bound_conditional_indep_var );
  testPrecondition( angle_cosine <= d_max_upper_bound_conditional_indep_var );

  // Find the bin boundaries
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( incoming_energy,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return Details::CosGridHelper<TwoDGridPolicy>::CosGridPolicy::template evaluateCDFCos<BaseOneDDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity>(
        incoming_energy,
        angle_cosine,
        min_secondary_indep_var_functor,
        max_secondary_indep_var_functor,
        evaluateCDF,
        lower_bin_boundary,
        upper_bin_boundary,
        this->getFuzzyBoundTolerance(),
        this->getRelativeErrorTolerance(),
        this->getErrorTolerance(),
        500 );
  }
  // Check for a primary value outside of the primary grid limits
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluateCDF)(angle_cosine);
    else
      return 0.0;
  }
}

////---------------------------------------------------------------------------//
//// SAMPLING METHODS
////---------------------------------------------------------------------------//

// Return a random sample from the secondary conditional PDF
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseUnivariateDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}


// Return a random sample from the secondary conditional PDF
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditional(
    const PrimaryIndepQuantity primary_indep_var_value,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>& min_secondary_indep_var_functor,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>& max_secondary_indep_var_functor ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditional( primary_indep_var_value );
}

// Return a random sample and record the number of trials
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            DistributionTraits::Counter& trials ) const
  -> SecondaryIndepQuantity
{
  ++trials;
  return this->sampleSecondaryConditional( primary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the sample.
 */
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            size_t& primary_bin_index,
                            size_t& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Dummy variable
  SecondaryIndepQuantity dummy_raw_sample;
  
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                            &BaseUnivariateDistributionType::sampleAndRecordBinIndex,
                            std::placeholders::_1,
                            std::ref( secondary_bin_index ) );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sampling_functor,
                                   dummy_raw_sample,
                                   primary_bin_index );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the raw_sample. The raw_sample is the original sample
 * that was made before the scaling operation was done.
 */
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            size_t& primary_bin_index,
                            size_t& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                            &BaseUnivariateDistributionType::sampleAndRecordBinIndex,
                            std::placeholders::_1,
                            std::ref( secondary_bin_index ) );

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
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
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

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the sample functor
  const double random_number =
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
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
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
                    d_lower_bound_conditional_indep_var );

  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
      sampling_functor;

  // Check if the max_secondary_indep_var_value is greater than the max indep value at the energy
  if ( max_secondary_indep_var_value >
       d_upper_bound_conditional_indep_var )
  {
    // Create the sampling functor
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseUnivariateDistributionType::sampleWithRandomNumberInSubrange,
                             std::placeholders::_1,
                             random_number,
                             d_upper_bound_conditional_indep_var );
  }
  else
  {
    // Create the sampling functor
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseUnivariateDistributionType::sampleWithRandomNumberInSubrange,
                             std::placeholders::_1,
                             random_number,
                             max_secondary_indep_var_value );
  }

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename SampleFunctor>
inline auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const
  -> SecondaryIndepQuantity
{
  // Dummy variables
  SecondaryIndepQuantity dummy_raw_sample;
  size_t dummy_primary_bin_index;

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sample_functor,
                                   dummy_raw_sample,
                                   dummy_primary_bin_index );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename SampleFunctor>
inline auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleDetailedImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor,
                            SecondaryIndepQuantity& raw_sample,
                            size_t& primary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  SecondaryIndepQuantity sample;
  if( lower_bin_boundary != upper_bin_boundary )
  {
    DistributionDataConstIterator sampled_bin_boundary;
    
    sample = Details::CosGridHelper<TwoDGridPolicy>::CosGridPolicy::template sampleCosDetailed<PrimaryIndepQuantity,SecondaryIndepQuantity>(
          sample_functor,
          primary_indep_var_value,
          lower_bin_boundary,
          upper_bin_boundary,
          sampled_bin_boundary,
          raw_sample );

    // Calculate the index of the primary bin boundary that will be used to
    // create the secondary conditional sample
    primary_bin_index = this->calculateBinIndex( sampled_bin_boundary );
  }
  else
  {
    if( this->arePrimaryLimitsExtended() )
    {
      raw_sample = sample_functor( *lower_bin_boundary->second );
      sample = raw_sample;

      // Calculate the index of the primary bin boundary that will be used to
      // create the secondary conditional sample
      primary_bin_index = this->calculateBinIndex( lower_bin_boundary );
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
                       "Error: Sampling beyond the primary grid boundaries "
                       "cannot be done unless the grid has been extended ("
                       << primary_indep_var_value << " not in ["
                       << this->getLowerBoundOfPrimaryIndepVar() << ","
                       << this->getUpperBoundOfPrimaryIndepVar() << "])!" );
    }
  }
  return sample;
}

////---------------------------------------------------------------------------//
//// MISC. FUNCTIONS
////---------------------------------------------------------------------------//

// Return the lower bound of the conditional distribution
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::getLowerBoundOfSecondaryConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Check for a primary value outside of the primary grid limits
  if( primary_indep_var_value < this->getLowerBoundOfPrimaryIndepVar() ||
      primary_indep_var_value > this->getUpperBoundOfPrimaryIndepVar() )
  {
    if( this->arePrimaryLimitsExtended() )
      return d_lower_bound_conditional_indep_var;
    else
      return SIQT::zero();
  }
  else
    return d_lower_bound_conditional_indep_var;
}

// Return the upper bound of the conditional distribution
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::getUpperBoundOfSecondaryConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Check for a primary value outside of the primary grid limits
  if( primary_indep_var_value < this->getLowerBoundOfPrimaryIndepVar() ||
      primary_indep_var_value > this->getUpperBoundOfPrimaryIndepVar() )
  {
    if( this->arePrimaryLimitsExtended() )
      return d_upper_bound_conditional_indep_var;
    else
      return SIQT::zero();
  }
  else
    return d_upper_bound_conditional_indep_var;
}

// Test if the second independent variable is compatible with Cosine processing
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
void UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::verifyValidSecondIndepVarProcessingType()
{
  testStaticPrecondition( (std::is_same<typename TwoDGridPolicy::TwoDInterpPolicy::SecondIndepVarProcessingTag,LogCosIndepVarProcessingTag>::value ||
                           std::is_same<typename TwoDGridPolicy::TwoDInterpPolicy::SecondIndepVarProcessingTag,LinIndepVarProcessingTag>::value) );
}

// Method for placing the object in an output stream
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
void UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->interpolatedFullyTabularToStreamImpl( os,
                                              "ElasticBasicBivariateDistribution",
                                              std::make_pair( "max conditional upper bound", d_max_upper_bound_conditional_indep_var ),
                                              std::make_pair( "conditional upper bound", d_upper_bound_conditional_indep_var ),
                                              std::make_pair( "conditional lower bound", d_lower_bound_conditional_indep_var ) );
}

// Save the distribution to an archive
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_max_upper_bound_conditional_indep_var );
  ar & BOOST_SERIALIZATION_NVP( d_upper_bound_conditional_indep_var );
  ar & BOOST_SERIALIZATION_NVP( d_lower_bound_conditional_indep_var );
}

// Load the distribution from an archive
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_max_upper_bound_conditional_indep_var );
  ar & BOOST_SERIALIZATION_NVP( d_upper_bound_conditional_indep_var );
  ar & BOOST_SERIALIZATION_NVP( d_lower_bound_conditional_indep_var );
}

} // end Utility namespace

#define __ELASTIC_BASIC_BIVARIATE_DIST_WITH_SAMPLE_POLICY__( DECL_TYPE, TwoDGridPolicy, ... ) \
  DECL_TYPE##_DISTRIBUTION_INST( Utility::UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy<Utility::LinLinLin>,__VA_ARGS__ > ); \
  DECL_TYPE##_DISTRIBUTION_INST( Utility::UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy<Utility::LinLogCosLin>,__VA_ARGS__ > ); \
  DECL_TYPE##_DISTRIBUTION_INST( Utility::UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy<Utility::LinLinLog>,__VA_ARGS__ > ); \
  DECL_TYPE##_DISTRIBUTION_INST( Utility::UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy<Utility::LinLogCosLog>,__VA_ARGS__ > ); \
  DECL_TYPE##_DISTRIBUTION_INST( Utility::UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy<Utility::LogLinLin>,__VA_ARGS__ > ); \
  DECL_TYPE##_DISTRIBUTION_INST( Utility::UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy<Utility::LogLogCosLin>,__VA_ARGS__ > ); \
  DECL_TYPE##_DISTRIBUTION_INST( Utility::UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy<Utility::LogLinLog>,__VA_ARGS__ > ); \
  DECL_TYPE##_DISTRIBUTION_INST( Utility::UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy<Utility::LogLogCosLog>,__VA_ARGS__ > )

#define ___ELASTIC_BASIC_BIVARIATE_DIST__( DECL_TYPE, ... ) \
  __ELASTIC_BASIC_BIVARIATE_DIST_WITH_SAMPLE_POLICY__( DECL_TYPE, Utility::Direct, __VA_ARGS__ ); \
  __ELASTIC_BASIC_BIVARIATE_DIST_WITH_SAMPLE_POLICY__( DECL_TYPE, Utility::UnitBase, __VA_ARGS__ ); \
  __ELASTIC_BASIC_BIVARIATE_DIST_WITH_SAMPLE_POLICY__( DECL_TYPE, Utility::CumulativePoints, __VA_ARGS__ ); \
  __ELASTIC_BASIC_BIVARIATE_DIST_WITH_SAMPLE_POLICY__( DECL_TYPE, Utility::Correlated, __VA_ARGS__ ); \
  __ELASTIC_BASIC_BIVARIATE_DIST_WITH_SAMPLE_POLICY__( DECL_TYPE, Utility::UnitBaseCorrelated, __VA_ARGS__ )

#define EXTERN_EXPLICIT_ELASTIC_BASIC_BIVARIATE_DIST( ... ) \
  ___ELASTIC_BASIC_BIVARIATE_DIST__( EXTERN_EXPLICIT, __VA_ARGS__ )

#define EXPLICIT_ELASTIC_BASIC_BIVARIATE_DIST( ... ) \
  ___ELASTIC_BASIC_BIVARIATE_DIST__( EXPLICIT, __VA_ARGS__ )

EXTERN_EXPLICIT_ELASTIC_BASIC_BIVARIATE_DIST( void, void, void );

#endif // UTILITY_ELASTIC_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ElasticBasicBivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
