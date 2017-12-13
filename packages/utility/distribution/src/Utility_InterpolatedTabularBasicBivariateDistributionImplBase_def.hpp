//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedTabularBasicBivariateDistributionImplBase_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated tabular two-dimensional dist. helper class defs.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_IMPL_BASE_DEF_HPP
#define UTILITY_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_IMPL_BASE_DEF_HPP

// FRENSIE Includes
#include "Utility_PartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_FullyTabularBasicBivariateDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename TwoDInterpPolicy, typename Distribution>
UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
  : BaseType( primary_indep_grid, secondary_distributions )
{
  // Verify that the distribution data is valid
  this->verifyValidData( primary_indep_grid, secondary_distributions );
}

// Set the distribution
template<typename TwoDInterpPolicy, typename Distribution>
void UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::setDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
{
  // Set the distribution
  Distribution::setDistribution( primary_indep_grid, secondary_distributions );
  
  // Verify that the distribution data is valid
  this->verifyValidData( primary_indep_grid, secondary_distributions );
}

// Verify that the distribution data is valid
template<typename TwoDInterpPolicy, typename Distribution>
void UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::verifyValidData(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
{
  // Check that there is at least one bin specified
  TEST_FOR_EXCEPTION( primary_indep_grid.size() <= 1,
                      Utility::BadBivariateDistributionParameter,
                      "The interpolated tabular basic bivariate distribution "
                      "cannot be created because at least one primary bin "
                      "needs to be specified!" );

  // Check that every univariate distribution is compatible with the
  // interpolation type
  typename std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >::const_iterator bad_secondary_dist =
    std::find_if( secondary_distributions.begin(),
                  secondary_distributions.end(),
                  [](const std::shared_ptr<const BaseUnivariateDistributionType>& dist){ return !dist->template isCompatibleWithInterpType<typename TwoDInterpPolicy::SecondaryBasePolicy>(); } );

  TEST_FOR_EXCEPTION( bad_secondary_dist != secondary_distributions.end(),
                      Utility::BadBivariateDistributionParameter,
                      "The interpolated tabular basic bivariate distribution "
                      "cannot be created because the secondary distribution "
                      "at index "
                      << std::distance( secondary_distributions.begin(), bad_secondary_dist ) <<
                      " is not compatible with " << TwoDInterpPolicy::name() <<
                      " interpolation!" );
}
 
// Evaluate the distribution
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluate(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseUnivariateDistributionType::evaluate);
}

// Evaluate the secondary conditional PDF
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseUnivariateDistributionType::evaluatePDF );
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy, typename Distribution>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluate,
                        const ReturnType below_lower_bound_return,
                        const ReturnType above_upper_bound_return ) const
{
  // Find the bin boundaries
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );
  
  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*Utility::get<1>( *lower_bin_boundary )).*evaluate)(secondary_indep_var_value);
    else 
      return QuantityTraits<ReturnType>::zero();
  }
  else
  {
    // Create the grid evaluation functors
    std::function<ReturnType(const SecondaryIndepQuantity)>
      evaluate_grid_0_functor =
      std::bind<ReturnType>( evaluate,
                             std::cref(Utility::get<1>( *lower_bin_boundary )),
                             std::placeholders::_1 );
  
    std::function<ReturnType(const SecondaryIndepQuantity)>
      evaluate_grid_1_functor =
      std::bind<ReturnType>( evaluate,
                             std::cref(Utility::get<1>( *upper_bin_boundary )),
                             std::placeholders::_1 );
  
    return LocalTwoDInterpPolicy::interpolateUnitBase(
             Utility::get<0>( *lower_bin_boundary ),
             Utility::get<0>( *upper_bin_boundary ),
             primary_indep_var_value,
             secondary_indep_var_value,
             Utility::get<1>( *lower_bin_boundary )->getLowerBoundOfIndepVar(),
             Utility::get<1>( *lower_bin_boundary )->getUpperBoundOfIndepVar(),
             Utility::get<1>( *upper_bin_boundary )->getLowerBoundOfIndepVar(),
             Utility::get<1>( *upper_bin_boundary )->getUpperBoundOfIndepVar(),
             evaluate_grid_0_functor,
             evaluate_grid_1_functor,
             below_lower_bound_return,
             above_upper_bound_return );
  }
}

// Return a random sample from the secondary conditional PDF
/*! \details A stochastic sampling procedure is used. If the primary value
 * provided is outside of the primary grid limits the appropriate limiting
 * secondary distribution will be used to create the sample. The alternative
 * to this behavior is to throw an exception unless the distribution has 
 * been extended by calling the extendBeyondPrimaryIndepLimits method. Since
 * this is a performance critical method we decided against this behavior.
 */
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                                             &BaseUnivariateDistributionType::sample,
                                             std::placeholders::_1 );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample and record the number of trials
/*! \details A stochastic sampling procedure is used. If the primary value
 * provided is outside of the primary grid limits the appropriate limiting
 * secondary distribution will be used to create the sample. The alternative
 * to this behavior is to throw an exception unless the distribution has 
 * been extended by calling the extendBeyondPrimaryIndepLimits method. Since
 * this is a performance critical method we decided against this behavior.
 */
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            DistributionTraits::Counter& trials ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                              &BaseUnivariateDistributionType::sampleAndRecordTrials,
                              std::placeholders::_1,
                              std::ref( trials ) );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleDetailedImpl(
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

  DistributionDataConstIterator sampled_bin_boundary =
    this->sampleBinBoundary( primary_indep_var_value,
                             lower_bin_boundary,
                             upper_bin_boundary );

  // Calculate the index of the primary bin boundary that will be used to
  // create the secondary conditional sample
  primary_bin_index = this->calculateBinIndex( sampled_bin_boundary );

  // Create the raw sample
  raw_sample = sample_functor( *Utility::get<1>( *sampled_bin_boundary ) );

  // Calculate the intermediate grid limits
  SecondaryIndepQuantity y_x_min =
    this->getLowerBoundOfSecondaryConditionalIndepVar( primary_indep_var_value );

  SecondaryIndepQuantity y_x_max =
    this->getUpperBoundOfSecondaryConditionalIndepVar( primary_indep_var_value );

  typename QuantityTraits<SecondaryIndepQuantity>::RawType
    intermediate_grid_length =
    TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                                                            y_x_min, y_x_max );
  
  // Calculate the unit base variable on the bin boundary corresponding to the
  // raw sample
  typename QuantityTraits<SecondaryIndepQuantity>::RawType eta;

  {
    typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
          Utility::get<1>( *sampled_bin_boundary )->getLowerBoundOfIndepVar(),
          Utility::get<1>( *sampled_bin_boundary )->getUpperBoundOfIndepVar());
    
    eta = TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
           raw_sample,
           Utility::get<1>( *sampled_bin_boundary )->getLowerBoundOfIndepVar(),
           grid_length );
  }
  
  // Scale the sample so that it preserves the intermediate limits.
  // Note: This is a stochastic procedure. The intermediate distribution that
  //       has been sampled is not the true distribution. The expected value
  //       of a sample will be a sample from the true distribution though.
  return TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                                      eta, y_x_min, intermediate_grid_length );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleImpl(
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

// Sample the bin boundary that will be used for stochastic sampling
/*! \details This method will throw an exception if the primary independent
 * value is outside of the primary grid limits and the primary grid has not
 * been extended.
 */
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleBinBoundary(
    const PrimaryIndepQuantity primary_indep_var_value,
    const DistributionDataConstIterator& lower_bin_boundary,
    const DistributionDataConstIterator& upper_bin_boundary ) const
  -> DistributionDataConstIterator
{
  if( lower_bin_boundary != upper_bin_boundary )
  {
    // Calculate the interpolation fraction
    double interpolation_fraction;

    {
      const double processed_lower_bin_boundary = 
        TwoDInterpPolicy::processFirstIndepVar( Utility::get<0>( *lower_bin_boundary ) );

      interpolation_fraction =
        (TwoDInterpPolicy::processFirstIndepVar( primary_indep_var_value ) -
         processed_lower_bin_boundary)/
        (TwoDInterpPolicy::processFirstIndepVar( Utility::get<0>( *upper_bin_boundary ) ) -
         processed_lower_bin_boundary );
    }

    // Sample to determine the distribution that will be used
    double random_number =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( random_number < interpolation_fraction )
      return upper_bin_boundary;
    else
      return lower_bin_boundary;
  }
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return lower_bin_boundary;
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
}

// Return the upper bound of the conditional distribution
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::getUpperBoundOfSecondaryConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return Utility::get<1>( *lower_bin_boundary )->getUpperBoundOfIndepVar();
    else
      return QuantityTraits<SecondaryIndepQuantity>::zero();
  }
  else
  {
    return TwoDInterpPolicy::calculateIntermediateGridLimit(
           Utility::get<0>( *lower_bin_boundary ),
           Utility::get<0>( *upper_bin_boundary ),
           primary_indep_var_value,
           Utility::get<1>( *lower_bin_boundary )->getUpperBoundOfIndepVar(),
           Utility::get<1>( *upper_bin_boundary )->getUpperBoundOfIndepVar() );
  }
}

// Return the lower bound of the conditional distribution
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::getLowerBoundOfSecondaryConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return Utility::get<1>( *lower_bin_boundary )->getLowerBoundOfIndepVar();
    else
      return QuantityTraits<SecondaryIndepQuantity>::zero();
  }
  else
  {
    return TwoDInterpPolicy::calculateIntermediateGridLimit(
           Utility::get<0>( *lower_bin_boundary ),
           Utility::get<0>( *upper_bin_boundary ),
           primary_indep_var_value,
           Utility::get<1>( *lower_bin_boundary )->getLowerBoundOfIndepVar(),
           Utility::get<1>( *upper_bin_boundary )->getLowerBoundOfIndepVar() );
  }
}

// Test if the distribution is continuous in the primary dimension
template<typename TwoDInterpPolicy, typename Distribution>
bool UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::isPrimaryDimensionContinuous() const
{
  return true;
}

// Save the distribution to an archive
template<typename TwoDInterpPolicy, typename Distribution>
template<typename Archive>
void UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

// Load the distribution from an archive
template<typename TwoDInterpPolicy, typename Distribution>
template<typename Archive>
void UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,Distribution>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLin,Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLin,Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLog,Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLog,Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLin,Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLin,Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLog,Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLog,Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLin,Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLin,Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLog,Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLog,Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLin,Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLin,Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLog,Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLog,Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );


#endif // end UTILITY_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_IMPL_BASE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularBasicBivariateDistributionImplBase_def.hpp
//---------------------------------------------------------------------------//
