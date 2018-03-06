//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedFullyTabularBasicBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular basic bivariate dist. class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_SERIALIZATION_DISTRIBUTION5_EXPORT_IMPLEMENT( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution );

namespace Utility{

namespace Details{

//! Helper class used to construct a cdf interpolation policy
template<typename YProcessingTag, typename XProcessingTag>
struct CDFInterpolationHelper
{ /* ... */ };

//! Helper class used to construct a LinLinLin cdf interpolation policy
template<>
struct CDFInterpolationHelper<LinIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLinLin CDFInterpPolicy;
};

//! Helper class used to construct a LinLinLog cdf interpolation policy
template<>
struct CDFInterpolationHelper<LinIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLinLog CDFInterpPolicy;
};

//! Helper class used to construct a LinLinLogCos cdf interpolation policy
template<>
struct CDFInterpolationHelper<LinIndepVarProcessingTag,LogCosIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLinLogCos CDFInterpPolicy;
};

//! Helper class used to construct a LinLogLin cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogLin CDFInterpPolicy;
};

//! Helper class used to construct a LinLogLog cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogLog CDFInterpPolicy;
};

//! Helper class used to construct a LinLogLogCos cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogIndepVarProcessingTag,LogCosIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogLogCos CDFInterpPolicy;
};

//! Helper class used to construct a LinLogCosLin cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogCosIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogCosLin CDFInterpPolicy;
};

//! Helper class used to construct a LinLogCosLog cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogCosIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogCosLog CDFInterpPolicy;
};
  
} // end Details namespace

// Default constructor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution()
{
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
  : BaseType( primary_indep_grid, secondary_distributions )
{
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Grid constructor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution(
       const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
       const std::vector<std::vector<SecondaryIndepQuantity> >& secondary_indep_grids,
       const std::vector<std::vector<DepQuantity> >& dependent_values,
       const double fuzzy_boundary_tol,
       const double evaluate_relative_error_tol,
       const double evaluate_error_tol )
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
          new UnitAwareTabularDistribution<typename TwoDInterpPolicy::SecondaryBasePolicy,SecondaryIndependentUnit,DependentUnit>(
                                                      secondary_indep_grids[i],
                                                      dependent_values[i] ) );
  }

  // Set the distribution data
  this->setDistribution( primary_indep_grid, secondary_distributions );
  
  this->setEvaluationTolerances( fuzzy_boundary_tol,
                                 evaluate_relative_error_tol,
                                 evaluate_error_tol );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

//---------------------------------------------------------------------------//
// EVALUATING METHODS
//---------------------------------------------------------------------------//

// Evaluate the secondary conditional CDF
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  typedef typename Details::CDFInterpolationHelper<typename TwoDInterpPolicy::SecondIndepVarProcessingTag,typename TwoDInterpPolicy::FirstIndepVarProcessingTag>::CDFInterpPolicy CDFInterpPolicy;
  
  return this->template evaluateImpl<CDFInterpPolicy,double>(
                                primary_indep_var_value,
                                secondary_indep_var_value,
                                &BaseUnivariateDistributionType::evaluateCDF );

  // if ( TwoDSamplePolicy::name() == "Direct" )
  // {
  //   return this->template evaluateCDFImpl<TwoDInterpPolicy>(
  //                                       primary_indep_var_value,
  //                                       secondary_indep_var_value,
  //                                       &BaseUnivariateistributionType::evaluateCDF );
  // }
  // else
  // {
  //   return this->template evaluateCDFImpl<CDFInterpPolicy>(
  //                                       primary_indep_var_value,
  //                                       secondary_indep_var_value,
  //                                       &BaseUnivariateistributionType::evaluateCDF );
  // }
}

template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            max_secondary_indep_var_functor ) const
{
  typedef typename Details::CDFInterpolationHelper<typename TwoDInterpPolicy::SecondIndepVarProcessingTag,typename TwoDInterpPolicy::FirstIndepVarProcessingTag>::CDFInterpPolicy CDFInterpPolicy;

  return this->template evaluateCDFImpl<CDFInterpPolicy>(
                                primary_indep_var_value,
                                secondary_indep_var_value,
                                min_secondary_indep_var_functor,
                                max_secondary_indep_var_functor,
                                &BaseUnivariateDistributionType::evaluateCDF );
  
  // if ( TwoDSamplePolicy::name() == "Direct" )
  // {
  //   return this->template evaluateCDFImpl<TwoDInterpPolicy>(
  //                                       primary_indep_var_value,
  //                                       secondary_indep_var_value,
  //                                       min_secondary_indep_var_functor,
  //                                       max_secondary_indep_var_functor,
  //                                       &BaseUnivariateistributionType::evaluateCDF );
  // }
  // else
  // {
  //   return this->template evaluateCDFImpl<CDFInterpPolicy>(
  //                                       primary_indep_var_value,
  //                                       secondary_indep_var_value,
  //                                       min_secondary_indep_var_functor,
  //                                       max_secondary_indep_var_functor,
  //                                       &BaseUnivariateistributionType::evaluateCDF );
  // }
}

// Evaluate the distribution using the desired CDF evaluation method
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename LocalTwoDInterpPolicy, typename EvaluationMethod>
double UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateCDFImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluateCDF ) const
{
  // Create the lower bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    min_secondary_indep_var_functor = std::bind<SecondaryIndepQuantity>(
                                &ThisType::getLowerBoundOfConditionalIndepVar,
                                std::cref( *this ),
                                std::placeholders::_1 );

  // Create the upper bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    max_secondary_indep_var_functor = std::bind<SecondaryIndepQuantity>(
                                &ThisType::getUpperBoundOfConditionalIndepVar,
                                std::cref( *this ),
                                std::placeholders::_1 );

  return this->evaluateCDFImpl<LocalTwoDInterpPolicy,EvaluationMethod>(
              primary_indep_var_value,
              secondary_indep_var_value,
              min_secondary_indep_var_functor,
              max_secondary_indep_var_functor,
              evaluateCDF );
}

// Evaluate the distribution using the desired CDF evaluation method
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename LocalTwoDInterpPolicy, typename EvaluationMethod>
double UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateCDFImpl(
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
  typename DistributionTypeConstIterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDSamplePolicy::template evaluateCDF<LocalTwoDInterpPolicy,BaseUnivariateDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity>(
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

// Return a random sample from the secondary conditional PDF and the index
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
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

// Return a random sample from the secondary conditional PDF
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
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
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
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
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
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
  std::function<SecondaryIndepQuantity(const BaseUnivariateistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                        &BaseUnivariateistributionType::sampleWithRandomNumber,
                        std::placeholders::_1,
                        random_number );

  return this->sampleImpl( primary_indep_var_value,
                           sampling_functor,
                           min_secondary_indep_var_functor,
                           max_secondary_indep_var_functor );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
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
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
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
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );

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
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
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
                              &ThisType::getLowerBoundOfConditionalIndepVar,
                              std::cref( *this ),
                              std::placeholders::_1 );

  // Create the upper bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    upper_bound_functor = std::bind<SecondaryIndepQuantity>(
                              &ThisType::getUpperBoundOfConditionalIndepVar,
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
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
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
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                          lower_bin_boundary,
                          upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDSamplePolicy::template sampleInSubrange<TwoDInterpPolicy,PrimaryIndepQuantity,SecondaryIndepQuantity>(
                    subrange_sample_functor,
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
                      "Error: Sampling beyond the primary grid boundaries "
                      "cannot be done unless the grid has been extended ("
                      << primary_indep_var_value << " not in ["
                      << this->getLowerBoundOfPrimaryIndepVar() << ","
                      << this->getUpperBoundOfPrimaryIndepVar() << "])!" );
    }
  }
}

// Method for placing the object in an output stream
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
void UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamTabularDistImpl( os,
                                 "InterpolatedFullyTabularBasicBivariateDistribution",
                                 std::make_pair( "interp", TwoDInterpPolicy::name() ),
                                 std::make_pair( "sampling", TwoDSamplingPolicy::name() ) );
}

// Save the distribution to an archive
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

// Load the distribution from an archive
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}
  
} // end Utility namespace

EXTERN_EXPLICIT_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DIST( Utility::InterpolatedFullyTabularBasicBivariateDistribution, void, void, void );

#endif // UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularBasicBivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
